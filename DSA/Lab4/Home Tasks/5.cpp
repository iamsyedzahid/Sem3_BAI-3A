#include <iostream>
using namespace std;

void sortBirthYears(int arr[], int n) {
    int low = 0, mid = 0, high = n-1;

    while(mid <= high) {
        if(arr[mid] == 2022) {
            swap(arr[low++], arr[mid++]);
        }
        else if(arr[mid] == 2023) {
            mid++;
        }
        else { // 2024
            swap(arr[mid], arr[high--]);
        }
    }
}

int main() {
    int arr[] = {2022, 2023, 2024, 2022, 2023, 2024};
    int n = sizeof(arr)/sizeof(arr[0]);

    sortBirthYears(arr, n);

    cout << "Sorted Array: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
