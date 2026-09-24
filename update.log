### 2026.9.24 19:52
Starting from HP 1.5.3, we will start writing update logs.
### 2026.9.24 20:30
We find the bug:
```cpp
HP_dec(const vector<int> it,const vector<int> dc){
    this->integer=HP_int(it);
}
```
The constructor input vector ignored the decimal part.