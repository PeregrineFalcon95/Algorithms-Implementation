/*
Ref: 
Category: 
Sample Test Case:
3 4
1 2 3
2 3 1
1 3 7
2 1 5
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define inf 1000000001
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
int t, cases;

struct node {
    int _node;
    int cost;
    node(int _cost, int __node){
        _node = __node;
        cost = _cost;
    }
    bool operator < (const node& p) const { return cost > p.cost; }
};

class solution{
private:
    int dijkstra(int source, int target, int n, vector < vector < pair < int, int > > >& graph){
        priority_queue < node > pq;
        pq.push(node(0,source));
        vector < int > cost (n+1, inf);
        cost [ source ] = 0;
        
        while( !pq.empty() ){
            source = pq.top()._node;
            if ( source == target )return pq.top().cost;
            pq.pop();

            int sz = graph [ source ].size();
            for ( int i = 0; i < sz; i++ ){
                int child = graph [ source ] [ i ].first;
                int cc = graph [ source ] [ i ].second;
                if ( cost [ child ] > cost [ source ] + cc ){
                    cost [ child ] = cost [ source ] + cc;
                    pq.push( node(cost [ child ], child) );
                }
            }
        }
        return -1;
    }
public:
    void inputAndPerform(){
        int n, m;
        cin>>n>>m;
        vector < vector < pair < int, int > > > graph (n+1, vector < pair < int ,int > >() );
        while( m-- ){
            int a, b , c;
            cin>>a>>b>>c;
            graph [ a ].push_back( {b,c} );
        }
        cout<<dijkstra(1,n,n,graph)<<"\n";
    }   
};
int main(){
    fast
    solution obj;
    obj.inputAndPerform();
    return 0;
}