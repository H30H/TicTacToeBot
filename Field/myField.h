//
// Created by Grisha on 06.10.2021.
//

#ifndef TICTACTOEBOT_MYFIELD_H
#define TICTACTOEBOT_MYFIELD_H

#include "myArraySequence.h"

class myField {
    newArraySequence<newArraySequence<char>> fieldMatrix;

    size_t delta;
    char pl1, pl2, nt;
public:

    void prependRow() {
        fieldMatrix.prepend(newArraySequence<char>());
        auto &row = fieldMatrix[0];

        if (fieldMatrix.length() > 1)
            for (size_t i = 0; i < fieldMatrix[1].length(); i++) {
                row.append(nt);
        }
    }

    void prependColumn() {
        for (auto &i : fieldMatrix) {
            i.prepend(nt);
        }
    }

    void appendRow() {
        fieldMatrix.append(newArraySequence<char>());
        auto &row = fieldMatrix[fieldMatrix.length() - 1];

        if (fieldMatrix.length() > 1)
            for (size_t i = 0; i < fieldMatrix[0].length(); i++) {
                row.append(nt);
            }
    }

    void appendColumn() {
        for (auto &i : fieldMatrix) {
            i.append(nt);
        }
    }

    void resizeField(size_t x, size_t y) {
        while(x < delta) {
            x += 1;
            prependColumn();
        }

        while (y < delta) {
            y += 1;
            prependRow();
        }

        while (x + delta >= fieldMatrix[0].length()) {
            appendColumn();
        }

        while (y + delta >= fieldMatrix.length()) {
            appendRow();
        }
    }

    struct coordsError: std::exception {
        size_t x, y;

        coordsError(size_t x, size_t y): x(x), y(y) {}

        const char * what() const noexcept override {
            return "This point is placed outside the field!";
        }
    };

    myField(size_t delta = 0, char player1 = 'X', char player2 = 'O', char nothing = ' '):
            delta(delta), pl1(player1), pl2(player2), nt(nothing) {
        for (size_t i = 0; i < delta * 2 + 1; i++) {
            appendRow();
            appendColumn();
        }
    }

    [[nodiscard]] const newArraySequence<newArraySequence<char>>& getField() const {
        return fieldMatrix;
    }

    void player1Turn(size_t x, size_t y) {
        if (y >= getHeight() || x >= getWidth())
            throw coordsError(x, y);

        if (fieldMatrix[y][x] != ' ')
            throw coordsError(x, y);

        fieldMatrix[y][x] = pl1;
    }

    void player2Turn(size_t x, size_t y) {
        if (y >= getHeight() || x >= getWidth())
            throw coordsError(x, y);

        if (fieldMatrix[y][x] != ' ')
            throw coordsError(x, y);

        fieldMatrix[y][x] = pl2;
    }

    void clear() {
//        fieldMatrix = newArraySequence<newArraySequence<char>>();
        fieldMatrix.clear();
    }

    [[nodiscard]] size_t getHeight() const {
        return fieldMatrix.length();
    }

    [[nodiscard]] size_t getWidth() const {
        if (fieldMatrix.length() == 0)
            return 0;
        return fieldMatrix[0].length();
    }


};


#endif //TICTACTOEBOT_MYFIELD_H
