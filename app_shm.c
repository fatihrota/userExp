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

    /* put some things into the memory */
    for (s = (char*)shm, c = 'a'; c <= 'z'; c++) *s++ = c;

    *s = '\0';

    /* wait until first character is changed to '*' */

    s = (char*)shm;

    while (*s != '*') sleep(1);

    exit(0);
}