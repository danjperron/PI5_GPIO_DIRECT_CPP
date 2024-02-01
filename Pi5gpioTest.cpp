#include "Pi5gpioHW.hpp"
#include <unistd.h>
#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
  int Pin = 19;

  Pi5gpioHW gpio = Pi5gpioHW();

  // PinMode(int Pin, int pad , int mode, int riodrive);
  gpio.PinMode(Pin,0,5,1); // pad=0 means output

  int value=0;
  while(true)
    {
       gpio.writeDigital(Pin,(value++)&1);
      usleep(1000000);
    }

  return 0;

}
