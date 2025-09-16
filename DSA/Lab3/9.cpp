#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node(int v){data=v;next=NULL;}
};

void append(Node*& head,int v){
    Node* n=new Node(v);
    if(!head){head=n;return;}
    Node* t=head; while(t->next) t->next; t->next=n;
}

void print(Node* head){
    while(head){cout<<head->data<<" "; head=head->next;}
    cout<<endl;
}

void rearrange(Node*& head){
    if(!head || !head->next) return;
    Node* odd=head;
    Node* even=head->next;
    Node* evenHead=even;
    while(even && even->next){
        odd->next=even->next; odd=odd->next;
        even->next=odd->next; even=even->next;
    }
    Node* prev=NULL,*curr=evenHead;
    while(curr){ Node* nxt=curr->next; curr->next=prev; prev=curr; curr=nxt; }
    odd->next=prev;
}

int main(){
    int arr[]={10,4,9,1,3,5,9,4};
    Node* head=NULL;
    for(int v:arr){
        Node* n=new Node(v);
        if(!head){head=n;continue;}
        Node* t=head; while(t->next) t=t->next; t->next=n;
    }
    rearrange(head);
    print(head);
}
