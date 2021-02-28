#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 8

int main(int argc, char *argv[])
{
    int fd_pair[2];
    int ret = pipe(fd_pair);
    if (ret != 0) exit(1);

    ret = fork();
    if (ret == -1) exit(1);
    if (ret == 0)
    {
        ret = dup2(fd_pair[0], STDIN_FILENO);
        close(fd_pair[0]);
        close(fd_pair[1]);
        char buffer[BUF_SIZE] = {0};
        while ((ret = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0)
        {
            write(STDOUT_FILENO, buffer, sizeof(buffer));
            memset(buffer, 0, BUF_SIZE);
        }
    }
    else
    {
        ret = dup2(fd_pair[1], STDOUT_FILENO);
        close(fd_pair[0]);
        close(fd_pair[1]);
        const char *pipe_data = "This is the string we need to pass through the pipe, the pipe is what? Well it is just a bunch self-clean kernel buffer space in which we can move bytes and use for IPC.\n";
        write(STDOUT_FILENO, pipe_data, strlen(pipe_data));
    }

    return 0;
}
