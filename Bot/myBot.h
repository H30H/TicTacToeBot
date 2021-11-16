//
// Created by Grisha on 22.10.2021.
//

#ifndef TICTACTOEBOT_MYBOT_H
#define TICTACTOEBOT_MYBOT_H

#include "myField.h"
//#include "myTimer.h"
#include <ctime>

class myBot {
    size_t delta;
    bool player;
    char nothing = ' ';
//    myTimer timer;

    struct states {
        //one_side_possible
        static constexpr size_t size1Priority[]{1, 5, 12, 100, 50000};
        //both_size_possible
        static constexpr size_t size2Priority[]{3, 10, 50, 600, 50000};
        //Coefficients for defence and attack
        static constexpr size_t defendCef = 3;
        static constexpr size_t attackCef = 4;

        static constexpr size_t distances[]{100, 20, 12, 7, 2, 0};
    };

    /*
    struct states {
        static const size_t def = 0;

        static const size_t near1 = 0; //10000;
        static const size_t near2 = 0; //3000;
        static const size_t near3 = 0; //200;
        static const size_t near4 = 0; //10;
        static const size_t lineCef = 10;

        static const size_t attackCef = 6;
        static const size_t defendCef = 4;

        static const size_t winTurn = size_t(-1);
        static const size_t defTurn = size_t(-2);
    };

    bool checkUseful(myField& field, long x, long y) const {
        size_t count = 1;
        char playerSymbol = !player ? 'X' : 'O';
        for (int i = 1; i < 5; i++) {
            if (getItem(field, x - i, y) == playerSymbol)
                break;
            if (++count == 5)
                return true;
        }
        for (int i = 1; i < 5; i++) {
            if (getItem(field, x + i, y) == playerSymbol)
                break;
            if (++count == 5)
                return true;
        }

        count = 1;
        for (int i = 1; i < 5; i++) {
            if (getItem(field, x, y - i) == playerSymbol)
                break;
            if (++count == 5)
                return true;
        }
        for (int i = 1; i < 5; i++) {
            if (getItem(field, x, y + i) == playerSymbol)
                break;
            if (++count == 5)
                return true;
        }

        count = 1;
        for (int i = 1; i < 5; i++) {
            if (getItem(field, x - i, y - i) == playerSymbol)
                break;
            if (++count == 5)
                return true;
        }
        for (int i = 1; i < 5; i++) {
            if (getItem(field, x + i, y + i) == playerSymbol)
                break;
            if (++count == 5)
                return true;
        }

        count = 1;
        for (int i = 1; i < 5; i++) {
            if (getItem(field, x - i, y + i) == playerSymbol)
                break;
            if (++count == 5)
                return true;
        }
        for (int i = 1; i < 5; i++) {
            if (getItem(field, x + i, y - i) == playerSymbol)
                break;
            if (++count == 5)
                return true;
        }

        return false;
    }

    static size_t checkDelta(myField& field, long x, long y, long dx, long dy, char symbol, bool one = false) {
        size_t count = 1;
        try {
            for (long i = 1; i < 5; i++) {
                long xCoord = x - dx * i, yCoord = y - dy * i;
                if (xCoord < 0 || yCoord < 0 || xCoord >= field.getWidth() || yCoord >= field.getHeight())
                    continue;
                if (field.getField()[yCoord][xCoord] != symbol)
                    break;
                ++count;
            }
        }
        catch(...) {}
        if (one)
            return count;
        try {
            for (long i = 1; i < 5; i++) {
                long xCoord = x + dx * i, yCoord = y + dy * i;
                if (xCoord < 0 || yCoord < 0 || xCoord >= field.getWidth() || yCoord >= field.getHeight())
                    continue;
                if (field.getField()[yCoord][xCoord] != symbol)
                    break;
                ++count;
            }
        }
        catch(...) {}
        return count;
    }

    bool checkWin(myField& field, long x, long y) const {
        if (x < 0 || y < 0 || x >= field.getWidth() || y >= field.getHeight())
            return false;
        if (field.getField()[y][x] == !player ? 'X' : 'O')
            return false;

        char botSymbol = player ? 'X' : 'O';
        return checkDelta(field, x, y, 1, 0, botSymbol) == 4 ||
                checkDelta(field, x, y, 1, 1, botSymbol) == 4 ||
                checkDelta(field, x, y, 0, 1, botSymbol) == 4 ||
                checkDelta(field, x, y, -1, 1, botSymbol) == 4;
    }

    bool checkLose(myField& field, long x, long y) const {
        if (x < 0 || y < 0 || x >= field.getWidth() || y >= field.getHeight())
            return false;
        if (field.getField()[y][x] == player ? 'X' : 'O')
            return false;

        char playerSymbol = !player ? 'X' : 'O';
        return checkDelta(field, x, y, 1, 0, playerSymbol) == 4 ||
               checkDelta(field, x, y, 1, 1, playerSymbol) == 4 ||
               checkDelta(field, x, y, 0, 1, playerSymbol) == 4 ||
               checkDelta(field, x, y, -1, 1, playerSymbol) == 4;
    }

    static size_t lineFunc(size_t count) {
        size_t res;
        switch (count) {
            default:
                res = 0;
                break;
            case 1:
                res = 10;
                break;
            case 2:
                res = 100;
                break;
            case 3:
                res = 1000;
                break;
            case 4:
                res = 10000;
                break;

        }
        return res;
    }

    size_t lineCef(myField& field, long x, long y, long dx, long dy) const {
        char playerSymbol = !player ? 'X' : 'O';
        char botSymbol = !player ? 'X' : 'O';

        auto defRes = lineFunc(checkDelta(field, x, y, dx, dy, botSymbol, true)) +
                lineFunc(checkDelta(field, x, y, -dx, -dy, playerSymbol, true));
        auto attRes = lineFunc(checkDelta(field, x, y, dx, dy, botSymbol, true)) +
                lineFunc(checkDelta(field, x, y, -dx, -dy, playerSymbol, true));

        return defRes * states::defendCef + attRes * states::attackCef;//res * states::lineCef;
    }

    size_t defaultValue(myField& field, long x, long y) const {
        size_t res = states::def;

        char playerSymbol = !player ? 'X' : 'O';
        char botSymbol = !player ? 'X' : 'O';
        for (int i = 1; i < 0; i++) {
            long dx = x - i, dy = y - i;
            int count = 0;
            for (int j = 0; j < i*2+1; j++) {
                if (getItem(field, dx++, dy) == playerSymbol)
                    count++;
            }
            for (int j = 0; j < i*2+1; j++) {
                if (getItem(field, dx, dy++) == playerSymbol)
                    count++;
            }
            for (int j = 0; j < i*2+1; j++) {
                if (getItem(field, dx--, dy) == playerSymbol)
                    count++;
            }
            for (int j = 0; j < i*2+1; j++) {
                if (getItem(field, dx, dy--) == playerSymbol)
                    count++;
            }

            switch(i) {
                case 1:
                    res += states::near1 * count;
                    break;
                case 2:
                    res += states::near2 * count;
                    break;
                case 3:
                    res += states::near3 * count;
                    break;
                case 4:
                    res += states::near4 * count;
                    break;
                default:
                    break;
            }
        }

        res += lineCef(field, x, y, 1, 0);
        res += lineCef(field, x, y, 1, 1);
        res += lineCef(field, x, y, 0, 1);
        res += lineCef(field, x, y,-1, 1);

        return res;
    }

    template<typename T, typename ...Args>
    static T max(T item1, T item2, Args...args) {
        return max(max(item1, item2), args...);
    }

    template<typename T>
    static T max(T item1, T item2) {
        return item1 > item2 ? item1 : item2;
    }





    size_t getState(myField& field, long x, long y) const {
        if (getItem(field, x, y) != ' ')
            return states::def;

        if (checkWin(field, x, y))
            return states::winTurn;
        if (checkLose(field, x, y))
            return states::defTurn;

        if (!checkUseful(field, x, y))
            return states::def;

        return defaultValue(field, x ,y);
    }
     */

    static char getItem(myField& field, long x, long y) {
        if (x < 0 || y < 0 || x >= field.getWidth() || y >= field.getHeight())
            return ' ';

        return field.getField()[y][x];
    }

    static int countSymbols(myField& field, long x, long y, long dx, long dy, char player, bool& close) {
        int count = 0;
        char c;
        for (int i = 1; i < 5; i++) {
            c = getItem(field, x+dx*i, y+dy*i);
            if (c == player) {
                count++;
                continue;
            }
            else if (c == ' ') {
                if (count)
                    break;
            }
            else {
                close = true;
                break;
            }
        }
        close = false;
        return count;
    }

    static size_t getDiagonalState(myField& field, long x, long y, long dx, long dy, char player) {
        if (getItem(field, x+dx, y+dy) == player && getItem(field, x-dx, y-dy) == player) {
            bool close1 = false, close2 = false;
            int count = countSymbols(field, x, y, dx, dy, player, close1) +
                    countSymbols(field, x, y, -dx, -dy, player, close2);

            if (count >= 4)
                return states::size2Priority[4] * states::distances[0];

            if (close1 && close2)
                return 0;

            if (close1 || close2) {
                return states::size1Priority[count] * states::distances[0];
            }
            else {
                return states::size2Priority[count] * states::distances[0];
            }
        }

        bool close1 = false, close2 = false;
        int spaces1 = countSymbols(field, x, y, dx, dy, ' ', close1);
        int spaces2 = countSymbols(field, x, y, -dx, -dy, ' ', close2);

        int playerSize1 = countSymbols(field, x, y, dx, dy, player, close1);
        int playerSize2 = countSymbols(field, x, y, -dx, -dy, player, close2);

        if (close1 && close2 && spaces1 + spaces2 + playerSize1 + playerSize2 < 4) {
            return 0;
        }

        size_t res = 0;
        if (close1) {
            res += states::size1Priority[playerSize1] * states::distances[spaces1];
        }
        else {
            res += states::size2Priority[playerSize1] * states::distances[spaces1];
        }
        if (close2) {
            res += states::size1Priority[playerSize2] * states::distances[spaces2];
        }
        else {
            res += states::size2Priority[playerSize2] * states::distances[spaces2];
        }
        return res;
    }

    static size_t getStatePlayer(myField& field, long x, long y, char player) {
        return getDiagonalState(field, x, y, 0, 1, player) +
                getDiagonalState(field, x, y, 1, 1, player) +
                getDiagonalState(field, x, y, 1, 0, player) +
                getDiagonalState(field, x, y, 1, -1, player);
    }

    size_t getState(myField& field, long x, long y) const {
        if (getItem(field, x, y) != ' ')
            return 0;
        char playerSymbol = !player ? 'X' : 'O';
        char botSymbol = player ? 'X' : 'O';

        return getStatePlayer(field, x, y, playerSymbol) * states::defendCef +
                getStatePlayer(field, x, y, botSymbol) * states::attackCef;
    }
public:
    myBot(size_t delta = 4, bool player = false): delta(delta), player(player) {
//        timer.reset();
        srand(time(nullptr));
    }

    struct Point {
        long x = 0, y = 0;
        size_t state = 0;
    };

    Point makeTurn(myField& field) const {
        Point point;
//        srand(size_t(timer.time()));

        newArraySequence<Point> points;
        for (long i = -((long) delta); i < (long) (field.getWidth() + delta); i++) {
            for (long j = -((long) delta); j < (long) (field.getHeight() + delta); j++) {
                size_t state = getState(field, i, j);
//                points.append(Point{state, i, j});
                if (points.length() == 0) {
                    points.append(Point{i, j, state});
                }
                else if (state > points[0].state) {
                    points.clear();
                    points.append(Point{i, j, state});
                }
                else if (state == points[0].state) {
                    points.append(Point{i, j, state});
                }
            }
        }

        /*

        if (player) {
            field.player1Turn(point.x, point.y);
        }
        else {
            field.player2Turn(point.x, point.y);
        }
         */
        auto index = rand();
        index %= points.length();
        return points[index%points.length()];
    }
};

#endif //TICTACTOEBOT_MYBOT_H
