/*
Ref: https://cp-algorithms.com/data_structures/disjoint_set_union.html
Category: 
Sample Test Case:
5 8
2 1 2
1 1 3
1 2 1
2 3 4
1 1 3
2 1 4
1 1 4
1 1 5
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define inf 1000000001
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
int t, cases;


class solution{
private:
    int findSet( int node, vector < int >& parent ){
        if ( node == parent [ node ] )return node;
        return parent [ node ] = findSet( parent [ node ], parent );
    }
    void unionSet(int nodeOne, int nodeTwo, vector < int >& parent, vector < int >& sizeOfSet ){
        nodeOne = findSet(nodeOne, parent);
        nodeTwo = findSet(nodeTwo, parent);
        if ( nodeOne != nodeTwo ){
            if ( sizeOfSet [ nodeOne ] < sizeOfSet [ nodeTwo] )swap(nodeOne, nodeTwo);
            parent [ nodeTwo ] = nodeOne;
            sizeOfSet [ nodeOne ] += sizeOfSet [ nodeTwo ];
        }
    }
public:
    void inputAndPerform(){
        int n, m; //Num of nodes and operations
        cin>>n>>m;
        vector < int > parent (n+1), sizeOfSet (n+1, 0);
        //Make set
        for ( int i = 1; i <= n; i++ )parent [ i ] = i;
        while( m-- ){
            int type, a, b;
            cin>>type>>a>>b;
            if ( type == 1 ){ // Find if same set
                a = findSet(a,parent);
                b = findSet(b,parent);
                if ( a == b )cout<<"Same set\n";
                else cout<<"Not same set\n";
            }
            else if ( type == 2 ){ //Join two set contains a and b
                unionSet(a,b, parent, sizeOfSet);
            }
        }
    }
};
int main(){
    fast
    solution obj;
    obj.inputAndPerform();
    return 0;
}