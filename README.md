# Wenman
***
[*Wenman*](https://en.wikipedia.org/wiki/Wolf_Island) is a simple app that simulates a trivial ecosystem consisting
of a population of bunnies and wolves.

![example image](../img/example1.PNG "Example image")

## Rules
***
There are 3 possible types of entities: bunnies, female wolves and male wolves.

Bunnies do not need any resources to persist. Each of their moves is random. 
Additionally, a bunny has 20% chance to generate offspring before every move.

Wolves have an attribute called fat. Its default value is 1.0 upon creation. 
However, when a new wolf is born from a female, it inherits her fat.

Making a move reduces a wolf's fat by 0.1. Eating a bunny increases it by 1.0, up to a maximum of 2.0.

A female wolf always makes a random move unless there is a neighbouring bunny. Then, it moves to that bunny's square
and eats the bunny. If more than 1 neghbouring bunny is available, the choice is random.

A male wolf acts similarly, prioritizing eating a bunny when possible. If no bunnies nearby, though, it looks for
a female wolf and moves onto her square. Provided that the female is not pregnant at that moment, a new wolf will be
born 2 turns later.

A hedge-confined area can be added to the simulation. Squares that are within its bounds are not accessible to wolves.

Note:
If a bunny jumps onto a square with wolves, it will not be eaten by the ones present therein.

## Dependencies
***
[`SFML 2.5`](https://www.sfml-dev.org/)

[`TGUI 0.8`](https://tgui.eu/)

## Run
***
After running the executable, it is needed to define some properties in the GUI.  
When choosing hedge's position, the squares are numbered *1 : x/y*.  
The sliders automatically refresh the range so that it is impossible to e.g. place the hedge outside the grid.

![example image](../img/example2.PNG "Example image")

The outcome:

![example image](../img/example3.PNG "Example image")

The text box on the left displays the currently chosen square to add animals onto.  
Clicking on an animal label spawns it there.  
Trying to put a wolf onto an invalid square does not result in anything.


![example image](../img/example4.PNG "Example image")

## License
***
[MIT](https://choosealicense.com/licenses/mit/)