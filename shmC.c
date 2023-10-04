#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<unistd.h>
#define SHMSZ 1024

int main()
{
  key_t key;
  
  int shmid;

  char *shm , *k , *s, *se, *th;
 
  key = 3450;
  
  if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666))<0)
  {
    perror("shmget");
	
    exit(1);
  }

  if((shm = shmat(shmid,NULL,0)) == (char *)-1)
  {
	perror("shmat");
	
    exit(1);
  }

  *shm = 'R';

  s = shm; // 's' points to the first mem. location...

  ++s;  //'s' points to the second mem. location...
  
  se = s;
  
  *se = 'N'; //Default value for when there is no other writers in the shared mem. space...
  
  ++s;  //'s' points to the Third mem. location...
  
  th = s;

  printf("Shared memory id is: %d\n", shmid);

  for (k = shm; *k != '\0'; k++)
		printf("%c",*k);
	putchar('\n');
  
  return 0;
}





