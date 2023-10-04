#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include <sys/shm.h>

#define SHMSZ 1024

#define MAX_LIMIT 1024

int main()
{
	int shmid;
	
	key_t key;
	
	key = 3450;
	
	char *shm , *s , *k , *se, *th;
	
	if ((shmid = shmget(key, SHMSZ, 0666))<0) 
	{
		perror("shmget");
		
		exit(1);
	}

	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
	{
		perror("shmat");
		
		exit(1);
	}
	
	//shm -> points to the first memory location of the shm.
	
	//*shm = 0;
	
	char flag = *shm;
	
	s = shm;
	
	++s; //Iterated to the second mem. location...
	
	se = s;
	
	++s; //Iterated to the Third Memory location...
	
	th = s;
	
	printf("\nThe data at the first location of the Shared Memory is: %c\n",flag);

	if(flag == 'R')
	{
		*se = 'Y';
		
		for (k = th; *k != '\0'; k++)
			
			printf("%c",*k);
			
		sleep(5);
		
		*se = 'N';
		
		/*putchar('\n');
		
		for (k = shm; *k != '\0'; k++)
			
			printf("%c",*k);*/
	}
	else
	{
		printf("\nYou can't access the Shared memory since it is in the Write mode!!\n");
		
		*shm = 'R';
	}
	
	printf("\nThe Read process of the Reader is complete!!!\n");

	return 0;
}
