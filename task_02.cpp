#include "Matrix.hpp"

int main(){
    Matrix<double> A;

    deque<int> abc;
    deque<int> abc2;
    abc.clear();

    int j =0;

    std::cin >> A;

    int dimxAtStart = A.dimx;

    double temp = 0;

    try{
        A.RowReducedEchelonForm();
        A.ZeroesToPlus();
        A.DeleteZeroRows();

        if (A.dimx == A.dimy && A.det() == 1) std::cout << 0 << " " << A.dimx;
        else{
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

            std::cout << dimxAtStart-A.dimx << " " << A.dimy << std::endl;

            for (int i = 0; i < dimxAtStart-A.dimx; i++){
                for (int k = 0; k < A.dimy; k++){
                    temp = 0;

                    for (int l = 0; l < abc2.size(); l++){
                        if (abc2[l] == k) temp = 1;
                    }

                    if (temp == 0) temp = 2;


                    if (temp == 1){

                        std::cout << -A.GetElement(k, abc[i]) + 0 << " ";
                    }
                    else{
                        if (abc[i] == k) std::cout << "1 ";
                        else std::cout << "0 ";
                    }

                }
                std::cout << std::endl;
            }
        }
    }

    catch (const char* msg){
        std::cout << -1 << std::endl << msg;
    }
}
