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

#define MAXS 700

int R,C,U,P,M;
int z[MAXS],cap[MAXS];
int ar[MAXS],as[MAXS],ap[MAXS];

int best[MAXS];

int score(){
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

	int ans = best[0];

	for(int i = 0;i < P;++i)
		ans = min(ans,best[i]);

	return ans;
}

int worst_score(){
	score();

	int pos = 0;

	for(int i = 1;i < P;++i)
		if(best[i] < best[pos])
			pos = i;

	return pos;
}

int best_score(){
	score();

	int pos = 0;

	for(int i = 1;i < P;++i)
		if(best[i] > best[pos])
			pos = i;

	return pos;
}

int main(){
	ios::sync_with_stdio(0);

	freopen("dc.in","r",stdin);

	cin >> R >> C >> U >> P >> M;

	for(int i = 0,r,c;i < U;++i)
		cin >> r >> c;

	for(int i  = 0,r,c;i < M;++i)
		cin >> z[i] >> cap[i];

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
		}
	}

	fclose(stdin);

	bool found = true;

	for(int it = 0;it < 100 && found;++it){
		int cur = score();

		/*for(int i = 0;i < P;++i)
			cout << best[i] << " ";
		cout << endl;*/

		int x = worst_score();
		found = false;
		//cout << "x = " << x << endl;

		for(int y = 0;y < P && !found;++y){
			int pos = -1;

			for(int i = 0;i < M;++i)
				if(ap[i] == y && (pos == -1 || cap[pos] > cap[i]))
					pos = i;

			if(pos != -1){
				ap[pos] = x;
			
				int now = score();

				if(best[x] > cur && best[y] > cur){
					//cout << y << " " << now << endl;
					found = true;
				}else{
					ap[pos] = y;
				}
			}
		}

		//cout << score() << endl;
	}

	for(int i = 0;i < M;++i){
		if(ar[i] == -1) cout << "x\n";
		else cout << ar[i] << " " << as[i] << " " << ap[i] << '\n';
	}

	return 0;
}