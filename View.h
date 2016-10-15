#pragma once

#include <iostream>
#include <iomanip>

#include "Game.h"

class View {
    private:
        Game* gameModel;
    public:
        View(Game* game):
            gameModel(game) {}

        void printWin() {
            system("cls");
            std::cout << "You are won with score " << gameModel->getScore() << std::endl;
        }

        void printLoss() {
            system("cls");
            std::cout << "You are lost with score " << gameModel->getScore() << std::endl;
        }

        void show() {
            system("cls");
            for(auto i : gameModel->getField().getBoard()) {
                for(auto j : i) {
                    std::cout << std::setw(4) << j << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            std::cout << "Score: " << gameModel->getScore() << std::endl;
        }
};
