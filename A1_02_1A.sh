#!/bin/bash

# ASSIGNMENT 1A

# Name :- Rishika Sur 
# Roll No. :- 002311001025
# Name :- Prama Ray
# Roll No. :- 002311001033
# Name :- Vidhi Mantry
# Roll No. :- 002311001043
#Group :- 02
# Sec. :- A1

# Questions:

#1) who:-It displays the information about all the users who have logged into the system currently

#[be2325@localhost os25]$ who
# (unknown) :0           2024-10-21 11:46 (:0)
# root     pts/0        2025-07-24 11:08 (172.16.5.159)
# be2361   pts/1        2025-07-24 12:05 (172.16.5.29)
# be2359   pts/3        2025-07-24 12:07 (172.16.5.29)
# be2316   pts/4        2025-07-24 12:13 (172.16.4.216)
# be2315   pts/6        2025-07-24 12:17 (172.16.4.209)
# be2353   pts/7        2025-07-24 12:10 (172.16.4.222)
# be2325   pts/8        2025-07-24 12:14 (172.16.4.211)
# be23L07  pts/9        2025-07-24 12:20 (172.16.5.16)
# be2348   pts/10       2025-07-24 12:22 (172.16.4.215)
# be2321   pts/12       2025-07-24 12:23 (172.16.4.204)
# be2320   pts/13       2025-07-24 12:24 (172.16.4.202)
# be2306   pts/14       2025-07-24 12:55 (172.16.4.203)
# be2312   pts/15       2025-07-24 12:35 (172.16.4.218)
# be2308   pts/16       2025-07-24 12:56 (172.16.4.207)
# be2309   pts/18       2025-07-24 12:39 (172.16.4.210)
# be2333   pts/19       2025-07-24 12:45 (172.16.4.214)
# be2338   pts/20       2025-07-24 12:45 (172.16.4.236)
# be2321   pts/21       2025-07-24 12:48 (172.16.4.204)
# be2345   pts/23       2025-07-24 12:48 (172.16.4.228)
# be2305   pts/24       2025-07-24 12:49 (172.16.4.225)

# 2) whoami:- It displays Current username, Terminal number, date and time at which user logged into the system

# [be2325@localhost os25]$ whoami
# be2325

# 3) pwd:- It displays current working directory

# [be2325@localhost os25]$ pwd
# /home/usr/student/ug/yr23/be2325/os25

# 4) date:- It displays system date and time

# [be2325@localhost os25]$ date
# Thu Jul 24 13:07:22 IST 2025

# 5) ls - It lists the files and directories stored in the current directory. To list the files in a directory use the following syntax: $ls dirnam

# [be2333@localhost ~]$ ls
# a.out  cnlab  cpnm33  dsalab  ooplab  ooslab  oosviva  selab

# 6) mkdir – It is used to create directories by using the command: $mkdir dirname
# [be2333@localhost ~]$ mkdir oslab
# [be2333@localhost ~]$ ls
# a.out  cnlab  cpnm33  dsalab  ooplab  ooslab  oosviva  oslab  selab

# 7) clear- It clears the screen

# [be2325@localhost os25]$ clear
# [be2325@localhost os25]$ 

# 8) cd - It is used to change the current working directory to any other directory specified
    
# [be2333@localhost ~]$ cd oslab
# [be2333@localhost oslab]$ 

# 9) df - It displays currently mounted file systems.

# [be2325@localhost os25]$ df
# Filesystem                   1K-blocks      Used  Available Use% Mounted on
# /dev/mapper/scientific-root   52399104  27788632   24610472  54% /
# devtmpfs                      32758584         0   32758584   0% /dev
# tmpfs                         32774652     10340   32764312   1% /dev/shm
# tmpfs                         32774652    789412   31985240   3% /run
# tmpfs                         32774652         0   32774652   0% /sys/fs/cgroup
# /dev/sda2                      1039616    238088     801528  23% /boot
# /dev/mapper/scientific-home 2256669952 136296944 2120373008   7% /home
# tmpfs                          6554932        16    6554916   1% /run/user/42
# tmpfs                          6554932         0    6554932   0% /run/user/3067
# tmpfs                          6554932         0    6554932   0% /run/user/3097
# tmpfs                          6554932         0    6554932   0% /run/user/3014
# tmpfs                          6554932         0    6554932   0% /run/user/3107
# tmpfs                          6554932         0    6554932   0% /run/user/3218
# tmpfs                          6554932         0    6554932   0% /run/user/3213
# tmpfs                          6554932         0    6554932   0% /run/user/3271
# tmpfs                          6554932         0    6554932   0% /run/user/3292
# tmpfs                          6554932         0    6554932   0% /run/user/3211
# tmpfs                          6554932         0    6554932   0% /run/user/3209
# tmpfs                          6554932         0    6554932   0% /run/user/3223
# tmpfs                          6554932         0    6554932   0% /run/user/3275
# tmpfs                          6554932         0    6554932   0% /run/user/0
# tmpfs                          6554932         0    6554932   0% /run/user/3264
# tmpfs                          6554932         0    6554932   0% /run/user/3262
# tmpfs                          6554932         0    6554932   0% /run/user/3256
# tmpfs                          6554932         0    6554932   0% /run/user/3219
# tmpfs                          6554932         0    6554932   0% /run/user/3228
# tmpfs                          6554932         0    6554932   0% /run/user/3354
# tmpfs                          6554932         0    6554932   0% /run/user/3251
# tmpfs                          6554932         0    6554932   0% /run/user/3224
# tmpfs                          6554932         0    6554932   0% /run/user/3215
# tmpfs                          6554932         0    6554932   0% /run/user/3236
# tmpfs                          6554932         0    6554932   0% /run/user/3248
# tmpfs                          6554932         0    6554932   0% /run/user/3208
# tmpfs                          6554932         0    6554932   0% /run/user/3232
# tmpfs                          6554932         0    6554932   0% /run/user/3234
# tmpfs                          6554932         0    6554932   0% /run/user/3231
# tmpfs                          6554932         0    6554932   0% /run/user/3235
# tmpfs                          6554932         0    6554932   0% /run/user/3246
# tmpfs                          6554932         0    6554932   0% /run/user/3212
# tmpfs                          6554932         0    6554932   0% /run/user/3222

# 10) rmdir - Directories can be deleted using the rmdir command - $rmdir dirname

# [be2333@localhost oslab]$ mkdir 1A
# [be2333@localhost oslab]$ ls
# 1A
# [be2333@localhost oslab]$ rmdir 1A
# [be2333@localhost oslab]$ ls

# 11) cat – It displays the contents of a file - $cat filename

# [be2333@localhost oslab]$ cat sample.txt
# // This is a Sample file

# //Sample C program

# #include<stdio.h>
# int main()
# {
# for(;;)
# {
# printf("Hi "+i);
# i++;
# }
# System.out.println("out of loop");
# return 0;
# }

# 12) cp - It is used to copy a file - $ cp source_file destination_file

# [be2333@localhost oslab]$ cp sample.txt sample.c
# [be2333@localhost oslab]$ cat sample.txt
# // This is a Sample file

# //Sample C program

# #include<stdio.h>
# int main()
# {
# for(;;)
# {
# printf("Hi "+i);
# i++;
# }
# System.out.println("out of loop");
# return 0;
# }

# [be2333@localhost oslab]$ cat sample.c
# // This is a Sample file

# //Sample C program

# #include<stdio.h>
# int main()
# {
# for(;;)
# {
# printf("Hi "+i);
# i++;
# }
# System.out.println("out of loop");
# return 0;
# }

# 13) mv- It is used to change the name of a file - $ mv old_file new_file

# [be2333@localhost oslab]$ mv sample.c sample1.c
# [be2333@localhost oslab]$ ls
# sample1.c  sample.txt

# 14) rm – It is used to delete an existing file - $ rm filename

# [be2333@localhost oslab]$ ls
# sample1.c  sample.txt
# [be2333@localhost oslab]$ rm sample.txt
# [be2333@localhost oslab]$ ls
# sample1.c

# 15) stat- It is used to display file or file system status - $ stat filename

# [be2333@localhost oslab]$ stat sample1.c
#   File: ‘sample1.c’
#   Size: 169       Blocks: 8          IO Block: 4096   regular file
# Device: fd02h/64770d Inode: 1610838551  Links: 1
# Access: (0644/-rw-r--r--)  Uid: ( 3236/  be2333)   Gid: ( 2926/  ugyr23)
# Context: unconfined_u:object_r:user_home_t:s0
# Access: 2025-07-24 13:25:44.917521805 +0530
# Modify: 2025-07-24 13:25:30.278521468 +0530
# Change: 2025-07-24 13:28:11.878525192 +0530
#  Birth: -
 
# 16) ln - It is used to create links between files and directories.

# [be2333@localhost oslab]$ ln sample1.c sample1.txt
# [be2333@localhost oslab]$ ls
# sample1.c  sample1.txt
# [be2333@localhost oslab]$ vi sample1.c

# Changes were made to only sample1.c but changes are also seen in sample1.txt as they are linked.

# [be2333@localhost oslab]$ cat sample1.c
# // This is a Sample file

# //Sample C program

# #include<stdio.h>
# int main()
# {
# int i=0;
# for(int j=0;;)
# {
# printf("Hi "+i);
# i++;
# }
# System.out.println("out of loop");
# return 0;
# }

#Previous sample1.txt : 

# // This is a Sample file

# //Sample C program

# #include<stdio.h>
# int main()
# {
# for(;;)
# {
# printf("Hi "+i);
# i++;
# }
# System.out.println("out of loop");
# return 0;
# }

# [be2333@localhost oslab]$ cat sample1.txt
# // This is a Sample file

# //Sample C program

# #include<stdio.h>
# int main()
# {
# int i=0; //Changes made here
# for(int j=0;;) //Changes made here
# {
# printf("Hi "+i);
# i++;
# }
# System.out.println("out of loop");
# return 0;
# }

# 17) tty – It prints the filename of the terminal connected to standard input.

# [be2333@localhost oslab]$ tty
# /dev/pts/19

# 18) uname –It prints system information

# [be2325@localhost os25]$ uname
# Linux

# 19) umask – It specifies user file creation mask, implying which of the 3 permissions are to be denied to the owner,group and others.

# [be2325@localhost os25]$ umask
# 0022

# 20) find – It searches for files in a directory hierarchy

# [be2325@localhost os25]$ find
# .
# ./A1_02_1A.sh

# 21) sort – It sorts the lines of text files

# [be2333@localhost oslab]$ sort sample1.txt


# {
# }

# {
# }
# for(int j=0;;)
# i++;
# #include<stdio.h>
# int i=0;
# int main()
# printf("Hi "+i);
# return 0;
# //Sample C program
# System.out.println("out of loop");
# // This is a Sample file

# 22) ps - It displays information about the current processes.

# [be2333@localhost oslab]$ ps
#   PID TTY          TIME CMD
# 14164 pts/19   00:00:00 bash
# 18911 pts/19   00:00:00 ps

# 23) chmod 777 file1 - gives full permission to owner, group and others

#[be2333@localhost oslab]$ chmod 777 sample1.txt

# 24) grep - It finds specific patterns in files.

# [be2333@localhost oslab]$ grep 'int' sample1.txt
# int main()
# int i=0;
# for(int j=0;;)
# printf("Hi "+i);
# System.out.println("out of loop");

# 25) touch - It creates an empty file or updates the timestamp of an existing file.

# [be2333@localhost oslab]$ touch sample.c
# [be2333@localhost oslab]$ ls
# sample.c  sample.txt

# 26) more/less - It displays file content one screen at a time, allowing you to scroll.

# [be2333@localhost oslab]$ more sample1.txt
# // This is a Sample file

# //Sample C program

# #include<stdio.h>
# int main()
# {
# int i=0;
# for(int j=0;;)
# {
# printf("Hi "+i);
# i++;
# }
# System.out.println("out of loop");
# return 0;
# }
# [be2333@localhost oslab]$ less sample1.txt




























# // This is a Sample file

# //Sample C program

# #include<stdio.h>
# int main()
# {      
#         int i=0;
#         for(int j=0;;)
#         {
#                 printf("Hi "+i);
#                 i++;
#         }
#         System.out.println("out of loop");
#         return 0;
# }
       
# sample1.txt (END)


# 27) head/tail - It displays First/Last 10 lines of a File.

# [be2333@localhost oslab]$ head sample1.txt
# // This is a Sample file

# //Sample C program

# #include<stdio.h>
# int main()
# {
# int i=0;
# for(int j=0;;)
# {

# [be2333@localhost oslab]$ tail sample1.txt
# int i=0;
# for(int j=0;;)
# {
# printf("Hi "+i);
# i++;
# }
# System.out.println("out of loop");
# return 0;
# }


# 28) top - It dynamically displays real-time information about system statistics.

# [be2333@localhost oslab]$ top
# top - 14:16:04 up 276 days,  2:29, 26 users,  load average: 0.00, 0.01, 0.05
# Tasks: 414 total,   1 running, 399 sleeping,  11 stopped,   0 zombie
# %Cpu(s):  0.0 us,  0.0 sy,  0.0 ni,100.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
# KiB Mem : 65549308 total, 53834476 free,  2387312 used,  9327520 buff/cache
# KiB Swap: 32899068 total, 32899068 free,        0 used. 61616688 avail Mem

#   PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND                                                                                            
# 20441 be2333    20   0  157996   2568   1556 R   0.7  0.0   0:00.28 top                                                                                                
#   10 root      20   0       0      0      0 S   0.3  0.0 328:09.28 rcu_sched                                                                                          
#     1 root      20   0  194444   7592   3988 S   0.0  0.0  29:30.43 systemd                                                                                            
#     2 root      20   0       0      0      0 S   0.0  0.0   0:25.75 kthreadd                                                                                            
#     3 root      20   0       0      0      0 S   0.0  0.0 360:10.51 ksoftirqd/0                                                                                        
#     8 root      rt   0       0      0      0 S   0.0  0.0   0:04.48 migration/0 

# 29) kill - It terminates a Process.

# [be2333@localhost oslab]$ ps
#   PID TTY          TIME CMD
# 14164 pts/19   00:00:00 bash
# 21430 pts/19   00:00:00 ps
# [be2333@localhost oslab]$ yes > /dev/null &[1] 11111
# [1] 21687
# bash: [1]: command not found...
# [be2333@localhost oslab]$ yes > /dev/null &
# [2] 21695
# [be2333@localhost oslab]$ ps
#   PID TTY          TIME CMD
# 14164 pts/19   00:00:00 bash
# 21687 pts/19   00:00:18 yes
# 21695 pts/19   00:00:07 yes
# 21705 pts/19   00:00:00 ps
# [be2333@localhost oslab]$ kill 21687
# [1]-  Terminated              yes > /dev/null
# [be2333@localhost oslab]$ ps
#   PID TTY          TIME CMD
# 14164 pts/19   00:00:00 bash
# 21695 pts/19   00:00:21 yes
# 21707 pts/19   00:00:00 ps
# [be2333@localhost oslab]$ ^C
# [be2333@localhost oslab]$ kill 21695
# [2]+  Terminated              yes > /dev/null
# [be2333@localhost oslab]$ ps
#   PID TTY          TIME CMD
# 14164 pts/19   00:00:00 bash
# 21761 pts/19   00:00:00 ps



# 30) history - It displays a list of previously executed commands.

# [be2325@localhost se25]$ history
#   36  javac q9.java
#   37  java Demo
#   38  vi q9.java
#   39  rm q9.java
#   40  vi q9.java
#   41  javac q9.java
#   42  java Demo
#   43  vi q16.java
#   44  w
#     .
#     .
#     .
#     .
#     .
#     .
#   1012  df
#   1013  uname
#   1014  umask
#   1015  find
#   1016  cd ..
#   1017  ls
#   1018  find
#   1019  ls
#   1020  cd se25
#   1021  find
#   1022  [be2333@localhost oslab]$ touch sample.c
#   1023  [be2333@localhost oslab]$ ls
#   1024  sample.c  sample.txt[be2333@localhost oslab]$ touch sample.c
#   1025  [be2333@localhost oslab]$ ls
#   1026  sample.c  sample.txt[be2333@localhost oslab]$ touch sample.c
#   1027  [be2333@localhost oslab]$ ls
#   1028  sample.c  sample.txt[be2333@localhost oslab]$ touch sample.c
#   1029  [be2333@localhost oslab]$ ls
#   1030  sample.c  sample.txt[be2333@localhost oslab]$ touch sample.c
#   1031  [be2333@localhost oslab]$ ls
#   1032  sample.c  sample.txt
#   1033  sort
#   1034  man sort
#   1035  history

# 31) du - It estimates file space usage (of a file or directory).

# [be2325@localhost se25]$ du
# 24	./ass1
# 16	./ass2
# 28	./ass3
# 8	./GitAss4
# 28	./ass4
# 104	.

# 32) ping - It tests network connectivity to a host.

# [be2325@localhost se25]$ ping 8.8.8.8
# PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
# 64 bytes from 8.8.8.8: icmp_seq=1 ttl=118 time=26.7 ms
# 64 bytes from 8.8.8.8: icmp_seq=2 ttl=118 time=26.6 ms
# 64 bytes from 8.8.8.8: icmp_seq=3 ttl=118 time=26.6 ms
# 64 bytes from 8.8.8.8: icmp_seq=4 ttl=118 time=26.3 ms
# 64 bytes from 8.8.8.8: icmp_seq=5 ttl=118 time=26.5 ms
# ^C
# --- 8.8.8.8 ping statistics ---
# 5 packets transmitted, 5 received, 0% packet loss, time 4006ms
# rtt min/avg/max/mdev = 26.376/26.608/26.779/0.134 ms

# 33) wc - It counts lines, words, and characters in a file.

# [be2325@localhost ass1]$ wc a.c
#  38 113 793 a.c
 
# 34) >/>> - It redirects the standard output of a command to a file, overwriting the file if it exists.

# [be2325@localhost os25]$ echo "This is the first line." > myfile.txt  
# [be2325@localhost os25]$ echo "This is the second line." >> myfile.txt 
# [be2325@localhost os25]$ ls
# A1_02_1A.sh  myfile.txt
# [be2325@localhost os25]$ cat myfile.txt
# This is the first line.
# This is the second line.

# 35) | - It takes the standard output of one command and uses it as the standard input for another command

# $ ls -l | grep "myfile"
# -rw-r--r--. 1 be2325 ugyr23   49 Jul 24 14:38 myfile.txt

