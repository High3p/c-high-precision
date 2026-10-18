#pragma once
#ifndef HP_MATH_H
#define HP_MATH_H
#include<cmath>
#include"HPdec.h"
inline HP_dec pow(const HP_dec& g,HP_int i){
	if(g==create_hp_dec("0.0")){
		if(i.PANNI)throw "0^negative undefined";
		return g;
	}
	bool neg=i.PANNI;
	if(neg)i=abs(i);
	HP_dec sum="1.0",h=g;
	while(!(i).is_zero()){
		if(i.isOdd()){
            sum=sum*h;
        }
        h*=h;
        i=hp_div2(i);
        i.trim_zeros();
	}
	if(neg)sum=create_hp_dec("1.0")/sum;
	return sum;
}
inline HP_int pow(const HP_int& g,HP_int i){
	if(g==create_hp("0"))return g;
	HP_int sum=hp_one(),h=g;
	while(!(i).is_zero()){
		if(i.isOdd()){
            sum=sum*h;
        }
        h*=h;
        i=hp_div2(i);
        i.trim_zeros();
	}
	return sum;
}
//inline double pow(const double& g,int i){
//	return pow((g),i);
//}
static HP_int hp_pow10_ll(long long k) {
	HP_int r=create_hp("1");
	for(long long i=0; i<k; i++)r.v.push_back(0);
	return r;
}
static HP_int hp_fixed(const HP_dec &x,long long work) {
	HP_int F;
	F.PANNI=x.PANNI;
	F.v=x.integer.v;
	for(int d:x.frac)F.v.push_back(d);
	while((long long )F.v.size()<(long long )x.integer.v.size()+work)F.v.push_back(0);
	if((long long )F.v.size()>(long long )x.integer.v.size()+work)
		F.v.resize((size_t)x.integer.v.size()+work);
	return F;
}
static HP_dec hp_fixed_to_dec(const HP_int &X,long long work) {
	HP_dec ret;
	ret.PANNI=X.PANNI;
	size_t n=X.v.size();
	if(n<=(size_t)work) {
		ret.integer=create_hp("0");
		std::vector<int >fr(X.v.begin(),X.v.end());
		while(fr.size()<(size_t)work)fr.insert(fr.begin(),0);
		ret.frac=fr;
	} else {
		ret.integer.v.assign(X.v.begin(),X.v.end()-work);
		ret.integer.trim_zeros();
		ret.frac.assign(X.v.end()-work,X.v.end());
	}
	ret.trim_tail_frac();
	if(ret.is_zero())ret.PANNI=false;
	return ret;
}
static HP_int hp_fixed_mul(const HP_int &A,const HP_int &B,long long work) {
	HP_int P=auto_mul(A,B);
	if(P.v.size()<=(size_t)work)return create_hp("0");
	P.v.erase(P.v.end()-work,P.v.end());
	P.trim_zeros();
	return P;
}
static HP_int hp_fixed_div_small(const HP_int &A,long long d) {
	if(d<=0)throw"hp_fixed_div_small:/0";
	HP_int Q;
	Q.PANNI=A.PANNI;
	long long carry=0;
	for(int c:A.v) {
		long long cur=carry*10+c;
		Q.v.push_back((int )(cur/d));
		carry=cur%d;
	}
	Q.trim_zeros();
	return Q;
}
static HP_int hp_fixed_div(const HP_int &A,const HP_int &B) {
	if(B.is_zero())throw"hp_fixed_div:/0";
	bool sign=A.PANNI!=B.PANNI;
	HP_int absA=abs(A),absB=abs(B);
	if(absA<absB)return create_hp("0");
	HP_int Bm[10];
	Bm[0]=create_hp("0");
	for(int i=1; i<=9; i++)Bm[i]=absB*i;
	HP_int rem=create_hp("0");
	std::vector<int >Qv;
	for(int c:absA.v) {
		rem=rem*10+c;
		int qd=0;
		for(int qq=9; qq>=1; qq--)
			if(Bm[qq]<=rem) {
				qd=qq;
				break;
			}
		if(qd)rem=rem-Bm[qd];
		Qv.push_back(qd);
	}
	HP_int Q;
	Q.v.clear();
	bool st=false;
	for(int c:Qv) {
		if(c)st=true;
		if(st)Q.v.push_back(c);
	}
	if(!st)Q.v.push_back(0);
	Q.PANNI=sign;
	if(Q.is_zero())Q.PANNI=false;
	return Q;
}
static HP_int hp_fixed_atan(const HP_int &X,long long work) {
	HP_int X2=hp_fixed_mul(X,X,work);
	HP_int term=X;
	HP_int sum=X;
	for(long long k=1; k<=work+10; k++) {
		term=hp_fixed_mul(term,X2,work);
		term=term*HP_int (2*k-1);
		term=hp_fixed_div_small(term,2*k+1);
		if(term.is_zero())break;
		if(k%2==1)sum=sum-term;
		else sum=sum+term;
	}
	return sum;
}
static HP_int hp_fixed_pi(long long work) {
	HP_int x5=hp_fixed(create_hp_dec("0.2"),work);
	HP_int inv239=hp_fixed_div_small(hp_pow10_ll(work),239);
	HP_int atan5=hp_fixed_atan(x5,work);
	HP_int atan239=hp_fixed_atan(inv239,work);
	return atan5*HP_int (16)-atan239*HP_int (4);
}
static HP_int hp_fixed_sin_series(const HP_int &X,long long work) {
	HP_int X2=hp_fixed_mul(X,X,work);
	HP_int term=X;
	HP_int sum=X;
	for(long long k=1; k<=work+10; k++) {
		term=hp_fixed_mul(term,X2,work);
		term=hp_fixed_div_small(term,(2*k)*(2*k+1));
		if(term.is_zero())break;
		if(k%2==1)sum=sum-term;
		else sum=sum+term;
	}
	return sum;
}
static HP_int hp_fixed_cos_series(const HP_int &X,long long work) {
	HP_int X2=hp_fixed_mul(X,X,work);
	HP_int term=hp_pow10_ll(work);
	HP_int sum=term;
	for(long long k=1; k<=work+10; k++) {
		term=hp_fixed_mul(term,X2,work);
		term=hp_fixed_div_small(term,(2*k-1)*(2*k));
		if(term.is_zero())break;
		if(k%2==1)sum=sum-term;
		else sum=sum+term;
	}
	return sum;
}
static HP_int hp_fixed_reduce(const HP_int &xf,const HP_int &two_pi_f,long long work) {
	HP_int q=hp_fixed_div(xf,two_pi_f);
	HP_int q_int ;
	if(q.v.size()>(size_t)work)q_int .v.assign(q.v.begin(),q.v.end()-work);
	else q_int =create_hp("0");
	q_int .trim_zeros();
	HP_int xr=xf-q_int *two_pi_f;
	while(xr.PANNI)xr=xr+two_pi_f;
	while(xr>=two_pi_f)xr=xr-two_pi_f;
	return xr;
}
inline HP_dec hp_pi(long long digits=0) {
	long long N=digits;
	if(N<=0) {
		N=HI_TO_LL(precision);
		if(N<40)N=100;
	}
	precision=create_hp(N+10);
	HP_int pi_f=hp_fixed_pi(N+10);
	return hp_round(hp_fixed_to_dec(pi_f,N+10),N);
}
inline HP_dec hp_sin(const HP_dec &x) {
	long long N=HI_TO_LL(precision);
	if(N<40)N=100;
	long long work=N+10;
	precision=create_hp(work);
	HP_int pi_f=hp_fixed_pi(work);
	HP_int two_pi_f=pi_f*HP_int (2);
	HP_int xf=hp_fixed(x,work);
	HP_int xr=hp_fixed_reduce(xf,two_pi_f,work);
	bool sign=false;
	if(xr>=pi_f) {
		xr=xr-pi_f;
		sign=true;
	}
	HP_int half_pi=hp_fixed_div_small(pi_f,2);
	if(xr>half_pi)xr=pi_f-xr;
	HP_int res=hp_fixed_sin_series(xr,work);
	if(sign)res.PANNI=!res.PANNI;
	return hp_round(hp_fixed_to_dec(res,work),N);
}
inline HP_dec hp_cos(const HP_dec &x) {
	long long N=HI_TO_LL(precision);
	if(N<40)N=100;
	long long work=N+10;
	precision=create_hp(work);
	HP_int pi_f=hp_fixed_pi(work);
	HP_int two_pi_f=pi_f*HP_int (2);
	HP_int xf=hp_fixed(x,work);
	HP_int xr=hp_fixed_reduce(xf,two_pi_f,work);
	bool sign=false;
	HP_int half_pi=hp_fixed_div_small(pi_f,2);
	if(xr>=pi_f) {
		xr=xr-pi_f;
		sign=true;
	}
	if(xr>half_pi) {
		xr=pi_f-xr;
		sign=!sign;
	}
	HP_int res=hp_fixed_cos_series(xr,work);
	if(sign)res.PANNI=!res.PANNI;
	return hp_round(hp_fixed_to_dec(res,work),N);
}
inline HP_dec hp_tan(const HP_dec &x) {
	long long N=HI_TO_LL(precision);
	if(N<40)N=100;
	precision=create_hp(N+10);
	HP_dec s=hp_sin(x);
	HP_dec c=hp_cos(x);
	if(c.is_zero())throw"tan在cos=0处无定义";
	return hp_round(s/c,N);
}
template<typename _T>
inline _T ALL_max(_T a,_T b){
	if(a>b)return a;
	else return b;
}
template<typename _T>
inline _T ALL_min(_T a,_T b){
	if(a<b)return a;
	else return b;
}
#endif
