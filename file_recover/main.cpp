#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define SECTOR_SIZE 512

int main() {
    int fd;
    char buffer[SECTOR_SIZE];

    // 打开硬盘设备文件
    fd = open("/dev/disk0", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 读取一个扇区的数据
    if (read(fd, buffer, SECTOR_SIZE) != SECTOR_SIZE) {
        perror("read");
        close(fd);
        return 1;
    }

    // 打印数据
    for (int i = 0; i < SECTOR_SIZE; i++) {
        printf("%02x ", (unsigned char)buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }

    close(fd);
    return 0;
}