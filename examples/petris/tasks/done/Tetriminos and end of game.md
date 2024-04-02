Tetriminos and end of game
- [x] All Tetriminos (I, Z, S, J, L, O, T)
	- [x] All Tetriminos selected randomly
	- [x] Tetriminos drawing
	- [x] Movement and collision working
- [x] Detect end of game if spawn overlap (aka. Block Out)
- No rotation needed


# Tetriminos
## Spawning
This is the default orientation for each of the Tetriminos
```Tetriminos
-OO- ---- -O-- --O- O--- -OO- OO--
-OO- OOOO OOO- OOO- OOO- OO-- -OO-
```

## Internal Representation
📝I chose (A), primarily because it takes less memory.
- I may need to backtrack on this decision to support blocks with different visuals, but using a more abstract internal representation forced me to make a cleaner interface. That should, in turn, make it easier to change in the future.
### Representation A)
Each Tetrimino default position is described by an 8-bit value.
```Tetriminos
Bits : 4567
       0123
Example :
"T" piece = -O-- = -5-- = --5- -210 = 0010 0111 = 0x27
            OOO-   012-

O = 0110 0110 = 0x66
I = 0000 1111 = 0x0F
T = 0010 0111 = 0x27
L = 0100 0111 = 0x47
J = 0000 0111 = 0x17
S = 0110 0011 = 0x63
Z = 0011 0110 = 0x36
```

### Representation B)
Each Tetrimino is an array of four (x, y) pairs.
#### Naïve Implementation
`array<4, pair<int8, int8>> pieceLocations;`
- 👍The signed (x, y) pair is nice and I don't have to deal with unpacking locations out of bit fields
- 👎Not very compact
#### Naïve Implementation++
`array<3, pair<int8, int8>> pieceLocations;`
- The first block is always at (0, 0), so it doesn't need extra storage
- 👍Saves some space
- 👎Still wastes a lot
