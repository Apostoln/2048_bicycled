#pragma once

#include "Viewer.h"

Viewer::Viewer(Field* field):
    field(field) {}


Field* Viewer::getField() {
    return field;
}
