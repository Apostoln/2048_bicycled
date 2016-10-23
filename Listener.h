#pragma once

#include "conio.h"

#include "IListener.h"
#include "Direction.h"
#include "Game.h"

class Listener: public IListener {
    protected:
        Game* game;

    public:
        Listener() = default;
        Listener(Game* game);

        virtual void setTarget(Game* game);
        virtual void listen() = 0;

        virtual void onPressed(Direction direction) = 0;
};
