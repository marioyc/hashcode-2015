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

int R,C,U,P,M;;
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

pair<int, int> orderR[MAXR];

void calc_rows(){
	for(int i = 0;i < R;++i){
		int cont = 0;

		for(int j = 0;j < C;++j)
			if(!used[i][j])
				++cont;

		orderR[i] = make_pair(cont,i);
	}

	sort(orderR,orderR + R);
}

int best[MAXS];

int worst_score(){
	for(int i = 0;i < P;++i){
		best[i] = -1;

		for(int j = 0;j < R;++j){
			int sum = 0;

			for(int k = 0;k < M;++k){
				if(ar[k] != -1 && ar[k] != j && ap[k] == i)
					sum += cap[k];
			}
			//cout << sum << endl;
			if(best[i] == -1) best[i] = sum;
			else best[i] = min(best[i],sum);
		}
	}

	int pos = 0;

	for(int i = 1;i < P;++i)
		if(best[i] < best[pos])
			pos = i;

	return pos;
}

int main(){
	ios::sync_with_stdio(0);

	cin >> R >> C >> U >> P >> M;

	for(int i = 0,r,c;i < U;++i){
		cin >> r >> c;
		used[r][c] = true;
	}

	memset(ar,-1,sizeof ar);
	memset(as,-1,sizeof as);

	pair< double , int> order[M];

	for(int i  = 0,r,c;i < M;++i){
		cin >> z[i] >> cap[i];
		order[i] = make_pair((double)cap[i] * cap[i] * cap[i] * cap[i] / z[i],i);
	}

	sort(order,order + M);

	calc_rows();

	for(int i = 0;i < M;++i){
		bool found = false;
		int ind = order[M - 1 - i].second;

		for(int j = 0;j < R && !found;++j){
			int r = (i + j) % R;//orderR[j].second;

			for(int k = 0;k + z[ind] <= C && !found;++k){
				if(check(r,k,z[ind])){
					ar[ind] = r;
					as[ind] = k;
					found = true;
					mark(r,k,z[ind]);
				}
			}
		}

		//calc_rows();
	}

	//int sum[P][R];
	//memset(sum,0,sizeof sum);

	for(int i = 0,pos = 0,done = 0,r;i < M;++i){
		int ind = order[M - 1 - i].second;

		if(ar[ind] != -1){
			if(done < 250) pos = (pos + 1) % P,++done;
			else pos = worst_score();//(pos + 1) % P;
			/*pos = 0; r = 0;

			for(int j = 0;j < P;++j)
				for(int k = 0;k < R;++k)
					if(sum[j][k] < sum[pos][r]){
						pos = j;
						r = k;
					}
			*/
			ap[ind] = pos;
			//sum[pos][r] += cap[ind];
		}
	}

	for(int i = 0;i < M;++i){
		if(ar[i] == -1) cout << "x\n";
		else cout << ar[i] << " " << as[i] << " " << ap[i] << '\n';
	}

	return 0;
}