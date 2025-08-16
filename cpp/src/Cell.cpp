#include "gol/Cell.hpp"
#include <algorithm>

namespace gol {

Cell::Cell(bool status):state(status){}

void Cell::setState(bool status) {
    state=status;
}

bool Cell::getState() const {
    return state;
}

} // namespace gol
