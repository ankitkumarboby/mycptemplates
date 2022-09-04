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

template<typename T>
class fenwick_tree{
	public:
	int n;
	vector<T> a,BIT;
	
	fenwick_tree(vector<T> &aa,int nn){
		n=nn;
		a=aa;
		BIT.resize(n+1,0);
		for(int i=1;i<=n;++i)add(a[i],i);
	}
	void add(T val,int ix){
		for(int i=ix;i<=n;i += i&-i)BIT[i]+=val;
	}	
	T get(int ix){
		T res=0;
		for(int i=ix;i>0;i -= i&-i)res+=BIT[i];
		return res;
	}
	T get(int l,int r){
		return get(r)-get(l-1);
	}
};
int main(){
	srand(time(0));
	int n;
	cin>>n;
	while(n--){
		int len = rand()%500;
		vector<int> a(len+1,0);
		fo(i,1,len)a[i] = rand()%100000;
		int ans1=0,ans2=0;
		fo(i,1,len)ans1+=a[i];
		fenwick_tree<int> o(a,len);
		ans2=o.get(1,len);
		if(ans1 == ans2)cout<<"OK\n";
		else cout<<"FAILED\n";
		
	}
}




