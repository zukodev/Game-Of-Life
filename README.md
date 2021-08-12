 # Conway's Game of Life C++ console application. 
 
 ## Simulates Conway's game of life, designed to satisfy a Catch2 testing suite.
 
 
 ![image](https://user-images.githubusercontent.com/48512015/129210372-20a9a29f-294e-4286-93fb-3813d7de5c35.png)

(Snapshot of glider simulation)

--NOTE 1--
 
Grid::get_index() - Grid.cpp line 364 - implemented but not used as I have used an STL 2-dimensional array (vector<vector>) as my data structure to hold the information.
Therefore Grid::operator()(x, y) - Grid.cpp line 487 & 530 - have been implemented without using Grid::get_index().

--NOTE 2--

Zoo::load_binary() & Zoo::save_binary() - Zoo.cpp line 322 & 436 respectively - Binary read and write methods are implemented under the assumption that the .bgol files are 16bytes. ({width} 4 + {height} 4 + {cells} 8). 
