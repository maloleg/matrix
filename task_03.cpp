#include "Matrix.hpp"

int main(){
    Matrix<double> A;
    double x = 0;
    double temp, check = 0;

    std::cin >> A;

    int dimxAtStart = A.dimx;

    A.dimy += 1;

    A.SetMatrixSize(A.dimx, A.dimy);

    for (int i = 0; i < A.dimx; i++){
        std::cin >> x;
        A.PutElement(i, A.dimy-1, x);
        //std::cout << B.GetElement(0, i);
    }

    try {
        A.DeleteZeroRows();

        for (int i = 0; i < A.dimx; i++){
            temp = 0;
            for (int j = 0; j < A.dimy; j++){
                temp += A.GetElement(i, j);
            }
            if (temp == A.GetElement(i, A.dimy-1)) check = 1;
        }

        if (check == 1) {
            std::cout << -1;
        }
        else {
            A.RowReducedEchelonForm();
            std::cout << A.dimy - 1 << " " << dimxAtStart - A.dimx << std::endl;

            for (int i = 0; i < A.dimx; i++){
                for (int j = i; j < A.dimy-1; j++){
                    temp = 0;

                    if (A.GetElement(i, j) != 0){
                        for (int k =j+1; k < A.dimy-1; k++) {temp += A.GetElement(i, k);}
                        std::cout << A.GetElement(i, A.dimy-1)-temp << " ";
                        break;
                    }
                    else std::cout << 1 << " ";
                }
            }

            for (int i = 0; i <dimxAtStart - A.dimx; i++) std::cout << "1 ";
            std::cout << std::endl;

            for (int i = dimxAtStart - A.dimx; i > 0; i--){
                temp = 0;
                for (int j = 0; j < A.dimy-1; j++){
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
}