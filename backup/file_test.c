#include "config.h"
#include "file_common.h"

int main(void) {
    int fd1, fd2, fd3;
    char buf[] = "Hello, class!\n";

    fd1 = socket(PF_INET, SOCK_STREAM, 0);
    if (fd1 == -1) ErrorHandling("socket() error!");

    fd2 = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (fd2 == -1) ErrorHandling("open() error!");

    fd3 = socket(PF_INET, SOCK_STREAM, 0);
    if (fd3 == -1) ErrorHandling("open() error!");

    printf("File Descriptor 1: %02d\n", fd1);
    printf("File Descriptor 2: %02d\n", fd2);
    printf("File Descriptor 3: %02d\n", fd3);

    if (write(fd2, buf, sizeof(buf)) == -1) ErrorHandling("write() error!");

    close(fd1);
    close(fd2);
    close(fd3);

    fd2 = open("test.txt", O_RDONLY);
    if (fd2 == -1) ErrorHandling("open() error!");

    printf("File Descriptor: %02d\n", fd2);

    if (read(fd2, buf, sizeof(buf)) == -1) ErrorHandling("read() error!");

    printf("File data: %s", buf);

    close(fd2);

    return 0;
}