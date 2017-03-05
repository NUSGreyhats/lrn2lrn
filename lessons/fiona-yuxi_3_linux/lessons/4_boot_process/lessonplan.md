# Traditional Boot Process

The traditional boot process of Linux starts when power is supplied
to the machine.

The sequence is as follows:

```
                        jumps        loads and
       fetches           to          executes        executes        executes          executes        executes
Reset    ==>    Reset    ==>   BIOS     ==>     MBR    ==>     GRUB    ==>     Kernel    ==>     init    ==>     Runlevel
                Vector
```

## Reset

When power is supplied, the hardware ensures that power sources are
stable. Various hardware subsystems start self-checks and
initialization in parallel. Memory and disk are not up.

For single-core processor systems, the processor is the Bootstrap
Processor (BSP). For multiprocessor and multicore systems, a hardware
voting protocol is used to determine which core will be the BSP after
the processors finished their internal self-check. Only the BSP
executes the boot sequence while others are locked by semaphores.

The instructor pointer is set to the reset vector.

## Reset Vector

Reset vector is the first instruction fetched. It is a jump to the
actual entry of the BIOS. The address of the reset vector
differ from processor to processor, usually at 16 bytes below 1 MB
(0xFFFF0 or 0x000FFFF0) or 16 bytes below 4 GB (0xFFFFFFF0). Since
the memory and disk is not up yet, the chipset, chips supporting the
processor, must ensure that one location of the BIOS is mapped to the
reset vector.

## BIOS

Basic Input/Output System (BIOS) is a firmware for hardware
initialization and booting. It resides in a non-volatile memory, which
will not be erased upon reboot, typically an Electrically Erasable
Programmable Read-Only Memory (EEPROM) sitting on the motherboard.

Updating the BIOS is done by flashing the EEPROM. If flashing is not
done properly, it may permanently locked up the motherboard and it is
not recoverable. Since the BIOS is required when flashing, reflashing
a corrupted BIOS will not work.

Functionalities include:

- USB booting
- USB hub
- USB keyboard and mouse

BIOS then executes the Power-On Self-Test (POST) which:

- Checks whether registers are working
- Checks integrity of BIOS code by checking the signature, which may
fail if flashing the BIOS is not done properly
- Verify basic components such as timer and interrupt controller
- Find the size and check system memory
- Initialize the BIOS
- Identify various devices and boot them in various sequence

Since memory is not available, cache is used as memory when running
the program to do the testing. When memory is up and available, the
BIOS is ready to load the OS. The BIOS loads and executes the MBR,
which loads the GRUB boot loader. Then, the BIOS jumps to the GRUB
boot loader.

### MBR

Master Boot Record (MBR) is the first sector of the primary boot disk.
The primary boot disk is one of the hard disk designated when setting
up the hard disk and it is bootable. It contains the bootstrap code of
around 400 bytes and a partition table. The partition table has 4
entries so only 4 primary partition is allowed. The partition table
entries consist of the starting and ending head, sector and cylinder.

## GRUB

GRUB boot loader is the bootstrap code section of the MBR. GRUB loads
the kernel and initial RAM disk. Then, it jumps to the kernel.

The stages of GRUB:

- GRUB Stage 1 (boot.img): The MBR itself. Since boot.img is only
around 400 bytes, its purpose it to locate, read in and jump to
diskboot.img.
- GRUB Stage 1.5 (diskboot.img): Loads the rest of GRUB and transfers
control to grub_main().
- GRUB Stage 2 (grub_main()):
  - Initialize console
  - Loads and parse the GRUB configuration file
  - Loads modules
  - Fill in Linux kernel header, the data structures that the kernel
  uses

### GRUB Configuration File

GRUB allows users to select which OS to boot up.

An example of a boot information of an OS in the GRUB configuration
file in Ubuntu:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/4_boot_process$ cat /boot/grub/grub.cfg
...
menuentry 'Ubuntu' --class ubuntu --class gnu-linux --class gnu --class os $menu
entry_id_option 'gnulinux-simple-3e032db5-2c68-4eb4-9725-76d06228adad' {
        recordfail
        load_video
        gfxmode $linux_gfx_mode
        insmod gzio
        if [ x$grub_platform = xxen ]; then insmod xzio; insmod lzopio; fi
        insmod part_msdos
        insmod ext2
        set root='hd0,msdos1'
        if [ x$feature_platform_search_hint = xy ]; then
          search --no-floppy --fs-uuid --set=root --hint-bios=hd0,msdos1 --hint-
efi=hd0,msdos1 --hint-baremetal=ahci0,msdos1  3e032db5-2c68-4eb4-9725-76d06228ad
ad
        else
          search --no-floppy --fs-uuid --set=root 3e032db5-2c68-4eb4-9725-76d06228adad
        fi
        linux   /boot/vmlinuz-4.4.0-64-generic root=UUID=3e032db5-2c68-4eb4-9725-76d06228adad ro  quiet splash $vt_handoff
        initrd  /boot/initrd.img-4.4.0-64-generic
}
...
ubuntu@ubuntu-xenial:/vagrant/lessons/4_boot_process$
```

The line `set root='hd0,msdos1'` indicates disk and partition that
the OS resides in. `hd` represents hard disk, `fd` represents floppy
disk and `cd` represents CD-ROM. The disk starts from `0`. `msdos`
indicates the partition and it starts from `1`. Partitions numbered
`1` to `4` are for physical partitions while partitions numbered
`5` and above are for extended partitions. In this example, the OS
resides in the first partition of the first hard disk.

The line `linux   /boot/vmlinuz-4.4.0-64-generic root=UUID=3e032db5-2c68-4eb4-9725-76d06228adad ro  quiet splash $vt_handoff`
indicates the Linux kernel location and its parameters.

The line `initrd  /boot/initrd.img-4.4.0-64-generic` inidicates the
initial RAM disk.

## Kernel

A kernel is the core of an OS. The OS is a software that runs in
kernel mode with complete access to all hardware resources. Other
software runs in user mode with limited access to hardware resources.
The kernel allows software in user mode to interact with the hardware
resources.

High-level view of the OS:

```
|---------------|
| User Programs | } User mode
|---------------|
|      OS       | } Kernel mode
|---------------|
|    Hardware   |
|---------------|
```

Features of the kernel:

- Interacts with hardware
- Provides system call interface
- Special code for interrupt handlers and device drivers

The older versions of kernel consist of the file `vmlinux`, which is a
statically linked (all libraries are linked in during compilation)
executable file containing the entire kernel, and other files. Newer
versions of kernel directly uses `vmlinuz`, which is a compressed
version of `vmlinux`.

When GRUB transfers control to the kernel, the kernel does
more initialization including setting up the stack and heap,
initializing the console and checks for the memory. The kernel is
decompressed and does more initialization.

The kernel mounts the inital RAM disk, `initrd` which is a temporary,
simple root file system, `/`, in the memory. It is needed because
there are no files since the OS have not boot up yet.

Then, the kernel executes the process `init`.

## init

init is the first user level process with PID 1. Other processes are
spawned from the init process. init is the parent of all processes
so killing the init process will shut down the machine.

The init process can be:

- `/sbin/init`
- `/etc/init`
- `/bin/init`
- `/bin/sh`

The init process is dependent on the Linux distribution. It loads all 
necessary drivers and switches from `initrd` to the disk root file
system.

It ends with the user selecting a runlevel.

## Runlevel

Runlevel is one of the modes a Linux system will boot into.

Some runlevels include:

- `0` [`/etc/rc0.d`]: Halt
- `1` or `S` [`/etc/rc1.d`]: Single-user mode
- `3` [`/etc/rc3.d`]: Multi-user mode with networking
- `5` [`/etc/rc5.d`]: Runlevel 3 with GUI
- `6` [`/etc/rc6.d`]: Reboot

## Obtain Root Shell from GRUB Menu

Root shell can be obtained by changing the init process in the GRUB
configuration file to `/bin/sh` or boot to recovery mode of an OS.

Steps to change init process from the GRUB menu:

1. Hold `Shift` button to enter the GRUB menu
2. Press `e` to edit the configurations before booting to the OS
3. At line starting with `linux` (last second line), add `init=/bin/sh`
to the end of the line
4. Press `Ctrl` + `X` to boot the OS

A preventive measure is to use passwords to protect the configuration
and GRUB console. However, booting to an OS will also be password
protected.

This may be redundant since an attacker who have physical access to
the machine may use other means by booting from a CD or USB and
password protect makes it harder to recover the system.

We should focus on restricting physical access to the machine instead
of password protect the BIOS or GRUB.