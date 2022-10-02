#include <bits/stdc++.h>
#define fre(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)

using namespace std;

int read() {
	int x=0, f=0; char c=getchar();
	while (!isdigit(c)) f|=c=='-', c=getchar();
	while (isdigit(c)) x=(x<<3)+(x<<1)+(c^48), c=getchar();
	return f ? -x : x;
}

const int N=5e3+10;
int n, a, b, h[N], f[N][N], g[N][N];

void cmp(int i, int j, int x, int y) {
	if (x>f[i][j] || (x==f[i][j] && y>g[i][j])) f[i][j]=x, g[i][j]=y;
}

int main() {
	fre(conqueror);
	int T=read();
	while (T--) {
		n=read(), a=read(), b=read();
		int ans=1e9;
		for (int i=1; i<=n; i++) h[i]=read();
		memset(f, 0, sizeof f), memset(g, 0, sizeof g);
		for (int i=0; i<=5000; i++)
			for (int j=0; j<=5000; j++) {
				if (f[i][j]==n) {ans=min(ans, max(i, j)); break;}
				if (g[i][j]+a>=h[f[i][j]+1]) cmp(i+1, j, f[i][j]+1, 0);
				else cmp(i+1, j, f[i][j], g[i][j]+a);
				if (g[i][j]+b>=h[f[i][j]+1]) cmp(i, j+1, f[i][j]+1, 0);
				else cmp(i, j+1, f[i][j], g[i][j]+b);
			}
		printf("%d\n", ans);
	}
	return 0;
}