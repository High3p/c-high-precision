#pragma once
#ifndef HP_MATH_H
#define HP_MATH_H
#include<cmath>
#include"HPdec.h"
inline HP_dec HPpow(const HP_dec& g,HP_int i){
	if(g==create_hp_dec("0.0"))return g;
	HP_dec sum="1.0",h=g;
	while(!(i).is_zero()){
		if(i.isOdd()){
            sum=sum*h;
        }
        h*=h;
        i=hp_div2(i);
        i.F5();
	}
	return sum;
}
inline HP_int HPpow(const HP_int& g,HP_int i){
	if(g==create_hp("0"))return g;
	HP_int sum=hp_one(),h=g;
	while(!(i).is_zero()){
		if(i.isOdd()){
            sum=sum*h;
        }
        h*=h;
        i=hp_div2(i);
        i.F5();
	}
	return sum;
}
inline double HPpow(const double& g,int i){
	return pow((g),i);
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
