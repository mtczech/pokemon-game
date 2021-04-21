Put your final project proposal here.

Since last winter, something I've always wanted to do is create an application
that determines the probability of catching a given Pokemon. The final project would give
me an opportunity to do this. However, this would be a bit too simple to do by itself for 
a three-week project. However, I would like to go with the Pokemon theme, and I really liked
the Mineopoly project where I designed a strategy to play a game. I could combine these and
create a program that will tell you what to do in a Pokemon battle (which moves to use, 
what pokemon to send out, etc) based on your Pokemon, the opponent's Pokemon, and other factors
such as status conditions. This program can be as simple or as complex as I want it to be,
so I will put in three weeks' worth of complexity. 

Plan for Week 1: Implement the JSON that loads all of the data necessary for the algorithm to
make informed decisions about basic attacking moves. This includes type matchups, the power and
accuracy of moves, and whether those moves are physical or special. I will use the PokeAPI Json
to put this move data in. If you know any libraries that would be helpful for this, 
I would appreciate it, since PokeAPI does not have a wrapper library for C++. 
I am planning on keeping a rotation of 15-20 Pokemon with preset movesets, which I will choose
during Week 1.

Plan for Week 2: When I was six and playing Pokemon, I did not know that there was more to
Pokemon than simply hitting the hardest. I know that now, and I want to use it to my advantage.
Week 2 will take into account status conditions and non-damaging moves, as well as other 
outside factors like weather and stat changes. These can also be found in PokeAPI.
However, there is a chance that some of the moves' data will have to be entered manually
due to bad formatting.

Plan for Week 3: One thing I'll be looking forward to is the final test: I want to be able
to beat a human player using Pokemon that may be stronger than theirs, but not by much. 
There are many varied aspects to the Pokemon game, such as multi-hit moves, held items,
and Dynamax forms, among other things. I will use Week 3 to account for these variables, 
as well as testing out my program against human opponents.

Update: Things aren't going as well as I thought they would be going, I cannot get data from
the Internet, so I took all the JSON data I need and directly put it into my project. As of right now,
my plan is to create a Pokemon game that the user can play against the computer. 