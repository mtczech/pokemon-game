My project is a simple Pokemon game between two randomly chosen teams of Pokemon.
The interface is simple: your options are displayed on the screen in the format 
"Press (number) to use (move)" or "Press (number) to switch to (pokemon)". 

Part 0: Why This?

When I was six, I received Pokemon Pearl for Christmas, and I never grew out of it.
My initial plan was to create a bot that could play Pokemon against a human opponent, 
but since I was unable to access PokeAPI to obtain information about every pokemon, 
I had to ditch the idea. So I decided to make a playable game instead, and I am happy with
the result.

Part 1: Loading.

In order to generate the teams, JSON files of all of the pokemon and 
moves used had to be taken from PokeAPI. Without it or nlohmann's JSON library, this project would not have
been possible. I also created my own JSON for the purposes of mapping pokemon names to movesets.
For those of you who know what I am talking about when I say this, all pokemon are assumed to be at 
level 100, with no EVs/IVs and a neutral nature. 

Part 2: Gameplay.

You receive a team of five pokemon, chosen randomly from the game's pool of fifteen.
The computer also receives five. Your starting pokemon is chosen semi-randomly (if you
have at least one pokemon with Stealth Rock, it will start. Otherwise, the pokemon is chosen randomly.)
The computer will always use whichever move deals the most damage. In theory this strategy seems
impossible to beat, but with skill and/or luck it can be done. 

NOTE: Upon the game being completed, it will crash. The reason for this is because all pokemon in the 
game are in pointer form, and they need to be deleted to prevent memory leaks. However, no pokemon left means 
nothing for a game to display.

Part 3: Features of the game.

In order to keep track of the game's events as they happen, I have sprinkled print statements 
throughout the code to display how much damage an attack has done, if a pokemon switches out, if a 
pokemon faints, etc. This will also tell you whether you won or lost. However, these print statements 
only work when the program is run in debug mode. This is due to compatibility issues with Windows-I 
have heard that people running programs on Linux or iOS do not have this problem. 

Other features include but are not limited to:

The following formula for damage calculation: https://bulbapedia.bulbagarden.net/wiki/Damage
This formula takes into account level, attack and defense stats, move power, type matchups, STAB,
a random number, and the burn status. However, it does not include any of the other details mentioned 
by Bulbapedia's damage formula.

Priority moves

Sleep, confusion, paralysis and freeze status conditions

Switch moves (note: you are automatically switched into the next pokemon in your party when you 
use these moves)

Using Explosion faints the user of the move

Stealth Rock deals damage to incoming pokemon based on type (1/8 of max HP, multiplied by type 
weaknesses/resistances to rock)

Stealth Rock can be cleared away with Defog

Multi-hit moves hit between 2 and 5 times

Good luck and have fun!