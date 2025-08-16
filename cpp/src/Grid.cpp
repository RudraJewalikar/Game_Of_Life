#include "gol/Grid.hpp"
#include <algorithm>

namespace gol {

Grid::Grid(int width, int height, bool wrap)
    : W(width), H(height), wrapEdges(wrap),
      curr(static_cast<size_t>(W)*H), //dead cell by default
      next(static_cast<size_t>(W)*H) {}

int Grid::width() const noexcept { return W; }
int Grid::height() const noexcept { return H; }

void Grid::setCell(int x, int y, bool alive) {
    if (x < 0 || x >= W || y < 0 || y >= H) return;
    curr[idx(x,y)].setState(alive);
}

bool Grid::getCell(int x, int y) const {
    if (x < 0 || x >= W || y < 0 || y >= H) return false;
    return curr[idx(x,y)].getState();
}

void Grid::clear() {
    std::fill(curr.begin(), curr.end(), new Cell());
}

void Grid::step(const int birthRule, const uint16_t surviveMask) {
    for (int y=0; y<H; ++y) {
        for (int x=0; x<W; ++x) {
            int n = neighborCount(x,y);
            bool alive = curr[idx(x,y)].getState();
            bool nextState = 0;
            if (!alive) {
                nextState = (n == birthRule) ? true : false;
            } else {
                nextState = ((surviveMask >> n) & 1u) ? true : false;
            }
            next[idx(x,y)] = nextState;
        }
    }
    curr.swap(next);
}

void Grid::setWrap(bool wrap) noexcept {
    wrapEdges = wrap;
}

int Grid::nx(int x) const noexcept {
    if (wrapEdges) {
        if (x < 0) return W-1;
        if (x >= W) return 0;
        return x;
    } else {
        if (x < 0) return 0;
        if (x >= W) return W-1;
        return x;
    }
}

int Grid::ny(int y) const noexcept {
    if (wrapEdges) {
        if (y < 0) return H-1;
        if (y >= H) return 0;
        return y;
    } else {
        if (y < 0) return 0;
        if (y >= H) return H-1;
        return y;
    }
}

int Grid::neighborCount(int x, int y) const {
    int sum = 0;
    if (wrapEdges) {
        // Faster path?: avoids repeated bounds checks inside loop.
        // const int xm1 = nx(x-1), xp1 = nx(x+1);
        // const int ym1 = ny(y-1), yp1 = ny(y+1);

        // sum += curr[idx(xm1, ym1)] != 0;
        // sum += curr[idx(x,   ym1)] != 0;
        // sum += curr[idx(xp1, ym1)] != 0;

        // sum += curr[idx(xm1, y  )] != 0;
        // // skip self (x,y)
        // sum += curr[idx(xp1, y  )] != 0;

        // sum += curr[idx(xm1, yp1)] != 0;
        // sum += curr[idx(x,   yp1)] != 0;
        // sum += curr[idx(xp1, yp1)] != 0;

        for (int dy=-1; dy<=1; ++dy) {
            for (int dx=-1; dx<=1; ++dx) {
                if (dx==0 && dy==0) continue;
                int xx = nx(x + dx);
                int yy = ny(y + dy);
                sum += curr[idx(xx,yy)].getState();
            }
        }
    } else {
        // Non-wrapping: clamp and skip out-of-bounds.
        for (int dy=-1; dy<=1; ++dy) {
            for (int dx=-1; dx<=1; ++dx) {
                if (dx==0 && dy==0) continue;
                int xx = x + dx;
                int yy = y + dy;
                if (xx < 0 || xx >= W || yy < 0 || yy >= H) continue;
                sum += curr[idx(xx,yy)].getState();
            }
        }
    }
    return sum;
}

} // namespace gol
