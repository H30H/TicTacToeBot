//
// Created by Grisha on 10.07.2021.
//

#ifndef BASE_CLASSES_MYARRAYSEQUENCE_H
#define BASE_CLASSES_MYARRAYSEQUENCE_H

#include "mySequence.h"
#include "myDynamicArray.h"

template<typename T>
class newArraySequence {
    static size_t defaultResizeFunc(size_t size, size_t newSize) {
        if (size == 0)
            size = 1;

        while (size <= newSize)
            size *= 2;

        while (size > newSize * 2 && size != 1) {
            size /= 2;
        }

        return size;
    }

    newDynamicArray<T> dynamicArray;
    size_t size;
    size_t cap;

    size_t (*resizeFunc)(size_t size, size_t newSize) = defaultResizeFunc;

    template<typename U, typename...Args>
    static size_t getArgsCount(const U& item, Args...args) {
        return getArgsCount(args...);
    }

    template<typename U>
    static size_t getArgsCount(const U& item) {
        return 1;
    }

    template<typename ...Args>
    void appendItems(const T& item, Args...args) {
        resizeFunc(size++ + 1, item);
        appendItems(args...);
    }

    void appendItems(const T& item) {
        resizeFunc(size++ + 1, item);
    }

    void recap(size_t newSize) {
        size_t newCap = resizeFunc(cap, newSize);
        if (cap != newCap) {
            cap = newCap;
            dynamicArray.recap(cap);
        }
        if (cap < size)
            size = cap;
    }


public:
    struct indexOutOfRange: std::exception {
        size_t index;
        explicit indexOutOfRange(size_t index = -1): index(index) {}

        const char* what() const noexcept override {
            return "Index out of range in dynamicArray";
        }
    };

    class iterator: std::iterator<std::random_access_iterator_tag, T> { //класс итератора
    private:
        T* item = nullptr;
    public:
        explicit iterator(T* item): item(item) {}

        iterator(const iterator &other): item(other.item) {}

        explicit iterator(const typename myDynamicArray<T>::iterator& other): item(other.item) {}

        iterator& operator = (const iterator &other) {
            item(other.item);
            return *this;
        }

        T& operator*() const {
            return *item;
        }

        T* operator->() const {
            return item;
        }

        bool operator==(const iterator &other) const {
            return item == other.item;
        }

        bool operator!=(const iterator &other) const {
            return item != other.item;
        }

        iterator& operator + (int num) {
            if (num < 0)
                return operator-(-num);

            for (int i = 0; i < num; i++) {
                operator++();
            }
            return *this;
        }

        iterator& operator - (int num) {
            if (num < 0)
                return operator+(-num);

            for (int i = 0; i < num; i++) {
                operator--();
            }
            return *this;
        }

        iterator& operator++() {
            item++;
            return *this;
        }

        iterator operator++(int) {
            T* res = item;
            ++item;
            return iterator(res);
        }

        iterator& operator--() {
            item--;
            return *this;
        }

        iterator operator--(int) {
            T* res = item;
            --item;
            return iterator(res);
        }
    };

    explicit newArraySequence(size_t (*resizeFunc)(size_t size, size_t newSize) = defaultResizeFunc): resizeFunc(resizeFunc), size(0), cap(0) {
        recap(0);
    }

    explicit newArraySequence(T* arr, size_t size, size_t (*resizeFunc)(size_t size, size_t newSize) = defaultResizeFunc):
                              resizeFunc(resizeFunc), size(0) {
        cap = resizeFunc(0, size);
        dynamicArray.recap(cap);
        for (size_t i = 0; i < size; i++) {
            append(arr[i]);
        }
    }

    template<typename iterator>
    explicit newArraySequence(iterator begin, iterator end, size_t (*resizeFunc)(size_t size, size_t newSize) = defaultResizeFunc):
                              resizeFunc(resizeFunc), size(0) {
        cap = resizeFunc(0, std::distance(begin, end));
        dynamicArray.recap(cap);
        for (begin; begin != end; ++begin) {
            append(*begin);
        }
    }

    newArraySequence(std::initializer_list<T> list, size_t (*resizeFunc)(size_t size, size_t newSize) = defaultResizeFunc):
                     resizeFunc(resizeFunc), size(0) {
        cap = resizeFunc(0, std::distance(list.begin(), list.end()));
        dynamicArray.recap(cap);
        for (auto &i : list) {
            append(i);
        }
    }

    newArraySequence(const newArraySequence<T>& sequence): size(sequence.size), cap(sequence.cap),
                     dynamicArray(sequence.dynamicArray), resizeFunc(sequence.resizeFunc) {}

    newArraySequence(newArraySequence<T>&& sequence) noexcept : dynamicArray(std::move(sequence.dynamicArray)),
                     size(sequence.size), cap(sequence.cap), resizeFunc(sequence.resizeFunc) {
        sequence.recap(0);
    }

    newArraySequence& operator = (const newArraySequence<T>& sequence) {
        size = sequence.size;
        cap = sequence.cap;
        resizeFunc = sequence.resizeFunc;
        dynamicArray = sequence.dynamicArray;
        return *this;
    }

    newArraySequence& operator = (newArraySequence<T>&& sequence) noexcept {
        dynamicArray = std::move(sequence.dynamicArray);
        size = sequence.size;
        cap = sequence.cap;
        resizeFunc = sequence.resizeFunc;
        sequence.recap(0);
        return *this;
    }

    template<typename ...Args>
    void append(const T& item, Args...args) {
        size_t count = getArgsCount(args...) + 1;
        recap(size + count);
        appendItems(item, args...);
    }

    void append(const T& item) {
        recap(size + 1);
        dynamicArray.resize(++size, item);
    }

    void prepend(const T& item) {
        recap(size + 1);

        dynamicArray.resize(++size, item);
        dynamicArray.move(size - 1, 0);
    }

    void insert(const T& item, size_t index) {
        if (index > size)
            throw indexOutOfRange(index);
        if (index == size)
            append(item);
        if (index == 0)
            prepend(item);

        recap(size + 1);

        dynamicArray.resize(++size, item);
        dynamicArray.move(size - 1, index);
    }

    T pop() {
        return pop(size - 1);
    }

    T pop(size_t index) {
        if (index >= size)
            throw indexOutOfRange(index);
        T res = dynamicArray.remove(index);

        recap(--size);

        return res;
    }

    T& getFirst() {
        if (size == 0)
            throw indexOutOfRange(0);

        return dynamicArray[0];
    }

    const T& getFirst() const {
        if (size == 0)
            throw indexOutOfRange(0);

        return dynamicArray[0];
    }

    T& getLast() {
        if (size == 0)
            throw indexOutOfRange(-1);

        return dynamicArray[size - 1];
    }

    const T& getLast() const {
        if (size == 0)
            throw indexOutOfRange(-1);

        return dynamicArray[size - 1];
    }

    T& get(size_t index) {
        if (index >= size)
            throw indexOutOfRange(index);

        return dynamicArray[index];
    }

    const T& get(size_t index) const {
        if (index >= size)
            throw indexOutOfRange(index);

        return dynamicArray[index];
    }

    T& operator[](size_t index) {
        return dynamicArray[index];
    }

    const T& operator[](size_t index) const {
        return dynamicArray[index];
    }

    void set(const T& item, size_t index) {
        if (index >= size)
            throw indexOutOfRange(index);

        dynamicArray[index] = item;
    }

    size_t length() const {
        return size;
    }

    void swap(size_t index1, size_t index2) {
        if (index1 >= size)
            throw indexOutOfRange(index1);
        if (index2 >= size)
            throw indexOutOfRange(index2);

        if (index1 == index2)
            return;

        dynamicArray.swap(index1, index2);
    }

    void move(size_t index1, size_t index2) {
        if (index1 >= size)
            throw indexOutOfRange(index1);
        if (index2 >= size)
            throw indexOutOfRange(index2);

        if (index1 == index2)
            return;

        dynamicArray.move(index1, index2);
    }

    void clear() {
        dynamicArray.resize(0);
        recap(0);
        size = 0;
    }

    iterator begin() {
        return iterator(dynamicArray.begin().operator->());
    }

    iterator end() {
        return iterator(dynamicArray.begin().operator->() + size);
    }

    iterator begin() const {
        return iterator(dynamicArray.begin().operator->());
    }

    iterator end() const {
        return iterator(dynamicArray.begin().operator->() + size);
    }

    bool operator()() const {
        return size;
    }
};

template<typename T>
static std::ostream& operator << (std::ostream& cout, const newArraySequence<T>& sequence) {
    cout << '{';
    for (size_t i = 0; i < sequence.length(); i++) {
        cout << sequence[i];
        if (i != sequence.length() - 1)
            cout << ", ";
    }
    return cout << '}';
}

static std::ostream& operator << (std::ostream& cout, const newArraySequence<char>& sequence) {
    for (auto &i : sequence)
        cout << i;
    return cout;
}

template<typename T>
class myArraySequence: public mySequence<T> {
public:
    static size_t defaultResizeFunc(size_t size, size_t newSize) {
        if (size == 0)
            size = 1;

        while (size <= newSize)
            size *= 2;

        while (size > newSize * 2 && size != 1) {
            size /= 2;
        }

        return size;
    }
private:
    myDynamicArray<T> dynamicArray;
    size_t size = 0;

    size_t (*resizeFunc)(size_t size, size_t newSize) = defaultResizeFunc;

    void resizePrivate(size_t newSize) {
        resizePrivate(newSize, 0, 0);
    }

    void resizePrivate(size_t newSize, long intent) {
        resizePrivate(newSize, intent, 0);
    }

    void resizePrivate(size_t newSize, long intent, size_t index) {
        auto dynSize = resizeFunc(0, newSize);
        size = newSize;
        if (dynamicArray.length() == dynSize && intent == 0 && index == 0) {
            return;
        }
        dynamicArray.resize(dynSize, intent, index);
    }

public:
    using seqIterator = typename mySequence<T>::seqIterator;

    class iterator: public mySequence<T>::seqIterator/*std::iterator<std::bidirectional_iterator_tag, T>*/ { //класс итератора
    private:
        T* item = nullptr;
    public:
        explicit iterator(T* item): item(item) {}

        iterator(const iterator &other): item(other.item) {}

        explicit iterator(const typename myDynamicArray<T>::iterator& other): item(other.item) {}

        iterator& operator = (const iterator &other) {
            item(other.item);
            return *this;
        }

        T& operator*() const {
            return *item;
        }

        T* operator->() const {
            return item;
        }

        bool operator==(const iterator &other) const {
            return item == other.item;
        }

        bool operator!=(const iterator &other) const {
            return item != other.item;
        }

        iterator& operator + (int num) {
            if (num < 0)
                return operator-(-num);

            for (int i = 0; i < num; i++) {
                operator++();
            }
            return *this;
        }

        iterator& operator - (int num) {
            if (num < 0)
                return operator+(-num);

            for (int i = 0; i < num; i++) {
                operator--();
            }
            return *this;
        }

        iterator& operator++() {
            item++;
            return *this;
        }

        iterator operator++(int) {
            T* res = item;
            ++item;
            return iterator(res);
        }

        iterator& operator--() {
            item--;
            return *this;
        }

        iterator operator--(int) {
            T* res = item;
            --item;
            return iterator(res);
        }
    }; //Класс итератора

    myArraySequence() = default;

    explicit myArraySequence(T item): size(1), dynamicArray(item) {}

    myArraySequence(const myArraySequence<T>& arraySequence): size(arraySequence.size),
                                                              dynamicArray(arraySequence.dynamicArray),
                                                              resizeFunc(arraySequence.resizeFunc) {}

    explicit myArraySequence(const myDynamicArray<T>& dynamicArray1) {
        dynamicArray = dynamicArray1;
        resizePrivate(dynamicArray.length());
    }

    myArraySequence(T* arr, size_t count) {
        resizePrivate(count);
        for (int i = 0; i < count; i++) {
            dynamicArray[i] = arr[i];
        }
    }
    myArraySequence(std::initializer_list<T> list) {
        dynamicArray = myDynamicArray<T>(list);
        resizePrivate(dynamicArray.length());
    }

    template<typename U>
    explicit myArraySequence(U begin, U end) {
        dynamicArray = myDynamicArray<T>(begin, end);
        resizePrivate(dynamicArray.length());
    }

    explicit myArraySequence(const mySequence<T>& sequence) {
        for (size_t i = 0; i < sequence.length(); i++) {
            append(sequence[i]);
        }
    }

    myArraySequence<T>& operator=(const myArraySequence<T>& arraySequence ) {
        size = arraySequence.size;
        dynamicArray = arraySequence.dynamicArray;
        resizeFunc = arraySequence.resizeFunc;
        return *this;
    }

    T getFirst() const {
        if (size == 0)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray[0];
    }

    T getLast() const {
        if (size == 0)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray[size - 1];
    }

    T get(size_t index) const {
        if (index >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray.get(index);
    }

    T& operator [] (size_t index) {
        if (index >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray[index];
    }

    const T& operator [] (size_t index) const {
        if (index >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        return dynamicArray[index];
    }

    void set(const T& item, size_t index) {
        if (index >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        dynamicArray.set(item, index);
    }

    void swap(size_t index1, size_t index2) {
        if (index1 >= size)
            throw typename mySequence<T>::IndexOutOfRange();
        if (index2 >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        if (index1 == index2)
            return;

        dynamicArray.swap(index1, index2);
    }

    void move(size_t indexFrom, size_t indexTo) {
        dynamicArray.move(indexFrom, indexTo);
    }

    mySequence<T>& getSubSequence(size_t startIndex, size_t endIndex) const {
        if (startIndex >= size)
            throw typename mySequence<T>::IndexOutOfRange();
        if (endIndex > size)
            throw typename mySequence<T>::IndexOutOfRange();

        return *(new myArraySequence<T>(dynamicArray.begin() + startIndex,
                                        dynamicArray.begin() + endIndex)); //Возвращает последовательность через итератор
    }

    size_t length() const {
        return size;
    }

    void append (const T& item) {
        if (size != 0 && &item >= &dynamicArray[0] && &item <= &dynamicArray[dynamicArray.length() - 1]) { //добавляется элемент из массива
            size_t indexItem = ((size_t)&item - (size_t)&dynamicArray[0]) / sizeof(T);
            resizePrivate(size+1);
            dynamicArray[size-1] = dynamicArray[indexItem];
        }
        else {
            resizePrivate(size+1);
            dynamicArray[size-1] = item;
        }
    }

    void prepend(const T& item) {
        if (size != 0 && &item >= &dynamicArray[0] && &item <= &dynamicArray[dynamicArray.length() - 1]) { //добавляется элемент из массива
            size_t indexItem = ((size_t)&item - (size_t)&dynamicArray[0]) / sizeof(T);
            resizePrivate(size+1, 1);
            dynamicArray[0] = dynamicArray[indexItem + 1];
        }
        else {
            resizePrivate(size+1, 1);
            dynamicArray[0] = item;
        }
    }

    void insert (const T& item, size_t index) {
        if (index > size)
            throw typename mySequence<T>::IndexOutOfRange();
        if (index == 0) {
            prepend(item);
            return;
        }
        if (index == size) {
            append(item);
            return;
        }

        if (&item >= &dynamicArray[0] && &item <= &dynamicArray[dynamicArray.length() - 1]) {       //добавляется элемент из массива
            size_t itemIndex = ((size_t)&item - (size_t)&dynamicArray[0]) / sizeof(T);
            resizePrivate(size+1, 1, index);
            if (itemIndex > index)
                itemIndex++;
            dynamicArray[index] = dynamicArray[itemIndex];
        }
        else {
            resizePrivate(size+1, 1, index);
            dynamicArray[index] = item;
        }
//        dynamicArray[index] = item;
    }

    T pop() {
        return pop(size - 1);
    }

    T pop(size_t index) {
        if (index >= size)
            throw typename mySequence<T>::IndexOutOfRange();

        T res = dynamicArray[index];

        resizePrivate(size - 1, -1, index);
        return res;
    }

    myArraySequence<T>& concat(const mySequence<T>& sequence) {
        auto startInd = size;
        resizePrivate(size + sequence.length());
        for (int i = 0; i < sequence.length(); i++, startInd++) {
            dynamicArray[startInd] = sequence[i];
        }
        return *this;
    }

     myArraySequence<T>& reverse() {
        for (int i = 0, j = size - 1; i < size/2; i++, j--) {
            dynamicArray.swap(i, j);
        }
         return *this;
    }

    void clear() {
        dynamicArray.resize(0);
        size = 0;
    }

    bool operator()() const override {
        return size;
    }

    mySequence<T>* copy(bool clear = false) const {
        if (clear)
            return (new myArraySequence<T>());
        return (new myArraySequence<T>(*this));
    }

    iterator begin() const {
        return iterator(dynamicArray.begin().operator->());
    }

    iterator end() const {
        return iterator(dynamicArray.begin().operator->() + size);
    }


};

#endif //BASE_CLASSES_MYARRAYSEQUENCE_H
