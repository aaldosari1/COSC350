/*
Jack Stoetzel
Lab 06
Task 4
forkExec.c

*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int myatoi(char *str)
{
	int num = 0;
	int index = 0;

	while(str[index] != '\0')
	{
		num = (num * 10) + (str[index] - 48);
		index++;
	}
	return num;
}

int main(int argc, char* argv[])
{
	int Nc = myatoi(argv[1]);
	int Np = myatoi(argv[2]);
	int Tc = myatoi(argv[3]);
	int Tp = myatoi(argv[4]);

	pid_t pid;
	int n, t, exit_code;

	printf("Fork program starting.\n");
	pid = fork();
	switch(pid)
	{
		case -1:
			perror("Fork failed.");
			exit(1);
		case 0:
			 execlp("./child", argv[1], argv[3], "Mommy says hi.", (char *)0);
			break;
		default:
			//wait(&pid);
			for(; Np > 0; Np--)
			{
				printf("Parent ID = %d. \n", getpid());
				sleep(Tp);
			}
			break;
	}

	if(pid != 0)
	{
		int stat_val;
		pid_t child_pid;

		child_pid = wait(&stat_val);

		printf("Child  has finished: PID = %d. \n", child_pid);
		if(WIFEXITED(stat_val))
		{
			printf("Child exited with code %d. \n", WEXITSTATUS(stat_val));
		}
		else
		{
			printf("Child terminated abnormally. \n");
		}
	}
	exit(exit_code);
}
