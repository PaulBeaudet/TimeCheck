// TimeCheck.cpp ~ Copyright 2015 Paul Beaudet
// MIT licence ~ See licence for details

#include "TimeCheck.h"

TimeCheck::TimeCheck(){}

void TimeCheck::set(uint32_t setTime){
	timer[1] = setTime;   // durration desired
	timer[0] = millis();  // current time noted
}

boolean TimeCheck::check(){
	if(millis() - timer[0] > timer[1]){return true;} // if specified time elapsed
	return false;                                    // return true else false
}
