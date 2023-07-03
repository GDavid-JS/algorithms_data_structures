#include "includes.h"

template <class T> class Sort {
private:
    T*array;
    const unsigned int LENGTH;
public:
    Sort(T*array, const unsigned int LENGTH) : array(array), LENGTH(LENGTH) {}
    Sort(const unsigned int LENGTH) : array(new T[LENGTH]), LENGTH(LENGTH) {}

    // Глупая сортировка O(n^3)
    static void stupid(T* array, const unsigned int LENGTH) {
        for (unsigned int i = 0; i < LENGTH; i++) {
            for (unsigned int j = 0; j < LENGTH - 1; j++) {
                if (array[j] > array[j+1]) {
                    std::swap(array[j], array[j+1]);
                }
            }
        }
    }

    // Пузырьковая сортировка O(n^2)
    static void bubble(T*array, const unsigned int LENGTH) {
        for (unsigned int i = 0; i < LENGTH; i++) {
            for (unsigned int j = 0; j < LENGTH-i-1; j++) {
                if (array[j] > array[j+1]) {
                    std::swap(array[j], array[j+1]);
                }
            }
        }
    }

    // является вариацией пузырьковой сортировки O(n^2) в худшем случае
    static void shaker(T* array, const unsigned int LENGTH) {
        unsigned int left = 0;
        unsigned int right = LENGTH - 1;
        bool swapped = false;

        while (left < right) {
            // Проход слева направо (аналогично обычной пузырьковой сортировке)
            for (unsigned int i = left; i < right; i++) {
                if (array[i] > array[i + 1]) {
                    std::swap(array[i], array[i + 1]);
                    swapped = true;
                }
            }
            right--;

            // Если не было обменов, значит массив уже отсортирован
            if (!swapped) {
                break;
            }

            swapped = false;

            // Проход справа налево
            for (unsigned int i = right; i > left; i--) {
                if (array[i] < array[i - 1]) {
                    std::swap(array[i], array[i - 1]);
                    swapped = true;
                }
            }
            left++;
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
            gap = (gap * 10) / 13;

            if (gap < 1) {
                gap = 1;
            }
            swapped = false;

            for (unsigned int i = 0; i < LENGTH-gap; i++) {
                if (array[i] > array[i+gap]) {
                    std::swap(array[i], array[i+gap]);
                    swapped = true;
                }
            }
        }
    }

    // Сортировка вставками в худшем случае и среднем случае составляет O(n^2)
    static void insertion(T* array, const unsigned int LENGTH) {
        for (unsigned int i = 1; i < LENGTH; i++) {
            T key = array[i];
            int j = i - 1;

            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j--;
            }

            array[j + 1] = key;
        }
    }


    static void selection(T* array, const unsigned int LENGTH) {
        for (unsigned int i = 0; i < LENGTH; i++) {
            unsigned int minIndex = i;

            for (unsigned int j = i + 1; j < LENGTH; j++) {
                if (array[j] < array[minIndex]) {
                    minIndex = j;
                }
            }

            if (minIndex != i) {
                std::swap(array[i], array[minIndex]);
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

    // разделяет массив на две части
    static int partition(T* array, int low, int high) {
        T pivot = array[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (array[j] < pivot) {
                i++;
                std::swap(array[i], array[j]);
            }
        }

        std::swap(array[i + 1], array[high]);
        return i + 1;
    }

    // Быстрая сортировка
    static void quick(T* array, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(array, low, high);

            quick(array, low, pivotIndex - 1);
            quick(array, pivotIndex + 1, high);
        }
    }

    static void quick(T* array, int length) {
        quick(array, 0, length - 1);
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

    static T max(T*array, const unsigned int LENGTH) {
        T maxElement = array[0];
        for (unsigned int i = 1; i < LENGTH; i++) {
            if (maxElement < array[i]) {
                maxElement = array[i];
            }
        }

        return maxElement;
    }

    static T min(T*array, const unsigned int LENGTH) {
        T minElement = array[0];
        for (unsigned int i = 1; i < LENGTH; i++) {
            if (minElement > array[i]) {
                minElement = array[i];
            }
        }

        return minElement;
    }

    static T sum(T*array, const unsigned int LENGTH) {
        T sumResult = array[0];
        for (unsigned int i = 1; i < LENGTH; i++) {
            sumResult += array[i];
        }

        return sumResult;
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

    void selection() {
        selection(array, LENGTH);
    }

    void merge() {
        merge(array, LENGTH);
    }

    void quick() {
        quick(array, LENGTH);
    }

    void print() const {
        print(array, LENGTH);
    }

    T max() const {
        return max(array, LENGTH);
    }

    T min() const {
        return min(array, LENGTH);
    }

    T sum() const {
        return sum(array, LENGTH);
    }

    void fillArrayRandomNumbers(const unsigned int MIN, const unsigned int MAX) {
        fillArrayRandomNumbers(array, LENGTH, MIN, MAX);
    }

    friend class Analysis<T>;
};

template <class T> class Analysis {
private:
    template<class FuncSort> void test(FuncSort funcSort) {
        for (unsigned int i = 1; i < length; i++) {
            Sort<T> sort(i);
            sort.fillArrayRandomNumbers(0, length);
            data[i] = i;
            timeValue[i] = time([&funcSort, &sort]() { funcSort(sort); });

            if (!isSort(sort)) {
                throw "Array is not sorted";
            }
        }
    }
protected:
    unsigned int length;
    double *timeValue;
    T *data;

    template<class FuncSort, class PltFunc> void test(FuncSort funcSort, PltFunc pltfunc) {
        for (unsigned int i = 1; i < length; i++) {
            Sort<T> sort(i);
            sort.fillArrayRandomNumbers(0, length);
            data[i] = i;
            timeValue[i] = time([&funcSort, &sort]() { funcSort(sort); });
            pltfunc(data, timeValue, i);

            if (!isSort(sort)) {
                throw "Array is not sorted";
            }
        }
    }
public:
    Analysis(unsigned int length) : length(length), timeValue(new double[length]), data(new T[length]) {}
    ~Analysis() {
        delete [] timeValue;
        delete [] data;
    }

    static double time(std::function<void()> func) {
        auto start = std::chrono::steady_clock::now();
        func();
        auto end = std::chrono::steady_clock::now();

        auto duration = end - start;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

        return seconds + static_cast<double>(milliseconds)/1000;
        // return seconds;
    }

    virtual void testStupid() {
        test([](Sort<double>& sort) {
            sort.stupid();
        });
    }

    virtual void testBubble() {
        test([](Sort<double>& sort) {
            sort.bubble();
        });
    }

    virtual void testShaker() {
        test([](Sort<double>& sort) {
            sort.shaker();
        });
    }

    virtual void testEvenOdd() {
        test([](Sort<double>& sort) {
            sort.evenOdd();
        });
    }

    virtual void testComb() {
        test([](Sort<double>& sort) {
            sort.comb();
        });
    }

    virtual void testInsertion() {
        test([](Sort<double>& sort) {
            sort.insertion();
        });
    }

    virtual void testSelection() {
        test([](Sort<double>& sort) {
            sort.selection();
        });
    }

    virtual void testMerge() {
        test([](Sort<double>& sort) {
            sort.merge();
        });
    }

    virtual void testQuick() {
        test([](Sort<double>& sort) {
            sort.quick();
        });
    }

    T* getData() {
        return data;
    }

    unsigned int getLength() {
        return length;
    }

    double* getTime() {
        return timeValue;
    }

    static bool isSort(Sort<T> &sort) {
        for (unsigned int i = 0; i < sort.LENGTH-1; i++) {
            if (sort.array[i] > sort.array[i+1]) {
                std::cout << i << "\t" << sort.array[i] << "\t" << sort.array[i+1] << "\n";
                return false;
            }
        }

        return true;
    }
};

class Plt : public QCustomPlot {
private:
    QString title;
    QVector<QCPGraph*> graphs;
public:
    Plt(QString title) : title(title) {
        yAxis->setRange(0, 0.1);

        // Установка цвета и ширины сетки
        QPen gridPen;
        gridPen.setColor(QColor("black")); // Установка цвета сетки (серый)
        gridPen.setWidth(1); // Установка ширины линии сетки
        xAxis->grid()->setPen(gridPen);
        yAxis->grid()->setPen(gridPen);

        // Установка цвета и ширины подсетки
        QPen subGridPen;
        subGridPen.setColor(QColor("black")); // Установка цвета подсетки (светло-серый)
        subGridPen.setWidth(1); // Установка ширины линии подсетки
        xAxis->grid()->setSubGridPen(subGridPen);
        yAxis->grid()->setSubGridPen(subGridPen);


        xAxis->setLabel("Объем данных");
        yAxis->setLabel("Время (миллисек)");

        // Настройка заголовка графика
        QCPTextElement *plotTitle = new QCPTextElement(this, title);
        QFont titleFont("Roboto", 14, QFont::Bold);
        plotTitle->setFont(titleFont);
        plotTitle->setTextColor(QColor("#black"));
        plotLayout()->insertRow(0);
        plotLayout()->addElement(0, 0, plotTitle);

        // Настройка фона графика
        setBackground(QColor("#fff"));
    }

    template <class T> Plt(QString title, T* arrayX, T* arrayY, const unsigned int LENGTH) : Plt(title) {
        addFunction<T>(arrayX, arrayY, LENGTH);
    }

    QCPGraph* addGraph() {
        QCPGraph* graph = QCustomPlot::addGraph();
        QPen pen(QColor("#FF5A5F"));
        pen.setWidth(2);
        graph->setPen(pen);
        graphs.append(graph);
        return graph;
    }

    template <class T> void addData(const unsigned short INDEX, T x, T y) {
        graphs[INDEX]->addData(x, y);
        rescaleAxes();
        replot();
    }

    template <class T> void addFunction(T* arrayX, T* arrayY, const unsigned int LENGTH) {
        QVector<T> vectorX(arrayX, arrayX + LENGTH);
        QVector<T> vectorY(arrayY, arrayY + LENGTH);

        addGraph();
        graphs.last()->setData(vectorX, vectorY);
        rescaleAxes();
        replot();
    }
};

template <class T> class PltTest : public Plt, Analysis<T> {
private:
    template <class Func> void test(Func func) {
        Analysis<T>::test(func, [&](T* arrayX, double* arrayY, const unsigned int index) {
            this->addData(0, static_cast<double>(arrayX[index]), arrayY[index]);
        });
    }
public:
    PltTest(unsigned int length, QString title) : Plt(title), Analysis<T>(length) {
        Plt::addGraph();
    }

    void testStupid() override {
        PltTest<T>::test([](Sort<T>& sort) {
            sort.stupid();
        });
    }

    void testBubble () override {
        PltTest<T>::test([](Sort<T>& sort) {
            sort.bubble();
        });
    }

    void testShaker () override {
        PltTest<T>::test([](Sort<T>& sort) {
            sort.shaker();
        });
    }

    void testEvenOdd () override {
        PltTest<T>::test([](Sort<T>& sort) {
            sort.evenOdd();
        });
    }

    void testComb () override {
        PltTest<T>::test([](Sort<T>& sort) {
            sort.comb();
        });
    }

    void testInsertion () override {
        PltTest<T>::test([](Sort<T>& sort) {
            sort.insertion();
        });
    }

    void testSelection () override {
        PltTest<T>::test([](Sort<T>& sort) {
            sort.selection();
        });
    }

    void testMerge () override {
        PltTest<T>::test([](Sort<T>& sort) {
            sort.merge();
        });
    }

    void testQuick () override {
        PltTest<T>::test([](Sort<T>& sort) {
            sort.quick();
        });
    }

    using Analysis<T>::getData;
    using Analysis<T>::getLength;
    using Analysis<T>::getTime;
};

class Tab : public QWidget {
public:
    Tab(QWidget* parent = nullptr) : QWidget(parent) {
        this->setStyleSheet("background-color: #fff;");
    }
};

class MainTab : public Tab {
private:
    unsigned short length = 9;
    PltTest<double>** plt = new PltTest<double>*[length];
    QString *pltName = new QString[length]{"Quick","Merge","Comb","Selection","Insertion","EvenOdd","Shaker","Bubble","Stupid"};
public:
    MainTab(QWidget* parent = nullptr) : Tab(parent) {
        for (unsigned short i = 0; i < length; i++) {
            plt[i] = new PltTest<double>(1300, pltName[i]);
        }

        QVBoxLayout* layout = new QVBoxLayout(this);

        // Создаем компонент с кнопкой
        QWidget* buttonWidget = new QWidget(this);
        QVBoxLayout* buttonLayout = new QVBoxLayout(buttonWidget);
        buttonLayout->setAlignment(Qt::AlignCenter);

        QPushButton* startButton = new QPushButton("Start", buttonWidget);
        startButton->setFixedSize(150, 50);
        startButton->setStyleSheet("QPushButton { text-transform: uppercase; background-color: #000; color: #fff;}");

        QObject::connect(startButton, &QPushButton::clicked, [this]() {
            plt[0]->testQuick();
            plt[1]->testMerge();
            plt[2]->testComb();
            plt[3]->testSelection();
            plt[4]->testInsertion();
            plt[5]->testEvenOdd();
            plt[6]->testShaker();
            plt[7]->testBubble();
            plt[8]->testStupid();
        });

        buttonLayout->addWidget(startButton);
        buttonWidget->setLayout(buttonLayout);

        QSizePolicy buttonSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        buttonSizePolicy.setVerticalStretch(1);
        buttonWidget->setSizePolicy(buttonSizePolicy);

        // Создаем компонент с сеткой графиков
        QWidget* gridWidget = new QWidget(this);
        QGridLayout* gridLayout = new QGridLayout(gridWidget);

        unsigned short rowLength = 3;
        unsigned short collLength = 3;
        for (unsigned short row = 0; row < rowLength; row++) {
            for (unsigned short col = 0; col < collLength; col++) {
                gridLayout->addWidget(plt[row * collLength + col], row, col);
            }
        }

        gridWidget->setLayout(gridLayout);

        // Добавляем компоненты в вертикальный компоновщик
        layout->addWidget(buttonWidget);
        layout->addWidget(gridWidget);

        this->setLayout(layout);
    }
};

class ListTab : public Tab {
public:
    ListTab(QWidget* parent = nullptr) : Tab(parent) {
        QVBoxLayout* layout = new QVBoxLayout(this);
        Plt* plt1 = new Plt("text");
        Plt* plt2 = new Plt("text");

        QSplitter* splitter = new QSplitter(Qt::Horizontal, this);

        splitter->addWidget(plt1);
        splitter->addWidget(plt2);

        layout->addWidget(splitter);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // Создание главного окна
    QMainWindow mainWindow;

    // Создание QTabWidget
    QTabWidget tabWidget(&mainWindow);

    QWidget* mainTab = new MainTab();
    QWidget* listTab = new ListTab();
    QWidget* doublyListTab = new QWidget();
    QWidget* binaryTreeTab = new QWidget();
    QWidget* queueTab = new QWidget();
    QWidget* stackTab = new QWidget();
    QWidget* hashTableTab = new QWidget();

    // Добавление новой вкладки в QTabWidget
    tabWidget.addTab(mainTab, "Сортировка");
    tabWidget.addTab(listTab, "Односвязный список");
    tabWidget.addTab(doublyListTab, "Двусвязный список");
    tabWidget.addTab(binaryTreeTab, "Бинарное дерево");
    tabWidget.addTab(queueTab, "Очередь");
    tabWidget.addTab(stackTab, "Стек");
    tabWidget.addTab(hashTableTab, "Хэш таблица");

    // Установка QTabWidget в качестве основного виджета главного окна
    mainWindow.setCentralWidget(&tabWidget);

    // Отображение главного окна
    mainWindow.showFullScreen();

    return app.exec();
}