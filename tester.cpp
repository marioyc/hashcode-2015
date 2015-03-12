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

bool mark(int r, int c, int sz){
	for(int i = 0;i < sz;++i){
		if(used[r][c + i])
			return false;
		used[r][c + i] = true;
	}

	return true;
}

int main(){
	ios::sync_with_stdio(0);

	int R,C,U,P,M;

	freopen("dc.in","r",stdin);

	cin >> R >> C >> U >> P >> M;
	//cout << R << " " << C << " " << U << " " << P << " " << M << endl;
	memset(used,false,sizeof used);

	for(int i = 0,r,c;i < U;++i){
		cin >> r >> c;
		used[r][c] = true;
	}

	for(int i  = 0,r,c;i < M;++i){
		cin >> z[i] >> cap[i];
		//cout << z[i] << " " << cap[i] << endl;
	}

	fclose(stdin);

	freopen("out.txt","r",stdin);

	string line;
	getline(cin,line);

	for(int i = 0;i < M;++i){
		getline(cin,line);

		if(line[0] == 'x'){
			ar[i] = -1;
			as[i] = -1;
			ap[i] = -1;
		}else{
			istringstream is(line);
			is >> ar[i] >> as[i] >> ap[i];

			bool ok = mark(ar[i],as[i],z[i]);

			if(!ok){
				cout << ":( " << i << endl;
				return 0;
			}
		}
	}

	int ans = -1;

	for(int i = 0;i < P;++i){
		int best = -1;

		for(int j = 0;j < R;++j){
			int sum = 0;

			for(int k = 0;k < M;++k){
				if(ar[k] != -1 && ar[k] != j && ap[k] == i)
					sum += z[k];
			}
			//cout << sum << endl;
			if(best == -1) best = sum;
			else best = min(best,sum);
		}

		if(ans == -1) ans = best;
		else ans = min(ans,best);
	}

	cout << ":) " << ans << endl;

	fclose(stdin);

	return 0;
}