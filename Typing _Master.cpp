#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 40
#define WIN_WIDTH 70

struct user_score
{
    int storescore;
    int level;
};

struct node
{
    struct node *next;
    int data;
    int user_level;
};

struct node *f=NULL;
struct node *r=NULL;


void gameover(int);
int tempmain();
void enqueueScore(int,int);
void traverse(struct node*);
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
int play(void);
char keys[10];
int keyPos[10][2];
int score = 0;

void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size)
{
    if(size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder()
{
    for(int i=4; i<SCREEN_WIDTH; i++)
    {
        gotoxy(i,3);
        cout<<"-";
    }
    for(int i=4; i<SCREEN_WIDTH; i++)
    {
        gotoxy(i,SCREEN_HEIGHT);
        cout<<"-";
    }
    gotoxy(3,SCREEN_HEIGHT);
    cout<<"+";
    gotoxy(SCREEN_WIDTH,SCREEN_HEIGHT);
    cout<<"+";
    for(int i=3; i<SCREEN_HEIGHT; i++)
    {
        gotoxy(3,3);
        cout<<"+";
        gotoxy(SCREEN_WIDTH,3);
        cout<<"+";
        gotoxy(3,i);
        cout<<"|";
        gotoxy(SCREEN_WIDTH,i);
        cout<<"|";
    }
    for(int i=4; i<SCREEN_HEIGHT; i++)
    {
        gotoxy(WIN_WIDTH,i);
        cout<<"|";
    }
}

void genAlphabet(int ind)
{
    keys[ind] = 65+rand()%25;
    keyPos[ind][0] = 4+rand()%(WIN_WIDTH-4);
    keyPos[ind][1] = 5;
}

void drawAlphabet(int ind)
{
    if(keyPos[ind][0]!=0)
    {
        gotoxy(keyPos[ind][0], keyPos[ind][1]);
        cout<<keys[ind];
    }
}

void eraseAlphabet(int ind)
{
    if(keyPos[ind][0]!=0)
    {
        gotoxy(keyPos[ind][0], keyPos[ind][1]);
        cout<<" ";
    }
}

void resetAlphabet(int ind)
{
    eraseAlphabet(ind);
    genAlphabet(ind);
}

void gameover(int levelcount)
{
    system("cls");
    FILE *fp;
    struct user_score s;
    cout<<endl;
    gotoxy(30,12);
    cout<<"============================"<<endl;
    gotoxy(30,13);
    cout<<"--------- Game Over --------"<<endl;
    gotoxy(30,14);
    cout<<"============================"<<endl;
    gotoxy(30,15);
    cout<<"Your score :"<<"|"<<score<<"|";

    fp=fopen("score1.txt","ab");
    s.storescore=score;
    s.level=levelcount;
    fwrite(&s,sizeof(s),1,fp);
    fclose(fp);
    gotoxy(30,18);
    cout<<"Press any key to go back Main Menu";
    getch();
}

void updateScore()
{
    gotoxy(WIN_WIDTH + 7,8);
    cout<<"Score : "<<score<<endl;
}

void instruction()
{
    system("cls");
    gotoxy(40,10);
    cout<<"Instructions";
    gotoxy(20,12);
    cout<<"========================================================";
    gotoxy(20,14);
    cout<<" 1. On the left side, you will see falling characters";
    gotoxy(20,15);
    cout<<" 2. You have to type that character before comes to down";
    gotoxy(20,16);
    cout<<" 3. Press respective key from keyboard to keep playing";
    gotoxy(20,17);
    cout<<" 4. Press 'escape' to exit";
    gotoxy(25,20);
    cout<<" Press any key to go back to Main Menu";
    getch();
}

void Low()
{
    score = 0;
    int level=1;
    for(int i=0; i<10; i++)
    {
        keyPos[i][0] = keyPos[i][1] = 5;
    }
    system("cls"); 
    drawBorder();
    updateScore();

    for(int i=0; i<10; i++)
    {
        genAlphabet(i);
    }
    gotoxy(WIN_WIDTH + 4, 5);
    cout<<"Typing Master";
    gotoxy(WIN_WIDTH + 4, 10);
    cout<<"ESC for Exit";
    gotoxy(WIN_WIDTH + 4, 7);
    cout<<"-------------";
    gotoxy(WIN_WIDTH + 4, 9);
    cout<<"-------------";

    while(1)
    {
        if(kbhit())
        {
            char ch = getch();
            for(int i=0; i<10; i++)
            {
                if(ch == keys[i] || ch-32 == keys[i])
                {
                    resetAlphabet(i);
                    score++;
                    updateScore();
                }

            }
            if(ch==27)
            {
                gameover(level);
                break;
            }

        }

        for(int i=0; i<10; i++)
        {
            drawAlphabet(i);
        }
        Sleep(1300);

        for(int i=0; i<10; i++)
        {
            eraseAlphabet(i);
            keyPos[i][1] += 1;
            if(keyPos[i][1]>SCREEN_HEIGHT)
            {
                gameover(level);
                return;
            }
        }
    }
}

void Intermediate()
{
    score = 0;
    int level=2;
    for(int i=0; i<10; i++)
    {
        keyPos[i][0] = keyPos[i][1] = 5;
    }
    system("cls");
    drawBorder();
    updateScore();

    for(int i=0; i<10; i++)
    {
        genAlphabet(i);
    }
    gotoxy(WIN_WIDTH + 4, 5);
    cout<<"Typing Master";
    gotoxy(WIN_WIDTH + 4, 10);
    cout<<"ESC for Exit";
    gotoxy(WIN_WIDTH + 4, 7);
    cout<<"-------------";
    gotoxy(WIN_WIDTH + 4, 9);
    cout<<"-------------";

    while(1)
    {
        if(kbhit())
        {
            char ch = getch();
            for(int i=0; i<10; i++)
            {
                if(ch == keys[i] || ch-32 == keys[i])
                {
                    resetAlphabet(i);
                    score++;
                    updateScore();
                }
            }
            if(ch==27)
            {
                gameover(level);
                break;
            }
        }

        for(int i=0; i<10; i++)
        {
            drawAlphabet(i);
        }
        Sleep(700);

        for(int i=0; i<10; i++)
        {
            eraseAlphabet(i);
            keyPos[i][1] += 1;
            if(keyPos[i][1]>SCREEN_HEIGHT)
            {
                gameover(level);
                return;
            }
        }
    }
}

void High()
{
    score = 0;
    int level=3;
    for(int i=0; i<10; i++)
    {
        keyPos[i][0] = keyPos[i][1] = 5;
    }
    system("cls");
    drawBorder();
    updateScore();

    for(int i=0; i<10; i++)
    {
        genAlphabet(i);
    }
    gotoxy(WIN_WIDTH + 4, 5);
    cout<<"Typing Tester";
    gotoxy(WIN_WIDTH + 4, 10);
    cout<<"ESC for Exit";
    gotoxy(WIN_WIDTH + 4, 7);
    cout<<"-------------";
    gotoxy(WIN_WIDTH + 4, 9);
    cout<<"-------------";

    while(1)
    {
        if(kbhit())
        {
            char ch = getch();
            for(int i=0; i<10; i++)
            {
                if(ch == keys[i] || ch-32 == keys[i])
                {
                    resetAlphabet(i);
                    score++;
                    updateScore();
                }
            }
            if(ch==27)
            {
                gameover(level);
                break;
            }
        }

        for(int i=0; i<10; i++)
        {
            drawAlphabet(i);
        }
        Sleep(300);

        for(int i=0; i<10; i++)
        {
            eraseAlphabet(i);
            keyPos[i][1] += 1;
            if(keyPos[i][1]>SCREEN_HEIGHT)
            {
                gameover(level);
                return;
            }
        }
    }
}


int play()
{
    int ch1;
    while(1)
    {
        system("cls");
        gotoxy(34,5);
        cout<<"Decide The Level You Want to Play!!";
        gotoxy(32,6);
        cout<<"-------------------------------------";
        gotoxy(38,8);
        cout<<"1. Low Level ";
        gotoxy(38,9);
        cout<<"2. Intermediate Level";
        gotoxy(38,10);
        cout<<"3. High Level ";
        gotoxy(38,11);
        cout<<"4. Back";
        gotoxy(32,13);
        cout<<"-------------------------------------";
        gotoxy(38,15);
        cout<<"Enter Your Choice : ";
        cin>>ch1;

        switch(ch1)	
        {
        case 1:
            Low();
            break;
        case 2:
            Intermediate();
            break;
        case 3:
            High();
            break;
        case 4:
            tempmain();
            break;
        }
    }
    return 0;
}

void progress()
{
    int x,y;
    struct scoreNode *head;
    system("cls");
    FILE *fp;
    fp=fopen("score1.txt","rb");
    struct user_score s;

    if(fp==NULL)
    {
        printf("error in opening file");
    }
    int i=1;
    gotoxy(15,2);
    cout<<"YOUR PROGRESS GRAPH";
    gotoxy(0,40);
    cout<<"Score";
    while(i<47)
    {
        gotoxy(5,++i);
        cout<<"|";
    }
    i=5;
    while(i<200)
    {
        gotoxy(++i,47);
        cout<<"_";
    }
    gotoxy(20,48);
    cout<<"Attempts";
    while(fread(&s,sizeof(s),1,fp))
    {
        enqueueScore(s.storescore,s.level);
    }
    traverse(f);
    fclose(fp);
    getch();
}


//creating nodes
void enqueueScore(int val,int levelcount)
{
    struct node *n;
    n=(struct node *)malloc(sizeof(struct node));
    if (n==NULL)
    {
        printf("\nQueue is Full");
    }
    else
    {
        n->data=val;
        n->next=NULL;
        n->user_level=levelcount;
        if (f==NULL)
        {
            f=r=n;
        }
        else
        {
            r->next=n;
            r=n;
        }
    }

}


void traverse(struct node *s)
{
    int y=0;
    int x=0;
    int  i=10;
    int draw=0;
    int Attempt=1;
    int posX;
    int posY;
    int temp;
    string userLevel;
    while (s!=NULL)
    {
        posX=(i+5);
        posY=temp=(48-s->data/4);
        gotoxy(--posX,--posY);
        if(s->user_level==1)
        {
            userLevel="Low";
        }
        else if(s->user_level==2)
        {
            userLevel="Moderate";
        }
        else if(s->user_level==3)
        {
            userLevel="High";
        }
        else
        {
            userLevel="Unknown";
        }
        cout<<"Level:"<<userLevel;
        gotoxy(++posX,++posY);
        cout<<"|("<<Attempt++<<","<<s->data<<")";
        while(posY<=46)
        {
            gotoxy(posX,++posY);
            cout<<"|";
        }

        /*while(posX>6){
            gotoxy(--posX,temp);
            cout<<"-";
        }*/

        s=s->next;
        i=i+15;
    }

    while(f!=NULL){
        struct node* ptr;
        ptr=f->next;
        free(f);
        f=ptr;
    }
}


int tempmain()
{
    setcursor(0,0);
//    srand((unsigned)time(NULL));

    do
    {
        system("cls");
        gotoxy(38,5);
        cout<<"TYPING MASTER";
        gotoxy(37,6);
        cout<<"---------------";
        gotoxy(29,8);
        cout<<"+------------------------------+";
        gotoxy(29,9);
        cout<<"|	         Main Menu          |";
        gotoxy(29,10);
        cout<<"|------------------------------|";
        gotoxy(29,11);
        cout<<"|                              |";
        gotoxy(29,12);
        cout<<"|   1. Start Game              |";
        gotoxy(29,13);
        cout<<"|   2. Instructions            |";
        gotoxy(29,14);
        cout<<"|   3. Your progress           |";
        gotoxy(29,15);
        cout<<"|   4. Quit                    |";
        gotoxy(29,16);
        cout<<"|                              |";
        gotoxy(29,17);
        cout<<"+------------------------------+";
        gotoxy(29,19);
        cout<<" Select Option : ";
        char ch =getche();
        cout<<"\n\n";
        if(ch=='1')
            play();
        else if(ch=='2')
            instruction();
        else if(ch=='3')
            progress();
        else if(ch=='4')
            exit(0);
        else
        {
            cout<<"\nyou entered a invalid choice";
            Sleep(800);
        }

    }
    while(1);

    return 0;
}

int main()
{
    system("color A");
    //char developers[][20]= {"AYUSH VERMA","NAMAN KUMAR","SURYANSH PUNDIR","SARTHAK GUPTA"};
        system("cls");
        gotoxy(36,3);
        cout<<"WELCOME TO TYPING MASTER";
		gotoxy(43,6);
        cout<<"DEVELOPERS";
        gotoxy(41,7);
        cout<<"--------------";
		gotoxy(31,9);
		cout<<"..............     .............";
        gotoxy(31,10);
        cout<<":                              :";
        gotoxy(40,11);
        cout<<"  AYUSH VERMA ";
        gotoxy(40,12);
        cout<<"  NAMAN KUMAR ";
        gotoxy(40,13);
        cout<<" SARTHAK GUPTA ";
        gotoxy(40,14);
        cout<<"SURYANSH PUNDIR ";
        gotoxy(31,15);
        cout<<":                              :";
        gotoxy(31,16);
        cout<<"..............     .............";
        gotoxy(31,18);
        cout<<"Press enter to continue...";

    getch();


    tempmain();
}
