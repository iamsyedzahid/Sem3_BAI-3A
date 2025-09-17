#include <iostream>
#include <string>
using namespace std;

int linearSearch(string arr[], int n, string key, int &steps) {
    steps = 0;
    for (int i = 0; i < n; i++) {
        steps++;
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

int binarySearch(string arr[], int n, string key, int &steps) {
    int low = 0, high = n - 1;
    steps = 0;
    while (low <= high) {
        steps++;
        int mid = (low + high) / 2;
        if (arr[mid] == key) {
            return mid;
        } else if (key < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

int main() {
    string arr[] = {"Ahmed", "Ali", "Basit", "Karim", "Rizwan", "Sarwar", "Tariq", "Taufiq", "Yasin", "Zulfiqar"};
    int n = 10;

    string keys[] = {"Aftab", "Rizwan", "Tariq"};
    int stepsLinear, stepsBinary;

    cout << "Name\t Linear(Index,Steps)\t Binary(Index,Steps)" << endl;

    for (int i = 0; i < 3; i++) {
        int indexL = linearSearch(arr, n, keys[i], stepsLinear);
        int indexB = binarySearch(arr, n, keys[i], stepsBinary);

        cout << keys[i] << "\t (" << indexL << "," << stepsLinear << ")\t\t (" 
             << indexB << "," << stepsBinary << ")" << endl;
    }

    return 0;
}
