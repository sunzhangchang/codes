#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define nade pair<int,pair<ll,ll> >
#define mkp make_pair
const int N=4e5+5;
map<nade,ll>mp;
int T,n,a[N],p[N];ll sum;
ll dfs(int t,ll sum,ll mul){
	if(sum==mul)return mul;
	if(t==n+1)return 0;
	nade u=mkp(t,mkp(sum,mul));
	if(mp.count(u))return mp[u];
	ll rec=dfs(t+1,sum,mul);
	for(int i=1;i<=a[t];i++){
		mul*=p[t];sum-=p[t];
		if(sum<mul)break;
		rec=max(rec,dfs(t+1,sum,mul));
	}
	mp[u]=rec;
	return rec;
}
int main(){
	freopen("poker.in","r",stdin);
	freopen("poker.out","w",stdout);
	scanf("%d",&T);
	for(int Case=1;Case<=T;Case++){
		mp.clear();
		scanf("%d",&n);sum=0;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&p[i],&a[i]);
			sum+=a[i]*p[i];
		}
		printf("Case #%d: %lld\n",Case,dfs(1,sum,1));
	}
}
