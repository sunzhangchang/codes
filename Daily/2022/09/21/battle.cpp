#include<bits/stdc++.h>
using namespace std;
#define double long double
const int N=505;
int n,K;
double f[N][N][2],a[N],g01[N][N],g10[N][N];
int main(){
	freopen("battle.in","r",stdin);
	freopen("battle.out","w",stdout);
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++)scanf("%Lf",&a[i]);
	for(int i=1;i<=n;i++)f[i][i][0]=f[i][i][1]=1;
	for(int i=1;i<n;i++){
		f[i][i+1][0]=a[i]/(a[i]+a[i+1]);
		f[i][i+1][1]=a[i+1]/(a[i]+a[i+1]);
		g01[i][i+1]=g10[i][i+1]=1;
	}
	for(int len=3;len<=n;len++)
		for(int l=1;l<=n-len+1;l++){
			int r=l+len-1;
			for(int i=l;i<=r-1;i++)f[l][r][0]+=f[l][i][0]*f[i+1][r][1]*a[l]/(a[l]+a[r]);
			for(int j=l;j<r;j++)f[l][r][0]+=g01[l][j]*f[j][r][0]*a[l]/(a[l]+a[j]);
			for(int i=l+1;i<=r;i++)f[l][r][1]+=f[l][i-1][0]*f[i][r][1]*f[l][l][1]*a[r]/(a[r]+a[l]);
			for(int j=r;j>l;j--)f[l][r][1]+=g10[j][r]*f[l][j][1]*a[r]/(a[r]+a[j]);
			f[l][r][1]/=(len-1);f[l][r][0]/=(len-1);
			for(int i=l+1;i<=r;i++)g10[l][r]+=f[l][i-1][0]*f[i][r][1];
			for(int i=l;i<r;i++)g01[l][r]+=f[l][i][0]*f[i+1][r][1];
		}
	double ans=f[1][K][1]*f[K][n][0];
	printf("%.17Lf",ans);
}
/*
#include<bits/stdc++.h>
using namespace std;
#define double long double
const int N=505;
int n,K;
double f[N][N][2],a[N];
int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++)scanf("%Lf",&a[i]);
	for(int i=1;i<=n;i++)f[i][i][0]=f[i][i][1]=1;
	for(int i=1;i<n;i++){
		f[i][i+1][0]=a[i]/(a[i]+a[i+1]);
		f[i][i+1][1]=a[i+1]/(a[i]+a[i+1]);
	}
	for(int len=3;len<=n;len++)
		for(int l=1;l<=n-len+1;l++){
			int r=l+len-1;
			for(int j=l;j<=r;j++){
				for(int i=l;i<=min(j,r-1);i++)
					f[l][r][0]+=f[l][i][0]*f[i+1][j][1]*f[j][r][0]*a[l]/(a[l]+a[j]);
			for(int j=r;j>=l;j--)
				for(int i=max(j,l+1);i<=r;i++)
					f[l][r][1]+=f[j][i-1][0]*f[i][r][1]*f[l][j][1]*a[r]/(a[r]+a[j]);
			f[l][r][1]/=(len-1);f[l][r][0]/=(len-1);
		}
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			for(int k=0;k<=1;k++)
				printf("%d %d %d %.6Lf\n",i,j,k,f[i][j][k]);
	double ans=f[1][K][1]*f[K][n][0];
	printf("%.17Lf",ans);
}
*/
