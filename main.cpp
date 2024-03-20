#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
public:
    Node<T>* head;
    Node<T>* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        clear();
    }

    void add(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    bool remove(T data) {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == data) {
                if (temp->prev) temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                if (temp == head) head = temp->next;
                if (temp == tail) tail = temp->prev;
                delete temp;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};

void testAddAndRemove() {
    DoublyLinkedList<int> list;

    list.add(1);
    list.add(2);
    list.add(3);

    assert(list.head->data == 1);
    assert(list.tail->data == 3);

    list.remove(2);

    assert(list.head->next->data == 3);
    assert(list.tail->prev->data == 1);

    std::cout << "Test Add and Remove Passed.\n";
}

int main()
{
    testAddAndRemove();
    return 0;
}
