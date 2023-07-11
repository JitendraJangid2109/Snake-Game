#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

#define N 20  // Defining width of the field area
#define M 40  // Defining the length of the field area

int i,j, Field[N][M],x,y,Gy,Head,Tail,Game, Frogs ,a ,b, var, direction; // a and b use to hold random position of frog


// x is the initial cordinate in horizontal direction of snake
// y is the initial cordinate in vertical direction of snake
// Gy is the temporary variable
// Head starting point of snake  Tail is the end point of snake


void snakeinitialization(){
    for(i=0;i<N;i++){           // This loop is traverse the whole field
        for(j=0;j<M;j++){       // and make every element of the field 0
            Field[i][j] = 0;
        }
    }

x= N/2;  y=M/2; Gy = y; Head = 5; Tail = 1;  Game=0;  Frogs=0;   // Game =0 signifies that the game is running and 1 represent
 for(i=0;i<Head;i++){
    Gy++;
    Field[x][Gy-Head] = i+1;
 }

}
void print(){
     
    //  This loop is use to make the the upper boundry of "Field of Play"
      for(i=0;i<=M+1;i++){
        if(i==0){
            printf("%c",201);  // Printing the "╔" symbol of ascii at the starting of the first row
        }

        else if(i==M+1){
            printf("%c",187); // Printing the "╗" symbol at the last of first row
        }

        else{
            printf("%c",205);   // Printing the "═" symbol at the remainng of first row
        }
      }

      printf("\n");


     //   This loop is use to make the the side boundry of "Field of Play"
      for(i=0;i<N;i++){
        printf("%c",186); // Printing the "║"  at the begining of every row
        for(j=0;j<M;j++){

            if(Field[i][j]==0){
                printf(" ");
            }

            if(Field[i][j] > 0 && Field[i][j] != Head){
                printf("%c",176);
            }

            if(Field[i][j]==Head){
                printf("%c",128);
            }

            if(Field[i][j]==-1){
                printf("%c",137);
            }
             if(j==M-1){
                printf("%c\n",186);
             }
        }
      }

      //  This loop is use to make the the Lower boundry of "Field of Play"

       for(i=0;i<=M+1;i++){
        if(i==0){
            printf("%c",200);  // Printing the "╚" symbol of ascii at the starting of the last row
        }

        else if(i==M+1){
            printf("%c",188); // Printing the "╝" symbol at the last of last row
        }

        else{
            printf("%c",205);   // Printing the "═" symbol at the remaining position of last row
        }
      }
}


// This function is moving the screen up and the cursor position is on the topmost left corner everytime
void ResetScreenPosition(){
    
     HANDLE hOut;
     COORD Position;
     hOut = GetStdHandle(STD_OUTPUT_HANDLE);
     Position.X = 0;
     Position.Y = 0;
     SetConsoleCursorPosition(hOut,Position);
}


Random(){
      srand(time(0));
      a = 1 + rand() % 18;
      b = 1 + rand() % 38;

      if(Frogs==0 && Field[a][b]==0){
          Field[a][b] = -1;
          Frogs = 1;
      }
}

int getch_noblock(){
    if(_kbhit()){
        return _getch;
    }
    else 
       return -1;
}

void movement(){
    var = getch_noblock();
    var = tolower(var);

    if(var=='d' || var=='a' || var=='w' || var=='s')  direction =var;
    if(direction == 'd'){
        y++;
        Head++;
        Field[x][y] = Head;
    }

     if(direction == 'a'){
        y--;
        Head++;
        Field[x][y] = Head;
    }
    
     if(direction == 'w'){
        x--;
        Head++;
        Field[x][y] = Head;
    }
    
     if(direction == 's'){
        x++;
        Head++;
        Field[x][y] = Head;
    }

}

void main() {
    snakeinitialization();

      while(Game == 0){
         print();
         ResetScreenPosition();
         Random();
         movement();
         Sleep(99);
      }

}