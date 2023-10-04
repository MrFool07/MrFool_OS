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
	
	char *shm , *s , *k  , *se , *th;
	
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
	
	char choice;
	
	char flag;
	
	*shm = 'W';
	
	flag = *shm;
	
	/*if(flag == 'W')
		printf("\nYou are now in the Write mode of the Shared Space!!!\n");
	else
		printf("\nYou are now in the Read mode of the Shared Space!!!\n");*/
	
	//choice = 'Y'; //Telling the other write processes that there is a write process already present...
	
	s = shm; //Making s, an iterator point to the first memory location.
	
	++s; //Iterating s to point to the second memory location...
	
	se = s;  //Making the 'se' pointer point to the second memory location always...
	
	choice = *se;
	
	//*s = choice; //Storing the choice in the second memory location...
	
	if(flag == 'W' && choice == 'N')
	{
		printf("\n%d is the only Write process that is accessing the Shared Memory...",getpid());
		
		*se = 'Y';
		
		++s; //Pointing to the third memory location...
		
		th = s;//Making the 'th' pointer point to the second memory location always...
		
		char temp1 = *s;
		
		printf("\nThe Data at the Third Memory location is %c\n",temp1);
		
		int temp = 1;
			
		while(temp)
		{
			//printf("\nInside the While Loop!!!\n");
			
			if(*s != '\0')
				
				++s;
			
			else
				
				temp = 0;
		}
			
		//printf("\nExited the While Loop!!!\n");
		
		char x = *s; 
			
		printf("\nThe Data here should be null: %c",x);
			
		char str[MAX_LIMIT];
	
		int choice;
			
		do
		{
			printf("\nEnter the String to be entered into the Shared Memory: ");
			
			//getchar();
	
			fgets(str, MAX_LIMIT, stdin); //Will accept till ENTER key is hit...
			
			printf("\nAre you sure the string you want to enter is: %s ",str);
			
			printf("\nIf YES -> 1 | NO -> 0: ");
			
			scanf("%d",&choice);
				
		}while(choice != 1);
		
		printf("The String that will be entered into the SHM is: %s\n", str);
			
		for(int i = 0 ; i < sizeof(str) ; i++)
		{
			*s++ = str[i]; //After the last mem. location, *s will point to NULL...
		}
		
		sleep(5);
		
		choice = 'N';
		
		*se = choice;
		
		*shm = 'R';
		
		printf("\nThe Write process for %d Process is complete!!!\n",getpid());
	}
	
	else if(flag == 'W')
	{
		printf("\nThere is a Another process within the Shared Memory Space!!!\n");
		
		*shm = 'R';
	}
	
	else
	{
		printf("\nThe Shared Space is in the Read Mode!!!\n");
		
		*shm = 'R';
	}
	
	for (k = th; *k != '\0'; k++)
		
		printf("%c",*k);
	putchar('\n');
	
	return 0;
}
