#include<iostream>
#include<ctime>
#include<random>
#include<chrono>
using namespace std;



int randomNumGen(int l,int r){
    static default_random_engine e(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> u(l,r);
    return u(e);
}


int main(){

    cout << randomNumGen(2,10);


    return 0;
}