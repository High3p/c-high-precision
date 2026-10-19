#pragma once
#ifndef HP_INT_H
#define HP_INT_H
#include<vector>
#include<string> 
#include<cmath>
#include<iostream>
#include<algorithm> 
#include<utility>
#include<climits>
//#include<>
using std::vector;
using std::reverse;
using std::pair;
using std::cout;
//#define 
struct HP_int;// 
HP_int hp_div2(HP_int num);
inline long long HI_TO_LL(const HP_int& a);
inline HP_int abs(HP_int a);// 
inline HP_int create_hp(const std::string& s);
inline HP_int create_hp(const long long& s);
static long long NTT_POW(long long a,long long e);
static void butterfly_transform(vector<int>&a,bool invert); 
const HP_int hp_one();
const long long NTT_MOD=2013265921;
const long long NTT_ROOT=31;
//hp_one.v={1};
struct HP_int{
	bool PANNI=false;//Positive and negative number identifiers 
	//:true PANNI
	//:false !PANNI
	vector<int> v={0};
	HP_int(std::string a){
//		long long f=a.find("-");
//		cout<<f<<"<-try\n";
//		if(f==std::string::npos){
			*this=create_hp(a);
//			cout<<1<<"<-try\n";
//		}else{
//			PANNI=0;
//			*this=a.substr(f+1);
//			cout<<2<<"<-try\n";
//		}
	}
	HP_int(long long ll):HP_int(std::to_string(ll)){
	}
	HP_int(int it):HP_int(std::to_string(it)){
	}
	HP_int(const vector<int>& a){
		v=a;
	}
	HP_int(vector<pair<int,int> > vpii){
		if(vpii.size()==0)return;
		v.clear();
		bool F=0;
		int i=0;
		if(vpii[0].second==-1)PANNI=1,i++;
		for(;i<vpii.size();i++){
			auto f=vpii[i];
			int a=f.first,b=f.second;
			if(b>=0&&b<=9){
				if(b!=0)F=1;
				if(F){
					for(int i=0;i<a;i++){
						v.push_back(b);
					}
				}
			}
		}
		if(!F)v.push_back(0);
	}
	HP_int(){
		
	}
	bool is_zero()const{return v.size()==1&&v[0]==0;}
	HP_int& trim_zeros(void){
		int i=0;
		while(i<(size_t)v.size()&&v[i]==0)i++;
		v.erase(v.begin(),v.begin()+i);
		if(v.size()==0)v.push_back(0);
		return *this;
	}
	bool operator >(const HP_int& b) const{
		size_t i=0; 
		bool y=1,n=0;
		if(PANNI||b.PANNI){
			if(PANNI&&!b.PANNI)return false;
			if(!PANNI&&b.PANNI)return true;
			if(PANNI&&b.PANNI)y=0,n=1;
		}
		if(v.size()>b.v.size())return y;
		if(v.size()<b.v.size())return n;
		for(;i<v.size();i++){
			if(v[i]>b.v[i])return y;
			if(v[i]<b.v[i])return n;
		}
		return false;
	} 
	bool operator <(const HP_int& b) const{return b>*this;}
	bool operator ==(const HP_int& b) const{
		if(is_zero()&&b.is_zero())return 1;
		if(PANNI!=b.PANNI)return 0; 
		if(v.size()!=b.v.size())return 0;
		for(size_t i=0;i<v.size();i++){
			if(v[i]!=b.v[i])return 0;
		}
		return 1;
	} 
	bool operator !=(const HP_int& b) const{return !(*this==b); }
	bool operator <=(const HP_int& b) const{return *this<b||*this==b; } 
	bool operator >=(const HP_int& b) const{return *this>b||*this==b;} 
	HP_int& operator =(const HP_int& b){
		if(&b==this)return *this;
		else v=b.v;
		PANNI=b.PANNI;
		return *this;
	}
	HP_int& operator =(const long long& b){
		return (*this=create_hp(b));
	}
	bool operator <(const long long& a)const{
		return *this<create_hp(a);
	}
	bool operator <=(const long long& a)const{
		return (*this<=create_hp(a));
	}
	bool operator>(const long long& a)const{
		return *this>create_hp(a);
	}
	bool operator >=(const long long& a)const{
		return *this>=create_hp(a);
	}
	bool operator ==(const long long& a)const{
		return *this==create_hp(a);
	}
	bool operator !=(const long long& a)const{
		return *this!=create_hp(a);
	}
	HP_int operator +(const HP_int& b) const{
	    if(PANNI&&!b.PANNI){
	        HP_int s=*this;
	        s=abs(s);
	        return b-s;
	    }
	    if(!PANNI&&b.PANNI){
	        HP_int s=b;
	        s=abs(s);
	        return *this-s;
	    }
	    HP_int sum,el;
	    if(v.size()>b.v.size()){
	        sum=*this;
	        el=b;
	    }else{
	        sum=b;
	        el=*this;
	    }
	    sum.PANNI=PANNI;
	    reverse(sum.v.begin(),sum.v.end());
	    reverse(el.v.begin(),el.v.end());
	
	    int to=0;
	    size_t i;

	    for(i=0;i<el.v.size();i++){
	        int s=sum.v[i]+el.v[i]+to;
	        to=s/10;
	        sum.v[i]=s%10;
	    }

	    for(;i<sum.v.size() && to>=0;i++){
	        int s=sum.v[i]+to;
	        to=s/10;
	        sum.v[i]=s%10;
	    }
	    if(to>0){
	        sum.v.push_back(to);
	    }
	    reverse(sum.v.begin(),sum.v.end());
	    return sum.trim_zeros();
	}
	HP_int operator +(const int& it){
		return *this+(HP_int)(it);
	}
	HP_int& operator++(){
	    *this=*this+hp_one();
	    return *this;
	}
	HP_int operator++(int){
	    HP_int tmp=*this;
	    *this=*this+hp_one();
	    return tmp;
	}
	HP_int& operator+=(const HP_int& b){
		*this=*this+b;
		return *this;
	} 
	const HP_int operator -(const HP_int& b) const{
	    if(b.PANNI){
	        HP_int tmp=b;
	        tmp=abs(tmp);
	        return *this+tmp;
	    }
	    if(PANNI){
	        HP_int res=*this;
	        res=abs(res);
            res+=b;
            if(res.is_zero()){
                res.PANNI=0;
                return res;
            }
            res.PANNI=1;
	        return res;
	    }
	    HP_int absA=*this;
	    HP_int absB=b;
	    absA=abs(absA);
	    absB=abs(absB);
	    HP_int res;
	    if(absA>absB){
	        res.PANNI=PANNI;
	        vector<int> ta=absA.v;
	        vector<int> tb=absB.v;
	        reverse(ta.begin(),ta.end());
	        reverse(tb.begin(),tb.end());
	        while(tb.size()<ta.size())tb.push_back(0);
	        int bo=0;
	        res.v.clear();
	        for(size_t i=0;i<ta.size();i++){
	            int da=ta[i];
	            int db=tb[i];
	            int diff=da-db-bo;
	            bo = 0;
	            if(diff < 0){
	                diff += 10;
	                bo = 1;
	            }
	            res.v.push_back(diff);
	        }
	        reverse(res.v.begin(), res.v.end());
	        while(res.v.size()>1&&res.v[0]==0)res.v.erase(res.v.begin());
	    }else if(absA<absB){
	        res.PANNI = !PANNI;
	        vector<int> ta=absB.v;
	        vector<int> tb=absA.v;
	        reverse(ta.begin(),ta.end());
	        reverse(tb.begin(),tb.end());
	        while(tb.size()<ta.size())tb.push_back(0);
	        int bo=0;
	        res.v.clear();
	        for(size_t i=0;i<ta.size();i++)
	        {
	            int da=ta[i];
	            int db=tb[i];
	            int diff=da-db-bo;
	            bo=0;
	            if(diff<0){
	                diff+=10;
	                bo=1;
	            }
	            res.v.push_back(diff);
	        }
	        reverse(res.v.begin(), res.v.end());
	        while(res.v.size()>1&&res.v[0]==0)res.v.erase(res.v.begin());
	    }else{
	        res.v={0};
	        res.PANNI=false;
	    }
	    return res;
	}
	HP_int operator -(const int& it){
		return *this-(HP_int)(it);
	}
	HP_int& operator--(){
	    *this=*this-hp_one();
	    return *this;
	}
	HP_int operator--(int){
	    HP_int tmp=*this;
	    *this=*this-hp_one();
	    return tmp;
	}
	HP_int& operator-=(const HP_int& b){
		*this=*this-b;
		return *this;
	} 
	HP_int operator*(const HP_int& b) const{
		if(this->v.size()<=(size_t)(64)&&b.v.size()<=(size_t)(64)){
		    bool res_sign=(PANNI != b.PANNI);
		    HP_int absA=*this;
		    absA=abs(absA);
		    HP_int absB=b;
		    absB=abs(absB);
			vector<int> a=absA.v;
		    vector<int> bv=absB.v;
		    reverse(a.begin(),a.end());
		    reverse(bv.begin(),bv.end());
		    vector<int> res(a.size()+bv.size(),0);
		    for(size_t i=0;i<a.size();i++){
		        long long carry = 0;
		        for(size_t j=0;j<bv.size()||carry>0;j++){
		            long long mul=(j < bv.size())?(long long)a[i]*bv[j]:0;
		            long long total=res[i+j]+mul+carry;
		            res[i+j]=total%10;
		            carry=total/10;
		        }
		    }
			reverse(res.begin(),res.end());
		    size_t p=0;
			while(p+1<res.size()&&res[p]==0)p++;
		    res.erase(res.begin(),res.begin() + p);
		    HP_int ans;
		    ans.v=res;
		    ans.PANNI=res_sign;
		    if(ans.v.size()==1&&ans.v[0]==0)ans.PANNI=false;
		    return ans;
		}
		//KARATSUBA
		else if(this->v.size()<=(size_t)(1024)&&b.v.size()<=(size_t)(1024)){
			bool res_sign = (PANNI != b.PANNI);
			HP_int A = *this; A.PANNI = false;
			HP_int Bn = b; Bn.PANNI = false;
			int n = std::max((int)A.v.size(), (int)Bn.v.size());
			int m = n / 2;
			HP_int a1, a0, b1, b0;
			if((int)A.v.size() <= m){
				a1=create_hp("0");
				a0=A;
			}else{
				a1.v.assign(A.v.begin(),A.v.begin()+((int)A.v.size()-m));
				a0.v.assign(A.v.begin()+((int)A.v.size()-m), A.v.end());
			}
			if((int)Bn.v.size()<=m){
				b1=create_hp("0");
				b0=Bn;
			}else{
				b1.v.assign(Bn.v.begin(),Bn.v.begin()+((int)Bn.v.size()-m));
				b0.v.assign(Bn.v.begin()+((int)Bn.v.size()-m),Bn.v.end());
			}
			HP_int z2=a1*b1,z0=a0*b0,z1=(a1+a0)*(b1+b0)-z2-z0;
			HP_int r2=z2;
			for(int i = 0; i < 2 * m; i++) r2.v.push_back(0);
			HP_int r1 = z1;
			for(int i = 0; i < m; i++) r1.v.push_back(0);
			HP_int ans = (r2 + r1 + z0).trim_zeros();
			ans.PANNI = res_sign && !ans.is_zero();
			return ans;
		}else{
			//NTT
		    bool neg=(PANNI!=b.PANNI);
		    vector<int>a=v;
		    vector<int>bb=b.v;
		    reverse(a.begin(),a.end());
		    reverse(bb.begin(),bb.end());
		    int need=(int)a.size()+(int)bb.size()-1;
		    int n=1;
		    while(n<need)n<<=1;
		    a.resize(n);
		    bb.resize(n);
		    butterfly_transform(a,0);
		    butterfly_transform(bb,0);
		    for(int i=0;i<n;i++)a[i]=(int)((long long)a[i]*bb[i]%NTT_MOD);
		    butterfly_transform(a,1);
		    vector<int>res;
		    res.reserve(need+1);
		    long long carry=0;
		    for(int i=0;i<need;i++){
		        long long cur=a[i]+carry;
		        res.push_back((int)(cur%10));
		        carry=cur/10;
		    }
		    while(carry){
		        res.push_back((int)(carry%10));
		        carry/=10;
		    }
		    while(res.size()>1&&res.back()==0)res.pop_back();
		    reverse(res.begin(),res.end());
		    HP_int ans;
		    ans.v=res;
		    ans.PANNI=neg;
		    if(ans.is_zero())ans.PANNI=false;
		    return ans;
		}

	}
	HP_int operator *(const long long& it){
		return *this*(HP_int)(it);
	}
	HP_int& operator*=(const HP_int& b){
		*this=*this*b;
		return *this;
	} 
	HP_int operator/(const HP_int& b) const{
	    HP_int zero;
	    zero.v={0};
	    zero.PANNI=false;
	    if (b==zero)throw "Divide by zero!\n";
	    bool res_sign=(PANNI != b.PANNI);
	    HP_int absA=*this;
	    absA=abs(absA);
	    HP_int absB=b;
	    absB=abs(absB);
	    HP_int quotient;
	    HP_int base=absB;
	    HP_int step;
	    step.v={1};
	    step.PANNI=false;
	    HP_int two=create_hp("2");
	    while(1){
	        HP_int next_base=base*two;
	        if (absA >= next_base){
	            base=next_base;
	            step=step*two;
	        }
	        else break;
	    }
	    vector<std::pair<HP_int, HP_int>> buf;
	    while (!(base == zero)){
	        buf.emplace_back(base, step);
	        base = hp_div2(base);
	        step = hp_div2(step);
	    }
	    for(auto& item:buf){
	        HP_int curr_base=item.first;
	        HP_int curr_step=item.second;
	        if(absA>=curr_base){
	            absA=absA-curr_base;
	            quotient=quotient+curr_step;
	        }
	    }
	    quotient.PANNI=res_sign;
	    if (quotient.v.size()==1&&quotient.v[0]==0)quotient.PANNI=false;
	    return quotient;
	}
	HP_int operator /(const int& it){
		return *this/(HP_int)(it);
	}
	HP_int& operator/=(const HP_int& b){
		*this=*this/b;
		return *this;
	}
	HP_int operator%(const HP_int& b)const{return *this-(*this/b)*b; }
	HP_int& operator%=(const HP_int& b){
		*this=*this%b;
		return *this;
	}
	HP_int operator %(const int& it){
		return *this%(HP_int)(it);
	}
	void out(std::ostream& ost=std::cout) const{
		if(this->PANNI&&!this->is_zero())ost<<"-";
		for(int i=0;i<v.size();i++)ost<<v[i];
		return;
	}
	bool isOdd() const{
	    int last_digit=v[v.size()-1];
	    return (last_digit%2)==1;
	}
	bool is_valid(void)const{
        if(!v.size())return 0;
        for(int now:v)if(now<0||now>9)return 0;
		return 1;
	}
};
//Compatible
inline HP_int operator+(const long long& a,const HP_int& b){return HP_int(a)+b;}
inline HP_int operator-(const long long& a,const HP_int& b){return HP_int(a)-b;}
inline HP_int operator*(const long long& a,const HP_int& b){return HP_int(a)*b;}
inline HP_int operator/(const long long& a,const HP_int& b){return HP_int(a)/b;}
inline HP_int operator%(const long long& a,const HP_int& b){return HP_int(a)%b;}
inline bool operator==(const long long& a,const HP_int& b){return HP_int(a)==b;}
inline bool operator!=(const long long& a,const HP_int& b){return HP_int(a)!=b;}
inline bool operator<(const long long& a,const HP_int& b){return HP_int(a)<b;}
inline bool operator<=(const long long& a,const HP_int& b){return HP_int(a)<=b;}
inline bool operator>(const long long& a,const HP_int& b){return HP_int(a)>b;}
inline bool operator>=(const long long& a,const HP_int& b){return HP_int(a)>=b;}
//Compatible
std::ostream& operator<<(std::ostream& os,const HP_int& num){
	num.out(os);
	return os; 
}
std::istream& operator>>(std::istream& is,HP_int& num){
	std::string in="";
	is>>in;
	num=(HP_int)(in);
	return is; 
}
inline HP_int abs(HP_int a){a.PANNI=0;return a;}
inline HP_int create_hp(const std::string& s){
    HP_int num;
	num.v.clear();
	num.PANNI = false;
	size_t start = 0;
    if(s.find("-") != std::string::npos){
		num.PANNI = true;
		start = 1;
	}
    for(size_t i = start; i < s.size(); i++){
		char c = s[i];
		if(c >= '0' && c <= '9'){
			num.v.push_back(c - '0');
		}
	}
    if(num.v.empty()) num.v.push_back(0);
	num.trim_zeros();
	if(num.is_zero()) num.PANNI = false;
    return num;
}
inline HP_int create_hp(const long long& s){
    return create_hp(std::to_string(s));
}
inline const HP_int hp_one(){return create_hp("1");}
HP_int hp_div2(HP_int num){
    HP_int res;
    res.v.clear();
    res.PANNI=0;
    num=abs(num);
    int carry=0;
    for(int digit:num.v){
        int cur=carry*10+digit;
        res.v.push_back(cur/2);
        carry = cur % 2;
    }

    size_t p=0;
    while(p<res.v.size()&&res.v[p]==0)p++;
    if(p==res.v.size()){
        res.v.clear();
        res.v.push_back(0);
    }
    else res.v.erase(res.v.begin(),res.v.begin()+p);
    return res;
}
inline long long HI_TO_LL(const HP_int& a){
    static const std::string MAXS = "9223372036854775807";
    static const std::string MINS = "9223372036854775808";
    bool neg = a.PANNI;
    std::string s;
    for(int d : a.v) s += char('0' + d);
    size_t p = s.find_first_not_of('0');
    if(p == std::string::npos) return 0;
    s = s.substr(p);
    const std::string& limit = neg ? MINS : MAXS;
    if(s.size() > limit.size() || (s.size() == limit.size() && s > limit)){
		throw "HP_int value out of long long range!";
	}
    unsigned long long u = 0;
    for(char c : s) u = u * 10 + (unsigned)(c - '0');
    if(neg){
        if(u == 9223372036854775808ULL) return LLONG_MIN;
        return -(long long)u;
    }
    return (long long)u;
}
static long long NTT_POW(long long a,long long e) {
	long long r=1;
	while(e) {
		if(e&1)r=r*a%NTT_MOD;
		a=a*a%NTT_MOD;
		e>>=1;
	}
	return r;
}
static void butterfly_transform(vector<int>& a, bool invert){
    int n=(int)a.size();
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        for(;j&bit;bit>>=1)j^=bit;
        j^=bit;
        if(i<j)std::swap(a[i],a[j]);
    }
    for(int len=2;len<=n;len<<=1){
        long long wlen=NTT_POW(NTT_ROOT,(NTT_MOD-1)/len);
        if(invert)wlen=NTT_POW(wlen,NTT_MOD-2);
        for(int i=0;i<n;i+=len){
            long long w=1;
            for(int j=0;j<len/2;j++){
                int u=a[i+j];
                int v=(int)(a[i+j+len/2]*w%NTT_MOD);
                a[i+j]=(int)(((long long)u+v)%NTT_MOD);
                a[i+j+len/2]=(int)(((long long)u-v+NTT_MOD)%NTT_MOD);
                w=w*wlen%NTT_MOD;
            }
        }
    }
    if(invert){
        long long inv_n=NTT_POW(n,NTT_MOD-2);
        for(int &x:a)x=(int)(x*inv_n%NTT_MOD);
    }
}
#endif
