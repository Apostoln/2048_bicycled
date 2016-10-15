#pragma once

#include <vector>
#include <random>
#include <chrono>
#include <tuple>

#include "Direction.h"

using Matrix = std::vector <std::vector<int>>;

class Field {
    private:
        Matrix board;
        size_t size;
        size_t row;
        size_t column;

        static int shiftVector(std::vector <int>& vect) {
            //It may look terrible, but it`s worked.
            int score = 0;
            auto mask = std::vector<bool> (false);
            for(int i = 0; i < vect.size(); i++) {
                if(vect[i] != 0 && i != 0) {
                    int j = i-1;
                    while(j > 0 && vect[j-1] == 0) {
                        j--;
                    }
                    if(vect[j] == 0 && vect[j-1] == vect[i] && mask[j-1] == false) {
                        vect[j-1] *= 2;
                        vect[i] = 0;
                        score += vect[j-1];
                        mask[j-1] = true;
                        mask[i] = false;
                    } else if(vect[j] == 0) {
                        vect[j] = vect[i];
                        vect[i] = 0;
                        mask[j] = mask[i];
                        mask[i] = false;
                    } else if (vect[j] == vect[i] && j!= i) {
                        vect[j] *= 2;
                        vect[i] = 0;
                        score += vect[j];
                    }
                }
            }
            return score;
        }

        static Matrix rotateMatrix(Matrix& matrix) {
            auto result = matrix;
            for(int i = 0; i < matrix.size(); i++) {
                for(int j = 0; j < matrix[0].size(); j++) {
                    result[i][j] = matrix[matrix.size()-j-1][i];
                }
            }
            return result;
        }

    public:
        Field() = default;

        Field(size_t size):
            size(size), row(size), column(size) {
            board = Matrix (size, std:: vector <int>(size, 0));
        }

        Matrix getBoard() {
            return board;
        }

        size_t getSize() {
            return size;
        }

        void newTile() {
            auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            std::mt19937 gen(seed);
            std::uniform_int_distribution<> rowDis(0, row-1 );
            std::uniform_int_distribution<> columnDis(0, column-1);
            std::bernoulli_distribution valueDis(0.5);
            int value = valueDis(gen)? 2 : 4;
            int y = rowDis(gen);
            int x = columnDis(gen);

            for(int i = 0; i < size*size; i++) {
                if (board[y][x] == 0) {
                    board[y][x] = value;
                    break;
                }
                x++;
                if (x >= board[y].size()) {
                    y++;
                    x = 0;
                }
                if (y >= board.size()) {
                    x++;
                    y = 0;
                }
            }
        }

        std::tuple <bool, int> shiftTiles(Direction dir) {
            // Rotate matrix, shift tiles for every row and rerotate back
            // Return a tuple, where first element is a boolean that mean is fields was shiften, and second is a score diff.
            size_t rotating; //amount of rotating for this direction
            switch (dir) {
                case Direction::LEFT:
                    rotating = 0;
                    break;
                case Direction::DOWN:
                    rotating = 1;
                    break;
                case Direction::RIGHT:
                    rotating = 2;
                    break;
                case Direction::UP:
                    rotating = 3;
                    break;
                case Direction::NONE:
                    return std::make_tuple(false, 0);
            }

            int score = 0;

            Matrix temp = board;
            for(int i = 0; i < rotating; i++) {
                temp = rotateMatrix(temp);
            }
            for(auto &i : temp) {
                score += shiftVector(i);
            }
            for(int i = 0; i < (4-rotating); i++) {
                temp = rotateMatrix(temp);
            }

            if(temp != board) {
                board = temp;
                return std::make_tuple(true, score);
            } else {
                return std::make_tuple(false, score);
            }
        }



};
