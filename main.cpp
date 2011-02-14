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

    V3 coeff(P, V2(P, V1(U-L+1)));

    V2 zindex(P, V1(P, L) );

    bool overflow = false;
    while (!overflow)
    {
        sample_function(coeff, L, zindex);      

        int row = 0;
        int col = 0;
        bool advanced = false;
        while (!advanced  && !overflow)
        {
            advanced = true;
            ++zindex[row][col];
            if ( zindex[row][col] > U )
            {
                advanced = false;
                zindex[row][col] = L;
                ++col;
                if (col == P)
                {
                    col = 0;
                    ++row;
                    if (row == P)
                    {
                        overflow = true;
                    }
                }
            }
        }
    }

    return 0;
}
