#include<bits/stdc++.h>
using namespace std;

string calcFactorial(int n){

    string factorial="1";

    long long y,c=0;

    for(int j=2;j<=n;j++){
        for(int i=0;i<factorial.length();i++){
            y = (factorial[i]-'0')*j+c;
            factorial[i]=y%10+'0';
            c=y/10;
        }
        while(c){
            factorial+=c%10+'0';
            c/=10;
        }
    }

    reverse(factorial.begin(),factorial.end());

    return factorial;
}

int main()
{
    int n;
    cin>>n;

    cout<<calcFactorial(n);
}
