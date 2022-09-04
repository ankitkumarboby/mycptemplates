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
#define   mymax                       100000000
#define   mymin                      -100000000
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
vector<int> bfs01(vector<pair<int,int> > g[],int n,int u){
	vector<int> dis;      //change if dis > 1e9
	vector<int> parent;
	
	parent.resize(n+1);
	dis.resize(n+1);
	
	fo(i,1,n)dis[i]=mymax;
	fo(i,1,n)parent[i]=-1;
	deque<int> qu;    //changable
	qu.push_back(u);
	dis[u]=0;
	parent[u]=u;
	while(!qu.empty()){
		int v=qu.front();
		qu.pop_front();
		for(auto pr:g[v]){
			if(dis[v]+pr.S<dis[pr.F]){
				dis[pr.F]=dis[v]+pr.S;
				parent[pr.F]=v;
				if(pr.S==1) qu.push_back(pr.F);
				else qu.push_front(pr.F);
			}
		}
	}
	return dis;
}

int main(){
	//fastio
	int n,m;cin>>n>>m;
	vector<pi> g[n+1];
	fo(i,1,m){
		int u,v,w;cin>>u>>v>>w;
		g[u].pb({v,w});
	}
	int q;cin>>q;
	while(q--){
		int source,sink;cin>>source>>sink;
		vi dis=bfs01(g,n,source);
		cout<<dis[sink]<<'\n';
		/*vi path=dijkstra(g,n,source);
		int u=sink;
		if(path[u]==-1){
			cout<<"NO PATH\n";continue;
		}
		vi ans;
		while(path[u]!=u){
			ans.pb(u);u=path[u];
		}
		ans.pb(u);
		reverse(ans.begin(),ans.end());
		for(auto i:ans)cout<<i<<' ';
		cout<<'\n';
		*/
	}
	
}



