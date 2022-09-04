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
 
//Aho-Corasick algorithm
//Time Complexity to build = O( sum of length of all strings )
//uses to go to max length prefix of any string which is also suffix at the particular node
 
struct vertex{
	char ch;
	int index;
	vertex *next[26],*go[26],*par,*link,*exit_link;
	
	vertex(){
		for(int i=0;i<26;++i){
			next[i]=go[i]=NULL;
		}
		par=exit_link=link=NULL;
		index=-1;
	}
	vertex(char cch,vertex* ppar){
		ch=cch;
		par=ppar;
		for(int i=0;i<26;++i){
			next[i]=go[i]=NULL;
		}
		exit_link=link=NULL;
		index=-1;
	}
};
 
class aho_corasick{
	public:
	
	vertex* root;
	vector<string> a;
	
	aho_corasick(vector<string> &aa){           //0-indexed
		a=aa;              
		root=new vertex;
		int ix=0;
		for(string s:a){
			add_string(s,ix);ix++;
		}
	}
	void add_string(string s,int ix){
		vertex* ptr=root;
		for(char ch:s){
			int c=int(ch)-int('a');
			if(ptr->next[c]==NULL)ptr->next[c]=new vertex(ch,ptr);
			ptr = ptr->next[c];
		}
		ptr->index=ix;
	}
	
	vertex* get_link(vertex* u){
		if(u->link!=NULL)return u->link;
		if(u==root || u->par==root){
			u->link=root;
		}
		else{
			u->link = go(get_link(u->par),u->ch);
		}
		return u->link;
	}
	
	vertex* go(vertex* u,char ch){
		int c=int(ch)-int('a');
		if(u->go[c]!=NULL) return u->go[c];
		
		if(u->next[c]!=NULL)u->go[c] = u->next[c];
		else u->go[c] = (u==root) ? root : go(get_link(u),ch);
		
		return u->go[c];
	}
	
	vertex* get_exit_link(vertex* u){  // nearest leaf vertex that is reachable using suffix links
		if(u->exit_link!=NULL)return u->exit_link;
		if(get_link(u)->index!=-1 || get_link(u)==root){
			u->exit_link=get_link(u);
		}
		else{
			u->exit_link=get_exit_link(get_link(u));
		}
		return u->exit_link;
	}
		
};
 
