/*
8 9
1 2 6 4 2 3 6 2
1 1 8
2 1 2
1 1 8
2 8 1
1 1 8
1 2 7
1 2 6
2 4 0
1 1 8
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define inf 1000000001
#define fast ios_base::sync_with_stdio(NULL);cin.tie(NULL);cout.tie( NULL);
int t, cases;

class solution{
private:
    void preprocess(int n, int segSize, vector < int >& ar, vector < int >& segment){
        int currentSeg = 0;
        for ( int i = 1; i <= n; i++ ){
            if ( i%segSize == 0 )currentSeg++;
            segment [ currentSeg ] += ar [ i ];
        }
    }
    int query(int l, int r, int segSize, vector < int >& segment, vector < int >& ar){
        int sum = 0;
        //Left most incomplete segment
        while( l < r && l % segSize != 0 )sum += ar [ l++ ];
        
        //Square root segment before the segment contains right
        while ( l+segSize <= r ){
            sum += segment [ l / segSize ];
            l += segSize;
        }

        //Right most incomplete segment
        while( l <= r )sum += ar [ l++ ];
        return sum;
    }
    void update(int pos, int val, int segSize, vector < int >& ar, vector < int >& segment){
        int segNum = pos / segSize;
        
        segment [ segNum ] -= ar [ pos ];
        segment [ segNum ] += val;
        ar [ pos ] = val;
    }
public:
    void inputAndPerform(){
        int n, q;
        cin>>n>>q;
        int segSize = sqrt(n+1);
        vector < int > ar (n+1), segment (sqrt(n)+5);
        for ( int i = 1; i <= n; i++ )cin>>ar [ i ];
        preprocess(n, segSize, ar, segment);

        //Queries
        while( q-- ){
            int type;
            cin>>type;
            if ( type == 1 ){ //Query
                int l ,r;
                cin>>l>>r;
                cout<<query(l, r, segSize, segment, ar)<<"\n";
            }
            else { //Update
                int pos, val;
                cin>>pos>>val;
                update(pos, val, segSize, ar, segment);
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