#pragma once
#include <vector>
#include <cstdint>

namespace gol
{
    class Cell
    {
    private:
        bool state; // Alive(1) or Dead(0) for now. (Can add more complexity later)
        // Other attributes to add later: Colour, Stats
    public:
        // Create the cell
        Cell(bool status = false);

        // Change cell state
        void setState(bool status);
        bool getState() const;

        // Clear cell.
        void clear();
    };

} // namespace gol
