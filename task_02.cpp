#include "Matrix.hpp"

int main(){
    std::ifstream f1;
    std::ofstream f2;

    f1.open("in.txt");
    f2.open("out.txt");

    Matrix<double> A;

    deque<int> abc;
    deque<int> abc2;
    abc.clear();

    int j =0;

    f1 >> A;

    int dimxAtStart = A.dimx;

    double temp = 0;

    try{
        A.RowReducedEchelonForm();
        A.ZeroesToPlus();
        A.DeleteZeroRows();

        if (A.dimx == A.dimy && A.det() == 1) f2 << 0 << " " << A.dimx;
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

            f2 << dimxAtStart-A.dimx << " " << A.dimy << std::endl;

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
