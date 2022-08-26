/*
Ref: https://cp-algorithms.com/data_structures/segment_tree.html
Category: Merge sort tree. Find the value greater or equal to the given value for a range.
Sample Test Case:
6 5
6 8 5 2 1 4
1 6 3
2 4 4
2 3 8
2 3 9
2 5 3
*/
#include<bits/stdc++.h>
using namespace std;
#define inf 1000000000
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
struct Data {
    int sum = 0, prefix = 0, suffix = 0, ans = 0;
};
int t, cases;
class segmentTree{
private:
    void build(int node, int le, int ri, vector < int >& ar,  vector < vector < int > >& treeData){
        if ( le == ri )treeData [ node ].push_back( ar [ le ] );
        else {
            int mid = (le+ri)>>1;
            build(node*2, le, mid, ar, treeData);
            build(node*2+1, mid+1,ri, ar, treeData);
            merge(treeData [node*2].begin(),treeData [node*2].end(), treeData [node*2+1].begin(),treeData [node*2+1].end(), back_inserter(treeData[ node]));
        }
    }
    int query(int node, int le, int ri, int lRange, int rRange, int val, vector < vector < int > >& treeData ){
        if ( lRange > rRange )return inf;
        if ( lRange == le && rRange == ri ){
            auto it = lower_bound(treeData [ node ].begin(), treeData [ node ].end(), val);
            if ( it == treeData [ node ].end() )return inf;
            return *it;
        }
        int mid = (le+ri)>>1;
        return min( query(node*2, le, mid, lRange, min(mid, rRange), val, treeData), query(node*2+1, mid+1, ri, max(lRange, mid+1), rRange, val, treeData) );
    }
public:
    void inputAndPerform(){
        int n,q;
        cin>>n>>q;
        vector < int > ar (n + 1);
        vector < vector < int > > treeData (n*4, vector < int >());
        for ( int i = 1; i <= n; i++ )cin>>ar [ i ];
        build(1,1,n, ar, treeData);
        while(q--){
            int l,r,val;
            cin>>l>>r>>val;
            val = query(1,1,n, l,r,val, treeData);
            if ( val == inf )cout<<"No value larger or equal\n";
            else cout<<val<<"\n";
        }
    }
};
int main(){
    fast
    segmentTree obj;
    obj.inputAndPerform();
    return 0;
}