#pragma once

#include "Listener.h"
#include "Game.h"
#include "Direction.h"

Listener::Listener(Game* game):
    game(game) {}


void Listener::listen() {
    while(true) {
        onPressed(getDirection());
    }
}

void Listener::setTarget(Game* target) {
    game = target;
}


Direction Listener::getDirection() {
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


void Listener::onStarted() {
    game->start();
}

void Listener::onPressed(Direction direction) {
    game->turn(direction);
}

