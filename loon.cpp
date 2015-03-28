#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int dh(int h, int A)
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

int main () {
    int R, C, A, L, V, B, T, x0, y0;
    cin >> R >> C >> A >> L >> V >> B >> T;
    
    int target[2250][2];
    int winds[75][300][8][2];
    int height[53][400];
    int dheight[53][400];
    
    for(int i=0; i<L; i++)
        cin >> target[i][0] >> target[i][1];
    
    cin >> x0 >> y0;
    for(int k=0; k<A; k++)
        for(int i=0; i<R; i++)
            for(int j=0; j<C; j++)
                cin >> winds[i][j][k][0] >> winds[i][j][k][1];
    
    
    for(int b=0; b<B; b++) // in round 0, all ballons leave
    {
        height[b][0] = 1;
        dheight[b][0] = 1;
    }
        
    for(int round=1; round<T; round++)
    {
        for(int b=0; b<B; b++)
        {
            dheight[b][round] = dh(height[b][round-1], A);
            height[b][round] = height[b][round-1] + dheight[b][round];
        }
    }
    
    for(int round=0; round<T; round++)
    {
        for(int b=0; b<B; b++)
            cout << dheight[b][round] << " ";
        cout << endl;
    }
    
    return 0;
}
