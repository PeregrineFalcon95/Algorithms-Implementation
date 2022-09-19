/*
Ref: https://www.topcoder.com/thrive/articles/Maximum%20Flow:%20Part%20One
Category: 
Sample Test Case:
4 5
1 2 3
2 4 2
1 3 4
3 4 5
4 1 3
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define inf 1000000001
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
int t, cases;


class solution{
int cost [ 501 ] [ 501 ], revCost [ 501 ] [ 501 ], bootleNeckCostArray [ 501 ];
vector < int > graph [ 501 ], revGraph [ 501 ];
private:
    void clearPrevData(){
        memset(cost, 0, sizeof cost);
        memset(revCost, -1, sizeof revCost);
        for ( int i = 0; i <= 500; i++ ){
            graph [ i ].clear();
            revGraph [ i ].clear();
        }
    }
    void makeGraph(int n ){
        for ( int i = 1; i <= n; i++ ){
            for ( int j = 1; j <= n; j++ ){
                if ( cost [ i ] [ j ] ){
                    graph [ i ].push_back( j );
                    revGraph [ j ].push_back ( i );
                    revCost [ j ] [ i ] = 0;
                }
            }
        }
    }
    int maxFlow(int source, int target, int n){
        while( augmentedPath(source, target, n) )continue;
        int ans = 0;
        for ( int i = 1; i <= n; i++ )
            if ( revCost [ i ] [ source ] != -1 )ans += revCost [ i ] [ source ];
        return ans;
    }
    bool augmentedPath(int source, int target, int n){
        bool vis [ n+1 ];
        int parent [ 2 ] [ n+1 ];
        memset(vis, false, sizeof vis);
        memset(parent, -1, sizeof parent);

        queue < pair < int , int > > qu;
        qu.push( {source, inf} );
        vis [ source ] = true;
        parent [ 0 ] [ source ] = source; ///Parent [ 0 ] is used for parent of node
        parent [ 1 ] [ source ] = 1; ///Parent [ 1 ] is used for mark if the parent is in original graph or reverse graph.

        while( !qu.empty() ){
            int frontNode = qu.front().first;
            int bootleNeckCost = qu.front().second;
            qu.pop();

            int sz = graph [ frontNode ].size();
            for ( int i = 0; i < sz; i++ ){
                int child = graph [ frontNode ] [ i ];
                if ( !vis [ child ] && cost [ frontNode ] [ child ]  ){
                    vis [ child ] = true;
                    qu.push( {child, min(bootleNeckCost, cost [ frontNode ] [ child ]) } );
                    parent [ 0 ] [ child ] = frontNode;
                    parent [ 1 ] [ child ] = 1;
                    bootleNeckCostArray [ child ] = min(bootleNeckCost, cost [ frontNode ] [ child ] );
                } 
            }

            sz = revGraph [ frontNode ].size();
            for ( int i = 0; i < sz; i++ ){
                int child = revGraph [ frontNode ] [ i ];
                if ( !vis [ child ] && revCost [ frontNode ] [ child ] ){
                    vis [ child ] = true;
                    qu.push( {child, min(bootleNeckCost, revCost [ frontNode ] [ child ])} );
                    parent [ 0 ] [ child ] = frontNode;
                    parent [ 1 ] [ child ] = 2;
                    bootleNeckCostArray [ child ] = min( bootleNeckCost, revCost [ frontNode ] [ child ]);
                }
            }
        }
        int temp = bootleNeckCostArray [ target ];
        if ( !vis [ target ] )return false;

        for ( int i = target; ; i = parent [ 0 ] [ i ] ){
            int a = parent [ 0 ] [ i ];
            if ( parent [ 1 ] [ i ] == 1 ){
                cost [ a ] [ i ] -= temp;
                revCost [ i ] [ a ] += temp;
            }
            else {
                revCost [ a ] [ i ] -= temp;
                cost [ i ] [ a ] += temp;
            }
            if ( a == source )break;
        }
        return true;
    }
public:
    void inputAndPerform(){
        int n, m;
        cin>>n>>m;
        clearPrevData();
        while( m-- ){
            int a, b, c;
            cin>>a>>b>>c;
            cost [ a ] [ b ] += c;
        }
        makeGraph(n);
        cout<<maxFlow(1, n, n)<<"\n";
    }
};
int main(){
    fast
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    solution obj;
    obj.inputAndPerform();
    return 0;
}