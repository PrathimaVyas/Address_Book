#include"addressbook.h"
int save_file()
{
    char filename[50];
    printf("Enter the filename to copy the content : ");
    scanf("%s",filename);
    if(strstr(filename,".csv") == NULL)
    {
	printf("%s is not .csv file \n",filename);
	return e_fail;
    }
    FILE *fptr = fopen(DEFAULT_FILE,"r");
    if(fptr == NULL)
    {
	printf("FILE OPEN FAILURE\n");
	return e_fail;
    }
    FILE *save_file = fopen(filename,"w");
    if(save_file == NULL)
    {
	printf("FILE OPEN FAILURE\n");
	return e_fail;
    }

    char str[500];
    while(fgets(str,500,fptr) != NULL)
	fprintf(save_file,"%s",str);
    printf("file content saved\n");
    fclose(fptr);
    fclose(save_file);
    return e_success;
}

