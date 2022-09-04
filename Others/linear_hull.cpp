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
 
bool cmp_line(line& l1,line& l2){
	return l1.m<=l2.m;
}
 
class linear_min_hull{
	public:
	//in min hull slopes are in order: m1>=m2>=m3>=m4>=...mk   ie. non-increasing
	deque<line> qu_line;
	deque<ll> qu;
	ll min_x,max_x;  //[min_x,max_x] is the range of operations
	
	linear_min_hull(ll mn,ll mx){
		min_x=mn;max_x=mx;
	}
	
	void insert_back(line l){
		// slope(back) >= l.m
		line t=qu_line.back();
		ll p=qu.back();
		
		while(qu.size()>1 && ( (l.c-t.c) <= p*(t.m-l.m) )){
			qu.pop_back();
			qu_line.pop_back();
			t=qu_line.back();
			p=qu.back();
		}
		
		t=qu_line.back();
		if(t.m == l.m){
			if(l.c<=t.c){
				qu_line.pop_back();
				qu_line.push_back(l);
			}
			return;
		}
		double num=l.c-t.c,denum=t.m-l.m;
		ll x = ceil(num/denum);
		
		qu_line.push_back(l);
		qu.push_back(x);
	}
	
	void insert_front(line l){
		// l.m >= slope(front)
		line t=qu_line.front();
		ll p=max_x;
		if(qu.size()>1){
			p=qu.at(1)-1;
		}
		while(qu.size()>1 && ( (t.c-l.c) >= p*(l.m-t.m) )){
			qu.pop_front();
			qu_line.pop_front();
			t=qu_line.front();
			p=max_x;
			if(qu.size()>1){
				p=qu.at(1)-1;
			}
		}
		
		t=qu_line.front();
		if(t.m == l.m){
			if(t.c>=l.c){
				qu_line.pop_front();
				qu_line.push_front(l);
			}
			return;
		}
		double num=t.c-l.c,denum=l.m-t.m;
		ll x = ceil(num/denum);
		qu.pop_front();
		qu.push_front(x);
		qu.push_front(min_x);
		qu_line.push_front(l);
		
	}
	
	void insert(line l){
		if(qu.size()==0){
			qu_line.push_back(l);
			qu.push_back(min_x);
			return;
		}
		if(qu_line.back().m>=l.m) insert_back(l);
		else if(l.m>=qu_line.front().m) insert_front(l);
		
	}
	
	ll find(ll x){
		auto itr=upper_bound(all(qu),x);
		auto it=qu.begin();
		int ix = (itr-it)-1;
		line l = qu_line.at(ix);
		return  l.value(x);
	}
	
	bool empty(){
		return qu.empty();
	}
	
};

int main(){
	
}


