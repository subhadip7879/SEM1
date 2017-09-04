#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

int main(int argc,char **argv)
{
		CLIENT *cl;
		input in;
		output out;
		if(argc!=2){
			printf("client localhost");
			exit(1);
		}

		cl = clnt_create(argv[1],DICTIONARY_PROG,DICTIONARY_VERS,"tcp");
		int choice;
		while(1)
				{

					printf("----------------------------------------------\n");
					printf("Enter \n1 to Insert new word and\n2 to Get meaning\n3 to Delete Word: ");
					scanf(" %d",&choice);
					printf("----------------------------------------------\n");
					switch(choice)
					{
						case 1 :
							printf("Enter Word to add to dictionary: ");
							scanf("%[^\n]s",in.word);
							printf("Enter Meaning : ");
							scanf("%[^\n]s",in.meaning);
							insert_proc_1(&in,&out,cl);
							if(out.status)
								printf("Word inserted successfully to database!!\n");
							else
								printf("Error in inserting the word to database!!\n");
							break;
						case 2 :
							printf("Enter word to get meaning from dictionary: ");
							scanf("%s",in.word);
							getmeaning_proc_1(&in,&out,cl);

							if(out.status == 1)
							{
								/*printf("meaning(s) of \"%s\" : \n",getmeaning_output->word);
								char **meanings = str_split(getmeaning_output->meaning,',');
								for (int i = 0; meanings[i]; i++)
								{
									printf("%d). %s\n",i+1, meanings[i]);
								}*/
							}

							else
								printf("Word doesn't exists in Dictionary!!\n");
							break;
						case 3 :
							printf("Enter Word to delete from dictionary : ");
							scanf("%s",in.word);
							delete_proc_1(&in,&out,cl);
							if(out.status == 1)
								printf("Word successfully deleted from Dictionary!!\n");
							else
								printf("Word not found in Dictionary!!\n");
							break;
						default :
							printf("Enter correct option\n");
							break;

					}
				}

}
