#include <iostream>
using namespace std;

int recursiveArraySum(int* arr[], int sizes[], int dim) {
    if (dim == 1) {
        int sum = 0;
        for (int i = 0; i < sizes[0]; i++) sum += arr[0][i];
        return sum;
    }
    int sum = 0;
    for (int i = 0; i < sizes[0]; i++)
        sum += recursiveArraySum((int**)arr[i], sizes + 1, dim - 1);
    return sum;
}

int main() {
    int a1[] = {1, 2};
    int a2[] = {3, 4, 5};
    int* arr[] = {a1, a2};
    int sizes[] = {2, 3};
    cout << recursiveArraySum(arr, sizes, 2);
}
