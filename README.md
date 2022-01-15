# Minesweeper
Is a single-player puzzle video game. The objective of the game is to clear a rectangular board containing hidden "mines" 
or bombs without detonating any of them.

 
## Rules
Rules are very simple. The board is divided into cells, with mines randomly distributed. 
To win, you need to open all the cells. The number on a cell shows the number of mines adjacent to it. 
Using this information, you can determine cells that are safe, and cells that contain mines. 
Cells suspected of being mines can be marked with a flag using the right mouse button.

# Git user attention
1. Clone the repo from GitHub

         $ git clone https://github.com/dariannax3/Minesweeper.git

2. Create and go to build directory and build the code

        $ mkdir build && cd build/ && cmake .. && make -j
        
3. Run the code
  
        $  ./minesweeper

# Usage
Our Minesweeper game is a terminal version. 

Write in console command in style: **action position_x position_y** where position_x is a selected row and position_y is a selected column.

Action could be:
- **c** -> choose field
- **f** -> mark filed with flag
- **u** -> unmark field

For example to choose top left corner type:  
          
          $  c 0 0
         
# Prerequisites
- cmake version 3.14
