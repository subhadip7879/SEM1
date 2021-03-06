#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <stdlib.h>

int main()
{
	struct message
	{
		long type;
		char msgbuf[256];
	} msg;

	int msqid;
	int key=1234;
	msg.type = 3;
	msqid = msgget(key,IPC_CREAT|0644);
	if(msqid < 0)
	{
		perror("Error in Connecting or Opening the message queue ");
		exit(1);
	}
	printf("Enter Message to be put on Queue : ");
	scanf("%s",msg.msgbuf);

	int status = msgsnd(msqid,&msg,sizeof(msg.msgbuf),IPC_NOWAIT);
	if(status < 0)
	{
		perror("Error in Putting Message on Queue ");
		exit(1);
	}

	printf("Message Sent Succesfully!!");
	return 0;

}
