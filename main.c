#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MSG_MAX_LEN 1024

static char* removeWhitespaces(char* string)
{
    int idx = -1;
    int i = 0;
    while (string[i] != '\0') {
        if (string[i] != ' ' && string[i] != '\t' && string[i] != '\n') {
            idx = i;
        }
        i++;
    }
    string[idx + 1] = '\0';
    return string;
}

int main(void)
{
    pid_t child = fork();

    if (child == (pid_t)0) {
        char* args[] = { "./bash.sh", NULL };
        if (execvp(args[0], args) == -1) {
            perror("cannot exec program.\n");
        }
    }
    sleep(5);
    int fd = open("/tmp/testpipe", O_RDONLY);
    char filename[MSG_MAX_LEN];
    memset(filename, 0, sizeof(char) * MSG_MAX_LEN);
    if (read(fd, filename, sizeof(char) * MSG_MAX_LEN) < 0) {
        perror("cannot read from fifo\n");
        exit(EXIT_FAILURE);
    }

    char* _filename = removeWhitespaces(filename);

    printf("The filename is %s\n", filename);

    FILE* pFile = fopen(_filename, "rb");
    if (pFile == NULL) {
        perror("error");
        exit(EXIT_FAILURE);
    }
    fseek(pFile, 0, SEEK_END);
    long len = ftell(pFile);
    assert(len);
    fseek(pFile, 0, SEEK_SET);

    char imgBuff[len];
    fgets(imgBuff, len, pFile);
    fclose(pFile);

    FILE* pCopy = fopen("copy.jpg", "wb");
    if (pCopy == NULL) {
        perror("error");
        exit(EXIT_FAILURE);
    }

    fprintf(pCopy, "%s", imgBuff);
    fclose(pCopy);
    // printf("Read %s\n", imgBuff);

    return 0;
}