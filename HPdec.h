#pragma once
#ifndef HP_DEC_H
#define HP_DEC_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include<utility>
#include<cmath>
#include"HPint.h"
struct HP_dec;
struct HP_int;
static HP_int precision=create_hp("-1");
inline HP_dec create_hp_dec(const std::string& s); 
struct HP_dec
{
    bool PANNI = false;
//	static const HP_int npos=HP_int((vector<pair<int,int>>){{3,-3}});
    HP_int integer;
    std::vector<int> frac;
    HP_dec(const vector<int> it,const vector<int> dc){
    	this->integer=HP_int(it);
    	this->frac=dc;
	}
    HP_dec(const std::string& a){
    	*this=create_hp_dec(a);
	}
	HP_dec(const char * c):HP_dec(std::string(c)){
		
	}
	HP_dec(const HP_int& a){
		integer=a;
	}
	HP_dec(vector<pair<int,int> > vpii){
		bool j=0,x=0;
		int t=vpii.size();
		for(int i=0;i<t;i++){
			int a=vpii[i].first,b=vpii[i].second;
			if((b==-2||a==-2)&&!j){
				j=1;
				PANNI=1;
			}
			if((a==-1||b==-1)&&!x){
				x=1;
			}
			if(b>=0&&b<=9){
				if(!x){
					for(int y=0;y<a;y++)integer.v.push_back(b);
				}
				if(x){
					for(int y=0;y<a;y++)frac.push_back(b);
				}
			}
		}
		integer.F5();
	}
	HP_dec(){
		
	}
	bool operator==(const HP_dec& b)const{
	    if(PANNI!=b.PANNI)return false;
	    if(!(integer==b.integer))return false;
	    if(frac.size()!=b.frac.size()){
	        size_t maxlen=std::max(frac.size(), b.frac.size());
	        for(size_t i=0;i<maxlen;i++){
	            int da=(i<frac.size())?frac[i]:0;
	            int db=(i<b.frac.size())?b.frac[i]:0;
	            if(da!=db)return false;
	        }
	        return true;
	    }
	    return frac==b.frac;
	}
	bool operator<(const HP_dec& b)const{
	    bool negA=PANNI;
	    bool negB=b.PANNI;
	    if(negA&&!negB)return true;
	    if(!negA&&negB)return false;
	    if(!negA&&!negB){
	        if(integer>b.integer)return false;
	        if(integer<b.integer)return true;
	        size_t maxlen=std::max(frac.size(), b.frac.size());
	        for(size_t i=0;i<maxlen;i++){
	            int da=(i<frac.size())?frac[i]:0;
	            int db=(i<b.frac.size())?b.frac[i]:0;
	            if(da<db)return true;
	            if(da>db)return false;
	        }
	        return false;
	    }
	    else{
	        if(integer>b.integer)return true;
	        if(integer<b.integer)return false;
	        size_t maxlen=std::max(frac.size(),b.frac.size());
	        for(size_t i=0;i<maxlen;i++){
	            int da=(i<frac.size())?frac[i]:0;
	            int db=(i<b.frac.size())?b.frac[i]:0;
	            if(da>db)return true;
	            if(da<db)return false;
	        }
	        return false;
	    }
	}
	bool operator!=(const HP_dec& b)const{ return !(*this==b);}
	bool operator>(const HP_dec& b)const{ return b<*this;}
	bool operator<=(const HP_dec& b)const{ return !(*this>b);}
	bool operator>=(const HP_dec& b)const{ return !(*this<b);}
    void trim_tail_frac()
    {
        while(!frac.empty() && frac.back() == 0) frac.pop_back();
    }

    static void align(HP_dec& a, HP_dec& b)
    {
        size_t max_len = std::max(a.frac.size(), b.frac.size());
        while(a.frac.size() < max_len) a.frac.push_back(0);
        while(b.frac.size() < max_len) b.frac.push_back(0);
    }

    HP_dec operator+(const HP_dec& b) const
    {
        HP_dec ta = *this, tb = b;
        align(ta, tb);
        size_t f_len = ta.frac.size();

        HP_int pow10("1");
        for(size_t i = 0; i < f_len; i++) pow10 = pow10 * HP_int("10");

        HP_int fracA; fracA.v.clear();
        for(int d : ta.frac) fracA.v.push_back(d);
        if(fracA.v.empty()) fracA.v.push_back(0);

        HP_int fracB; fracB.v.clear();
        for(int d : tb.frac) fracB.v.push_back(d);
        if(fracB.v.empty()) fracB.v.push_back(0);

        HP_int totalA = ta.integer * pow10 + fracA;
        totalA.PANNI = ta.PANNI;
        HP_int totalB = tb.integer * pow10 + fracB;
        totalB.PANNI = tb.PANNI;

        HP_int res = totalA + totalB;
        bool sign = res.PANNI;
        res.PANNI = false;

        HP_dec ret;
        ret.PANNI = sign;
        ret.integer = res / pow10;
        std::vector<int> temp = (res % pow10).v;
        while(temp.size() < f_len) temp.insert(temp.begin(), 0);
        ret.frac.swap(temp);
        ret.trim_tail_frac();
        return ret;
    }

    HP_dec operator-(const HP_dec& b) const
    {
        HP_dec ta = *this, tb = b;
        align(ta, tb);
        size_t f_len = ta.frac.size();

        HP_int pow10("1");
        for(size_t i = 0; i < f_len; i++) pow10 = pow10 * HP_int("10");

        HP_int fracA; fracA.v.clear();
        for(int d : ta.frac) fracA.v.push_back(d);
        if(fracA.v.empty()) fracA.v.push_back(0);

        HP_int fracB; fracB.v.clear();
        for(int d : tb.frac) fracB.v.push_back(d);
        if(fracB.v.empty()) fracB.v.push_back(0);

        HP_int totalA = ta.integer * pow10 + fracA;
        totalA.PANNI = ta.PANNI;
        HP_int totalB = tb.integer * pow10 + fracB;
        totalB.PANNI = tb.PANNI;

        HP_int res = totalA - totalB;
        bool sign = res.PANNI;
        res.PANNI = false;

        HP_dec ret;
        ret.PANNI = sign;
        ret.integer = res / pow10;
        std::vector<int> temp = (res % pow10).v;
        while(temp.size() < f_len) temp.insert(temp.begin(), 0);
        ret.frac.swap(temp);
        ret.trim_tail_frac();
        return ret;
    }

    HP_dec operator*(const HP_dec& b) const
    {
        HP_dec ta = *this, tb = b;
        size_t fa = ta.frac.size(), fb = tb.frac.size();

        HP_int powA("1");
        for(size_t i = 0; i < fa; i++) powA = powA * HP_int("10");
        HP_int powB("1");
        for(size_t i = 0; i < fb; i++) powB = powB * HP_int("10");

        HP_int fracA; fracA.v.clear();
        for(int d : ta.frac) fracA.v.push_back(d);
        if(fracA.v.empty()) fracA.v.push_back(0);

        HP_int fracB; fracB.v.clear();
        for(int d : tb.frac) fracB.v.push_back(d);
        if(fracB.v.empty()) fracB.v.push_back(0);

        HP_int A = ta.integer * powA + fracA; A.PANNI = ta.PANNI;
        HP_int B = tb.integer * powB + fracB; B.PANNI = tb.PANNI;
		HP_int res= A * B;
//        else res=precision;
        bool sign = res.PANNI;
        res.PANNI = false;

        size_t total_f = fa + fb;
        HP_int pow_total("1");
        for(size_t i = 0; i < total_f; i++) pow_total = pow_total * HP_int("10");

        HP_dec ret;
        ret.PANNI = sign;
        ret.integer = res / pow_total;
        std::vector<int> temp = (res % pow_total).v;
        while(temp.size() < total_f) temp.insert(temp.begin(), 0);
        ret.frac.swap(temp);
        ret.trim_tail_frac();
//        if(!(precision<=0)){
////	        long long n=0;
////	        std::string s;
////	        for(int d:precision.v)s+=char('0'+d);
////	        n=std::stoll(s);
////	        if(ret.frac.size()>(size_t)n){
////	            int round_digit=ret.frac[n];
////	            ret.frac.resize(n);
////	            if(round_digit >=5){
////	                HP_dec add_one;
////	                add_one.integer=HP_int("0");
////	                add_one.frac.assign(n,0);
////	                add_one.frac.back()=1;
////	                ret=ret+add_one;
////	            }
////	            ret.trim_tail_frac();
////	        }
//			if((HP_int)((long long)ret.frac.size())<=precision)return ret;
//			while((HP_int)((long long)ret.frac.size())>precision)ret.frac.pop_back();
//    	}
    	if(!(precision<=0)){
		    long long n=HI_TO_LL(precision);
		    if((long long)(ret.frac.size())<=n)return ret;
		    int round_digit=ret.frac[n];
		    ret.frac.resize(n);
		    if(round_digit>=5){
		        if(n==0){
		            HP_dec add_one;
		            add_one.integer=HP_int(1);
		            ret=ret+add_one;
		        }else{
		            HP_dec add_one;
		            add_one.integer=HP_int(0);
		            add_one.frac.assign(n,0);
		            add_one.frac.back()=1;
		            ret=ret+add_one;
		        }
		    }
		    ret.trim_tail_frac();
		}

        return ret;
    }

    HP_dec operator/(const HP_dec& b)const{
        HP_dec ta=*this;
        size_t fa=ta.frac.size();
        size_t fb=b.frac.size();
        size_t out_frac=fa*fb;
        HP_int powA("1");
        for(size_t i = 0; i < fa; i++) powA = powA * HP_int("10");
        HP_int powB("1");
        for(size_t i = 0; i < fb; i++) powB = powB * HP_int("10");
        HP_int fracA; fracA.v.clear();
        for(int d : ta.frac) fracA.v.push_back(d);
        if(fracA.v.empty()) fracA.v.push_back(0);
        HP_int fracB; fracB.v.clear();
        for(int d : b.frac) fracB.v.push_back(d);
        if(fracB.v.empty()) fracB.v.push_back(0);
        HP_int A = ta.integer * powA + fracA; A.PANNI = ta.PANNI;
        HP_int B = b.integer * powB + fracB; B.PANNI = b.PANNI;
        HP_dec zero;
        zero.PANNI=false;zero.integer=HP_int("0");zero.frac.clear();
        if(B.is_zero())return zero;
        HP_int pow_out("1");
        for(size_t i=0;i<out_frac;i++)pow_out=pow_out*HP_int("10");
        HP_int numerator=A*pow_out;
        HP_int res_total=numerator/B;
        bool sign=(A.PANNI!=B.PANNI);
        res_total.PANNI=0;
        HP_dec ret;
        ret.PANNI=sign;
        ret.integer=res_total/pow_out;
        std::vector<int> temp=(res_total%pow_out).v;
        while(temp.size()<out_frac)temp.insert(temp.begin(),0);
        ret.frac.swap(temp);
        ret.trim_tail_frac();
        return ret;
    }
    HP_dec& operator+=(const HP_dec& b){*this=*this+b;return *this;}
    HP_dec& operator-=(const HP_dec& b){*this=*this-b;return *this;}
    HP_dec& operator*=(const HP_dec& b){*this=*this*b;return *this;}
    HP_dec& operator/=(const HP_dec& b){*this=*this/b;return *this;}
    HP_dec& operator++(){
        HP_dec one = create_hp_dec("1");
        *this = *this + one;
        return *this;
    }
    HP_dec& operator--(){
        HP_dec one=create_hp_dec("1");
        *this=*this-one;
        return *this;
    }
    HP_dec operator++(int){HP_dec tmp=*this;++(*this); return tmp;}
    HP_dec operator--(int){HP_dec tmp=*this;--(*this); return tmp;}
    bool is_npos(){
    	if(integer.is_npos())return 0;
    	for(int r:frac){if(r<0||r>9)return 0;}
		return 1;
	}
};
inline std::ostream& operator<<(std::ostream& os,const HP_dec& num)
{
    if(num.PANNI) os<<'-';
    os<<num.integer;
    if(!num.frac.empty())
    {
        os<<".";
        for(int d:num.frac) os<<d;
    }
    return os;
}
std::istream& operator>>(std::istream& is,HP_dec& num){
	std::string in="";
	is>>in;
	num=HP_dec(in);
	return is; 
}
inline HP_dec create_hp_dec(const std::string& s)
{
    HP_dec res;
    res.PANNI = false;
    res.integer = HP_int("0");
    res.frac.clear();
    size_t i = 0;
    if(i < s.size() && s[i] == '-'){ res.PANNI = true; i++; }

    std::string int_part;
    size_t dot_pos = std::string::npos;
    for(;i<s.size();i++)
    {
        if(s[i]=='.'){ dot_pos = i; break; }
        int_part.push_back(s[i]);
    }
    if(!int_part.empty()) res.integer = create_hp(int_part);

    if(dot_pos != std::string::npos)
    {
        for(size_t k=dot_pos+1;k<s.size();k++)
        {
            char ch = s[k];
            if(ch>='0'&&ch<='9') res.frac.push_back(ch-'0');
        }
    }
    res.trim_tail_frac();
    return res;
}
#endif
