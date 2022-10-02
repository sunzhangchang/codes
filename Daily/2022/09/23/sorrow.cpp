#include <bits/stdc++.h>
#define fre(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)

using namespace std;

int read() {
	int x=0, f=0; char c=getchar();
	while (!isdigit(c)) f|=c=='-', c=getchar();
	while (isdigit(c)) x=(x<<3)+(x<<1)+(c^48), c=getchar();
	return f ? -x : x;
}

const int N=2e5+10;
int n, m;
multiset<int> s[N];

int main() {
	fre(sorrow);
	n=read(), m=read();
	while (m--) {
		int op=read();
		if (op==1) {
			int l=read(), r=read(), k=read();
			for (int i=l; i<=r; i++) s[i].insert(-k);
		}
		else {
			int l=read(), r=read(), mx=-1;
			for (int i=l; i<=r; i++) if (s[i].size()) mx=max(mx, -*s[i].begin());
			if (op==3) printf("%d\n", mx);
			else for (int i=l; i<=r; i++) if (s[i].size() && s[i].count(-mx)) s[i].erase(s[i].find(-mx));
		}
	}
	return 0;
}