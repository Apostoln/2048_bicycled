#pragma once

#include "Direction.h"

class Game;

class IListener {
    public:
        virtual void setTarget(Game* game) = 0;
        virtual void listen() = 0;
        virtual void onPressed(Direction) = 0;
};
