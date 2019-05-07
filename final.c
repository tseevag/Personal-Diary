#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

struct rec
{
	char time[5],note[200];
};

struct upass
{
	char name[20],unam[20],pass[15];
};

short int count,check;
char uname[15];


void heading(int);
void add();
void view(char [],int);
void modify();
void deleterec();
void changepass(char unam[]);

short int pass (short int k)
{
	short int i=0,a=0;
	struct upass p;
	char epass[15],c;
	FILE *f;

	if(k==2)
	{
		printf("\n\n\tEnter your name:");
		gets(p.name);
		fflush(stdin);
	}

	printf("\n\n\tEnter user name:");
	gets(p.unam);
	fflush(stdin);

	strcpy(uname, p.unam);

	if(k==1)
	f=fopen(p.unam,"rb");

	else
	f=fopen(p.unam,"wb");

	printf("\tEnter the password:");

	while(i<10)
	{
		c=getch();

		if(c==8)
		{
			if (i==0)
			continue;

			else
			{
				printf("\b");
				printf(" ");
				printf("\b");
				i--;
				continue;
			}
		}

		epass[i]=c;

		if(c==13)
		break;

		else
		printf("*");

		i++;

	}

	epass[i]='\0';

	if (k==1)
	{
		if(f==NULL)
		{
			printf("\n\tYou entered wrong username.");

			if (a<2)
			printf("\n\tPlease try again.");

			a++;

			fclose(f);
			return 0;
		}

		while(fread(&p,sizeof(p),1,f)==1)
		{
			if(strcmp(p.pass,epass)==0)
			{
				printf("\n\n\tSUCCESSFULLY LOGGED IN.\n\n\t\t\t\tWel-Come %s.\n\n\n\n\t\tPress any key to continue.",strupr(p.name));
				fclose(f);
				getch();
				return 1;
			}

			else
			{
				printf("\n\tYou have entered wrong password.");

				if (a<2)
				printf("\n\tPlease try again.");

				a++;

				fclose(f);
				return 0;
			}
		}
	}

	else
	{
		strcpy(p.pass,epass);
		fwrite(&p,sizeof(p),1,f);

		fclose(f);

		printf("\n\n\n\t\t\tYour account has been successfully created.\n\n\n\n\t\t\tPress any key to continue.");
		getch();
		return 1;
	}

}

void signin()
{
	struct upass p;
	short int cho,a=0;
	FILE *f;


	printf("\n\t\t\t~SIGN IN PORTAL~\n\n\tEnter\n\t<1> to LOG IN.\n\t<2> to Create New Accout.\n\t<3> to exit.\n\n\tPlease enter your choise:");
valid:
	scanf("%d",&cho);
	fflush(stdin);

	switch(cho)
	{
		case 1:
			while(check!=1 && a<3 )
			{
				check = pass(1);
				a++;

			}

			if (a>2)
			{
				printf("\n\tYou entered wrong username or password for three times.\n\tYou are not authorized. ");
				exit(0);
			}
			break;


		case 2:
			check =pass(2);
			break;

		case 3:
			break;

		default:
			printf("\n\tYour choise is wrong.\n\n\tPlease make valid choise:");
			goto valid;
	}

}




int main()										//main
{
	int i,opt;
	char date[10];

	heading(0);
	signin();

	if (check==1)
	{
		start:
		printf("\n");
		heading(0);

		printf("\n\n\t\t~MAIN MENU~\n\t\t");

		for(i=0;i<11;i++)
		printf("%c",205);

		printf("\n\n\tPress <1> To ADD RECORD\t");
		printf("\n\tPress <2> To VIEW RECORDS\t");
		printf("\n\tPress <3> To MODIFY RECORDS\t");
		printf("\n\tPress <4> To DELETE RECORD\t");
		printf("\n\tPress <5> To CHANGE PASSWORD\t\t");
		printf("\n\tPress <6> To EXIT\t\t");

		printf("\n\n\tPlese Enter your choise:");
		feri:
		scanf("%d",&opt);
		fflush(stdin);

		switch(opt)
		{
			case 1:
		        add();

		        goto start;

		    case 2:
		    	count=0;

		    	heading(2);

		       	printf("\tEnter the date of record you want to view[dd-mm-yyyy]:");
		    	gets(date);
		    	fflush(stdin);

				view ( date , 10 );

		        goto start;

		    case 3:
		    	count=0;

		        modify();

		        goto start;

		    case 4:
		    	count=0;

		        deleterec();

		        goto start;

			case 5:
				count =0;

				heading(5);

				changepass(uname);

				goto start;

		    case 6:
		    	heading(0);

		        printf("\n\n\t\tThank you for using the software.");

		        getch();

		        exit(0);

		    default:

		        printf("\n\tYou entered wrong choise.\nPlease enter valid choise:");

		        goto feri;

		}
	}

    printf("\tPress any key to exit.");
    getch();

}


								// Functions start here
void heading(int a)
{
	int i;
	system("cls");

	printf("\t\t\t\t%c",201);

	for(i=0;i<29;i++)
	printf("%c",205);

	printf("%c",187);

	printf("\n\t\t\t\t%c ",186);

	switch(a)
	{
		case 0:
			printf(" WEL-COME TO PERSONAL DIARY ");
			break;

		case 1:
			printf("        ADDING MENU         ");
			break;

		case 2:
			printf("       VIEWING MENU         ");
			break;

		case 3:
			printf("       MODIFING MENU        ");
			break;

		case 4:
			printf("       DELETING MENU        ");
			break;

		case 5:
			printf("      CHANGE PASSWORD       ");
			break;

	}

	printf("%c\n",186);

	printf("\t\t\t\t%c",200);

	for(i=0;i<29;i++)
	printf("%c",205);

	printf("%c\n",188);

	if (a==0)
	printf("\t\t\t\t\t\t\t\tby Shiva Gaihre");

}



										//Function 2
void  view ( char dat[], int a)
{
	struct rec r;
	char ch;
	FILE *f;

	f=fopen(dat,"rb");

	if (f==NULL)
	{
		printf("\n\tFile doesn't exist.\n\tPress any key to exit.");
		getch();
		return ;
	}

	while(fread(&r,sizeof(r),1,f)==1)
	{
		printf("\tTime:");
		puts(r.time);

		printf("\tNote:");
		puts(r.note);
	}

	fclose(f);

	if(a==10)
	{
		printf("\n\tDo you want to view another record?[Y/N]:");
		ch = getche();
		fflush(stdin);
		printf("\n");

		if (ch=='y' || ch=='Y')
		{
			heading(2);

	       	printf("\tEnter the date of record you want to view[dd-mm-yyyy]:");
        	gets(dat);
        	fflush(stdin);

			view ( dat , 10 );

		}

		printf("\n\n\tPress any key to exit.");
		getch();
	}
	return ;
}


						//Function 1
void add()
{
	struct rec r,rc;
	char date[10], ch ='y';
	int rij=1,i;
	FILE *f;

	heading(1);

	printf("\n\t\nEnter Date[dd-mm-yyyy]:");
	gets(date);
	fflush(stdin);

	f=fopen(date,"wb+");

	if (f==NULL)
	{
		printf("\t\nUnable to open file.");
		return ;
	}

	else
	{

		while(ch=='y'||ch=='Y')
		{
			rij=1;
			printf("\tTime[HH:MM]:");
			gets(r.time);
			fflush(stdin);

			while(fread(&rc,sizeof(rc),1,f)==1)
			{
				if (strcmp(r.time,rc.time)==0)
				{
					printf("\n\n\tThis record already exists.");
					rij=0;
					break;
				}

			}

			if(rij!=0)
			{
				printf("\tNote:");
				gets(r.note);
				fflush(stdin);


				fwrite(&r,sizeof(r),1,f);

				printf("\n\tYour record is added successfully.");
				rewind(f);
			}


			printf("\n\n\n\tDo You Want to add another record[Y/N]:");
			ch=getche();
			printf("\n");

		}
	}

	fclose(f);

	if(count==0)
	{
		count++;
		printf("\n\n\n\tPress any key to exist.");
		getch();
	}


	return ;
}


							//Function 3
void modify()
{
	struct rec r,rc;
	char date[10], ch ='y',choise=89;
	int way,rij=1,tari,i=0;
	FILE *f;

	heading(3);

	printf("\n\tEnter the date[dd-mm-yyyy] of the record you want to modify:");
	gets(date);
	fflush(stdin);

	f=fopen(date,"rb+");

	if (f==NULL)
	{
		printf("\n\tFile doesn't exist.");
		return ;
	}
	printf("\n\tYour record is:\n");

	view(date,1);

	printf("\n\n\n\tPress \n\t<1> to modify whole records.\n\t<2> to modify the record of specific time.\n\t<3> to exit.\n\t\n\n\tPlease make a choise:");
	valid1:
	scanf("%d",&way);
	fflush(stdin);

	switch(way)
	{
		case 1:
			fclose(f);
			remove(date);

			f=fopen(date,"wb+");

			while(choise =='y'||choise=='Y')
			{
				rij=1;
				printf("\n\tTime[HH:MM]:");
				gets(r.time);
				fflush(stdin);

				while(fread(&rc,sizeof(rc),1,f)==1)
				{
					if (strcmp(r.time,rc.time)==0)
					{
						printf("\n\n\tThis record already exists.");
						rij=0;
						break;
					}

				}

				if(rij!=0)
				{
					printf("\tNote:");
					gets(r.note);
					fflush(stdin);


					fwrite(&r,sizeof(r),1,f);

					printf("\n\tYour record is added successfully.");
					rewind(f);
				}


				printf("\n\n\n\n\tDo You Want to add another record to the same date?[Y/N]:");
				choise=getche();
				fflush(stdin);
				printf("\n");

			}

			break;

		case 2:
			printf("\n\n\tPress \n\t<1> to modify date.\n\t<2> to Modify note.\n\t<3> to exit.\n\n\tPlease enter your choise:");
			valid2:
			scanf("%d",&tari);
			fflush(stdin);

			if(tari!=1 && tari!=2 && tari!=3)
			{
				printf("\n\tYour choise is invalid.\n\tPlease make valid choise:");
				goto valid2;
			}


			printf("\n\tEnter the time of record to be modified[HH:MM]:");
			gets(r.time);
			fflush(stdin);

			while (fread(&rc,sizeof(rc),1,f)==1)
			{
				if(strcmp(r.time,rc.time)==0)
				{
					if(tari==1)
					{
						printf("\n\tEnter the new time[HH:MM]:");
						gets(r.time);
						strcpy(r.note,rc.note);
						fflush(stdin);
					}

					else if(tari==2)
					{
						printf("\n\tEnter new note:");
						gets(r.note);
						fflush(stdin);
					}

					else if(tari==3)
					break;

					i++;
				}
			}

			if(i==0)
			printf("\n\tCOULDN'T FIND A MATCH.");

			else
			{
				fseek(f,-sizeof(r),SEEK_CUR);
				fwrite(&r,sizeof(r),1,f);
			}


			break;

		case 3:
			break;

		default:
			printf("\n\n\tYour choise is invalid.\n\n\tPlease make valid choise:");
			goto valid1;
			break;


	}

	fclose(f);

	printf("\n\n\tDo You Want to modify another record?[Y/N]:");
	ch=getche();
	printf("\n");


	if(ch=='y' || ch=='Y')
	{
		modify();
	}


	fclose(f);

	if(count==0)
	{
		count++;
		printf("\n\n\n\tPress any key to exist.");
		getch();
	}

	return ;
}


									//Function 4
void deleterec()
{
	struct rec r,rc;
	char date[10],time[5], ch ='y';
	int way;
	FILE *f,*t;

	heading(4);


	printf("\n\tEnter the date[dd-mm-yyyy] of the record you want to delete:");
	gets(date);
	fflush(stdin);


	f=fopen(date,"rb");

	if (f==NULL)
	{
		printf("\n\tFile doesn't exist.");
		return ;
	}

	printf("\n\tYour record is:\n");

	view(date,1);


	printf("\n\n\tPress \n\t<1> to delete whole records.\n\t<2> to delete the record of specific time.\n\t<3> to exit.\n\n\tPlease make your choise:");
	valid:
	scanf("%d",&way);
	fflush(stdin);

	switch(way)
	{
		case 1:
			fclose(f);
			remove(date);
			break;

		case 2:
			printf("\n\tEnter the time of record to be deleted:");
			gets(time);
			fflush(stdin);

			while(fread(&rc,sizeof(rc),1,f)==1)
			{
				if(strcmp(time,rc.time)==0)
				goto xa;

				else
				{
					printf("\n\tCouldn't find the entered time.");
					fclose(f);
					break ;
				}
			}
		xa:
			rewind(f);
			t = fopen("Temp","wb");

			while(fread(&r,sizeof(r),1,f)==1)
			{
				if (strcmp(time,r.time)!=0)
				fwrite(&r,sizeof(r),1,t);
			}

			fclose(f);
			fclose(t);
			remove(date);
			rename("Temp",date);
			break;

		case 3:
			break;

		default:
			printf("\n\tYour choise is wrong.\n\n\tPlease make a valid choise:");
			goto valid;
	}


	printf("\n\n\n\tDo you want to delete another record[Y/N]:");
	ch=getche();
	printf("\n\n");


	if (ch=='y'||ch=='Y')
	deleterec();

	if(count==0)
	{
		count++;
		printf("\n\n\n\tPress any key to exist.");
		getch();
	}

	return ;
}




void changepass(char unam[])
{
	short int i=0,a=0,ch,b;
	struct upass p;
	char epass[15],newpass[15],confirm[15],c;
	FILE*f;




	printf("\n\tEnter old password:");
	while(i<10)
	{
		c=getch();

		if(c==8)
		{
			if (i==0)
			continue;

			else
			{
				printf("\b");
				printf(" ");
				printf("\b");
				i--;
				continue;
			}
		}

		epass[i]=c;

		if(c==13)
		break;

		else
		printf("*");

		i++;

	}

	epass[i]='\0';

	f=fopen(unam,"rb+");

	while(fread(&p,sizeof(p),1,f)==1)
	{
		if(strcmp(epass,p.pass)==0)
		{
			while(a<2)
			{
				if (a==0)
				printf("\n\tEnter new password:");

				else if (a==1)
				printf("\n\tConfirm password:");

				for(i=0;i<15;i++)
				{
					c=getch();

					if(c==8)
					{
						if (i==0)
						continue;

						else
						{
							printf("\b");
							printf(" ");
							printf("\b");
							i--;
							continue;
						}
					}

					epass[i]=c;
					b=i;

					if(c==13)
					break;

					else
					printf("*");

					i++;

				}

				epass[i]='\0';

				if(a==0)
				strcpy(newpass,epass);

				else
				strcpy(confirm ,epass);

				a++;
			}

			if( strcmp (newpass,confirm)==0)
			{
				rewind(f);

				strcpy(p.pass,epass);
				strcpy(p.unam,unam);

				fwrite(&p,sizeof(p),1,f);

				fclose(f);

				ch=1;
			}

			else
			{
				printf("\n\tThe passwords you entered don't match.");
				fclose(f);
				ch=0;
				break;
			}
		}

		else
		{
			printf("\n\tYou entered wrong password.");
			fclose(f);
			ch=0;
			break;
		}
	}

	if(ch==1)
	printf("\n\n\n\n\t\t\t\PASSWORD SUCCESSFULLY CHANGED.");


	printf("\n\n\t\t\tPress any key to exit.");
	getch();

}
