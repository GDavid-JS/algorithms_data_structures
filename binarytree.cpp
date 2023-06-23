//Бинарное дерево - каждая яцейка хранит данные, адрес элемента который меньше текущих данных и адрес элемента который больше текущих данных
#include <iostream>
#include <string>
#include <vector>
#include "queue.cpp"

template <typename T> class Tree {
private:
    class Node;
    
    unsigned int list_length = 0;
    Node* head = nullptr;

    class Node {
    public:
        Node* pRight;
        Node* pLeft;
        T data;

        Node(T data = T(), Node* pLeft = nullptr, Node* pRight = nullptr) {
            this->data = data;
            this->pLeft = pLeft;
            this->pRight = pRight;
        }
    };

    void add(T data, Node *&element) {
        if (element == nullptr) {
            element = new Node(data);
        } else {
            if (data > element->data) {
                add(data, element->pRight);
            } else if (data < element->data) {
                add(data, element->pLeft);
            }
        }
    }

    void print_levels(Node* element) {
        if (element == nullptr) {
            return;
        }

        Queue<Node*> queue;
        queue.push(element);

        std::vector<std::string> levels;

        while (!queue.is_empty()) {
            std::string level;

            int levelSize = queue.size();
            for (int i = 0; i < levelSize; i++) {
                Node* current = queue.front();
                queue.pop();

                level += std::to_string(current->data) + " ";

                if (current->pLeft != nullptr) {
                    queue.push(current->pLeft);
                }
                if (current->pRight != nullptr) {
                    queue.push(current->pRight);
                }
            }

            levels.push_back(level);
        }

        for (const auto& level : levels) {
            std::cout << level << "\n";
        }
    }

    void print(Node* element, const std::string& prefix = "", bool isLeft = true) {
        if (element == nullptr) {
            return;
        }

        std::cout << prefix;

        if (isLeft) {
            std::cout << "├── ";
        } else {
            std::cout << "└── ";
        }

        std::cout << element->data << std::endl;

        if (element->pLeft != nullptr && element->pRight != nullptr) {
            print(element->pLeft, prefix + (isLeft ? "│   " : "    "), true);
            print(element->pRight, prefix + (isLeft ? "│   " : "    "), false);
        } else if (element->pLeft != nullptr) {
            print(element->pLeft, prefix + "    ", true);
        } else if (element->pRight != nullptr) {
            print(element->pRight, prefix + "    ", false);
        }
    }

public:
    template <typename... Args> Tree(Args... args) {
        (add(args, head), ...);
    }

    void add(T data) {
        add(data, head);
    }

    void print_levels() {
        print_levels(head);
    }

    void print() {
        print(head);
    }
};

int main() {
    Tree<int> tree = {50, 25, 75, 12, 37, 63, 87, 6, 18, 31, 43, 56, 69, 81, 93, 3, 9, 15, 21, 28, 34, 40, 46, 53, 59, 65, 71, 78, 84, 90, 96, 1, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35, 38, 41, 44, 47, 51, 54, 57, 60, 64, 67, 70, 73, 76, 79, 82, 85, 88, 91, 94, 97, 99, 2, 4, 7, 10, 13, 16, 19, 22, 25, 27, 30, 33, 36, 39, 42, 45, 48, 52, 55, 58, 61, 66, 68, 72, 74, 77, 80, 83, 86, 89, 92, 95, 98};


    tree.print();
    std::cout << "\n";
    tree.print_levels();

   return 0; 
}