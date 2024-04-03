Dice Solitaire is a simple solitare game for the [Arduboy].
To install on the Arduboy, simply load ``DiceSolitaire.ino`` in the
[Arduino IDE][arduino] and load to the Arduboy per normal.

Hex files are also included with the release tags, which
can be used with the [ProjectABE] emulator, or other tools.

[Arduboy]: https://www.arduboy.com/
[arduino]: https://www.arduino.cc/en/software
[ProjectABE]: https://github.com/felipemanga/ProjectABE

# How to Play

This game is a solitare variant that uses two colours of dice
instead of cards. The objective is to stack all six dice of
the same colour in decreasing order from right to left. Pickup
rules are similar to Yukon solitaire: you can pick up from
any position in the stack, and place so long as the destination
position is valid for the item picked up.

Unlike Yukon, there are no foundations and only five playing
stacks. Additionally, dice are stacked in the same colour,
not alternating. When a full set of six is collected, it will
be collapsed into a single entry in the left-most column. No
further dice can be placed upon a collapsed stack, though
dice already on that stack can still be built upon.

Press the left button to pick up and place a dice (if in a
valid destination). Press the right button to return a grabbed
stack to its original location. No stack may grow larger
than what can fit on the screen.
