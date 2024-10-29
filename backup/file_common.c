#include "file_common.h"

void ErrorHandling(char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}