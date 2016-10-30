#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main (int argc, char *argv[])
{
	printf("Prog2: my arguments are: %s %s\n",argv[0],argv[1]); 
	sleep(1);
	printf("Prog2: pid = %d\n",getpid()); 
	sleep(1);

return 0;
}