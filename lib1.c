#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
//#include"lib1.h"
//#include"mainfile.h"
struct book
{
  int bookid;
  char bname[25] ;
  char author[25];
  int status;
}book;
struct membr
{
  int mis;
  char mname[25] ;
  char department[25];
  int availibcard;
  int phno,year;

}membr;
void screentitle();
void Addbook();
void Search();
void Displaybook();
void Displaymem();
void availablebook();
void Issue();
void Addmembr();
void Exit();
void computer();
char data[500];
#define INBOOK 1 //it is flag for know book is present in library or not. 
#define OUTBOOK 0
FILE *libfile;
FILE *membrfile;
//FILE *co;
FILE *fp1;
FILE *fp2;
FILE *temp1;
FILE *temp2;
void screentitle() {
//display coep library title
	printf("\n                       :::::::::::::::::::::::::::::::::::::");
	printf("\n                       ::                                 ::");
	printf("\n                       ::     ~~~~~~~~~~~~~~~~~~~~~~~     ::");
	printf("\n                       ::     ~                     ~     ::");
	printf("\n                       ::     ~      WELCOME TO     ~     ::");
	printf("\n                       ::     ~                     ~     ::");
	printf("\n                       ::     ~     COEP  LIBRARY   ~     ::");
	printf("\n                       ::     ~                     ~     ::");
	printf("\n                       ::     ~~~~~~~~~~~~~~~~~~~~~~~     ::");
	printf("\n                       ::                                 ::");
	printf("\n                       :::::::::::::::::::::::::::::::::::::\n\n");
}
void Addbook() {
//enter the books from user
 int i;book.status=INBOOK;
	//printf("Choose ur trade:");
	   //opening the libfile file
	libfile = fopen("libfile.txt","a+");
	printf(">Enter The unique id of The Book\n");
	scanf("%d",&book.bookid);
	printf(">Enter The Name of The Book :\n");
        scanf("%s",book.bname);
	printf(">Enter The Name of Author :\n");
        scanf("%s",book.author);
	fprintf(libfile,"\n%d\t\t%s\t\t%s\t\t%d\t\t\t",book.bookid,book.bname,book.author,book.status);    
	fclose(libfile);
	printf(">A New Book has been Added Successfully...\n");
}
void Issue()
{
    int mis,i,Found1=0,Found2=0;char iname[20];
    printf("\nEnter The userid of the Member : \n");
        scanf("%d",&mis);
    if((membrfile=fopen("membrfile.txt","r"))==NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        while(!feof(membrfile)&& Found1==0)
        {
            fscanf(membrfile,"%d %s %s %d %d ",&membr.mis,membr.mname,membr.department,&membr.phno,&membr.availibcard);
            if(mis==membr.mis)
            {
                Found1=1;
            }
        }
        if(Found1)
        {
            if(membr.availibcard<1)
            {
                printf(" ! Library card not available...\n");
            }
            else
            {    printf("\nEnter The Name of book :");
                scanf("%s",iname);
                if((libfile=fopen("libfile.txt","r"))==NULL)
                    printf(" ! The file is empty...\n\n");
                else
                {
                    while(!feof(libfile)&& Found2==0)
                    {
                        fscanf(libfile,"%d %s %s %d", &book.bookid,book.bname,book.author,&book.status);
                        if(strcmp(iname,book.bname)==0)
                            Found2=1;
                        
                    }
                    if(Found2)
                    {
                        if(book.status==0)
                        {
                            printf(" ! Book already issued...\n");
                        }
                        else
                        {   
                           
                            fp2=fopen("fp2.txt","w");
                            if((temp2=fopen("membrfile.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %d %d ",&membr.mis,membr.mname,membr.department,&membr.phno,&membr.availibcard);
                           
                                   
                                    if(mis==membr.mis)
                                    {
                                        membr.availibcard--;
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",membr.mis,membr.mname,membr.department,membr.phno,    membr.availibcard);
                                    }
                                    else{
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t%d\t",membr.mis,membr.mname,membr.department,membr.phno,membr.availibcard);}
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);
                           

                            fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("libfile.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                      fscanf(temp1,"%d %s %s %d", &book.bookid,book.bname,book.author,&book.status);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(iname,book.bname)!=0)
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t",book.bookid,book.bname,book.author,book.status);
                                    }
                                    else
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t",book.bookid,book.bname,book.author,0);
                                    }
                                   
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(libfile);
                            fclose(membrfile);
                            remove("libfile.txt");
                            rename("fp1.txt","libfile.txt");
                            remove("membrfile.txt");
                            rename("fp2.txt","membrfile.txt");
                            printf("Book Successfully issued...\n");
                        }               
                    }
                    else if(!Found2)
                        printf(" ! There is no such Book...\n");
               
                }
            }
        }
        else if(!Found1)
            printf(" ! Invalid User id...\n");
	}
   
}



void Displaybook(){
//display the available books
	libfile = fopen("libfile.txt","a+");
	printf("==============================================================================");
	printf("\nBookid\t\tName\t\tAuthor\t\tStatus_No.\n",data);
	printf("==============================================================================");
	do{
        	fgets(data,500,libfile);
       		printf("%s\n",data);
	}while(!feof(libfile));
	
	fclose(libfile);
  
}
void Displaymem(){
//display member record
membrfile = fopen("membrfile.txt","a+");
	printf("==============================================================================");
	printf("\nMid\tName\tDept\tPh.no\tAvailablecards\tyear\n",data);
	printf("==============================================================================");
    do
    {
        fgets(data,500,membrfile);
        printf("%s\n",data);
    }while(!feof(membrfile));
	
	fclose(membrfile);
  
}
void Author(){
//easy to search book by name
}
void availablebook(){
//how many books available
}
void Search(){
//search the books available in files

     int i;
    char Target[25],stats[3];
    int Found=0;
    if((libfile=fopen("libfile.txt","r"))==NULL)
        printf(" ! The File is Empty...\n\n");
    else
    {
        printf("\nEnter The Name Of Book : ");
            scanf("%s",Target);
        while(!feof(libfile)&& Found==0)
        {
        fscanf(libfile,"%d %s %s %d", &book.bookid,book.bname,book.author,&book.status);
            if(strcmp(Target,book.bname)==0)
                Found=1;
           
        }
        if(Found)
        {
            if(book.status==INBOOK)
                strcpy(stats,"IN");
            else
                strcpy(stats,"OUT");+
           
            printf("\nThe Unique ID of The Book--->  %d\nThe Name of Book is--->  %s\nThe Author is--->  %s\nThe Book Status--->%s\n\n",book.bookid,book.bname,book.author,stats);
            }
        else if(!Found)
            printf("! There is no such Entry...\n");
        fclose(libfile);
    }
}
void Addmembr()
{
	membrfile = fopen("membrfile.txt","a+");
	printf("Enter The MIS of the Member:\n");
        scanf("%d",&membr.mis);
	printf("Enter The Name of the Member :\n");
        scanf("%s",membr.mname);
	printf("Enter The Department\n");
        scanf("%s",membr.department);
	printf("Enter The year of the Member:\n");
        scanf("%d",&membr.year);
	printf("Enter The phone number of the member:\n");
        scanf("%d",&membr.phno);
	membr.availibcard=5;
	fprintf(membrfile,"\n%d\t%s\t%s\t%d\t%d\t",membr.mis,membr.mname,membr.department,membr.phno,membr.availibcard,membr.year);
	fclose(membrfile);
	printf("\nAdded  A New member Successfully...\n");
}
void Exit()
{
  exit(0);
}
int main()
{       
	int choice=0,i;
	screentitle();
	do{

		printf("\n\t~~MENU~~\n [1] Add A New Book\n [2] Display Books Information\n [3] Display members Information\n [4] Search a book \n [5] Add A New Member\n [6] Issue Book\n [7] Exit the program\n\n\t Enter your choice <1-7>: ");
	scanf("%i",&choice);//%i for integer
	switch (choice)
	{   	
        	case 1:Addbook();
			break;
        	case 2:Displaybook();
			break;
		case 3:Displaymem();
			break;
		case 4:Search();
                	break;
        	case 5:Addmembr();
                	break;
		case 6:Issue();
                	break;
		case 7:Exit();
                	break;
		default:
            		printf(" ! Invalid Input...\n");
	}
	}while(choice!=7);
	
return (0);
}


