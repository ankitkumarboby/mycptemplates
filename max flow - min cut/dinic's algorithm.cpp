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
 
struct flow_edge{
	int u,v;
	int cap,flow;
	flow_edge(int _u,int _v,int _cap,int _flow=0){
		u=_u;
		v=_v;
		cap=_cap;
		flow=_flow;
	}
};
 
//dinic's algorithm -> O(V^2*E)  for unit edges graph (w(e)=1) --> O(E*sqrt(V))
class max_flow_dinic{
	public:
	vector<vector<pi> > g;  //{v,w} v-> to_vertex  w-> capacity of (u,v) and g is directed graph
	
	int n,m; //n-> no of vertex
	int s,t; //s->source t->sink
	
	int INF=1000000000; //change as required
	vector<flow_edge> edges;
	vector<vector<int> > adj;
	vector<int> level,ptr;
	queue<int> qu;
	
	void build(){
		fo(u,1,n){
			for(pi pr:g[u]){
				add_edge(u,pr.F,pr.S);
			}
		}
	}
	void add_edge(int u,int v,int w){
		edges.pb(flow_edge(u,v,w));
		edges.pb(flow_edge(v,u,0));
		adj[u].pb(m);
		adj[v].pb(m+1);
		m+=2;
	}
	
	max_flow_dinic(vector<vector<pi> > &gg,int nn,int ss,int tt){
		g=gg;
		n=nn;
		s=ss;
		t=tt;
		m=0;
		level.resize(n+1);
		ptr.resize(n+1);
		adj.resize(n+1);
		build();
	}
	
	bool bfs(){
		while(!qu.empty()){
			int u=qu.front();
			qu.pop();
			for(int id:adj[u]){
				if(edges[id].cap - edges[id].flow ==0)continue;
				if(level[edges[id].v] != -1)continue;
				level[edges[id].v] = level[u]+1;
				qu.push(edges[id].v);
			}
		}
		return (level[t]!=-1);
	}
	
	int dfs(int u,int pushed){
		if(pushed == 0)return 0;
		if(u==t) return pushed;
		int lim=adj[u].size();
		for(int& cid=ptr[u];cid<lim;cid++){
			int id=adj[u][cid];
			int v=edges[id].v;
			if(level[u]+1!=level[v] || edges[id].cap-edges[id].flow==0)
			continue;
			int tr=dfs(v,min( pushed, edges[id].cap-edges[id].flow));
			if(tr==0)continue;
			edges[id].flow+=tr;
			edges[id^1].flow-=tr;
			return tr;
		}
		return 0;
	}
	
	int max_flow(){
		int flow=0;
		while(true){
			fill(all(level),-1);
			level[s]=0;
			qu.push(s);
			if(!bfs()) break;
			fill(all(ptr),0);
			while(int pushed = dfs(s,INF)){
				flow+=pushed;
			}
		}
		return flow;
	}
};
 
