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
#define   mymax                       1000000000000000001
#define   mymin                      -1000000000000000001
#define   mod                         (ll)1000000007ll
#define   SZ                          sizeof
#define   test(t_case)                "Case #"<<t_case<<": "
//#include <unordered_set>
using namespace std;
//int dx[]={0,1,0,-1};
//int dy[]={1,0,-1,0};
//int dx[]={0,1,1,-1,0,-1,1,-1};
//int dy[]={1,0,1,0,-1,-1,-1,1};
//int dx[]={1,1,2,2,-1,-1,-2,-2};
//int dy[]={2,-2,1,-1,2,-2,1,-1};

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
    if(r>n || r<0)return 0;
    if(n<0)return 0;
    ll n1=1,d1=1,d2=1;
    n1=fact(n,m);d1=fact(r,m);d2=fact(n-r,m);
    ll ans=mod_inverse((d1*d2)%m,m);
    ans=(ans*n1)%m;
    return ans;
}

/***************************code begins here*****************************/

pair<vi,vi> manacher(string s){
	// dp1 --> odd length palindrome [t]+s[i]+[rev(t)] --> dp1[i] = 1+len(t)
	// dp2 --> even length palindrome [t+s[i-1]] + [s[i]+t] , s[i-1]==s[i]  --> dp2[i] = 1+len(t)
	int n =s.size();
	vi dp1(n),dp2(n);
	for(int i=0,l=0,r=-1;i<n;++i){
		if(i>r)dp1[i]=1;
		else dp1[i]=min(r-i+1 , dp1[l-(i-l)]);
		
		while(0<=(i-dp1[i]) && (i+dp1[i])<n && (s[i-dp1[i]]==s[i+dp1[i]])){
			dp1[i]++;
		}
		if(i+dp1[i]-1 > r){
			r=i+dp1[i]-1;
			l=i;
		}
	}
	for(int i=0,l=0,r=-1;i<n;++i){
		if(i>r)dp2[i]=0;
		else dp2[i]=min(r-i+1,dp2[l-(i-l)]);
		
		while(0<=(i-1-dp2[i]) && (i+dp2[i])<n && (s[i-1-dp2[i]] == s[i+dp2[i]])){
			dp2[i]++;
		}
		if(i+dp2[i]-1 > r){
			r=i+dp2[i]-1;
			l=i;
		}
	}
	return {dp1,dp2};
}


int main(){
	fastio
	
}




