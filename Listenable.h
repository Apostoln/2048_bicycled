#pragma once

#include "Direction.h"

class Game;

class Listenable {
    public:
        virtual ~Listenable() = default;
        virtual void setTarget(Game* game) = 0;
        virtual void listen() = 0;
        virtual void onPressed(Direction) = 0;
};
