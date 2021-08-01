/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 963653
 * @date April, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the class.
// #include ...

#include "grid.h"


/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World {
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.

private:

    Grid m_curr_buff;
    Grid m_next_buff;

    unsigned int count_neighbours(unsigned int x, unsigned int y, bool toroidal = false);

public:

    World();
    explicit World(unsigned int const & square_size);
    World(unsigned int const & width, unsigned int const & height);
    explicit World(Grid const & initial_state);
    
    unsigned int const & get_width() const; 
    unsigned int const & get_height() const; 
    
    Grid & get_state();

    unsigned int const get_total_cells() const;
    unsigned int const get_alive_cells() const;
    unsigned int const get_dead_cells() const;
    
    void resize(unsigned int square_size);
    void resize(unsigned int const & new_width, unsigned int const & new_height);

    void step(bool toroidal = false);

    void advance(unsigned int steps, bool toroidal = false); 
};