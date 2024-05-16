#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define DEFAULT_FILE "contact_info.csv"
#define DUPLICATE_FILE "duplicate.csv"

enum
{
    ADD_CONTACT = 1,
    EDIT,
    SEARCH,
   DELETE,
   PRINT,
  SAVE,
 EXIT,
}; 

typedef enum
{
	e_fail = -10,
	e_back,
	e_success,
	e_no_match,
	e_new_line,
} Status;

typedef struct
{
	char name[60];
	char mobile_num[11]; 
	char email_address[70];
	char location[100];
} ContactInfo;

typedef struct
{
	FILE *fp;
	ContactInfo *list;
	int count;	
} AddressBook;

	//TO ADD THE CONTACT TO FILE
int add_contact(AddressBook *book,char *line1);

int check_name_or_not(char *name);

int check_name_in_file(char *name,char *file);
int check_till_comma(char *str);

int check_num_or_not(char *phonenum);
int check_phno_in_file(char *phonenum,char *file);

int check_mail_or_not(char *mail);
int check_mail_in_file(char *mail,char *file);

	// TO SEARCH THE CONTACT IN FILE
int search_contact(AddressBook *book);

int search_name(char *name,char *file);
int store_str(char *str,char *line);

int search_phno(char *num,char *file);

int search_mail(char *mail_id,char *file);

int search_location(char *place,char *file);

	// TO EDIT THE CONTACT IN THE FILE

int edit_contact(AddressBook  *book);
int edit_name(char *name,char *new_name,char *input_file,char *extrafile);
int edit_phno(char *phno,char *new_num,char *input_file,char *extrafile);
int copy_till_comma(char *str,FILE *file);
int edit_mail(char *mail,char *new_mail,char *input_file,char *extrafile);
int edit_location(char *area,char *new_area,char *input_file,char *extrafile);
int save(char *file1,char *file2);

	// TO PRINT ALL THE INFO
int print();
int print_till_comma(char *str,FILE *fptr,char *name);
int include(char *file,int inc,char *dup);


int save_file();

int delete_contact(AddressBook *book);
int delete_contact_info(char *name,char *file,char *dup_name);

#endif

