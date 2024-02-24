## Helmets & Hordes

Helmets & Hordes is an endless runner where you need to avoid enemies, dodge traps and collect coins and other treasures. You can also defeat enemies to obtain extra treasure. You can find and wear 7 helmets which give you unique powerups that let you play the game in different ways. The goal is to gather as much treasure as possible before the enemies defeat you. We need to find the right balance of game speed, enemy variety, wave intensity and powerup functions to make this a fun game.

I think we should use a jump button, an action button (for helmet abilities) and the left/right buttons for movement. The down button should probably pause the game.

* GAMEPLAY IDEAS
* Helena: The main character, a warrior who is trying to take as much loot as she can from a trapped dungeon filled with savage Orks (and maybe other creatures, too). She can equip different helmets that grant her special abilities.
* Health: Helena has 3 hit points, which are indicated through the character sprite.
  * Naked (no helmet, no armour) - Helena will die if she is hit.
  * Armoured (no helmet) - Helena will lose her armour if she is hit and will become naked.
  * Armoured (with helmet) - Helena will lose her helmet if she is hit and will become armoured.
* Armour: Helena wears protective armour that is discarded when she is hit while not wearing a helmet. She can find more armour in the dungeon by touching an armour icon. If Helena is already armoured, the armour she touches will turn to treasure (score) instead.
* The Helmets: There will be 8 helmet abilities (to fit 1 byte). You can retrieve them by opening (touching) treasure chests. They are given to the player randomly, and some have a higher rate of probability than others. This should add a kind of risk/reward aspect to the gameplay - do I touch this treasure chest, gaining a new helmet and losing the one I have now? It should not be possible to find the helmet you are currently wearing in a new treasure chest - the helmet should always be different.

  * Warrior's Helm: Helena performs an automatic downwards attack in midair - she can kill enemies by landing on them.
  * ~~Helm of Atlas: Helena causes a shockwave each time she lands from a jump/fall. This shockwave knocks all enemies over.~~
  * Football Helmet: Helena can perform a running tackle that can smash anything, including traps.
  * Thief's Hood: Helena can become intangible for a short time when the action button is pressed, allowing her to pass through traps without taking damage.
  * Cutter Mask: Helena can throw a boomerang cutter in a wide arc. Inspired by this helmet in Dragon Ball! https://www.youtube.com/watch?v=WPOMIQyLTbM
  * Magnet Helm: Treasure (coins) is automatically pulled towards Helena, elimainating some potentially risky scenarios.
  * Mercury's Helm: Helena can glide downwards while jumping/falling by holding the jump button.
  * Battery Hat: Pressing the action button will cause an electrical discharge around Helena that has a long reach and defeats any enemy it touches.

* Mana Stones: Some of the helmet abilities use Mana Stones. These are collectible items that are spent each time an ability is used. You can find more in the dungeon, but you can only carry 3 at a time! Use them wisely.
* Sword, dagger or unarmed: Helena will be equipped with either a sword, a dagger or nothing (unarmed) depending on the helmet she is wearing or her current health state.

  * Naked (no helmet, no armour) - Helena carries a dagger.
  * Armoured (no helmet) - Helena carries a sword.
  * Warrior's Helm: Sword.
  *~~Helm of Atlas: Unarmed.~~
  * Football Helmet: Unarmed.
  * Thief's Hood: Dagger.
  * Cutter Mask: Unarmed.
  * Magnet Helm: Sword.
  * Mercury's Helm: Sword.
  * Battery Hat: Unarmed.
  
* Combat: Helena can defeat most enemies by running into them with her sword or dagger. Additionally, some helmet abilities can be used to defeat enemies.
* Enemies:
  * Unarmed Ork: Charges at the player and carries no weapon. Can be defeated if you simply run into him with your sword or dagger.
  * Ork Spearman (forward): Charges at the player and carries a spear pointed forwards. You need to jump over him or defeat him in some other manner.
  * Ork Spearman (upward): Charges at the player and carries a spear pointed upwards. If you try to jump over him, you'll be hurt by his spear. You can simply run into him with your sword or dagger to defeat him.
  * It would be cool to have other enemies too, like Skeletons or Slimes. As long as they have cool gameplay functions!
* Traps:
  * Spikes: These are laid in groups of 3 on the ground and will hurt the player if they are touched.
  * Arrows: Arrows are fired from trap pillars and must be avoided or hit with a special helmet ability (for example, the Cutter Mask can be thrown at them in midair).
  * Boulders: The Orks will sometimes drop boulders from overhead - you need to dodge them by moving left or right!
* Collecting treasure (coins) will give you points. You also get coins for killing enemies, and for collecting armour when you don't need it.

*GRAPHICS IDEAS
* Background scrolling: The background (a dark dungeon) will be composed of 3 different layers that will use a scrolling effect.
  * Layer 3 (back): This layer contains some brick wall tiles and barred dungeon windows.
    * Bricks: There are 3 brick wall graphics - they can be arranged randomly via code.
    * Windows: These can be arranged via code, but only near the top of the screen.
  * Layer 2 (mid): This layer has some hanging chains, stone pillars and wooden crates (loot stolen by the Orks).
    * Chains: There is a vertically repeatable chain graphic. These can be arranged to hang from the ceiling randomly, but should probably not be more than 16 pixels high.
    * Pillars: These should be placed more evenly, to indicate a bit of a regular structure to the Ork dungeon.
    * Wooden crates: I suppose we can just arrange these randomly? Maybe they should be object in the playing field that you need to jump over?
  * Layer 1 (front): This layer contains the floor brick tiles, pebbles and other debris, weeds, etc. This is the level that the player is running on. Maybe the weeds/pebbles/debris can be drawn on top of the player sprite?
