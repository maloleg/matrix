#include <iostream>
#include <vector>
#include "fstream"
#include "assert.h"
using std::vector;


template <class T>
class Matrix{
public:
    vector<vector<T>> m;
    size_t dimx, dimy;
    T temp;

    Matrix<T>(size_t rows = 0, size_t cols = 0) {
        dimx = rows;
        dimy = cols;

        m.resize(dimx);

        for (int i = 0; i < dimx; i++) m[i].resize(dimy);
    }

    void PrintMatrix(){
        T x = 0;
        for (int i = 0; i < dimx; i++){
            for (int j = 0; j < dimy; j++){
                std::cout << m[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void MatrixInit (int x, int y){
        m.resize(x);
        for (int i = 0; i < x; i++){
            m[i].resize(y);
        }
    }

    T GetElement(int x, int y){
        if (m.size() > x && m[0].size() > y) return m[x][y];
        else abort();
    }

    void PutElement (int x, int y, T a){
        if (m.size() < x) m.resize(x);

        if (m[0].size() < y)
            for (int i = 0; i < y; i++){
                m[i].resize(y);
            }

        m[x][y] = a;
    }

    void MultiplyByNumber(T x){
        for (int i = 0; i < m.size(); i++)
            for (int j = 0; j < m[0].size(); j++){
                m[i][j]*=x;
            }
    }

    void MatrixSum(Matrix<T> b){
        if (b.m.size() == m.size() && b.m[0].size() == b.m[0].size()){
            for (int i = 0; i < dimx; i++)
                for (int j = 0; j < dimy; j++)
                    m[i][j] += b.m[i][j];
        }
        else abort();
    }

    void MatrixMult(Matrix<T> b){
        if (dimx!=b.dimy && dimy!=b.dimx) abort();
        else{
            for (int i = 0; i < dimx; i++)
                for (int j = 0; j < dimy; j++){
                    temp = 0;

                    for (int k = 0; k < std::max(dimx, dimy); k++){
                        temp += m[i][k]*b.m[k][j];
                    }
                 m[i][j] = temp;
                }
        }
    }

    void transpose(){
        m.resize(std::max(dimx, dimy));
        for (int i = 0; i < std::max(dimx, dimy); i++) m[i].resize(std::max(dimx, dimy), 0);

        if (dimx > dimy) {
            for (int i = 0; i < dimx; i++) {
                for (int j = 0; j < dimy; j++) {
                    if (i > j) std::swap(m[j][i], m[i][j]);
                }
            }
        }
        else{
            for (int i = 0; i < dimy; i++) {
                for (int j = 0; j < dimx; j++) {
                    if (i > j) std::swap(m[j][i], m[i][j]);
                }
            }
        }
     std::swap(dimx, dimy);
    }

    void RowEchelonForm(){
            T temp = 0;
            for (int i = 0; i < dimx; i++) {
                temp = m[i][i];
                for (int j = 0; j < dimy; j++) {
                    if (i < dimy && temp != 0) m[i][j] /= temp;
                }

                this->PrintMatrix();

                for (int j = 0; j < dimx; j++) {
                    temp = m[j][i];
                    for (int k = 0; k < dimy; k++) {


                       // std::cout << "-- " << j << " " << k <<  " m=" << m[j][k] << " temp=" << temp << std::endl;

                        if (j > i) m[j][k] -= m[i][k] * temp;

                    }

                }
                this->PrintMatrix(); std::cout << std::endl;

            }
    //    }
    //else std::cout << "Not square matrix" << dimx << "x" << dimy << std::endl;
    }

    void RowReducedEchelonForm(){
        T temp = 0;
        for (int i = 0; i < dimx; i++) {
            temp = m[i][i];
            for (int j = 0; j < dimy; j++) {
                if (i < dimy && temp != 0) m[i][j] /= temp;
            }

            this->PrintMatrix();

            for (int j = 0; j < dimx; j++) {
                temp = m[j][i];
                for (int k = 0; k < dimy; k++) {


                    // std::cout << "-- " << j << " " << k <<  " m=" << m[j][k] << " temp=" << temp << std::endl;

                    if (j != i) m[j][k] -= m[i][k] * temp;

                }

            }
            this->PrintMatrix(); std::cout << std::endl;

        }
        //    }
        //else std::cout << "Not square matrix" << dimx << "x" << dimy << std::endl;
    }

    void GetMatrixFromFile(std::ifstream& f){
        int x, y;
        T a;

        m.clear();

        f >> x >> y;

        for (int i = 0; i < x; i++){
            for (int j = 0; j < y; j++){
                f >> a;
                this->PutElement(i, j, a);
            }
        }

    }

    void PrintMatrixInFile(std::ofstream& f){
        f << dimx << " " << dimy;

        for (int i = 0; i < dimx; i++) {
            f << std::endl;
            for (int j = 0; j < dimy; j++) {
                f << m[i][j] << " ";
            }
        }
    }

    T det (){
        assert(dimx == dimy);

        T det = 1;

        T temp = 0;
        for (int i = 0; i < dimx; i++) {
            temp = m[i][i];

            if (temp != 0) det *= temp;
            for (int j = 0; j < dimy; j++) {
                if (i < dimy && temp != 0){ m[i][j] /= temp;}
            }

            this->PrintMatrix();

            for (int j = 0; j < dimx; j++) {
                temp = m[j][i];
                for (int k = 0; k < dimy; k++) {


                    // std::cout << "-- " << j << " " << k <<  " m=" << m[j][k] << " temp=" << temp << std::endl;

                    if (j > i) m[j][k] -= m[i][k] * temp;

                }

            }
            this->PrintMatrix(); std::cout << std::endl;

        }

     return det;

    }

    void SetMatrixSize(){
        std::cin >> dimx;
        std::cin >> dimy;

        m.resize(dimx);

        for (int i = 0; i < dimx; i++) m[i].resize(dimy);

        std::cout << "dimx = " << dimx << "  dimy = " << dimy << std::endl;
    }
};

int main() {
    Matrix<double> mat1(3, 3);

    double x = 0;

    std::cout << mat1.dimx << " " << mat1.dimy << std::endl;

   // mat1.SetMatrixSize();

    for (int i = 0; i < mat1.dimx; i++)
        for (int j = 0; j < mat1.dimy; j++){
     //       std::cout << mat1.dimx << " " << mat1.dimy << std::endl;

            std::cin >> x;
            mat1.PutElement(i, j, x);
        }

    //mat1.StairCase();

    mat1.PrintMatrix();

  //  mat1.Transpose();

  //  mat1.PrintMatrix();

    //mat1.RowReducedEchelonForm();

    mat1.PrintMatrix();

    std::cout << "Determinant = " << mat1.det();



    return 0;
}
