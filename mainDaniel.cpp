#include <bits/stdc++.h>
#define f(i,x,y) for (int i = x; i < y; i++)
#define fd(i,x,y) for(int i = x; i>= y; i--)
#define FOR(it,A) for(typeof A.begin() it = A.begin(); it!=A.end(); it++)
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define vint vector<int>
#define ll long long
#define clr(A,x) memset(A, x, sizeof A)
#define pb push_back
#define pii pair<int,int>
#define fst first
#define snd second
#define ones(x) __builtin_popcount(x)
#define cua(x) (x)*(x)
#define eps (1e-9)
#define oo (1<<30)
#define debug(x) cout <<#x << " = " << x << endl
#define adebug(x,n) cout <<#x<<endl; f(i,0,n)cout<<x[i]<<char(i+1==n?10:32)
#define mdebug(x,m,n) cout <<#x<<endl; f(i,0,m)f(j,0,n)cout<<x[i][j]<<char(j+1==n?10:32)
#define N 1
using namespace std;
template<class T> inline void mini(T &a,T b){if(b<a) a=b;}
template<class T> inline void maxi(T &a,T b){if(b>a) a=b;}

int cibles[75][300];
int hascibles[75][300];

int main(){
	int R,C,A; cin >> R >> C >> A;
	int cib, rayon, nb, ntour;
	cin >> cib >> rayon >> nb >> ntour;
	int rs,cs; cin >> rs >> cs;
	f(i,0,cib) {
		int r,c; cin >> r >> c;
		cibles[r][c] = 1;
		f(di,-7,8) f(dj,-7,8) if (di*di + dj*dj <= 49) {
			if (0 <= r + di && r + di < R) {
				int r2 = r + di, c2 = (c + dj + C) % C;
				hascibles[r2][c2] = 1;
			}
		}
	}

	f(i,0,300) f(j,0,75) {
		printf("%d", hascibles[j][i]);
		if (j + 1 == 75) putchar(10);
	}


	
}


