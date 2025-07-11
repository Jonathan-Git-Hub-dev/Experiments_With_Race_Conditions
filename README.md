# Experiments_With_Race_Conditions

race.c has a single tread responsible for updating a global string and 5 threads deticated to consuming it.
There is drastically different behaviours exhibited when race.c is comiled with the mutex commented out and when they are not.
When the output is redirected and analyzed the mutex version only outputs the 6 predefined strings while the non mutex version outputs a bunch of junbled strings.

How a mutex works: 
  
