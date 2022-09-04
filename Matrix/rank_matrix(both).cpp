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



int compute_rank(vector<vector<double>> a) {
	const double EPS = 1E-9;
    int n = a.size();
    int m = a[0].size();

    int rank = 0;
    vector<bool> row_selected(n, false);
    for (int i = 0; i < m; ++i) {
        int j;
        for (j = 0; j < n; ++j) {
            if (!row_selected[j] && abs(a[j][i]) > EPS)
                break;
        }

        if (j != n) {
            ++rank;
            row_selected[j] = true;
            for (int p = i + 1; p < m; ++p)
                a[j][p] /= a[j][i];
            for (int k = 0; k < n; ++k) {
                if (k != j && abs(a[k][i]) > EPS) {
                    for (int p = i + 1; p < m; ++p)
                        a[k][p] -= a[j][p] * a[k][i];
                }
            }
        }
    }
    return rank;
}


int compute_rank(vector<vector<ll>> a,ll base) {
    int n = a.size();
    int m = a[0].size();

    int rank = 0;
    vector<bool> row_selected(n, false);
    for (int i = 0; i < m; ++i) {
        int j;
        for (j = 0; j < n; ++j) {
            if (!row_selected[j] && (abs(a[j][i]) != 0ll))
                break;
        }

        if (j != n) {
            ++rank;
            row_selected[j] = true;
            
            for (int k = 0; k < n; ++k) {
                if (k != j && (abs(a[k][i]) != 0ll)) {
                    for (int p = i + 1; p < m; ++p){
                        a[k][p] = (a[k][p] * a[j][i])%base;
						a[k][p] -= ((a[j][p] * a[k][i])%base);
						a[k][p] = (a[k][p]+base)%base;
                    }
                }
            }
        }
    }
    return rank;
}


int main(){
	fastio
//	pre_compute();
	
}






