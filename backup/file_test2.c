#include "config.h"
#include "file_common.h"

int main(int argc, char* argv[]) {
    int fd1 = -1;
    int fd2 = -1;
    int n;
    char buf[1024];

    if (argc != 3) {
        printf("Argument error!");
        goto ERROR;
    }

    fd1 = open(argv[1], O_RDONLY, S_IRWXU);
    if (fd1 == -1) {
        ErrorHandling("error opening file!");
        goto ERROR;
    }

    fd2 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (fd2 == -1) {
        ErrorHandling("error opening file!");
        goto ERROR;
    }

    while ((n = read(fd1, buf, sizeof(buf))) > 0) {
        if (write(fd2, buf, n) != n) {
            ErrorHandling("writing error");
            goto ERROR;
        }
    }

ERROR:
    if (fd1 != -1) close(fd1);
    if (fd2 != -1) close(fd2);

    return 0;
}