#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define tableSize 10
struct Node
{
    char key;
    string value;
    Node* next;
};
Node* arr[tableSize];

int hashFunction(int sum){
    return sum%tableSize;
}

int sumStr(string key){
    int sum = 0;
    int len = key.length();
    char arr[len+1];
    strcpy(arr, key.c_str());
    for (int i = 0; i < len; i++)
    {
        sum += arr[i];
    }
    return sum;
}
int size = 0;

void insert(char key, string value){
    int hashIndex = hashFunction(sumStr(value));
    
    Node* newNode = new Node;
    newNode->key = key;
    newNode->value = value;
    
    newNode->next = arr[hashIndex];
    arr[hashIndex] = newNode;
}

int main(){
    int nsum = sumStr("Zahid");
    int index = hashFunction(nsum);
    // cout << index<< endl;
    // cout << nsum;

    insert('a', "zahid");

    return 0;
}
