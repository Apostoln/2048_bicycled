#pragma once

class Field;

class Viewable {
    public:
        virtual void printWin() = 0;
        virtual void printLoss() = 0;
        virtual void show() = 0;
};
