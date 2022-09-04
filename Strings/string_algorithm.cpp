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
#define   mymax                       1000000000000000
#define   mymin                      -1000000000000000
#define   mod                         1000000007
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

/***************************code begins here*****************************/

vector<int> prefix_function(string &s){
	int n=s.size();
	vector<int> pfun(n,0);
	fo(i,1,n-1){
		int j=pfun[i-1];
		while(j>0&&s[j]!=s[i]){
			j=pfun[j-1];
		}
		if(s[i]==s[j]) j++;
		pfun[i]=j;
	}
	return pfun;
}

vector<int> z_function(string &s){
	int n=s.size();
	vector<int> zfun(n,0);
	for(int i=1,l=0,r=0;i<n;++i){
		if(i<=r) zfun[i]=min(zfun[i-l],r-i+1);
		
		while(i+zfun[i]<n&&s[zfun[i]]==s[i+zfun[i]])
		zfun[i]++;
		
		if(i+zfun[i]-1>r){
			l=i;
			r=i+zfun[i]-1;
		}
	}
	return zfun;
}
int main(){
	//fastio
	int q;
	cin>>q;
	while(q--){
		string s;cin>>s;
		vi pre=prefix_function(s),z=z_function(s);
		cout<<"Prefix Function: ";
		for(auto i:pre)cout<<i<<' ';
		cout<<"\nZ Function: ";
		for(auto i:z)cout<<i<<' ';
		cout<<'\n';
	}
}



