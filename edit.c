#include"addressbook.h"

int edit_contact(AddressBook *book)
{
    printf("\t1. Name\n\t2. Mobile no\n\t3. gmail\n\t4. address\n\t5. exit");
    int choice;
    ContactInfo *contact = malloc(sizeof(ContactInfo));

    fseek(book->fp,0,SEEK_END);
    int i=1;
    while(i)
    {
        printf("\n\tEnter the choice to edit : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                char user[60];
                getchar();
                printf("Enter the name to edit -> ");
                scanf("%[^\n]s",user);
                char user_edit[60];
                getchar();
                printf("Enter the name to replace the %s -> ",user);
                scanf("%[^\n]s",user_edit);
                if(ftell(book->fp) == 4)
                    printf("FILE IS EMPTY TO EDIT\n");
                else if(edit_name(user,user_edit,DEFAULT_FILE,"duplicate.csv")== e_success)
                {
                    printf("Name edited\n");
                    save(DEFAULT_FILE,DUPLICATE_FILE);
                }
                else
                    printf("Name cann't be edited\n");
                break;
            case 2:
                char phno[11];
                getchar();
                printf("Enter the phno to edit : ");
                scanf("%s",phno);
                char new_num[11];
                getchar();
                printf("Enter the new number to replace in %s : ",phno);
                scanf("%s",new_num);
                if(ftell(book->fp) == 4)
                    printf("FILE IS EMPTY TO EDIT\n");
                else if(check_num_or_not(new_num) == e_success && check_num_or_not(phno) == e_success)
                {
                    if(edit_phno(phno,new_num,DEFAULT_FILE,DUPLICATE_FILE) == e_success)
                    {
                        printf("Mobile number edited\n");
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

                char new_mail[80];
                getchar();
                printf("Enter the new mail to edit %s -> ",mail);
                scanf("%s",new_mail);

                if(ftell(book->fp) == 4)
                    printf("FILE IS EMPTY TO EDIT\n");
                else if(check_mail_or_not(mail) == e_success && check_mail_or_not(new_mail) == e_success)
                {
                    if(edit_mail(mail,new_mail,DEFAULT_FILE,DUPLICATE_FILE) == e_success)
                    {
                        printf("Mail edited\n");
                        save(DEFAULT_FILE,DUPLICATE_FILE);
                    }
                    else
                        printf("%s not found to edit\n",mail);
                }
                else
                    printf("INVALID MAIL ID!!!\n");
                break;


            case 4:
                char area[100];
                getchar();
                printf("Enter the location to edit -> ");
                scanf("%[^\n]s",area);
                char new_area[100];
                getchar();
                printf("Enter the new area to replace %s -> ",area);
                scanf("%[^\n]s",new_area);
                if(ftell(book->fp) == 4)
                    printf("FILE IS EMPTY TO EDIT\n");
                else if(edit_location(area,new_area,DEFAULT_FILE,DUPLICATE_FILE) == e_success)
                {
                    printf("Location edited\n");
                    save(DEFAULT_FILE,DUPLICATE_FILE);
                }
                else
                    printf("%s not found to edit\n",area);
                break;
            case 5:
                return e_success;
            default:
                printf("INVALID CHOICE TO EDIT!!!!\n");
                return e_success;
        }
    }
}

int save(char *file1,char *file2)
{
    FILE *fptr = fopen(file1,"w");
    FILE *fptr1 = fopen(file2,"r");
    if(fptr == NULL || fptr1 == NULL)
    {
        printf("FAILED TO OPEN FILES TO SAVE\n");
        return e_fail;
    }
    char str[500];
    while(fgets(str,500,fptr1) != NULL)
    {
        fprintf(fptr,"%s",str);
    }
    fclose(fptr);
    fclose(fptr1);
   // exit(0);
    return e_success;
}
int edit_name(char *name,char *new_name,char *input_file,char *extrafile)
{
    FILE *fptr = fopen(input_file,"r");
    FILE *fptr1 = fopen(extrafile,"w");
    if(fptr == NULL || fptr1 == NULL)
    {
        printf("FAILED TO OPEN FILE");
        return e_fail;
    }

    char *str = malloc(500);
    fgets(str,500,fptr);
    fprintf(fptr1,"%s",str);
    while(fgets(str,500,fptr) != NULL)
    {
        char *found = strstr(str,name);
        if(found != NULL)
        {
            fprintf(fptr1,"%s",new_name);
            str = strstr(str,",");
            printf("found --> %s\n",found);
            fprintf(fptr1,"%s",str);
        }
        else
        {
            fprintf(fptr1,"%s",str);
        }
    }
    fclose(fptr);
    fclose(fptr1);
    return e_success;
}


int edit_phno(char *phno,char *new_num,char *input_file,char *extrafile)
{
    int flag=0;
    FILE *fptr = fopen(input_file,"r");
    FILE *fptr1 = fopen(extrafile,"w");
    if(fptr == NULL || fptr1 == NULL)
    {
        printf("FAILED TO OPEN FILE");
        return e_fail;
    }

    char *str = malloc(500);
    fgets(str,500,fptr);
    fprintf(fptr1,"%s",str);
    while(fgets(str,500,fptr) != NULL)
    {
        // fprintf(fptr1,"%s",str);
        char *found = strstr(str,phno);
        if(found != NULL)
        {
            flag=1;
            copy_till_comma(str,fptr1);
            str = strstr(str,",")+1;
            fprintf(fptr1,"%s",new_num);
            str = strstr(str,",");
            printf("found --> %s\n",found);
            fprintf(fptr1,"%s",str);
        }
        else
        {
            fprintf(fptr1,"%s",str);
        }
    }
    if(flag == 0)
        return e_fail;
    fclose(fptr);
    fclose(fptr1);
    return e_success;
}

int copy_till_comma(char *str,FILE *file)
{
    int i=0;
    char *num=malloc(100);
    while(str[i] != ',' && str[i] != ';')
    {
        num[i++] = str[i];
    }
    num[i] = ',';
    fprintf(file,"%s",num);
    free(num);
}
int edit_mail(char *mail,char *new_mail,char *input_file,char *extrafile)
{
    int flag =0;

    FILE *fptr = fopen(input_file,"r");
    FILE *fptr1 = fopen(extrafile,"w");
    if(fptr == NULL || fptr1 == NULL)
    {
        printf("FAILED TO OPEN FILE");
        return e_fail;
    }

    char *str = malloc(500);
    fgets(str,500,fptr);
    fprintf(fptr1,"%s",str);
    while(fgets(str,500,fptr) != NULL)
    {
        char *found = strstr(str,mail);
        if(found != NULL)
        {
            flag =1;
            copy_till_comma(str,fptr1);
            str = strstr(str,",")+1;
            copy_till_comma(str,fptr1);
            str = strstr(str,",")+1;
            fprintf(fptr1,"%s",new_mail);
            str = strstr(str,",");
            fprintf(fptr1,"%s",str);
        }
        else
        {
            fprintf(fptr1,"%s",str);
        }

    }
    if(flag == 0)
        return e_fail;
    fclose(fptr);
    fclose(fptr1);
    return e_success;
}

int edit_location(char *area,char *new_area,char *input_file,char *extrafile)
{
    int flag =0;

    FILE *fptr = fopen(input_file,"r");
    FILE *fptr1 = fopen(extrafile,"w");
    if(fptr == NULL || fptr1 == NULL)
    {
        printf("FAILED TO OPEN FILE");
        return e_fail;
    }

    char *str = malloc(500);
    fgets(str,500,fptr);
    fprintf(fptr1,"%s",str);
    while(fgets(str,500,fptr) != NULL)
    {
        char *found = strstr(str,area);
        if(found != NULL)
        {
            flag =1;
            copy_till_comma(str,fptr1);
            str = strstr(str,",")+1;
            copy_till_comma(str,fptr1);
            str = strstr(str,",")+1;
            copy_till_comma(str,fptr1);
            str = strstr(str,",")+1;
            fprintf(fptr1,"%s",new_area);
            str = strstr(str,";");

            fprintf(fptr1,"%s",str);
        }
        else
        {
            fprintf(fptr1,"%s",str);
        }

    }
    if(flag == 0)
        return e_fail;
    fclose(fptr);
    fclose(fptr1);
    return e_success;
}


