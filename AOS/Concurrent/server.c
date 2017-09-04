#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

struct m
{
	char *meaning;
	struct m *ptrtonextmeaning;
};

struct w
{
	char *word;
	struct m *ptrtomeaning;
	int noofmeanings;
	struct w *ptrtonextword;
};

struct w *head = NULL;

struct w* findindexofword(char *word)
{
	 struct w *temp = head;
	 while(temp)
	 {
		 if(strcmp(temp->word,word) == 0)
			 return temp;

		 temp=temp->ptrtonextword;
	 }
	 return NULL;
}

struct w* findpreviousindexofword(char *word)
{
	 struct w *temp = head;
	 while(temp->ptrtonextword)
	 {
		 if(strcmp(temp->ptrtonextword->word,word) == 0)
			 return temp;

		 temp=temp->ptrtonextword;
	 }
	 return NULL;
}

void printallmeaningsforaword(struct m *ptr)
{
	int i=1;
	while(ptr)
	{
		printf("%d). %s\n",i,ptr->meaning);
		ptr=ptr->ptrtonextmeaning;
		i++;
	}
}

void print()
{
	struct w *temp = head;
	while(temp)
		 {
			 //printf("word is %s and meaning is %s\n",temp->word,temp->ptrtomeaning->meaning);
			printf("word is %s \n",temp->word);
			printallmeaningsforaword(temp->ptrtomeaning);
			 temp=temp->ptrtonextword;
		 }
}

 bool_t insert_proc_1_svc(input *in,output *out,struct svc_req *rqstp)
{

	 bool_t retval = 1;;
	 if(head == NULL)
	 	{
	 		 head = (struct w*)malloc(sizeof(struct w));
	 		 head->word = (char *)malloc(strlen(in->word)*sizeof(char));
	 		 strcpy(head->word,in->word);
	 		 head->ptrtonextword = NULL;
	 		 head->ptrtomeaning = (struct m*)malloc(sizeof(struct m));
	 		 head->ptrtomeaning->meaning = (char *)malloc(strlen(in->meaning)*sizeof(char));
	 		 strcpy(head->ptrtomeaning->meaning,in->meaning);
	 		 head->ptrtomeaning->ptrtonextmeaning = NULL;
	 		 out->status = 1;
	 		 print();
	 		 return retval;
	 	}


	 struct w *indexofword = (struct w*)findindexofword(in->word);
	 if(indexofword == NULL)
	 {
		 printf("Word doesn't exists\n");
		 struct w *temp = head;
		 while(temp->ptrtonextword)
			 temp=temp->ptrtonextword;
		 struct w *newword = (struct w*)malloc(sizeof(struct w));
		 newword->word = (char *)malloc(strlen(in->word)*sizeof(char));
			strcpy(newword->word,in->word);
			newword->ptrtonextword = NULL;
			newword->ptrtomeaning = (struct m*)malloc(sizeof(struct m));
			newword->ptrtomeaning->meaning = (char *)malloc(strlen(in->meaning)*sizeof(char));
			strcpy(newword->ptrtomeaning->meaning,in->meaning);
			newword->ptrtomeaning->ptrtonextmeaning = NULL;
			out->status = 1;
			temp->ptrtonextword = newword;
			print();
			return retval;

	 }
	 else
	 {
		 printf("Word exists\n");
		 struct m *temp = indexofword->ptrtomeaning;
		 while(temp->ptrtonextmeaning)
			 temp=temp->ptrtonextmeaning;
		 struct m *newmeaning = (struct m*)malloc(sizeof(struct m));
		 //newmeaning->ptrtonextmeaning = (struct m*)malloc(sizeof(struct m));
		 newmeaning->meaning = (char *)malloc(strlen(in->meaning)*sizeof(char));
		strcpy(newmeaning->meaning,in->meaning);
		newmeaning->ptrtonextmeaning = NULL;
		out->status = 1;
		temp->ptrtonextmeaning = newmeaning;
		print();
		return retval;

	 }


	 out->status = 1;

	return retval;
}

 bool_t getmeaning_proc_1_svc(input *in,output *out,struct svc_req *rqstp)
 {
	 return 1;
 }

 void deleteallmeaningsforspecificword(struct w *ptrtoword)
 {
	 struct m *temp = ptrtoword->ptrtomeaning;
	 struct m *todelete;
	 while(temp)
	 {
		 todelete = temp;
		 temp=temp->ptrtonextmeaning;
		 printf("meaning %s deleted\n",todelete->meaning);
		 free(todelete);
	 }
 }


 bool_t delete_proc_1_svc(input *in,output *out,struct svc_req *rqstp)
  {
	 struct w *indexofword = (struct w*)findindexofword(in->word);
	 struct w *previousindexofword = (struct w*)findpreviousindexofword(in->word);
	 deleteallmeaningsforspecificword(indexofword);
	 previousindexofword = indexofword->ptrtonextword;
	 free(indexofword);
 	 return 1;
  }




 int dictionary_prog_1_freeresult (SVCXPRT *svcprt, xdrproc_t xdr, caddr_t cadr)
 {
	 (void) xdr_free(xdr, cadr);
	 return 1;
 }
