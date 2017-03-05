# Privilege

Find out more about the linux system

## Information & Users
Who are you?
```shell
root@admin:~# id
root@admin:~# who
root@admin:~# w
root@admin:~# last
root@admin:~# cat /etc/passwd | cut -d: -f1    # List of users
root@admin:~# grep -v -E "^#" /etc/passwd | awk -F: '$3 == 0 { print $1}'   # List of super users
root@admin:~# awk -F: '($3 == "0") {print}' /etc/passwd   # List of super users
root@admin:~# cat /etc/sudoers
root@admin:~# sudo -l

```
sensitive files?
```shell
root@admin:~# cat /etc/passwd
root@admin:~# cat /etc/group
root@admin:~# cat /etc/shadow
root@admin:~# ls -alh /var/mail/
```
What has the user being doing?
```shell
root@admin:~# cat ~/.bash_history
root@admin:~# cat ~/.nano_history
root@admin:~# cat ~/.atftp_history
root@admin:~# cat ~/.mysql_history
root@admin:~# cat ~/.php_history
```
file systems
```shell
root@admin:~# mount
root@admin:~# df -h
root@admin:~# cat /etc/fstab
```

## Operating System

What's the distribution type? What version?

```shell
root@admin:~# cat /etc/issue
root@admin:~# cat /etc/*-release
root@admin:~# cat /etc/lsb-release # Debian based
root@admin:~# cat /etc/redhat-release   # Redhat based
```

What's the kernel version? Is it 64-bit?

```shell
root@admin:~# cat /proc/version
root@admin:~# uname -a
root@admin:~# dmesg | grep Linux
root@admin:~# ls /boot | grep vmlinuz-
```
Environmental variables?
```shell
root@admin:~# echo "$PATH"

```

printer?
```shell
root@admin:~# lpstat -a
```

## Applications & Services

What services are running? Which service has which user privilege?
```shell
root@admin:~# ps aux
root@admin:~# ps -ef
root@admin:~# top
root@admin:~# cat /etc/services

```
What applications are installed? What version are they? Are they currently running?

```shell
root@admin:~# ls -alh /usr/bin/
root@admin:~# ls -alh /sbin/
root@admin:~# dpkg -l #debian
root@admin:~# rpm -qa  #red hat
```


What jobs are scheduled?

```shell
root@admin:~# crontab -l
root@admin:~# cat /etc/crontab
root@admin:~# cat /var/spool/cron/crontabs/root
```

## Networks

What NIC(s) does the system have? Is it connected to another network?

```shell
root@admin:~# ifconfig
root@admin:~# cat /etc/network/interfaces
root@admin:~# cat /etc/sysconfig/network
```
DHCP server? DNS server? Gateway?
```shell
root@admin:~# cat /etc/resolv.conf
root@admin:~# cat /etc/sysconfig/network
root@admin:~# cat /etc/networks
root@admin:~# hostname
root@admin:~# dnsdomainname
```
What other users & hosts are communicating with the system?
```shell
root@admin:~# lsof -i
root@admin:~# lsof -i :80
root@admin:~# grep 80 /etc/services
root@admin:~# netstat -antup
root@admin:~# netstat -antpx
root@admin:~# netstat -tulpn
root@admin:~# last
root@admin:~# w
```
Whats cached? IP and/or MAC addresses
```shell
root@admin:~# arp -e
root@admin:~# route
root@admin:~# route -ne

```
