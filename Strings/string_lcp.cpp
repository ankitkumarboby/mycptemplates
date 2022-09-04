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
//radix_sort
void radix_sort(vector<pair<pair<int,int>,int> > &a){
	int n=a.size();
	{
		vi cnt(n,0);
		fo(i,0,n-1)cnt[a[i].F.S]++;
		vi pos(n,0);
		pos[0]=0;
		fo(i,1,n-1)pos[i]=pos[i-1]+cnt[i-1];
		vector<pair<pair<int,int>,int> > new_a(n);
		fo(i,0,n-1){
			new_a[pos[a[i].F.S]]=a[i];
			pos[a[i].F.S]++;
		}
		a=new_a;
	}
	{
		vi cnt(n,0);
		fo(i,0,n-1)cnt[a[i].F.F]++;
		vi pos(n,0);
		pos[0]=0;
		fo(i,1,n-1)pos[i]=pos[i-1]+cnt[i-1];
		vector<pair<pair<int,int>,int> > new_a(n);
		fo(i,0,n-1){
			new_a[pos[a[i].F.F]]=a[i];
			pos[a[i].F.F]++;
		}
		a=new_a;
	}
}



//suffix_array
pair<pair<vi,vi>,vi> suffix_array(string s){
	s+="$";
	int n=s.size();
	vector<int> p(n),c(n);  
	//p->suffix array : indices of the suffixes in lexographical sorted order
	//c-> class array: class of the suffixes
	{
		vector<pair<char,int> > a(n);
		fo(i,0,n-1)a[i]={s[i],i};
		sort(all(a));
		fo(i,0,n-1)p[i]=a[i].S;
		c[a[0].S]=0;
		fo(i,1,n-1){
			if(a[i].F==a[i-1].F)c[a[i].S]=c[a[i-1].S];
			else c[a[i].S]=c[a[i-1].S]+1;
		}
	}
	int k=0;
	while((1<<k)<n){
		vector<pair<pair<int,int>,int> > a(n);
		fo(i,0,n-1)a[i]={{c[i],c[(i+(1<<k))%n]},i};
		//sort(all(a));
		radix_sort(a);
		fo(i,0,n-1)p[i]=a[i].S;
		c[a[0].S]=0;
		fo(i,1,n-1){
			if(a[i].F==a[i-1].F)c[a[i].S]=c[a[i-1].S];
			else c[a[i].S]=c[a[i-1].S]+1;
		}
		k++;
	}
	
	vector<int> lcp(n,0);
	{
		int k=0;
		fo(i,0,n-2){
			int x=c[i];
			int j=p[x-1];
			while(s[i+k]==s[j+k])k++;
			lcp[x]=k;
			k=max(0,k-1);
		}
	}
	
	return {{p,c},lcp};             //return as required p-> if suffix_array or c-> class_array
}

template<typename T>
class sparse_table{
	public:
	vector<T> a;
	int n,h;
	vector<vector<T> > dp;
	void build(){
		fo(i,1,n)dp[i][0]=a[i];
		for(int j=1;(1<<j)<=n;++j){
			int k=(1<<j);
			for(int i=1;i+k-1<=n;++i){
				dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);  //changable
			}
		}
	}
	
	sparse_table(){}
	
	sparse_table(vector<T> aa,int len):a(aa){
		n=len;
		h=ceil(log2(n));
		dp=vector<vector<T> >(n+1,vector<T>(h+1,0));
		build();
	}
	
	T find(int l,int r){
		if(l>r)swap(l,r);
		int d=(r-l+1);
		int lg_d=floor(log2(d));
		return min(dp[l][lg_d],dp[r-(1<<lg_d)+1][lg_d]);     //changable
	}
		
};

//string LCP
class string_lcp{
	public:
	string &s;
	vector<int> p,c,lcp;   //size =n+1  because of extra charecter '$'
	int n;
	sparse_table<int> s_table;     //comment if not required
	
	string_lcp(string ss):s(ss){
		n=s.size();
		pair<pair<vi,vi>,vi> prr=suffix_array(s);
		p=prr.first.first;
		c=prr.first.second;
		lcp=prr.second;
		s_table=sparse_table<int>(lcp,n);
	}
	
	int find_lcp(int i,int j){     //i,j 0-indexed lcp(s[i...n-1] ans s[j...n-1])
		if(i==j)return n-i;
		i=c[i];
		j=c[j];
		if(i>j)swap(i,j);
		i++;
		return s_table.find(i,j);
	}
		
};
int main(){
	//fastio
	string s;
	cin>>s;
	int n=s.size();
	string_lcp o(s);
	int t;cin>>t;
	while(t--){
		int l,r;
		cin>>l>>r;
		cout<<o.find_lcp(l,r)<<'\n';
	}
}






