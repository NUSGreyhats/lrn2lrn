# Users, Files and Processes

## Superuser

In Linux, the administrator or privileged user is the superuser.
The superuser has the username `root` and a user ID (UID) of 0.
Some Linux distributions, such as Ubuntu, lock the root account by
default to prevent any user from logging in directly as root. This
prevents the security risks of a bug in a program or attackers
from corrupting the system due to a vulnerability being exploited
as root.

To switch to root, execute the following command:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ su
```

It starts a new shell as the target user. If the account is locked,
we cannot switch to the user. Although there are ways to unlock the
root account and enable root logins, it is NOT recommended.

Root has access to many system files and can execute special
commands that normal users are not allowed to execute. Only root
can start services at privileged ports 0-1023.

Instead of switching to root, we execute commands as root only when
it is necessary.

Prepend this command to the command we want to execute so that the
command is executed with root privileges:

```shell
sudo
```

## passwd file

The file `/etc/passwd` contains the user account information of all
users. From the manual, the format of the password file is as follows:

```
username:encrypted_password:UID:GID:comments:home_directory:shell
```

The `encrypted_password` field was previously used to store the password.
The encrypted password is now stored in the `/etc/shadow` file. An `x` in
this field indicates that the encrypted password is in the shadow file.
All users can access this file because some programs need the user account
information.

The group ID (GID) is the ID of the user's default group. The UID and
GID is usually the same number, with the group name same as the username.

The comments field includes other account information, usually the
fullname.

The shell field indicates the initial login program.

An example of the password file:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ cat /etc/passwd
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
sys:x:3:3:sys:/dev:/usr/sbin/nologin
sync:x:4:65534:sync:/bin:/bin/sync
...
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$
```

View the whole manual:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ man 5 passwd
```

## shadow file

The `/etc/shadow` file stores password information of all user accounts.
Root privileges are needed to view this file. From the manual, the
format of the shadow file is as follows:

```
username:encrypted_password:date_of_last_password_change:min_age:max_age:warning_period:inactivity_period:account_expiration_date:reserved
```

For the `encrypted_password` field, an `!` indicates that the password is
locked. An `*` indicates that the user cannot login using a password but
may login by other means.

An example of the shadow file:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ sudo cat /etc/shadow
root:!:17093:0:99999:7:::
daemon:*:17001:0:99999:7:::
bin:*:17001:0:99999:7:::
sys:*:17001:0:99999:7:::
sync:*:17001:0:99999:7:::
...
```

View the format of the encrpted password:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ man 3 crypt
```

View the whole manual:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ man 5 passwd
```

Let's try to crack the password for the user `alice`.

The [password file][1]:

```
alice:x:1000:1000:alice,,,:/home/alice:/bin/bash
```

The [shadow file][2]:

```
alice:$6$1tMUFOTC$Hz55wORf/SpWS50S9ZGwXffcAAfeWCiT7l/WInQkIlyQ2AfOIG4bgft4ANSE8uED1D8qHpHoSx43hITBAKVei0:17228:0:99999:7:::
```

John the Ripper is a tool used to crack weak passwords on Unix,
Windows and other OS.

Install John the Ripper:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes/files$ sudo apt-get install john
```

Combine the password file and the shadow file:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes/files$ unshadow passwd shadow > mypasswd
```

Run the tool:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes/files$ john mypasswd
Loaded 1 password hash (crypt, generic crypt(3) [?/64])
Press 'q' or Ctrl-C to abort, almost any other key for status
secret           (alice)
1g 0:00:00:03 100% 2/3 0.2551g/s 239.5p/s 239.5c/s 239.5C/s 123456..pepper
Use the "--show" option to display all of the cracked passwords reliably
Session completed
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes/files$
```

The password for `alice` is `secret`.

To prevent passwords from being cracked easily, we should enforce password
policies. Some rules include the requirements of:

- Minimum length
- Combination of alphabets, digits and symbols
- Password expiry date
- No reuse of previous passwords

## group file

The `/etc/group` file contains the all group information. Users can belong to
more than 1 group. The password file shows the GID of the default group only.
We can retrieve the other groups a user belong to from the group file. From the
manual, the format of the group file is as follows:

```
group_name:encrypted_password:GID:members_username
```

An example of the group file:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ cat /etc/group
root:x:0:
daemon:x:1:
bin:x:2:
sys:x:3:
adm:x:4:syslog,ubuntu
...
```

View the whole manual:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ man 5 group
```

## Files

In Linux, directories (aka folders) and devices are treated as files.
The root directory `/` is the main directory of the file system
containing other subdirectories.

The subdirectories of the root directory includes:

- `/root`: Home directory of user `root`
- `/bin`: Common programs for system, system adminsitrator and users
- `/sbin`: Programs for system and system administrator
- `/etc`: Configuration files
- `/boot`: Startup files and kernel
- `/dev`: Devices
- `/lib`: Library files
- `/usr`: User-related programs
- `/mnt`: Mount point for external file systems
- `/var`: Variable files and temporary files created by users
- `/tmp`: Temporary files that will be deleted upon reboot
- `/home`: Home directories of users

`.` is the current directory while `..` is the parent directory.

To print the (current) working directory:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ pwd
/vagrant/lessons/1_users_files_processes
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$
```

When a server requests for a file path to display the contents,
an attacker may use `../` to traverse to the parent directory.

It is not recommended to filter out `../` strings because
the same string can come in many forms using unicode characters.

The `/` character can be represented as `%2F`, `%CO%AF` and others.

A simple string replace that loops through the string once and
replaces the string upon finding the substring is vulnerable.

A [sample][3] python script:

```python
#!/bin/python

def main():
    s = "....//....//a.out"
    print s
    print s.replace("../", "")

if __name__ == "__main__":
    main()
```

Prints the following:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes/script$ python filter.py
....//....//a.out
../../a.out
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes/script$
```

For the string:

```
string:            ....//
position:          012345
replaced string:   ../
previous position: 015
```

When at position 4, the replace() function found a match of `../`
and replaces characters 2 to 4. The pointer is now at position 5
but the string buffer only has the character `/`. Since the replace()
function loop once, the remaining characters at position 1, 2 and 5
of the form `../` is not filtered.

To prevent attacker from accessing other files outside the
intended directory, get the canonical path, a unique full file
path with `../` and symbolic links resolved, and validate the
path.

## Processes

Processes are running programs with a process ID (PID) and other
information required for program execution. The parent process
`init` with PID 1 spawns other processes.

View the active processes:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ ps -aux
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root         1  0.1  0.2 119584  5808 ?        Ss   07:18   0:01 /sbin/init splash
root         2  0.0  0.0      0     0 ?        S    07:18   0:00 [kthreadd]
root         3  0.0  0.0      0     0 ?        S    07:18   0:00 [ksoftirqd/0]
...
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$
```

Processes are spawned by using `fork()`, which creates a child
process, and `exec()`, which replaces the current process image
with a new process image.

An [example][4] usage of `fork()` and `exec()`:

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    int childPid;

    childPid = fork();

    if (childPid) {
        printf("Parent process\n");
    } else {
        printf("Child process\n");
        execl("/bin/ls", "ls", NULL);
    }

    return 0;
}
```

The [binary][5] spawns a child process and the child process
execute the command `ls`.

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes/build$ ./process
/process 
Parent process
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes/build$ Child process
ls  process
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes/build$
```

An attacker may use a fork bomb to launch a DoS attack. A fork bomb is
a process continuously replicating itself through an infinite loop to
deplete available system resources.

**CAUTION! DO NOT TRY THIS ON YOUR MACHINE!**

The source code looks like this:

```c
#include <unistd.h>

void main() {
    while (1) {
        fork();
    }
}
```

## Environment Variables

Environment variables can affect a process. As the name suggests, it
is a part of the environment of a process.

View all environment variables:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ env
```

or:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ printenv
```

One of the most important environment variable is `PATH`. It specifies
the search path to look for the program to be executed if the program
is not built into the shell or the program was not specified with its
full path. The search stops when the program name is found in a
directory specified and the program is executed.

View the value of the `PATH` environment variable:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ printenv PATH
```

or:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ echo $PATH
```

An attacker may store a malicious program in a directory at the start
of the search path and masquerades itself as a common program used by
many users.

Let's try to masquerade as a `ls` command.

Locate the full path of `ls`:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ which ls
/bin/ls
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$
```

Using a simple [binary][6] with the following [source code][7]:

```c
#include <stdio.h>

int main(int argc, char** argv) {
    int i;

    for (i = 1; i < argc; i++) {
        printf("%s  ", argv[i]);
    }

    printf("\n");

    return 0;
}
```

Compile the binary:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ gcc -o ls ls.c
```

Temporarily prepend the directory to the search path:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ PATH="/vagrant/lessons/1_users_files_processes/build:$PATH"
```

or permanently prepend the directory to the search path:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes$ export PATH=/vagrant/lessons/1_users_files_processes/build:$PATH
```

or store the binary in one of the directory in the search path
before the directory `/bin` since the actual full path of `ls`
is `/bin/ls`.

Try executing the command `ls`. Is the command executed the actual
command the user wanted?

Verify that the location of `ls` is the location of our binary:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes/build$ which ls
/vagrant/lessons/1_users_files_processes/build/ls
ubuntu@ubuntu-xenial:/vagrant/lessons/1_users_files_processes/build$
```

To prevent the execution of another program instead of the system
command, we should explicitly use the full path of the command and
ensure that the system files are not tampered with by using tools,
such as Tripwire, that monitor the data integrity of files.

[1]: ./files/passwd
[2]: ./files/shadow
[3]: ./script/filter.py
[4]: ./src/process.c
[5]: ./build/process
[6]: ./build/ls
[7]: ./src/ls.c