#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef vector< vector< vector<int> > > V3;
typedef vector< vector<int> >  V2;
typedef vector<int>  V1;


void sample_function(V3& coeff, int zlow, V2& zindex)
{
    int t = 0; 
    cout << "t=";
    for (size_t r = 0; r < zindex.size(); ++r)
    {
        for (size_t c = 0; c < zindex[0].size(); ++c)
        {
            cout << "coeff(" << r << ", " << c << ", " << zindex[r][c] << ")";
            if (r < zindex.size()-1 || c < zindex[0].size()-1 )
                cout << "+";
            t += coeff[r][c][zindex[r][c]-zlow];
        }
    }
    cout << endl;
}

// advance to the "next" the collection of z values
// advance returns false when we advance the "last" 
// collection of z values.
bool advance(V2& zindex, int zlow, int zhigh)
{
    int row = 0;
    int col = 0;
    bool advanced = false;
    while (!advanced)
    {
        advanced = true;
        ++zindex[row][col];
        if ( zindex[row][col] > zhigh )
        {
            advanced = false;
            zindex[row][col] = zlow;
            ++col;
            if (col == zindex[0].size())
            {
                col = 0;
                ++row;
                if (row == zindex.size())
                {
                    return false;  // overflow
                }
            }
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    int P,U,L;
    
    std::istringstream i;       
    i.str(string(argv[1]));
    i >> P;

    i.clear();
    i.str(string(argv[2]));
    i >> L;

    i.clear();
    i.str(string(argv[3]));
    i >> U;

    cout << "P = " << P << endl;
    cout << "L = " << L << endl;
    cout << "U = " << U << endl;

    // Initialize a coeff array with size: PxPx(U-L+1)
    V3 coeff(P, V2(P, V1(U-L+1)));

    // Initialize 2d vector, zindex to hold a collection of z values
    // To begin with all values of zindex are equal to L
    V2 zindex(P, V1(P, L) );

    do
    {
        sample_function(coeff, L, zindex);      
    } while (advance(zindex, L, U));  

    return 0;
}
