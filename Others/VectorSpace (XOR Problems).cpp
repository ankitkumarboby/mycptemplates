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
#define   all(a)                      (a).begin(),(a).end()
#define   F                           first
#define   S                           second
#define   mymax                       100000000
#define   mymin                      -100000000
#define   mod                         1000000007
#define   SZ                          sizeof

//#include <unordered_set>
using namespace std;

//int dx[]={0,1,0,-1}
//int dy[]={1,0,-1,0}
//int dx[]={0,1,1,-1,0,-1,1,-1};
//int dy[]={1,0,1,0,-1,-1,-1,1}
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
ll fact(ll n,ll m){
    if(n<=1)return 1;
    return (fact(n-1,m)*n)%m;
}
ll ncr(ll n,ll r,ll m){
    if(r>n)return 0;
    ll n1=1,d1=1,d2=1;
    n1=fact(n,m);d1=fact(r,m);d2=fact(n-r,m);
    ll ans=mod_inverse((d1*d2)%m,m);
    ans=(ans*n1)%m;
    return ans;
}
int ispal(string s){
    int len=s.size();
    int flag=1;
    for(int i=0;i<len;++i){
        if(s[i]!=s[len-i-1]){
            flag=0;break;
        }
    }
    return flag;
}

ll sroot(ll n,ll low=1,ll high=1e9+1){
    if(low==high)return low;
    if(low==high-1){
        if(high*high<=n)return high;
        else return low;
    }
    ll mid=(low+high)/2;
    ll a=mid*mid;
    if(a>n)return sroot(n,low,mid-1);
    else return sroot(n,mid,high);
}
ll croot(ll n,ll low=1,ll high=1e6+1){
    if(low==high)return low;
    if(low==high-1){
        if(high*high*high<=n)return high;
        else return low;
    }
    ll mid=(low+high)/2;
    ll a=mid*mid*mid;
    if(a>n)return croot(n,low,mid-1);
    else return croot(n,mid,high);

}
pi operator+(pi p1,pi p2){
	return {p1.F+p2.F,p1.S+p2.S};
}
/***************************code begins here*****************************/
int sz=0;
int d=30;  //maximum no if bit in the number
int basis[31]={};
void insert(int mask){
	for(int i=d;i>=0;--i){
		if((mask&(1<<i))==0)continue;
		if(basis[i]==0){
			basis[i]=mask;
			sz++;
			return;
		}
		mask^=basis[i];
	}
}

int main(){
	//fastio
	
}






