#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int main(void)
{
    if (fork() == 0)
    {
        printf("hello\n");
        kill(getppid(), SIGCONT);
    }
    else if (errno == 0)
    {
        raise(SIGSTOP);
        printf("goodbye\n");
    }
    return 0;
}
