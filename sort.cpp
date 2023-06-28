#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>

template <class T> class Analysis;

template <class T> class Sort {
private:
    T*array;
    const unsigned int LENGTH;
public:
    Sort(T*array, const unsigned int LENGTH) : array(array), LENGTH(LENGTH) {}
    Sort(const unsigned int LENGTH) : array(new T[LENGTH]), LENGTH(LENGTH) {}

    ~Sort() {
        delete [] array;
    }

    // Глупая сортировка O(n^3)
    static void stupid(T*array, const unsigned int LENGTH) {
        for (unsigned int i = 0; i < LENGTH-1; i++) {
            for (unsigned int i = 0; i < LENGTH-1; i++) {
                if (array[i] > array[i+1]) {
                    std::swap(array[i], array[i+1]);
                }
            }
        }
    }

    // Пузырьковая сортировка O(n^2)
    static void bubble(T*array, const unsigned int LENGTH) {
        for (unsigned int i = 0; i < LENGTH-1; i++) {
            for (unsigned int j = 0; j < LENGTH - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    std::swap(array[j], array[j + 1]);
                }
            }
        }
    }

    // является вариацией пузырьковой сортировки O(n^2) в худшем случае
    static void shaker(T*array, const unsigned int LENGTH) {
        for (unsigned int i = 0; i < LENGTH-1; i++) {
            for (unsigned int j = 0; j < LENGTH-i-1; j++) {
                if (array[j] > array[j+1]) {
                    std::swap(array[j], array[j+1]);
                }
            }

            for (int j = LENGTH-i-2; j >= 1; j--) {
                if (array[j] < array[j-1]) {
                    std::swap(array[j], array[j-1]);
                } 
            }
        }
    }

    // Четная-нечетная O(n^2) также является вариацией пузырьковой сортировки
    static void evenOdd(T*array, const unsigned int LENGTH) {
        bool swapped = true;
        while (swapped) {
            swapped = false;

            for (unsigned int i = 1; i < LENGTH-1; i+=2) {
                if (array[i] > array[i+1]) {
                    std::swap(array[i], array[i+1]);
                    swapped = true;
                }
            }

            for (unsigned int i = 0; i < LENGTH-1; i+=2) {
                if (array[i] > array[i+1]) {
                    std::swap(array[i], array[i+1]);
                    swapped = true;
                }
            }
        }
    }
    
    // Сортировка расчёской имеет временную сложность в среднем случае O(n^2), но в лучшем случае может достигать O(n*log n).
    static void comb(T*array, const unsigned int LENGTH) {
        unsigned int gap = LENGTH;
        bool swapped = true;

        while (gap > 1 || swapped) {
            swapped = false;
            gap = (gap * 10) / 13;

            for (unsigned int i = 0; i < LENGTH-gap; i++) {
                if (array[i] > array[i+gap]) {
                    std::swap(array[i], array[i+gap]);
                    swapped = true;
                }
            }
        }
    }

    // Сортировка вставками в худшем случае и среднем случае составляет O(n^2)
    static void insertion(T*array, const unsigned int LENGTH) {
        for (unsigned int i = 1; i < LENGTH; i++) {
            for(int j = i; j > 0 && array[j-1] > array[j]; j--) {
                std::swap(array[j-1], array[j]);
            }
        }
    }

    // Сортировка слиянием O(n log n)
    static void merge(T* array, const unsigned int LENGTH) {
        if (LENGTH <= 1) {
            return;
        }

        unsigned int mid = LENGTH / 2;
        unsigned int LEFTLENGTH = mid;
        unsigned int RIGHTLENGTH = LENGTH - mid;

        T* leftArray = new T[LEFTLENGTH];
        T* rightArray = new T[RIGHTLENGTH];

        for (unsigned int i = 0; i < LEFTLENGTH; i++) {
            leftArray[i] = array[i];
        }

        for (unsigned int i = 0; i < RIGHTLENGTH; i++) {
            rightArray[i] = array[mid + i];
        }

        merge(leftArray, LEFTLENGTH);
        merge(rightArray, RIGHTLENGTH);

        mergeArrays(leftArray, LEFTLENGTH, rightArray, RIGHTLENGTH, array);

        delete[] leftArray;
        delete[] rightArray;
    }

    // Объединяет два массива в один
    static void mergeArrays(const T* leftArray, const unsigned int LEFTLENGTH, const T* rightArray, const unsigned int RIGHTLENGTH, T* resultArray) {
        unsigned int i = 0;
        unsigned int j = 0;
        unsigned int k = 0;

        while (i < LEFTLENGTH && j < RIGHTLENGTH) {
            if (leftArray[i] <= rightArray[j]) {
                resultArray[k] = leftArray[i];
                i++;
            } else {
                resultArray[k] = rightArray[j];
                j++;
            }
            k++;
        }

        while (i < LEFTLENGTH) {
            resultArray[k] = leftArray[i];
            i++;
            k++;
        }

        while (j < RIGHTLENGTH) {
            resultArray[k] = rightArray[j];
            j++;
            k++;
        }
    }


    // Заполняет массив случайными числами
    static void fillArrayRandomNumbers(T*array, const unsigned int LENGTH, int MIN, int MAX) {
        std::srand(std::time(nullptr));

        for (int i = 0; i < LENGTH; i++) {
            array[i] = (std::rand() % (MAX - MIN + 1)) + MIN;
        }
    }

    static void print(T*array, const unsigned int LENGTH) {
        for (unsigned int i = 0; i < LENGTH; i++) {
            std::cout << array[i] << "\n";
        }
    }

    void stupid() {
        stupid(array, LENGTH);
    }

    void bubble() {
        bubble(array, LENGTH);
    }

    void shaker() {
        shaker(array, LENGTH);
    }

    void evenOdd() {
        evenOdd(array, LENGTH);
    }

    void comb() {
        comb(array, LENGTH);
    }

    void insertion() {
        insertion(array, LENGTH);
    }

    void merge() {
        merge(array, LENGTH);
    }

    void print() const {
        print(array, LENGTH);
    }

    void fillArrayRandomNumbers(const unsigned int MIN, const unsigned int MAX) {
        fillArrayRandomNumbers(array, LENGTH, MIN, MAX);
    }

    friend class Analysis<T>;
};

template <class T> class Analysis {
public:
    template<class Func> static double time(Func func) {
        auto start = std::chrono::steady_clock::now();
        func();
        auto end = std::chrono::steady_clock::now();

        auto duration = end - start;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

        return seconds + static_cast<double>(milliseconds);
    }

    static void test(T *arrayX, double *arrayY, const unsigned int LENGTH) {
        for (unsigned int i = 1; i < LENGTH; i++) {
            Sort<T> sort(i);
            sort.fillArrayRandomNumbers(0, LENGTH);
            arrayX[i] = i;
            arrayY[i] = time([&sort]() { sort.merge(); });

            // std::cout << time([&sort]() { sort.bubble(); }) << "\n";


            if (!isSort(sort)) {
                throw "Array is not sorted";
            }
        }
    }

    static bool isSort(Sort<T> &sort) {
        bool result = true;

        for (unsigned int i = 0; i < sort.LENGTH-1; i++) {
            if (sort.array[i] > sort.array[i+1]) {
                result = false;
            }
        }

        return result;
    }
};

int main() {
    // const unsigned int LENGTH = 10000;
    // Sort<int> sortArray(LENGTH);

    // sortArray.fillArrayRandomNumbers(0, 10000);

    // sortArray.stupid();

    // sortArray.print();

    // std::cout << "\n" << Analysis<int>::isSort(sortArray) << "\n";
    const unsigned int TESTLENGTH = 100;
    double *time = new double[TESTLENGTH];
    double *data = new double[TESTLENGTH];
    Analysis<double>::test(data, time, TESTLENGTH);

    for (unsigned int i = 0; i < TESTLENGTH; i++) {
        std::cout << data[i] << "\t" << time[i] << "\n";
    }

    // Sort<int>::print(data, TESTLENGTH);

    delete[] time;
    delete[] data;

    // Sort<int>::stupid(array, LENGTH);
    // Sort<int>::print(array, LENGTH);

    return 0;
}