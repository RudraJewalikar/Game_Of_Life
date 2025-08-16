#pragma once
#include <vector>
#include <cstdint>

namespace gol
{
    // Conway's Game of Life grid with optional edge wrapping.
    // Default rules: B3/S23 via step()'s defaults.
    class Grid
    {
    public:
        // Construct a width x height grid. wrap=true makes edges toroidal.
        Grid(int width, int height, bool wrap = true);

        // Dimensions
        int width() const noexcept;
        int height() const noexcept;

        // Mutate/query a single cell (handle out-of-bounds via neighbourCount).
        void setCell(int x, int y, bool alive);
        bool getCell(int x, int y) const;

        // Clear all cells.
        void clear();

        // Advance one generation.
        // birthRule: number of neighbors to birth a dead cell (default 3).
        // surviveMask: bitmask where bits set at positions 2 and/or 3 keep a live cell alive (default S23).
        void step(const int birthRule = 3, const uint16_t surviveMask = (1u << 2) | (1u << 3));

        // Toggle wrapping if needed.
        void setWrap(bool wrap) noexcept;

    private:
        int W, H;
        bool wrapEdges;
        std::vector<uint8_t> curr, next;

        // Index helpers
        inline int idx(int x, int y) const noexcept { return y * W + x; }

        // Neighbor helpers (definitions in .cpp)
        int neighborCount(int x, int y) const;
        int nx(int x) const noexcept;
        int ny(int y) const noexcept;
    };

} // namespace gol
