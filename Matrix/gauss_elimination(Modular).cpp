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


// 0 -> no solution
// 1 -> only one unique solution
// 2 -> infinitely many solutions
// matrix(a)= matrix(cofficients) + matrix(value)
//time complixity =   O(min(n,m)*nm)
//precompute inverse fact for optimization

int gauss (vector < vector<ll> > a, vector<ll> & ans, ll base) {  // ans will be 0-indexed
	
	const int INF = 2; // it doesn't actually have to be infinity or a big number

    int n = (int) a.size();
    int m = (int) a[0].size() - 1;
    ans.resize(m);
    
    vector<int> where (m, -1);    // the indices i, where[i] == -1 , x[i] can take any value
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) == 0ll)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
            	ll c = a[i][col];
            	for(int j=0; j<=m; ++j){
            		a[i][j] = (a[i][j] * a[row][col])%base;
            		a[i][j] = (a[i][j] - ( (a[row][j] * c) % base) + base)%base;       
				}
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = (a[where[i]][m] * mod_inverse(a[where[i]][i],base) )%base;
    for (int i=0; i<n; ++i) {
        ll sum = 0;
        for (int j=0; j<m; ++j){
            sum += (ans[j] * a[i][j])%base;
            sum%=base;
        }
        if (sum != a[i][m])
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}


int main(){
	fastio
//	pre_compute();
	
}






