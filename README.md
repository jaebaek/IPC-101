# IPC-101
Very simple Inter Process Communication via character device driver to help people who want to run Android Binder-like IPC implementation

Author
------------------
- Jaebaek Seo (jaebaek@kaist.ac.kr)

simpleDD
------------------
- In the directory, you can check out the file hello.c and Makefile
- Build
~~~~~{.sh}
$ make
~~~~~

- Test
~~~~~{.sh}
$ sudo insmod hello.ko
$ lsmod
$ cat /dev/kmsg # this shows kernel message (i.e., `output of printk()`)
$ sudo rmmod hello
$ cat /dev/kmsg
~~~~~

simpleMsgDD
------------------
- msg.c support sending and receiving message from a thread to another thread.
    - Note that it is very simple one (e.g., vulnerable to race condition, no multiple message support).
- test.c save a string to the device driver and read the string from the device driver.

- Build
~~~~~{.sh}
$ make
$ gcc test.c
~~~~~

- Test
~~~~~{.sh}
$ sudo mknod /dev/simple_msg_dd c 250 0 # 250 is the major number used for register_chrdev()
$ sudo insmod hello.ko
$ lsmod
$ cat /dev/kmsg # this shows kernel message (i.e., `output of printk()`)
$ sudo ./a.out
$ cat /dev/kmsg
$ sudo rmmod hello
$ cat /dev/kmsg
$ sudo rm /dev/simple_msg_dd
~~~~~
