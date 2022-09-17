/*
Ref: 
Category: 
Sample Test Case:
5 4
1 2
2 3
3 4
4 2
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define inf 1000000001
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
int t, cases;


class solution{
private:
    void dfs(int source, int& startNode, int& endNode, vector < vector < int > >& graph, vector < int >& color, vector < int >& parent){
        color [ source ] = 1;
        int sz = graph [ source ].size();
        for ( int i = 0; i < sz; i++ ){
            int child = graph [ source ] [ i ];
            if ( startNode != -1 )return;
            if ( !color [ child ] ){
                parent [ child ] = source;
                dfs( child, startNode, endNode, graph, color, parent );
            }
            else if ( color [ child ] == 1 && parent [ source ] != child ){
                //Back edge found
                startNode = child;
                endNode = source;
            }
        }
        color [ source ] = 2;
    }
public:
    void inputAndPerform(){
        int n, m;
        cin>>n>>m;
        vector < vector < int > > graph (n+1, vector< int > ());
        vector < int > color (n+1, 0 ), parent (n+1, 0);
        int haveCycle, startNode = -1, endNode = -1;
        while(m--){
            int a, b;
            cin>>a>>b;
            graph [ a ].push_back( b );
            graph [ b ].push_back( a );
        }
        for ( int i = 1; i <= n; i++ ){
            if ( !color [ i ] && startNode == -1 ){
                parent [ i ] = i;
                dfs(i, startNode, endNode, graph, color, parent);
            }
        }
        
        if ( startNode == -1 ){
            cout<<"IMPOSSIBLE\n";
            return;
        }
        vector < int > path;
        path.push_back( startNode );
        while( parent [ endNode ] != startNode){
            path.push_back( endNode );
            endNode = parent [ endNode ];
        }
        path.push_back( endNode );
        path.push_back( startNode );

        cout<<path.size()<<"\n";
        while( !path.empty() ){
            cout<<path.back()<<" ";
            path.pop_back();
        }
    }   
};
int main(){
    fast
    solution obj;
    obj.inputAndPerform();
    return 0;
}