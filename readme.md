#TimeCheck

Simple stopwatch library: Does one simple thing, does it well

Author's Note: This was a basic function that I was using over in my Arduino code. Having a library for it allows the creation of multiple instances of a stopwatch without creating in code separately named copies of timers.

##Use
	void myFunction(int amountOfTime){
		static TimeCheck timer;

		if(timer.check()){           // check is timed task has run
			doTheThing();            // run timed task
			timer.set(amountOfTime); // set next amount of time
		}
	}

Note that "timer.check()" defaults to returning true.
In other words timer.check() only returns false when time has been set and is elapsing.
Also note that this type of utility is meant to run in a asynchronously structured program. Meaning that "if(timer.check()){}" is meant to be polled frequently in an unencumbered main loop. A loop with that runs instruction by instruction with long delays in between polling will likely end up in unexpected results.
