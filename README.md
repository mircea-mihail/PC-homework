# PC-homework
This repository contains my 3 homework assignments from the Computer Programming class.

## Divide et Impera
For this programming technique I chose to solve the well known egg dropping puzzle. I did steal the formula idea for the dropping algorithm from https://www.geeksforgeeks.org/egg-dropping-puzzle-dp-11/ but the rest of the code is my own implementation and solution. In this partiular case bottles were dropped, not eggs but the same principles apply.

## The problem in question:
Maria lives in a block of flats with n floors, numbered from 0 to n-1
She wishes to find out what the highest floor that doesn't break the bottle is.
	Maria only has 2 glass bottles at hand. Using the divide et impera method, 
display the floors she needs to throw the bottle from in order to find the answer,
with the lowest amount of attempts.
	Input data: 
		the floors.in file
		on the first line there is n number of floors
	Output:
		the etaje.out file where the floors where the bottle is thrown at are displayed in order
		each line must contain a floor
    
## Files
floors.c contains my code
floors is the executable
floors.in is autogenerated by my code

## Code
"filegen" generates random floors at witch the bottles break. To choose your own floor un-comment the index variable and set it to anything.
"reading" retrieves the generated data from the file (required by the assignment)
"printing" prints the floor to make the process easier to understand
"iterativeFinalFloor" finds the required floor dropping the bottle from one to the next
"recursiveFloor" finds the first floor at whitch the bottle breaks using the "formula" function 
"counter" prints the floors' index

## Some possible results
![](https://github.com/mircea-mihail/bkt-through-tetris/blob/master/8x6_example.png)
![](https://github.com/mircea-mihail/bkt-through-tetris/blob/master/6x6_example.png)
![](https://github.com/mircea-mihail/bkt-through-tetris/blob/master/4x4_example.png)
![](https://github.com/mircea-mihail/bkt-through-tetris/blob/master/2x4_example.png)


