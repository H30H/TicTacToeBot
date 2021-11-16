//
// Created by Grisha on 27.09.2021.
//

#include "ArraySequenceTest.h"

#define maxSizeAS 1000    // *Максимальный размер последовательности массива
#define maxElement 1000

void myArraySequenceTest(int count, bool print) {
    srand(count);
    Tests::printText("Тестирование ArraySequence.\n", print);
    myArraySequenceTestResize(count, print);
    myArraySequenceTestGetItem(count, print);
    myArraySequenceTestReverse(count, print);
    myArraySequenceTestCopy(count, print);
    myArraySequenceTestSwap(count, print);
}

int getLen(int max) {
    int len;
    do {
        len = rand()%max;
    } while (len == 0);
    return len;
}

int getIndex(int max){
    if (max == 0) return 0;
    return rand()%max;
}

void myArraySequenceTestResize(int count, bool print) {
    int done = 0;
    Tests::printText("\tТестирование изменения размера последовательности\n", {255, 255, 0}, print);

    for (int j = 0; j < count; j++) {
        myArraySequence<int> sequence;
        int len = getLen(maxSizeAS / 3);
        for (int i = 0; i < len; i++) {
            sequence.append(i);
        }
        if (sequence.length() != len)
            continue;

        for (int i = 0; i < len; i++) {
            sequence.prepend(i);
        }

        if (sequence.length() != len*2)
            continue;

        for (int i = 0; i < len; i++) {
            sequence.insert(i, getIndex(sequence.length()));
        }

        if (sequence.length() != len*3)
            continue;

        for (int i = 0; i < len*3; i++) {
            sequence.pop();
        }

        if (sequence.length() != 0)
            continue;

        done++;
    }

    if (!print && done != count)
        throw Tests::testFault(done, count - done);

    myConsole::moveCursorUp();
    myConsole::removeLine();
    if (done == count) {
        Tests::printText("\tТестирование изменения размера последовательности успешно\n", {0, 255, 0}, print);
    }
    else {
        Tests::printText("\tТестирование изменения размера последовательности провалено "
                         "(" + std::to_string(count - done) + " ошибок)\n", {255, 0, 0}, print);
    }
}

void myArraySequenceTestGetItem(int count, bool print) {
    int done = 0;
    int actions = 100;
    Tests::printText("\tТестирование чтения элеметов последовательности\n", {255, 255, 0}, print);

    for (int i = 0; i < count; i+=actions) {
        myArraySequence<int> sequence;
        int len = getLen(maxSizeAS);
        for (int j = 0; j < len; j++) {
            sequence.append(j);
        }
        for (int j = 0; j < actions; j++) {
            if (i + j >= count) break;
            int index = getIndex(maxSizeAS);
            try {
                if (sequence[index] == index)
                    done++;
            }
            catch (myArraySequence<int>::IndexOutOfRange err) {
                if (index >= len)
                    done++;
            }
        }
    }
    if (!print && done != count)
        throw Tests::testFault(done, count - done);

    myConsole::moveCursorUp();
    myConsole::removeLine();
    if (done == count) {
        Tests::printText("\tТестирование чтения элеметов последовательности успешно\n", {0, 255, 0}, print);
    }
    else {
        Tests::printText("\tТестирование чтения элеметов последовательности провалено "
                         "(" + std::to_string(count - done) + " ошибок)\n", {255, 0, 0}, print);
    }
}

void myArraySequenceTestReverse(int count, bool print) {
    int done = 0;

    Tests::printText("\tТестирование разворота последовательности\n", {255, 255, 0}, print);

    for (int i = 0; i < count; i++) {
        myArraySequence<int> sequence;
        int len = getLen(maxSizeAS);
        for (int j = 0; j < len; j++) {
            sequence.append(j);
        }
        auto sequenceRev = sequence;
        sequenceRev.reverse();
        int res = 1;
        for (int j = 0; j < len; j++) {
            if (sequence[j] != sequenceRev[len - j - 1]) {
                res = 0;
                break;
            }
        }
        done += res;
    }
    if (!print && done != count)
        throw Tests::testFault(done, count - done);

    myConsole::moveCursorUp();
    myConsole::removeLine();

    if (done == count) {
        Tests::printText("\tТестирование разворота последовательности успешно\n", {0, 255, 0}, print);
    }
    else {
        Tests::printText("\tТестирование разворота последовательности провалено "
                         "(" + std::to_string(count - done) + " ошибок)\n", {255, 0, 0}, print);
    }
}

void myArraySequenceTestCopy(int count, bool print) {
    int done = 0;

    Tests::printText("\tТестирование копирования последовательности\n", {255, 255, 0}, print);

    for (int i = 0; i < count; i++) {
        myArraySequence<int> sequence;
        int len = getLen(maxSizeAS);
        for (int j = 0; j < len; j++) {
            sequence.append(j);
        }
        auto resSeq = sequence.copy();

        if (resSeq->length() != sequence.length())
            continue;

        int res = 1;
        for (size_t j = 0; j < resSeq->length(); j++) {
            if (resSeq->operator[](j) != sequence[j]) {
                res = 0;
                break;
            }
        }
        done += res;
    }
    if (!print && done != count)
        throw Tests::testFault(done, count - done);

    myConsole::moveCursorUp();
    myConsole::removeLine();

    if (done == count) {
        Tests::printText("\tТестирование копирования последовательности успешно\n", {0, 255, 0}, print);
    }
    else {
        Tests::printText("\tТестирование копирования последовательности провалено "
                         "(" + std::to_string(count - done) + " ошибок)\n", {255, 0, 0}, print);
    }
}

void myArraySequenceTestSwap(int count, bool print) {
    int done = 0;

    Tests::printText("\tТестирование перемещения элементов последовательности\n", {255, 255, 0}, print);

    if (!print && done != count)
        throw Tests::testFault(done, count - done);

    for (int i = 0; i < count; i++) {
        myArraySequence<int> sequence;
        int len = getLen(maxSizeAS);
        for (int j = 0; j < len; j++) {
            sequence.append(getIndex(maxElement));
        }

        size_t ind1 = getIndex(len);
        size_t ind2 = getIndex(len);

        int elem1 = sequence[ind1];
        int elem2 = sequence[ind2];

        sequence.swap(ind1, ind2);

        if (sequence[ind1] != elem2)
            continue;

        if (sequence[ind2] != elem1)
            continue;

        try {
            sequence.swap(0, len + 1);
            continue;
        }
        catch (myArraySequence<int>::IndexOutOfRange) {
            done++;
        }
    }

    myConsole::moveCursorUp();
    myConsole::removeLine();

    if (done == count) {
        Tests::printText("\tТестирование перемещения элементов последовательности успешно\n", {0, 255, 0}, print);
    }
    else {
        Tests::printText("\tТестирование перемещения элементов последовательности провалено "
                         "(" + std::to_string(count - done) + " ошибок)\n", {255, 0, 0}, print);
    }
}