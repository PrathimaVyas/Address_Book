#include"addressbook.h"
int delete_contact(AddressBook *book)
{
    printf("\t1.Name\n\t2. Mobile no\n\t3. gmail\n\t4. exit\n");
    int choice;
    fseek(book->fp,0,SEEK_END);
    while(1)
    {
	printf("\n\tEnter the choice to delete based on which option : ");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:
		char user[60];
		getchar();
		printf("Enter the name to delete that contact : ");
		scanf("%[^\n]s",user);
printf("name ourside -> %s\n",user);
		if(ftell(book->fp) == 4)
		    printf("FILE IS EMPTY TO DELETE THE CONTENT\n");
		else if(check_name_or_not(user)==e_success)
		{
		    if(delete_contact_info(user,DEFAULT_FILE,DUPLICATE_FILE) == e_success)
		    {
			printf("Deleted contact successfully\n");
		    }
		    else
		    {
			printf("Name not found to delete the contact\n");
		    }
		}
		else
		    printf("Entered name is invalid\n");
		break;
	    case 2:
                char phno[11];
                getchar();
                printf("Enter the phno to edit : ");
                scanf("%s",phno);
                if(ftell(book->fp) == 4)
                    printf("FILE IS EMPTY TO EDIT\n");
                else if(check_num_or_not(phno) == e_success)
                {
                    if(delete_contact_info(phno,DEFAULT_FILE,DUPLICATE_FILE) == e_success)
                    {
                        printf("deleted contact\n");
                        save(DEFAULT_FILE,DUPLICATE_FILE);
                    }
                }
                else
                    printf("INVALID MOBILE NUMBERS\n");
break;
	    case 3:

                char mail[70];
                getchar();
                printf("Enter mail to edit -> ");
                scanf("%s",mail);

                if(ftell(book->fp) == 4)
                    printf("FILE IS EMPTY TO EDIT\n");
                else if(check_mail_or_not(mail) == e_success)
                {
                    if(delete_contact_info(mail,DEFAULT_FILE,DUPLICATE_FILE) == e_success)
                    {
                        printf("Deleted contact successfully\n");
                        save(DEFAULT_FILE,DUPLICATE_FILE);
                    }
                    else
		    {
			printf("mail is not present to delete the contact\n");
		    }
		}
		else
		    printf("INVALID MAILID TO DELETE\n");
		break;

	    case 4:
		return e_success;

	    default:
		printf("INVALID CHOICE!!!\n");
		break;

	}
    }
}

int delete_contact_info(char *name,char *file,char *dup_file)
{
    char str[500];
    FILE *fptr = fopen(file,"r");
    FILE *fp = fopen(dup_file,"w");
    if(fptr == NULL || fp == NULL)
    {
	printf("FILES OPEN FAILURE\n");
	return e_fail;
    }
int flag=0;
    while(fgets(str,500,fptr) != NULL)
    {
	if(strstr(str,name) == NULL)
	   	 fprintf(fp,"%s",str);
	else
	    flag=1;
    }
    fclose(fptr);
    fclose(fp);
    save(file,dup_file);
if(flag ==1)
    return e_success;
else
    return e_fail;

}
/*
int delete_by_phno(char *num,char *file,char *dup_file)
{
    int flag=0;
    FILE *fptr = fopen(file,"r");
    FILE *fp = fopen(dup_file,"w");
    if(fptr == NULL || fp == NULL)
    {
        printf("FAILED TO OPEN FILE");
        return e_fail;
    }

    char *str = malloc(500);
    while(fgets(str,500,fptr) != NULL)
    {
	if(strstr(str,num) == NULL)
	   	 fprintf(fp,"%s",str);
	else
	    flag=1;  
    }
    if(flag == 0)
        return e_fail;
    fclose(fptr);
    fclose(fp);
    return e_success;
}*/
