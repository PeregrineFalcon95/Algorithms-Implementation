/*
8 7
1 5 3 2 4 5 6 9
1 8
2 7
1 7
3 8
4 4
6 7
7 8
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define inf 1000000001
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
int t, cases;

static int k = 200; //Block size

struct queryData {
    int le, ri, idx;
};
bool cmp (queryData &a, queryData &b ){
    int k_a = a.le / k , k_b = b.le / k;
    if ( k_a == k_b )return a.ri < b.ri;
    return k_a < k_b;
}

class solution{
private:
    void add(int idx, int& sum, vector < int >& ar){
        sum += ar [ idx];
    }
    void remove(int idx, int& sum, vector < int >& ar){
        sum -= ar [ idx ];
    }
public:
    void inputAndPerform(){
        int n,q;
        cin>>n>>q;
        k = sqrt( ( (double)n * (double)q ) / (double)q );
        vector < queryData > qu (q+1);
        vector < int > ar (n+1), ans (q+1);
        for ( int i = 1; i <= n; i++ )cin>>ar [ i ];
        for ( int i = 1; i <= q; i++ ){
            cin>>qu [ i ].le>>qu [ i ].ri;
            qu [ i ].idx = i;
        }
        sort(qu.begin() +1, qu.begin() + q + 1, cmp);
        
        int currentL = 1, currentR = 0, sum = 0;
        for ( int i = 1; i <= q; i++ ){ //Offline quries
            while( currentL < qu [ i ].le )remove( currentL++, sum, ar );
            while( currentL > qu [ i ].le )add( --currentL, sum, ar );
            while( currentR < qu [ i ].ri )add( ++currentR, sum, ar );
            while( currentR > qu [ i ].ri )remove( currentR--, sum, ar );

            ans [ qu [ i ].idx ] = sum;
        }
        for ( int i = 1; i <= q; i++ )cout<<ans [ i ]<<"\n";
    }
};
int main(){
    fast
    solution obj;
    obj.inputAndPerform();
    return 0;
}