// asyncBlink.ino ~ blink all the things as opposed to just one thing
// Copyright 2015 ~ Paul Beaudet ~ MIT Licence
#include <TimeCheck.h> // Include library
// TimeCheck abstracts some complexity around checking a stop watch
#define LED_PIN 13     // replace the word LED_PIN with 13 before compile

void setup(){               // "setup" is the first function arduino calls
	pinMode(LED_PIN, OUTPUT); // tell Arduino which pin is the LED
	                          // and that the LED is an output
	Serial.begin(9600);       // set rate of communication with computer
	// Serial is a library included with Arduino
	// Allows the Arduino to send characters over usb
	// the period deliminates a method / "function" of "Serial"
	// That is, descibes a function Serial can do, in this case "begin"
}

void loop(){          // "loop" is the second function arduino calls
  blink(1000);        // blinks LED every x millisecond for x milliseconds
	blinkCharA(30000);  // sends A char to serial monitor @ x milliseconds
	blinkCharB(60000);  // sends B char @ x milliseconds
}

/* setup and loop are part of every Arduino sketch
 * setup runs once and loop runs continueously
 * The programer can define their own functions just like setup and loop
 * This keeps instructions modular and simple to read if done right
   -- Quick disection of a function in 4 parts --
	example: see "setup" above
   1. the "void" part descibes what the function might return
	    - void: returns nothing worth talking about
			- boolean: return 1 or O aka true or false
			- char: return any number between -127 and 127
			- ext. (there are more types of data)
	 2. "setup" is the name of the function
	 3. "()" a function can be passed data just as it can return it
	    - example "void myFunction(char letter){doSomething();}"
			- in that case "letter" would be a parameter of myFunction
			- setup has no parameters it could also be "void setup(void){}"
	 4. "{}" functions excute a sets of instructions within the brackets
 *
 * remember instructions are deliminated by semicolons
 */

void blink(unsigned long amountOfTime){  // takes amount of time
	static TimeCheck timer;
	// create a persistent instence of timer for this specific function
	static boolean ledStatus = false;
	// create a persitent idicator of whether the led is on or not
	if(timer.check()){ // if time has elapsed
		// check returns 1 first run and 0 when time set and still elapsing
		// then returns 1 when its done
		ledStatus = !ledStatus;
		// toggle LED status
		digitalWrite(LED_PIN, ledStatus);
		// turn LED on or off
		if(ledStatus){Serial.println("Blink!");}
		// if led is on send Blink! to computer
		timer.set(amountOfTime);
		// set amount of time till check returns true/1
	}
}

void blinkCharA(unsigned long amountOfTime){
	// unsigned long is a data type that can represent
	// any number between 0 and 4,294,967,295
	// or about a maximum of 49 days in terms of what is being represented
	// see -> https://www.arduino.cc/en/Reference/HomePage
	// for more information about which data types are appropriate
	// normally the goal is to use the "smallest" type needed
  static TimeCheck timer; // blinkCharA's timer
	/* TimeCheck is a type of data as defined by the Timecheck library
	 * an instance of this data is created just for this function
	 * static denotes that a persitent version of the data is desired
	 * TimeCheck Timer; would create a new version of the data every
	   time the function was called, thus losing the time placeholder
	   that was "set" */
	if(timer.check()){
		Serial.println("A");
		timer.set(amountOfTime);
	}
}

void blinkCharB(unsigned long amountOfTime){
  static TimeCheck timer; // blickCharB's Timer
	if(timer.check()){
		Serial.println("B");
		timer.set(amountOfTime);
	}
}
