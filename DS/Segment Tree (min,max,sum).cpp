#include<bits/stdc++.h>
#define   ll                          long long int
#define   mod                         998244353
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
//#include <unordered_set>
using namespace std;
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
//min seg tree
template<typename T>
class min_seg_tree{
	public:
	int n;
	T mx,mn;
	vector<T> &a;
	vector<T> st;
	void build(int ind,int low,int high){
		if(low==high){
			st[ind]=a[low];return;
		}
		int mid=(low+high)/2;build(2*ind,low,mid);build(2*ind+1,mid+1,high);
		st[ind]=min(st[2*ind],st[2*ind+1]);
	}
	
	min_seg_tree(vector<T> &v,int len):a(v){
		n=len;
		mn=0;             //change
		mx=1000000000;          //change
		st=vector<T>(4*n);  //change size of segment tree if MLE
		build(1,1,n);
	}
	T find(int l,int r,int ind,int low,int high){
		if(low>r||high<l)return mx;
		if(low>=l&&high<=r){
			return st[ind];
		}
		int mid=(low+high)/2;
		return min(find(l,r,2*ind,low,mid),find(l,r,2*ind+1,mid+1,high));
	}
	void update(int x,T val,int ind,int low,int high){
		if(low>x||high<x)return;
		if(low==high){
			st[ind]=val;return;
		}
		int mid=(low+high)/2;
		update(x,val,2*ind,low,mid);
		update(x,val,2*ind+1,mid+1,high);
		st[ind]=min(st[2*ind],st[2*ind+1]);
	}
		
};
//max seg tree
template<typename T>
class max_seg_tree{
	public:
	int n;
	T mx,mn;
	vector<T> &a;
	vector<T> st;
	void build(int ind,int low,int high){
		if(low==high){
			st[ind]=a[low];return;
		}
		int mid=(low+high)/2;build(2*ind,low,mid);build(2*ind+1,mid+1,high);
		st[ind]=max(st[2*ind],st[2*ind+1]);
	}
	
	max_seg_tree(vector<T> &v,int len):a(v){
		n=len;
		mn=0;             //change
		mx=1000000000;          //change
		st=vector<T>(4*n);  //change size of segment tree if MLE
		build(1,1,n);
	}
	T find(int l,int r,int ind,int low,int high){
		if(low>r||high<l)return mn;
		if(low>=l&&high<=r){
			return st[ind];
		}
		int mid=(low+high)/2;
		return max(find(l,r,2*ind,low,mid),find(l,r,2*ind+1,mid+1,high));
	}
	void update(int x,T val,int ind,int low,int high){
		if(low>x||high<x)return;
		if(low==high){
			st[ind]=val;return;
		}
		int mid=(low+high)/2;
		update(x,val,2*ind,low,mid);
		update(x,val,2*ind+1,mid+1,high);
		st[ind]=max(st[2*ind],st[2*ind+1]);
	}
		
};

//sum_seg_tree
template<typename T>
class sum_seg_tree{
	public:
	int n;
	T mx,mn;
	vector<T> &a;
	vector<T> st;
	void build(int ind,int low,int high){
		if(low==high){
			st[ind]=a[low];return;
		}
		int mid=(low+high)/2;build(2*ind,low,mid);build(2*ind+1,mid+1,high);
		st[ind]=st[2*ind]+st[2*ind+1];
	}
	
	sum_seg_tree(vector<T> &v,int len):a(v){
		n=len;
		mn=0;             //change
		mx=1000000000;          //change
		st=vector<T>(4*n);  //change size of segment tree if MLE
		build(1,1,n);
	}
	T find(int l,int r,int ind,int low,int high){
		if(low>r||high<l)return mn;
		if(low>=l&&high<=r){
			return st[ind];
		}
		int mid=(low+high)/2;
		return find(l,r,2*ind,low,mid)+find(l,r,2*ind+1,mid+1,high);
	}
	void update(int x,T val,int ind,int low,int high){
		if(low>x||high<x)return;
		if(low==high){
			st[ind]=val;return;
		}
		int mid=(low+high)/2;
		update(x,val,2*ind,low,mid);
		update(x,val,2*ind+1,mid+1,high);
		st[ind]=st[2*ind]+st[2*ind+1];
	}
		
};

int main(){
	int n;cin>>n;vi a(n+1);fo(i,1,n)cin>>a[i];
	min_seg_tree<int> mnst(a,n);
	max_seg_tree<int> mxst(a,n);
	sum_seg_tree<int> smst(a,n);
	int q;cin>>q;
	while(q--){
		string s;cin>>s;
		if(s=="min"){
			int l,r;cin>>l>>r;
			cout<<mnst.find(l,r,1,1,n)<<'\n';
		}
		else if(s=="max"){
			int l,r;cin>>l>>r;
			cout<<mxst.find(l,r,1,1,n)<<'\n';
		}
		else if(s=="sum"){
			int l,r;cin>>l>>r;
			cout<<smst.find(l,r,1,1,n)<<'\n';
		}
		else{
			int x,val;cin>>x>>val;
			mnst.update(x,val,1,1,n);
			mxst.update(x,val,1,1,n);
			smst.update(x,val,1,1,n);
		}
	}
}
