#include "Game.h"
#include "Direction.h"
#include "Listener.h"

const int FIELD_SIZE = 4;

int main() {
    Listener listener;
    Field field(FIELD_SIZE);
    Viewer viewer(&field);

    Game game(&viewer, &listener);
    game.run();

}
