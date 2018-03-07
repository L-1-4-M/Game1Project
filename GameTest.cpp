#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

void printMap(char[][20]);
void creatMap(char[][20]);
void placeChar(char[][20],int[][3]);
void placeEnemy(char[][20],int[][3]);
void moveChar(char[][20],char,int[][3]);
void enemyMove(char[][20],int[][3]);
int charDistance(int,int,int[][3]);
int checkDistance(int,int,int,int[][3]);
int min(int,int);

int numChars = 0;

int main()
{
   char map[20][20];
   char move;
   int charPosition[20][3] = {};
   srand(time(0));
   creatMap(map);
   placeChar(map,charPosition);
   placeEnemy(map,charPosition);
   printMap(map);
   do
   {
      cin >> move;
      cout << endl;
      moveChar(map,move,charPosition);
      enemyMove(map,charPosition);
      printMap(map);
      cout << charDistance(0,1,charPosition) << endl;
   }while(move == 'a'||move == 's' ||move == 'd' ||move == 'w');
}

void creatMap(char map[][20])
{
   for(int i = 0;i<20;i++)
   {
      for(int j = 0;j<20;j++)
      {
         map[i][j] = '.';
      }
   }
   for(int i = 0;i<1;i++)
   {
      for(int j = 0;j<20;j++)
      {
         map[i][j] = '#';
         map[i+19][j] = '#';
         map[j][0] = '#';
         map[j][19] = '#';
      }
   }
}

void printMap(char map[][20])
{
   for(int i = 0;i<20;i++)
   {
      for(int j = 0;j<20;j++)
      {
         cout << map[i][j] << " ";
      }
      cout << endl;
   }
   cout << endl;
}

void placeChar(char map[][20],int charPosition[][3])
{
   int x = 1+rand()%18,y = 1+rand()%18;
   map[x][y] = 'A';
   charPosition[numChars][0] = 1;
   charPosition[numChars][1] = x;
   charPosition[numChars][2] = y;
   numChars++;
}

void placeEnemy(char map[][20],int charPosition[][3])
{
   int row,column;
   do
   {
      row =1+rand()%18;
      column =1+rand()%18;
   }while(map[row][column] == 'A');
   map[row][column] = 'E';
   charPosition[numChars][0] = 2;
   charPosition[numChars][1] = row;
   charPosition[numChars][2] = column;
   numChars++;
}

void moveChar(char map[][20], char move,int charPosition[][3])
{
   int currentI,currentJ;
   currentI = charPosition[0][1];
   currentJ = charPosition[0][2];
   if(move == 'a' && map[currentI][currentJ-1] != '#')
   {
      map[currentI][currentJ] = '.';
      map[currentI][currentJ-1] = 'A';
      charPosition[0][2]--;
   }else if(move == 'd' && map[currentI][currentJ+1] != '#')
   {
      map[currentI][currentJ] = '.';
      map[currentI][currentJ+1] = 'A';
      charPosition[0][2]++;
   }else if(move == 's' && map[currentI+1][currentJ] != '#')
   {
      map[currentI][currentJ] = '.';
      map[currentI+1][currentJ] = 'A';
      charPosition[0][1]++;
   }else if(move == 'w' && map[currentI-1][currentJ] != '#')
   {
      map[currentI][currentJ] = '.';
      map[currentI-1][currentJ] = 'A';
      charPosition[0][1]--;
   }
}

void enemyMove(char map[][20],int charPosition[][3])
{
   int row,column;
   int currentI,currentJ;
   int dist1,dist2,dist3,dist4,smallD;
   currentI = charPosition[1][1];
   currentJ = charPosition[1][2];
   row = currentI;
   column = currentJ;
   if(charDistance(0,1,charPosition) > 8)
   {
      do
      {
         if(rand()%2 == 0)
         {
            row = currentI + (rand()%3 - 1);
            column = currentJ;
         }else
         {
            row = currentI;
            column = currentJ + (rand()%3 - 1);
         }
      }while(map[row][column] == '#');
   }else
   {
      dist1 = checkDistance(0,currentI+1,currentJ,charPosition);
      dist2 = checkDistance(0,currentI-1,currentJ,charPosition);
      dist3 = checkDistance(0,currentI,currentJ+1,charPosition);
      dist4 = checkDistance(0,currentI,currentJ-1,charPosition);
      smallD = min(min(dist1,dist2),min(dist3,dist4));
      if(dist1 == smallD)
      {
         if(map[currentI+1][currentJ] != '#')
         {
            row = currentI+1;
            column = currentJ;
            cout << "MOVE DOWN" << endl;
         }
      }else if(dist2 == smallD)
      {
         if(map[currentI-1][currentJ] != '#')
         {
            row = currentI-1;
            column = currentJ;
            cout << "MOVE UP" << endl;
         }
      }else if(dist3 == smallD)
      {
         if(map[currentI][currentJ+1] != '#')
         {
            row = currentI;
            column = currentJ+1;
            cout << "MOVE RIGHT" << endl;
         }
      }else
      {
         if(map[currentI][currentJ-1] != '#')
         {
            row = currentI;
            column = currentJ-1;
            cout << "MOVE LEFT" << endl;
         }
      }
      
   }
   map[currentI][currentJ] = '.';
   map[row][column] = 'E';
   charPosition[1][1]=row;
   charPosition[1][2]=column;
}

int charDistance(int char1,int char2,int charPosition[][3])
{
   int char1Row = charPosition[char1][1], char1Column = charPosition[char1][2];
   int char2Row = charPosition[char2][1], char2Column = charPosition[char2][2];
   cout << endl << "Hero " << char1Row << " " << char1Column << endl;
   cout << "Enemy " << char2Row << " " << char2Column << endl;
   return sqrt(pow((char1Row - char2Row),2) + pow((char1Column-char2Column),2));
}

int checkDistance(int char1,int char2Row,int char2Column,int charPosition[][3])
{
   int char1Row = charPosition[char1][1], char1Column = charPosition[char1][2];
   return sqrt(pow((char1Row - char2Row),2) + pow((char1Column-char2Column),2));
}
int min(int d1,int d2)
{
   if(d1<d2)
      return d1;
   else
      return d2;
}
