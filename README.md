# 42-Lem-in
Lem-in is a project about moving an ant colony from A to B in the most optimised way.  

Subject : [English](https://github.com/ssfar/42-Subjects.pdf/blob/master/lem-in.en.pdf) - [Français](https://github.com/ssfar/42-Subjects.pdf/blob/master/lem-in.fr.pdf)

Grade 100/100  
Bonus 22/25:  
 :heavy_check_mark: Graphic visualiser (SDL2) | :heavy_check_mark: Very quick

#### Objectives :
• Graph traversal  
• Depth-first search

#### Skills :
• Imperative programming  
• Algorithms & AI  
• Rigor  

## How to use

#### pre-required : Make, GCC, SDL2 and SDL2_ttf

First of all, open a terminal, go into the project and build it:   
```  
make
```
### Input

The program reads the map from the standart input: 
```
./lem_in < a_map_file
```
Valid maps can be found inside the maps/ folder.
#### Inside map files, the anthill parameters are represented in this order:
![anthill_representation](https://user-images.githubusercontent.com/45463065/86970673-0c97e300-c170-11ea-901c-e3b9292d86e3.png)  
#### Here is a exemple of a map:
![map](https://user-images.githubusercontent.com/45463065/86971327-461d1e00-c171-11ea-9414-09d787977ffa.png)  

If you want to use the visualiser, just pipe it to the previous command:
```
./lem_in < a_map_file | ./visualiser/visu
```  
### Output

#### If the map is valid, the program will display the map followed by the solution:
![lem_in_output](https://user-images.githubusercontent.com/45463065/86971332-474e4b00-c171-11ea-9a65-772554c5cd5a.png)

In the solution, each lines represent the movement of the ants of a turn.
Each ants are represented whit a 'L' folowed by a number.
The string after the '-' character is the name of the room in which the ant moved during the turn.
An ant can move once per turn and a room can only contain one ant (except for the start and end rooms).
(Read the subject for more infos).  
In the previous exemple at the first turn the ant 1 moved from START to A, and ant 2 form START to B.
In the second round, the ant 1 moved from A to C ...

#### Here is a demo of the visualiser (due to video compression, colors are a bit washed out):
[![lem_in_visu_screen](https://user-images.githubusercontent.com/45463065/86975363-774d1c80-c178-11ea-89db-98cdfbb90ebe.png)](https://www.youtube.com/watch?v=ONwSkZ5tPZk)

If the map is not valid, the program will display an error message.
