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

//persistent segment tree
struct vertex{
	vertex *l,*r;
	int sum;
	
	vertex(int val):l(NULL),r(NULL),sum(val){}
	vertex(vertex* left_ptr, vertex* right_ptr):l(left_ptr),r(right_ptr),sum(0){
		if(left_ptr)sum+=left_ptr->sum;
		if(right_ptr)sum+=right_ptr->sum;
	}
};

vertex* build(vector<int> &a,int low,int high){
	if(low==high) return new vertex(a[low]);
	int mid=(low+high)/2;
	return new vertex(build(a,low,mid),build(a,mid+1,high));
}

int find(vertex* ptr,int l,int r,int low,int high){
	if(low>r||high<l)return 0;
	if(low>=l&&high<=r)return ptr->sum;
	int mid=(low+high)/2;
	return find(ptr->l ,l,r,low,mid)+find(ptr->r, l,r,mid+1,high);
}

vertex* update(vertex* ptr,int ix,int val,int low,int high){
	if(low==high)return new vertex(val);
	int mid=(low+high)/2;
	if(ix<=mid)return new vertex(update(ptr->l, ix,val,low,mid),ptr->r);
	return new vertex(ptr->l,update(ptr->r, ix,val,mid+1,high));
}

int main(){
	
}


