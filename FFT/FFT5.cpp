/*-- ILSH  --*/

// Multipoint evaluation + Divide and Conquer
// Time ( Iterative ) < Time ( Recursive )

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double ld;

#define pb push_back
#define pop pop_back
#define mp make_pair
#define vll vector < ll > 
#define len length 
#define sz size

const ll inf=1e18+1e17;
const ll mod = 998244353;

ll modInverse(ll a,ll m){ll m0=m;ll y=0,x=1;if(m == 1)return 0;while(a> 1){ll q=a/m;ll t=m;m=a%m,a=t;t=y;y=x-q*y;x=t;}if(x<0)x+=m0;return x;}  
ll powm(ll a,ll b){a=a%mod;ll res=1;while(b){if(b&1)res=(res*a)%mod;a=(a*a)%mod;b>>=1;}return (res%mod);}

const ll N = (1<<18)+5;
const ll root= 2192,rooti=modInverse(root,mod);

ll omega[N][2],precomp[N],poll[N],ans;
struct st{ll a, b; };
st store[(N<<1)];
vll polls[(N<<1)];

void rootinit(){
	omega[0][0]=1; omega[0][1]=1; precomp[0]=1;
	for ( ll i=1;i<N;i++){
		omega[i][0]=(omega[i-1][0]*root)%mod;
		omega[i][1]=(omega[i-1][1]*rooti)%mod;
	}
}

void fft( vll &mia, int f){
	ll n=(ll ) mia.size();
	for ( ll i=1,j=0;i<n;i++){
		ll bit=n>>1;
		for (;j&bit;bit>>=1)
			j^=bit;
		j^=bit;
		if ( i<j)
			swap( mia[i],mia[j]);
	}
	for ( ll len=1;(1<<len)<=n;len++){
		ll itr=18-len,z=(1<<len);itr=(1<<itr);
		for ( ll i=0;i<n;i+=z){
			ll pos=0;
			for ( ll j=0;j<z/2;j++){
				ll x=mia[i+j], y = ( mia[i+j+z/2] * omega[pos][f] )%mod;
				mia[i+j]=(x+y>mod?x+y-mod:x+y);
				mia[i+j+z/2]=(x-y<0?x-y+mod:x-y);
				pos+=itr;
			}
		}
	}
	if ( f){
		n=modInverse(n,mod);
		for ( ll &i: mia)
			i=(i*n)%mod;
	}
}
void polymul( vll &lana, vll &mia, int x,ll n=1){
	if (x){
		while (n<(ll)lana.sz()+(ll)mia.sz()){n<<=1;}
		lana.resize(n);mia.resize( n);
	}
	fft(lana,0);
	fft(mia,0);
	for ( ll i=0;i<n;i++)
		lana[i]=(lana[i]*mia[i])%mod;
	fft( lana,1);
}
void norma( vll &v){
	while ( (ll)v.sz()!=0&&v.back()==0)
		v.pop();
}
void inv(vll &v, ll d){
	vll res={modInverse(v[0],mod)};
	ll a=1;
	while  ( a<d){
		vll mia((a*2)), lana(( a*2));
		for ( ll i=0;i<min( (ll)v.sz(),2*a);i++)
			lana[i]=v[i];
		for ( ll i=0;i<a;i++)
			mia[i]=res[i];
		polymul(lana,mia,0,2*a);
		for ( ll i=0;i<2*a;i++)
			if ( i<a)
				lana[i]=mod-lana[i+a];
			else
				lana[i]=0;
		fft( lana,0);
		for ( ll i=0;i<2*a;i++)
			mia[i]=(mia[i]*lana[i])%mod;
		fft( mia,1);
		for ( ll i=0;i<a;i++){
			mia[i+a]=mia[i];
			mia[i]=res[i];
		}
		swap( mia,res);
		a<<=1;
	}
	swap( res,v);
	v.resize(d);
}
void s_Mod(vll &mia,vll &lana){
	ll i=(ll)mia.sz()-1,j=lana.sz()-1;
	while ( i>=j){
		ll x=(mia[i]*modInverse(lana[j],mod))%mod;
		if ( x!=0 )
			for ( ll k=0;k<=j;k++)
				mia[i-k]=(mia[i-k]-(x*lana[j-k])%mod  + mod)%mod;
		mia.pop(); i--;
	}
	norma(mia);
}
void f_Mod(vll &va,vll vb){
	ll n1=(ll)va.sz(),n2=(ll)vb.sz(), d=n1-n2+1;
	if ( d<=0)
		return;
	if ( min( n1,n2)<130){
		s_Mod(va,vb);
		return;
	}
	vll mia(d),lana(d);
	for ( ll i=0;i<d;i++)
		mia[i]=va[n1-i-1];
	for ( ll j=0;j<min( d,(ll)vb.sz());j++)
		lana[j]=vb[n2-j-1];
	inv( lana, d);
	polymul(mia, lana,1);
	reverse( mia.begin(),mia.begin()+d);
	mia.resize( d);
	polymul(mia,vb,1);
	va.resize( n1);
	for ( ll i=0;i<n1;i++)
		va[i]= ( va[i]-mia[i]<0?va[i]-mia[i]+mod:va[i]-mia[i]);
	norma(va);
}
void fast_eval(ll node, vll v,ll start, ll end){
	f_Mod(v,polls[node]);
	if ((ll) v.sz()==1){
		ans=(ans*v[0]*(end-start+1))%mod;
		return;
	}
	ll m=(start+end)/2;
	fast_eval(node*2,v,start, m);
	fast_eval(node*2+1,v,m+1, end);
}
void make (int node, int start, int end){
	if ( start==end){
		polls[node]={-poll[start]+mod,1};
		return;
	}
	int mid=( start+end)/2;
	make( node*2, start, mid);
	make ( node*2+1,mid+1,end);
	if ( node==1)
		return;
	polls[node]=polls[node*2];
	vll temp=polls[node*2+1];
	polymul(polls[node],temp,1);
	norma(polls[node]);
}
void sol_s( int start, int end) {
	int mid=( start+end)/2;
	for ( int i=start;i<=mid;i++)
		for ( int j=mid+1;j<=end;j++)
			ans=(ans*(poll[j]-poll[i])%mod)%mod;
}
void sol_f(int node, int start, int end){
	if ( start==end)
		return;
	int mid=(start+end)/2;
	if ( end-start<150){
		sol_s( start, end);
	}
	else {
		fast_eval((node*2+1)*2,polls[node*2],mid+1,(mid+1+end)/2);
		fast_eval((node*2+1)*2+1,polls[node*2],(mid+1+end)/2+1,end);
	}
	sol_f( node*2,start, mid);
	sol_f( node*2+1, mid+1,end);
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie( NULL);
	cout.tie(NULL);
	
}

