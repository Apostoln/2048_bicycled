#pragma once

#include "conio.h"

#include "Direction.h"

class Game;

class Listener {
    private:
        Game* game;

        Direction getDirection();

    public:
        Listener() = default;
        Listener(Game* game);

        void setTarget(Game* game);
        void listen();

        void onPressed(Direction direction);
};
