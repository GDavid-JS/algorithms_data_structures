#include <iostream>

template <class T> class Queue {
private:
    class Node;

    unsigned int length = 0;

    Node* head = nullptr;
    Node* tail = nullptr;

    class Node {
    public:
        Node* pNext;
        Node* pPrev;
        T data;

        Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr) {
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
    };
public:
    template <typename... Args> Queue(Args... args) {
        (push(args), ...);
    }

    ~Queue() {
        clear();
    }

    void push(T data) {
        if (head == nullptr) {
            head = new Node(data);
            tail = head;
        } else {
            Node *current = new Node(data);
            tail->pNext = current;
            current->pPrev = tail;
            tail = current;
        }

        length++;
    }

    T pop() {
        Node *new_head = head->pNext;
        T head_data = head->data;
        delete head;
        head = new_head;
        length--;

        return head_data;
    }

    T front() {
        return head->data;
    }

    bool is_empty() {
        return length ? false : true;
    }

    void clear() {
        while (length) {
            pop();
        }
    }

    void print() {
        Node* element = head;
        while (element != nullptr) {
            std::cout << element->data << "\n";
            element = element->pNext;
        }
    }

    unsigned int size() {
        return length;
    }
};

// int main() {
//     Queue<int> queue = {1,2,3};
    // std::cout << queue.pop() << "\n";
    // std::cout << queue.pop() << "\n";
    // queue.clear();

    // queue.print();
// }