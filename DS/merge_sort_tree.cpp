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
//merge_sort_tree
template<typename T>
class merge_sort_tree{
	public:
	int n;	
	vector<T> &a;
	vector<T> *st;
	void build(int ind,int low,int high){
		if(low==high){
			st[ind].resize(1,a[low]);return;
		}
		int mid=(low+high)/2;
		build(2*ind,low,mid);
		build(2*ind+1,mid+1,high);
		//now merging
		st[ind].resize(0);
		int l1=st[2*ind].size(),l2=st[2*ind+1].size();
		int i=0,j=0;
		while(i<l1&&j<l2){
			if(st[2*ind][i]<st[2*ind+1][j]){
				st[ind].pb(st[2*ind][i]);i++;
			}
			else{
				st[ind].pb(st[2*ind+1][j]);j++;
			}
		}
		while(i<l1){
			st[ind].pb(st[2*ind][i]);i++;	
		}
		while(j<l2){
			st[ind].pb(st[2*ind+1][j]);j++;	
		}
	}
	
	merge_sort_tree(vector<T> &v,int len):a(v){
		n=len;
		st=new vector<T>[4*n];    //change in case of MLE
		build(1,1,n);  
	}
	//LB-> number of elements less than x in the range [l to r]
	//UB-> number of elements less than or equal to x in the range [l to r]
	int LB(int l,int r,T x,int ind,int low,int high){
		if(low>r||high<l)return 0;
		if(low>=l&&high<=r){
			return int(lower_bound(st[ind].begin(),st[ind].end(),x)-st[ind].begin());
		}
		int mid=(low+high)/2;
		return LB(l,r,x,2*ind,low,mid)+LB(l,r,x,2*ind+1,mid+1,high);
	}

	int UB(int l,int r,T x,int ind,int low,int high){
		if(low>r||high<l)return 0;
		if(low>=l&&high<=r){
			return int(upper_bound(st[ind].begin(),st[ind].end(),x)-st[ind].begin());
		}
		int mid=(low+high)/2;
		return UB(l,r,x,2*ind,low,mid)+UB(l,r,x,2*ind+1,mid+1,high);
	}
};

int main(){
	//fastio
	int n;cin>>n;vi a(n+1);fo(i,1,n)cin>>a[i];merge_sort_tree<int> mst(a,n);
	int q;
	cin>>q;
	while(q--){
		int l,r,x;
		cin>>l>>r>>x;
		cout<<mst.LB(l,r,x,1,1,n)<<"   "<<mst.UB(l,r,x,1,1,n)<<'\n';
	}
	
	return 0;
}
