//Односвязный список - массив в котором хранится текущее значение элемента массива и адрес следующего элемента
#include <iostream>

template <typename T> class List {
private:
    class Node;
    
    unsigned int list_length = 0;
    Node* head = nullptr;

    class Node {
    public:
        Node* pNext;
        T data;

        Node(T data = T(), Node* pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }
    };
public:

    template <typename... Args> List(Args... args) {
        (push_back(args), ...);
    }

    ~List() {
        clear();
    }

    void push_back(T data) {
        list_length++;

        if (head == nullptr) {
            head = new Node(data);
        } else {
            // last->pNext = new Node(data);
            // last = last->pNext;

            Node* element = head;
            while (element->pNext != nullptr) {
                element = element->pNext;
            }
            element->pNext = new Node(data);
        }
    }

    void push_front(T data) {
        // Node *last_head = head;
        head = new Node(data, head);
        // head->pNext = last_head;

        list_length++;
    }

    void pop_back() {
        Node* element = head;
        while (element->pNext->pNext != nullptr) {
            element = element->pNext;
        }

        delete element->pNext;
        element->pNext = nullptr;
        

        list_length--;
    }

    void pop_front() {
        Node *new_head = head->pNext;
        delete head;
        head = new_head;
        list_length--;
    }

    void insert(T value, int index) {
        int counter = 0;
        Node* element = head;
        Node* new_element = new Node(value);
        while (element != nullptr) {
            if (counter == index-1) {
                new_element->pNext = element->pNext;
                element->pNext = new_element;
                break;
            }

            element = element->pNext;
            counter+=1;
        }
        
        list_length++;
    }

    void removeAt(int index) {
        int counter = 0;
        Node* element = head;
        while (element != nullptr) {
            if (counter == index-1) {
                Node* del_element = element->pNext;
                element->pNext = element->pNext->pNext;
                delete del_element;
                break;
            }

            element = element->pNext;
            counter+=1;
        }
        
        list_length--;
    }

    void clear() {
        while (list_length) {
            pop_front();
        }
    }

    T& operator[] (const int index) {
        int counter = 0;
        Node* element = head;
        while (element != nullptr) {
            if (counter == index) {
                return element->data;
            }

            element = element->pNext;
            counter+=1;
        }

        throw std::out_of_range("Index out of range");
    }

    int length() {
        return list_length;
    }

    void print() {
        Node* element = head;
        while (element != nullptr) {
            std::cout << element->data << "\n";
            element = element->pNext;
        }
    }
};

int main() {
    List<float> list = {1,2,3};
    list.push_back(4);
    list.push_front(0);

    list.pop_back();
    list.pop_front();

    list.insert(2.5, 2);
    list.removeAt(2);
    list.print();

    // for (int i = 0; i < list.length(); i++) {
    //     std::cout << list[i] << "\n";
    // }

   return 0; 
}