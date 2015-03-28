#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

#define MAXR 75
#define MAXC 300
#define MAXA 8
#define MAXL 2250
#define MAXV 7
#define MAXB 53
#define MAXT 400

int R, C, A, L, V, B, T, xref, yref;
int target[MAXL][2];
int winds[MAXR][MAXC][MAXA][2];
bool world[MAXR][MAXC];
bool ballonOut[MAXB];
int positions[MAXB][2];
  

int randomDh(int h, int A)
{
   double prob = (rand()/(double)(RAND_MAX + 1));
   if(h > 1 && h < A) // prob = 1/3
       return (prob < .333 ? -1 : (prob < .666 ? 0 : 1));
   else
   {
       if (h == 1)
           return (prob < .5 ? 1 : 0);
       else // h == A
           return (prob < .5 ? -1 : 0);
   }
}

double columndist(int c1, int c2){
  return min(abs(c1 - c2), C - abs(c1 - c2));
}

bool isInRadius(int u, int v, int r, int c, int V){
   double d = (r - u)*(r - u) + columndist(c,v)*columndist(c,v);
   if(d <= V)
       return true;
   return false;
}

int score(int r, int c, int radius){
   int left = ((c - R)%C + C)%C;
   int right = c + R; 
   int bottom = r - R;
   int up = r + R;
   int score = 0;
   
   if(bottom < 0)
       bottom = 0;
   if(up >= R)
       up = R-1;
   
   for (int i = bottom; i <= up; ++i)
   {
       for (int j = left; j <= right; j++)
       {
           if(isInRadius(i, j%C, r, c, radius) && world[i][j%C])
               score++;
       }
   }
   
   return score;
}

bool isOut(int x){
   return (x<0 || x>=R);
}

int findDh(int x0, int y0, int h0)
{
   int x, y, h;
   int scores[3];
   
   // case dh = -1
   if(h0 > 1)
   {
       h = h0 - 1;
       x = x+winds[x0][y0][h][0];
       y = (y+winds[x0][y0][h][1])%C;
       if(!isOut(x))
           scores[0] = score(x, y, V);
       else
           scores[0] = -1;
   }
   
   // case dh = 0
   h = h0 - 1;
   x = x+winds[x0][y0][h][0];
   y = (y+winds[x0][y0][h][1])%C;
   if(!isOut(x))
       scores[1] = score(x, y, V);
   else
       scores[1] = -1;
   
   // case dh = 0
   if(h0 < h)
   {
       h = h0 + 1;
       x = x+winds[x0][y0][h][0];
       y = (y+winds[x0][y0][h][1])%C;
       if(!isOut(x))
           scores[2] = score(x, y, V);
       else
           scores[2] = -1;
   }

   if(scores[2] > scores[1] && scores[2] > scores[0])
       return 1;
   if(scores[1] > scores[0])
       return 0;
   return -1;
}

bool test(){
    for(int round=0; round<MAXT; round++)
    {
        for(int b=0; b<MAXB; b++){
            cin >> dheight;


        }
        cout << endl;
    }
}



int main () {
   cin >> R >> C >> A >> L >> V >> B >> T;
      
   for(int i=0; i<L; i++)
   {
       cin >> target[i][0] >> target[i][1];
       world[target[i][0]][target[i][1]] = true;
   }
   
   cin >> xref >> yref; // initial coordinates
   for(int k=0; k<A; k++)
       for(int i=0; i<R; i++)