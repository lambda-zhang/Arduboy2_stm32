# Implementation
- There are two (2) ways to rotate from each orientation (clockwise and counter-clockwise)
- Each piece has four (4) orientations (North, East, South, and West)
- There are five (5) possible rotations destinations for each attempt
	- The first rotation simply cycles between the four orientations
	- If that rotation fails, the other possibilities are tried in order
	- If all five possible rotations are blocks, rotation is not allowed
- Each piece has 2 ways to rotate * 4 facings * 4 non-default rotations = 32 total rotations
- Each rotation offset is packed into an 8-bit value (two 4-bit signed integers)
	- Offsets in the range [-8..7] are supported.
	- 🤔 other compression may be possible
		- Lookup table into used coordinates (per piece, or across the board)
		- Range seems to be [-2..2] on each axis, which could be represented by a single value of [0..24], or 5-bits.
			- This would reduce data size from 192 bytes (32 bytes * 6 pieces) down to 120 bytes (20 bytes * 6 pieces)

## Rotation Possibilities
Rotation possibilities are defined by an (x, y) offset relative to the default rotation.
```Psudocode
offset = PieceData::GetRotationOffset(startingOrientation, rotationDirection, rotationIndex);

Offset PieceData::GetRotationOffset(startingOrientation, rotationDirection, rotationIndex)
{
	if (rotationIndex == 0) { return (0, 0); }
	return m_rotations[rotationDirection][startingOrientation][rotationIndex - 1];
}
```


# Design
## "O" Piece
Nothing to be done here. The O piece just rotates in place.

## "I" Piece
```Tetrimino
North   East    South   West
....    .0-.    ....    .-3.
----    .1-.    3210    .-2.
0123    .2-.    ----    .-1.
....    .3-.    ....    .-0.
```
### Clockwise Rotations
| Direction     | 1      | 2       | 3       | 4        | 5        |
| ------------- | ------ | ------- | ------- | -------- | -------- |
| North -> East | (0, 0) | (-2, 0) | ( 1, 0) | (-2, -1) | ( 1,  2) |
| East -> South | (0, 0) | (-1, 0) | ( 2, 1) | (-1,  2) | ( 2, -1) |
| South -> West | (0, 0) | ( 2, 0) | (-1, 0) | ( 2,  1) | (-1, -2) |
| West -> North | (0, 0) | ( 1, 0) | (-2, 0) | ( 1, -2) | (-2,  1) |
### Counter-Clockwise Rotations
| Direction     | 1      | 2       | 3       | 4        | 5        |
| ------------- | ------ | ------- | ------- | -------- | -------- |
| North -> West | (0, 0) | (-1, 0) | ( 2, 0) | (-2,  2) | ( 2, -1) |
| East -> North | (0, 0) | ( 2, 0) | (-1, 0) | ( 2,  1) | (-1, -2) |
| South -> East | (0, 0) | ( 1, 0) | (-2, 0) | ( 1, -2) | (-2,  1) |
| West -> South | (0, 0) | (-2, 0) | ( 1, 0) | (-2, -1) | ( 1,  2) |

## "T" Piece
```Tetrimino
North   East    South   West
....    ....    ....    ....
-5--    .0-.    ....    -2..
012-    .15.    210.    51..
....    .2-.    -5-.    -0..
```
### Clockwise Rotations
| Direction     | 1      | 2       | 3        | 4       | 5        |
| ------------- | ------ | ------- | -------- | ------- | -------- |
| North -> East | (0, 0) | (-1, 0) | (-1,  1) | n/a     | (-1, -2) |
| East -> South | (0, 0) | ( 1, 0) | ( 1,  1) | ( 0, 2) | ( 1,  2) |
| South -> West | (0, 0) | ( 1, 0) | n/a      | ( 0, 2) | ( 1,  2) |
| West -> North | (0, 0) | (-1, 0) | (-1, -1) | ( 0, 2) | (-1,  2) |
### Counter-Clockwise Rotations
| Direction     | 1      | 2       | 3        | 4       | 5        |
| ------------- | ------ | ------- | -------- | ------- | -------- |
| North -> West | (0, 0) | ( 1, 0) | ( 1,  1) | n/a     | ( 1, -2) |
| East -> North | (0, 0) | ( 1, 0) | ( 1, -1) | ( 0, 2) | ( 1,  2) |
| South -> East | (0, 0) | (-1, 0) | n/a      | ( 0, 2) | (-1,  2) |
| West -> South | (0, 0) | (-1, 0) | (-1, -1) | ( 0, 2) | (-1,  2) |


## "L", "J", "S", and "Z" Pieces
### Clockwise Rotations
| Direction     | 1      | 2        | 3        | 4       | 5        |
| ------------- | ------ | -------- | -------- | ------- | -------- |
| North -> East | (0, 0) | (-1,  0) | (-1,  1) | ( 0, -2) | (-1, -2) |
| East -> South | (0, 0) | ( 1,  0) | ( 1, -1) | ( 0,  2) | ( 1,  2) |
| South -> West | (0, 0) | ( 1,  0) | ( 1,  1) | ( 0, -2) | ( 1, -2) |
| West -> North | (0, 0) | (-1,  0) | (-1, -1) | ( 0,  2) | (-1,  2) |
### Counter-Clockwise Rotations
| Direction     | 1      | 2        | 3        | 4        | 5        |
| ------------- | ------ | -------- | -------- | -------- |
| North -> West | (0, 0) | ( 1,  0) | ( 1,  1) | ( 0, -2) | ( 1, -2) |
| East -> North | (0, 0) | ( 1,  0) | ( 1, -1) | ( 0,  2) | ( 1,  2) |
| South -> East | (0, 0) | (-1,  0) | (-1,  1) | ( 0, -2) | (-1, -2) |
| West -> South | (0, 0) | (-1,  0) | (-1, -1) | ( 0,  2) | (-1,  2) |
