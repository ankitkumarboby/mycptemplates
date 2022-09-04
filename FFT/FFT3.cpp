// Base of NTT taken from KTH's kactl on github, 
//https://github.com/kth-competitive-programming/kactl

// My solution required a multipoint polynomial evaluator, hopefully this is quick enough
// Feels like my soltion should scale n (log n)^inf at this point, with a big constant

// EDIT: Found out how to do it quickly, needed to make use of formal derivative

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define   fo(number1,number2,number3) for(int number1=number2;number1<=number3;++number1)
#define   fastio                      ios_base::sync_with_stdio(false);cin.tie(NULL);


typedef long long ll;
typedef pair<int, int> pii;
//typedef vector<int> vi;
typedef vector<ll> vl;
 
const ll mod = 998244353, root = 3;

 ll power(ll x,ll y,ll m){            //power(x,y)=x^y  %m;
    if(x==0)return 0;
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
 
ll modpow(ll x,ll y)
{
	return power(x,y,mod);
	ll ret=1;
	for (; y; y >>= 1, x = (x*x)%mod)
	    if (y&1) ret = (x*ret)%mod;
	return ret;
}

ll modinv(ll a)
{
    return modpow(a,mod-2);
}

// https://arxiv.org/pdf/1708.01873.pdf
void BitReverse(vl& vec,int n) {
    int L = 31 - __builtin_clz(n);
    int rev = 0;
	rep(i,0,n) 
    {
		if (i < rev) swap(vec[i], vec[rev]);
		int tail = i ^ (i + 1), shift = 32 - __builtin_clz(tail);
		rev ^= tail << (L - shift);
	}
}


// For p < 2^30 there is also e . g . (5 << 25, 3) , (7 << 26, 3) ,
// (479 << 21, 3) and (483 << 21, 5) . The last two are > 10^9.
void ntt(vl& x, vl roots) {
    int n = x.size();
    if (n == 1) return;
    BitReverse(x,n);
    
    int L = 31 - __builtin_clz(n);
    int mask = (1<<L)-1;

    for (int s=1; s<=L; ++s){
        int m = 1<<s;
        int dx = n/m;
        for (int k = 0; k<n; k+=m){
            int index = 0;
            for (int j = 0; j<m/2;++j)
            {
                ll t = roots[index]*(x[k+j+m/2]%mod);
                ll u = x[k+j];
                x[k+j] = (u+t);
                x[k+j+m/2] = (u-t);
                index = (index+dx)&mask;
            }
        }

    }
    for (int i=0; i<n; ++i)
        x[i]%=mod;
}

// Remember roots to speed up fft
vl precalced_roots[32][2];

void ntt(vl& x, bool inv = false) {
    int L = sz(x);
    int s = 31 - __builtin_clz(L);

    if (precalced_roots[s][inv].size()==0)
    { 
        ll e = modpow(root, (mod-1) / L);
        if (inv)
            e = modpow(e, mod-2);
        vl roots(L,1);
        rep(i,1,L) 
        {
            roots[i] = (roots[i-1] * e) % mod;
        }
        precalced_roots[s][inv]=roots;
    }
    ntt(x, precalced_roots[s][inv]);        
}

vl conv(vl a, vl b) {
    int s = sz(a) + sz(b) - 1; if (s <= 0) return {};
    int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
    if (s <=100 || sz(a)<100 || sz(b)<100) { // ( factor 10 optimization for jaj , j b j = 10) 
        vl c(s);
        rep(i,0,sz(a)) rep(j,0,sz(b))
        {
            c[i+j] = (c[i + j] + (a[i] * b[j])%mod) % mod;
        }
        return c;
    }
    a.resize(n); ntt(a);
    b.resize(n); ntt(b);
    
    ll d = modpow(n, mod-2);
    rep(i,0,n) a[i]=((a[i]*b[i]%mod)*d)%mod;//c[i] = a[i] * b[i] % mod * d % mod;
    ntt(a, true); 
    a.resize(s); 
    return a;
}

vl dumbpolyfloor(vl poly1, vl poly2)
{
    int m = poly1.size()-1;
    int n = poly2.size()-1;
 
    assert(m>=n);
    assert((poly2.back()-1)%mod==0);
    vl q(m-n+1);
    for (int k=m-n;k>=0;--k)
    {
        q[k] = poly1[n+k];
        for (int j = n+k; j>=k; --j)
        {
            poly1[j]=(poly1[j] - (q[k]*poly2[j-k])%mod+mod)%mod;
        }
        assert(poly1.back()==0);
        poly1.pop_back();
    }
    return q;
}


//http://web.cs.iastate.edu/~cs577/handouts/polydivide.pdf

// For poly with deg k-1 calculates floor(x^(2k-2)/poly1)
// output got degree k-1
// Assunes poly1[k-1]=1
vl reci(vl poly1)
{
    assert((poly1.back()-1)%mod==0);
    int k = poly1.size();
    
    int p=1;
    while (p<k) p*=2;
    
    // Need k to have length power of 2
    if (p!=k)
    {
        vl newpoly1(k + p-k); 
        copy(poly1.begin(),poly1.end(),newpoly1.begin()+p-k);
        vl ans = reci(newpoly1);
        return {ans.begin()+p-k,ans.end()};
    }
    
    if (k==1)
    {
        return {1};
    }
    vl q = reci({poly1.begin()+k/2,poly1.end()});

    vl a(2*k-2);
    for (int i=0; i<k/2; ++i)
    {
        a[3*(k/2)-2+i] = 2*q[i]%mod;
    }

    vl b = conv(conv(q,q),poly1);
    
    vl ans(k);
    for (int i=0;i<k;++i)
    {
        ans[i] = (a[i+k-2] - (b[i+k-2])%mod+mod)%mod;
    }
    return ans;

}

// Quickly calculates poly1//poly2, but needs s=reci(poly1) to do it quickly
// This method also requires len(poly1)>=len(poly2) and len(poly2) to be a power of 2
vl quickpolyfloor(vl poly1,vl poly2, vl s)
{
    int m = poly1.size()-1;
    int n = poly2.size()-1;

    vl prod = conv(poly1,s);
    vl out(prod.begin()+2*n,prod.end());
    
    // If m<2*n then there is no need for recursion
    if (m<=2*n)
    {
        return out;
    } 
 
    vl t(n);
    vl prod2 = conv(poly2,s);
    for (int i=0; i<n; ++i)
    {
        t[i] = (mod-prod2[i])%mod;
    }

    // Do the recursive call
    
    vl prod3 = conv(poly1,t);
    
    vl tmp(prod3.begin()+2*n,prod3.end());

    // This would have been 0 if m<2*n
    vl out2 = quickpolyfloor(tmp,poly2,s);

    for (int i=0;i<m-2*n;++i)
    {
        out[i] = (out[i]+out2[i])%mod;
    }

    return out;
}


// if len(poly1)>=len(poly2) then it calculates poly1//poly2,
// Othervise dont use the polyfloor function, as the answer it trivial
vl polyfloor(vl poly1, vl poly2)
{
    int m = poly1.size()-1;
    int n = poly2.size()-1;
 
    assert(m>=n);
    return quickpolyfloor(poly1,poly2,reci(poly2));
}



// poly1 mod poly2
vl modu(vl poly1, vl poly2)
{
    // Will assume poly2 to start with a 1
    int m = poly1.size()-1;
    int n = poly2.size()-1;
    
    if (m<n)
        return poly1;
    if (n==0)
        return {};
    
    if (m-n<500 || n<500)
    {
        for (int k=m-n;k>=0;--k)
        {
            ll qk = poly1[n+k];
            for (int j = n+k-1; j>=k; --j)
            {
                poly1[j]=(poly1[j] - (qk*poly2[j-k])%mod+mod)%mod;
            }
        }
        poly1.resize(n);
        return poly1;
    } else 
    {
        vl q = polyfloor(poly1,poly2);
        
        // poly1 = poly2*q + r, deg(r)<n
        vl prod = conv(poly2,q);
        vl r(n);
        for (int i=0;i<n;++i)
            r[i] = (poly1[i]-(prod[i])%mod+mod)%mod;
        return r;
    }

}

// Multipoint evaluation
vl eval(vl poly,vl points)
{   
    if (points.size()<50 || poly.size()<50)
    {
        vl ans(points.size());
        for (int i = 0; i<points.size(); ++i)
        {
            ll x = 1;
            for (int j=0; j<poly.size(); ++j)
            {
                ans[i] = (ans[i] + (x*poly[j])%mod)%mod;
                x = (x*points[i])%mod;
            }
        }
        return ans;
    }
    
    
    
    int n = points.size();
    int m=1;
    while (m<n) m*=2;

    vector<vl> polytree(2*m,{1});
    
    for (int i=0; i<n; ++i)
        polytree[i+m] = {(mod-points[i])%mod,1};
    
    for (int i=m-1; i>1; --i)
        polytree[i] = conv(polytree[2*i],polytree[2*i+1]);
    
    polytree[1]=poly;
    for (int i=2;i<2*m;++i)
        polytree[i] = modu(polytree[i/2],polytree[i]);
    
    vl ans(n);
    for (int i=0; i<n; ++i)
        ans[i] = polytree[i+m][0];
    
    
    return ans;
}

vl formal_derivative(vl A)
{
    for (ll i=1; i<A.size(); ++i)
        A[i-1] = (i*A[i])%mod;
    A.resize(A.size()-1);
    return A;
}




class solver{
	public:
	ll n,x;
	ll *a,*xa,*sa,*px;
	
	vl bs_mul(int l,int r){
		if(l==r){
			vector<ll> tmp(2);
			tmp[0]=(mod-sa[l])%mod;
			tmp[1]=1;
			return tmp;
		}
		int m=(l+r)/2;
		return conv(bs_mul(l,m),bs_mul(m+1,r));
	}
	
	void solve(){
		cin>>n;
		cin>>x;
		a=new ll[n+1];
		xa=new ll[n+1];
		sa=new ll[n+1];
		px=new ll[n+1];
		
		fo(i,1,n)cin>>a[i];
		fo(i,1,n){
			a[i]%=mod;
			if(a[i]==0){
				cout<<0<<'\n';
				return;
			}
		}
		
		px[0]=1;
		fo(i,1,n)px[i]=(px[i-1]*x)%mod;
		fo(i,1,n)xa[i]=(a[i]*px[i])%mod;
		fo(i,1,n)sa[i]=(sa[i-1]+xa[i])%mod;
		
		vl p=bs_mul(0,n);
		p=formal_derivative(p);
		vector<ll> v(n+1);
		fo(i,0,n)v[i]=sa[i];
		v=eval(p,v);
		ll ans=1;
		fo(i,0,n)ans=(ans*v[i])%mod;
		ans=(ans+mod)%mod;
		ll pw=(n*(n+1)*(n+2))/3;
		pw=power(x,pw,mod);
		ans=(ans*mod_inverse(pw,mod))%mod;
		if(((n*(n+1))/2)%2==1)ans=(mod-ans)%mod;
		cout<<ans<<'\n';
		
	}	
};

int main(){
	fastio
	int test=1;
	cin>>test;
	while(test--){
		solver o;
		o.solve();
	}
    return 0;
}


