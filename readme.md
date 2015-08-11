#TimeCheck

Simple stopwatch library: Does one simple thing, does it well

Author's Note: This was a basic function that I was using over in my Arduino code. Having a library for it allows the creation of multiple instances of a stopwatch without creating in code separately named copies of timers.

##Use
	#include <TimeCheck.h>

	void myFunction(int amountOfTime){
		static TimeCheck timer;      // instantiate a persistent timer  

		if(timer.check()){           // check if timed task has run: first defaults true
			doTheThing();            // run timed task
			timer.set(amountOfTime); // set next amount of time
		}
	}

Note that "timer.check()" defaults to returning true.
In other words timer.check() only returns false when time has been set and is elapsing.

Also note that this type of utility is meant to run in a asynchronously structured program. Meaning that "if(timer.check()){}" is meant to be polled frequently in an unencumbered main loop. A loop with that runs instruction by instruction with long delays in between polling will likely end up in unexpected results.

##Thoughts and examples of TimeCheck need

It is important to think about this way of doing things as a contrast to the way Arduino coding is initially presented. Which is to say a strict step by step procedure. Of course strict step by step makes a simple example like the plain old blink sketch easy to understand, however in reality projects will likely involve more than just blinking a singular LED. Maybe multiple sensors need to be polled for when they hit an odd value and react to the oddest value every second. This is may be doable with standard delays,

#### More realistic situation (delay way)

	void loop(){
		runningAverageSensor1();
		runningAverageSensor2();
		runningAverageSensor3();
		delay(980);              // maybe it takes 10ms to read sensors?
		reactToHighestAverage(); // intended to run at least every second
		                         // might run every 995ms
		// most importantly note each sensor is being averaged only once before reaction
	}


Ultimately it becomes much easier to think about the problem in terms of checking when information needs to be reacted to. Otherwise the whole sequence of events needs to be modeled around how long it takes to read a sensor value and how many sensors are being read. In that synchronous way, if a sensor was added all of the code would need to be changed (or at least the delay in the case of the example). With the asynchronous TimeCheck way just add that sensor! As long as all of the sensors can be read faster than the duration between reactions things will behave as expected.

#### Easier to manage / more capable (TimeCheck way)

	void loop(){
		runningAverageSensor1();
		runningAverageSensor2();
		runningAverageSensor3();
		checkIfTimeToReact();
		// note each sensor is averaged as much can be as divided among multiple sensors
	}

	void checkIfTimeToReact(){
		static TimeCheck timer;

		if(timer.check()){           // resolves as true when times up
			reactToHighestAverage();
			timer.set(1000);         // sets to at least a second
		}
	}

In this way this code MIGHT check IF it is time to react over a thousand times a second depending on what else is going in the main loop. This may sound inefficient and like more work, and maybe it is, but remember "doing nothing" is an oxymoron because doing implies something is happing. The Arduino is always "doing" something unless it is turned off, put it to sleep, blown it up, etc. In the Arduino's case of "doing nothing" AKA "delay" is wasting precious clock cycles proverbially twiddling its thumbs when it could be polling your sensors for a much higher resolution average. In that way this second TimeCheck example would probably produce more desirable results. That is so long as the following issue is avoided

#### Over-reaching capability


	void loop(){
		Average2000Sensors(); // takes ~3 seconds
		checkIfTimeToReact(); // will occur after sensors are finished
	}

	void checkIfTimeToReact(){
		static TimeCheck timer;

		if(timer.check()){           // resolves as true when times up
			reactToHighestAverage();
			timer.set(1000);
			// sets TimeCheck to resolve true at least after the next second.
		}
	}

This example shows where TimeCheck will fail to work as intended. Averaging 2000 sensors at once is far too synchronous to play nice with this TimeCheck because it takes around 3 seconds to accomplish that feat and the reaction is desired every 1 second. TimeCheck merely test if AT LEAST the desired time has past. In this case reaction will still occur, just every 3 seconds or so. Probably not what was intended.

#### Conclusion
All of this may seem to indicate that timing is super confusing, and it can be. However it can generally be simple if one can gather their thoughts around doing things in an asynchronous way and organize their code that way. Remember that little Arduino is fast and can do things in the order of micro seconds. Which is to say a somethings can be done in fraction of a millisecond which is a fraction of a second. There is likely more headroom there then most people need and if one does find themselves needing more headroom a faster Arduino or like Microcontrollor is an easy enough solution.
