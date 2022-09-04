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
 
//push_relabel algorithm -> O(V^2 * E)
 
class max_flow_push_relabel{
	public:
	vector<vector<pi> > g;	//{v,w} v-> to_vertex  w-> capacity of (u,v) and g id directed graph
	
	int n; //n-> no of vertex
	int s,t; //s->source t->sink
	
	vector<vector<int> > capacity,flow;
	vector<int> height, excess, seen;
	queue<int> excess_vertices;
	int INF=1000000000; //change as required
	
	void build(){
		flow = vector<vi>(n+1,vi(n+1,0));
		capacity = vector<vi>(n+1,vi(n+1,0));
		height=vi(n+1,0);
		excess = vi(n+1,0);
		seen=vi(n+1,1);
		
		height[s]=n;
		excess[s]=INF;
		
		fo(u,1,n){
			for(auto pr:g[u]){
				int v=pr.F,w=pr.S;
				capacity[u][v]+=w;
			}
		}
	}
	max_flow_push_relabel(vector<vector<pi> > &gg,int nn,int ss,int tt){
		g=gg;
		n=nn;
		s=ss;
		t=tt;
		build();
	}
	
	void push(int u, int v){
	    int d = min(excess[u], capacity[u][v] - flow[u][v]);
	    flow[u][v] += d;
	    flow[v][u] -= d;
	    excess[u] -= d;
	    excess[v] += d;
	    if (d && excess[v] == d) excess_vertices.push(v);
	}
	
	void relabel(int u){
		int d=INF;
		fo(i,1,n){
			if(capacity[u][i] - flow[u][i] > 0) d=min(d,height[i]);
		}
		if(d<INF) height[u]=d+1;
	}
	
	void discharge(int u){
		while(excess[u]>0){
			
			if(seen[u]<=n){
				int v=seen[u];
				if(capacity[u][v]-flow[u][v]>0 && height[u]>height[v]){
					push(u,v);
				}
				else{
					seen[u]++;
				}
			}
			else{
				relabel(u);
				seen[u]=1;
			}
		}
	}
	
	int max_flow(){
		fo(i,1,n){
			if(i!=s)push(s,i);
		}
		
		while(!excess_vertices.empty()){
			int u=excess_vertices.front();
			excess_vertices.pop();
			if(u!=s && u!=t) discharge(u);
		}
		int max_flow=0;
		fo(i,1,n){
			max_flow+=flow[i][t];
		}
		return max_flow;
	}
		
};
 
