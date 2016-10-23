#pragma once

#include "Viewer.h"

class Field;

class ConsoleViewer: public Viewer {
    public:
        ConsoleViewer(Field* field);
        void printWin();
        void printLoss();
        void show();
};
