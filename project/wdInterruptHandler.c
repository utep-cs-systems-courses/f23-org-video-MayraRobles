#include <msp430.h>
#include "buzzer.h"
#include "led.h"
#include "lcddraw.h"
#include "lcdutils.h"
#include "switches.h"
#include "stateMachines.h"

char button_sequence_state = -1;

void
__interrupt_vec(WDT_VECTOR) WDT(){ /* 250 interrupts/sec */
  static int secondCount = 0;
  secondCount ++;
   
  switch(button_sequence_state) {
  case 0:
    if(secondCount >= 35) {
      canon_in_D_state_advance();
      secondCount = 0;
    }
    break;
  case 2:
    if(secondCount >= 62) {
      siren_state_advance();
      secondCount = 0;
    }
    break;
  }
}
