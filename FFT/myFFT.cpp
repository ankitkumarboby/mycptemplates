#include<bits/stdc++.h>
#define   ll                          long long int
#define   fo(number1,number2,number3) for(int number1=number2;number1<=number3;++number1)
using namespace std;

template<typename T>
struct myComplex{
	T x,y;
	
	myComplex<T>(T _x=0,T _y=0):x(_x),y(_y){}
	
	T real(){return x; }
	T imag(){return y; }
	
	void real(T _x){ x=_x; }
	void imag(T _y){ y=_y; }
	
	myComplex<T>& operator+=(myComplex<T> &other){x+=other.x; y+=other.y;return *this ;}
	myComplex<T>& operator-=(myComplex<T> &other){x-=other.x; y-=other.y;return *this ;}
	
	myComplex<T> operator+(myComplex<T> &other){ return myComplex<T>(*this)+=other;}
	myComplex<T> operator-(myComplex<T> &other){ return myComplex<T>(*this)-=other;}
	
	myComplex<T> operator*(myComplex<T> &other){
		return {x*other.x-y*other.y,x*other.y+y*other.x };
	}
	
	friend myComplex<T> conj(myComplex<T> &other){
		return {other.x,-other.y};
	}
	
	friend ostream& operator<<(ostream &stream,myComplex<T> &other){
		return stream<<'('<<other.x<<','<<other.y<<')';
	}
	
};

template<typename T>
myComplex<T> myPolar(T magnitude,T angle){
	return {magnitude* cos(angle), magnitude*sin(angle)};
}

using cd=myComplex<double>;
const double PI = acos(-1);

vector<cd> w;

void initializeRoot(int mx_n){
	int lg_n=0;
	while((1<<lg_n)<mx_n){
		double ang=2*PI/(1<<lg_n);
		w.push_back(myPolar(double(1),ang));
		lg_n++;
	}
}

void fft(vector<cd> &a,bool invert,int lg_n=0){
	int n=a.size();
	if(n==1)return;
	vector<cd> a1(n/2),a2(n/2);
	for(int i=0;2*i<n;++i){
		a1[i]=a[2*i];
		a2[i]=a[2*i+1];
	}
	fft(a1,invert,lg_n-1);
	fft(a2,invert,lg_n-1);
	cd wn=w[lg_n],_w((double)1,(double)0);
	if(invert){
		wn.y*=(double)-1;
    }
	for(int i=0;2*i<n;++i){
		cd tmp=_w*a2[i];
		a[i]=a1[i]+tmp;
		a[i+n/2]=a1[i]-tmp;
		if(invert){
			a[i].x/=(double)2;
			a[i].y/=(double)2;
			a[i+n/2].x/=(double)2;
			a[i+n/2].y/=(double)2;
		}
		_w=_w*wn;
	}
}

const int fft_cutoff=100;

template<typename T>
class Polynomial{
	public:
	vector<T> p;
	int n;  // n=2^s
	
	Polynomial(vector<T> poly){
		p=poly;
		n=p.size();
	}
	Polynomial(int _n){
		n=_n;
		p.resize(n,0);
	}
	void normalize(){
		int len=p.size();
		int k=0;
		while((1<<k)<len)k++;
		n=(1<<k);
		p.resize(n,0);
	}
	void shrink(){
		while(p.size()!=0&&p.back()==0)p.pop_back();
	}
	
	friend Polynomial<T> fast_mul(Polynomial<T> &x,Polynomial<T> &y){
		vector<cd> v1,v2;
		int lg_n=0;
		int n1=x.p.size(),n2=y.p.size();
		while((1<<lg_n)<n1+n2)lg_n++;
		int _n=(1<<lg_n);
		v1.resize(_n);
		v2.resize(_n);
		for(int i=0;i<n1;++i)v1[i].x=(double)x.p[i];
		for(int i=0;i<n2;++i)v2[i].x=(double)y.p[i];
		fft(v1,false,lg_n);
		fft(v2,false,lg_n);
		for(int i=0;i<_n;++i)v1[i]=v1[i]*v2[i];
		fft(v1,true,lg_n);
		Polynomial<T> result(_n);
		for(int i=0;i<_n;++i)result.p[i]=T(round(v1[i].x));
		return result;		
	}
	
	friend Polynomial<T> slow_mul(Polynomial<T> &x,Polynomial<T> &y){
		int n1=x.p.size(),n2=y.p.size();
		Polynomial<T> result(n1+n2);
		for(int i=0;i<n1;++i){
			for(int j=0;j<n2;++j){
				result.p[i+j]+=x.p[i]*y.p[j];
			}
		}
		return result;
	}
	
	friend Polynomial<T> operator*(Polynomial<T> &x,Polynomial<T> &y){
		if(min(x.p.size(),y.p.size())<=fft_cutoff)return slow_mul(x,y);
		return fast_mul(x,y);
	}
	
	
	friend Polynomial<T> operator+(Polynomial<T> &x,Polynomial<T> &y){
		int n1=x.p.size(),n2=y.p.size();
		Polynomial<T> result(n1+n2);
		for(int i=0;i<n1;++i)result.p[i]+=x.p[i];
		for(int i=0;i<n2;++i)result.p[i]+=y.p[i];
		return result;
	}
	friend Polynomial<T> operator-(Polynomial<T> &x,Polynomial<T> &y){
		int n1=x.p.size(),n2=y.p.size();
		Polynomial<T> result(n1+n2);
		for(int i=0;i<n1;++i)result.p[i]+=x.p[i];
		for(int i=0;i<n2;++i)result.p[i]-=y.p[i];
		return result;
	}
	
		
};

int main(){
	initializeRoot(100);
	for(int i=0;i<=10;++i){
		cout<<w[i]<<'\n';
	}
	int n,m;
	cin>>n>>m;
	Polynomial<int> p(n),q(m);
	for(int i=0;i<n;++i)cin>>p.p[i];
	for(int i=0;i<m;++i)cin>>q.p[i];
	p=p*q;
	for(auto i:p.p)cout<<i<<' ';cout<<'\n';
}
