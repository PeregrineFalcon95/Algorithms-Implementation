/*
Ref: http://www.shafaetsplanet.com/?p=692
Category: 
Sample Test Case:
n = num of nodes, m = num of edge.
8 11
1 5 2 // edge 1 - 5. 2 is cost 
1 2 4
1 4 10
2 4 8
2 3 18
5 4 5
3 4 11
4 7 11
4 8 9
7 6 1
6 8 2
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define inf 1000000001
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
int t, cases;
class segmentTree{
private:
    void MST(int n, vector < vector < pair < int, int > > >& graph, vector < pair < int , int > >& mst){
        priority_queue < pair < int, int > > pq;
        bool vis [ n + 1 ];
        memset(vis, false, sizeof vis);
        pq.push( {0,1} );
        mst [ 1 ].first = 0;
        mst [ 1 ].second = 1;
        
        while( !pq.empty() ){
            int node = pq.top().second;
            pq.pop();
            if ( vis [ node ] )continue;
            vis [ node ] = true;
            int sz = graph [ node ].size();
            for ( int i = 0; i < sz; i++ ){
                int child = graph [ node ] [ i ].first;
                int cc = graph [ node ] [ i ].second;
                if ( !vis [ child ] && mst [ child ].first > cc ){
                    pq.push({-cc, child});
                    mst [ child ].first = cc;
                    mst [ child ].second = node;
                }
            }
        }
    }
public:
    void inputAndPerform(){
        int n,m;
        cin>>n>>m;
        vector < vector < pair < int, int > > > graph( n+1, vector < pair < int, int > > ());
        vector < pair < int , int > > mst (n+1, make_pair(inf, 0));
        while( m-- ){
            int a, b, c;
            cin>>a>>b>>c;
            graph [ a ].push_back( {b,c} );
            graph [ b ].push_back( {a,c} );
        } 
        MST(n, graph, mst);
        cout<<"Minimum Spanning Tree:\n";
        for ( int i = 2; i <= n; i++ ){
            cout<<i<<" "<<mst [ i ].second<<" cost: "<<mst [ i ].first<<"\n";
        }
    }
};
int main(){
    fast
    segmentTree obj;
    obj.inputAndPerform();
    return 0;
}