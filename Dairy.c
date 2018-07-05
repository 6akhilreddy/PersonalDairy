#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>

void clearInput(void);
void addNewpage(void);
void listAll(void);
void deletepage(void);
void modifypage(void);
int findpage(void);
int prompt(void);
int findnum (int);
int passdairy();

void addpass();
void changepass();
void forgotpass();
void enterpass();

struct password
{
char p[20],q[20];
}pass;
FILE *fp,*ft;
char name[20],hero[20],p;
int i=0;



typedef struct dairy {
    int number;
    char name[20];
    char date[15];
    char month[15];
    char year[15];
    char details[200];
    struct dairy *next;
    int count;
    } Dairy;
Dairy *firstc,*currentc,*newc;
int cnum = 0;

//---------------------------------------------------------------------------

void main()
{
int ch,ch1;
clrscr();
printf("1.enter password\n2.change password\n3.forgot password\n4.exit\n");
scanf("%d",&ch);
switch(ch)
{
case 1:
fp=fopen("password.txt","r");
if(fp==NULL)
addpass();
else
enterpass();
break;
case 2:
changepass();
break;
case 3:
forgotpass();
break;
case 4:
break;
default:break;
}
getch();
}

//--------------------------------------------------------------------------
void addpass()
{
clrscr();
fp=fopen("password.txt","a");
fflush(stdin);
printf("enter password");
while((p=getch())!=13)
{
pass.p[i++]=p;
printf("*");
}
pass.p[i]='\0';


fflush(stdin);
printf("favourite hero");
while((p=getch())!=13)
{
pass.q[i++]=p;
printf("*");
}
pass.q[i]='\0';


fflush(stdin);
fwrite(&pass,sizeof(pass),1,fp);
fclose(fp);
clrscr();
passdairy();
}

void forgotpass()
{
clrscr();
fp=fopen("password.txt","r");
fflush(stdin);
printf("your favorite hero:");
while((p=getch())!=13)
{
hero[i++]=p;
printf("*");
}
hero[i]='\0';


fflush(stdin);
while(fread(&pass,sizeof(pass),1,fp)==1)

if(stricmp(hero,pass.q)==0)
{
printf("password is %s",pass.p);
enterpass();
}

else
printf("wrong answer");
fclose(fp);
}

void changepass()
{
clrscr();
fp=fopen("password.txt","r");
ft=fopen("temp.dat","w");
fflush(stdin);
printf("enter the correct password to change");
while((p=getch())!=13)
{
name[i++]=p;
printf("*");
}
name[i]='\0';


fflush(stdin);
while(fread(&pass,sizeof(pass),1,fp)==1)
if(strcmp(name,pass.p)==0)
{

fflush(stdin);
printf("\n\n..::Editing '%s'\n\n",name);
printf("..::enter new password");
while((p=getch())!=13)
{
pass.p[i++]=p;
printf("*");
}
pass.p[i]='\0';


fflush(stdin);

printf("..::enter your fav hero");
while((p=getch())!=13)
{
pass.q[i++]=p;
printf("*");
}
pass.q[i]='\0';


fflush(stdin);
fwrite(&pass,sizeof(pass),1,ft);
fclose(fp);
fclose(ft);
remove("password.txt");
rename("temp.dat","password.txt");
clrscr();
passdairy();
}
else
printf("you entered wrong password");
}

void enterpass()
{
clrscr();
fp=fopen("password.txt","r");
fflush(stdin);
printf("enter correct password");
while((p=getch())!=13)
{
name[i++]=p;
printf("*");
}
name[i]='\0';


fflush(stdin);
while(fread(&pass,sizeof(pass),1,fp)==1)
if(strcmp(name,pass.p)==0)
{
printf("\nyou are logged in");
getch();
clrscr();
passdairy();
}
else
printf("\nwrong password");

}








int passdairy()
{

    FILE *datafile;
    char *filename = "passdairy.txt";
    char ch;
    firstc = NULL;

    datafile = fopen(filename,"r");

    if(datafile)
    {
	    firstc = (struct dairy *)malloc(sizeof(struct dairy));

	    currentc = firstc;
	    while(1)
	    {
		    newc = (struct dairy *)malloc(sizeof(struct dairy));
		    fread(currentc,sizeof(struct dairy),1,datafile);
		    if(currentc->next == NULL)
			    break;
		    currentc->next = newc;
	    currentc->count=0;
		    currentc = newc;
	    }
	    fclose(datafile);
	    cnum = currentc->number;

    }

    do
    {
	fflush(stdin);
	puts("\nWelcome To The Personal Dairy");
	puts("-- -----------------------------");
	puts("1 - Add a new page");
	puts("2 - Delete a page");
	puts("3 - List all pages");
	puts("4 - Modify page");
	puts("5 - Find a page by name");
	puts("-- -----------------------------");
	puts("Q - Save and quit\n");
	printf("\tYour choice:");
	ch = getchar();
	    ch = toupper(ch);
	switch(ch)
	{
	    case '1':
		puts("Add a new page\n");
		fflush(stdin);
		addNewpage();
		break;
	    case '2':
		puts("Delete a page\n");
		deletepage();
		break;
	    case '3':
		puts("List all pages\n");
		fflush(stdout);
		listAll();
		break;
	    case '4':
		puts("Modify a page\n");
		modifypage();
		break;
	    case '5':
		puts("Find a page by name\n");
		findpage();
		break;
	    case 'Q':
		puts("Save and quit\n");
		default:
		break;
	}
    }
    while(ch != 'Q');





    currentc = firstc;

    if(currentc == NULL)
	    return(0);

    datafile = fopen(filename,"w");

    if(datafile == NULL)
    {
	    printf("Error writing to %s\n",filename);
	    return(1);
    }

    while(currentc != NULL)
    {
	    fwrite(currentc,sizeof(struct dairy),1,datafile);
	    currentc = currentc->next;
    }
    fclose(datafile);
    return(0);
}







void addNewpage(void)
{
clrscr();
    newc = (struct dairy *)malloc(sizeof(struct dairy));

    if(firstc==NULL)
	firstc = currentc = newc;


    else
    {
	currentc = firstc;


	while(currentc->next != NULL)currentc = currentc->next;

	currentc->next = newc;
	currentc = newc;
    }


    fflush(stdin);
    cnum++;
    printf("%27s: %5i\n","page number",cnum);
    currentc->number = cnum;
    fflush(stdin);
    printf("%27s: ","Enter page name");
    gets(currentc->name);
    fflush(stdin);
    printf("%27s: ","Enter date");
    gets(currentc->date);
    fflush(stdin);
    printf("%27s: ","Enter month");
    gets(currentc->month);
    fflush(stdin);
    printf("%27s: ","Enter year");
    gets(currentc->year);
    fflush(stdin);

    printf("\n%30s: ","start writing dairy without pressing enter\n");
    gets(currentc->details);
    fflush(stdin);

    printf("page added!");
    currentc->count=0;
    fflush(stdin);

    currentc->next = NULL;
    getch();
}





void listAll(void)
{
clrscr();
fflush(stdin);
    if(firstc==NULL)
	puts("There are no pages to display!");

    else
    {
    fflush(stdout);
	    printf("%6s %-20s %-15s %-15s %-15s\n","page no#","Name","date","month","year");
	puts("------ -------------------- ------------- -------------------");
      fflush(stdin);
	currentc=firstc;

	do
	{
		fflush(stdout);
		printf("%6d: %-20s %-15s %-15s %-15s\ndairy:\n%s\n\n",\
		currentc->number,\
		currentc->name,\
		currentc->date,\
		currentc->month,\
		currentc->year,\
		currentc->details);
		fflush(stdout);
		getch();


	}

	while((currentc=currentc->next) != NULL);
    }
    getch();
}



void deletepage(void)
{
    int record;
    struct dairy *previousa;

    if(firstc==NULL)
    {
	puts("There are no pages to delete!");
	return;
    }

    listAll();
    printf("Enter dairy page number to delete: ");
    scanf("%d",&record);

    currentc = firstc;

    while(currentc != NULL)
    {
	if(currentc->number == record)
	{
	    if(currentc == firstc)
		firstc=currentc->next;
	    else
		previousa->next = currentc->next;

	free(currentc);
	    printf("page %d deleted!\n",record);
	    return;
	}

	else
	{
	previousa = currentc;
	    currentc = currentc->next;
	}
    }
    printf("page %d not found!\n",record);
    getch();
 }


 void modifypage(void)
{
    int record, result;

    if(firstc==NULL)
    {
	puts("There are no pages to modify!");
	return;
    }

    listAll();
    printf("Enter dairy page number to modify or change: ");
    scanf("%d",&record);

    result = findnum(record);

    if( result >0 ){
	    printf("page %d:\n",currentc->number);
	    printf("Name: %s\n",currentc->name);
	    if(prompt())
		    gets(currentc->name);

	    printf("date: %s\n",currentc->date);
	    if(prompt())
		    gets(currentc->date);

	     printf("month: %s\n",currentc->month);
	    if(prompt())
		    gets(currentc->month);

	     printf("year: %s\n",currentc->year);
	    if(prompt())
		    gets(currentc->year);


	    printf("dairy: %s\n",currentc->details);
	    if(prompt())
		    gets(currentc->details);
	    return;
	}
    printf("page %d was not found!\n",record);
}
/*----------------------------------------------------------------------------*/
int findnum (int recordnum)
{
    int record;
    record = recordnum;
    currentc = firstc;
    while(currentc != NULL)
    {

	if(currentc->number == record)
	     {
	   return 1;
	 }

	else
	{
	    currentc = currentc->next;
	}
    }
    return -1;
}
/*----------------------------------------------------------------------------*/
int findpage(void)
{
     char buff[20];

     if(firstc==NULL)
	{
	puts("There are no pages to find!");
	    return 1;
    }

    printf("Enter page name: ");
    fflush(stdin);
    gets(buff);

    currentc = firstc;
    while(currentc != NULL)
    {
	if( strcmp(currentc->name, buff) == 0 )
	    {
			printf("%6s %-20s %-15s %-15s %-15s\n","pg no#","Name","date","month","year");

	    printf("%6d: %-20s %-15s %-15s %15s\ndairy:\n%s\n",\
	    currentc->number,\
	    currentc->name,\
	    currentc->date,\
	    currentc->month,\
	    currentc->year,\
	    currentc->details);

			return 0;
	    }
		else
		{
			currentc = currentc->next;
		}
    }
    printf("page name %s was not found!\n",buff);
	  return 1;
}
/*----------------------------------------------------------------------------*/
int prompt(void)
{
	char ch;

    fflush(stdin);
	printf("Update? (Y to update any other key to not)");
	ch = getchar();
	ch = toupper(ch);
	fflush(stdin);
	if(ch == 'Y')
	{
		printf("Enter new value: ");
		return(1);
	}
	else
		return(0);
}
/*----------------------------------------------------------------------------*/
