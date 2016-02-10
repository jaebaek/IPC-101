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
