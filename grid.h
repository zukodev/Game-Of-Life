/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
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

#include <vector>
#include <exception>
#include <iostream>
#include <sstream>

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD  = ' ',
    ALIVE = '#'
};

/**
 * Custom exception class build as an extension of std::exception. Stores
 * the invalid coordinate, and also the grid dimensions to enable analysis of 
 * how the coordinate is invalid.
 */
class coord_exception : public std::exception 
{
private:

    unsigned int m_x, m_y, m_grid_width, m_grid_height;

public:
    coord_exception(unsigned int x, unsigned int y, unsigned int grid_width, unsigned int grid_height)
        : std::exception(), m_x(x), m_y(y), m_grid_width(grid_width), m_grid_height(grid_height) {}
    
    virtual void describe(std::ostream &os) const 
    {
        os << "Coordinate Exception : " << "x: " << m_x 
           << ", y:  " << m_y 
           << ", grid width: " << m_grid_width
           << ", grid height: " << m_grid_height;
    }
    
    unsigned int get_x() const { return m_x; }
    unsigned int get_y() const { return m_y; }
    unsigned int get_grid_width() const { return m_grid_width;}
    unsigned int get_grid_height() const { return m_grid_height;}
};



/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {

private:
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.
    
    unsigned int m_width, m_height;

    std::vector<std::vector<Cell> > m_body;     //Vector of a vector of cells. (Mimics a 2d array.)

    unsigned int const get_index(unsigned int x, unsigned int y);

public: 

    Grid();
    explicit Grid(unsigned int const & sqaure_size);
    Grid(unsigned int const & width, unsigned int const & height);

    Cell & operator()(unsigned int x, unsigned int y);
    Cell const & operator()(unsigned int x, unsigned int y) const;
    friend std::ostream & operator << (std::ostream & output, const Grid & grid);

    Cell get(unsigned x, unsigned y) const;
    void set(unsigned x, unsigned y, Cell value);

    unsigned int const & get_width() const; 
    unsigned int const & get_height() const; 

    unsigned int const get_alive_cells() const;
    unsigned int const get_dead_cells() const;
    unsigned int const get_total_cells() const;

    void resize(unsigned int const & square_size);
    void resize(unsigned int const & new_width, unsigned int const & new_height);

    Grid crop(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1) const;
    void merge(Grid const & other, unsigned int x0, unsigned int y0, bool alive_only = false);
    Grid rotate(int rotation);
};
