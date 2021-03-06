/* thread3.c */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
int pipedata [2];

void *reader_function () 
{
	while (1) 
	{
		char ch;
		if (read(pipedata[0],&ch,1)!=1) 
		{
			printf ("Read error\n");
			exit(1);
		}
		printf("Thread ID:%lu, Data read: %c\n", pthread_self(), ch);
		if(ch=='q') 
		{
			break;
		}
	}
	pthread_exit (NULL);
}

void *writer_function () 
{
	int i = 0;
	char ch = 'a', dummy;
	while (ch != 'q') 
	{
		scanf ("%c", &ch);
		scanf (" %c", &dummy);	
		if (write (pipedata [1], &ch, 1)!=1)
		{
			printf("Write error\n");
			exit(1);
		}
		printf ("Thread ID: %lu, Data written: %c\n", pthread_self (), ch);
	}
	pthread_exit (NULL);
}


int main () 
{
	pthread_t reader, writer;
	if (pipe(pipedata) < 0) 
	{
		printf ("Pipe creation error\n");
		exit (1);
	}
	pthread_create(&writer,NULL,writer_function,NULL);
	pthread_create(&reader,NULL,reader_function,NULL);
	pthread_join(writer,NULL);
	pthread_join(reader,NULL);
    exit(0);
}
