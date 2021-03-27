# Othello
Othello/Reversi Game made in C and run in python cause my mac just can't display graphics in c++

## Thinking about using this yourself?
You only need to download c, python 
and on top of that ctypes on python.
that's it i think.

I made Shell Scripts to help me make the shared library that can be imported to python for use

### About Shell Scripts(.command files)
RUNC.command is not needed
RUNC.command is just there to help me run c++ code cause i don't want to type out that long string everytime

Compile.command is not needed
Compile.command is there just to build the shared library using my c files so that I don't have to type it out everytime

### History on how this came about
Roughly 2 Months back I made this Game with the files in the Old folder but it was very flawed and still quite slow.\n
I was just very bad at Othello so I wanted to know if it was a solved game.
I already mapped out quite a few games on my own like tic tac toe, chopsticks and the 4-in-a-row gravity game(Connect 4) so I wanted to know.
Turns out it wasn't for the 8x8 version so I decided with the improvements in technology, I could solve it.
Given my mac is the MacBookPro(15.4 inch 1440x900) from the Mid-2010, I wasn't expecting much 
**but surprisingly** it was really fast the first time I ran the neagmax algorithm for a depth of 60 moves.
Now it's pretty fast but still slow, not sure if there are any more optimisations I could implement in finding moves and such
I know there are still plenty of optimisations to the AI I can make so I will be working on that for the time being.

The .o file is the compiled object code of the c code.
The .dylib file is the shared library file of the c code.
Thats about it.
