#pragma once

#include "ConsoleListener.h"
#include "Game.h"
#include "Direction.h"

ConsoleListener::ConsoleListener(Game* game):
    Listener(game) {}


void ConsoleListener::listen() {
    while(true) {
        onPressed(getDirection());
    }
}

Direction ConsoleListener::getDirection() {
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

void ConsoleListener::onPressed(Direction direction) {
    game->turn(direction);
}


