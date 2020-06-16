#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<conio.h>
#include <ctype.h>
//#include <windows.h>
#include<time.h>
#define AB      "0123456789"
#define ABLEN   ( sizeof(AB) - 1 )
#define ARRSIZ  5
void reg();
void menu(char userid[6]);
void ram();
void shoppinglist(char uid[6]);
struct mess{
   char id[6];
   char feedback[500];
   char month[10],weekd[10],time[10],day[10],year[10];
}m1;
struct web
{

  char name[30],pass[30];
  char complaint[1000];

  char attendance[5];
  char  date[10], time[10],year[10],month[10],weekd[10],day[10];


  char  id[6];
  char feedback[1000];

}w[99];
struct schedule
{
    char userid[6];
    char eventname[30][100];
    int eventdate[30][3];
};
struct bill
{
    int status[48];
    int duedate[48][3];
    char bill[48][100];
    char uid[6];
};
struct comp{
    char id[6];
    char complaint[500];
    char month[10],weekd[10],time[10],day[10],year[10];
}c1,c2,c3;

struct feed{
   char id[6];
   char feedback[500];
   char month[10],weekd[10],time[10],day[10],year[10];
}f1;
struct shopping
{
    char id[6];
    char items[100][100];
    int qty[100];
    int delivery;
    int order;
    int houseno;
};
/*void setcolor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
    {
        wColor=(csbi.wAttributes & 0xB0)+(ForgC & 0x0B);
    //	SetConsoleTextAttributes(hStdOut,wColor);
        SetConsoleTextAttribute(hStdOut,wColor);
    }
}*/
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}
int kal()
{
    int r, h, n;

    n=10;

    for(r=n/2; r<=n; r+=2)
    {
        for(h=1; h<n-r; h+=2)
        {
            printf(" ");
        }

        for(h=1; h<=r; h++)
        {
            printf("*");
        }

        for(h=1; h<=n-r; h++)
        {
            printf(" ");
        }

        for(h=1; h<=r; h++)
        {
            printf("*");
        }

        printf("\n");
    }

    for(r=n; r>=1; r--)
    {
        for(h=r; h<n; h++)
        {
            printf(" ");
        }

        for(h=1; h<=(r*2)-1; h++)
        {
            printf("*");
        }

        printf("\n");
    }

    return 0;
}
char* timy()
{
    static char arr[10] = {'\0'};
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strcpy(arr,asctime(tm));
    return arr;
}
char* random()
{
    srand( time(NULL) );
    //static char arr[ARRSIZ] = {'\0'};
    static char arr[6];
    arr[ARRSIZ]='\0';
    int  nletters = 1;
    int  ndigits  = ARRSIZ - nletters;
    arr[0]='#';
    int b = 1;
    while ( ndigits )
    {
        int c = AB[ rand() % ABLEN ];
        if ( ndigits && isdigit(c))
        {
            ndigits--;
            arr[b++] = c;
        }
        else
        {
            continue;
        }
    }
    return arr;
}
void shoplistcreate(char uid[6])
{
    FILE *fp;
    int house=0;
    printf("Enter your house number to avail shopping list facility\nIf you do not wish to use this facility enter 0\n");
    scanf("%d",&house);
    struct shopping make;
    strcpy(make.id,uid);
    make.delivery=0;
    make.order=0;
    make.houseno=house;
    int x;
    for(x=0;x<100;x++)
    {
        make.qty[x]=0;
        make.items[x][0]='\0';
    }
    fp=fopen("ShoppingList.bin","rb+");
    if(!fp)
    {
        fclose(fp);
        fp=fopen("ShoppingList.bin","wb+");
    }
    //fp=fopen("ShoppingList.bin","ab+");
    fseek(fp,sizeof(struct shopping),SEEK_END);
    fwrite(&make,sizeof(struct shopping),1,fp);
    fclose(fp);
}
void loggedin(char uid[6])
{
    FILE *f;
    struct schedule creation;
    struct bill b;
    strcpy(creation.userid,uid);
    for(int x=0;x<30;x++)
    {
        creation.eventdate[x][0]=0;
        creation.eventdate[x][1]=0;
        creation.eventdate[x][2]=0;
        creation.eventname[x][0]='\0';
    }
    {f=fopen("UserSched.bin","rb+");
    if(!f)
    {
        fclose(f);
        f=fopen("UserSched.bin","wb+");
    }
    fseek(f,sizeof(struct schedule),SEEK_END);
    fwrite(&creation,sizeof(struct schedule),1,f);
    fclose(f);}
    {f=fopen("payments.bin","rb+");
    time_t now;
    time(&now);
    struct tm *local=localtime(&now);
    int d,m,y;
    d=local->tm_mday;
    m=local->tm_mon+1;
    y=local->tm_year+1900;
    int p,o=0;
    if(!f)
    {
        fclose(f);
        f=fopen("payments.bin","wb+");
    }
    strcpy(b.uid,uid);
            for(p=0;p<12;p++)
            {
                if((p+1)<m)
                {
                    b.status[p]=1;
                    b.status[12+p]=1;
                    b.status[24+p]=1;
                    b.status[36+p]=1;
                }
                else
                {
                    b.status[p]=0;
                    b.status[12+p]=0;
                    b.status[24+p]=0;
                    b.status[36+p]=0;
                }
                b.duedate[p][1]=(p+1);
                b.duedate[12+p][1]=(p+1);
                b.duedate[24+p][1]=(p+1);
                b.duedate[36+p][1]=(p+1);
                strcpy(b.bill[p],"Electricity Bill");
                strcpy(b.bill[12+p],"Water Bill");
                strcpy(b.bill[24+p],"Digital Cable Bill");
                strcpy(b.bill[36+p],"Maintenance Bill");
                b.duedate[p][0]=5;
                b.duedate[12+p][0]=5;
                b.duedate[24+p][0]=5;
                b.duedate[36+p][0]=5;
                b.duedate[p][2]=y;
                b.duedate[12+p][2]=y;
                b.duedate[24+p][2]=y;
                b.duedate[36+p][2]=y;
            }
    fseek(f,sizeof(struct bill),SEEK_END);
    fwrite(&b,sizeof(struct bill),1,f);
    fclose(f);}
    {strcpy(creation.userid,"12345");
    f=fopen("SocSched.bin","rb+");
    if(!f)
    {
        fclose(f);
        f=fopen("SocSched.bin","wb+");
    }
    fseek(f,sizeof(struct schedule),SEEK_END);
    fwrite(&creation,sizeof(struct schedule),1,f);
    fclose(f);}
}
int t=2;
void login()
{
    FILE *fp;
    char c,name[30],pass[30],passid[6],passname[30]; int z=0;
    int checku,checkp;
    fp=fopen("ran2","rb+");
    printf("\n\n\t\t\t\t------------------------------        \n");
    printf( "                               |                              |\n");
    printf( "                               |   WELCOME TO LOG IN ZONE     | \n");
    printf("                                 ------------------------------     \n " );
    printf("\n\n\t\t\t\t  ENTER USERNAME: ");
    scanf("%s",name);
    printf("\n\n\t\t\t\t  ENTER PASSWORD: ");
    while((c=getch())!=13)
    {if(c==8)
                                      {if(z!=0)
                                      {z--;
                                      printf("\b");
                                      printf(" \b");
                                      }}

       else{ pass[z++]=c;
        printf("%c",'*');}
    }
    pass[z]='\0';
    static int j;
    fseek(fp,0L,0);
    j=0;
    while(!feof(fp))
    {
        fread(&w[j],sizeof(w[j]),1,fp);
        checku=strcmp(name,w[j].name);
        checkp=strcmp(pass,w[j].pass);
        strcpy(passid,w[j].id);
        strcpy(passname,w[j].name);
        j++;
        if(checku==0&&checkp==0)
        {
            t=1;
            printf("\n\n\n\t\t\tYOU HAVE LOGGED IN SUCCESSFULLY!!\n\nPlease wait....");
            delay(3);
            system("cls");
            printf("\t\tWELCOME, HAVE A NICE DAY\n");
            //kal();
            menu(passid);
            break;
        }
    }
    fseek(fp,0L,0);
    while(!feof(fp))
    {
        j=0;
        fread(&w[j],sizeof(w[j]),1,fp);
        checku=strcmp(name,w[j].name);
        checkp=strcmp(pass,w[j].pass);
        j++;
        if(checku==0&&checkp!=0)
        {
            printf("\n\n\n\t\t\tWRONG PASSWORD!! Not %s??",name);
            printf("\n\n\t\t\t\t  (Press 'Y' to re-login)");
            if(getch()=='y'||getch()=='Y')
            {
                login();
            }
        }
    }
    fseek(fp,0L,0);
    j=0;
    if(t!=1)
    {
        while(!feof(fp))
        {
            fread(&w[j],sizeof(w[j]),1,fp);
            checku=strcmp(name,w[j].name);
            checkp=strcmp(pass,w[j].pass);
            j++;
            if(checku!=0)
            {
                //printf("%s",w[j].name);
                //printf("%s",w[j].pass);
                printf("\n\n\n\t\t\tYou are not a Registered User\n \t\t\tPress enter to register yourself");
                if(getch()==13)
                {system ("cls");
                reg();}
                else
                        break;
            }
        }
        getch();
    }
}
int static i=0;
void reg()
{
    i=i+1;
    FILE *fp;
    char c,checker[30];
    int z=0;int k=0;
    time_t t1;
    t1 = time(NULL);
    char time[10],month[10],day[10],year[10],weekd[10],date[15];
    sscanf(ctime(&t1),"%s %s %s %s %s",weekd,month,day,time,year);
    fp=fopen("ran2","ab+");
    printf("\n\n\t\t\t\t------------------------------\n");
    printf( "                               |                              |\n");
    printf( "                               |WELCOME TO REGISTRATION ZONE  | \n");
    printf("                               --------------------------------     \n " );
    strcpy(date,timy());
    printf("\n\n\t\t\t\t  ENTER USERNAME: ");
    scanf("%s",checker);
    strcpy(w[i].year,year);
    strcpy(w[i].date,date);
    strcpy(w[i].time,time);
    strcpy(w[i].weekd,weekd);
    strcpy(w[i].month,month);
    strcpy(w[i].day,day);
    char id9[6];
    strcpy(id9,random());
    fseek(fp,0L,0);
    int q=0,r=2;
    while(!feof(fp))
    {
        fread(&w[q],sizeof(w[q]),1,fp);
        if(strcmp(checker,w[q].name)==0||strcmp(id9,w[q].id)==0)
        {
            system ("cls");
            r=0;
            printf("\n\n\t\t\tUSERNAME ALREADY EXISTS");
            reg();
            break;
        }
        q++;
    }
        if(r!=0)
        {
            strcpy(w[i].id,id9);
            strcpy(w[i].name,checker);
        }
    printf("\n\n\t\t\t\t  DESIRED PASSWORD: ");
    while((c=getch())!=13)
    {
        if(c==8)
                                      {if(z!=0)
                                      {z--;
                                      printf("\b");
                                      printf(" \b");
                                      }}

       else{ w[i].pass[z++]=c;
        printf("%c",'*');}
    }
    fseek(fp,0L,2);
    fwrite(&w[i],sizeof(w[i]),1,fp);
    fclose(fp);
    printf("\n\n\tPress enter if you agree with Username and Password");
    if((c=getch())==13)
    {
        system ("cls");
        loggedin(w[i].id);
        shoplistcreate(w[i].id);
        printf("\n\n\t\tYou have successfully registered\n");
        printf("YOUR USER ID IS: %s\n",w[i].id);
        printf("PLEASE REMEMBER THIS FOR FURTHER USE!");
        printf("\n\n\t\tDo you wish to login into your account??\n\n\t\t  ");
        printf("> PRESS 1 FOR YES\n\n\t\t  > PRESS 2 FOR NO\n\n\t\t\t\t");
        int n;
        scanf("%d",&n);
        switch(n)
        {
            case 1: system ("cls");
                    login();
                    break;
            case 2: system ("cls");
                    printf("\n\n\n\t\t\t\t\tTHANK YOU FOR REGISTERING");
                    delay(2);
                    system("cls");
                    ram();
                    break;
        }
    }
    getch();
}
void ram()
{
    int k;
    time_t t;
    time(&t);
    int s=0;
    char c;
    printf("\nenter 1 for Administrator login \n");
    printf("enter 2 for Registration of members \n");
    printf("enter 3 for Member login\n");
    printf("enter 4 for Grocer login\n");
    printf("enter 5 for exit from program\n\n");
    for(int l=0;l<80;l++)
		printf("-");
	    printf("\nCurrent date and time : %s",ctime(&t));
    scanf("%d",&k);
    printf("\n");
     switch(k)
     {
         case 1:
                  {printf("Admin login section:\n");
                  char username[10]="A1001";
                  char password[10]="asdfgh";
                  char username1[10];
                  char password1[10];
                  bool p=true;
                  if(strcmp(username,username1)!=0||strcmp(password1,password)!=0)
                  {
                        while(p)
                        {   s=0;
                            if(strcmp(username,username1)!=0||strcmp(password1,password)!=0)
                            {

                                printf("\nEnter the username:");
                                scanf("%s",username1);
                                printf("\n");
                                printf("Enter the password:");

                                while((c=getch())!=13)
                                {   if(c==8)
                                      {if(s!=0)
                                      {s--;
                                      printf("\b");
                                      printf(" \b");
                                      }}
                                    else{password1[s++]=c;
                                    printf("*");}
                                }
                                password1[s]='\0';
                                printf("\n\n\n\n\n");
                            }
                            if(strcmp(username,username1)!=0||strcmp(password1,password)!=0)
                            {
                                printf("You have entered wrong password or username \n");
                            }
                            if(strcmp(username,username1)==0&&strcmp(password1,password)==0)
                            {
                                  //kal();
                                  delay(2);
                                  system("cls");
                                  printf("\t\tA warm welcome! You have successfully logged in!\n");
                                  menu(username);
                                  break;
                            }
                        }
                    }
                  break;
                  }
        case 2:
                reg();
                ram();
                break;
        case 3:
                printf("welcome to the login zone");
                login();
                break;
        case 4:
                {
                    printf("Grocer login section:\n");
                    char username[10]="G1001";
                    char password[10]="groc3r";
                    char username1[10];
                    char password1[10];
                    bool p=true;
                    if(strcmp(username,username1)!=0||strcmp(password1,password)!=0)
                    {
                        while(p)
                        {   s=0;
                            if(strcmp(username,username1)!=0||strcmp(password1,password)!=0)
                            {

                                printf("\nEnter the username:");
                                scanf("%s",username1);
                                printf("\n");
                                printf("Enter the password:");

                                while((c=getch())!=13)
                                {   if(c==8)
                                      {if(s!=0)
                                      {s--;
                                      printf("\b");
                                      printf(" \b");
                                      }}
                                    else{password1[s++]=c;
                                    printf("*");}
                                }
                                password1[s]='\0';
                                printf("\n\n\n\n\n");
                            }
                            if(strcmp(username,username1)!=0||strcmp(password1,password)!=0)
                            {
                                printf("You have entered wrong password or username \n");
                            }
                            if(strcmp(username,username1)==0&&strcmp(password1,password)==0)
                            {
                                  //kal();
                                  delay(2);
                                  system("cls");
                                  printf("\t\tA warm welcome! You have successfully logged in!\n");
                                  shoppinglist(username);
                                  break;
                            }
                        }
                    }
                  break;
                }
        case 5:
            system("cls");
            printf("\n*****Thank you.Visit again*****\n");
            for(int l=0;l<80;l++)
		    printf("-");
            delay(2);
            exit(0);
                break;
        default:printf("Invalid input\n");
     }
}
void typemess()
{FILE *f;
    time_t t1;
    t1 = time(NULL);
    char weekd[10],month[10],day[10],time[10],year[10];
    f=fopen("message","ab+");
    if(f==0)
    {
        f=fopen("message","wb+");
    }
    while(1){
        printf("Type the user id you want to send to\n");
        scanf("%s",m1.id);
        fflush(stdin);
        printf("Type your message\n");
        gets(m1.feedback);
        sscanf(ctime(&t1),"%s %s %s %s %s",weekd,month,day,time,year);
           printf("%s %s %s %s %s",weekd,month,day,time,year);
            strcpy(m1.time,time);
            strcpy(m1.weekd,weekd);
            strcpy(m1.month,month);
            strcpy(m1.day,day);
            strcpy(m1.year,year);
            fwrite(&m1,sizeof(m1),1,f);
            printf("\n\nMessage successfully sent \n");
            fflush(stdin);
            getche();
            break;}
        fclose(f);
}
void readmess(char uid[6])
{FILE *fe;
     int l=0;
    if((fe=fopen("message","rb"))!=NULL)
	printf("\n\n\t\t Message from admin\n");
	{for(int k=0;k<=80;k++)
        printf("-");
        printf("\n");
	l++;
	while(fread(&m1,sizeof(m1),1,fe)==1)
	{   if(strcmp(uid,m1.id)==0)
	    {printf("%s",m1.feedback);
		printf("\t%s %s %s %s %s\n",m1.time,m1.weekd,m1.day,m1.month,m1.year);}
	}

	printf("\n");}
	if(l==0)printf("No Messages\n");
    printf("Press any ket to go back\n");
    getch();


	fclose(fe);
}
void display(struct schedule disp,int m,int y)
{
    for(int i=0;i<30;i++)
    {
        if((disp.eventdate[i][1]==m)&&(disp.eventdate[i][2]==y))
        {
            printf("%d/%d/%d-%s\n",disp.eventdate[i][0],disp.eventdate[i][1],disp.eventdate[i][2],disp.eventname[i]);
        }
        else
            continue;
    }
}
void viewsched(char uid[6])
{
    FILE *f,*fp;
    struct schedule view;
    time_t now;
    time(&now);
    struct tm *local=localtime(&now);
    int d,m,y,i,k;
    d=local->tm_mday;
    m=local->tm_mon+1;
    y=local->tm_year+1900;
    printf("                                                       Events\n");
printf("________________________________________________________________________________________________________________________\n");
    if(uid[0]=='#')
    {
        f=fopen("UserSched.bin","rb+");
        fseek(f,sizeof(struct schedule),SEEK_SET);
printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Your events:\n");
printf("------------------------------------------------------------------------------------------------------------------------\n");
        k=0;
        while(!feof(f))
        {
            fread(&view,sizeof(struct schedule),1,f);
            if((strcmp(uid,view.userid)==0)&&(k==0))
            {
                display(view,m,y);
                k++;
            }
        }
        fclose(f);
        f=fopen("payments.bin","rb+");
        fseek(f,sizeof(struct bill),SEEK_SET);
printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Payment events:\n");
printf("------------------------------------------------------------------------------------------------------------------------\n");
        k=0;
        struct bill p;
        while(!feof(f))
        {
            fread(&p,sizeof(struct bill),1,f);
            if((strcmp(uid,p.uid)==0)&&(k==0))
            {
                    for(i=0;i<12;i++)
                    {
                        if(p.duedate[i][2]<=y)
                        {
                            if((p.duedate[i][2]==y)&&(p.duedate[i][1]<=m)&&(p.status[i]==0))
                            {
                                printf("%d/%d/%d- %s\n",p.duedate[i][0],p.duedate[i][1],p.duedate[i][2],p.bill[i]);
                                if(p.duedate[i][0]<d)
                                {
                                    printf("\t\tOverdue!! Note:Interest rates are charged for each day bill is overdue.\n");
                                }
                            }
                            else
                                if((p.status[i]==0)&&(p.duedate[i][2]<y))
                                    {printf("%d/%d/%d- %s\n",p.duedate[i][0],p.duedate[i][1],p.duedate[i][2],p.bill[i]);
                                    printf("\t\tOverdue!! Note:Interest rates are charged for each day bill is overdue.\n");}
                        }
                        if(p.duedate[i+12][2]<=y)
                        {
                            if((p.duedate[i+12][2]==y)&&(p.duedate[i+12][1]<=m)&&(p.status[i+12]==0))
                            {
                                printf("%d/%d/%d- %s\n",p.duedate[i+12][0],p.duedate[i+12][1],p.duedate[i+12][2],p.bill[i+12]);
                                if(p.duedate[i+12][0]<d)
                                {
                                    printf("\t\tOverdue!! Note:Interest rates are charged for each day bill is overdue.\n");
                                }
                            }
                            else
                                if((p.status[i+12]==0)&&(p.duedate[i+12][2]<y))
                                    {printf("%d/%d/%d- %s\n",p.duedate[12+i][0],p.duedate[i+12][1],p.duedate[i+12][2],p.bill[i+12]);
                                    printf("\t\tOverdue!! Note:Interest rates are charged for each day bill is overdue.\n");}
                        }
                        if(p.duedate[i+24][2]<=y)
                        {
                            if((p.duedate[i+24][2]==y)&&(p.duedate[i+24][1]<=m)&&(p.status[i+24]==0))
                            {
                                printf("%d/%d/%d- %s\n",p.duedate[24+i][0],p.duedate[i+24][1],p.duedate[i+24][2],p.bill[i+24]);
                                if(p.duedate[i+24][0]<d)
                                {
                                    printf("\t\tOverdue!! Note:Interest rates are charged for each day bill is overdue.\n");
                                }
                            }
                            else
                                if((p.status[i+24]==0)&&(p.duedate[i+24][2]<y))
                                    {printf("%d/%d/%d- %s\n",p.duedate[24+i][0],p.duedate[i+24][1],p.duedate[i+24][2],p.bill[i+24]);
                                    printf("\t\tOverdue!! Note:Interest rates are charged for each day bill is overdue.\n");}
                        }
                        if(p.duedate[i+36][2]<=y)
                        {
                            if((p.duedate[i+36][2]==y)&&(p.duedate[i+36][1]<=m)&&(p.status[i+36]==0))
                            {
                                printf("%d/%d/%d- %s\n",p.duedate[i+36][0],p.duedate[i+36][1],p.duedate[i+36][2],p.bill[i+36]);
                                if(p.duedate[i+36][0]<d)
                                {
                                    printf("\t\tOverdue!! Note:Interest rates are charged for each day bill is overdue.\n");
                                }
                            }
                            else
                                if((p.status[i+36]==0)&&(p.duedate[i+36][2]<y))
                                    {printf("%d/%d/%d- %s\n",p.duedate[i+36][0],p.duedate[i+36][1],p.duedate[i+36][2],p.bill[i+36]);
                                    printf("\t\tOverdue!! Note:Interest rates are charged for each day bill is overdue.\n");}
                        }
                    }
                    k++;
            }
        }
        fclose(f);
        f=fopen("SocSched.bin","rb+");
        fseek(f,sizeof(struct schedule),SEEK_SET);
printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("Society events:\n");
printf("------------------------------------------------------------------------------------------------------------------------\n");
        k=0;
        while(!feof(f))
        {
            fread(&view,sizeof(struct schedule),1,f);
            for(i=0;i<30;i++)
            {
                if((view.eventdate[i][2]==y)&&(k==0))
                {
                    printf("%d/%d/%d-%s\n",view.eventdate[i][0],view.eventdate[i][1],view.eventdate[i][2],view.eventname);
                }
            }
            k++;
        }
printf("------------------------------------------------------------------------------------------------------------------------\n");
        fclose(f);
    }
    else if(uid[0]=='A')
    {
        f=fopen("SocSched.bin","rb+");
        fseek(f,sizeof(struct schedule),SEEK_SET);
printf("-----------------------------------------------------------------------------------------------------------------------\n");
    printf("Society events:\n");
printf("------------------------------------------------------------------------------------------------------------------------\n");
        k=0;
        while(!feof(f))
        {
            fread(&view,sizeof(struct schedule),1,f);
            for(i=0;i<30;i++)
            {
                if((view.eventdate[i][2]==y)&&(k==0))
                {
                    printf("%d/%d/%d-%s\n",view.eventdate[i][0],view.eventdate[i][1],view.eventdate[i][2],view.eventname);
                }
            }
            k++;
        }
printf("------------------------------------------------------------------------------------------------------------------------\n");
        fclose(f);
    }
    else
    {
        printf("No record exists for your user id");
        fclose(f);
    }
}
void addsched(char uid[6])
{
    FILE *f;
    struct schedule add;
    int i=0;
    char ch;
    if(uid[0]=='#')
    {
        f=fopen("UserSched.bin","rb+");
        fseek(f,sizeof(struct schedule),SEEK_SET);
        while(!feof(f))
        {
            fread(&add,sizeof(struct schedule),1,f);
            if(strcmp(uid,add.userid)==0)
            {
                for(i=0;i<30;i++)
                {
                    if(add.eventdate[i][0]!=0)
                        continue;
                    else
                    {
                        z:
                        printf("enter date of event(dd/mm/yyyy):");
                        scanf("%d/%d/%d",&add.eventdate[i][0],&add.eventdate[i][1],&add.eventdate[i][2]);
                        fflush(stdin);
                        printf("enter name of the event:");
                        gets(add.eventname[i]);
                        printf("enter 'y' to confirm event\n");
                        ch=getch();
                        if(ch=='y'||ch=='Y')
                        {
                            fseek(f,  - (long)sizeof(struct schedule), 1);
                            fwrite(&add,sizeof(struct schedule),1,f);
                            printf("Event successfully added to schedule\n");
                            goto u;
                        }
                        else
                            goto z;
                    }
                }
            }
        }
        u:
        fclose(f);
    }
    else if(uid[0]=='A')
    {
        f=fopen("SocSched.bin","rb+");
        fseek(f,sizeof(struct schedule),SEEK_SET);
        while(!feof(f))
        {
            fread(&add,sizeof(struct schedule),1,f);
            for(i=0;i<30;i++)
            {
                if(add.eventdate[i][0]!=0)
                    continue;
                else
                {
                    y:
                    printf("enter date of event(dd/mm/yyyy):");
                    scanf("%d/%d/%d",&add.eventdate[i][0],&add.eventdate[i][1],&add.eventdate[i][2]);
                    fflush(stdin);
                    printf("enter name of the event:");
                    gets(add.eventname[i]);
                    printf("enter 'y' to confirm event\n");
                    ch=getch();
                    if(ch=='y'||ch=='Y')
                    {
                        fseek(f,  - (long)sizeof(struct schedule), 1);
                        fwrite(&add,sizeof(struct schedule),1,f);
                        printf("Event successfully added to schedule\n");
                        goto w;
                    }
                    else
                        goto y;
                }
            }
        }
        w:
        fclose(f);
    }
    else
    {
        printf("Couldn't add event for user id\n");
        fclose(f);
    }
}
void delsched(char uid[6])
{
    FILE *f;
    struct schedule del;
    int dd,dm,dy,i;
    char ch;
    if(uid[0]=='#')
    {
        f=fopen("UserSched.bin","rb+");
        fseek(f,sizeof(struct schedule),SEEK_SET);
        while(!feof(f))
        {
            fread(&del,sizeof(struct schedule),1,f);
            if(strcmp(uid,del.userid)==0)
            {
                uedel:
                printf("enter date of user event you want to delete(dd/mm/yyyy):\t");
                scanf("%d/%d/%d",&dd,&dm,&dy);
                for(i=0;i<30;i++)
                {
                    if((del.eventdate[i][0]==dd)&&(del.eventdate[i][1]==dm)&&(del.eventdate[i][2]==dy))
                    {
                        printf("Are you sure you want to delete?Yes(y)/No(n). To change the date press any other key\n");
                        ch=getch();
                        if(ch=='y'||ch=='Y')
                        {
                            del.eventdate[i][0]=0;
                            del.eventdate[i][1]=0;
                            del.eventdate[i][2]=0;
                            del.eventname[i][0]='\0';
                            fseek(f,  - (long)sizeof(struct schedule), 1);
                            fwrite(&del,sizeof(struct schedule),1,f);
                            printf("delete successful\n");
                            goto v;
                        }
                        else if(ch=='n'||ch=='N')
                        {
                            break;
                        }
                        else
                        {
                            goto uedel;
                        }
                    }
                }
            }
        }
        v:
        fclose(f);
    }
    else if(uid[0]=='A')
    {
        f=fopen("SocSched.bin","rb+");
        fseek(f,sizeof(struct schedule),SEEK_SET);
        sedel:
        printf("enter date of user event you want to delete(dd/mm/yyyy):\t");
        scanf("%d/%d/%d",&dd,&dm,&dy);
        while(!feof(f))
        {
            fread(&del,sizeof(struct schedule),1,f);
                for(i=0;i<30;i++)
                {
                    if((del.eventdate[i][0]==dd)&&(del.eventdate[i][1]==dm)&&(del.eventdate[i][2]==dy))
                    {
                        printf("Are you sure you want to delete?Yes(y)/No(n). To change the date press any other key\n");
                        ch=getch();
                        if(ch=='y'||ch=='Y')
                        {
                            del.eventdate[i][0]=0;
                            del.eventdate[i][1]=0;
                            del.eventdate[i][2]=0;
                            del.eventname[i][0]='\0';
                            fseek(f,  - (long)sizeof(struct schedule), 1);
                            fwrite(&del,sizeof(struct schedule),1,f);
                            printf("delete successful\n");
                            break;
                        }
                        else if(ch=='n'||ch=='N')
                        {
                            break;
                        }
                        else
                        {
                            goto sedel;
                        }
                    }
                }
        }
        fclose(f);
    }
    else
    {
        printf("No record found for your user id\n");
    }
}
void schedulemanager(char uid[6])
{
    time_t t=time(&t);
    int choice;
    do
    {
        printf("Schedule manager\n");
        for(int l=0;l<80;l++)
		printf("-");
    printf("\nTo view schedule enter 1\n");
    if(uid[0]=='#')
        printf("To add an event enter 2\n");
    else
        printf("To add a society event enter 2\n");
    printf("To delete an event enter 3\n");
    printf("To exit enter 4\n");
    for(int l=0;l<80;l++)
		printf("-");
	    printf("\nCurrent date and time : %s",ctime(&t));
    scanf("%d",&choice);
    char ch;
    switch(choice)
    {
        case 1: printf("Loading events...\n");
                delay(2);
                system("cls");
                viewsched(uid);
                delay(2);
                printf("press any key to return to menu\n");
                ch=getch();
                system("cls");
                break;
        case 2: printf("________________________________________________________________________________________________________________________\n");
                addsched(uid);
                delay(1);
                system("cls");
                break;
        case 3: printf("________________________________________________________________________________________________________________________\n");
                delsched(uid);
                delay(1);
                system("cls");
                break;
        case 4: delay(1);
                system("cls");
                menu(uid);
                break;
        default: printf("invalid input\n");
    }
    }while(choice!=4);
}
void electricity(char uid[6])
{
    struct bill ecity;
    int choice,i,mc;
    char ch, billname[100];
    time_t now;
    time(&now);
    struct tm *local=localtime(&now);
    int d,m,y,k,duedate[3];
    d=local->tm_mday;
    m=local->tm_mon+1;
    y=local->tm_year+1900;
    FILE *f;
    f=fopen("payments.bin","rb+");
    fseek(f,sizeof(struct bill),SEEK_SET);
    k=0;
    while(!feof(f))
    {
        fread(&ecity,sizeof(struct bill),1,f);
        if((strcmp(uid,ecity.uid)==0)&&(k==0))
        {
            k++;
            break;
        }
    }
    printf("To update status of payment enter 1\n");
    scanf("%d",&choice);
    strcpy(billname,"Electricity Bill");
    if(choice==1)
    {
        for(i=0;i<12;i++)
        {
            if((i<m)&&(ecity.duedate[i][2]==y))
            {
                printf("Bill month: %d\t",(i+1));
                printf("Status: ");
                if(ecity.status[i]==1)
                    printf("paid\n");
                else
                    printf("payment due\n");
            }
        }
        z:
                printf("Enter month no. for which you want to change status: ");
                scanf("%d",&mc);
                if(mc>=1&&mc<=m)
                {
                    if(ecity.status[mc-1]==1)
                        ecity.status[mc-1]=0;
                    else
                        ecity.status[mc-1]=1;
                }
                else
                {
                    printf("invalid entry\n");
                    goto z;
                }
        fseek(f,-(long)sizeof(struct bill),1);
        fwrite(&ecity,sizeof(struct bill),1,f);
    }
    fclose(f);
}
void water(char uid[6])
{
    struct bill aqua;
    int choice,i,mc;
    char ch, billname[100];
    time_t now;
    time(&now);
    struct tm *local=localtime(&now);
    int d,m,y,k,duedate[3];
    d=local->tm_mday;
    m=local->tm_mon+1;
    y=local->tm_year+1900;
    FILE *f;
    f=fopen("payments.bin","rb+");
    fseek(f,sizeof(struct bill),SEEK_SET);
    k=0;
    while(!feof(f))
    {
        fread(&aqua,sizeof(struct bill),1,f);
        if((strcmp(uid,aqua.uid)==0)&&(k==0))
        {
            k++;
            break;
        }
    }
    printf("To update status of payment enter 1\n");
    scanf("%d",&choice);
    strcpy(billname,"Water Bill");
    if(choice==1)
    {
        for(i=0;i<12;i++)
        {
            if((i<m)&&(aqua.duedate[i+12][2]==y))
            {
                printf("Bill month: %d\t",(i+1));
                printf("Status: ");
                if(aqua.status[i+12]==1)
                    printf("paid\n");
                else
                    printf("payment due\n");
            }
        }
        z:
                printf("Enter month no. for which you want to change status: ");
                scanf("%d",&mc);
                if(mc>=1&&mc<=m)
                {
                    if(aqua.status[(mc-1)+12]==1)
                        aqua.status[(mc-1)+12]=0;
                    else
                        aqua.status[(mc-1)+12]=1;
                }
                else
                {
                    printf("invalid entry\n");
                    goto z;
                }
        fseek(f,-(long)sizeof(struct bill),1);
        fwrite(&aqua,sizeof(struct bill),1,f);
    }
    fclose(f);
}
void cable(char uid[6])
{
    struct bill dth;
    int choice,i,mc;
    char ch, billname[100];
    time_t now;
    time(&now);
    struct tm *local=localtime(&now);
    int d,m,y,k,duedate[3];
    d=local->tm_mday;
    m=local->tm_mon+1;
    y=local->tm_year+1900;
    FILE *f;
    f=fopen("payments.bin","rb+");
    fseek(f,sizeof(struct bill),SEEK_SET);
    k=0;
    while(!feof(f))
    {
        fread(&dth,sizeof(struct bill),1,f);
        if((strcmp(uid,dth.uid)==0)&&(k==0))
        {
            k++;
            break;
        }
    }
    printf("To update status of payment enter 1\n");
    scanf("%d",&choice);
    strcpy(billname,"Digital Cable Bill");
    if(choice==1)
    {
        for(i=0;i<12;i++)
        {
            if((i<m)&&(dth.duedate[i+24][2]==y))
            {
                printf("Bill month: %d\t",(i+1));
                printf("Status: ");
                if(dth.status[i+24]==1)
                    printf("paid\n");
                else
                    printf("payment due\n");
            }
        }
        z:
                printf("Enter month no. for which you want to change status: ");
                scanf("%d",&mc);
                if(mc>=1&&mc<=m)
                {
                    if(dth.status[(mc-1)+24]==1)
                        dth.status[(mc-1)+24]=0;
                    else
                        dth.status[(mc-1)+24]=1;
                }
                else
                {
                    printf("invalid entry\n");
                    goto z;
                }
        fseek(f,-(long)sizeof(struct bill),1);
        fwrite(&dth,sizeof(struct bill),1,f);
    }
    fclose(f);
}
void maintenance(char uid[6])
{
    struct bill mt;
    int choice,i,mc;
    char ch, billname[100];
    time_t now;
    time(&now);
    struct tm *local=localtime(&now);
    int d,m,y,k,duedate[3];
    d=local->tm_mday;
    m=local->tm_mon+1;
    y=local->tm_year+1900;
    FILE *f;
    f=fopen("payments.bin","rb+");
    fseek(f,sizeof(struct bill),SEEK_SET);
    k=0;
    while(!feof(f))
    {
        fread(&mt,sizeof(struct bill),1,f);
        if((strcmp(uid,mt.uid)==0)&&(k==0))
        {
            k++;
            break;
        }
    }
    printf("To update status of payment enter 1\n");
    scanf("%d",&choice);
    strcpy(billname,"Maintenance Bill");
    if(choice==1)
    {
        for(i=0;i<12;i++)
        {
            if((i<m)&&(mt.duedate[i+36][2]==y))
            {
                printf("Bill month: %d\t",(i+1));
                printf("Status: ");
                if(mt.status[36+i]==1)
                    printf("paid\n");
                else
                    printf("payment due\n");
            }
        }
        z:
                printf("Enter month no. for which you want to change status: ");
                scanf("%d",&mc);
                if(mc>=1&&mc<=m)
                {
                    if(mt.status[(mc-1)+36]==1)
                        mt.status[(mc-1)+36]=0;
                    else
                        mt.status[(mc-1)+36]=1;
                }
                else
                {
                    printf("invalid entry\n");
                    goto z;
                }
        fseek(f,-(long)sizeof(struct bill),1);
        fwrite(&mt,sizeof(struct bill),1,f);
    }
    fclose(f);
}
void billtracker(char uid[6])
{   if(uid[0]=='#'){
    time_t t=time(&t);
    int duedate[3];
    char billname[100];
    int choice,inchoice;
    do
    {
        printf("Bill Tracker\n");
        for(int l=0;l<80;l++)
		printf("-");
        printf("\nSelect bill type\n");
        printf("enter 1 for electricity\n");
        printf("enter 2 for water\n");
        printf("enter 3 for cable/DTH\n");
        printf("enter 4 for maintenance\n");
        printf("enter 5 to exit\n");
        for(int l=0;l<80;l++)
		printf("-");
	    printf("\nCurrent date and time : %s",ctime(&t));
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: electricity(uid);
                    delay(5);
                    system("cls");
                    break;
            case 2: water(uid);
                    delay(5);
                    system("cls");
                    break;
            case 3: cable(uid);
                    delay(5);
                    system("cls");
                    break;
            case 4: maintenance(uid);
                    delay(5);
                    system("cls");
                    break;
            case 5: delay(1);
                    system("cls");
                    menu(uid);
                    break;
            default:printf("invalid choice\n");
        }
    }while(choice!=5);}
    else
    {
        printf("you are not authorized to use this facility\n");
        delay(2);
        system("cls");
        menu(uid);
    }
}
void billfile(char uid[6])
{
    FILE *fp;
    fp=fopen("payments.bin","rb+");
    struct schedule a;
    struct bill b;
    time_t now;
    time(&now);
    struct tm *local=localtime(&now);
    int d,m,y;
    d=local->tm_mday;
    m=local->tm_mon+1;
    y=local->tm_year+1900;
    int i,k=0;
    fseek(fp,sizeof(struct bill),SEEK_SET);
    k=0;
    while((!feof(fp))&&(k==0))
    {
        fread(&b,sizeof(struct bill),1,fp);
        if((strcmp(uid,b.uid)==0))
        {
             for(i=0;i<12;i++)
            {
                if(b.status[i]==1)
                {
                    b.status[i]=0;
                    b.duedate[i][2]+=1;
                }
                if(b.status[12+i]==1)
                {
                    b.status[12+i]=0;
                    b.duedate[12+i][2]+=1;
                }
                if(b.status[24+i]==1)
                {
                    b.status[24+i]=0;
                    b.duedate[24+i][2]+=1;
                }
                if(b.status[36+i]==1)
                {
                    b.status[i+36]=0;
                    b.duedate[36+i][2]+=1;
                }
            }
            k++;
            fseek(fp,  - (long)sizeof(struct bill), 1);
            fwrite(&b,sizeof(struct bill),1,fp);
        }
    }
    fclose(fp);
}
 int k=8;
 int l=0;
 void waste(char uid[6])
 {
     FILE *f;
    time_t t1;
    t1 = time(NULL);
    char weekd[10],month[10],day[10],time[10],year[10];

    printf("\t\tEnter your complaint \n\n\n");
    f=fopen("waste","ab+");
    if(f==0)
    {
        f=fopen("waste","wb+");
    }
while(1){
        strcpy(c1.id,uid);
        for(int l=0;l<80;l++)
		printf("-");
        fflush(stdin);
        printf("\nEnter the complaint: \n");
        gets(c1.complaint);
        for(int l=0;l<80;l++)
		printf("-");
        fflush(stdin);
        sscanf(ctime(&t1),"%s %s %s %s %s",weekd,month,day,time,year);
       printf("\n%s %s %s %s %s",weekd,month,day,time,year);
        strcpy(c1.time,time);
        strcpy(c1.weekd,weekd);
        strcpy(c1.month,month);
        strcpy(c1.day,day);
        strcpy(c1.year,year);
        fwrite(&c1,sizeof(c1),1,f);
        printf("\n\nComplaint successfully registered \n");
        printf("Press any key to go back");
        fflush(stdin);
        getche();
        break;}
    fclose(f);
 }
 void link(char uid[6])
 {
    FILE *fp;
    char name[20];
    int check;
    char date[10],time1[10],month[10],day[10],year[10],weekd[10];
    fp=fopen("ran2","rb+");
    fseek(fp,0L,0);
    while(!feof(fp))
    {
        fread(&w[l],sizeof(w[l]),1,fp);
        check=strcmp(w[l].id,uid) ;
        if ((check==0)||(uid[0]=='A'))
        {
            if(uid[0]!='A')
                printf("Hi  %s . Your user ID is %s ",w[l].name,w[l].id);
            int h;
            do{
              kai:
              printf("\n\t\t\t>Enter 1 for writing  complaint .");
              printf("\n\t\t\t>Enter 2 for attendance");
              printf("\n\t\t\t>Enter 3 for viewing your attendance for correct disposal of waste");
              printf("\n\t\t\t>Enter 4 to exit\n");
            printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("This is the workspace everything has to be written here:\n");
            scanf("%d",&h);
            system("cls");
            switch(h)
            {
                case 1: if(uid[0]=='#')
                        {
                            waste(uid);
                            goto kai;
                        }
                        else
                        {
                            printf("You cannot enter a complaint\n");
                            goto kai;
                        }
                        break;
                case 2: {system("cls");
                        printf("\nYou have entered the attendance zone\n");
                        FILE *fp2;
                        char at[5];
                        fp2=fopen("ran4","ab+");
                        printf("Enter Y if cleaning is done.\n");
                        printf("Enter N if cleaning is not done\n");
                        scanf("%s",at);
                        strcpy(w[l].attendance,at);
                        fwrite(&(w[l]),sizeof(w[l]),1,fp2);
                        printf("\nYour attendance has been successfully registered\n");
                        fclose(fp2);
                        goto kai;
                        break;}
                case 3: {system("cls");
                        FILE *f4;
                        if((f4=fopen("ran4","rb+"))!=NULL)
                        {
                            fseek(f4,0L,0);
                            fread(&w[l],sizeof(w[l]),1,f4);
                            printf("Todays date:%s  \n",w[l].date);
                            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                            fseek(f4,0L,0);
                            while(!feof(f4))
                            {
                                fread(&w[l],sizeof(w[l]),1,f4);
                                if(feof(f4))
                                {
                                    break;
                                }
                                printf("\n User-id %s has given %s at %s\n ",w[l].id,w[l].attendance,w[l].time);
                                printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                            }
                        }
                        break;}
                case 4: menu(uid);
                        break;
                default: printf("Invalid input\n");
                         goto kai;
            }
            }while(h!=7);
        }
        l++;
    }
 }
 void viewfeed(char userid[6])
{    if(userid[0]=='A')
    {FILE *fe;
     int l=0;
    if((fe=fopen("feedback","rb"))!=NULL)
    {for(int k=0;k<=80;k++)
    printf("-");
	printf("\n\n\t\t User Feedbacks are shown below:\n");
	l++;
	while(fread(&f1,sizeof(f1),1,fe)==1)
	{   printf("\n%s ",f1.id);
	    printf("\t%s",f1.feedback);
		printf("\t%s %s %s %s %s",f1.time,f1.weekd,f1.day,f1.month,f1.year);
	}

	printf("\n");}
	if(l==0)printf("No Feedback\n");



	fclose(fe);}


}
 void burglary(char uid[6])
{   FILE *f;
    time_t t1;
    t1 = time(NULL);
    char weekd[10],month[10],day[10],time[10],year[10];

    printf("\t\tEnter your complaint \n\n\n");
    f=fopen("burglary","ab+");
    if(f==0)
    {
        f=fopen("burglary","wb+");
    }
while(1){
        strcpy(c1.id,uid);
        for(int l=0;l<80;l++)
		printf("-");
        fflush(stdin);
        printf("\nEnter the complaint: \n");
        gets(c1.complaint);
        for(int l=0;l<80;l++)
		printf("-");
        fflush(stdin);
        sscanf(ctime(&t1),"%s %s %s %s %s",weekd,month,day,time,year);
       printf("\n%s %s %s %s %s",weekd,month,day,time,year);
        strcpy(c1.time,time);
        strcpy(c1.weekd,weekd);
        strcpy(c1.month,month);
        strcpy(c1.day,day);
        strcpy(c1.year,year);
        fwrite(&c1,sizeof(c1),1,f);
        printf("\n\nComplaint successfully registered \n");
        printf("Press any key to go back");
        fflush(stdin);
        getche();
        break;}
    fclose(f);

}
void rescomp(char uid[6])
{
  FILE *f;
    time_t t2;
    t2 = time(NULL);
    char weekd[10],month[10],day[10],time[10],year[10];
    printf("\t\tEnter your complaint \n\n\n");
    f=fopen("rescomp","ab+");
    if(f==0)
    {
        f=fopen("rescomp","wb+");
    }
    while(1)
    {
        strcpy(c2.id,uid);
        for(int l=0;l<80;l++)
		printf("-");
        fflush(stdin);
        printf("\nEnter the complaint: \n");
        gets(c2.complaint);
        for(int l=0;l<80;l++)
		printf("-");
        fflush(stdin);
        sscanf(ctime(&t2),"%s %s %s %s %s",weekd,month,day,time,year);
        printf("\n%s %s %s %s %s",weekd,month,day,time,year);
        strcpy(c2.time,time);
        strcpy(c2.weekd,weekd);
        strcpy(c2.month,month);
        strcpy(c2.day,day);
        strcpy(c2.year,year);
        fwrite(&c2,sizeof(c2),1,f);
        printf("\n\nComplaint successfully registered \n");
        printf("Press any key to go back");
        fflush(stdin);
        getche();
        break;}
    fclose(f);

}
void maintain(char uid[6])
{
    FILE *f;
    time_t t3;
    t3 = time(NULL);
    char weekd[10],month[10],day[10],time[10],year[10];
    printf("\t\tEnter your complaint \n\n\n");
    f=fopen("maintenance","ab+");
    if(f==0)
    {
        f=fopen("maintenance","wb+");
    }
    while(1)
    {
        strcpy(c3.id,uid);
        for(int l=0;l<80;l++)
		printf("-");
        fflush(stdin);
        printf("\nEnter the complaint: \n");
        gets(c3.complaint);
        for(int l=0;l<80;l++)
		printf("-");
        fflush(stdin);
        sscanf(ctime(&t3),"%s %s %s %s %s",weekd,month,day,time,year);
        printf("\n%s %s %s %s %s",weekd,month,day,time,year);
        strcpy(c3.time,time);
        strcpy(c3.weekd,weekd);
        strcpy(c3.month,month);
        strcpy(c3.day,day);
        strcpy(c3.year,year);
        fwrite(&c3,sizeof(c3),1,f);
        printf("\n\nComplaint successfully registered \n");
        printf("Press any key to go back");
        fflush(stdin);
        getche();
        break;}
    fclose(f);

}
void feedback(char uid[6])
{
    FILE *f;
    time_t t4;
    t4 = time(NULL);
    char weekd[10],month[10],day[10],time[10],year[10];
    printf("\t\tFEEDBACK \n\n\n");
    f=fopen("feedback","ab+");
    if(f==0)
    {
        f=fopen("feedback","wb+");
    }
    while(1)
    {
        strcpy(f1.id,uid);
        for(int l=0;l<80;l++)
		printf("-");
        fflush(stdin);
        printf("\nEnter your feedback: \n");
        gets(f1.feedback);
        for(int l=0;l<80;l++)
		printf("-");
        fflush(stdin);
        sscanf(ctime(&t4),"%s %s %s %s %s",weekd,month,day,time,year);
        printf("\n%s %s %s %s %s",weekd,month,day,time,year);
        strcpy(f1.time,time);
        strcpy(f1.weekd,weekd);
        strcpy(f1.month,month);
        strcpy(f1.day,day);
        strcpy(f1.year,year);
        fwrite(&f1,sizeof(f1),1,f);
        printf("\n\nFeedback successfully send \n");
        printf("Press any key to go back");
        fflush(stdin);
        getche();
        break;
        }
    fclose(f);

}
 void viewcomp(char userid[6])
{
    char ch;
 if(userid[0]=='A')
 {
  FILE *f1,*f2,*f3,*f4;
	int l=0;
	system("cls");
	printf("\t\t User Complaints are shown below:\n\n");


    if((f1=fopen("burglary","rb"))!=NULL)
		{   l++;

	while(fread(&c1,sizeof(c1),1,f1)==1)
	{   int day,year,hour,min;
	    printf("\n%s ",c1.id);
	    printf("\t%s",c1.complaint);
		printf("\t%s %s %s %s %s",c1.time,c1.weekd,c1.day,c1.month,c1.year);
		printf("\tBurglary and other crime related issues\n");
	}
	printf("\n\n");
	}
	if((f2=fopen("rescomp","rb"))!=NULL)
    {l++;

	while(fread(&c2,sizeof(c2),1,f2)==1)
	{   printf("\n%s ",c2.id);
	    printf("\t%s",c2.complaint);
		printf("\t%s %s %s %s %s",c2.time,c2.weekd,c2.day,c2.month,c2.year);
		printf("\tIssues with other residents\n");
	}
	printf("\n");}
	if((f3=fopen("maintenance","rb"))!=NULL)
	{   l++;

	while(fread(&c3,sizeof(c3),1,f3)==1)
	{   printf("\n%s",c3.id);
	    printf("\t%s",c3.complaint);
		printf("\t%s %s %s %s %s",c2.time,c2.weekd,c2.day,c2.month,c2.year);
		printf("\tMaintenance Issues \n");
	}
	}
	if((f4=fopen("waste","rb"))!=NULL)
	{   l++;

	while(fread(&c3,sizeof(c3),1,f4)==1)
	{   printf("\n%s",c3.id);
	    printf("\t%s",c3.complaint);
		printf("\t%s %s %s %s %s",c3.time,c3.weekd,c3.day,c3.month,c3.year);
		printf("\tIssues with waste management\n");
	}
	}
	if(l==0) {printf("No Complaints to show\n");}
    printf("If you want to send a message enter 'y'\n");
    ch=getch();
    if(ch=='Y'||ch=='y')
    {
        typemess();
    }
	viewfeed(userid);

	printf("Press any key to go back");
	getch();
	system("cls");
	menu(userid);


	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);}
	else if(userid[0]=='#')
         {
             char choice;
int l;
time_t t;
time(&t);

while (1)
	{
		system("cls");

		printf("\n");
		printf("Complaints and Feedback \n");
		for(l=0;l<80;l++)
		printf("-");
		printf("\n");
		printf("\n\n");
		printf(" \n Enter 1 -> Burglary and other crime related issues");
		printf("\n----------------------------------");
		printf(" \n Enter 2 -> Issues with other residents");
		printf("\n----------------------------------");
		printf(" \n Enter 3 -> Issues with maintenance/services");
		printf("\n-----------------------------------");
		printf(" \n Enter 4 -> To view message from Administrator");
		printf("\n-----------------------------------");
		printf(" \n Enter 5 -> To give feedback");
		printf("\n-----------------------------------");
		printf(" \n Enter 6 -> Exit");
		printf("\n-----------------");
		printf("\n");
		for(l=0;l<80;l++)
		printf("-");
	    printf("\nCurrent date and time : %s",ctime(&t));
        choice=getche();
		choice=toupper(choice);
		switch(choice)           // SWITCH STATEMENT
		{
			case '1':
			    system("cls");
				burglary(userid);
				break;
			case '2':
			    system("cls");
			    rescomp(userid);
				;break;
			case '3':
			    system("cls");
			    maintain(userid);
				break;
            case '4':
                    system("cls");
                    readmess(userid);
                    break;
			case '5':
			    system("cls");
                feedback(userid);
				break;
			case '6':
				system("cls");
				menu(userid);
				exit(0);
				break;
			default:
				system("cls");
				printf("Incorrect Input");
				printf("\n Press any key to continue");
				getch();
		}


         }
}
}
void viewlist(char uid[6])
{
    system("cls");
    printf("Your list:\n");
    printf("----------\n\n");
    FILE *f;
    struct shopping view;
    int c=0,fn=0,x,q;
    char ch,item[100];
    f=fopen("ShoppingList.bin","rb+");
    fseek(f,sizeof(struct shopping),SEEK_SET);
    while(!feof(f))
    {
        fread(&view,sizeof(struct shopping),1,f);
        if((strcmp(uid,view.id)==0)&&(fn==0))
        {
            for(x=0;x<100;x++)
            {
                if(view.qty[x]!=0)
                {
                    printf("%s\t\t%d\n",view.items[x],view.qty[x]);
                    c++;
                }
            }
            fn++;
            break;
        }
    }
    if(c==0)
    {
        printf("Your list is empty\n");
    }
    if((view.order!=0)&&(view.delivery==0))
    {
        printf("Your order has been placed and the items will be delivered soon.\n");
        printf("Please do not create a new list until your order has been delivered.\n");
        printf("press any key to return to Shopping list menu\n");
        getch();
        shoppinglist(uid);
    }
    else if((view.order!=0)&&(view.delivery!=0))
    {
        printf("Your order has been delivered. Please create a fresh list\n");
        printf("press any key to return to Shopping list menu\n");
        getch();
        shoppinglist(uid);
    }
    else
    {
        m:
        printf("To add an item enter (A)\nTo place your order enter (B)\nTo delete an item enter (D)\nTo exit view enter (E)\n");
        ch=getch();
        if(ch=='A'||ch=='a')
        {
            fflush(stdin);
            printf("Enter the name of the item:\t");
            gets(item);
            printf("Enter the quantity:\t");
            scanf("%d",&q);
            printf("Enter 'y' to confirm item and quantity\n");
            ch=getch();
            if(ch=='Y'||ch=='y')
            {
                for(x=0;x<100;x++)
                {
                    if(view.qty[x]==0)
                    {
                        strcpy(view.items[x],item);
                        view.qty[x]=q;
                        break;
                    }
                    else
                    {
                        if(x==99){
                        printf("Your list is full!\n");
                        printf("press any key to return to Shopping list menu\n\n");
                        getch();}
                    }
                }
            }
            goto m;
        }
        else if(ch=='B'||ch=='b')
        {
            view.order=1;
            printf("Your order has been placed and the items will be delivered soon.\n");
            printf("Please do not create a new list until your order has been delivered.\n");
            printf("press any key to return to Shopping list menu\n\n\n");
            getch();
            shoppinglist(uid);
            goto m;
        }
        else if(ch=='E'||ch=='e')
        {
            goto end;
        }
        else if(ch=='D'||ch=='d')
        {
            fflush(stdin);
            printf("enter the name of the item you want to delete:\t");
            gets(item);
            for(x=0;x<100;x++)
            {
                if(strcmp(item,view.items[x])==0)
                {
                    view.qty[x]=0;
                }
            }
        }
        else
        {
            printf("Invalid input\n\n");
            goto m;
        }
    }
    end:
    fseek(f,  - (long)sizeof(struct shopping), 1);
    fwrite(&view,sizeof(struct shopping),1,f);
    fclose(f);
}
void freshlist(char uid[6])
{
    int x,fn=0,q;
    char item[100],ch;
    struct shopping fl;
    FILE *f;
    f=fopen("ShoppingList.bin","rb+");
    while(!feof(f))
    {
        fread(&fl,sizeof(struct shopping),1,f);
        if((strcmp(uid,fl.id)==0)&&(fn==0))
        {
            fl.order=0;
            fl.delivery=0;
            for(x=0;x<100;x++)
            {
                fl.qty[x]=0;
                fl.items[x][0]='\0';
            }
            another:
                fflush(stdin);
            printf("Enter the name of the item:\t");
            gets(item);
            printf("Enter the quantity:\t");
            scanf("%d",&q);
            printf("Enter 'y' to confirm item and quantity\n");
            ch=getch();
            if(ch=='Y'||ch=='y')
            {
                for(x=0;x<100;x++)
                {
                    if(fl.qty[x]==0)
                    {
                        strcpy(fl.items[x],item);
                        fl.qty[x]=q;
                        break;
                    }
                }
            }
            printf("if you want to add another item enter (I)\n");
            ch=getch();
            if(ch=='I'||ch=='i')
            {
                goto another;
            }
            else
            {
                printf("You can view and edit your new list in the future in view mode\n");
                printf("press any key to return to Shopping list menu\n");
                getch();
                goto endfl;
            }
        }
    }
    endfl:
    fseek(f,  - (long)sizeof(struct shopping), 1);
    fwrite(&fl,sizeof(struct shopping),1,f);
    fclose(f);
}
void grocerlistview()
{
    FILE *f;
    struct shopping g;
    int c=0,x,hn,h=0;
    char ch;
    f=fopen("ShoppingList.bin","rb+");
    printf("Pending orders:\n");
    printf("----------------\n");
    while(!feof(f))
    {
        fread(&g,sizeof(struct shopping),1,f);
        if((g.order==1)&&(g.delivery==0))
        {
            if(g.houseno!=h)
            {
                printf("House no.:\t%d\n",g.houseno);
                for(x=0;x<100;x++)
                {
                    h=g.houseno;
                    if(g.qty[x]!=0)
                        printf("item:%s\tquantity:%d\n",g.items[x],g.qty[x]);
                }
                c++;
        printf("---------------------------------------------------------------------------------\n");
            }
        }
    }
    if(c==0)
    {
        printf("No pending orders!\n");
        printf("Press any key to logout\n");
        for(int l=0;l<80;l++)
            printf("-");
        printf("\n");
        ch=getch();
        system("cls");
        ram();
    }
    else
    {
        printf("If an order has been delivered enter (D)\nTo exit enter (E)\n");
        ch=getch();
        if(ch=='D'||ch=='d')
        {
            printf("Enter the house no.:\t");
            scanf("%d",&hn);
            fseek(f,sizeof(struct shopping),SEEK_SET);
            while(!feof(f))
            {
                fread(&g,sizeof(struct shopping),1,f);
                if((g.order==1)&&(g.delivery==0)&&(hn==g.houseno))
                {
                    g.delivery=1;
                    //printf("%d,%d,%d,%d\n",g.order,g.delivery,hn,g.houseno);
                    fseek(f,  - (long)sizeof(struct shopping), 1);
                    fwrite(&g,sizeof(struct shopping),1,f);
                    fclose(f);
                    break;
                }
            }
            grocerlistview();
        }
        else if(ch=='E'||ch=='e')
        {
            system("cls");
            ram();
        }
        else
        {
            printf("Invalid option\n");
        }
    }
    fclose(f);
}
void shoppinglist(char uid[6])
{
    char opt=NULL;
    time_t t;
    time(&t);
    FILE *f;
    int fn=0;
    f=fopen("ShoppingList.bin","rb+");
    struct shopping s;
    fseek(f,sizeof(struct shopping),SEEK_SET);
    while(!feof(f))
    {
        fread(&s,sizeof(struct shopping),1,f);
        if((strcmp(uid,s.id)==0)&&(fn==0))
        {
            fn++;
            break;
        }
    }
    if((uid[0]=='#')&&(s.houseno!=0))
    {
        usermenu:
            system("cls");
        printf("Shoppping List\n");
        for(int l=0;l<80;l++)
            printf("-");
        printf("\n");
        printf("To view or add an item to your shopping list enter (V)\nTo create a fresh list enter (F)\nTo exit enter (E)\n");
        for(int l=0;l<80;l++)
            printf("-");
	    printf("\nCurrent date and time : %s",ctime(&t));
        opt=getch();
        printf("\n");
        if(opt=='V'||opt=='v')
        {
            viewlist(uid);
            goto usermenu;
        }
        else if(opt=='F'||opt=='f')
        {
            printf("Are you sure you want to create a fresh list? Doing so will remove all items from your present list.\nEnter (Y) for yes and (N) for no\n");
            char fl;
            fl=getch();
            if(fl=='y'||fl=='Y')
            {
                freshlist(uid);
                goto usermenu;
            }
            else
            {
                goto usermenu;
            }
        }
        else if(opt=='E'||opt=='e')
        {
            delay(2);
            system("cls");
            menu(uid);
        }
        else
        {
            printf("Invalid option\n");
            goto usermenu;
        }
    }
    else if(uid[0]=='G')
    {
        grocerlistview();
    }
    else
    {
        printf("you are not allowed to use this feature\n");
        delay(2);
        system("cls");
        menu(uid);
    }
    fclose(f);
}

void menu(char userid[6])
{   time_t t=time(&t);
    a:
    printf("\n******************************  |MAIN MENU|  ***************************** \n\n");
    printf("*Please enter your choice *:\n");
    printf("Enter 1 to open Schedule Manager\n");
    printf("Enter 2 to open Bill Tracker\n");
    printf("Enter 3 to open Waste Management\n");
    printf("Enter 4 to open Complaints and Feedback\n");
    printf("Enter 5 to open Shopping List\n");
    printf("Enter 6 to logout\n");
    for(int l=0;l<80;l++)
		printf("-");
	    printf("\nCurrent date and time : %s",ctime(&t));
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
        case 1: printf("Opening Schedule Manager...\n");
                delay(2);
                system("cls");
                schedulemanager(userid);
                menu(userid);
                break;
        case 2: printf("Opening Bill Tracker...\n");
                delay(2);
                system("cls");
                billfile(userid);
                billtracker(userid);
                break;
        case 3: printf("Opening Waste Manager...\n");
                delay(2);
                system("cls");
                link(userid);
                break;
        case 4:printf("Opening Complaints and Feedback...\n");
               delay(2);
               system("cls");
               viewcomp(userid);
               viewfeed(userid);
               break;
        case 5: printf("Opening Shopping List...\n");
                delay(2);
                system("cls");
                shoppinglist(userid);
                break;
        case 6: delay(3);
                system("cls");
                ram();
                break;
        default: printf("Invalid input\n");
                 goto a;
    }
}
void main()
{
    //system("Color F0");
    //setcolor(10);
    ram();
}
