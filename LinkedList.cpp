#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Insert at head
Node* insertAtHead(Node* head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    return newNode;
}

// Insert at tail
Node* insertAtTail(Node* head, int val) {
    Node* newNode = new Node(val);
    if (!head) return newNode;
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return head;
}

// Delete node by value
Node* deleteNode(Node* head, int val) {
    if (!head) return nullptr;
    if (head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    Node* curr = head;
    while (curr->next && curr->next->data != val)
        curr = curr->next;
    if (curr->next) {
        Node* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
    }
    return head;
}

// Print list
void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

int main() {
    Node* head = nullptr;

    head = insertAtHead(head, 3);
    head = insertAtHead(head, 2);
    head = insertAtHead(head, 1);

    head = insertAtTail(head, 4);
    head = insertAtTail(head, 5);

    cout << "Initial List: ";
    printList(head);

    head = deleteNode(head, 3);
    cout << "After Deleting 3: ";
    printList(head);

    head = deleteNode(head, 1);
    cout << "After Deleting 1 (Head): ";
    printList(head);

    return 0;
}




