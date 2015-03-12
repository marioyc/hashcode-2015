#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>

using namespace std;

#define MAXR 1000
#define MAXC 1000
#define MAXS 700

bool used[MAXR][MAXC];
int z[MAXS],cap[MAXS];
int ar[MAXS],as[MAXS],ap[MAXS];

bool check(int r, int c, int sz){
	for(int i = 0;i < sz;++i)
		if(used[r][c + i])
			return false;

	return true;
}

void mark(int r, int c, int sz){
	for(int i = 0;i < sz;++i)
		used[r][c + i] = true;
}

int main(){
	ios::sync_with_stdio(0);

	int R,C,U,P,M;

	cin >> R >> C >> U >> P >> M;

	for(int i = 0,r,c;i < U;++i){
		cin >> r >> c;
		used[r][c] = true;
	}

	memset(ar,-1,sizeof ar);
	memset(as,-1,sizeof as);

	pair<int, int> order[M];

	for(int i  = 0,r,c;i < M;++i){
		cin >> z[i] >> cap[i];
		order[i] = make_pair(cap[i],i);
	}

	sort(order,order + M);

	for(int i = 0;i < M;++i){
		bool found = false;
		int ind = order[M - 1 - i].second;

		for(int j = 0;j < R && !found;++j){
			for(int k = 0;k + z[ind] <= C && !found;++k){
				if(check(j,k,z[ind])){
					ar[ind] = j;
					as[ind] = k;
					found = true;
					mark(j,k,z[ind]);
				}
			}
		}
	}

	for(int i = 0,pos = 0;i < M;++i){
		int ind = order[M - 1 - i].second;

		if(ar[ind] != -1){
			ap[ind] = pos;
			pos = (pos + 1) % P;
		}
	}

	for(int i = 0;i < M;++i){
		if(ar[i] == -1) cout << "x\n";
		else cout << ar[i] << " " << as[i] << " " << ap[i] << '\n';
	}

	return 0;
}