#include"addressbook.h"

int add_contact(AddressBook *book,char *line1)
{
    // To store the contact details temporarily
    printf("\t1.Name\n\t2.ph.no\n\t3.gmail\n\t4. location\n\t5. exit\n");
    int choice;
    ContactInfo *contact=malloc(sizeof(ContactInfo));

    fseek(book->fp,0,SEEK_END);
    int i=1;

    while(i)
    {
	printf("\n\tEnter the choice to insert : ");
	scanf("%d",&choice);
	printf("\ncheck case-%d\n\n",choice);
	switch(choice)
	{
	    case 1:
		char user[60];
		getchar();
		printf("Enter name -> ");
		scanf("%[^\n]s",user);
		if(ftell(book->fp) == 4)
		{
		    strcpy(contact->name,user);
		}
		else if(check_name_or_not(user) == e_success)
		{
		    if(check_name_in_file(user,DEFAULT_FILE) == e_success)
		    strcpy(contact -> name,user);
		}
		else
		{
		    printf("Invalid name\n");
		    choice = 1;
		}
		    break;
	    case 2:
		char phno[11];
		getchar();
		printf("Enter phno --> ");
		scanf("%s",phno);
		if(ftell(book->fp) == 4)
		{
		    strcpy(contact->mobile_num,phno);
		    break;
		}
		else if(check_num_or_not(phno)==e_success)
		{
		    if(check_phno_in_file(phno,DEFAULT_FILE) == e_no_match)
		    {
			strcpy(contact->mobile_num,phno);
			break;
			//printf("mobile number copied\n\n");
		    }
		    else
		    {
			choice = 2;
			break;
		    }
		}
		else
		{
		    printf("---> INVALID MOBILE NUMBER <---\n");
		    choice = 2;
		    break;
		}
	    case 3:
		char mail_id[70];
		getchar();
		printf("Enter mail --> ");
		scanf("%s",mail_id);
		if(ftell(book->fp) == 4)
		{
		    strcpy(contact->email_address,mail_id);
		}
		else if(check_mail_or_not(mail_id) == e_success)
		{
		    if(check_mail_in_file(mail_id,DEFAULT_FILE) == e_no_match)
		    {
			strcpy(contact->email_address,mail_id);
			//      printf("mail id copied\n");
		    }
		    else
		    {
			choice = 3;
		    }
		}
		else
		{
		    printf("---> INVALID MAIL ID <---\n");
		    choice = 3;
		}
		    break;
	    case 4:
		char place[100];
		getchar();
		printf("Enter location --> ");
		scanf("%[^\n]s",place);
		strcpy(contact -> location,place);
		printf("Name -> %s\nMobile -> %s\nemail -> %s\nplace -> %s\n",contact->name,contact->mobile_num,contact->email_address,contact->location);

	    default:
		i=0;
		break;
	}
    }

    fseek(book->fp,-1,SEEK_END);
    printf("ftell -> %ld\n",ftell(book->fp));
    fprintf(book->fp,"%s,%s,%s,%s;\n",contact->name,contact->mobile_num,contact->email_address,contact->location);
    free(contact);
    fseek(book->fp,0,SEEK_END);
    printf("ftell after adding-> %ld\n",ftell(book->fp));
    return e_success;
}

int check_name_in_file(char *name,char *file)
{
    FILE *fptr;
    fptr = fopen(file,"r");
    char *str=malloc(500);
    fgets(str,500,fptr);
    while(fgets(str,500,fptr) != NULL)
    {
	check_till_comma(str);
	if(strcmp(str,name) == 0)
	{
	    printf("---> SAME NAMES FOUND, CHANGE THE NAME <---\n");
	    return e_fail;
	}
    }
    return e_success;
}

int check_till_comma(char *str)
{
    int i=0;
    while(str[i] != ',' && str[i] != '\0')
	i++;
    str[i] = '\0';
}


int check_num_or_not(char *phonenum)
{
    int i=0;
    while(phonenum[i] >= '0' && phonenum[i] <= '9')
	i++;

    if(phonenum[i] == '\0' && i == 10)
	return e_success;
    else
	return e_fail;
}

int check_phno_in_file(char *phonenum,char *file)
{
    FILE *fptr = fopen(file,"r");
    char *str=malloc(500);
    fgets(str,500,fptr);
    while(fgets(str,500,fptr) != NULL)
    {
	str = strstr(str,",")+1;
	check_till_comma(str);
	if(strcmp(str,phonenum) == 0)
	{
	    printf("---> SAME PHONE NUMBERS FOUND,CHANGE THE NUMBER <---\n");
	    return e_fail;
	}
    }
    return e_no_match;
}

int check_mail_or_not(char *mail)
{
    char *str = malloc(100);
    str = strstr(mail,"@");
    if(str == NULL)
	return e_fail;
    else
	str = strstr(mail,".com");
    if(str == NULL)
	return e_fail;

    return e_success;
}

int check_mail_in_file(char *mail,char *file)
{
    FILE *fptr = fopen(file,"r");
    if(fptr == NULL)
    {
	printf("FILE CANN'T OPEN\n");
	return e_fail;
    }
    char *str = malloc(500);
    fgets(str,500,fptr);
    while(fgets(str,500,fptr) != NULL)
    {
	str = strstr(str,",")+1;
	str = strstr(str,",")+1;
	check_till_comma(str);
	if(strcmp(str,mail) == 0)
	{
	    printf("---> SAME MAIL FOUND, CHANGE THE MAIL <---\n");
	    return e_fail;
	}
    }
    return e_no_match;
}

int check_name_or_not(char *name)
{
    int i=0;
   while(name[i] !='\0')
   {
       if((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z'));
       else
	   return e_fail;
       i++;
   }
   return e_success;
}
