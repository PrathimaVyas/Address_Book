#include"addressbook.h"
int print()
{
    FILE *fptr = fopen(DEFAULT_FILE,"r");
    if(fptr == NULL)
    {
	printf("FILE OPEM FAILURE\n");
	return e_fail;
    }
 fseek(fptr,0,SEEK_SET);
    char *str=malloc(500);
    printf("NAME    ->     Mobile number    ->    mail_id   ->    location\n\n");    
    fgets(str,500,fptr);
    while(fgets(str,500,fptr)!=NULL)
    {
	print_till_comma(str,fptr,"NAME");
	str = strstr(str,",")+1;
	print_till_comma(str,fptr,"PHNO");
	str = strstr(str,",")+1;
	print_till_comma(str,fptr,"MAIL_ID");
	str = strstr(str,",")+1;
	print_till_comma(str,fptr,"ADDRESS");
	str = strstr(str,";");
	printf("\n");
    }
}

int print_till_comma(char *str,FILE *fptr,char *name)
{
    char *ch=malloc(500);
    int i=0;
    while(str[i] != ',' && str[i] != ';')
    {	ch[i] = str[i];
	i++;

    }
    printf("%s		-> %s \n",name,ch);
    free(ch);
}
