#include <stdio.h>      
#include <windows.h>   // used for the use of sleep function
#include <stdlib.h>    // this header file includes memory allocation freeing function
#include <conio.h>    // used function  clrscr, getch, getche, kbhit from this file
#include <time.h>  // The time.h header file contains definitions of 
                    // functions to get and manipulate date and time information. 

#define N 20  // Defining the width of field
#define M 40  // Defining the length of field

int i,j,Field[N][M],x,y,Gy,Head,Tail,Game,Frogs,a,b,var,dir,score,HighScore,Speed;

// x is the initial cordinate in horizontal direction of snake
// y is the initial cordinate in vertical direction of snake
// Gy is the temporary variable
// Head starting point of snake  Tail is the end point of snake

FILE *f;  // File to store the High Score

void snakeInitialization(){
    f=fopen("highscore.txt","r");   // Creating file in read mode to read to highscore
    fscanf(f,"%d",&HighScore);      // Taking the high as input in file
    fclose(f);                      // Closing the file

    for(i=0;i<N;i++){
        for(j=0;j<M;j++){       // This loop is to make all element of the given play area
            Field[i][j]=0;      //  equal to 0 , So that we can make use of numbers to create othe used things
        }
    }

   // It is the begining cordinates of the snake where the game starts
    x=N/2;y=M/2; Gy = y; Head = 5; Tail =1; Game = 0,Frogs = 0,dir='d',score=0,Speed = 60;

    for(i=0;i<Head;i++){
        Gy++;                       // This variable takes the value from 
        Field[x][Gy-Head] = i+1;    // F[20][6]=1 , F[20][7]=2,  F[20][8]=3 , F[20][9] = 4 , F[20][10]=5
                                   // We are using these numbers to print our snake by using there value
    }
}




void print(){

    //  This loop is use to make the the upper boundry of "Field of Play"
    for(i=0;i<=M+1;i++){
        if(i==0){
            printf("%c",201); // Printing the "╔" symbol of ascii at the starting of the first row
        }
        else if(i==M+1){
            printf("%c",187); // Printing the "╗" symbol at the last of first row
        }
        
        else{
            printf("%c",205); // Printing the "═" symbol at the remainng of first row
        
        }
    }
    printf("   Current Score: %d  HighScore: %d",score,HighScore);
    printf("\n");

    for(i=0;i<N;i++){
        printf("%c",186);    // Printing the "║"  at the begining of every row

        for(j=0;j<M;j++){
            if(Field[i][j]==0) printf(" ");

            if(Field[i][j]>0 && Field[i][j]!=Head) printf("%c",176);  // the middle portion of snake printing ASCII char 176
            
            if(Field[i][j]==Head) printf("%c",178);     // Printing the head with dark dotted character
            
            
            if(Field[i][j]==-1) printf("%c",224);       // Printing the Frog
            
            if(j==M-1) printf("%c\n",186);
        }
    }

    
     //  This loop is use to make the the Lower boundry of "Field of Play"

    for(i=0;i<=M+1;i++){
        if(i==0){
            printf("%c",200);    // Printing the "╚" symbol of ascii at the starting of the last row
        }
        else if(i==M+1){
            printf("%c",188);    // Printing the "╝" symbol at the last of last row
        }
        else{
            printf("%c",205);    // Printing the "═" symbol at the remaining position of last row
        }
    }

    system("color 78");
}
void ResetScreenPosition(){
    HANDLE hOut;                  // void pointer HANDLE func. , it handles the console of the program
    COORD Position;               // It provides the cordinates x,y
    hOut = GetStdHandle(STD_OUTPUT_HANDLE); // handles the standard output that we see on terminal
    Position.X = 0;              // these positions are of lefttop corner from where the next frame will be made 
    Position.Y = 0;
    SetConsoleCursorPosition(hOut,Position);  // it is setting up the cursor on position (0,0) 
                                             // untill the second comes it print the field and the snake on the same position
}



 // srand with rand generates  different number everytime
 // but rand  function alone generate a same type of pattern for the numbers
void Random(){             // time(0) shows current time
    srand(time(0));        // srand give the frog position randomly everytime  it is connected with time
    a = 1+ rand() % 18;    // rand()%18 give random number on the screen under the width of 18 bcoz we dont want frog on
    b = 1 + rand() % 38;   // on  both the borders
                           // same for the length


    // Frog not present and space is blank than show the frog as -1 
    if(Frogs == 0 && Field[a][b]==0){
        Field[a][b]= -1;    // -1 is given to space where the will print
        Frogs = 1;          // increasing frog whenever the space shows -1 
        if(Speed>10 && score!=0) Speed = Speed - 10; // Speed is used in sleep function as the speed decreases 
    }                                           // Sleep time decrease and the execution goes fastly
}

int getch_noblock(){
    if(_kbhit())     // this is used to take input from keyboard  
        return _getch();  // only accept the character return ascii value otherwise return -1
    else
        return -1;
}

void movement(){
    var = getch_noblock();
    var = tolower(var);

    if(((var=='d'||var=='a')||(var=='w'||var=='s'))
       &&(abs(dir-var)>5)) dir = var;  // abs(dir-var)>5  this is used so that the snake could not take 180 degree turn
    if(dir =='d'){
        y++;       // moving in this direction increases snake in d(right) direction 
        if(y==M-1) y = 0;   // if snake goes in the boundry then it come out from opposite wall
        
    // The below condition is first snake is not in the blank space
    //  second the snake is not on the frog 
    // so finally it is on its own body and the game is over 
        if(Field[x][y]!=0 && Field[x][y]!=-1) GameOver();
        if(Field[x][y]==-1){
            Frogs = 0;
            Beep(750,200);   

            score+=5;    // Every time snake eats frog, score increase by 5
            Tail -= 1;
        }

        Head++;   // this shows that the head is continuously moving ahead
        Field[x][y] = Head;
    }

    if(dir =='a'){
        y--;
        if(y==0) y = M-1;  // if entering from upper boundry comes out from lower boundry
        
    // The below condition is first snake is not in the blank space
    //  second the snake is not on the frog 
    // so finally it is on its own body and the game is over 
        if(Field[x][y]!=0 && Field[x][y]!=-1) GameOver();


        if(Field[x][y]==-1){
            Frogs = 0;
            Beep(750,200);   

            score+=5;  // Every time snake eats frog, score increase by 5 
            Tail -= 1;
        }
        Head++;
        Field[x][y] = Head;
    }

    if(dir =='w'){
        x--;
        if(x==-1) x = N-1;

        
    // The below condition is first snake is not in the blank space
    //  second the snake is not on the frog 
    // so finally it is on its own body and the game is over 
        if(Field[x][y]!=0 && Field[x][y]!=-1) GameOver();
        if(Field[x][y]==-1){
            Frogs = 0;
            Beep(750,200);   

            score+=5;        // Every time snake eats frog, score increase by 5
            Tail -= 1;
        }
        Head++;
        Field[x][y] = Head;
    }

    if(dir =='s'){
        x++;
        if(x==N-1) x = 0;


    // The below condition is first snake is not in the blank space
    //  second the snake is not on the frog 
    // so finally it is on its own body and the game is over    
        if(Field[x][y]!=0 && Field[x][y]!=-1) GameOver();
        if(Field[x][y]==-1){
            Frogs = 0;  
            Beep(750,200);   
            score+=5;      
            Tail -= 1;
        }
        Head++;
        Field[x][y] = Head;
    }
}


// This function is used to make the tail of snake move when the snake move ahead
void TailRemove(){
    for(i=0;i<N;i++){                    
        for(j=0;j<M;j++){
            if(Field[i][j]==Tail){
                Field[i][j] = 0;
            }
        }
    }
    Tail++;
}

void GameOver(){
    printf("\a");       // \a gives beep sound in C 
    Beep(750,800);
    Beep(750,800);

    Sleep(1500);        //  it is the waiting time of 1500 milisecond
    system("Cls");      // Cls is used to clear the screen

    if(score>HighScore){          // If score is greater than high score than storing the score in the file
        printf("  New HighScore %d!!!!!!\n\n",score);
        system("pause");
        f=fopen("highscore.txt","w");  // Storing the high score in 'w' write mode of file
        fprintf(f,"%d",score);
        fclose(f);
    }

    system("Cls");
    printf("\n\n                           GAME OVER !!!!!!\n");
    printf("                              Score : %d \n\n",score);
    printf("                     Press ENTER to play again or ESC to exit ... \n");


    while(1){
        var = getch_noblock();
        if(var == 13){     // 13 is the ASCII value of Enter if entr press than game initialise again
            Game = 0;     // Here Game =0 shows game is ON
            snakeInitialization();
            break;
        }else if(var == 27){  // 27 is escape ASCII value if press escape than the game terminate
            Game = 1;   // Game =1 shows game is terminated
            break;
        }
    }
    system("Cls");
}
void main(){
    snakeInitialization();

    while(Game == 0){   // here i have taken game==0 as the game is in ON condition
        print();
        ResetScreenPosition();
        Random();
        movement();
        TailRemove();
        Sleep(Speed);  //sleep() function will stop the present executable for the specified time
    }
}