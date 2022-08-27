/*
Ref: 
Category: Given an undirected graph, find the articulation points. 
Sample Test Case:
9 10
1 2
1 3
2 3
2 4
4 5
5 7
7 8
5 8
4 6
6 9
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
    void artPoint(int root, int node, int& time_, vector < vector < int > >& graph, vector < bool >& vis, vector < bool >& isArtPoint, vector < int >& start, vector < int >& low, vector < int >& parent){
        vis [ node ] = true;
        time_++;
        start [ node ] = low [ node ] = time_;
        int sz = graph [ node ].size();
        int childCount = 0;
        for ( int i = 0; i < sz; i++ ){
            int child = graph [ node ] [ i ];
            if ( parent [ node ] == child )continue;
            
            if ( !vis [ child ] ){ //Tree edge
                childCount++;
                parent [ child ] = node;
                artPoint(root, child, time_, graph, vis, isArtPoint, start, low, parent);
                low [ node ] = min( low [ child ], low [ node] );
                if ( start [ node ] <= low [ child ] && node != root )isArtPoint [ node ] = true;
            }
            else  //Back edge
                low [ node ] = min( low [ node ], start [ child ] );
        }
        if ( node == root && childCount > 1 )isArtPoint [ root ] = true;
    }
public:
    void inputAndPerform(){
        int n,m, time_;
        cin>>n>>m;
        vector < int > start (n+1), low (n+1), parent (n+1, 0);
        vector < bool > vis ( n+1, false), isArtPoint(n+1, false);
        vector < vector < int > > graph ( n+1, vector < int > ());
        while( m-- ){
            int a,b;
            cin>>a>>b;
            graph [ a ].push_back( b );
            graph [ b ].push_back( a );
        }
        parent [ 1 ] = 1;
        artPoint(1,1,time_,graph,vis, isArtPoint, start, low, parent);
        cout<<"Articulation points are: \n";
        for ( int i = 1; i <= n; i++ )
            if ( isArtPoint [ i ] )cout<<i<<" ";
    }
};
int main(){
    fast
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    segmentTree obj;
    obj.inputAndPerform();
    return 0;
}