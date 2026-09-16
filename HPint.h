#pragma once
#ifndef HP_INT_H
#define HP_INT_H
#include<vector>
#include<string> 
#include<cmath>
#include<iostream>
#include<algorithm> 
#include<utility>
//#include<>
using std::vector;
using std::reverse;
using std::pair;
using std::cout;
//#define 
struct HP_int;//声明 
HP_int hp_div2(HP_int num);
inline long long HI_TO_LL(const HP_int& a);
inline void HP_abs(HP_int& a);//声明 
inline HP_int create_hp(const std::string& s);
inline HP_int create_hp(const long long& s);
const HP_int hp_one();
//hp_one.v={1};
struct HP_int{
	bool PANNI=false;//Positive and negative number identifiers 
	//负数:true PANNI
	//正数:false !PANNI
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
	HP_int(vector<int> a){
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
	bool operator <(long long a){
		return *this<create_hp(a);
	}
	bool operator <=(long long a){
		return (*this<=create_hp(a));
	}
	bool operator>(long long a){
		return *this>create_hp(a);
	}
	bool operator >=(long long a){
		return *this>=create_hp(a);
	}
	bool operator ==(long long a){
		return *this==create_hp(a);
	}
	bool operator !=(long long a){
		return *this!=create_hp(a);
	}
	HP_int operator +(const HP_int& b) const{
	    if(PANNI&&!b.PANNI){
	        HP_int s=*this;
	        HP_abs(s);
	        return b-s;
	    }
	    if(!PANNI&&b.PANNI){
	        HP_int s=b;
	        HP_abs(s);
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

	    for(;i<sum.v.size() && to>0;i++){
	        int s=sum.v[i]+to;
	        to=s/10;
	        sum.v[i]=s%10;
	    }
	    if(to>0){
	        sum.v.push_back(to);
	    }
	    reverse(sum.v.begin(),sum.v.end());
	    return sum;
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
	        HP_abs(tmp);
	        return *this+tmp;
	    }
	    if(PANNI){
	        HP_int tmp=*this;
	        HP_abs(tmp);
	        return b+tmp;
	    }
	    HP_int absA=*this;
	    HP_int absB=b;
	    HP_abs(absA);
	    HP_abs(absB);
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
	    bool res_sign=(PANNI != b.PANNI);
	    HP_int absA=*this;
	    HP_abs(absA);
	    HP_int absB=b;
	    HP_abs(absB);
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
	HP_int operator *(const int& it){
		return *this*(HP_int)(it);
	}
	HP_int& operator*=(const HP_int& b){
		*this=*this*b;
		return *this;
	} 
	HP_int operator/(const HP_int& b) const
	{
	    HP_int zero;
	    zero.v = {0};
	    zero.PANNI = false;
	    if (b == zero)
	    {
	        std::cerr << "Divide by zero!\n";
	        exit(EXIT_FAILURE);
	    }
	
	    bool res_sign = (PANNI != b.PANNI);
	    HP_int absA = *this;
	    
	    HP_abs(absA);
	    HP_int absB = b;
	    HP_abs(absB);
	
	    HP_int quotient;
	    HP_int base = absB;
	    HP_int step;
	    step.v = {1};
	    step.PANNI = false;
	
	    HP_int two = create_hp("2");
	
	    while (true)
	    {
	        HP_int next_base = base * two;
	        if (absA >= next_base)
	        {
	            base = next_base;
	            step = step * two;
	        }
	        else
	            break;
	    }
	
	    vector<std::pair<HP_int, HP_int>> buf;
	    while (!(base == zero))
	    {
	        buf.emplace_back(base, step);
	        base = hp_div2(base);
	        step = hp_div2(step);
	    }
	    for (auto& item : buf)
	    {
	        HP_int curr_base = item.first;
	        HP_int curr_step = item.second;
	        if (absA >= curr_base)
	        {
	            absA = absA - curr_base;
	            quotient = quotient + curr_step;
	        }
	    }
	
	    quotient.PANNI = res_sign;
	    if (quotient.v.size() == 1 && quotient.v[0] == 0)
	        quotient.PANNI = false;
	
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
	void out() const{
		if(this->PANNI/*&&(v.size()!=0&&v[0]!=0)*/)std::cout<<"-";
		for(int i=0;i<v.size();i++)std::cout<<v[i];
		return;
	}
	void F5(void){
		*this+=(long long)(0);
		int i=0;
		while(i<(size_t)v.size()&&v[i]==0){
			i++;
		}
		
		v.erase(v.begin(),v.begin()+i);
		if(v.size()==0)v.push_back(0);
	}
	bool isOdd() const{
	    int last_digit=v[v.size()-1];
	    return (last_digit%2)==1;
	}
	bool is_npos(){
		return 0;
	}
};
std::ostream& operator<<(std::ostream& os,const HP_int& num){
	num.out();
	return os; 
}
inline void HP_abs(HP_int& a){a.PANNI=0;}
inline HP_int create_hp(const std::string& s){
    HP_int num;num.v.clear();
    if(s.find("-")!=std::string::npos)num.PANNI=1;
    for(char c:s){if(c>='0'&&c<='9'){num.v.push_back(c - '0');}}
    if(num.v.empty())num.v.push_back(0);
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
    HP_abs(num);
    int carry=0;
    for(int digit:num.v){
        int cur=carry*10+digit;
        res.v.push_back(cur/2);
        carry = cur % 2;
    }

    size_t p=0;
    while(p<res.v.size()&&res.v[p]==0)
        p++;
    if(p==res.v.size()){
        res.v.clear();
        res.v.push_back(0);
    }
    else res.v.erase(res.v.begin(),res.v.begin()+p);
    return res;
}
inline long long HI_TO_LL(const HP_int& a){
    static const std::string MAXS="9223372036854775807";//LLONG_MAX
    static const std::string MINS="9223372036854775808";//|LLONG_MIN|
    bool neg=a.PANNI;
    std::string s;
    for(int d:a.v)s+=char('0'+d);
    size_t p=s.find_first_not_of('0');
    if(p==std::string::npos)return 0;
    s=s.substr(p);
    const std::string& limit=neg?MINS:MAXS;
    if(s.size()>limit.size()||(s.size()==limit.size()&&s>limit))return 0;//溢出
    unsigned long long u=0;
    for(char c:s)u=u*10+(unsigned)(c-'0');
    if(neg){
        if(u==9223372036854775808ULL)return LLONG_MIN;
        return -(long long)u;
    }
    return (long long)u;
}

#endif
