template <class T> class Stack {
private:
    class Node;
    Node* head = nullptr;
    unsigned int length = 0;

    class Node {
    public:
        Node* address;
        T data;

        Node(T data = T(), Node* address = nullptr) {
            this->data = data;
            this->address = address;
        }
    };
public:
    Stack(std::initializer_list<T> args) {
        for (int arg : args) {
            push(arg);
        }
    }

    void push(T data) {
        if (head == nullptr) {
            head = new Node(data);
        } else {
            Node* last_head = head;
            head = new Node(data);
            head->address = last_head;
        }

        length++;
    }

    ~Stack() {
        clear();
    }

    T pop() {
        Node* last_head = head->address;
        T last_data = head->data; 
        delete head;
        head = last_head;
        length--;
        return last_data;
    }

    void clear() {
        while(length) {
            pop();
        }
    }

    void print() {
        Node* element = head;

        while (element != nullptr) {
            std::cout << element->data << "\n";
            element = element->address;
        }
    }
};

// int main() {
//     Stack<float> stack = {1,2,3};

//     stack.push(10);
//     stack.push(101);

//     stack.print();
//     std::cout << "\n";

//     float value = stack.pop();
//     std::cout << value << "\n\n";

//     stack.print();

//     stack.clear();
//     stack.print();

//     return 0;
// }