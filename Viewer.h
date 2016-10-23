#pragma once

#include "Field.h"
#include "IViewer.h"

class Viewer: public IViewer {
    protected:
        Field* field;

    public:
        Viewer(Field* field);

        virtual Field* getField();

        virtual void printWin() = 0;
        virtual void printLoss() = 0;
        virtual void show() = 0;
};
