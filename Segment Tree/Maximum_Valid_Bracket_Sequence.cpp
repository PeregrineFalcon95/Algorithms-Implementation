/*
Ref: https://codeforces.com/contest/381/problem/E

Sample case to test:
())(())(())(
7
1 1
2 3
1 2
1 12
8 12
5 11
2 10

*/



#include<bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);

struct Data {
    int opening = 0, closing = 0, complete = 0;
};
class solution{
private:
    Data combine(Data l, Data r){
        int matched = min(l.opening , r.closing);
        Data res;
        res.opening = l.opening + r.opening - matched;
        res.closing = l.closing + r.closing - matched;
        res.complete = l.complete + r.complete + matched;
        return res;
    }
    void build(int node, int le, int ri, string& s, vector < Data >& treeData){
        if ( le == ri ){
            if ( s [ le ] == '(')treeData [ node ].opening = 1;
            else treeData [ node ].closing = 1;
            return;
        }
        int mid = ( le+ri )>>1;
        build(node*2, le, mid, s, treeData);
        build(node*2+1, mid+1, ri, s, treeData);
        treeData [ node ] = combine(treeData [ node*2 ], treeData [ node*2+1]);
    }
    Data query(int node, int le, int ri, int lRange, int rRange, vector < Data>& treeData){
        Data res;
        if ( lRange > rRange ){
            res.opening = res.closing = res.complete = 0;
            return res;
        }
        if ( lRange == le && rRange == ri )return treeData [ node ];
        int mid = (le+ri)>>1;
        return combine(query(node*2, le, mid, lRange, min(rRange, mid), treeData), query(node*2+1, mid+1, ri, max(lRange, mid+1), rRange, treeData));
    }
public:
    void brainfuck(){
        string s;
        cin>>s;
        int m ;
        cin>>m;
        int n = s.size() - 1;
        vector < Data > treeData( max(n,1)*5 );
        build(1,0,n,s,treeData);
        while( m-- ){
            int le, ri;
            cin>>le>>ri;
            Data res = query(1,0,n,--le,--ri, treeData);
            cout<<res.complete * 2<<"\n";
        }
    }
};


int main(){
    fast
    solution solve;
    solve.brainfuck();
    return 0;
}

