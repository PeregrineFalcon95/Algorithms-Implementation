/*
Ref: https://cp-algorithms.com/data_structures/segment_tree.html

Sample case to test:
5 9
5 6 2 1 4
1 1 5
1 2 4
2 2 3
1 1 5
1 2 4
2 1 1
1 1 5
1 2 5
1 1 3
*/
#include<bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);

class segmentTree{
private:
    void build(int node, int le, int ri, vector < int >& ar, vector < int >& treeData){
        if ( le == ri ){
            treeData [ node ] = ar [ le ];
            return;
        }
        int mid = (le+ri)>>1;
        build(node*2, le, mid, ar, treeData);
        build(node*2+1, mid+1, ri, ar, treeData);
        treeData [ node ] = treeData [ node * 2 ] + treeData [ node * 2 + 1 ];
    }
    int query(int node, int le, int ri, int lRange, int rRange, vector < int >& treeData){
        if ( lRange > rRange )return 0;
        if ( lRange == le && rRange == ri )return treeData [ node ];
        
        int mid = (le+ri)>>1;
        return query (node*2, le, mid, lRange, min( rRange, mid ), treeData) + query (node*2+1, mid+1, ri, max(mid+1, lRange), rRange, treeData);
    }
    void update(int node, int le, int ri, int pos, int val, vector < int >& treeData){
        if ( le == ri )treeData [ node ] = val;
        else {
            int mid = (le+ri)>>1;
            if ( pos <= mid )update(node*2, le, mid, pos, val, treeData);
            else update(node*2+1, mid+1, ri, pos, val, treeData);
            treeData [ node ] = treeData [ node * 2 ] + treeData [ node * 2 + 1 ];
        }
    }
public:
    void inputAndPerform(){
        //N array size and M is the number of quires
        int n, m;
        cin>>n>>m;
        vector < int > ar (n+1);
        vector < int > treeData ( n * 4, 0 );
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
                cout<<query(1,1,n, lRange, rRange, treeData)<<"\n";
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