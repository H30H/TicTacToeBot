//
// Created by Grisha on 10.07.2021.
//

#ifndef BASE_CLASSES_MYSEQUENCE_H
#define BASE_CLASSES_MYSEQUENCE_H

#include <iostream>

template<typename T>
class mySequence {
public:
    class IndexOutOfRange{
    public:
        size_t length = 0;
        size_t index = 0;
        IndexOutOfRange(size_t length, size_t index): length(length), index(index) {};
        IndexOutOfRange() = default;
    };

    mySequence<T>& operator = (const mySequence<T>& sequence) {
        if (length() < sequence.length()) {
            size_t i = 0;
            for (i; i < length(); i++) {
                operator[](i) = sequence[i];
            }
            for (i; i < sequence.length(); i++) {
                append(sequence[i]);
            }
        }
        else {
            size_t i = 0;
            for (i; i < sequence.length(); i++) {
                operator[](i) = sequence[i];
            }
            while (i != length())
                pop();
        }
        return *this;
    }

    using seqIterator = std::iterator<std::bidirectional_iterator_tag, T>;

    virtual T getFirst() const = 0;
    virtual T getLast() const = 0;
    virtual T get(size_t index) const = 0;

    virtual T& operator [] (size_t index) = 0;
    virtual const T& operator [] (size_t index) const = 0;

    virtual void set(const T& item, size_t index) = 0;
    virtual void swap(size_t index1, size_t index2) = 0;
    virtual void move(size_t indexFrom, size_t indexTo) = 0;

    virtual mySequence<T>& getSubSequence(
            size_t startIndex, size_t endIndex) const = 0;

    virtual size_t length() const = 0;

    virtual void append (const T& item) = 0;
    virtual void prepend(const T& item) = 0;
    virtual void insert (const T& item, size_t index) = 0;
    virtual T pop() = 0;
    virtual T pop(size_t index) = 0;

    virtual mySequence<T>& concat(const mySequence<T>& sequence) = 0;
    virtual mySequence<T>& reverse() = 0;
    virtual void clear() = 0;

    virtual mySequence<T>* copy(bool clear = false) const = 0;
    virtual bool operator()() const = 0;
};

template<typename T>
static std::ostream& operator << (std::ostream& cout, const mySequence<T>& sequence) {
    cout << "{";
    for (size_t i = 0; i < sequence.length(); i++) {
        cout << sequence[i];
        if (i == sequence.length() - 1)
            break;

        cout << ", ";
    }
    return cout << "}";
}

static std::ostream& operator << (std::ostream& cout, const mySequence<char>& sequence) {
    for (size_t i = 0; i < sequence.length(); i++) {
        cout << sequence[i];
    }
    return cout;
}

#endif //BASE_CLASSES_MYSEQUENCE_H
