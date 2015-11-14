

/*****************************************************************************
 * Copyright (C) 2015 Bhagyashri J. Kshirsagar
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/

//---------------------------------HEADER FILES AND SOME DECLERATION-----------------------------------------------------------------
#define _XOPEN_SOURCE
#define _GNU_SOURCE
#define SIZE 6000
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define INBOOK 1 //it is flag for know book is present in library or not. 
#define OUTBOOK 0

//-------------------------------STRUCTURE DECLERATION-------------------------------------------------------------------------------
struct book
{
  int bookid;
  char bname[25] ;
  char author[25];
  int status;

}book,temp;
struct membr
{
  int mis;
  char mname[25] ;
  char department[25];
  int availibcard;
  long phno,year;

}membr;
void screentitle();
void Addbook();
void Search();
void Displaybook();
void Displaymem();
void Issue();
void Addmembr();
void Exit();
void Author();
void bookret();
void sort();
void login();
char data[500];
struct book ar[1000];

FILE *libfile,*membrfile;
FILE *fp1;
FILE *fp2;
FILE *temp1, *temp2;
FILE *login1;
FILE *outfile;

//---------------------------------------------LOGIN-----------------------------------------------------------------------------------
void login(){

	char username[SIZE],password1[SIZE],password2[SIZE],*buf;
	char filename[SIZE];

	printf("enter password filename:");
	scanf("%s",filename);
	printf("username");
	scanf("%s",username);
	do{
		buf=getpass("password:");
		sprintf(password1,"%s",buf);
		buf=getpass("enter again:");
		sprintf(password2,"%s",buf);
		if(strcmp(password1,password2)!=0)
			printf("password do not match! TRY AGAIN\n\n");
	}
	while(strcmp(password1,password2)!=0);
		if((outfile=fopen(filename,"a+"))==NULL){
			printf("\n file error!");
		}
	else{
		fprintf(outfile,"%s\t%s\t",username,buf);
	}
	fclose(outfile);
	
	//menu();
}

//-------------------------------------------MENU-------------------------------------------------------------------------------------
int menu(){
	int choice=0,i;
	do{

	printf("\n\t~~Library MENU~~\n [1] Add A New Book\n [2] Add A New Member\n [3] Display Books Information\n [4] Display Members Information  \n [5] Issue Book\n [6] Search a book\n [7] Sort\n [8] Search by author\n [9] Return book \n [10] Exit\n\n\t Enter your choice <1-10>: ");
	scanf("%i",&choice);//%i for integer
	switch (choice)
		{   	
		case 1:Addbook();
			break;
		case 2:Addmembr();
			break;
		case 3:Displaybook();
			break;
		case 4:Displaymem();
			break;
		case 5:Issue();
			break;
		case 6:Search();
			break;
		case 7:sort();
			break;
		case 8:Author();
			break;
		case 9:bookret();
			break;
		case 10:Exit();
			break;
		default:
			printf(" ! Invalid Input...\n");
		}
	}while(choice!=10);

	return (0);
}

//---------------------------------------------------------display coep library title----------------------------------------------
void screentitle() {
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

//-------------------------------------------------------------Add new books-------------------------------------------------------
void Addbook() {
	int i,s;
	book.status=INBOOK;
	libfile = fopen("libfile.txt","a+");
	printf(">>>Enter The unique id of The Book :\n");
	scanf("%d",&book.bookid);
	printf(">>>Enter The Name of The Book :\n");
	scanf("%s",book.bname);
	printf(">>>Enter The Name of Author :\n");
	scanf("%s",book.author);
	fprintf(libfile,"\n%d\t\t%s\t\t%s\t\t%d\t\t\t",book.bookid,book.bname,book.author,book.status);    
	fclose(libfile);
	printf(">>>A New Book has been Added Successfully...\n");

}

//-----------------------------------------------Add new member---------------------------------------------------------------------
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
	scanf("%ld",&membr.year);
	printf("Enter The phone number of the member:\n");
	scanf("%ld",&membr.phno);
	membr.availibcard=5;
	fprintf(membrfile,"\n%d\t%s\t%s\t%ld\t%d\t%ld\t",membr.mis,membr.mname,membr.department,membr.phno,membr.availibcard,membr.year);
	fclose(membrfile);
	printf("\nAdded  A New member Successfully...\n");
}

//------------------------------------------------Display books------------------------------------------------------------------------
void Displaybook(){
	libfile = fopen("libfile.txt","a+");

	printf("==========================================================================================================");
	printf("\nBookid\t\tName\t\tAuthor\tStatus_No.\n",data);
	printf("============================================================================================================");
	do{
		fgets(data,500,libfile);
		printf("%s\n",data);
	}while(!feof(libfile));

	fclose(libfile);

}

//-----------------------------------------Dsiplay member record------------------------------------------------------------------
void Displaymem(){
	membrfile = fopen("membrfile.txt","a+");

	printf("==============================================================================");
	printf("\nMIS\tName\tDept\tPh.no\tAvailablecards\tyear\n",data);
	printf("==============================================================================");
	do
	{
		fgets(data,500,membrfile);
		printf("%s\n",data);
	}while(!feof(membrfile));

	fclose(membrfile);
}

//-----------------------------------------issue books-----------------------------------------------------------------------------
void Issue() {
	int mis,i,Found1=0,Found2=0;char iname[20];
	printf("\nEnter The userid of the Member : \n");
	scanf("%d",&mis);
	if((membrfile=fopen("membrfile.txt","r"))==NULL)
		printf(" ! The file is empty...\n\n");
	else {
	
		while(!feof(membrfile)&& Found1==0) {
			fscanf(membrfile,"%d %s %s %ld %d ",&membr.mis,membr.mname,membr.department,&membr.phno,&membr.availibcard);
		if(mis==membr.mis) {
			Found1=1;
		}
		}
		if(Found1) {
			if(membr.availibcard<1){
			printf(" ! Library card not available...\n");
		}
		else {
			printf("\nEnter The Name of book :");
			scanf("%s",iname);
		if((libfile=fopen("libfile.txt","r"))==NULL)
			printf(" ! The file is empty...\n\n");
		else {
		while(!feof(libfile)&& Found2==0) {
			fscanf(libfile,"%d %s %s %d", &book.bookid,book.bname,book.author,&book.status);
		if(strcmp(iname,book.bname)==0)
			Found2=1;
		}
		if(Found2) {
		if(book.status==0) {
			printf(" ! Book already issued...\n");
		}
		else {   
			fp2=fopen("fp2.txt","w");
		if((temp2=fopen("membrfile.txt","r"))==NULL)
			printf(" ! The file is empty...\n\n");
		else {
		while(!feof(temp2)) {
			fscanf(temp2,"%d %s %s %ld %d ",&membr.mis,membr.mname,membr.department,&membr.phno,&membr.availibcard);
		if(mis==membr.mis) {
			membr.availibcard--;	
			fprintf(fp2,"\n %d\t%s\t%s\t%ld\t%d\t",membr.mis,membr.mname,membr.department,membr.phno,membr.availibcard);
		}                          
		else{
			fprintf(fp2,"\n %d\t%s\t%s\t%ld\t%d\t",membr.mis,membr.mname,membr.department,membr.phno,membr.availibcard);
		}
		if(feof(temp2))
		break;
		}
		}
			fclose(temp2);
			fclose(fp2);
			fp1=fopen("fp1.txt","w");
		if((temp1=fopen("libfile.txt","r"))==NULL)
			printf(" ! The file is empty...\n\n");
		else {
		while(!feof(temp1)) {	
			fscanf(temp1,"%d %s %s %d", &book.bookid,book.bname,book.author,&book.status);
		if(feof(temp1))
		break;	
		if(strcmp(iname,book.bname)!=0) {
			fprintf(fp1,"\n%d\t%s\t%s\t%d\t",book.bookid,book.bname,book.author,book.status);
		}
		else {
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

//-----------------------------------------search book----------------------------------------------------------------------------
void Search(){

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
		strcpy(stats,"OUT");

		printf("\nThe Unique ID of The Book--->  %d\nThe Name of Book is--->  %s\nThe Author is--->  %s\nThe Book Status--->%s\n\n",book.bookid,book.bname,book.author,stats);
		}
	else if(!Found)
		printf("! There is no such Entry...\n");
		fclose(libfile);
	}
}

//-----------------------------------------------------search by author------------------------------------------------------------------
void Author(){
	int i;   
	char Target[500];
	int Found=0;
	
	if((libfile=fopen("libfile.txt","r"))==NULL)
		printf(" ! The file is empty... \n\n");
	else
	{
		printf("\nEnter The Name Of Author : ");
		scanf("%s",Target);
		printf("\nBooks:");
		while(!feof(libfile))
		{
	
		fscanf(libfile,"%d %s %s %d",&book.bookid,book.bname,book.author,&book.status);
		if(strcmp(Target,book.author)==0)
		{
		Found=1;
		printf("\n\t%s",book.bname);
		}
		}
	if(!Found)
		printf(" ! There is no such Entry...\n");
	fclose(libfile);
	}
}

//-----------------------------------------books return------------------------------------------------------------------------
void bookret() {
	int mis,i,Found1=0,Found2=0,flag=0;char retbookname[20];
	temp1=libfile;temp2=membrfile;
	printf("\nEnter The userid of the Member :\n");
	scanf("%d",&mis);
	if((membrfile=fopen("membrfile.txt","r"))==NULL)
		printf(" ! The file is empty...\n\n");
	else {
		while(!feof(membrfile)&& Found1==0) {
		fscanf(membrfile,"%d %s %s %ld %d ",&membr.mis,membr.mname,membr.department,&membr.phno,&membr.availibcard);
	if(mis==membr.mis) {
		Found1=1;
		}		
	}
	if(Found1) {
		if(membr.availibcard>=5) {
			printf(" ! Error...\n");
		}
		else
		{    
			printf("\nEnter The Name of book :");
			scanf("%s",retbookname);
		if((libfile=fopen("libfile.txt","r"))==NULL)
			printf(" ! The file is empty\n\n");
		else
		{
			while(!feof(libfile)&& Found2==0)
		{
			fscanf(libfile,"%d %s %s %d", &book.bookid,book.bname,book.author,&book.status);
		if(strcmp(retbookname,book.bname)==0)
			Found2=1;
		}
		if(Found2)
		{	
			if(book.status==1)
			{
			printf(" ! Error:Book already in stock...\n");
			}
		else
		{   
			fp2=fopen("fp2.txt","w");
		if((temp2=fopen("membrfile.txt","a+"))==NULL)
			printf(" ! The file is empty...\n\n");
		else
		{
		while(!feof(temp2))
		{
			fscanf(temp2,"%d %s %s %ld %d ",&membr.mis,membr.mname,membr.department,&membr.phno,&membr.availibcard);


		if(mis==membr.mis)
		{
			membr.availibcard++;
			fprintf(fp2,"\n %d\t%s\t%s\t%ld\t%d\t",membr.mis,membr.mname,membr.department,membr.phno,    membr.availibcard);
		}
		else
		{
			fprintf(fp2,"\n %d\t%s\t%s\t%ld\t%d\t",membr.mis,membr.mname,membr.department,membr.phno,membr.availibcard);
		}
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
		if(strcmp(retbookname,book.bname)!=0)
		{
			fprintf(fp1,"\n%d\t%s\t%s\t%d\t",book.bookid,book.bname,book.author,book.status);
		}
		else
		{
			fprintf(fp1,"\n%d\t%s\t%s\t%d\t",book.bookid,book.bname,book.author,1);
		}

		}
		}
		fclose(temp1);
		fclose(fp1);
		fclose(libfile);
		fclose(membrfile);
		printf("Book Successfully Returned...\n");
		remove("libfile.txt");
		rename("fp1.txt","libfile.txt");
		remove("membrfile.txt");
		rename("fp2.txt","membrfile.txt");

		}               
		}
		else if(!Found2)
		printf("! There is no such Book...\n");

		}
		}
		}
		else if(!Found1)
		printf("! Invalid User id...\n");      
		}
}

//-----------------------------------------------SORT DATA------------------------------------------------------------------------
void sort(){
	libfile=fopen("libfile.txt","r");
	printf("\nBookid\t\tName\t\tAuthor\tStatus_No.\t\n");
   		int count = 0;
		struct book ar[10000];
            	while(fread(&book,sizeof(book),1,libfile)==1){
				ar[count] = book;
				count++;
               
	    	}	
		printf("%d", count);
		int i, j;
		for(i = 0;i < count; i++) {
			for(j = i + 1; j < count; j++) {
				//if(strcmp(ar[i].bname, ar[j].bname) > 0) {
				if(ar[i].bookid > ar[j].bookid ) {
					struct book temp = ar[i];
					ar[i] = ar[j];
					ar[j] = temp;
				}
			}
		}
		
		for(i = 0; i < count; i++)
               	printf("\n%d\t\t%s\t\t%s\t\t%d\t\t\t",ar[i].bookid,ar[i].bname,ar[i].author,ar[i].status);
		return;
		fclose(libfile);
	
}
//--------------------------------------------------------exit function----------------------------------------------------------------
void Exit() {
	/*int a;
	char y,n;
	printf("Do you want to exit(Y/N) press y for Yes or n or No:");
	scanf("%d",&a);
	if(a==y) {
	exit(0);
	}
	else if (a==n) {
	menu();
	}*/
exit(0);
}


//------------------------------------------------MAIN FUNCTION-------------------------------------------------------------------------
int main() {       
	login();
	screentitle();
	menu();	
}
//----------------------------------------------------------------------------------------------------------------------------------
