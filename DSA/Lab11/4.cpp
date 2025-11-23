#include <iostream>
#include <cmath>

const int MAX_SUM_MAP_SIZE = 101; 
const int EMPTY_SENTINEL = -99999; 

struct SumEntry {
    int sum = EMPTY_SENTINEL; 
    int a = EMPTY_SENTINEL;   
    int b = EMPTY_SENTINEL;   
};

SumEntry sumMap[MAX_SUM_MAP_SIZE]; 

int hashSum(int sum) {
    return std::abs(sum) % MAX_SUM_MAP_SIZE;
}

bool insertSum(int sum, int a, int b) {
    int index = hashSum(sum);
    int attempt = 0;

    while (attempt < MAX_SUM_MAP_SIZE) {
        int current_index = (index + attempt) % MAX_SUM_MAP_SIZE;

        if (sumMap[current_index].sum == EMPTY_SENTINEL) {
            sumMap[current_index].sum = sum;
            sumMap[current_index].a = a;
            sumMap[current_index].b = b;
            return true;
        }
        
        if (sumMap[current_index].sum == sum) {
            return true; 
        }

        attempt++;
    }
    return false;
}

int searchSumIndex(int sum) {
    int index = hashSum(sum);
    int attempt = 0;

    while (attempt < MAX_SUM_MAP_SIZE) {
        int current_index = (index + attempt) % MAX_SUM_MAP_SIZE;
        
        if (sumMap[current_index].sum == EMPTY_SENTINEL) {
            return -1; 
        }
        
        if (sumMap[current_index].sum == sum) {
            return current_index; 
        }
        
        attempt++;
    }
    return -1; 
}


void findPairsWithEqualSum(const int arr[], int n) {
    for (int i = 0; i < MAX_SUM_MAP_SIZE; ++i) {
        sumMap[i].sum = EMPTY_SENTINEL;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int currentSum = arr[i] + arr[j];

            int storedIndex = searchSumIndex(currentSum);

            if (storedIndex != -1) {
                SumEntry stored = sumMap[storedIndex];

                if (arr[i] != stored.a && arr[i] != stored.b &&
                    arr[j] != stored.a && arr[j] != stored.b) {

                    std::cout << "Output: (" << arr[i] << ", " << arr[j] << ") and ("
                              << stored.a << ", " << stored.b << ")" << std::endl;
                    std::cout << "Explanation: " << arr[i] << "+" << arr[j] << " = "
                              << stored.a << "+" << stored.b << std::endl;
                    return; 
                }
            }
            else {
                insertSum(currentSum, arr[i], arr[j]);
            }
        }
    }

    std::cout << "Output: No pairs found" << std::endl;
}
