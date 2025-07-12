# Experiments_With_Race_Conditions
race.c is a program designed to loosely imitate a html server being accessed by internet users and occasionally being updated.
It has a single tread responsible for updating a global string representing the content and 5 threads dedicated to consuming by printing it to the screen
When race.c is run non naively  with concurrency protection in the form of mutexes it exhibits the desired behaviour.
But this is not the case when these protections are removed, as the program produces the original strings along with a bunch of jumbled versions.
This behaviour happens because consuming treads accessing the global string randomly which eventually means the string will be accessed while also being updated. 


How a mutex works: 
A mutex is a global value that can represent a locked and unlocked state.
If a Mutex was just a global variable it would similarly be vulnerable to race conditions in situations where lock operation on the mutex is interleaved on two or more operations simultaneously.
To prevent such a situation mutexes use atomic operation which allow a thread to exclusively and uninterruptedly check and set a lock.  
