//
// Created by Grisha on 10.07.2021.
//

#ifndef BASE_CLASSES_MYDYNAMICARRAY_H
#define BASE_CLASSES_MYDYNAMICARRAY_H

#include <iostream>
#include <iterator>
#include <cstring>

template<typename T>
class newDynamicArray {
    template<typename t1, typename t2>
    struct cmpTypes {
        static const bool item = false;
    };

    template<typename u>
    struct cmpTypes<u, u> {
        static const bool item = true;
    };

    static T* createArr(size_t size) {
        if (!size)
            return nullptr;
        auto res = new int8_t[size * sizeof(T)];
        return reinterpret_cast<T*>(res);
    }

    static void removeArr(T* arr, size_t size = 0) {
        if (!size)
            return;
        for (size_t i = 0; i < size; i++)
            (arr+i)->~T();
        delete[] reinterpret_cast<int8_t*>(arr);
    }

    template<typename U, typename ...Args>
    void appendItems(size_t index, const U& item, Args...args) {
        new (array + index) T(item);
        appendItems(index + 1, args...);
    }

    template<typename U>
    void appendItems(size_t index, const U& item) {
        new (array + index) T(item);
    }

    T* array;
    size_t size;  //element count
    size_t cap;   //real array size
    T* swapBuff = createArr(1);
public:
    struct indexOutOfRange: std::exception {
        size_t index;
        explicit indexOutOfRange(size_t index = -1): index(index) {}

        const char* what() const noexcept override {
            return "Index out of range in dynamicArray";
        }
    };

    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T* item = nullptr;
    public:
        explicit iterator(T* item): item(item) {}

        iterator(const iterator &other): item(other.item) {}

        iterator& operator = (const iterator &other) {
            item(other.item);
            return *this;
        }

        T& operator*() {
            return *item;
        }

        T* operator->() {
            return item;
        }

        bool operator==(const iterator &other) const {
            return item == other.item;
        }

        bool operator!=(const iterator &other) const {
            return item != other.item;
        }

        iterator operator + (size_t num) {
            for (int i = 0; i < num; i++) {
                operator++();
            }
            return *this;
        }

        iterator operator + (int num) {
            if (num < 0)
                return operator-(-num);

            for (int i = 0; i < num; i++) {
                operator++();
            }
            return *this;
        }

        iterator operator - (size_t num) {
            for (int i = 0; i < num; i++) {
                operator--();
            }
            return *this;
        }

        iterator operator - (int num) {
            if (num < 0)
                return operator+(-num);

            for (int i = 0; i < num; i++) {
                operator--();
            }
            return *this;
        }

        iterator &operator++() {
            item++;
            return *this;
        }

        iterator operator++(int) {
            T* res = item;
            ++item;
            return iterator(res);
        }

        iterator &operator--() {
            item--;
            return *this;
        }

        iterator operator--(int) {
            T* res = item;
            --item;
            return iterator(res);
        }
    };

    explicit newDynamicArray(size_t capacity = 0): size(0), cap(capacity), array(createArr(capacity)) {}

    explicit newDynamicArray(size_t size, const T& val): size(size), cap(size), array(createArr(size)) {
        for (size_t i = 0; i < size; i++) {
            new(array + i) T(val);
        }
    }

    explicit newDynamicArray(const T* arr, size_t size): size(size), cap(size), array(createArr(size)) {
        for (size_t i = 0; i < size; i++) {
            new(array + i) T(arr[i]);
        }
    }

    newDynamicArray(const newDynamicArray<T>& dynamicArray):
                    size(dynamicArray.size), cap(dynamicArray.cap), array(createArr(dynamicArray.cap))
    {
        for (size_t i = 0; i < size; i++) {
            new(array + i) T(dynamicArray.array[i]);
        }
    }

    template<typename iterator>
    explicit newDynamicArray(iterator begin, iterator end):
                    size(std::distance(begin, end)), cap(size)
    {
        array = createArr(size);
        for (size_t i = 0; begin != end; ++begin, i++) {
            new(array + i) T(*begin);
        }
    }

    newDynamicArray(std::initializer_list<T> list):
                    size(std::distance(list.begin(), list.end())), cap(size)
    {
        array = createArr(size);
        size_t i = 0;
        for (auto& val : list) {
            new(array + i++) T(val);
        }
    }

    template <typename U, typename ...Args>
    explicit newDynamicArray(const U& item, Args... args):
                    size(sizeof...(args) + 2), cap(size)
    {
        array = createArr(size);
        appendItems(0, item, args...);
    }

    newDynamicArray(newDynamicArray<T>&& dynamicArray) noexcept : array(dynamicArray.array), size(dynamicArray.size),
                    cap(dynamicArray.cap) {
        dynamicArray.array = nullptr;
        dynamicArray.size = 0;
        dynamicArray.cap = 0;
    }

    ~newDynamicArray() {
        removeArr(array, size);
        removeArr(swapBuff, 1);
    }

    /*
    newDynamicArray& operator = (newDynamicArray<T> dynamicArray) {
        std::swap(array, dynamicArray.array);
        std::swap(size, dynamicArray.size);
        std::swap(cap, dynamicArray.cap);
        return *this;
    }
    */
    newDynamicArray& operator = (newDynamicArray<T>&& dynamicArray) noexcept {
        removeArr(array, size);
        array = dynamicArray.array;
        size = dynamicArray.size;
        cap = dynamicArray.cap;

        dynamicArray.array = nullptr;
        dynamicArray.size = 0;
        dynamicArray.cap = 0;

        return *this;
    }

    T& get(size_t index) {
        if (index >= size)
            throw indexOutOfRange(index);
        return array[index];
    }

    const T& get(size_t index) const {
        if (index >= size)
            throw indexOutOfRange(index);
        return array[index];
    }

    void set(const T& item, size_t index) {
        if (index >= size)
            throw indexOutOfRange(index);

        array[index] = std::move(item);
    }

    T& operator[](size_t index) {
        return array[index];
    }

    const T& operator[](size_t index) const {
        return array[index];
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return cap;
    }

    void resize(size_t newSize, const T& val = T()) {
        ///method for alloc memory if necessary and for calling constructor
        if (size == newSize)      //resize not needed
            return;

        if (newSize < size) {     //necessary to clear items from *newSize* to *size*
            for (size; size > newSize; size--) {
                (array + size)->~T();
            }
            return;
        }

        if (newSize < cap) {      //necessary to create objects *T* in memory
            for (size; size < newSize; size++) {
                new(array + size) T(val);
            }
            return;
        }

        //necessaty to alloc new array
        T *newArray = createArr(newSize);
        size_t i = 0;
        try {
            for (i; i < size; i++) {
                new(newArray + i) T(std::move(array[i]));
            }
            for (i; i < newSize; i++) {
                new(newArray + i) T(val);
            }
        }
        catch(...) {
            removeArr(newArray, i);
            throw;
        }
        removeArr(array, size);
        size = newSize;
        cap = newSize;
        array = newArray;
    }

    void recap(size_t newCapacity) {
        ///method for alloc free memory without calling constructor
        if (newCapacity == cap)    //recap not needed
            return;

        if (newCapacity < size) {  //recap with removing elements
            T* newArr = createArr(newCapacity);
            size_t i;
            try {
                for (i = 0; i < newCapacity; i++) {
                    new(newArr + i) T(std::move(array[i]));
                }
            }
            catch(...) {
                removeArr(newArr, i);
                throw;
            }
            removeArr(array, size);

            size = newCapacity;
            cap = newCapacity;
            array = newArr;
            return;
        }

        //recap without removing elements
        T* newArr = createArr(newCapacity);
        size_t i = 0;
        try {
            for (i; i < size; i++) {
                new(newArr + i) T(std::move(array[i]));
            }
        }
        catch(...) {
            removeArr(newArr, i);
            throw;
        }

        removeArr(array, size);
        cap = newCapacity;
        array = newArr;
    }

    T remove(size_t index) {
        if (index >= size)
            throw indexOutOfRange(index);

        T res = array[index];
        (array + index)->~T();
        if (index != size - 1) {
            for (size_t i = index; i < size - 1; i++) {
                array[i] = array[i + 1];
            }
            (array + size - 1)->~T();
        }
        --size;
        return res;
    }

    T removeCopy(size_t index) {
        if (index >= size)
            throw indexOutOfRange(index);

        T res = array[index];
        (array + index)->~T();
        if (index != size - 1) {
            memmove(array + index, array + index + 1, sizeof(T) * (size - index - 1));
            (array + size - 1)->~T();
        }
        --size;
        return res;
    }

    void swap(size_t index1, size_t index2) {
        ///change position of 2 elements (using =)
        if (index1 == index2)
            return;

        if (index1 >= size)
            throw indexOutOfRange(index1);
        if (index2 >= size)
            throw indexOutOfRange(index2);

        T item1 = std::move(array[index1]);
        array[index1] = std::move(array[index2]);
        array[index2] = std::move(item1);
    }

    void swapCopy(size_t index1, size_t index2) {
        ///change position of 2 elements (using memcpy)
        if (index1 >= size)
            throw indexOutOfRange(index1);
        if (index2 >= size)
            throw indexOutOfRange(index2);

        if (index1 == index2) {
            return;
        }

        memcpy(swapBuff, array + index1, sizeof(T));
        memcpy(array + index1, array + index2, sizeof(T));
        memcpy(array + index2, swapBuff, sizeof(T));
    }

    void move(size_t index1, size_t index2) {
        ///move element from index1 to index2 (using constructor)
        if (index1 >= size)
            throw indexOutOfRange(index1);
        if (index2 >= size)
            throw indexOutOfRange(index2);
        
        if (index1 == index2)
            return;
        
        T item = std::move(array[index1]);
        if (index1 < index2) {
            for (size_t i = index1; i < index2; i++) {
                array[i] = std::move(array[i+1]);
            }
        }
        else {
            for (size_t i = index1; i > index2; i--) {
                array[i] = std::move(array[i-1]);
            }
        }
        array[index2] = std::move(item);
    }
    
    void moveCopy(size_t index1, size_t index2) {
        ///move element from index1 to index2 (using memcpy and memmove)
        if (index1 >= size)
            throw indexOutOfRange(index1);
        if (index2 >= size)
            throw indexOutOfRange(index2);

        if (index1 == index2)
            return;
        
        memcpy(swapBuff, array + index1, sizeof(T));

        if (index1 > index2) {
            memmove(array + index2 + 1, array + index2, sizeof(T) * (index1 - index2));
        }
        else {
            memmove(array + index1, array + index1 + 1, sizeof(T) * (index2 - index1));
        }
        memcpy(array + index2, swapBuff, sizeof(T));
    }

    bool operator()() {
        return getSize();
    }

    iterator begin() {
        return iterator(array);
    }

    iterator end() {
        return iterator(array + size);
    }

    iterator begin() const {
        return iterator(array);
    }

    iterator end() const {
        return iterator(array + size);
    }
};

template<typename T>
class myDynamicArray {
private:
    template<typename t1, typename t2>
    struct cmpType {
        static const bool item = false;
    };

    template<typename u>
    struct cmpType<u, u> {
        static const bool item = true;
    };

    static void copyArr(size_t count, const T* from, T* to) {
        std::copy(from, from + count, to);
    }

    static void copyArr(size_t count, const T* from, T* to, long intent) {
        if (intent < 0) {
            std::copy(from - intent, from + count - intent, to);
//            for (size_t i = 0, j = -intent; j < count; i++, j++) {
//                to[i] = from[j];
//            }
        }
        else {
            std::copy(from, from + count, to + intent);
//            for (size_t i = intent, j = 0; j < count; i++, j++) {
//                to[i] = from[j];
//            }
        }
    }

    template<typename U, typename ...Args>
    void appendItems(size_t index, const U& item, Args...args) {
        appendItems(index, item);
        appendItems(index + 1, args...);
    }

    template<typename U>
    void appendItems(size_t index, const U& item) {
        if (cmpType<T, U>::item) {
            array[index] = item;
            return;
        }
        else {
            array[index] = static_cast<const T&>(item);
        }
    }

    static T* createArray(size_t size) {
        char* newArr = new char[sizeof(T) * size];
        return reinterpret_cast<T*>(newArr);
    }

    static void removeArray(T* arr, size_t size = 0) {
        if (size)
            for(size_t i = 0; i < size; i++);
//                ~(array[i]);
        delete[] reinterpret_cast<char*>(arr);
    }

    static void initializeArray(T* arr, size_t size, size_t index = 0) {
        for (size_t i = index; i < size; i++) {
            new(arr + i) T();
        }
    }

    size_t size = 0;                       //размер массива
    T* array = nullptr;                    //сам массив
    char* swapBuff = new char[sizeof(T)];  //буфер для свапа
public:
    class indexOutOfRange{};

    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> { //класс итератора
    private:
        T* item = nullptr;
    public:
        explicit iterator(T* item): item(item) {}

        iterator(const iterator &other): item(other.item) {}

        iterator& operator = (const iterator &other) {
            item(other.item);
            return *this;
        }

        T& operator*() {
            return *item;
        }

        T* operator->() {
            return item;
        }

        bool operator==(const iterator &other) const {
            return item == other.item;
        }

        bool operator!=(const iterator &other) const {
            return item != other.item;
        }

        iterator operator + (size_t num) {
            for (int i = 0; i < num; i++) {
                operator++();
            }
            return *this;
        }

        iterator operator + (int num) {
            if (num < 0)
                return operator-(-num);

            for (int i = 0; i < num; i++) {
                operator++();
            }
            return *this;
        }

        iterator operator - (size_t num) {
            for (int i = 0; i < num; i++) {
                operator--();
            }
            return *this;
        }

        iterator operator - (int num) {
            if (num < 0)
                return operator+(-num);

            for (int i = 0; i < num; i++) {
                operator--();
            }
            return *this;
        }

        iterator &operator++() {
            item++;
            return *this;
        }

        iterator operator++(int) {
            T* res = item;
            ++item;
            return iterator(res);
        }

        iterator &operator--() {
            item--;
            return *this;
        }

        iterator operator--(int) {
            T* res = item;
            --item;
            return iterator(res);
        }
    };

    myDynamicArray() = default; //пустой конструктор

    explicit myDynamicArray(T item) { //Конструктор через один объект
        size = 1;
        array = createArray(1);
        new(array) T(item);
    }

    myDynamicArray(const myDynamicArray<T>& dynamicArray) { //Копирующий конструктор
        size = dynamicArray.size;
        array = createArray(size);
        copyArr(size, dynamicArray.array, array);
    }

    template<typename iterator>
    explicit myDynamicArray(iterator begin, iterator end) { //Конструктор через итератор: myDynamicArray<int> dArray(thing.begin(), thing.end())
        resize(std::distance(begin, end));
        size_t ind = 0;
        for (auto i = begin; i != end; ++i, ind++) {
            new(array + ind) T(*i);
        }
    }

    myDynamicArray(std::initializer_list<T> list) { //Конструктор через массив (прикольная вещь): myDynamicArray<int> dArray{1, 2, 3, 4, 5};
        resize(list.size());
        size_t ind = 0;
        for (auto &i : list) {
            new(array + ind) T(i);
            ind++;
        }
    }

    template <typename U, typename ...Args>
    explicit myDynamicArray(const U& item, Args... args) {
        resize(sizeof...(args) + 1);
        appendItems(0, item, args...);
    }

    myDynamicArray(T* arr, size_t count) {  //Конструктор через массив и его длину
        size = count;
        array = createArray(size);
        for (size_t i = 0; i < size; i++) {
            new(array + i) T(arr[i]);
        }
    }

    ~myDynamicArray(){ //Деструктор
        removeArray(array, size);
        delete[] swapBuff;
    }

    myDynamicArray<T>& operator = (const myDynamicArray<T>& dynamicArray) {
        removeArray(array, size);
        size = dynamicArray.size;
        array = createArray(size);
//        resize(dynamicArray.size);
//        copyArr(size, dynamicArray.array, array);
        for (size_t i = 0; i < size; i++) {
            new(array + i) T(dynamicArray.array[i]);
        }
        return *this;
    }

    T get(size_t index) const {
        if (index >= size)
            throw indexOutOfRange();

        return array[index];
    }

    void set(const T& item, size_t index) {
        if (index >= size)
            throw indexOutOfRange();

        array[index] = item;
    }

    T& operator [] (size_t index) {
        if (index >= size)
            throw indexOutOfRange();

        return array[index];
    }

    const T& operator [] (size_t index) const {
        if (index >= size)
            throw indexOutOfRange();

        return array[index];
    }

    void resize(size_t newSize) {
        if (newSize == size)
            return;

        resize(newSize, 0);
    }

    void resize(size_t newSize, long intent) {
        if (newSize == 0) {
            removeArray(array, size);
            array = nullptr;
            size = 0;
            return;
        }

        T* newArr = new T[newSize];
        size_t minSize = (newSize > size ? size : newSize);
        copyArr(minSize, array, newArr, intent);
        for (size_t i = 0; i < -intent; i++) {
//            ~array[i];
        }
        removeArray(array);
        array = newArr;
        initializeArray(array, intent);
        size = newSize;
    }

    void resize(size_t newSize, long intent, size_t index) {
        if ((index >= newSize && (long) index + intent >= newSize) || index > size) {
            throw indexOutOfRange();
        }

        if (newSize == 0) {
            removeArray(array, size);
            array = nullptr;
            size = 0;
            return;
        }

        T* newArr = createArray(newSize);
        size_t minSize = (newSize > size ? size : newSize);
        copyArr(index, array, newArr);
        copyArr(minSize-index, array+index, newArr+index, intent);
        for (long i = 0; i < -intent; i++) {
//            ~array[i + index];
        }
        removeArray(array);
        array = newArr;
        if (intent > 0) {
            initializeArray(array, intent, index);
        }
        size = newSize;
    }

    size_t length() const {
        return size;
    }

    void swap(size_t index1, size_t index2) {
        if (index1 >= size)
            throw indexOutOfRange();
        if (index2 >= size)
            throw indexOutOfRange();

        if (index1 == index2)
            return;

//        T* item = (T*) malloc(sizeof(T));
        memcpy(swapBuff, array + index1, sizeof(T));
        memcpy(array + index1, array + index2, sizeof(T));    //более универсальный варик
        memcpy(array + index2, swapBuff, sizeof(T));
//        free(item);

//        T item = array[index1];
//        array[index1] = array[index2];                     //самый лёгкий варик
//        array[index2] = item;
    }

    void move(size_t indexFrom, size_t indexTo) {  //перемещает элемент с индексом 1 на место с индексом 2
        if (indexFrom >= size)
            throw indexOutOfRange();
        if (indexTo >= size)
            throw indexOutOfRange();

        if (indexFrom == indexTo)
            return;

        size_t count;
        if (indexFrom > indexTo) {
            count = indexFrom - indexTo;
            memcpy(swapBuff, array + indexFrom, sizeof(T));
            memmove(array + indexTo + 1, array + indexTo, sizeof(T) * count);
            memcpy(array + indexTo, swapBuff, sizeof(T));
        }
        else {
            count = indexTo - indexFrom;
            memcpy(swapBuff, array + indexFrom, sizeof(T));
            memmove(array + indexFrom, array + indexFrom + 1, sizeof(T) * count);
            memcpy(array + indexTo, swapBuff, sizeof(T));
        }
    }

    bool operator()() const {
        return size;
    }

    iterator begin() const { //Функция для итератора, возвращает итератор, указывающий на начало
        return iterator(array);
    }

    iterator end() const { //Функция для итератора, возвращает итератор, указывающий на конец
        return iterator(array + size);
    }
};

template<typename T>
std::ostream& operator << (std::ostream& cout, const myDynamicArray<T>& dynamicArray) {
    cout << "{";
    for (int i = 0; i < dynamicArray.length(); i++) {
        cout << dynamicArray[i];
        if (i == dynamicArray.length() - 1)
            break;

        cout << ", ";
    }
    return cout << "}";
}

template<typename T>
std::ostream& operator << (std::ostream& cout, const newDynamicArray<T>& dynamicArray) {
    cout << "{";
    for (int i = 0; i < dynamicArray.getSize(); i++) {
        cout << dynamicArray[i];
        if (i == dynamicArray.getSize() - 1)
            break;

        cout << ", ";
    }
    return cout << "}";
}

#endif //BASE_CLASSES_MYDYNAMICARRAY_H
