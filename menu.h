//
//
// Created by Grisha on 12.10.2021.

#ifndef TICTACTOEBOT_MENU_H
#define TICTACTOEBOT_MENU_H

#include "myField.h"
#include "myConsole.h"
#include "conio.h"
#include "windows.h"
#include "myBot.h"


/*
 * TODO list:
 *  1. cursor positional with arrow keys
 *  2. map updating
 *  3. menu opening on pressing escape
 *
 * DONE list:
 *  1. keys capture with conio.h
 */

class menu {
public:
    static void startMenu() {
//        getKeyCodes();
        menu m;
        m.mainMenu();
    }

    void mainMenu() {
        std::string str;
        getString(std::cin, str);
        myConsole::changeBackgroundColor(defaultBackColor);
        myConsole::changeTextColor(defaultTextColor);
        printBound();
        myConsole::moveCursorDown();
        myConsole::moveCursorRight(2);

        moveRight(columns/2);
        moveDown(rows/2);
        bool stop = false;
        HWND hwnd;
        HideCaret(hwnd);
        while(!stop) {
            switch (getKey()) {
                case keys::UP:
                    moveUp();
                    break;
                case keys::DOWN:
                    moveDown();
                    break;
                case keys::LEFT:
                    moveLeft();
                    break;
                case keys::RIGHT:
                    moveRight();
                    break;
                case keys::CTRL_UP:
                    moveCTRLUp();
                    break;
                case keys::CTRL_DOWN:
                    moveCTRLDown();
                    break;
                case keys::CTRL_LEFT:
                    moveCTRLLeft();
                    break;
                case keys::CTRL_RIGHT:
                    moveCTRLRight();
                    break;
                case keys::ENTER:
                    if (!gameOver)
                        turn();
                    break;
                case keys::ESCAPE:
//                    stop = true;
                    restartGame();
                    break;
            }
        }
//        for (size_t i = 0 ; i < columns; i++) {
//            std::cout << i%10 << ' ';
//        }
        getString(std::cin, str);

    }

    using color = myConsole::color;

    constexpr static const color defaultTextColor = {255, 255, 255};
    constexpr static const color defaultBackColor = {0, 0, 0};
    constexpr static const color winColor{10, 200, 10};
    constexpr static const color chosenTextColor = {255, 255, 255};
    constexpr static const color chosenBackColor = {0, 0, 0};
private:
    static const size_t columns = 80;
    static const size_t rows = 35;

    static const size_t delta = 4;
    myField field;
    bool gameOver = false;
    struct Point {long x, y;};
    newArraySequence<Point> points;

    unsigned cursorX = 0;
    unsigned cursorY = 0;
    bool playerTurn = true;  //true = player1, false = player2
    myBot bot;

    long globalX = 0;
    long globalY = 0;

    void printBound() {
        myConsole::changeBackgroundColor(defaultBackColor);
        myConsole::changeTextColor(defaultTextColor);
        std::cout << "┌─";       //┐└ ┘┌ │ ─
        for (size_t i = 0; i < columns; i++) {
            std::cout << "──";
        }
        std::cout << "┐";
        myConsole::moveCursorLeft();
        myConsole::moveCursorDown();
        for (size_t i = 0; i < rows; i++) {
            std::cout << "│";
            myConsole::moveCursorLeft();
            myConsole::moveCursorDown();
        }
        std::cout << "┘";
        myConsole::moveCursorLeft(columns*2+3);
        std::cout << "└─";
        for (size_t i = 0; i < columns; i++) {
            std::cout << "──";
        }
        myConsole::moveCursorLeft(columns*2+2);
        myConsole::moveCursorUp();
        for (size_t i = 0; i < rows; i++) {
            std::cout << "│";
            myConsole::moveCursorLeft();
            myConsole::moveCursorUp();
        }
    }

    static void getString(std::basic_istream<char>& stream, std::string& str) {
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

    void restartGame() {
//        field = myField();
        field.clear();
        field.appendColumn();
        field.appendRow();
        clearAll();
        moveToXY(columns/2, rows/2);
        gameOver = false;
        points.clear();
        playerTurn = true;
    }

    size_t diagonalCount(long x, long y, int dx, int dy) {
        char c = playerTurn ? 'X' : 'O';
        size_t count = 0;
        for (long i = 0; x - dx * i >= 0 && y - dy * i >= 0; i++) {
            if (x - dx*i == field.getWidth() || y - dy*i == field.getHeight())
                break;
            if (field.getField()[y - i*dy][x - i*dx] != c)
                break;
            count++;
        }
        for (long i = 1; x + dx * i >= 0 && y + dy * i >= 0; i++) {
            if (x + dx*i == field.getWidth() || y + dy*i == field.getHeight())
                break;
            if (field.getField()[y + i*dy][x + i*dx] != c)
                break;
            count++;
        }
        return count;
    }

    template<typename T>
    bool in(T value, T down, T upper) {
        return value >= down && value < upper;
    }

    void getDiagonalPoints(long x, long y, int dx, int dy) {
        if (diagonalCount(x, y, dx, dy) < 5) {
            return;
        }
        gameOver = true;
        char c = playerTurn ? 'X' : 'O';
        auto tmpX = x, tmpY = y;
        for (long i = 0; in<long>(tmpX, 0, field.getWidth()) && in<long>(tmpY, 0, field.getHeight()); i++, tmpX -= dx, tmpY -= dy) {
            if (field.getField()[tmpY][tmpX] != c)
                break;
            points.append(Point{tmpX, tmpY});
        }
        x+=dx, y+=dy;
        for (long i = 0; in<long>(x, 0, field.getWidth()) && in<long>(y, 0, field.getHeight()); i++, x += dx, y += dy) {
            if (field.getField()[y][x] != c)
                break;
            points.append(Point{x, y});
        }
    }

    void checkWin(long x, long y) {
        getDiagonalPoints(x, y, 0, 1);
        getDiagonalPoints(x, y, 1, 1);
        getDiagonalPoints(x, y, 1, 0);
        getDiagonalPoints(x, y, 1, -1);
    }

    struct keys {
        static const int ENTER = 0;
        static const int UP = 1;
        static const int DOWN = 2;
        static const int LEFT = 3;
        static const int RIGHT = 4;
        static const int CTRL_UP = 5;
        static const int CTRL_DOWN = 6;
        static const int CTRL_LEFT = 7;
        static const int CTRL_RIGHT = 8;
        static const int ESCAPE = 9;
        static const int UNKNOWN = 10;
    };

    static void getKeyCodes(bool code = false) {
        while(code) {
            int k = getch();
            std::cout << k << ' ';
            if (!kbhit())
                std::cout << std::endl;
        }
        while(!code) {
            std::cout << getKey() << std::endl;
        }
    }

    static int getKey() {
        int k = getch();
        if (k == 10)
            return keys::ENTER;

        if (k == 27) {
            if (!kbhit())
                return keys::ESCAPE;
            if (getch() == 91) {
                switch (getch()) {
                    default:
                        break;
                    case 49:
                        if (getch() != 59)
                            return keys::UNKNOWN;
                        if (getch() != 53)
                            return keys::UNKNOWN;
                        switch(getch()) {
                            default:
                                break;
                            case 65:
                                return keys::CTRL_UP;
                            case 66:
                                return keys::CTRL_DOWN;
                            case 68:
                                return keys::CTRL_LEFT;
                            case 67:
                                return keys::CTRL_RIGHT;
                        }
                    case 65:
                        return keys::UP;
                    case 66:
                        return keys::DOWN;
                    case 68:
                        return keys::LEFT;
                    case 67:
                        return keys::RIGHT;
                }
            }
        }

        return keys::UNKNOWN;
    }

    void turn() {
        if (field.getWidth() == 1 && field.getHeight() == 1 && playerTurn) {
            field.player1Turn(0, 0);
//            std::cout << 'X';
//            myConsole::moveCursorLeft();
            globalX = 0;
            globalY = 0;
            playerTurn = !playerTurn;
//            checkWin(0, 0);
            botTurn();
            return;
        }

        while(globalX < 0) {
            globalX++;
            field.prependColumn();
        }

        while(globalX >= field.getWidth()) {
            field.appendColumn();
        }

        while(globalY < 0) {
            globalY++;
            field.prependRow();
        }

        while(globalY >= field.getHeight()) {
            field.appendRow();
        }

        try {
            if (playerTurn) {
                field.player1Turn(globalX, globalY);
//                std::cout << 'X';
//                myConsole::moveCursorLeft();
            } else {
                field.player2Turn(globalX, globalY);
//                std::cout << '0';
//                myConsole::moveCursorLeft();
            }
            checkWin(globalX, globalY);
            if (gameOver) {
                updateMap();
                return;
            }
//            bot.makeTurn(field);
            playerTurn = !playerTurn;
            botTurn();
//            updateMap();
        }
        catch(myField::coordsError& err) {
//            return;
        }
    }

    void botTurn() {
        auto point = bot.makeTurn(field);
        while (point.x < 0) {
            field.prependColumn();
            point.x++;
            globalX++;
        }

        while (point.y < 0) {
            field.prependRow();
            point.y++;
            globalY++;
        }

        while (point.x >= field.getWidth()) {
            field.appendColumn();
        }

        while (point.y >= field.getHeight()) {
            field.appendRow();
        }

        if (playerTurn) {
            field.player1Turn(point.x, point.y);
        }
        else {
            field.player2Turn(point.x, point.y);
        }
        checkWin(point.x, point.y);
        playerTurn = !playerTurn;
        updateMap();
    }

    void clearAll() {
        auto tmpX = cursorX, tmpY = cursorY;
        for (int i = 0; i < rows; i++) {
            moveToXY(0, i);
            for (int j = 0; j < columns; j++) {
                std::cout << "  ";
            }
            cursorX = columns;
        }
        moveToXY(tmpX, tmpY);
    }

    void updateMap() {
        if (field.getWidth() == 1 && field.getHeight() == 1 && playerTurn)
            return;

        long fieldXStart = cursorX - globalX;
        long fieldYStart = cursorY - globalY;

        if (fieldXStart > (long) columns || fieldYStart > (long) rows)
            return;

        if (fieldXStart + field.getWidth() < 0 || fieldYStart + field.getHeight() < 0)
            return;

        unsigned printXStart;
        unsigned printYStart;

        unsigned tmpCursorX = cursorX;
        unsigned tmpCursorY = cursorY;

        if (fieldXStart < 0) {
            printXStart = -fieldXStart;
            fieldXStart = 0;
        }
        else
            printXStart = 0;

        if (fieldYStart < 0) {
            printYStart = -fieldYStart;
            fieldYStart = 0;
        }
        else
            printYStart = 0;

        unsigned i1, i2, j1, j2;
        for (i1 = 0; i1 < fieldYStart; i1++) {
            moveToXY(0, i1);
            for (unsigned j = 0; j < columns; j++) {
                std::cout << "  ";
                cursorX++;
            }
        }
        for (i2 = 0; i2 + fieldYStart < rows && i2 + printYStart < field.getHeight(); i2++) {
            moveToXY(0, fieldYStart + i2);

            for (j1 = 0; j1 < fieldXStart; j1++) {
                std::cout << "  ";
                cursorX++;
            }

            for (j2 = 0; j2 + fieldXStart < columns && j2 + printXStart < field.getWidth(); j2++) {
                std::cout << field.getField()[i2 + printYStart][j2 + printXStart] << ' ';
                cursorX++;
            }

            for (unsigned j3 = j1 + j2; j3 < columns; j3++) {
                std::cout << "  ";
                cursorX++;
            }
        }

        for (unsigned i3 = i1 + i2; i3 < rows; i3++) {
            moveToXY(0, i3);
            for (unsigned j = 0; j < columns; j++) {
                std::cout << "  ";
                cursorX++;
            }
        }
        if (!gameOver) {
            moveToXY(tmpCursorX, tmpCursorY);
            return;
        }
        myConsole::changeBackgroundColor(winColor);
        for (const auto &i: points) {
            if (!in<long>(i.x + fieldXStart - printXStart, 0, (long)columns) || !in<long>(i.y + fieldYStart - printYStart, 0, (long)rows))
                continue;
            moveToXY(i.x + fieldXStart - printXStart, i.y + fieldYStart - printYStart);
            std::cout << field.getField()[i.y][i.x];
            myConsole::moveCursorLeft();
        }
        myConsole::changeBackgroundColor(defaultBackColor);
        moveToXY(tmpCursorX, tmpCursorY);
    }

    void moveUp(size_t count=1) {
        if (count == 0)
            return;

        globalY -= count;
        if (cursorY < count + delta) {
            //TODO сделать смещение карты с её полной отрисовкой
            count = cursorY - delta;
            myConsole::moveCursorUp(count);
            updateMap();
            return;
        }

        myConsole::moveCursorUp(count);
        cursorY -= count;
    }

    void moveDown(size_t count=1) {
        if (count == 0)
            return;

        globalY += 1;
        if (cursorY + count + delta >= rows) {
            //TODO сделать смещение карты с её полной отрисовкой
            count = rows - cursorY - delta - 1;
            myConsole::moveCursorDown(count);
            updateMap();
            return;
        }

        myConsole::moveCursorDown(count);
        cursorY += count;
    }

    void moveLeft(size_t count=1) {
        if (count == 0)
            return;

        globalX -= count;
        if (cursorX < count + delta) {
            //TODO сделать смещение карты с её полной отрисовкой
            count = cursorX - delta;
            myConsole::moveCursorLeft(count);
            updateMap();
            return;
        }

        myConsole::moveCursorLeft(count*2);
        cursorX -= count;
    }

    void moveRight(size_t count=1) {
        if (count == 0)
            return;

        globalX += count;
        if (cursorX + count + delta >= columns) {
            //TODO сделать смещение карты с её полной отрисовкой
            count = columns - cursorX - delta - 1;
            myConsole::moveCursorRight(count);
            updateMap();
            return;
        }

        myConsole::moveCursorRight(count*2);
        cursorX += count;
    }

    void moveCTRLUp(size_t count = 1) {
        if (cursorY - delta < count) {
            count = cursorY - delta;
        }
        if (!count)
            return;

        myConsole::moveCursorUp(count);
        cursorY -= count;
        updateMap();
    }

    void moveCTRLDown(size_t count = 1) {
        if (rows - cursorY - delta <= count) {
            count = rows - cursorY - delta - 1;
        }
        if (!count)
            return;

        myConsole::moveCursorDown(count);
        cursorY += count;
        updateMap();
    }

    void moveCTRLLeft(size_t count = 1) {
        if (cursorX - delta < count) {
            count = cursorX - delta;
        }
        if (!count)
            return;

        myConsole::moveCursorLeft(count*2);
        cursorX -= count;
        updateMap();
    }

    void moveCTRLRight(size_t count = 1) {
        if (columns - cursorX - delta <= count) {
            count = columns - cursorX - delta - 1;
        }
        if (!count)
            return;

        myConsole::moveCursorRight(count*2);
        cursorX += count;
        updateMap();
    }

    void moveToXY(unsigned x, unsigned y) {
        if (x >= columns)
            x = columns - 1;
        if (y >= rows)
            y = rows - 1;

        if (x < cursorX) {
            myConsole::moveCursorLeft((cursorX - x) * 2);
//            moveLeft(cursorX - x, false, false);
        }
        else {
            myConsole::moveCursorRight((x - cursorX) * 2);
        }

        if (y < cursorY) {
            myConsole::moveCursorUp((cursorY - y) * 1);
        }
        else {
            myConsole::moveCursorDown((y - cursorY) * 1);
        }

        cursorX = x;
        cursorY = y;
    }
};

#endif //TICTACTOEBOT_MENU_H
