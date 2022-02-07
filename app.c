#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

 

#define SHMSZ     27


int main()
{
    int shmid;
    key_t key;
    char c,  *s;                               
    void* shm;

    key = 5678; /* selected key */
 

    if ((shmid = shmget(key,SHMSZ,IPC_CREAT | 0666)) < 0)
    {
        perror("shmget"); 
        exit(1);
    }

    /* Now we attach the segment to our data space.*/
    if ((shm = shmat(shmid, NULL, 0)) == (void*)-1) {

        perror("shmat"); exit(1);

    }

    std::string cmd = "main_shm"; // secondary program you want to run

    pid_t pid = fork(); // create child process
    int status;

    switch (pid)
    {
    case -1: // error
        perror("fork");
        exit(1);

    case 0: // child process
        execl(cmd.c_str(), "hop", NULL); // run the command
        perror("execl"); // execl doesn't return unless there is a problem
        exit(1);

    default: // parent process, pid now contains the child pid
    for (s = (char*)shm, c = 'a'; c <= 'z'; c++) *s++ = c;

    *s = '\0';

    /* wait until first character is changed to '*' */

    s = (char*)shm;

    while (*s != '*') sleep(1);

    sleep(10);

     for (s = (char*)shm, c = 'a'; c <= 'z'; c++) *s++ = c;

    *s = '\0';

    /* wait until first character is changed to '*' */

    s = (char*)shm;

    while (*s != '*') sleep(1);


    break;

#if 0
        while (-1 == waitpid(pid, &status, 0)); // wait for child to complete
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
        {
            // handle error
            std::cerr << "process " << cmd << " (pid=" << pid << ") failed" << std::endl;
        }
        break;
#endif
    }

    return 0;
}