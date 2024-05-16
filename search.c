#include"addressbook.h"
int search_contact(AddressBook *book)
{
    printf("\n\tSearch contact\n\t1. Name\n\t2. Mobile no\n\t3. mail_id \n\t4. Address\n\n");
    int choice,i=1;
    fseek(book->fp,0,SEEK_END);
    while(i)
    {
	printf("\n\tEnter the choice to search : ");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:
		char user[60];
		printf("Enter name to search : ");
		getchar();
		scanf("%[^\n]s",user);
		if(ftell(book->fp) == 4)
		{
		    printf("INFO : FILE IS EMPTY TO SEARCH\n");
		    return e_fail;
		}
		else if(search_name(user,DEFAULT_FILE) == e_success)
		{
		    printf("Names found\n");
		    return e_success;
		}
		else
		{
		    printf("names not found\n");
		    return e_fail;
		}
	    case 2:
		char phno[11];
		printf("Enter phno to search : ");
		getchar();
		scanf("%s",phno);
		if(ftell(book->fp) == 4)
		{
		    printf("INFO : FILE IS EMPTY TO SEARCH\n");
		    return e_fail;
		}
		else if(check_num_or_not(phno) == e_success)
		{
		    if(search_phno(phno,DEFAULT_FILE) == e_success)
		    {
			printf("Mobile number found\n");
			return e_success;
		    }
		    else
		    {
			printf("Mobile number not found\n");
			return e_fail;
		    }
		}
		else
		{
		    printf("INFO : INVALID MOBILE NUMBER TO SEARCH\n");
		    return e_success;
		}
	    case 3:
		char mail_id[70];
		getchar();
		printf("Enter mail to search --> ");
		scanf("%s",mail_id);
		if(ftell(book->fp) == 4)
		{
		    printf("INFO : FILE IS EMPTY TO SEARCH\n");
		    return e_fail;
		}
		else if(check_mail_or_not(mail_id) == e_success)
		{
		    if(search_mail(mail_id,DEFAULT_FILE) == e_success)
		    {
			printf("Mail found\n");
			return e_success;
		    }
		    else
		    {
			printf("Mail not found\n");
			return e_fail;
		    }
		}
		else
		{
		    printf("INFO : INVALID MAIL ID TO SEARCH\n");
		    return e_success;
		}
	    case 4:
		char place[100];
		getchar();
		printf("Enter location to search --> ");
		scanf("%[^\n]s",place);
		if(ftell(book->fp) == 4)
		{
		    printf("INFO : FILE IS EMPTY TO SEARCH\n");
		    return e_fail;
		}
		else if(search_location(place,DEFAULT_FILE) == e_success)
		{
		    printf("Location found\n");
		    return e_success;
		}
		else
		{
		    printf("Location not found\n");
		    return e_success;
		}
	    default:
		printf("INVALID CHOICE TO SEARCH!!!\n");
		i=0;
		break;
	}
    }
}

int search_name(char *name,char *file)
{
    int flag=0;
    FILE *fptr = fopen(file,"r");
    if(fptr == NULL)
    {
	printf("FILE CANN'T OPEN\n");
	return e_fail;
    }
    char *str = malloc(500);
    char line[500];
    //fgets(line,500,fptr);
    fgets(str,500,fptr);
    while(fgets(str,500,fptr) != NULL)// && fgets(line,500,fptr) != NULL)
    {
	store_str(str,line);
	check_till_comma(str);
	if(strstr(str,name) != NULL)
	{
	    printf("%s found in\n\t",name);
	    flag++;
	    printf("%s\n",line);
	}
    }
    if(flag != 0)
	return e_success;
    else
	return e_fail;
}

int store_str(char *str,char *line)
{
    int i=0;
    while(str[i] != '\0')
	line[i++] = str[i];
    line[i] = '\0';
}

int search_phno(char *num,char *file)
{
    int flag=0;
    FILE *fptr = fopen(file,"r");
    if(fptr == NULL)
    {
	printf("FILE CANN'T OPEN\n");
	return e_fail;
    }
    char *str = malloc(500);
    char line[500];
    //fgets(line,500,fptr);
    fgets(str,500,fptr);
    while(fgets(str,500,fptr) != NULL)// && fgets(line,500,fptr) != NULL)
    {
	store_str(str,line);
	str = strstr(str,",")+1;
	check_till_comma(str);
	if(strstr(str,num) != NULL)
	{
	    printf("%s found in\n\t",num);
	    flag++;
	    printf("%s\n",line);
	}
    }
    if(flag != 0)
	return e_success;
    else
	return e_fail;
}

int search_mail(char *mail_id,char *file)
{
    int flag=0;
    FILE *fptr = fopen(file,"r");
    if(fptr == NULL)
    {
	printf("FILE CANN'T OPEN\n");
	return e_fail;
    }
    char *str = malloc(500);
    char line[500];
    //fgets(line,500,fptr);
    fgets(str,500,fptr);
    while(fgets(str,500,fptr) != NULL)// && fgets(line,500,fptr) != NULL)
    {
	store_str(str,line);
	str = strstr(str,",")+1;
	str = strstr(str,",")+1;
	check_till_comma(str);
	if(strstr(str,mail_id) != NULL)
	{
	    printf("%s found in\n\t",mail_id);
	    flag++;

	    printf("%s\n",line);
	}
    }
    if(flag != 0)
	return e_success;
    else
	return e_fail;
}

int search_location(char *place,char *file)
{
    int flag=0;
    FILE *fptr = fopen(file,"r");
    if(fptr == NULL)
    {
	printf("FILE CANN'T OPEN\n");
	return e_fail;
    }
    char *str = malloc(500);
    char line[500];
    //fgets(line,500,fptr);
    fgets(str,500,fptr);
    while(fgets(str,500,fptr) != NULL)// && fgets(line,500,fptr) != NULL)
    {
	store_str(str,line);
	str = strstr(str,",")+1;
	str = strstr(str,",")+1;
	str = strstr(str,",")+1;
	check_till_comma(str);
	if(strstr(str,place) != NULL)
	{
	    printf("%s found in\n\t",place);
	    flag++;

	    printf("%s\n",line);
	}
    }
    if(flag != 0)
	return e_success;
    else
	return e_fail;
}

