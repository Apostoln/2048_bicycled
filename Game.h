#pragma once

#include "Field.h"
#include "Direction.h"

class Game {
    private:
        Field field;
        int score = 0;

    public:
        Game(size_t size) {
            field = Field(size);
        }

        Field& getField() {
            return field;
        }

        int getScore() {
            return score;
        }

        bool isWin() {
            for(auto i: field.getBoard()) {
                for(auto j: i) {
                    if (2048 == j) {
                        return true;
                    }
                }
            }
            return false;
        }

        bool isLoss() {
            std::vector <Direction> dirs = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
            for(auto dir: dirs) {
                auto temp = field;
                if (std::get<0>(temp.shiftTiles(dir))) {
                    return false;
                }
            }
            return true;
        }

        void operator += (int num) {
            this->score += num;
        }
};
