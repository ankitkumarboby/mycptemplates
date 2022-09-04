#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define trav(x,a) for (const auto& x: a)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), x.end()
#define mem(a,v) memset((a), (v), sizeof (a))
#define enl printf("\n")
#define case(t) printf("Case #%d: ", (t))
#define ni(n) scanf("%d", &(n))
#define nl(n) scanf("%I64d", &(n))
#define nai(a, n) for (int _i = 0; _i < (n); _i++) ni(a[_i])
#define nal(a, n) for (int _i = 0; _i < (n); _i++) nl(a[_i])
#define pri(n) printf("%d\n", (n))
#define prl(n) printf("%I64d\n", (n))
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vii vector<pii>
#define vll vector<pll>
#define vi vector<int>
#define vl vector<long long>
#define pb push_back
#define mp make_pair
#define st first
#define nd second
#define   fo(number1,number2,number3) for(int number1=number2;number1<=number3;++number1)
#define   fastio                      ios_base::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef long double ld;
typedef cc_hash_table<int,int,hash<int>> ht;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> oset;
 
/*
Source: https://cp-algorithms.com/algebra/polynomial.html, me
Verification:
  uoj.ac/problem/50 (exp, log, invert for ntt)
  loj.ac/problem/6703 (multipoint eval)
*/
 
//for extra speed use follwoing custom complex type
constexpr ld eps = 1e-6;
struct cpx {
  ld a=0,b=0;
  cpx(){}
  cpx(ld p, bool ang = 0) {
    if (ang)
      a = cos(p), b = sin(p);
    else
      a = p, b = 0;
  }
  // cpx(double a): a(a) {}
  cpx(ld a, ld b):a(a),b(b){}
  ld modsq() {
    return a * a + b * b;
  }
  cpx bar() {
    return cpx(a, -b);
  }
  cpx operator/=(ld n) {
    a /= n, b /= n;
    return *this;
  }
  cpx operator*=(ld n) {
    a *= n, b *= n;
    return *this;
  }
  cpx operator+=(const cpx& y) {
    a += y.a, b += y.b;
    return *this;
  }
  cpx operator-=(const cpx& y) {
    a -= y.a, b -= y.b;
    return *this;
  }
  cpx operator*=(const cpx& y) {
    tie(a, b) = make_pair(a * y.a - b * y.b, a * y.b + b * y.a);
    return *this;
  }
  cpx operator/=(cpx y) {
    *this *= y.bar();
    return *this / y.modsq();
  }
  friend cpx operator+(cpx x, const cpx& y) { return x += y; }
  friend cpx operator-(cpx x, const cpx& y) { return x -= y; }
  friend cpx operator*(cpx x, const cpx& y) { return x *= y; }
  friend cpx operator/(cpx x, cpx y) { return x /= y; }
  friend cpx operator*(cpx x, ld y) { return x *= y; }
  friend cpx operator/(cpx x, ld y) { return x /= y; }
  friend bool operator==(const cpx& x, const cpx& y) {
    return (x-y).modsq() < eps;
  }
  friend bool operator!=(const cpx& x, const cpx& y) {
    return !(x == y);
  }
  friend ostream& operator<<(ostream& os, const cpx& p) {
    return os << p.a << " " << p.b;
  }
};
ld abs(cpx x) {
  return x.modsq();
}
using cd = cpx;
//otherwise use
//using cd = complex<ld>;
 
template <class T> struct equ {
  bool operator() (const T& x, const T& y) const {
    return (is_integral<T>::value || !is_fundamental<T>::value) ? x==y : abs(x-y) < eps;
  }
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};
 
template<class T> struct Poly {
  const ll evalLIM = 500000;
  const ll mulLIM = 500000;
  int n;
  vector<T> a;
  Poly() : n(0), a(n) {}
  Poly(int n) : n(n), a(n,T(0)) {}
  Poly(vector<T> a) : n(sz(a)), a(a) {}
  Poly(const Poly<T>& a) : n(a.n), a(a.a) {}
  T operator[](int i) const {
    return i < n ? a[i] : T(0);
  }
  struct modop {
    static const ll mod = 998244353;
    static const ll mxn = 1 << 23;
    static const ll root = 15311432;
    static const ll iroot = 469870224;
    static T add(T x, T y) {
      x%=mod;
      y%=mod;
      return (x+y)%mod;
    }
    static T sub(T x, T y) {
      return (x-y+mod)%mod;
    }
    static T mul(T x, T y) {
        x%=mod;
        y%=mod;
      return (x * y) % mod;
    }
    static T pw(T x, ll y) {
      T r = T(1);
      for (; y; y /= 2, x = mul(x, x))
        if (y & 1)
          r = mul(r, x);
      return r;
    }
    static T div(T x, T y) {
      return mul(x, pw(y, mod-2));
    }
    static T val(ll x, ll i) {
      for (int j = i; j < mxn; j *= 2)
        x = mul(x, x);
      return x;
    }
  };
  struct realop {
    static constexpr ld root = 2*acos(-1); // +2*pi
    static constexpr ld iroot = -root; // -2*pi
    static T add(T x, T y) {
      return x+y;
    }
    static T sub(T x, T y) {
      return x-y;
    }
    static T mul(T x, T y) {
      return x * y;
    }
    static T div(T x, T y) {
      return x / y;
    }
    static cd val(ld x, int i) {
      return cd(x / (ld) i, true);
    }
  };
  // use realop for non modular arithmetic
  using op = modop;
 
  T evaluate(T x) {
    T ret(0);
    for (int i = n-1; ~i; i--)
      ret = op::add(op::mul(ret, x), a[i]);
    return ret;
  }
 
  int firstc() {
    for (int i = 0; i < n; i++)
      if (!equ<T>()(a[i], T(0)))
        return i;
    return 0;
  }
 
  static Poly zero() {
    return Poly(vector<T>({T(0)}));
  }
 
  static Poly one() {
    return Poly(vector<T>({T(1)}));
  }
 
  Poly shiftL(int i) {
    if (i >= n) return zero();
    return Poly(vector<T>(a.begin() + i, a.end()));
  }
 
  Poly shiftR(int i) {
    vector<T> b(i, T(0));
    b.insert(b.end(), a.begin(), a.end());
    return Poly(b);
  }
 
  Poly range(int l, int r) {
    assert(l >= 0 && r >= 0);
    l = min(l, n-1), r = min(r, n-1);
    return Poly(vector<T>(a.begin()+l, a.begin()+r+1));
  }
 
  void resize(int n) {
    if (n == (*this).n) return;
    a.resize(n);
    if (n > (*this).n)
      fill(a.begin()+n, a.end(), T(0));
    (*this).n = n;
  }
 
  void pop_back() {
    assert(n > 1);
    n--; a.pop_back();
  }
 
  void push_back(T x) {
    n++; a.push_back(x);
  }
 
  void mirror() {
    reverse(a.begin(), a.end());
  }
 
  void norm() {
    while (n > 1 && equ<T>()(a[n-1], T(0)))
      pop_back();
  }
 
  Poly differentiate() {
    Poly ret(n-1);
    for (int i = 1; i < n; i++)
      ret.a[i-1] = op::mul(a[i], T(i));
    return ret;
  }
 
  Poly integrate() {
    Poly ret(n+1);
    ret.a[0] = T(0); // constant
    for (int i = 1; i <= n; i++)
      ret.a[i] = op::div(a[i-1], T(i));
    return ret;
  }
 
  void transform(int i, int j, T w) {
    T x = a[i], y = op::mul(a[j], w);
    a[i] = op::add(x, y), a[j] = op::sub(x, y);
  }
 
  void fft(Poly& b, bool inv) {
    for (int i = 1, j = 0; i < n; i++) {
      int bt = n >> 1;
      for (j ^= bt; !(j & bt); j ^= (bt >>= 1));
      if (i < j) {
        swap(a[i], a[j]);
        if (!inv) swap(b.a[i], b.a[j]);
      }
    }
    for (int i = 2; i <= n; i *= 2) {
      T cur = op::val(inv ? op::iroot : op::root, i);
      for (int j = 0; j < n; j += i) {
        T w(1);
        for (int k = j; k < j+i/2; k++) {
          transform(k, k+i/2, w);
          if (!inv) b.transform(k, k+i/2, w);
          w = op::mul(w, cur);
        }
      }
    }
    if (inv) {
      T m = op::div(T(1), T(n));
      for (int i = 0; i < n; i++)
        a[i] = op::mul(a[i], m);
    }
  }
 
  Poly operator*=(Poly p) {
    int s = p.n + n - 1;
    if (p.n * 1ll * n <= mulLIM) {
      Poly<T> ret(s);
      for (int i = 0; i < n; i++)
        for (int j = 0; j < p.n; j++)
          ret.a[i+j] = op::add(ret.a[i+j], op::mul(a[i], p[j]));
      return *this = ret;
    }
    int m = 1; while (m < max(n, p.n)) m *= 2;
    // use commented lines for non modular arithmetic
    resize(m*2); p.resize(m*2);
    fft(p, 0);
    for (int i = 0; i < m*2; i++)
      a[i] = op::mul(a[i], p[i]);
    fft(p, 1);
    // Poly<cd> x(m*2), y(m*2);
    // for (int i = 0; i < m; i++)
    //   x.a[i] = cd((*this)[i]), y.a[i] = cd(p[i]);
    // x.fft(y, 0);
    // for (int i = 0; i < m*2; i++)
    //   x.a[i] = Poly<cd>::op::mul(x[i], y[i]);
    // x.fft(y, 1);
    // resize(s);
    // for (int i = 0; i < s; i++)
    //   a[i] = is_integral<T>::value ? round(x[i].a) : x[i].a;
    return *this;
  }
 
  Poly operator+=(const Poly& p) {
    int m = max(n, p.n); resize(m);
    for (int i = 0; i < p.n; i++)
      a[i] = op::add(a[i], p[i]);
    return *this;
  }
 
  Poly operator-=(const Poly& p) {
    int m = max(n, p.n); resize(m);
    for (int i = 0; i < p.n; i++)
      a[i] = op::sub(a[i], p[i]);
    return *this;
  }
 
  // calculates the first s terms of the series expansion of 1 / p at x=0
  Poly invert(int s) {
    Poly ret = Poly(vector<T>({op::div(T(1), a[0])}));
    int k = 1;
    for (; k < s; k *= 2) {
      ret += ret - (ret * ret) * (*this).range(0, 2*k);
      ret.resize(2*k);
    }
    ret.resize(s);
    return ret;
  }
 
  Poly invert() {
    return invert(n);
  }
 
  // calculates the first max(p.n, n) terms of the series expansion of 1 / p at x=0
  Poly operator/=(Poly p) {
    norm(), p.norm();
    int i = p.firstc();
    p = p.shiftL(i);
    *this = shiftL(i);
    int m = max(p.n, n);
    *this *= p.invert(m); resize(m);
    norm();
    return *this;
  }
  
  Poly operator*=(T x) {
    if (equ<T>()(x, T(0)))
      return zero();
    for (int i = 0; i < n; i++)
      a[i] = op::mul(a[i], x);
    return *this;
  }
 
  Poly operator/=(T x) {
    assert(!equ<T>()(x, T(0)));
    x = op::div(T(1), x);
    for (int i = 0; i < n; i++)
      a[i] = op::mul(a[i], x);
    return *this;
  }
 
  Poly operator+=(T x) {
    assert(n > 0);
    a[0] = op::add(a[0], x);
    return *this;
  }
 
  Poly operator-=(T x) {
    assert(n > 0);
    a[0] = op::sub(a[0], x);
    return *this;
  }
 
  Poly operator%=(Poly p) {
    p.norm();
    int deg = n - p.n + 1;
    if (deg <= 0) return *this;
    mirror(); p.mirror();
    Poly ret = *this * p.invert(deg);
    ret.resize(deg);
    ret.mirror();
    p.mirror(); mirror();
    ret = (*this) - p * ret;
    return ret.range(0, p.n-1);
  }
 
  // calculates s terms of ln(p(x))
  Poly log(int s) { // requires p(0)=1
    norm();
    assert(equ<T>()(a[0], T(1)));
    if (s == 1)
      return zero();
    Poly ret = (*this).differentiate();
    ret *= (*this).invert(s-1);
    ret.resize(s-1);
    return ret.integrate();
  }
 
  Poly log() {
    return log(n);
  }
 
  // calculates s terms of exp(p(x))
  Poly exp(int s) {
    norm(); assert(equ<T>()(a[0], T(0)));
    Poly ret = Poly(vector<T>({T(1)}));
    int k = 1;
    for (; k < s; k *= 2) {
      ret += ret * ((*this).range(0, 2*k) - ret.log(2*k));
      ret.resize(2*k);
    }
    ret.resize(s);
    return ret;
  }
 
  Poly exp() {
    return exp(n);
  }
 
  // returns the polynomial p(x) = (x-b[l])*..*(x-b[r])
  Poly build(vector<Poly>& tree, const vector<T>& b, int l, int r, int k) {
    if (l == r)
      return tree[k] = Poly(vector<T>({op::sub(T(0), b[l]), T(1)}));
    int m = (l+r) / 2;
    return tree[k] = build(tree, b, l, m, k*2) * build(tree, b, m+1, r, k*2+1);
  }
 
  void eval(vector<Poly>& tree, const vector<T>& b, vector<T>& ret, int l, int r, int k) {
    if (r - l < evalLIM) {
      for (int i = l; i <= r; i++)
        ret.push_back(evaluate(b[i]));
      return;
    }
    int m = (l+r) / 2;
    (*this % tree[k*2]).eval(tree, b, ret, l, m, k*2);
    (*this % tree[k*2+1]).eval(tree, b, ret, m+1, r, k*2+1);
  }
 
  vector<T> evaluate(const vector<T>& b) {
    norm(); assert(n != 0);
    if (n == 1)
      return vector<T>(sz(b), a[0]);
    vector<Poly> tree(4*sz(b));
    build(tree, b, 0, sz(b)-1, 1);
    vector<T> ret;
    eval(tree, b, ret, 0, sz(b)-1, 1);
    return ret;
  }
 
  Poly inter(vector<Poly>& tree, const vector<T>& x, const vector<T>& y, int l, int r, int k) {
    if (l == r)
      return Poly(vector<T>({op::div(y[l], a[0])}));
    int m = (l+r) / 2;
    Poly lhs = (*this % tree[k*2]).inter(tree, x, y, l, m, k*2);
    Poly rhs = (*this % tree[k*2+1]).inter(tree, x, y, m+1, r, k*2+1);
    return lhs * tree[k*2+1] + rhs * tree[k*2];
  }
 
  Poly interpolate(const vector<pair<T,T>>& b) {
    vector<Poly> tree(4*sz(b));
    vector<T> x(sz(b)), y(sz(b));
    for (int i = 0; i < sz(b); i++)
      x[i] = b[i].first, y[i] = b[i].second;
    build(tree, x, 0, sz(b)-1, 1);
    Poly tmp = tree[1].differentiate();
    return tmp.inter(tree, x, y, 0, sz(b)-1, 1);
  }
 
  Poly& operator=(const Poly& x) {
    (*this).a = x.a;
    (*this).n = x.n;
    return *this;
  }
  friend Poly operator+(Poly x, const Poly& y) { return x += y; }
  friend Poly operator-(Poly x, const Poly& y) { return x -= y; }
  friend Poly operator*(Poly x, const Poly& y) { return x *= y; }
  friend Poly operator/(Poly x, const Poly& y) { return x /= y; }
  friend Poly operator*(Poly x, T y) { return x *= y; }
  friend Poly operator*(T y, Poly x) { return x *= y; }
  friend Poly operator/(Poly x, T y) { return x /= y; }
  friend Poly operator/(T y, Poly x) { return y * x.invert(); }
  friend Poly operator+(Poly x, T y) { return x += y; }
  friend Poly operator+(T y, Poly x) { return x += y; }
  friend Poly operator-(Poly x, T y) { return x -= y; }
  friend Poly operator-(T y, Poly x) { return x = y + op::sub(T(0),T(1)) * x; }
  friend Poly operator%(Poly x, const Poly& y) { return x %= y; }
  Poly pow_naive(ll k, int s) { // first s coefficients of p(x) ** k
    Poly ret = one();
    Poly x = *this;
    if (x.n > s) x.resize(s);
    while (k > 0)
      if (k & 1) {
        ret *= x, k--;
        if (ret.n > s) ret.resize(s);
      } else {
        x *= x, k /= 2;
        if (x.n > s) x.resize(s);
      }
    ret.resize(s);
    return ret;
  }
  Poly pow(ll k, int s) {
    int i = firstc();
    if (s <= i*k || equ<T>()(a[i],T(0)))
      return zero();
    //if (!equ<T>()(a[i], T(1)))
      return (*this).shiftL(i).pow_naive(k, s-i*k).shiftR(i*k);
    //T v = a[i];
    //return (((*this) / v).shiftL(i).log(s-i*k) * T(k)).exp(s-i*k).shiftR(i*k) * op::pw(v, k);
  }
  Poly pow(ll k) {
    return pow(k, (n-1) * k + 1); // assume (n-1) * y + 1 < inf
  }
  Poly kthroot(ll k, int s) { // first s coefficients of p(x) ** (1/k)
    assert(equ<T>()(a[0], T(1))); // otherwise you need to calculate a[0] ** (1/k)
    return ((*this).log(s) / T(k)).exp(s);
  }
  Poly kthroot(ll k) {
    return kthroot(k, n);
  }
  friend bool operator==(const Poly& x, const Poly& y) {
    if (x.n != y.n) return false;
    return x.a == y.a;
  }
  friend bool operator!=(const Poly& x, const Poly& y) {
    return !(x == y);
  }
  friend ostream& operator<<(ostream& os, const Poly& p) {
    // os << p.n << " :: ";
    for (int i = 0; i < p.n; i++)
      os << p[i] << (i+1 == p.n ? "" : " ");
    return os;
  }
};
 
 
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
 
 
 
const double pi = acos(-1);
const ll mod = 998244353;
typedef Poly<ll> polyn;
class solver{
	public:
	ll n,x;
	ll *a,*xa,*sa,*px;
	
	polyn bs_mul(int l,int r){
		if(l==r){
			vector<ll> tmp(2);
			tmp[0]=(mod-sa[l])%mod;
			tmp[1]=1;
			polyn tm(tmp);
			return tm;
		}
		int m=(l+r)/2;
		return bs_mul(l,m)*bs_mul(m+1,r);
	}
	
	void solve(){
		cin>>n;
		cin>>x;
		a=new ll[n+1];
		xa=new ll[n+1];
		sa=new ll[n+1];
		px=new ll[n+1];
		
		fo(i,1,n)cin>>a[i];
		px[0]=1;
		fo(i,1,n)px[i]=(px[i-1]*x)%mod;
		fo(i,1,n)xa[i]=(a[i]*px[i])%mod;
		fo(i,1,n)sa[i]=(sa[i-1]+xa[i])%mod;
		
		polyn p=bs_mul(0,n);
		p=p.differentiate();
		
		vector<ll> v(n+1);
		fo(i,0,n)v[i]=sa[i];
		v=p.evaluate(v);
		
		ll ans=1;
		fo(i,0,n)ans=(ans*v[i])%mod;
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
}
