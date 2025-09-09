#include <iostream>
using namespace std;

class DynamicMatrix {
private:
    int** mat;
    int rows, cols;
public:
    DynamicMatrix(int r, int c, int initVal = 0) {
        rows = r; cols = c; allocateMemory(initVal);
    }
    void allocateMemory(int initVal) {
        mat = new int*[rows];
        for (int i = 0; i < rows; i++) {
            mat[i] = new int[cols];
            for (int j = 0; j < cols; j++) mat[i][j] = initVal;
        }
    }
    void resize(int newR, int newC, int initVal = 0) {
        int** newMat = new int*[newR];
        for (int i = 0; i < newR; i++) {
            newMat[i] = new int[newC];
            for (int j = 0; j < newC; j++) {
                if (i < rows && j < cols) newMat[i][j] = mat[i][j];
                else newMat[i][j] = initVal;
            }
        }
        for (int i = 0; i < rows; i++) delete[] mat[i];
        delete[] mat;
        mat = newMat; rows = newR; cols = newC;
    }
    void transpose() {
        int** trans = new int*[cols];
        for (int i = 0; i < cols; i++) {
            trans[i] = new int[rows];
            for (int j = 0; j < rows; j++) trans[i][j] = mat[j][i];
        }
        for (int i = 0; i < rows; i++) delete[] mat[i];
        delete[] mat;
        mat = trans; int temp = rows; rows = cols; cols = temp;
    }
    void addTwoToOddIndex() {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                if ((i + j) % 2 == 1) mat[i][j] += 2;
    }
    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) cout << mat[i][j] << " ";
            cout << endl;
        }
    }
    ~DynamicMatrix() {
        for (int i = 0; i < rows; i++) delete[] mat[i];
        delete[] mat;
    }
};

int main() {
    DynamicMatrix dm(2, 3, 1);
    dm.print();
    dm.resize(3, 4, 5);
    dm.print();
    dm.transpose();
    dm.print();
    dm.addTwoToOddIndex();
    dm.print();
    return 0;
}
