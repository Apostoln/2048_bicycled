#pragma once

#include "Field.h"
#include "Viewable.h"

class Viewer: public Viewable {
    protected:
        Field* field;

    public:
        Viewer(Field* field);

        virtual Field* getField();

        virtual void printWin() = 0;
        virtual void printLoss() = 0;
        virtual void show() = 0;
};
