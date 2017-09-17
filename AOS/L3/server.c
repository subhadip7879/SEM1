#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

sort_out *sortarray_proc_1_svc(sort_in *in,struct svc_req *rqstp)
{
	static sort_out outp;
	int temp;
	printf("elements are :");
	for(int i=0;i<10;i++)
	{
		printf("%d",in->unsortedarray[i]);
	}
	for(int i=0;i<10;i++)
	{
		for(int j=i;j<10;j++)
		{
			if((in->unsortedarray[i])<(in->unsortedarray[j]))
			{
				
				temp=in->unsortedarray[i];
				in->unsortedarray[i]=in->unsortedarray[j];
				in->unsortedarray[j]=temp;
				
			}
		}
	}
	for(int i=0;i<10;i++)
	{
		outp.sortedarray[i]=in->unsortedarray[i];
	}
	return (&outp);
}
