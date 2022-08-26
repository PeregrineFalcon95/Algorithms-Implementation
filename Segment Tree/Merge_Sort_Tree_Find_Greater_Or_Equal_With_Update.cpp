/*
Ref: https://cp-algorithms.com/data_structures/segment_tree.html
Category: Merge sort tree, find greater or equal value in a range with update.
Sample Test Case:
6 7
6 8 5 2 1 4
1 1 6 3
1 2 4 4
2 2 9
1 2 3 8
2 6 3
1 1 6 8
1 2 5 3
*/
#include<bits/stdc++.h>
using namespace std;
#define inf 1000000000
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
struct Data {
    int sum = 0, prefix = 0, suffix = 0, ans = 0;
};
int t, cases;
multiset < int > treeData [ 40001 ];
vector < int > ar ( 10001 );
class segmentTree{
private:
    void build(int node, int le, int ri ){
        treeData [ node ].clear();
        if ( le == ri )treeData [ node ].insert( ar [ le ] );
        else {
            int mid = (le+ri)>>1;
            build(node*2, le, mid);
            build(node*2+1, mid+1,ri);
            merge(treeData [node*2].begin(),treeData [node*2].end(), treeData [node*2+1].begin(),treeData [node*2+1].end(), inserter(treeData [node], treeData[ node].begin()));
        }
    }
    int query(int node, int le, int ri, int lRange, int rRange, int val ){
        if ( lRange > rRange )return inf;
        if ( lRange == le && rRange == ri ){
            auto it = treeData [ node ].lower_bound( val );
            if ( it == treeData [ node ].end() )return inf;
            return *it;
        }
        int mid = (le+ri)>>1;
        return min( query(node*2, le, mid, lRange, min(mid, rRange), val ), query(node*2+1, mid+1, ri, max(lRange, mid+1), rRange, val ) );
    }
    void update(int node, int le, int ri, int pos, int val){
        treeData [ node ].erase( treeData [ node ].find( ar [ pos ] ) );
        treeData [ node ].insert( val );
        if ( le < ri ){
            int mid = (le+ri)>>1;
            if ( pos <= mid )update(node*2, le, mid, pos, val);
            else update(node*2+1, mid+1, ri, pos, val);
        }
        else  ar [ pos ] = val;
    }
public:
    void inputAndPerform(){
        int n,q;
        cin>>n>>q;
        for ( int i = 1; i <= n; i++ )cin>>ar [ i ];
        
        build(1,1,n);

        while(q--){
            int type;
            cin>>type;
            if ( type == 1 ){
                //Query
                int l,r,val;
                cin>>l>>r>>val;
                val = query(1,1,n, l,r,val);
                if ( val == inf )cout<<"No value larger or equal\n";
                else cout<<val<<"\n";
            }
            else {
                //Update
                int pos, val;
                cin>>pos>>val;
                update(1, 1,n, pos, val);
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