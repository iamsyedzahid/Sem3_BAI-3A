#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int v) { data = v; next = NULL; }
};

void print(Node* head) {
    if (!head) return;
    Node* temp = head;
    do { cout << temp->data << " "; temp=temp->next; } while(temp!=head);
    cout << endl;
}

void insertEnd(Node*& head,int v) {
    Node* n=new Node(v);
    if (!head) { head=n; n->next=head; return; }
    Node* t=head; while(t->next!=head) t=t->next;
    t->next=n; n->next=head;
}

void insertFront(Node*& head,int v) {
    Node* n=new Node(v);
    if(!head){ head=n; n->next=head; return; }
    Node* t=head; while(t->next!=head) t=t->next;
    n->next=head; t->next=n; head=n;
}

void insertAtPos(Node*& head,int v,int pos){
    if(pos==1){insertFront(head,v);return;}
    Node* t=head;
    for(int i=1;i<pos-1 && t->next!=head;i++) t=t->next;
    Node* n=new Node(v); n->next=t->next; t->next=n;
}

void deleteNode(Node*& head,int v){
    if(!head) return;
    if(head->data==v && head->next==head){ delete head; head=NULL; return; }
    Node* t=head,*prev=NULL;
    do{ if(t->data==v) break; prev=t; t=t->next; }while(t!=head);
    if(t==head){
        prev=head; while(prev->next!=head) prev=prev->next;
        prev->next=head->next;
        Node* d=head; head=head->next; delete d; return;
    }
    prev->next=t->next; delete t;
}

int main(){
    Node* head=NULL;
    insertEnd(head,10); insertEnd(head,20); insertEnd(head,30);
    insertFront(head,5);
    insertAtPos(head,15,3);
    deleteNode(head,20);
    print(head);
}
