#include "Matrix.hpp"

int main(){
    std::ifstream f1;
    std::ofstream f2;

    f1.open("in.txt");
    f2.open("out.txt");

    Matrix<double> A;
    double x = 0;
    double temp, check = 0;

    int j = 0;

    deque<int> abc;
    deque<int> abc2;

    abc.clear();
    abc2.clear();

    f1 >> A;

    int dimxAtStart = A.dimx;

    A.dimy += 1;

    A.SetMatrixSize(A.dimx, A.dimy);

    for (int i = 0; i < A.dimx; i++){
        f1 >> x;
        f1 >> x;
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
            f2 << -1;
        }
        else {
            A.RowReducedEchelonForm();
            f2 << A.dimy - 1 << " " << dimxAtStart - A.dimx << std::endl;

            for (int i = 0; i < A.dimx; i++){
                for (int j = i; j < A.dimy-1; j++){
                    temp = 0;

                    if (A.GetElement(i, j) != 0){
                        for (int k =j+1; k < A.dimy-1; k++) {temp += A.GetElement(i, k);}
                        f2 << A.GetElement(i, A.dimy-1)-temp << " ";
                        break;
                    }
                    else f2 << 1 << " ";
                }
            }

            for (int i = 0; i < A.dimx; i++) {
                A.PutElement(i, A.dimy-1, 0);
            }

            A.transpose();
            A.DeleteZeroRows();
            A.transpose();

            for (int i = 0; i <dimxAtStart - A.dimx; i++) f2 << "1 ";
            f2 << std::endl;

            for (int i = 0; i < A.dimx; i++) {
                j = 0;
                while (A.GetElement(j, i) != 1 && j < A.dimy) {
                    j++;
                }
                abc.push_back(j);
            }

            abc2 = abc;

            for (int i = A.dimx-1; i < A.dimy; i++){
                temp = 0;
                for (int k = 0; k < A.dimx; k++){
                    if (abc[k] == i) temp = 1;
                }
                if (temp == 0) abc.push_back(i);
            }

            for (int i = 0; i < A.dimx; i++) abc.pop_front();

            for (int i = 0; i < dimxAtStart-A.dimx; i++){
                for (int k = 0; k < A.dimy; k++){
                    temp = 0;

                    for (int l = 0; l < abc2.size(); l++){
                        if (abc2[l] == k) temp = 1;
                    }

                    if (temp == 0) temp = 2;


                    if (temp == 1){
                        f2 << -A.GetElement(k, abc[i]) + 0 << " ";
                    }
                    else{
                        if (abc[i] == k) f2 << "1 ";
                        else f2 << "0 ";
                    }

                }
                f2 << std::endl;
            }
        }

        }
    catch (const char* msg){
        f2 << -1 << std::endl << msg;
    }

    f1.close();
    f2.close();
}