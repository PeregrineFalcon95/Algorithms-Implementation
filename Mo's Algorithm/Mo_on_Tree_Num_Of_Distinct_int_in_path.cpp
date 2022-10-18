/*
Problem: https://www.spoj.com/problems/COT2/en/
Distinct number in a path.

8 7
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5
7 8
1 1
2 7
7 7
3 7
4 3
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define inf 1000000001
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
int t, cases;

static int k = 200;

struct queryData{
    int le, ri, idx;
    int lca = 0;
};

bool cmp (queryData &a, queryData &b ){
    int k_a = a.le / k , k_b = b.le / k;
    if ( k_a == k_b )return a.ri < b.ri;
    return k_a < k_b;
}

class solution{
private:
    void dfs(int node, int& time_, vector < vector < int > >& graph,  vector < int >& level, vector < vector < int > >& sparse, vector < int >& nodeStart, vector < int >& nodeEnd, vector < int >& moAr, vector < ll >& nodeVal){
        nodeStart [ node ] = ++time_;
        moAr [ time_ ] = node;
        int sz = graph [ node ].size();
        for ( int i = 0; i < sz; i++ ){
            int child = graph [ node ] [ i ];
            if ( sparse [ child ] [ 0 ] == -1 ){
                level [ child ] = level [ node ] + 1;
                sparse [ child ] [ 0 ] = node;
                dfs( child, time_, graph, level, sparse, nodeStart, nodeEnd, moAr, nodeVal );
            }
        }
        nodeEnd [ node ] = ++time_;
        moAr [ time_ ] = node;
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
    void add(int idx, int& disNumCount, vector < int  >& moAr, vector < int >& counter, vector < int >& nodeCount, vector < ll >& nodeVal){
        nodeCount [ moAr [ idx ] ]++;
        if ( nodeCount [ moAr [ idx ] ] == 1 ){
            counter [ nodeVal [ moAr [ idx ] ] ]++;
            if ( counter [ nodeVal [ moAr [ idx ] ] ] == 1 )disNumCount++;
        }
        else if (nodeCount [ moAr [ idx ] ] == 2){
            counter [ nodeVal [ moAr [ idx ] ] ]--;
            if ( counter [ nodeVal [ moAr [ idx ] ] ] == 0 )disNumCount--;
        }
    }
    void remove(int idx, int& disNumCount, vector < int >& moAr, vector < int >& counter, vector < int >& nodeCount, vector < ll >& nodeVal){
        if ( !idx )return;
        nodeCount [ moAr [ idx ] ]--;
        if ( nodeCount [ moAr [ idx ] ] == 1 ){
            counter [ nodeVal [ moAr [ idx ] ] ]++;
            if ( counter [ nodeVal [ moAr [ idx ] ] ] == 1 )disNumCount++;
        }
        else if (nodeCount [ moAr [ idx ] ] == 0){
            counter [ nodeVal [ moAr [ idx ] ] ]--;
            if ( counter [ nodeVal [ moAr [ idx ] ] ] == 0 )disNumCount--;
        }
    }
    void compressValues(int n, vector < ll >& nodeVal){
        map < ll, int > mp;
        deque < ll > dq;
        for ( int i = 1; i <= n; i++ )dq.push_back( nodeVal [ i ] );
        sort( dq.begin(), dq.end() );
        int marker = 1;
        while( !dq.empty() ){
            if ( mp.find( dq.front() ) == mp.end() )
                mp [ dq.front() ] = marker++;
            dq.pop_front();
        }
        for ( int i = 1; i <= n; i++ )nodeVal [ i ] = mp [ nodeVal [ i ] ];
    }
public:
    void inputAndPerform(){
        int n, q, time_ = 0;
        cin>>n>>q; //Tree size and query num
        k = sqrt( 2.0 * n * n / q) + 2;
        vector < int > level (n+1), nodeStart (n+1), nodeEnd (n+1), moAr(n+n+2);
        vector < ll > nodeVal (n+1);
        vector < vector < int > > graph (n+1, vector < int > ());
        vector < vector < int > > sparse ( n+1, vector < int > (32, -1) );
        vector < queryData > qu (q+1);

        //Value of nodes
        for ( int i = 1; i <= n; i++ )cin>>nodeVal [ i ];
        compressValues(n,nodeVal);

        for ( int i = 1; i < n; i++ ){
            int a,b;
            cin>>a>>b;
            graph [ a ].push_back( b );
            graph [ b ].push_back( a );
        }

        sparse [ 1 ] [ 0 ] = 1;
        level [ 1 ] = 0;
        dfs(1, time_, graph, level, sparse, nodeStart, nodeEnd, moAr, nodeVal);
        makeSparse(n,sparse);

        for ( int i = 1; i <= q; i++ ){
            int a, b, c;
            cin>>a>>b; //Queries
            if ( nodeStart [ a ] > nodeStart [ b ] )swap(a,b);
            int lca = query( a , b, n, sparse, level );
            qu [ i ].idx = i;
            if ( lca != a ){
                qu [ i ].lca = lca;
                qu [ i ].le = nodeEnd [ a ];
                qu [ i ].ri = nodeStart [ b ];
            }
            else {
                qu [ i ].le = nodeStart [ a ];
                qu [ i ].ri = nodeStart [ b ];
            }
        }

        sort( qu.begin()+1, qu.begin()+q+1, cmp );
        int currentL = 1, currentR = 0, disNumCount = 0;
        vector < int > counter (n+1, 0), nodeCount (n+1, 0);
        int ans [ q+1];

        //Mo
        for ( int i = 1; i <= q; i++ ){
            while( currentL < qu [ i ].le )remove(currentL++, disNumCount,moAr,counter, nodeCount, nodeVal);
            while( currentL > qu [ i ].le )add(--currentL, disNumCount, moAr,counter, nodeCount, nodeVal);
            while( currentR < qu [ i ].ri )add(++currentR, disNumCount, moAr,counter, nodeCount, nodeVal);
            while( currentR > qu [ i ].ri )remove(currentR--, disNumCount, moAr,counter, nodeCount, nodeVal);

            ans [ qu [ i ].idx ] = disNumCount;
            if ( qu [ i ].lca ){
                if ( counter [ nodeVal [ qu [ i ].lca ] ] == 0 )ans [ qu [ i ].idx ]++;
            }
        }
        for ( int i = 1; i <= q; i++ )cout<<ans [ i ]<<"\n";
        cout<<"\n";
    }
};
int main(){
    fast
    solution obj;
    obj.inputAndPerform();
    return 0;
}