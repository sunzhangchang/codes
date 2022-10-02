#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define Mp make_pair
#define eb emplace_back
#define fir(x, y, z) for(int x = (y); x <= (z); ++ x)
#define fdr(x, y, z) for(int x = (y); x >= (z); -- x)
#define fre(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)

namespace io {
	const int n = 1e6;
	char c, b[n], *i, *j;
	inline char gc() {
		if (i == j) {
			j = (i = b) + fread(b, 1, n, stdin);
			if (i == j) return EOF;
		} return *i ++;
	}
	#define gc getchar
	template <typename T = int>
	inline T read() {
		T s = 0; int x = 0;
		while (!isdigit(c = gc())) x |= c == '-';
		for (; isdigit(c); c = gc())
			s = (s << 1) + (s << 3) + (c & 15);
		return x ? - s : s;
	}
}

using io :: read;

const int N = 105;

int m, cnt, a[N], ans, Sum[N];

inline void dfs(int x, int sum, int mul) {
	if (mul > sum + Sum[x]) return;
	if (x > cnt) {
		if (sum == mul)
			ans = max(ans, sum);
		return;
	}
	dfs(x + 1, sum + a[x], mul);
	dfs(x + 1, sum, mul * a[x]);
}

signed main() {
	fre(poker);
	int _ = read();
	fir (T, 1, _) {
		m = read();
		cnt = 0;
		fir (i, 1, m) {
			int p = read(), x = read();
			fir (j, 1, x) a[++ cnt] = p;
		}
		Sum[cnt + 1] = 0;
		fdr (i, cnt, 1) Sum[i] = Sum[i + 1] + a[i];
		ans = 0;
		dfs(1, 0, 1);
		printf("Case #%d: %d\n", T, ans);
	}
	return 0;
}
/*
4
5
2 2
3 1
5 2
7 1
11 1
1
17 2
2
2 2
3 1
1
2 7
*/
