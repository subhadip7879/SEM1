//Header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "dictionary.h"


CLIENT *cl;   //client handle
input in;     //input  structure used as communication between client and structure
output out;   //output structure used as communication between client and structure
int choice;   //user choice to insert delete or get meaning



void insert();            // insert word in server
void getmeaning();        //get the meaning of word
void deletemeaning();     //delete word
char** str_split(char* , const char);  // function used to split strings


int main(int argc,char **argv)
{

		if(argc!=2){
			printf("client localhost");
			exit(1);
		}


		cl = clnt_create(argv[1],DICTIONARY_PROG,DICTIONARY_VERS,"tcp");
		while(1)
				{

					printf("----------------------------------------------\n");
					printf("Enter \t1.Insert new word\t2.Get meaning\t3.Delete Word\t4.Quit\n");
					printf("Your Input : ");
					scanf("%d",&choice);

					printf("----------------------------------------------\n");
					switch(choice)
					{
						case 1 :
							printf("Enter Word to add to dictionary: ");
							scanf("%s",in.word);
							getchar();
							printf("Enter Meaning : ");
							scanf("%[^\n]s",in.meaning);
							insert();
							break;
						case 2 :
							printf("Enter word to get meaning from dictionary: ");
							scanf("%s",in.word);
							getmeaning();
							break;
						case 3 :
							printf("Enter Word to delete from dictionary : ");
							scanf("%s",in.word);
							getmeaning();
							deletemeaning();
							break;
						case 4 :
							exit(1);
						default :
							printf("Enter correct option\n");
							break;

					}
				}

}
/*
 * This function is used to insert a word .
 * */
void insert()
{
	insert_proc_1(&in,&out,cl);
	if(out.status == 1)
		printf("Word and its meaning inserted successfully to database!!\n");
	else if(out.status == 2)
		printf("Word and its meaning already exists in dictionary\n");
	else
		printf("Error in inserting the word to database!!\n");

}

/*
 * This function is used to get meaning of a word
 * */
void getmeaning()
{
	getmeaning_proc_1(&in,&out,cl);
	if(out.status == 1)
	{
		printf("Meaning(s) of Word \"%s\" : \n",out.word);
		char **meanings = str_split(out.allmeaningsappended,',');
		for (int i = 0; meanings[i]; i++)
		{
			printf("%d) %s\n",i+1, meanings[i]);
		}
	}
	else
		printf("Word doesn't exists in Dictionary!!\n");

}

/*
 * This function is used to delete a word by displaying the word
 * */

void deletemeaning()
{
	delete_proc_1(&in,&out,cl);
	if(out.status == 1)
		printf("Word successfully deleted from Dictionary!!\n");
	else
		printf("Word not found in Dictionary!!\n");

}

/*
 * This function is used to split a string.
 * It takes input as a string and a delimiter.
 * It returns subsequent strings which are seperated by delimiter
 * */
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}


