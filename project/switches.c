#include <msp430.h>
#include "switches.h"
#include "stateMachines.h"
#include "buzzer.h"
#include "lcddraw.h"
#include "lcdutils.h"

char switch_state_down, switch_state_changed; /* effectively boolean */


static char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */
  return p2val;
}


void
switch_init()/* setup switch */
{
  P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE |= SWITCHES;/* enable interrupts from switches */
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */
  switch_update_interrupt_sense();
}

void 
switch_interrupt_handler()
{ 
  __disable_interrupt();
  
  char p2val = switch_update_interrupt_sense();
    
  /* Everytime a button is pressed, change sequence state*/
  if ((p2val & SW1) == 0){ //Button 1 was pressed
    button_sequence_state = 0;
    clearScreen(COLOR_BLUE);
    drawRobot();
  }
  else if ((p2val & SW2) == 0){ //Button 2 was pressed
    button_sequence_state = 1;
    buzzer_set_period(0);
    clearScreen(COLOR_YELLOW);
    nietzscheDramaticQuote();
  }
  else if ((p2val & SW3) == 0){ //Button 3 was pressed
    button_sequence_state = 2;
    clearScreen(COLOR_MAGENTA);
  }
  else if ((p2val & SW4) == 0){ //Button 4 was pressed
    button_sequence_state = 3;
    rectangles_two_notes_state_advance();
  }
  __enable_interrupt();
}


