#ifndef LAB6_MATRIX_HPP
#define LAB6_MATRIX_HPP


#include <iostream>
#include <vector>
#include "fstream"
#include "assert.h"
using std::vector;

template <typename T>
class Matrix;

template <typename T>
std::istream& operator>> (std::istream &in, Matrix<T> &matrix){
    in >> matrix.dimx >> matrix.dimy;

    matrix.SetMatrixSize(0, 0);

    for (int i = 0; i < matrix.dimx; i++)
        for (int j = 0; j < matrix.dimy; j++){
            in >> matrix.m[i][j];
        }
    return in;
}

template <typename T>
std::ostream& operator<< (std::ostream &out, const Matrix<T> &matrix){
    for (int i = 0; i < matrix.dimx; i++) {
        for (int j = 0; j < matrix.dimy; j++) {
            out << matrix.m[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}

template <typename T>
Matrix<T>& operator+ (Matrix<T> &lhs, const Matrix<T> &rhs){

    if (lhs.dimx != rhs.dimx || lhs.dimy != rhs.dimy) throw "Additition of two matrix with different sizes";

    assert(lhs.dimx == rhs.dimx);
    assert(lhs.dimy == rhs.dimy);

    for (int i = 0; i < lhs.dimx; i++)
        for (int j = 0; j <lhs.dimy; j++){
            lhs.m[i][j]+=rhs.m[i][j];
        }
    return lhs;
}

template <typename T>
Matrix<T>& operator* (Matrix<T> &lhs, const T &rhs){
    for (int i = 0; i < lhs.dimx; i++)
        for (int j = 0; j <lhs.dimy; j++){
            lhs.m[i][j]*=rhs;
        }
    return lhs;
}

template <typename T>
Matrix<T>& operator* (const T &rhs, Matrix<T> &lhs){
    for (int i = 0; i < lhs.dimx; i++)
        for (int j = 0; j <lhs.dimy; j++){
            lhs.m[i][j]*=rhs;
        }
    return lhs;
}

template <typename T>
const Matrix<T>& operator* (const Matrix<T> &lhs, const Matrix<T> &rhs){
    Matrix<T>* mnew = new Matrix<T>(lhs.dimx, rhs.dimy);

    if (lhs.dimx != rhs.dimy) throw "Multiplication of unsutable matrixes";
    assert(lhs.dimx == rhs.dimy);
    for (int i = 0; i < lhs.dimx; i++)
        for (int j = 0; j < rhs.dimy; j++){
            for (int k = 0; k < rhs.dimx; k++){
                mnew->m[j][i] += rhs.m[k][i]*lhs.m[j][k];
            }
        }
    return *mnew;
}


template <typename T>
class Matrix{
private:
    vector<vector<T>> m;
    vector<vector<T>> mTemp;
    T temp;

public:
    size_t dimx, dimy;

    Matrix<T>(size_t rows = 0, size_t cols = 0) {
        dimx = cols;
        dimy = rows;

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
        if (m.size() < x) m.resize(dimx);

        if (m[0].size() < y)
            for (int i = 0; i < y; i++){
                m[i].resize(dimy);
            }
        m[x][y] = a;
    }

    void MatrixResize(int x, int y){
        m.size(dimx);

        for (int i = 0; i < dimx; i++){
            m[i].resize(dimy);
        }
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
            for (int j = i; j < dimy; j++)
                if (m[j][i] != 0) {
                    std::swap(m[i], m[j]);
                    break;
                }

            temp = m[i][i];

            for (int j = 0; j < dimy; j++) {
                if (i < dimy && temp != 0) m[i][j] /= temp;
            }

            for (int j = 0; j < dimx; j++) {
                temp = m[j][i];
                for (int k = 0; k < dimy; k++) {
                    if (j > i) m[j][k] -= m[i][k] * temp;
                }
            }
        }
    }

    void RowReducedEchelonForm(){
        T temp = 0;
        for (int i = 0; i < dimx; i++) {
            for (int j = i; j < dimy; j++)
                if (m[j][i] != 0) {
                    std::swap(m[i], m[j]);
                    break;
                }

            temp = m[i][i];

            for (int j = 0; j < dimy; j++) {
                if (i < dimy && temp != 0) m[i][j] /= temp;
            }

            for (int j = 0; j < dimx; j++) {
                temp = m[j][i];
                for (int k = 0; k < dimy; k++) {
                    if (j != i) m[j][k] -= m[i][k] * temp;
                }
            }
        }
    }

    void DeleteZeroRows(){
        temp = 0;
        for (int i = 0; i < dimx; i++){
            for (int j = 0; j < dimy; j++){
                temp+=abs(m[i][j]);
            }
            if (temp == 0){
                m.erase(m.begin() + i);
                dimx--;
                i--;
            }
            temp = 0;
        }
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
        if (dimx != dimy) throw "Non Square matrix! Can not compute the determinant.";

        mTemp = m;

        T det = 1;

        T temp = 0;
        for (int i = 0; i < dimx; i++) {

            for (int j = i; j < dimy; j++)
                if (m[j][i] != 0) {
                    std::swap(m[i], m[j]);
                    det *= -1;
                    break;
                }

            temp = m[i][i];

            if (temp != 0) det *= temp;
            for (int j = 0; j < dimy; j++) {
                if (i < dimy && temp != 0){ m[i][j] /= temp;}
            }
            for (int j = 0; j < dimx; j++) {
                temp = m[j][i];
                for (int k = 0; k < dimy; k++) {
                    if (j > i) m[j][k] -= m[i][k] * temp;
                }
            }
        }

        for (int i = 0; i < dimx; i++) det*=m[i][i];

        m = mTemp;

        mTemp.clear();

        return -det;
    }

    void inverse(){
        vector<vector<T>> mnew;

        if (this->det() == 0) throw "Cannot Inverse Matrix wirh Determinant = 0";
        mnew.resize(m.size());
        for (int i = 0; i < dimy; i++){
            mnew[i].resize(m[i].size());
            mnew[i][i] = 1;
        }

        T temp = 0;
        for (int i = 0; i < dimx; i++) {
            for (int j = i; j < dimy; j++)
                if (m[j][i] != 0) {
                    std::swap(m[i], m[j]);
                    std::swap(mnew[i], mnew[j]);
                    break;
                }

            temp = m[i][i];

            for (int j = 0; j < dimy; j++) {
                if (i < dimy && temp != 0) {
                    m[i][j] /= temp;
                    mnew[i][j] /= temp;
                }
            }
            for (int j = 0; j < dimx; j++) {
                temp = m[j][i];
                for (int k = 0; k < dimy; k++) {

                    if (j != i){
                        m[j][k] -= m[i][k] * temp;
                        mnew[j][k] -= mnew[i][k] * temp;

                    }

                }

            }
        }

        m = mnew;
    }

    void SetMatrixSize(size_t i, size_t i1) {

        m.resize(dimx);

        for (int i = 0; i < dimx; i++) m[i].resize(dimy);
    }

    void ZeroesToPlus(){
        for (int i = 0; i < dimx; i++){
            for (int j = 0; j < dimy; j++){
                if (m[i][j] == 0) m[i][j] = abs(m[i][j]);
            }
        }
    }

    friend std::istream& operator >><T>(std::istream &in, Matrix &matrix);

    friend std::ostream& operator <<<T>(std::ostream &out, const Matrix &matrix);

    friend Matrix<T>& operator +<T>( Matrix &lhs, const Matrix &rhs);

    friend Matrix<T>& operator *<T>( Matrix &lhs, const T &rhs);

    friend Matrix<T>& operator *<T>( const T &rhs, Matrix &lhs);

    friend Matrix<T>& operator +<T>( Matrix &lhs, const Matrix &rhs);

    friend const Matrix<T>& operator *<T>(const Matrix &lhs, const Matrix &rhs);
};


#endif //LAB6_MATRIX_HPP
