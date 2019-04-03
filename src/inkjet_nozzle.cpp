#include "inkjet_nozzle.h"
#include "Configuration.h"

long lastPulse = 0;
uint16_t strip_buffer = 4096;

void hpc6602_init(){
  
  #if defined(INK_PINA) && INK_PINA > -1
    SET_OUTPUT(INK_PINA);
  #endif
  #if defined(INK_PINB) && INK_PINB > -1
    SET_OUTPUT(INK_PINB);
  #endif
  #if defined(INK_PINC) && INK_PINC > -1
    SET_OUTPUT(INK_PINC);
  #endif
  #if defined(INK_PIND) && INK_PIND > -1
    SET_OUTPUT(INK_PIND);
  #endif
  #if defined(INK_PULSE0)
    SET_OUTPUT(INK_PULSE0);
  #endif

}



void nozzle_trigger(const uint16_t &strip_code)
{  
  if(micros() - lastPulse >= DEATH_PULSE_RATE && strip_code < 4096){
    for (byte n = 0; n <= 11; n++)
    {
      if (strip_code & 1<<n)
      {
        if(n & 1<<0)
          WRITE(INK_PINA, 1);
        if(n & 1<<1)
          WRITE(INK_PINB, 1);
        if(n & 1<<2)
          WRITE(INK_PINC, 1);
        if(n & 1<<3)
          WRITE(INK_PIND, 1);

                //Fire the Nozzle
      WRITE(INK_PULSE0, HIGH);
      delayMicroseconds(5);
      //Set everything low
      WRITE(INK_PULSE0, LOW);
      WRITE(INK_PINA, 0);
      WRITE(INK_PINB, 0);
      WRITE(INK_PINC, 0);
      WRITE(INK_PIND, 0);
      }
    }
    lastPulse = micros();
  }
}
