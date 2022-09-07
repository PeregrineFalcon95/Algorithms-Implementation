/*
Ref: 
Category: 
Sample Test Case:
16 10
1 2
1 8
2 3
3 4
4 5
5 6
6 7
6 14
8 9
9 10
10 11
11 15
11 12
12 13
12 16
12 13
7 13
7 9
14 15
1 14
2 16
11 11
6 11
15 7
13 16
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define inf 1000000001
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
int t, cases;
class segmentTree{
private:
    void bfs(int n, vector < vector < int > >& graph, vector < vector < int > >& sparse, vector < int >& level){
        queue < int > qu;
        qu.push(1);
        sparse [ 1 ] [ 0 ] = 1;
        level [ 1 ] = 0;
        while( !qu.empty() ){
            int node = qu.front();
            qu.pop();
            int sz = graph [ node ].size();
            for ( int i = 0; i < sz; i++ ){
                int child = graph [ node ] [ i ];
                if ( sparse [ child ] [ 0 ] == -1 ){
                    qu.push(child);
                    level [ child ] = level [ node ] + 1;
                    sparse [ child ] [ 0 ] = node;
                }
            }
        }
    }
    void makeSparse(int n, vector < vector < int > >& sparse ){
        for ( int i = 1; (1<<i) < n; i++ )
            for ( int j = 1; j <= n; j++ )
                if ( sparse [ j ] [ i -1 ] != -1 )
                sparse [ j ] [ i ] = sparse [ sparse [ j ] [ i - 1 ] ] [ i - 1 ];
    }
    
    int query( int p , int q, int n, vector < vector < int > >& sparse, vector < int >& level ){
        int log = 1;
        if ( level [ p ] < level [ q ] )swap( p , q );
        while ( ( 1 << ( log + 1 ) ) < n  )log++;
        for ( int i = log; i >= 0; i-- ){
            if ( sparse [ p ] [ i ] != -1 && level [ p ] - ( 1 << i )>= level [ q ] ){
                p = sparse [ p ] [ i ];
            }
        }
        if ( p == q )return p;
        for ( int i = log; i >= 0; i-- ){
            if ( sparse [ p ] [ i ] != -1 && sparse [ p ] [ i ] != sparse [ q ] [ i ] ){
                p = sparse [ p ] [ i ];
                q = sparse [ q ] [ i ];
            }
        }
        return sparse [ p ] [ 0 ];
    }


public:
    void inputAndPerform(){
        int n, q;
        cin>>n>>q; //n = num of nodes, q = num of quries
        vector < vector < int > > graph (n+1, vector < int >());
        vector < int > parent ( n+1, -1 ), level (n+1);
        vector < vector < int > > sparse ( n+1, vector < int > (32, -1) );
        for ( int i = 1; i < n; i++ ){
            int a, b;
            cin>>a>>b; //Edges of tree
            graph [ a ].push_back( b );
            graph [ b ].push_back( a );
        }
        //Find parents and level using BFS
        bfs(n, graph, sparse, level);
        //Make sparse table
        makeSparse(n, sparse);
        while( q-- ){
            int a, b;
            //Query for LCA using sparse table
            cin>>a>>b;
            cout<<"LCA of "<<a<<" "<<b<<" = "<<query(a,b,n,sparse,level)<<"\n";
        }
    }   
};
int main(){
    fast
    segmentTree obj;
    obj.inputAndPerform();
    return 0;
}