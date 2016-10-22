#pragma once

#include <vector>
#include <tuple>

#include "Direction.h"

using Matrix = std::vector <std::vector<int>>;

class Field {
    private:
        Matrix board;
        size_t size;
        int score = 0;

        static int shiftVector(std::vector <int>& vect);
        static Matrix rotateMatrix(Matrix& matrix);

    public:
        Field() = default;
        Field(size_t size);

        Matrix getBoard();
        size_t getSize();
        int getScore();

        void operator += (int num);

        void newTile();
        std::tuple <bool, int> shiftTiles(Direction dir);
};
