#include "Matrix.hpp"

int main(){
    Matrix<double> A;

    std::cin >> A;

    int dimxAtStart = A.dimx;

    double temp = 0;

    try{
        A.RowReducedEchelonForm();
        A.ZeroesToPlus();
        A.DeleteZeroRows();

        if (A.dimx == A.dimy && A.det() == 1) std::cout << 0 << " " << A.dimx;
        else{
            std::cout << dimxAtStart-A.dimx << " " << A.dimy << std::endl;
            for (int i = 0; i <dimxAtStart - A.dimx; i++){
                temp = 0;
                for (int j = 0; j < A.dimy; j++){
                    if (temp == 0 || A.GetElement(i, j) == 0) std::cout << A.GetElement(i, j) << " ";
                    else std::cout << -1*A.GetElement(i, j) << " ";

                    if (A.GetElement(i, j) == 1) temp = 1;
                }
                std::cout << std::endl;
            }
        }
    }

    catch (const char* msg){
        std::cout << -1 << std::endl << msg;
    }
}
