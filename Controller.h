#pragma once

#include "conio.h"

#include "Game.h"
#include "View.h"
#include "Direction.h"

class Controller {
    private:
        Game* model;
        View* view;

    public:
        Controller(Game* model, View* view):
            model(model), view(view) {}

        void run() {
            model->getField().newTile();
            model->getField().newTile();
            update();
            while(true) {
                Direction direction = control();
                if(direction != Direction::NONE) {
                    auto result = model->getField().shiftTiles(direction);
                    if (std::get<0>(result)) {
                        *model += std::get<1>(result);
                        model->getField().newTile();

                       update();

                        if(model->isWin()) {
                            win();
                            return ;
                        }
                        if(model->isLoss()) {
                            loss();
                            return ;
                        }
                    }
                }
            }
        }

        Direction control() {
            Direction direction = Direction::NONE;
            if(kbhit()) {
                int key = getch();
                key = getch();
                switch(key) {
                    case 72:
                        direction = Direction::UP;
                        break;
                    case 80:
                        direction = Direction::DOWN;
                        break;
                    case 75:
                        direction = Direction::LEFT;
                        break;
                    case 77:
                        direction = Direction::RIGHT;
                        break;
                    default:
                        direction = Direction::NONE;
                        break;
                }
            }
            return direction;
        }

        void update() {
            view->show();
        }

        void win() {
            view->printWin();
        }

        void loss() {
            view->printLoss();
        }


};
