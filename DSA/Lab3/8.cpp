#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev,*next;
    Node(int v){data=v;prev=next=NULL;}
};

void append(Node*& head,int v){
    Node* n=new Node(v);
    if(!head){head=n;return;}
    Node* t=head; while(t->next) t=t->next;
    t->next=n; n->prev=t;
}

Node* concat(Node* L, Node* M){
    if(!L) return M;
    if(!M) return L;
    Node* t=L; while(t->next) t=t->next;
    t->next=M; M->prev=t;
    return L;
}

void print(Node* head){
    while(head){cout<<head->data<<" ";head=head->next;}
    cout<<endl;
}

int main(){
    Node* L=NULL; append(L,1); append(L,2); append(L,3);
    Node* M=NULL; append(M,4); append(M,5);
    Node* C=concat(L,M);
    print(C);
}
