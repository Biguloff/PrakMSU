#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	char buf[32];
	int st1,st2;
	int method;
	FILE *fp;
	
	//check arguments
	if (argc!=7) 
	{
		printf("ERROR: Wrong number of arguments\n");
		return 0;
	}

    // prog1 -> ./prog1
	argv[1]=strcat(strcpy(buf, "./"), argv[1]);
	argv[4]=strcat(strcpy(buf, "./"), argv[4]);

    //check if exist
 	if ((fp = fopen(argv[1], "r")) == NULL)
    { printf("ERROR: There is no \"%s\" file|\n", argv[1]); return 0;}
	if ((fp = fopen(argv[4], "r")) == NULL)
    {printf("ERROR: There is no \"%s\" file\n", argv[4]);return 0;}

	printf("Mode select:\n(1) Parallel\n(2) Successively\n");
	scanf("%d",&method);

	//create child1 process
	if((pid =fork())<0) 
	{
		perror("fork(1) fail");
		return -1;
	}
	else if (!pid) //child 1 code
	{

		printf("prog1: launching..\n"); sleep(1);
		execlp(argv[1],argv[2],argv[3],NULL);
		sleep(2); // give it some time
		printf("prog1: ..finish\n");
		_exit(0);
	}

	if(method==2) wait(&st1); //wait child 1

	//create child2 process
	if ((pid =fork())<0)
	{
		perror("fork(2) fail");
		return -1;
	}
	else if (!pid)
	{
		printf("prog2: launching..\n"); sleep(1);
		execlp(argv[4],argv[5],argv[6],NULL);	
		sleep(2);
		printf("prog1: ..finish\n");		
		_exit(0);	
	}

	if(method==1) wait(&st1);
	wait(&st2);
	

	if(!st1 && !st2) printf("Success\n");
	else if(!st2) printf("ERROR: %s compile/run failure\n",argv[1]);
	else if(!st1) printf("ERROR: %s compile/run failure\n",argv[4]);

	/*if (!WIFEXITED(st2)) 
	{
		printf("%d\n",WEXITSTATUS(st1) );
		printf("%d\n",WIFSIGNALED(st1));
		printf("%d\n",WTERMSIG(st2));
	}
	*/

return 0;
}