#include "Matrix.hpp"

int main(){
    std::ifstream f1;
    std::ofstream f2;

    f1.open("in.txt");
    f2.open("out.txt");

    double k;
    Matrix<double> A;
    Matrix<double> B;
    Matrix<double> C;

    f1 >> k >> A >> B >> C;

    try{
        B.transpose();
        C.inverse();

        A = A + k*B*C;

        f2 << 1 << std::endl << A.det() << std::endl << A;
    }
    catch (const char* msg){
        f2 << -1 << std::endl << msg;
    }
    f1.close();
    f2.close();
}