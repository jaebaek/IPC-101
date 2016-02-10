#include <stdio.h>

// open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// ioctl
#include <sys/ioctl.h>

// close
#include <unistd.h>

int main(int argc, const char *argv[])
{
    int fd = open("/dev/simple_msg_dd", O_RDWR);
    char buf[1024];  // write to dd
    char buf2[1024]; // read from dd

    printf("fd = %d\n", fd);
    sprintf(buf, "This is a long string %lx", 0x1234567891011);

    // write and read the string
    ioctl(fd, 0, buf);
    ioctl(fd, 1, buf2);

    puts(buf2);
    close(fd);
    return 0;
}
