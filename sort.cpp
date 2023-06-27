#include <iostream>
#include <cstdlib>
#include <ctime>

template <class T> class Sort {
private:
    T*array;
    const unsigned int length;
public:
    Sort(T*array, const unsigned int length) : array(array), length(length) {}
    Sort(const unsigned int length) : array(new T[length]), length(length) {}

    // Глупая сортировка O(n^3)
    static void stupid(T*array, const unsigned int length) {
        for (unsigned int i = 0; i < length-1; i++) {
            if (array[i] > array[i+1]) {
                std::swap(array[i], array[i+1]);
                stupid(array, length);
            }
        }
    }

    // Пузырьковая сортировка O(n^2)
    static void bubble(T*array, const unsigned int length) {
        for (unsigned int i = 0; i < length-1; i++) {
            for (unsigned int j = 0; j < length - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    std::swap(array[j], array[j + 1]);
                }
            }
        }
    }

    // является вариацией пузырьковой сортировки O(n^2) в худшем случае
    static void shaker(T*array, const unsigned int length) {
        for (unsigned int i = 0; i < length-1; i++) {
            for (unsigned int j = 0; j < length-i-1; j++) {
                if (array[j] > array[j+1]) {
                    std::swap(array[j], array[j+1]);
                }
            }

            for (int j = length-i-2; j >= 1; j--) {
                if (array[j] < array[j-1]) {
                    std::swap(array[j], array[j-1]);
                } 
            }
        }
    }

    // Четная-нечетная O(n^2) также является вариацией пузырьковой сортировки
    static void evenOdd(T*array, const unsigned int length) {
        bool swapped = true;
        while (swapped) {
            swapped = false;

            for (unsigned int i = 1; i < length-1; i+=2) {
                if (array[i] > array[i+1]) {
                    std::swap(array[i], array[i+1]);
                    swapped = true;
                }
            }

            for (unsigned int i = 0; i < length-1; i+=2) {
                if (array[i] > array[i+1]) {
                    std::swap(array[i], array[i+1]);
                    swapped = true;
                }
            }
        }
    }
    
    // Сортировка расчёской имеет временную сложность в среднем случае O(n^2), но в лучшем случае может достигать O(n*log n).
    static void comb(T*array, const unsigned int length) {
        unsigned int gap = length;
        bool swapped = true;

        while (gap > 1 || swapped) {
            swapped = false;
            gap = (gap * 10) / 13;

            for (unsigned int i = 0; i < length-gap; i++) {
                if (array[i] > array[i+gap]) {
                    std::swap(array[i], array[i+gap]);
                    swapped = true;
                }
            }
        }
    }

    // Сортировка вставками в худшем случае и среднем случае составляет O(n^2)
    static void insertion(T*array, const unsigned int length) {
        for (unsigned int i = 1; i < length; i++) {
            for(int j = i; j > 0 && array[j-1] > array[j]; j--) {
                std::swap(array[j-1], array[j]);
            }
        }
    }

    // Сортировка слиянием
    static void merge(T*array, const unsigned int length) {
        for (unsigned int i = 1; i < length; i++) {

        }
    }

    static void fillArrayRandomNumbers(T*array, const unsigned int length, int min, int max) {
        std::srand(std::time(nullptr));

        for (int i = 0; i < length; i++) {
            array[i] = (std::rand() % (max - min + 1)) + min;
        }
    }

    static void print(T*array, const unsigned int length) {
        for (unsigned int i = 0; i < length; i++) {
            std::cout << array[i] << "\n";
        }
    }

    void stupid() {
        stupid(array, length);
    }

    void bubble() {
        bubble(array, length);
    }

    void shaker() {
        shaker(array, length);
    }

    void evenOdd() {
        evenOdd(array, length);
    }

    void comb() {
        comb(array, length);
    }

    void insertion() {
        insertion(array, length);
    }

    void merge() {
        merge(array, length);
    }

    void print() const {
        print(array, length);
    }

    void fillArrayRandomNumbers(const unsigned int min, const unsigned int max) {
        fillArrayRandomNumbers(array, length, min, max);
    }
};

int main() {
    const unsigned int length = 10;
    Sort<int> sortArray(length);

    sortArray.fillArrayRandomNumbers(0, 10000);

    // sortArray.insertion();
    sortArray.print();

    // Sort<int>::stupid(array, length);
    // Sort<int>::print(array, length);

    return 0;
}