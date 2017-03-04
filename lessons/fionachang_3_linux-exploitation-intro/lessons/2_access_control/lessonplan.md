# Access Control

Access control is the permission to access resources. In Linux, the
resources can be files, directories or devices. The resources are
treated as files.

There are 2 types of access control:

1. Discretionary Access Control: Owner sets the permissions
2. Mandatary Access Control: Based on system-wide policies

## Access Control Matrix

A table with the users and files as the rows and columns can be used
to specify the access rights to resources. However, storing a table
wastes space as it can grow very large.

There are 2 approaches to storing the access contol matrix:

1. Access Control List (ACL): List of access rights of a resource
2. Capabilities: List of capabilities of a user to access a resource

Linux uses ACL.

The lists can be compressed by grouping the users or files.

## File Permissions

The permission bits of a resource looks like this:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$ ls -al
total 12
drwxrwxr-x 2 ubuntu ubuntu 4096 Mar  3 20:17 .
drwxrwxr-x 4 ubuntu ubuntu 4096 Mar  3 20:17 ..
-rw-rw-r-- 1 ubuntu ubuntu   18 Mar  3 20:18 lessonplan.md
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$
```

The output of long format:

```
file_permissions number_of_links owner_username owner_group file_size timestamp_last_modification file_name
```

The `file_permission` field format:

```
drwxrwxr-x
||  |  |
||  |  other
||  |
||  group
||
|owner
|
file type
```

The file type includes:

- `-`: Regular file
- `d`: Directory
- `l`: Symbolic link

The 3 permission bits for owner, group and other:

- `r`: Read
- `w`: Write
- `x`: Execute

For directories, the permissions allows us to:

- Read: View the files in the directory (Using `ls`)
- Write: Create and delete files in the directory and rename the directory
- Execute: Enter the directory (Using `cd`) and access files and directories inside 

If the user accessing the resource is the owner or group, the
respective permission bits will be applied. Otherwise, the
permission bits of other will be applied.

To change the permissions of a file:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$ ls -l lessonplan.md
-rw-rw-r-- 1 ubuntu ubuntu 2578 Mar  4 03:11 lessonplan.md
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$ chmod u+x lessonplan.md
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$ ls -l lessonplan.md
-rwxrw-r-- 1 ubuntu ubuntu 2578 Mar  4 03:11 lessonplan.md
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$
```

For the first character, use `u`, `g`, `o` or `a` to specify user, group,
other or all respectively. For the second character, use `+`, `-` or `=`
to add, remove or set the permission respectively.

Alternatively, we can set the permissions using octal digits.

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$ chmod 664 lessonplan.md
```

`7` indicates `rwx` are set. Usually, the permissions for regular files
are `644` and permissions for directories are `755`.

## SUID, SGID and Sticky bits

Set UID (SUID) and set GID (SGID) bit allows the process to be executed
as the owner or group respectively.

The `passwd` command changes the password of user accounts by updating
the `/etc/shadow` file. However, only root can edit the shadow file.
To allow normal users to change their password, the SUID bit for the
`passwd` command is set. Normal users can run `passwd` as root and
it will have writing access to the shadow file. The process has obtained
elevated privileges to access sensitive data.

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$ ls -l /usr/bin/passwd /etc/shadow
-rw-r----- 1 root shadow  1269 Mar  4 01:48 /etc/shadow
-rwsr-xr-x 1 root root   54256 Mar 29  2016 /usr/bin/passwd
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$
```

Sticky bit restricts the deletion of files and directories such that only
root, owner or users with write permissions are allowed to delete them.
It is useful for publically accessible directories such as `/tmp`.

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$ ls -l / | grep tmp
drwxrwxrwt  10 root root  4096 Mar  4 03:37 tmp
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$
```

Set SUID, SGID and sticky bits:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$ chmod u+s lessonplan.md
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$ chmod g+s lessonplan.md
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$ chmod o+t lessonplan.md
```

or using octal representation:

```shell
ubuntu@ubuntu-xenial:/vagrant/lessons/2_access_control$ chmod 7644 lessonplan.md
```

`7` indicates `sst` are set.

If the `x` bit is set, the special bits are represented in lowercase.
Otherwise, they are in uppercase.