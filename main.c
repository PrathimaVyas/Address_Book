#include"addressbook.h"
static int inc;
int main()
{
    int choice;
    AddressBook *book=malloc(sizeof(AddressBook));
    book -> fp = NULL;
    /*validate the file and check for presence*/
    if(book -> fp == NULL)
    {
	book ->fp = fopen(DEFAULT_FILE,"a+");
	if(book->fp ==  NULL)
	{
	    printf("ERROR : GIVE PROPER FILENAME TO OPEN\n");
	    return e_fail;
	}
    }
    char *line1=malloc(5);
    fgets(line1,5,book->fp);
    line1 = line1+1;
    inc = line1[0]-48;
    while(1)
    {
    printf("\n1. Add contact\n2. Edit contact\n3. Search contact\n4. Delete contact\n5. print\n6. save\n7. Exit\n");
	printf("\nEnter the choice : ");
	scanf("%d",&choice);

	switch(choice)
	{
	    case ADD_CONTACT:
		if(add_contact(book,line1)==e_success)
		{
		    printf("CONTACT ADDED SUCCESSFULLY\n");
		    fseek(book->fp,0,SEEK_SET);
		    include(DEFAULT_FILE,inc,DUPLICATE_FILE);
		}
		break;
	    case EDIT:
		edit_contact(book);
		break;
	    case SEARCH:
		search_contact(book);
		break;
	    case DELETE:
		delete_contact(book);
		break;
	    case PRINT:
		print();
		break;
	    case SAVE:
		save_file();
		break;
	    case EXIT:
		return e_success;
	    default:
		printf("INVALID CHOICE!!!\n");
		break;

	}
    }
}

int include(char *file,int inc,char *dup)
{
    inc++;
    save(dup,file);
    FILE *f = fopen(file,"w");
    FILE *fp = fopen(dup,"r");
    if(f == NULL || fp == NULL)
    {
	printf("FAILED TO OPEN FILES TO SAVE\n");
	return e_fail;
    }
    char str[500];
    fgets(str,500,fp);
    fprintf(f,"#%d#\n",inc);
    while(fgets(str,500,fp) != NULL)
    {
	fprintf(f,"%s",str);
    }
    fclose(fp);
    fclose(f);
    return e_success;
}
