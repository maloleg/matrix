#include "Matrix.hpp"

int main(){
    double k;
    Matrix<double> A;
    Matrix<double> B;
    Matrix<double> C;

    std::cin >> k >> A >> B >> C;

    try{
        B.transpose();
        C.inverse();

        A = A + k*B*C;

        std::cout << 1 << std::endl << A.det() << std::endl << A;
    }
    catch (const char* msg){
        std::cout << -1 << std::endl << msg;
    }
    }