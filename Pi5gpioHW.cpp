
#include "Pi5gpioHW.hpp"
#include <iostream>
#include <system_error>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <sys/mman.h>

using namespace std;


void * Pi5gpioHW::base=NULL;
uint32_t * Pi5gpioHW::pwm0=NULL;
uint32_t * Pi5gpioHW::iobank0=NULL;
uint32_t * Pi5gpioHW::iobank0pads=NULL;
uint32_t * Pi5gpioHW::rio0=NULL;
uint32_t * Pi5gpioHW::rio0_set=NULL;
uint32_t * Pi5gpioHW::rio0_clr=NULL;
uint32_t * Pi5gpioHW::rio0_xor=NULL;


int Pi5gpioHW::setIOMap()
{
   const char *fname = "/sys/bus/pci/devices/0000:01:00.0/resource1";
   int fd;
   if (-1 == (fd = open(fname, O_RDWR | O_SYNC)))
      {
       cout << "iomap1" << endl;
       throw system_error(EIO,generic_category());
       return(0);
      }
   // 0x400000 is the size in bytes of the "resource1" sysfs file
   base =  mmap(NULL, 0x400000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   if (base == MAP_FAILED)
      {
       cout << "map failed" << endl;
       throw system_error(EIO,generic_category());
       return(0);
      }
   if (-1 == close(fd))
     {
       cout << "map category" << endl;
       throw system_error(EIO,generic_category());
      return(0);
     }
   iobank0 = (uint32_t *)((uint8_t *) base + OFFSET_IOBANK0);
   iobank0pads = (uint32_t *)((uint8_t *) base + OFFSET_IOBANK0PADS);
   rio0 = (uint32_t *)((uint8_t *) base + OFFSET_RIO0); // real gpio output not used
   rio0_set = (uint32_t *)((uint8_t *) base + OFFSET_RIO0 + RIO_SET); // real gpio output not used
   rio0_clr = (uint32_t *)((uint8_t *) base + OFFSET_RIO0 + RIO_CLR); // real gpio output not used
   rio0_xor = (uint32_t *)((uint8_t *) base + OFFSET_RIO0 + RIO_XOR); // real gpio output not used
 return 1;
}

void  Pi5gpioHW::releaseIOMap()
{
  if(base)
    munmap(base,0x400000);
base = NULL;
iobank0=NULL;
iobank0pads=NULL;
rio0=NULL;
rio0_clr=NULL;
rio0_xor=NULL;
rio0_set=NULL;
}

Pi5gpioHW::Pi5gpioHW()
{
    if(Pi5gpioHW::base==NULL)
      setIOMap();
}

Pi5gpioHW::~Pi5gpioHW()
{
  releaseIOMap();
}



void Pi5gpioHW::PinMode(int Pin,int pad,  int mode, int rioDrive)
{
   int temp= 1 << Pin;
   iobank0[1+(Pin*2)]= mode;
   iobank0pads[1+Pin]= pad;
   if(rioDrive)
     rio0_set[1]=temp;
   else
     rio0_clr[1]=temp;

}


void Pi5gpioHW::getPinMode(int Pin, int &pad, int &mode,int &rioDrive)
{
   int temp = 1 << Pin;
   mode = iobank0[1+(Pin*2)];
   pad =iobank0pads[1+Pin];
   rioDrive = rio0[1] & temp;

}

int Pi5gpioHW::readDigital(int Pin)
{
   uint32_t  temp = 1 << Pin;

   return (*rio0 & temp) ? 1 : 0;
}


void Pi5gpioHW::writeDigital(int Pin, int value)
{

   uint32_t  temp = 1 << Pin;
   if(value)
       rio0_set[0]=temp;
   else
       rio0_clr[0]=temp;
}

void Pi5gpioHW::toggleDigital(int Pin)
{
   uint32_t  temp = 1 << Pin;
   rio0_xor[0] = temp;
}

