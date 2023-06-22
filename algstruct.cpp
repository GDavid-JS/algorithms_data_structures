//Односвязный список - массив в котором хранится текущее значение элемента массива и адрес следующего элемента
#include <iostream>

template <typename T> class List {
private:
    template <typename T2> class Node;
    
    unsigned int list_length = 0;
    Node<T>* head = nullptr;
    Node<T>* last = nullptr;

    template <typename T2> class Node {
    public:
        Node* pNext;
        T2 data;

        Node(T2 data = T2(), Node* pNext = nullptr) {
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
            head = new Node<T>(data);
            last = head;
        } else {
            Node<T> *current = new Node<T>(data);
            last->pNext = current;
            last = current;
        }
    }

    void push_front(T data) {
        // Node<T> *last_head = head;
        head = new Node<T>(data, head);
        // head->pNext = last_head;

        list_length++;
    }

    void pop_back() {
        Node<T>* element = head;
        while (element->pNext->pNext != nullptr) {
            element = element->pNext;
        }

        delete last;
        last = element;
        last->pNext = nullptr;

        list_length--;
    }

    void pop_front() {
        Node<T> *new_head = head->pNext;
        delete head;
        head = new_head;
        list_length--;
    }

    void insert(T value, int index) {
        int counter = 0;
        Node<T>* element = head;
        Node<T>* new_element = new Node<T>(value);
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
        Node<T>* element = head;
        while (element != nullptr) {
            if (counter == index-1) {
                Node<T>* del_element = element->pNext;
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
        Node<T>* element = head;
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

    void print_all() {
        Node<T>* element = head;
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

    for (int i = 0; i < list.length(); i++) {
        std::cout << list[i] << "\n";
    }

   return 0; 
}