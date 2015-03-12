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

vector<pair<int,int> > v[16];

struct pool {
	int sum;
	int mx;
	int val[16];
	pool() {
		sum = 0;
		mx = 0;
		f(i,0,16) val[i] = 0;
	}
	pool(int s, int c, int v[16]) {
		sum = s; mx = c;
		f(i,0,16) val[i] = v[i];
	}
	bool canadd(int c, int t) {
		vint valid(16,0);
		f(i,0,16) if (v[i].size() && v[i][0].fst >= t) valid[i] = 1;
		int pos, mn = oo;
		f(i,0,16) if (valid[i] && mn > val[i]) mn = val[i], pos = i;
//		cout << v[pos][0].fst << " " << t << endl;

		if (v[pos].size() && v[pos][0].fst >= t) return 1;
		else return 0;
	}
	void add(int c, int t, int &row, int &col ) {
		vint valid(16,0);
		f(i,0,16) if (v[i].size() && v[i][0].fst >= t) valid[i] = 1;
		int pos, mn = oo;

		f(i,0,16) if (valid[i] && mn > val[i]) mn = val[i], pos = i;
//		if (mn == oo) return 0;


//		if (v[pos].size() && v[pos][0].fst >= t) {
		v[pos][0].fst -= t;
		v[pos][0].snd += t;
//		} else return 0;
		row = pos;
		col = v[pos][0].snd - t;
		int j = 0;
		while(j+1 < v[pos].size() &&  v[pos][j] < v[pos][j+1] ) swap(v[pos][j], v[pos][j+1]), j++;
		

		val[pos] += c;
		sum += c;
		mx = max(mx, val[pos]);
	}
	int capacity() {
		return sum - mx;
	}
	int value() {
		return capacity() * 10000 + sum;
	}
} pl[45];

struct server {
	int tam, cap;
	int id;
	server() {}
	server(int t, int c, int i) : tam(t), cap(c), id(i) {}

	void read() {
		scanf("%d %d", &tam, &cap);
	}
} sv[625];

bool operator<(server A, server B) {
	int v1, v2;
	v1 = A.tam * 100 + A.cap;
	v2 = B.tam * 100 + B.cap;
	return v1 > v2;
}

struct answer {
	int x,y,z;
	answer() { x = -1; }
	answer(int x, int y, int z) : x(x), y(y), z(z) {}
	void print() {
		if (x == -1) puts("x");
		else printf("%d %d %d\n", x, y, z);
	}
} ans[625];

int A[16][100];

int main(){
	int r,s,u,p,m;
	cin >> r >> s >> u >> p >> m;
	f(t,0,u) {
		int x,y;
		scanf("%d%d", &x, &y);
		A[x][y] = 1;
	}
//	f(i,0,16) {
//		f(j,0,100) printf("%d", A[i][j]);
//		putchar(10);
//	}


	f(i,0,16) {
//		debug(i);
		for(int j = 0, k = 0; j < 100; j = ++k) if (A[i][j] == 0) {
			k = j;
//			debug(k);
			for(; k < 100 && A[i][k] == 0; k++);
//			debug(k);
			v[i].pb( pii(k-j, j) );
		}
		sort(rall(v[i]));
//		f(j,0,v[i].size()) cout << "(" << v[i][j].fst << ","<<v[i][j].snd << ") ";
//		cout << endl;
	}
	f(t,0,m) {
		sv[t].read();
		sv[t].id = t;
	}

	sort(sv, sv + m);

	f(t,0,m) {
		int cap = sv[t].cap, tam = sv[t].tam;

		int who, mincap = oo;
		int row[p], col[p];
		vint valid(p, 0);

		f(w,0,p) {
			valid[w] = pl[w].canadd( cap, tam );
		}


		f(i,0,p) if(valid[i]) {
			int tmp = pl[i].value();
			if (mincap > tmp) mincap = tmp, who = i;
		}
		if (mincap == oo) continue;
		

//		debug(t);
		pl[who].add( cap, tam, row[who], col[who] );
		ans[ sv[t].id ] = answer(row[who], col[who], who);

//		cout << row[who] << " " << col[who] << " " << who << "   " << cap << " " << tam << endl;
//		putchar(10);
//		f(i,0,16) {
//			f(j,0,100) printf("%d", A[i][j]);
//			putchar(10);
//		}
		/*
		cout << endl;
		f(i,0,16) {
			f(j,0,v[i].size()) cout << "(" << v[i][j].fst << ","<<v[i][j].snd << ") ";
			cout << endl;
		}
		*/

	}
	f(i,0,p) {
		f(j,0,16) cout << pl[i].val[j] << " "; cout << " " << pl[i].capacity() << endl;
	}


	cout << "here" << endl;
	f(t,0,m) {
		ans[t].print();
	}



}


