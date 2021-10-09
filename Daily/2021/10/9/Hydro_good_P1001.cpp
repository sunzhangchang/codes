#include<bits/stdc++.h>

const int N=1e5+10,Mod=1e9+7;

int a[N],b[N];
bool vis[N];
int n,ans1,ans2=1;

int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=1; i<=n; i++) scanf("%d",&b[i]);
	for(int i=1; i<=n; i++) if(a[i]==b[i]&&a[i]<=n) vis[a[i]]=true;
	for(int i=0; i<=n; i++) if(!vis[i]) { ans1=i; break; }
	int sum=n;
	for(int i=1; i<=n; i++) if((a[i]==ans1&&b[i]!=ans1)||(a[i]!=ans1&&b[i]==ans1)) --sum;
	for(int i=1; i<=sum; i++) ans2=ans2*2%Mod;
	printf("%d %d\n",ans1,ans2);
	return 0;
}
