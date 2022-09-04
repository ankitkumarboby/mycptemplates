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

//Generalized Segment Tree
struct node{
	//make node as required
};

node merge(node n1, node n2){
	//merge as requied
}

class seg_tree{
	public:
	int n;
	vector<node> a,st;
	node empty_node;
	
	void build(int ind,int low,int high){
		if(low==high){
			st[ind]=a[low];
			return;
		}
		int mid=(low+high)/2;
		build(2*ind,low,mid);
		build(2*ind+1,mid+1,high);
		st[ind]=merge(st[2*ind],st[2*ind+1]);
	}
		
	seg_teee(vector<node> vec,int nn){
		n=nn;
		a=vec;
		st.resize(4*n);  //change if required
		//make empty_node
	}	
	
	void update(int x,node val,int ind,int low,int high){
		if(x<low || x>high)return;
		if(low==high){
			st[ind] = val;
			return;
		}
		int mid=(low+high)/2;
		update(x,val,2*ind,low,mid);
		update(x,val,2*ind+1,mid+1,high);
		st[ind]=merge(st[2*ind],st[2*ind+1]);
	}
	
	node find(int l,int r,int ind,int low,int high){
		if(l>high || r<low) return empty_node;
		if(l>=low && r<=high) return st[ind];
		int mid=(low+high)/2;
		return merge(
			find(l,r,2*ind,low,mid),
			find(l,r,2*ind+1,mid+1,high)
		);
	}
};

int main(){
	fastio
	
}







