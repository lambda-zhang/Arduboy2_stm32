# Tetriminos
## Spawning
This is the default (aka North) orientation for each of the Tetriminos
```Tetriminos
-XX- XXXX -X-- --X- X--- -XX- XX--
-XX- ---- XXX- XXX- XXX- XX-- -XX-
```

## Internal Representation
📝This representation was chosen to keep memory usage low
Each Tetrimino default position is described by an 8-bit value.
```Tetriminos
Bits : 4567
       0123
Example :
"T" piece = -O-- = -5-- = --5- -210 = 0010 0111 = 0x27
            OOO-   012-

O = 0110 0110 = 0x66
I = 1111 0000 = 0xF0
T = 0010 0111 = 0x27
L = 0100 0111 = 0x47
J = 0001 0111 = 0x17
S = 0110 0011 = 0x63
Z = 0011 0110 = 0x36
```

## Orientation
There are 4 possible orientations per piece, North, East, South, and West.
The default orientation is North.

### O, I Pieces
```Tetriminos
O = 0110 0110 = 0x66
North   East    South   West
....    .--.    ....    .--.
-56-    .15.    -21-    .62.
-12-    .26.    -65-    .51.
....    .--.    ....    .--.

I = 1111 0000 = 0xF0
North   East    South   West
....    .-4.    ....    .7-.
4567    .-5.    ----    .6-.
----    .-6.    7654    .5-.
....    .-7.    ....    .4-.

Formula A
North = (bit % 4      , (bit / 4) + 1)
East  = ((bit / 4) + 1, 3 - (bit % 4))
South = (3 - (bit % 4), 2 - (bit / 4))
West  = (2 - (bit / 4), bit % 4      )
```

### T, L, J, S, Z Pieces
```Tetriminos
T = 0010 0111 = 0x27
North   East    South   West
....    ....    ....    ....
-5--    .0-.    ....    -2..
012-    .15.    210.    51..
....    .2-.    -5-.    -0..

L = 0100 0111 = 0x47
North   East    South   West
....    ....    ....    ....
--6-    .0-.    ....    62..
012-    .1-.    210.    -1..
....    .26.    6--.    -0..

J = 0001 0111 = 0x17
North   East    South   West
....    ....    ....    ....
4---    .04.    ....    -2..
012-    .1-.    210.    -1..
....    .2-.    --4.    40..

S = 0110 0011 = 0x63
North   East    South   West
....    ....    ....    ....
-56-    .0-.    ....    6-..
01--    .15.    -10.    51..
....    .-6.    65-.    -0..

Z = 0011 0110 = 0x36
North   East    South   West
....    ....    ....    ....
45--    .-4.    ....    -2..
-12-    .15.    21-.    51..
....    .2-.    -54.    4-..

Formula B
North = (bit % 4      , (bit / 4) + 1)
East  = ((bit / 4) + 1, 2 - (bit % 4))
South = (2 - (bit % 4), 1 - (bit / 4))
West  = (1 - (bit / 4), bit % 4      )

```


# Drop Speed
Level 1 - 1s per block; 0.045s per block soft drop
Level 2 - 0.792s per block
Level 6 - 0.260s per block
Level 14 - 0.012s per block

- 0.5s to lock in once touching the ground	
- 0.07 - 0.10s delay between lock and next piece appears
- 0.4s to remove lines

