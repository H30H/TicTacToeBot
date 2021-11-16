#include "menu.h"

int main()
{
    menu::startMenu();
    return 0;
}


























//#include <iostream>

//#include "myField.h"
//#include "mySequence.h"
//#include "menu.h"
//#include "unistd.h"
//#include "stdlib.h"
//#include "curses.h"
//
//using namespace std;
/*
class destruct {
    size_t* deleted = nullptr;

    char* arr1 = nullptr;
public:
    destruct() = default;

    destruct(size_t* created, size_t* destructed): deleted(destructed) {
        (*created)++;
        cout << *created << ": construct\n";
        arr1 = new char[10];
    }

    ~destruct() {
        if (!deleted)
            return;
        (*deleted)++;
        delete[] arr1;
        cout << *deleted << ": destruct\n";
    }
};

template<typename T>
class container {
private:
    T* arr = nullptr;
    size_t size = 0;
    size_t cap = 0;
public:
    container(size_t size, const T& def = T()): size(size) {
        if (!size)
            return;
        arr = reinterpret_cast<T*>(new char[size * sizeof(T)]);
        for (size_t i = 0; i < size; i++) {
            new(arr + i) T(def);
        }
        cap = size;
    }

    container(const container<T>& other): container(other.size) {
        for (int i = 0; i < size; i++) {
            new(arr + i) T(other[i]);
        }
    }

    container& operator = (const container<T>& other) {
        delete[] reinterpret_cast<char*>(arr);
        size = other.size;
        if (!size)
            return *this;
        arr = reinterpret_cast<T*>(new char[size * sizeof(T)]);
        for (size_t i = 0; i < size; i++) {
            new(arr + i) T(other[i]);
        }
        return *this;
    }

    T& operator [] (size_t index) {
        return arr[index];
    }

    const T& operator [] (size_t index) const {
        return arr[index];
    }

    size_t getSize() const {
        return size;
    }

    ~container() {
        for (size_t i = 0; i < size; i++)
            (arr+i)->~T();
        delete[] reinterpret_cast<char*>(arr);
    }
};

template<typename T>
ostream& operator << (ostream& cout, const container<T>& c) {
    cout << '{';
    for (size_t i = 0; i < c.getSize(); i++) {
        cout << c[i];
        if (i != c.getSize() - 1)
            cout << ", ";
    }
    return cout << '}';
}

void getString(basic_istream<char>& stream, std::string& str) {
    char c;
    while (c != '\n') {
        stream.get(c);
        if (c == '\n')
            return;
        if (c == '\0') {
            stream.clear();
            continue;
        }

        str += c;
    }
}
*/
//int main() {

//    string str;
//
//    getString(cin, str);
//    myConsole::moveCursorUp();
//    myConsole::removeLine();
//    cout << str;
//    cin >> str;

//    menu::startMenu();
//    initscr();
//    move(5, 15);
//    printw("%s", "Hello World");
//    refresh();
//    sleep(2);
//    endwin();
//    exit(EXIT_SUCCESS);

//    return 0;
/*
    myField field;

    size_t x, y;
    bool switcher = true;
    while(true) {
        cin >> x >> y;

        if (x == size_t(-1) || y == size_t(-1))
            break;

        if (switcher)
            field.player1Turn(x, y);
        else
            field.player2Turn(x, y);

        switcher = !switcher;

        for (auto &i : field.getField()) {
            cout << i << endl;
        }
    }
    return 0;
    */
//}