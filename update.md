### 2026.9.24 19:52
Starting from HP 1.5.3, we will start writing update logs.

### 2026.9.24 20:30
We find the BUG:
```cpp
HP_dec(const vector<int> it,const vector<int> dc){
    this->integer=HP_int(it);
}
```
The constructor input vector ignored the decimal part.

### 2026.9.24 20:52
```cpp
HP_int(vector<int> a){
    v=a;
}
```
We didn't speed up and consider the const parameter.

### 2026.9.24 20:57
We add the HP's input method.

### 2026.9.24 21:03
We not add the
```cpp
#include<climits>
```

### 2026.9.24 21:07
Input Stream Correction
```cpp
std::ostream& operator<<(std::ostream& os,const HP_int& num){
    num.out(os);
    return os; 
}
```

### 2026.9.24 21:27 push
HPint.h
HPdec.h
HPmath.h
HPannex.h

### 2026.9.26 13:15
find the bug:
Sign error when subtracting a positive number from a negative number.

### 2026.9.26 16:44(Not approved)
Fix a bug with subtracting a positive number from a negative number.

### 2026.9.26 16:54
Fix a bug with subtracting a positive number from a negative number.

### 2026.9.26 16:56
```cpp
void out(std::ostream& ost=std::cout) const{
    if(this->PANNI&&this->is_zero())ost<<"-";
    for(int i=0;i<v.size();i++)ost<<v[i];
    return;
}
```
The condition in out() was written the wrong way around.

### 2026.9.26 17:47
Fix the -0 output bug (out() printed "-" only when is_zero, condition was reversed).
