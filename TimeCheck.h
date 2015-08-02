// TimeCheck.h ~ Copyright 2015 Paul Beaudet
// MIT licence ~ See licence for details
#ifndef TimeCheck_H
#define TimeCheck_H

#include <Arduino.h>

class TimeCheck {
public:
  TimeCheck();
	boolean check();              // returns if set time elapsed
	void set(uint32_t durration); // enter time to wait for
private:
  uint32_t timer[2] = {1, 0};   // holds set time and durration
};

#endif
