#pragma once

#include "Field.h"
#include "Viewer.h"
#include "IListener.h"
#include "Direction.h"

class Game {
    private:
        Field* field;
        Viewer* viewer;
        IListener* listener;
        int score = 0;

    public:
        Game(Viewer* viewer, IListener* listener);
        Game(Field* field, Viewer* viewer, IListener* listener);
        Field* getField();

        void run();
        void start();
        void turn(Direction direction);

        void update();
        void win();
        void loss();

        bool isWin();
        bool isLoss();
};
