/*
Ref: https://cp-algorithms.com/data_structures/segment_tree.html

Note: Only positive numbers are handles within 32 bit integer range.
Sample case to test:
6 9
2 1 5 3 5 4
1 4 4
1 1 6
2 4 6
1 1 6
1 2 5
2 5 6
1 2 6
1 5 6
1 1 6
*/
#include<bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);

class segmentTree{
private:
    pair < int , int > combine(pair<int, int> a, pair<int, int> b){
        if ( a.first > b.first )return a;
        if ( b.first > a.first )return b;
        return make_pair(a.first, a.second + b.second);
    } 
    void build(int node, int le, int ri, vector < int >& ar, vector < pair < int , int > >& treeData){
        if ( le == ri ){
            treeData [ node ] = make_pair(ar [le], 1);
            return;
        }
        int mid = (le+ri)>>1;
        build(node*2, le, mid, ar, treeData);
        build(node*2+1, mid+1, ri, ar, treeData);
        treeData [ node ] = combine( treeData [ node * 2 ] , treeData [ node * 2 + 1 ]);
    }
    pair <int, int> query(int node, int le, int ri, int lRange, int rRange, vector < pair < int , int > >& treeData){
        if ( lRange > rRange )return make_pair(0,0);
        if ( lRange == le && rRange == ri )return treeData [ node ];
        
        int mid = (le+ri)>>1;
        return combine(query (node*2, le, mid, lRange, min( rRange, mid ), treeData) , query (node*2+1, mid+1, ri, max(mid+1, lRange), rRange, treeData));
    }
    void update(int node, int le, int ri, int pos, int val, vector < pair < int , int > >& treeData){
        if ( le == ri )treeData [ node ] = make_pair(val,1);
        else {
            int mid = (le+ri)>>1;
            if ( pos <= mid )update(node*2, le, mid, pos, val, treeData);
            else update(node*2+1, mid+1, ri, pos, val, treeData);
            treeData [ node ] = combine(treeData [ node * 2 ] , treeData [ node * 2 + 1 ]);
        }
    }
public:
    void inputAndPerform(){
        //N array size and M is the number of quires
        int n, m;
        cin>>n>>m;
        vector < int > ar (n+1);
        vector < pair < int , int > > treeData ( n * 4, make_pair(0,0) );
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
                pair <int, int> ans = query(1,1,n, lRange, rRange, treeData);
                cout<<"Max: "<<ans.first<<" Occur: "<<ans.second<<"\n";
            }
            else {
                //Update
                int pos, val;
                cin>>pos>>val;
                update(1,1,n, pos,val, treeData);
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