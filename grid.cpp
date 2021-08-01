/**
 * Implements a class representing a 2d grid of cells.
 *      - New cells are initialized to Cell::DEAD.
 *      - Grids can be resized while retaining their contents in the remaining area.
 *      - Grids can be rotated, cropped, and merged together.
 *      - Grids can return counts of the alive and dead cells.
 *      - Grids can be serialized directly to an ascii std::ostream.
 *
 * You are encouraged to use STL container types as an underlying storage mechanism for the grid cells.
 *
 * @author 963653
 * @date April, 2020
 */
#include "grid.h"

// Include the minimal number of headers needed to support your implementation.
// #include ...
#include <stdexcept>

/**
 * Grid::Grid()
 *
 * Construct an empty grid of size 0x0.
 * Can be implemented by calling Grid::Grid(square_size) constructor.
 *
 * @example
 *
 *      // Make a 0x0 empty grid
 *      Grid grid;
 *
 */
Grid::Grid()
    : Grid(0)
{

}


/**
 * Grid::Grid(square_size)
 *
 * Construct a grid with the desired size filled with dead cells.
 * Single value constructors should be marked "explicit" to prevent them
 * being used to implicitly cast ints to grids on construction.
 *
 * Can be implemented by calling Grid::Grid(width, height) constructor.
 *
 * @example
 *
 *      // Make a 16x16 grid
 *      Grid x(16);
 *
 *      // Also make a 16x16 grid
 *      Grid y = Grid(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      Grid z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the grid.
 */
Grid::Grid(unsigned int const & sqaure_size)
    : Grid(sqaure_size, sqaure_size)
{
}


/**
 * Grid::Grid(width, height)
 *
 * Construct a grid with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 * @param width
 *      The width of the grid.
 *
 * @param height
 *      The height of the grid.
 */
Grid::Grid(unsigned int const & width, unsigned int const & height)
    : m_width(width), m_height(height)
{

    for(unsigned int i = 0; i < height; i++)
    {      
        m_body.push_back(std::vector<Cell>());

        for(unsigned int j = 0; j < width; j++)
        {
            m_body[i].push_back(Cell::DEAD);    //Insert default dead cell.
        }   
    }
}


/**
 * Grid::get_width()
 *
 * Gets the current width of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the width of the grid to the console
 *      std::cout << grid.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the width of the grid to the console
 *      std::cout << read_only_grid.get_width() << std::endl;
 *
 * @return
 *      The width of the grid.
 */
 unsigned int const & Grid::get_width() const { return m_width; }


/**
 * Grid::get_height()
 *
 * Gets the current height of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the height of the grid to the console
 *      std::cout << grid.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the height of the grid to the console
 *      std::cout << read_only_grid.get_height() << std::endl;
 *
 * @return
 *      The height of the grid.
 */
 unsigned int const & Grid::get_height() const { return m_height; }


/**
 * Grid::get_total_cells()
 *
 * Gets the total number of cells in the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << grid.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << read_only_grid.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
unsigned int const Grid::get_total_cells() const { return m_width * m_height; }


/**
 * Grid::get_alive_cells()
 *
 * Counts how many cells in the grid are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of alive cells to the console
 *      std::cout << grid.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of alive cells to the console
 *      std::cout << read_only_grid.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
unsigned int const Grid::get_alive_cells() const 
{
    unsigned int count = 0;

    for(unsigned int i = 0; i < m_height; i++)
    {
        for(unsigned int j = 0; j < m_width; j++)
        {
            if(m_body[i][j] == Cell::ALIVE)
            {
                count++;
            }
        }
    }
    return count;
}



/**
 * Grid::get_dead_cells()
 *
 * Counts how many cells in the grid are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of dead cells to the console
 *      std::cout << grid.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of dead cells to the console
 *      std::cout << read_only_grid.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
unsigned int const Grid::get_dead_cells() const 
{
    unsigned int count = 0;

    for(unsigned int i = 0; i < m_height; i++)
    {
        for(unsigned int j = 0; j < m_width; j++)
        {
            if(m_body[i][j] == Cell::DEAD)
            {
                count++;
            }
        }
    }
    return count;
}


/**
 * Grid::resize(square_size)
 *
 * Resize the current grid to a new width and height that are equal. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 8x8
 *      grid.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */
void Grid::resize(unsigned int const & square_size)
{
    Grid::resize(square_size, square_size);
}


/**
 * Grid::resize(width, height)
 *
 * Resize the current grid to a new width and height. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 2x8
 *      grid.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */
void Grid::resize(unsigned int const & new_width, unsigned int const & new_height)
{    
    //If the new width is less than the current width, pop a Vector of Cells off the main Vector. 
    if(new_height < m_height)
    {  
        for(unsigned int i = 0; i < (m_height - new_height) ;i++)
            m_body.pop_back();
    }
    else    //If the new width is greater, append the difference.
    {
        for(unsigned int i = m_height; i < new_height;i++)
        {
            m_body.push_back(std::vector<Cell>());  //Push back rows.
            for(unsigned int j = 0; j < new_height; j++)
            {
                    m_body[i].push_back(Cell::DEAD);    //Insert default dead cell.
            }
        }
    }

    this->m_height = new_height;

    //If the new width is less than the current width, pop off the necessary amount of Vector of Cells from the main Vector. 
    if(new_width < m_width)
    {  
        for(unsigned int i = 0; i < new_height; i++)
        {
            for(unsigned int j = 0; j < (m_width - new_width); j++)
                m_body[i].pop_back();
        }
    }
    else
    {
        for(unsigned int i = 0; i < new_height; i++)
        {
            for(unsigned int j = m_width; j < new_width; j++)
                m_body[i].push_back(Cell::DEAD);
        }

    }

    this->m_width = new_width;  
}

/**
 * Grid::get_index(x, y)
 *
 * Private helper function to determine the 1d index of a 2d coordinate.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      The 1d offset from the start of the data array where the desired cell is located.
 */ 
unsigned int const Grid::get_index(unsigned int x, unsigned int y) { 
   
    return (m_width * y) + x;
}


/**
 * Grid::get(x, y)
 *
 * Returns the value of the cell at the desired coordinate.
 * Specifically this function should return a cell value, not a reference to a cell.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Read the cell at coordinate (1, 2)
 *      Cell cell = grid.get(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @return
 *      The value of the desired cell. Should only be Grid::ALIVE or Grid::DEAD.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell Grid::get(unsigned x, unsigned y) const
{

    if((x < m_width) && (y < m_height))
    {
        return this->operator()(x,y);
    }
    else 
    {
        throw coord_exception(x, y , m_width, m_height);
    }
}


/**
 * Grid::set(x, y, value)
 *
 * Overwrites the value at the desired coordinate.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Assign to a cell at coordinate (1, 2)
 *      grid.set(1, 2, Cell::ALIVE);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @param value
 *      The value to be written to the selected cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
void Grid::set(unsigned x, unsigned y, Cell value) 
{
    if((x < m_width) && (y < m_height))
    {
        this->operator()(x,y) = value;
    }
    else 
    {
        throw coord_exception(x, y , m_width, m_height);
    }
}



/**
 * Grid::operator()(x, y)
 *
 * Gets a modifiable reference to the value at the desired coordinate.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = grid(1, 2);
 *
 *      // Directly assign to a cell at coordinate (1, 2)
 *      grid(1, 2) = Cell::ALIVE;
 *
 *      // Extract a reference to an individual cell to avoid calculating it's
 *      // 1d index multiple times if you need to access the cell more than once.
 *      Cell &cell_reference = grid(1, 2);
 *      cell_reference = Cell::DEAD;
 *      cell_reference = Cell::ALIVE;
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A modifiable reference to the desired cell.
 *
 * @throws
 *      std::runtime_error or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell & Grid::operator()(unsigned int x, unsigned int y)
{
    if((x < m_width) && (y < m_height))
    {
        return m_body[y][x];;
    }
    else 
    {
        throw coord_exception(x, y , m_width, m_height);
    }
}


/**
 * Grid::operator()(x, y)
 *
 * Gets a read-only reference to the value at the desired coordinate.
 * The operator should be callable from a constant context.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Constant reference to a grid (does not make a copy)
 *      const Grid &read_only_grid = grid;
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = read_only_grid(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A read-only reference to the desired cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell const & Grid::operator()(unsigned int x, unsigned int y) const 
{
    if((x < m_width) && (y < m_height))
    {
        return m_body[y][x];
    }
    else 
    {
        throw coord_exception(x, y , m_width, m_height);
    };
}


/**
 * Grid::crop(x0, y0, x1, y1)
 *
 * Extract a sub-grid from a Grid.
 * The cropped grid spans the range [x0, x1) by [y0, y1) in the original grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid y(4, 4);
 *
 *      // Crop the centre 2x2 in y, trimming a 1 cell border off all sides
 *      Grid x = y.crop(x, 1, 1, 3, 3);
 *
 * @param x0
 *      Left coordinate of the crop window on x-axis.
 *
 * @param y0
 *      Top coordinate of the crop window on y-axis.
 *
 * @param x1
 *      Right coordinate of the crop window on x-axis (1 greater than the largest index).
 *
 * @param y1
 *      Bottom coordinate of the crop window on y-axis (1 greater than the largest index).
 *
 * @return
 *      A new grid of the cropped size containing the values extracted from the original grid.
 *
 * @throws
 *      std::exception or sub-class if x0,y0 or x1,y1 are not valid coordinates within the grid
 *      or if the crop window has a negative size.
 */
Grid Grid::crop(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1) const
{

    //If x0 or y0 are smaller than grids bounds, then throw an error.
    if(x0 < 0 || y0 <0)
    {
        throw coord_exception(x0, y0 , m_width, m_height);
    }
    //If x1 or y1 are larger than the the original grids bounds then throw an error.
    else if((x1  - 1) > m_width || (y1 - 1) > m_height)
    {
        throw coord_exception(x0, y0 , m_width, m_height);
    }
    //If x0 or y0 are bigger than x1 or y1 then throw an error.
    else if(x0 > (x1-1) || y0 > (y1-1))
    {
        throw std::out_of_range("Illegal Coordinates provided");
    }
    else
    {
        Grid newGrid = Grid(x1-x0, y1-y0);  
        for(unsigned int y = y0, i = 0; y < y1 && i < newGrid.get_height(); y++, i++)
        {
            for(unsigned int x = x0, j = 0; x < x1 && j < newGrid.get_width(); x++, j++)
            {
                newGrid.set(j, i, this->get(x,y));
            }
        }
        return newGrid;
    }
}


/**
 * Grid::merge(other, x0, y0, alive_only = false)
 *
 * Merge two grids together by overlaying the other on the current grid at the desired location.
 * By default merging overwrites all cells within the merge reason to be the value from the other grid.
 *
 * Conditionally if alive_only = true perform the merge such that only alive cells are updated.
 *      - If a cell is originally dead it can be updated to be alive from the merge.
 *      - If a cell is originally alive it cannot be updated to be dead from the merge.
 *
 * @example
 *
 *      // Make two grids
 *      Grid x(2, 2), y(4, 4);
 *
 *      // Overlay x as the upper left 2x2 in y
 *      y.merge(x, 0, 0);
 *
 *      // Overlay x as the bottom right 2x2 in y, reading only alive cells from x
 *      y.merge(x, 2, 2, true);
 *
 * @param other
 *      The other grid to merge into the current grid.
 *
 * @param x0
 *      The x coordinate of where to place the top left corner of the other grid.
 *
 * @param y0
 *      The y coordinate of where to place the top left corner of the other grid.
 *
 * @param alive_only
 *      Optional parameter. If true then merging only sets alive cells to alive but does not explicitly set
 *      dead cells, allowing whatever value was already there to persist. Defaults to false.
 *
 * @throws
 *      std::exception or sub-class if the other grid being placed does not fit within the bounds of the current grid.
 */
void Grid::merge(Grid const & other, unsigned int x0, unsigned int y0, bool alive_only)
{
    //In the case x or y are out of bounds throw an error.
    if(x0 < 0 || x0 > this->m_width || y0 < 0 || y0 > this->m_height)
    {
        throw coord_exception(x0, y0 , m_width, m_height);
    }
    //In the case that the grid does not fit on the original grid, throw an error.
    else if((x0 + other.m_width) > this->m_width || y0 + other.m_height > this->m_height)
    {
        throw std::out_of_range("Grid too large to merge.");
    }
    else
    {
        if(alive_only)
        {
            for(unsigned int i = 0; i < other.m_width; i++)
            {
                for(unsigned int j = 0; j < other.m_height; j++)
                {
                    if(other.get(i,j) == Cell::ALIVE)
                    {
                        this->set(x0 + i, y0 + j, other.get(i,j));
                    }
                }
            }
        }
        else
        {
            for(unsigned int i = 0; i < other.m_width; i++)
            {
                for(unsigned int j = 0; j < other.m_height; j++)
                {
                    this->set(x0 + i, y0 + j, other.get(i,j));
                }
            }
        }
    }
}

/**
 * Grid::rotate(rotation)
 *
 * Create a copy of the grid that is rotated by a multiple of 90 degrees.
 * The rotation can be any integer, positive, negative, or 0.
 * The function should take the same amount of time to execute for any valid integer input.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a 1x3 grid
 *      Grid x(1,3);
 *
 *      // y is size 3x1
 *      Grid y = x.rotate(1);
 *
 * @param rotation
 *      An positive or negative integer to rotate by in 90 intervals.
 *
 * @return
 *      Returns a copy of the grid that has been rotated.
 */
Grid Grid::rotate(int rotation)
{
    int turns = (4 * abs(rotation) + rotation) % 4;  

    switch(turns)
    {
        case 0:
        {
            Grid temp = *this;

            std::cout << "" << std::endl;

            return temp;
        }
        case 1: 
        {
            unsigned int new_width = m_height;
            unsigned int new_height = m_width;

            Grid temp(new_width, new_height); 

            for (unsigned int i = 0; i < new_height; i++) 
            {
                for (unsigned int j = 0; j < new_width; j++) 
                {
                    temp.m_body[i][j] = this->m_body[new_width - j - 1][i];
                }
            }

            return temp;
        }
        case 2: 
        {
            unsigned int new_width = m_width;
            unsigned int new_height = m_height;

            Grid temp(new_width, new_height); 

            for (unsigned int i = 0; i < new_height; i++) 
            {
                for (unsigned int j = 0; j < new_width; j++) 
                {
                    temp.m_body[i][j] = this->m_body[new_height - i - 1][new_width - j - 1];
                }
            }
            
            return temp;
        }
        case 3: 
        {
            unsigned int new_width = m_height;
            unsigned int new_height = m_width;

            Grid temp(new_width, new_height); 

            for (unsigned int i = 0; i < new_height; i++) 
            {
                for (unsigned int j = 0; j < new_width; j++) 
                {
                    temp.m_body[i][j] = this->m_body[j][new_height - i - 1];
                }
            }   

            return temp;
        }
        default:
        {   
            //In default case, return unrotated original. (Shouldnt occur.)
            Grid temp = *this;

            return temp;
        }
    }
}


/**
 * operator<<(output_stream, grid)
 *
 * Serializes a grid to an ascii output stream.
 * The grid is printed wrapped in a border of - (dash), | (pipe), and + (plus) characters.
 * Alive cells are shown as # (hash) characters, dead cells with ' ' (space) characters.
 *
 * The function should be callable on a constant Grid.
 *
 * @example
 *
 *      // Make a 3x3 grid with a single alive cell
 *      Grid grid(3);
 *      grid(1, 1) = Cell::ALIVE;
 *
 *      // Print the grid to the console
 *      std::cout << grid << std::endl;
 *
 *      // The grid is printed with a border of + - and |
 *
 *      +---+
 *      |   |
 *      | # |
 *      |   |
 *      +---+
 *
 * @param os
 *      An ascii mode output stream such as std::cout.
 *
 * @param grid
 *      A grid object containing cells to be printed.
 *
 * @return
 *      Returns a reference to the output stream to enable operator chaining.
 */
std::ostream & operator <<(std::ostream & output, const Grid & grid)
{

    //Converted to ints and stored as temp variables...
    //instead of casting to int each time a comparison is made between width/height
    //and the loop variables (ints).
    int width = grid.m_width;
    int height = grid.m_height;


    for(int i = -1; i < height + 1; i++)
    {
        for(int j = -1; j < width + 1; j++)
        {
            if(    (i == -1 && j == -1)
                || (i == -1 && j == width) 
                || (i == height && j == -1)  
                || (i == height && j == width))
            {   
                output << "+";
            }
            else if(i == -1 || i == height) 
            {
                output << "-";
            }
            else if(j == -1 || j == width)
            {
                output << "|";
            }
            else 
            {
                output << char(grid.get(j,i));
            }
        }
        output << std::endl;
    }

    return output;

}


