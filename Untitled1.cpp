#include<bits/stdc++.h>
#define   ll                          long long int
#define   fo(number1,number2,number3) for(int number1=number2;number1<=number3;++number1)
#define   pi                          pair<int,int>
#define   vi                          vector<int>
#define   pb                          push_back
#define   fastio                      ios_base::sync_with_stdio(false);cin.tie(NULL);
#define   cps                         CLOCKS_PER_SEC
#define   decimal(k)                  fixed<<setprecision(k)
#define   PI                          3.14159265359
#define   F                           first
#define   S                           second
#define   all(A)                      (A).begin(),(A).end()
#define   mymax                       1000000000000000001ll
#define   mymin                      -1000000000000000001ll
#define   mod                         1000000007ll
#define   SZ                          sizeof
#define   test(t_case)                "Case #"<<t_case<<": "
#define   trace(x)                    cout<<#x<<": "<<x<<" "<<endl
#define   trace2(x,y)                 cout<<#x<<": "<<x<<" | "<<#y<<": "<<y<<endl
#define   trace3(x,y,z)               cout<<#x<<":" <<x<<" | "<<#y<<": "<<y<<" | "<<#z<<": "<<z<<endl
#define   trace4(a,b,c,d)             cout<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl
using namespace std;
//int dx[]={0,1,0,-1};
//int dy[]={1,0,-1,0};
//int dx[]={0,1,1,-1,0,-1,1,-1};
//int dy[]={1,0,1,0,-1,-1,-1,1};
//int dx[]={1,1,2,2,-1,-1,-2,-2};
//int dy[]={2,-2,1,-1,2,-2,1,-1};


ll fact[100010],fact_inv[100010];

ll power(ll x,ll y,ll m){            //power(x,y)=x^y  %m;
    if(y==0)return 1;
    ll a=power(x,y/2,m);
    if(y%2){
        return (a*((a*x)%m))%m;
    }
    else{
        return (a*a)%m;
    }
}
ll mod_inverse(ll x,ll m){
    return power(x,m-2,m);
}

ll ncr(ll n,ll r,ll m){
    if(r>n || r<0)return 0;
    if(n<0)return 0;
    ll n1=1,d1=1,d2=1;
    n1=fact[n];
	d1=fact_inv[r];
	d2=fact_inv[n-r];
    ll ans=(d1*d2)%m;
    ans=(ans*n1)%m;
    return ans;
}
void pre_compute(){
	int mx=100001;
	fact[0]=1ll;
	fo(i,1,mx){
		fact[i] = (fact[i-1]*((ll)i))%mod;
	}
	fo(i,0,mx){
		fact_inv[i] = mod_inverse(fact[i],mod);
	}
}
/***************************code begins here*****************************/

class solver{
	public:

	void solve(int test_){
		int n,p;
		cin>>n>>p;
		vector<vector<ll> > a(n+1,vector<ll>(p+1,0ll));
		vector<vector<ll> > dp(n+1,vector<ll>(p+1,0ll));
		fo(i,1,n)fo(j,1,p)cin>>a[i][j];
		fo(i,1,n){
			sort(a[i].begin()+1,a[i].end());
		}
		for(int i=n;i>0;--i){
			ll l,r;
			l=r=mymax;
			if(i!=n){
				fo(j,1,p){
					l=min(l,abs(a[i][1]-a[i+1][j])+dp[i+1][j]);
					r=min(r,abs(a[i][p]-a[i+1][j])+dp[i+1][j]);
				}
			}
			else{
				l=r=0ll;
			}
			fo(j,1,p){
				ll li,ri;
				li=abs(a[i][j]-a[i][p])+abs(a[i][p]-a[i][1])+l;
				ri=abs(a[i][j]-a[i][1])+abs(a[i][p]-a[i][1])+r;
				dp[i][j]=min(li,ri);
			}
		}
		ll ans=a[1][1]+dp[1][1];
		cout<<test(test_)<<ans<<'\n';
	}
};

int main(){
	fastio
//	pre_compute();
	int test=1;
	cin>>test;
	fo(i,1,test){
		solver o;
		o.solve(i);
	}
}







