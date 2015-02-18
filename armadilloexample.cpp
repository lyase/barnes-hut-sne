#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;
void setZeroMean(mat& A)

{
    int n_rows;
    int D;
    n_rows=A.n_rows;
    cout<<"number row:"<<n_rows<<endl;
    D=A.n_cols;
    cout<<"number col:"<<D<<endl;
    mat Mean=mean(A); // should be 1 row D coln;
    cout<<"Mean ="<<Mean<<endl;
// subtract the mean - use score_out as temporary matrix
    A =A-repmat(mean(A), n_rows, 1);
    return ;
}
int main(int argc, char** argv)
{
    mat A = randu<mat>(4,5); //random matrix 4 rows 5 cols
    setZeroMean(A);
    mat Mean=mean(A);
    cout<<" centered data new Mean ="<<Mean<<endl;

    mat B = randu<mat>(4,5);

//    cout << A*B.t() << endl;

    return 0;
}
