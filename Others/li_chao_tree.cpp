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
#define   mod                         (ll)1000000007
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
    if(r>n)return 0;
    ll n1=1,d1=1,d2=1;
    n1=fact(n,m);d1=fact(r,m);d2=fact(n-r,m);
    ll ans=mod_inverse((d1*d2)%m,m);
    ans=(ans*n1)%m;
    return ans;
}
 
/***************************code begins here*****************************/
 
struct line{
	//line of form y=mx+c;
	ll m,c;
	line(ll mm,ll cc){
		m=mm;c=cc;
	}
	line(){
		m=c=0;
	}
	ll value(ll x){
		return m*x+c;
	}
};
 
//max
class li_chao_tree{
	public:
	vector<line> st;
	ll mn,mx;
	
	li_chao_tree(ll mn_,ll mx_){
		mx=mx_;
		mn=mn_;
		st.resize((mx-mn+1)*4,line(0,mymin));
	}
	
	void add_line(line ln,int ind,int low,int high){
		int mid=low+((high-low)/2);
		bool l=(st[ind].c==mymin || ln.value(low)>=st[ind].value(low));
		bool m=(st[ind].c==mymin || ln.value(mid)>=st[ind].value(mid));
		if(m)swap(ln,st[ind]);
		if(low==high)return;
		if(l!=m){
			add_line(ln,2*ind,low,mid);
		}
		else{
			add_line(ln,2*ind+1,mid+1,high);
		}
	}
	
	ll find(ll x,int ind,int low,int high){
		int mid=(low+high)/2;
		if(low==high) return st[ind].value(x);
		if(x<=mid){
			return max(st[ind].value(x),find(x,2*ind,low,mid));
		}
		else{
			return max(st[ind].value(x),find(x,2*ind+1,mid+1,high));
		}
	}
};
