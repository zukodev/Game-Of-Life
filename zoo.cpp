/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 963653
 * @date April, 2020
 */
#include "zoo.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <bitset>
#include <math.h>  
#include <bits/stdc++.h> 

#define BGOL_FILE_GRID_BYTE_CAPACITY 8
#define BGOL_FILE_GRID_BIT_CAPACITY 64
#define BYTE_SIZE 8
#define BYTE_SIZE_DOUBLE 8.0
// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
 Grid Zoo::glider()
 {
    Grid glider(3);

    glider.set(0, 2, Cell::ALIVE);
    glider.set(1, 2, Cell::ALIVE);
    glider.set(2, 2, Cell::ALIVE);
    glider.set(2, 1, Cell::ALIVE);
    glider.set(1, 0, Cell::ALIVE);

    return glider;
 }


/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */
 Grid Zoo::r_pentomino()
 {
    Grid r_pentomino(3);


    r_pentomino.set(1, 0, Cell::ALIVE);
    r_pentomino.set(2, 0, Cell::ALIVE);
    r_pentomino.set(0, 1, Cell::ALIVE);
    r_pentomino.set(1, 1, Cell::ALIVE);
    r_pentomino.set(1, 2, Cell::ALIVE);

    return r_pentomino;
 }


/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 5x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
Grid Zoo::light_weight_spaceship()
 {
    Grid light_weight_spaceship(5, 4);

    light_weight_spaceship.set(1, 0, Cell::ALIVE);
    light_weight_spaceship.set(4, 0, Cell::ALIVE);
    light_weight_spaceship.set(0, 1, Cell::ALIVE);
    light_weight_spaceship.set(0, 2, Cell::ALIVE);
    light_weight_spaceship.set(4, 2, Cell::ALIVE);
    light_weight_spaceship.set(0, 3, Cell::ALIVE);
    light_weight_spaceship.set(1, 3, Cell::ALIVE);
    light_weight_spaceship.set(2, 3, Cell::ALIVE);
    light_weight_spaceship.set(3, 3, Cell::ALIVE);

    return light_weight_spaceship;
 }


/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */
Grid Zoo::load_ascii(std::string path)
{

    unsigned int width;
    unsigned int height;

    char c;

    std::ifstream file(path);

    if(!file)
    {   
        file.close();
        throw std::runtime_error("Unable to open file.");
    }
    else
    {
        file >> width;
        file >> height; 
        file.get(c);

        Grid g(width, height);

        if(c == '\n')
        {
            for(unsigned int i = 0; i < height; i++)
            {
                for(unsigned int j = 0; j < width + 1; j++)
                {
                    file.get(c);

                    if(c == char(Cell::ALIVE))
                    {
                        g.set(j, i, Cell::ALIVE);
                    }
                    else if(c == char(Cell::DEAD))
                    {
                         g.set(j, i, Cell::DEAD);
                    }
                    else if(c == '\n' && j == width)
                    {
                        //Do nothing, move to next char.
                    }
                    else
                    {
                        file.close();
                        throw std::runtime_error("Invalid Character.");
                    }
                }
            }

            file.close();
            return g;
        }
        else
        {
            throw std::runtime_error("Expected new line character.");
        } 
    }
}


/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_ascii(std::string path, Grid const & grid)
{

    unsigned int width = grid.get_width();
    unsigned int height = grid.get_height();

    std::ofstream outdata(path);

    if(!outdata)
    {
        outdata.close();
        throw std::runtime_error("Unable to open file.");
    }
    else
    {

        outdata << width << " " << height << '\n';

        for(unsigned int i = 0; i < height; i++)
        {
            for(unsigned int j = 0; j < width + 1; j++)
            {

                if(j == width)
                {
                    outdata << '\n';
                }
                else
                {
                    outdata << char(grid.get(j,i));
                }
            }
        }
    }

    outdata.close();
}


/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */
Grid Zoo::load_binary(std::string path)
{
    unsigned int size;
    unsigned int width, height;
    char* buff;
    std::string string_bitset;
   
    std::ifstream file(path, std::ios::in|std::ios::binary);
   
    if (file.is_open())
    {

        //Read Header of file, to get width and height.
        file.read((char*)&width, sizeof(width));
        file.read((char*)&height, sizeof(height));
        
        //Calculate the size 
        size = std::ceil( (width*height) / BYTE_SIZE_DOUBLE);

        //Evaluates whether the grid specified can be described in 8 bytes.
        if(size > BGOL_FILE_GRID_BYTE_CAPACITY)
        {
            throw std::overflow_error("File/Grid is too large to be read or is invalid.");
        }
        else
        {
            //Construct grid with parsed width and height.
            Grid g(width, height);

            buff = new char[size];
            
            file.read(buff, size);

            //If the file was unable to read that amount of bits then the file must be shorter than expected.
            if(file.fail())
            {
                delete buff;
                throw std::runtime_error("Unexpected end to file.");
            }
            else
            {
                for(unsigned int i = 0; i < size; i++)
                {       
                    std::bitset<BYTE_SIZE> bitset = buff[i];

                    std::string temp = bitset.to_string();

                    //Flip the byte to correct bit endianness.
                    std::reverse(temp.begin(), temp.end());
                
                    string_bitset += temp;
                }
                
                for(unsigned int i = 0, k = 0; i < height; i++)
                {
                    for(unsigned int j = 0; j < width; j++, k++)
                    {
                        if(string_bitset[k] == '0')
                        {
                            g.set(j, i, Cell::DEAD);
                        }
                        else if(string_bitset[k] == '1')
                        {
                            g.set(j, i, Cell::ALIVE);
                        }
                        else
                        {
                            delete buff;
                            throw std::runtime_error("Unexpected character.");
                        }
                    }   
                }
                
                delete buff;
                file.close();
                return g;
            } 
        }    
    }
    else
    {
        throw std::runtime_error("File couldnt be opened.");
    }
    
}

/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_binary(std::string path, Grid const & grid)
{
    
    unsigned int width = grid.get_width();
    unsigned int height = grid.get_height();

    std::ofstream outdata(path, std::ios::binary);
    if(!outdata)
    {
        throw std::runtime_error("Unable to open file.");
    }
    else
    {   
        outdata.write(reinterpret_cast<const char *>(&width), sizeof(width));
        outdata.write(reinterpret_cast<const char *>(&height), sizeof(height));

        if(outdata.fail())
        {
            throw std::runtime_error("Error writing width and/or height to file.");
        }else
        {
            std::bitset<BGOL_FILE_GRID_BIT_CAPACITY> bit;

            for(unsigned int i = 0, k = 0; i < height; i++)
            {
                for(unsigned int j = 0; j < width; j++, k++)
                {
                    char c = char(grid.get(j,i));

                    if(c == char(Cell::DEAD))
                    {
                        bit[k] = 0;
                    }
                    else if(c == char(Cell::ALIVE))
                    {
                        bit[k] = 1;
                    }      
                }
            }

            outdata.write(reinterpret_cast<const char *>(&bit), sizeof(bit));

            if(outdata.fail())
            {
                outdata.close();
                throw std::runtime_error("Error writing grid values to file.");
            }
            else
            {
                outdata.close();
            }
        }
    }
}

#undef BGOL_FILE_GRID_BYTE_CAPACITY
#undef BGOL_FILE_GRID_BIT_CAPACITY
#undef BYTE_SIZE 
#undef BYTE_SIZE_DOUBLE

