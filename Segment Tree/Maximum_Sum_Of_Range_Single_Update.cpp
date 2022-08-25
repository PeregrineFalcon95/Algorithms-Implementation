/*
Ref: https://cp-algorithms.com/data_structures/segment_tree.html

Sample case to test:
6 6
1 -2 5 -3 6 -1
1 1 6
2 2 2
1 2 5
1 2 6
1 4 6
1 2 2
*/
#include<bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
struct Data {
    int sum = 0, prefix = 0, suffix = 0, ans = 0;
};
class segmentTree{
private:
    Data combine(Data l, Data r){
        Data res;
        res.sum = l.sum + r.sum;
        res.prefix = max(l.prefix, l.sum + r.prefix);
        res.suffix = max(r.suffix, r.sum + l.suffix);
        res.ans = max(max(r.ans, l.ans), l.suffix + r.prefix);
        return res;
    }
    Data makeData(int val){
        Data res;
        res.sum = val;
        res.prefix = res.suffix = res.ans = max(val, 0);
        return res;
    }
    void build(int node, int le, int ri, vector < int >& ar, vector < Data >& treeData){
        if ( le == ri ){
            treeData [ node ] = makeData(ar [ le ]);
            return;
        }
        int mid = (le+ri)>>1;
        build(node *2, le, mid, ar, treeData);
        build(node * 2 + 1, mid+1, ri, ar, treeData);
        treeData [ node ] = combine(treeData [ node * 2], treeData [ node * 2 + 1 ]);
    }
    Data query(int node, int le, int ri, int lRange, int rRange, vector < Data >& treeData){
        if ( lRange > rRange )return makeData(0);
        if ( lRange == le && rRange == ri )return treeData [ node ];
        int mid = (le+ri)>>1;
        return combine( query(node*2, le, mid, lRange, min(mid,rRange), treeData) , query(node*2+1, mid+1, ri, max(lRange, mid+1), rRange, treeData) );
    }
    void update(int node, int le, int ri, int pos, int val, vector < Data >& treeData){
        if ( le == ri ){
            treeData [ node ] = makeData(val);
            return;
        }
        int mid = (le+ri)>>1;
        if ( pos <= mid )update(node*2, le, mid, pos, val, treeData);
        else update(node*2+1, mid+1, ri, pos, val, treeData);
        treeData [ node ] = combine(treeData [ node*2 ], treeData [ node*2+1] );
    }
public:
    void inputAndPerform(){
        //N array size and M is the number of quires
        int n, m;
        cin>>n>>m;
        vector < int > ar (n+1);
        vector < Data > treeData ( n * 4 );
        for ( int i = 1; i <= n; i++ )cin>>ar [ i ];
        
        //Build the segment tree from input array
        build(1, 1, n, ar, treeData);
        
        //Query part. 
        while( m-- ){
            int type;
            cin>>type;
            if ( type == 1 ){
                //Query
                int lRange, rRange;
                cin>>lRange>>rRange;
                Data res = query(1,1,n, lRange,rRange, treeData);
                cout<<res.ans<<"\n";
            }
            else {
                //Update
                int pos, val;
                cin>>pos>>val;
                update(1,1,n, pos, val, treeData);
            }
        }
    }
};
int main(){
    fast
    segmentTree obj;
    obj.inputAndPerform();
    return 0;
}