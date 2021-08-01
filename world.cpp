/**
 * Implements a class representing a 2d grid world for simulating a cellular automaton.
 *      - Worlds can be constructed empty, from a size, or from an existing Grid with an initial state for the world.
 *      - Worlds can be resized.
 *      - Worlds can return counts of the alive and dead cells in the current Grid state.
 *      - Worlds can return their current Grid state.
 *
 *      - A World holds two equally sized Grid objects for the current state and next state.
 *          - These buffers are swapped after each update step.
 *
 *      - Stepping a world forward in time applies the rules of Conway's Game of Life.
 *          - https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *
 *      - Worlds have a private helper function used to count the number of alive cells in a 3x3 neighbours
 *        around a given cell.
 *
 *      - Updating the world state can conditionally be performed using a toroidal topology.
 *          - Moving off the left edge you appear on the right edge and vice versa.
 *          - Moving off the top edge you appear on the bottom edge and vice versa.
 *
 * @author 963653
 * @date April, 2020
 */
#include "world.h"

// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * World::World()
 *
 * Construct an empty world of size 0x0.
 *
 * @example
 *
 *      // Make a 0x0 empty world
 *      World world;
 *
 */
World::World()
    : World(0) 
{

}


/**
 * World::World(square_size)
 *
 * Construct a world with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x16 world
 *      World x(16);
 *
 *      // Also make a 16x16 world
 *      World y = World(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      World z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the world.
 */
World::World(unsigned int const & square_size)
    : World(square_size, square_size)
{

}


/**
 * World::World(width, height)
 *
 * Construct a world with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 world
 *      World world(16, 9);
 *
 * @param width
 *      The width of the world.
 * @param height
 *      The height of the world.
 */
World::World(unsigned int const & width, unsigned int const & height)
        :m_curr_buff(Grid(width, height)) , m_next_buff(Grid(width, height)) 
{

}

/**
 * World::World(initial_state)
 *
 * Construct a world using the size and values of an existing grid.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 *      // Make a world by using a grid as an initial state
 *      World world(grid);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      World bad_world = grid; // All around me are familiar faces...
 *
 * @param initial_state
 *      The state of the constructed world.
 */
World::World(Grid const & initial_state)
    : m_curr_buff(initial_state), m_next_buff(initial_state)
{

}


/**
 * World::get_width()
 *
 * Gets the current width of the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the width of the worlds grid to the console
 *      std::cout << world.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the width of the worlds grid to the console
 *      std::cout << read_only_world.get_width() << std::endl;
 *
 * @return
 *      The width of the world.
 */
unsigned int const & World::get_width() const { return m_curr_buff.get_width(); }


/**
 * World::get_height()
 *
 * Gets the current height of the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the height of the worlds grid to the console
 *      std::cout << world.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the height of the worlds grid to the console
 *      std::cout << read_only_world.get_height() << std::endl;
 *
 * @return
 *      The height of the world.
 */
unsigned int const & World::get_height() const { return m_curr_buff.get_height(); }


/**
 * World::get_total_cells()
 *
 * Gets the total number of cells in the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the total number of cells on the worlds current state grid to the console
 *      std::cout << world.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the total number of cells on the worlds current state grid to the console
 *      std::cout << read_only_world.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
unsigned int const World::get_total_cells() const {  return m_curr_buff.get_total_cells(); }


/**
 * World::get_alive_cells()
 *
 * Counts how many cells in the world are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the number of alive cells in the worlds current state grid to the console
 *      std::cout << world.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the number of alive cells in the worlds current state grid to the console
 *      std::cout << read_only_world.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
unsigned int const World::get_alive_cells() const { return m_curr_buff.get_alive_cells(); }

/**
 * World::get_dead_cells()
 *
 * Counts how many cells in the world are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the number of dead cells in the worlds current state grid to the console
 *      std::cout << world.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the number of dead cells in the worlds current state grid to the console
 *      std::cout << read_only_world.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
unsigned int const World::get_dead_cells() const { return m_curr_buff.get_dead_cells(); }

/**
 * World::get_state()
 *
 * Return a read-only reference to the current state
 * The function should be callable from a constant context.
 * The function should not invoke a copy the current state.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the current state of the world to the console without copy
 *      std::cout << world.get_state() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the current state of the world to the console without copy
 *      std::cout << read_only_world.get_state() << std::endl;
 *
 * @return
 *      A reference to the current state.
 */
Grid & World::get_state() { return m_curr_buff; }

/**
 * World::resize(square_size)
 *
 * Resize the current state grid in to the new square width and height.
 *
 * The content of the current state grid should be preserved within the kept region.
 * The values in the next state grid do not need to be preserved, allowing an easy optimization.
 *
 * @example
 *
 *      // Make a grid
 *      World world(4, 4);
 *
 *      // Resize the world to be 8x8
 *      world.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */
void World::resize(unsigned int square_size)
{
    World::resize(square_size, square_size);
}



/**
 * World::resize(new_width, new_height)
 *
 * Resize the current state grid in to the new width and height.
 *
 * The content of the current state grid should be preserved within the kept region.
 * The values in the next state grid do not need to be preserved, allowing an easy optimization.
 *
 * @example
 *
 *      // Make a grid
 *      World world(4, 4);
 *
 *      // Resize the world to be 2x8
 *      world.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */
void World::resize(unsigned int const & new_width, unsigned int const & new_height)
{

    m_curr_buff.resize(new_width, new_height);
    m_next_buff = Grid(new_width, new_height);
}


/**
 * World::count_neighbours(x, y, toroidal)
 *
 * Private helper function to count the number of alive neighbours of a cell.
 * The function should not be visible from outside the World class.
 *
 * Neighbours are considered within the 3x3 square centred around the cell at x,y in the current state grid.
 * Ignore the centre coordinate, a cell is not its own neighbour.
 * Attempt to keep the logic as simple, expressive, and readable as possible.
 *
 * If toroidal = false then skip any neighbours that would be outside of the grid,
 * this assumes the grid is Cell::DEAD outside its bounds.
 *
 * If toroidal = true then correctly wrap out of bounds coordinates to the opposite side of the grid.
 *
 * This function is in World and not Grid because the 3x3 sized neighbourhood is specific to Conway's Game of Life,
 * while Grid is more generic to any 2D grid based cellular automaton.
 *
 * @param x
 *      The x coordinate of the centre of the neighbourhood.
 *
 * @param y
 *      The y coordinate of the centre of the neighbourhood.
 *
 * @param toroidal
 *      If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom.
 *
 * @return
 *      Returns the number of alive neighbours.
 */
unsigned int World::count_neighbours(unsigned int x, unsigned int y, bool toroidal)
{

    unsigned int count = 0;

    for(int i = 0, neighbour_x = x-1; i < 3; i++, neighbour_x++)
    {
        for(int j = 0, neighbour_y = y-1; j < 3; j++, neighbour_y++)
        {

            if(toroidal)
            {
                //Check x conditions.
                if(neighbour_x < 0)
                {
                    neighbour_x = m_curr_buff.get_width() - 1;
                }
                else if(neighbour_x >= (int)m_curr_buff.get_width())
                {
                    neighbour_x = 0;
                }
                
                //Check y conditions.
                if(neighbour_y < 0)
                {
                    neighbour_y = m_curr_buff.get_height() - 1;
                }
                else if(neighbour_y >= (int)m_curr_buff.get_height())
                {
                    neighbour_y = 0;
                }

                if(m_curr_buff.get(neighbour_x, neighbour_y) == Cell::ALIVE && !(neighbour_x == (int)x &&  neighbour_y == (int)y))
                {
                    count++;
                }

            }
            else
            {
                bool isOutOfBounds = false;

                if(neighbour_x < 0 
                   || neighbour_x >= (int)m_curr_buff.get_width()
                   || neighbour_y < 0
                   || neighbour_y >= (int)m_curr_buff.get_height())
                {
                    isOutOfBounds = true;
                }

                if(!isOutOfBounds)
                {
                    if(m_curr_buff.get(neighbour_x, neighbour_y) == Cell::ALIVE && !(neighbour_x == (int)x &&  neighbour_y == (int)y))
                    {
                     count++;
                    }
                }
            }
        }
    }


    return count;

}

/**
 * World::step(toroidal)
 *
 * Take one step in Conway's Game of Life.
 *
 * Reads from the current state grid and writes to the next state grid. Then swaps the grids.
 * Should be implemented by invoking World::count_neighbours(x, y, toroidal).
 * Swapping the grids should be done in O(1) constant time, and should not invoke a copy.
 * Try and boil the logic down to the fewest and most simple conditional statements.
 *
 * Rules: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *      - Any live cell with fewer than two live neighbours dies, as if by underpopulation.
 *      - Any live cell with two or three live neighbours lives on to the next generation.
 *      - Any live cell with more than three live neighbours dies, as if by overpopulation.
 *      - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 *
 * @param toroidal
 *      Optional parameter. If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom. Defaults to false.
 */
void World::step(bool toroidal)
{
    for(unsigned int i = 0; i < m_curr_buff.get_height(); i++)
    {   
        for(unsigned int j = 0; j < m_curr_buff.get_width(); j++)
        {

            unsigned int num_neighbours = this->count_neighbours(j, i, toroidal);
            
            // - Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            if((m_curr_buff.get(j, i) == Cell::ALIVE) && (num_neighbours < 2))
            {
                m_next_buff.set(j,i, Cell::DEAD);
            }

            // - Any live cell with two or three live neighbours lives on to the next generation.
            else if((m_curr_buff.get(j, i) == Cell::ALIVE)
                    && (num_neighbours == 2 || num_neighbours == 3))
            {
                m_next_buff.set(j, i, Cell::ALIVE);
            }
            // - Any live cell with more than three live neighbours dies, as if by overpopulation.
            else if((m_curr_buff.get(j, i) == Cell::ALIVE) && (num_neighbours > 3))
            {
                m_next_buff.set(j, i, Cell::DEAD);
            }
            // - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
            else if((m_curr_buff.get(j, i) == Cell::DEAD) && (num_neighbours == 3))
            {
                m_next_buff.set(j, i, Cell::ALIVE);
            }
            else
            {
                 m_next_buff.set(j, i, Cell::DEAD);
            }
        }       
    }

    std::swap(m_curr_buff, m_next_buff);

}

/**
 * World::advance(steps, toroidal)
 *
 * Advance multiple steps in the Game of Life.
 * Should be implemented by invoking World::step(toroidal).
 *
 * @param steps
 *      The number of steps to advance the world forward.
 *
 * @param toroidal
 *      Optional parameter. If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom. Defaults to false.
 */
void World::advance(unsigned int steps, bool toroidal)
{
    for(unsigned int i = 0; i < steps; i++)
    {
        step(toroidal);
    }    
}
