#include "userExp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <sys/ipc.h>

#include <sys/shm.h>
#include <iostream>

#define SHMSZ     27
 
int main(void)
{
	int shmid;

    key_t key;

    char *s;

    void* shm;

 

    key = 5678; /* selected key by server */

    /* Locate the segment. */

 

    if ((shmid = shmget(key,SHMSZ,0666)) < 0)
    {

    perror("shmget"); exit(1);

    }

    /* Now we attach the segment to our data space. */ 

    if ((shm = shmat(shmid, NULL, 0)) ==  (void*) -1)

   {

        perror("shmat"); exit(1);

    }

	/* read what the server put in the memory. */

    while(1)
    {

    	char *tmp = (char *)shm;

    	if(*tmp == 'a')
    	{
    		for (s = (char *)shm; *s != '\0'; s++)                                         
		   	std::cout << *s << std::endl;

		                                                                                                           
		    std::cout << std::endl;

		    puts("This is a shared library test...");
		    add();		 

		    /* change the first character in segment to '*' */
		    s=(char*)shm;    *s= '*';   /* exit(0);*/
    	}

    }
 
    
    return 0;
}