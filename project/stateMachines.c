#include <msp430.h> 
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"
#include "notes.h"

static int cur_note = 0;

// void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
//		   u_int colorBGR)

void rectangle_inside_rectangle_advace()
{
  static char cur_state = 0;
  
  switch(cur_state) {
  case 0:
    fillRectangle(10,10,50,100, COLOR_GREEN);
    cur_state ++;
    break;
  case 1:
    fillRectangle(20,20,30,90, COLOR_BLUE);
    cur_state ++;
    break;
  case 2:
    fillRectangle(20,20,30,90, COLOR_PINK);
    cur_state++;
    break;
  case 3:
    fillRectangle(20,20,30,90, COLOR_YELLOW);
    cur_state ++;
    break;
  case 4:
    fillRectangle(20,20,30,90, COLOR_ORANGE);   
    cur_state ++;
    break;
  default:
    cur_state = 0;
    break;  
}


void rectangles_two_notes_state_advance()
{
  static char cur_state = 1;

  if (cur_state == 1){
    buzzer_set_period(A5);
    rectangle_inside_rectangle_advace;
    cur_state ++;
  } else if (cur_state == 2){
    buzzer_set_period(G5);
    rectangle_inside_rectangle_advace;
    cur_state = 1;
  }
}
 

void dim_green_state_advance()
{
  static int count = 0;
  static int blinkLimitGreen = 7;  // duty cycle = 1/blinkLimit
  static int blinkCountGreen = 0;  // cycles 0...blinkLimit-1

  count ++;
  blinkCountGreen ++;
  
  if (blinkCountGreen >= blinkLimitGreen) { // on for 1 interrupt period
    blinkCountGreen = 0;
    green_on = 1;
  } else {          // off for blinkLimit - 1 interrupt periods
     green_on = 0;
  }
   
  if (count >= 500) {  // once each two seconds, to make brightness patterns change slower
    count = 0;
    blinkLimitGreen --; // increase duty cycle to go from dim-to-bright
    if (blinkLimitGreen <= 0)    
      blinkLimitGreen = 7;
  }
  led_update();  
}


void dim_red_state_advance()
{
  static int count = 0;
  static int blinkLimitRed = 0;
  static int blinkCountRed = 0;
 
  count ++;
  blinkCountRed ++;
  if (blinkCountRed >= blinkLimitRed) { // on for 1 interrupt period
    blinkCountRed = 0;
    red_on = 1;
  } else            // off for blinkLimit - 1 interrupt periods
    red_on = 0;

  if (count >= 500) {  // once each two seconds, to make brightness patterns change slower
    count = 0;
    blinkLimitRed ++;   // decrease duty cycle to go from bright-to-dim
    if (blinkLimitRed >= 5)
      blinkLimitRed = 0;       
  }
  led_update();
}


void red_green_toggle_state_advance()
{
  enum State {RED, GREEN};
  static enum State cur_state = RED;

  if (cur_state == RED){
    red_on = 1;
    green_on = 0;
    buzzer_set_period(A5);
    cur_state = GREEN;
  } else if (cur_state == GREEN){
    green_on = 1;
    red_on = 0;
    buzzer_set_period(G5);
    cur_state = RED;
  }
   led_update();
}

void siren_state_advance()
{
  static char siren_state = 0;
  static int cur_cycle = 500;
  
  switch(siren_state) {
  case 0:
    green_on = 1;
    red_on = 0;
    cur_cycle = 500;
    siren_state ++;
    break;
  case 1:
  case 2:
    green_on = 0;
    red_on = 1 ;
    cur_cycle += 300;
    siren_state ++;
    break;
  case 3:
  case 4:
    cur_cycle += 400;
    siren_state ++;
    break;
  case 5:
  case 6:
    siren_state++;
    break;
  case 7:
  case 8:
    green_on = 1;
    red_on = 0;
    cur_cycle -= 500;
    siren_state ++;
    break;
  case 9:
    cur_cycle -= 300;
    siren_state ++;
    break;
  case 10:
    cur_cycle -= 200;
    siren_state = 0;
    break;
  }
  led_update();
  buzzer_set_period(cur_cycle);
}  


void binary_count_state_advance()
  {
  static int binary_count_state = 0;

  binary_count_state = (binary_count_state + 1) % 4; // Increment binary count and take modulo

   switch (binary_count_state) {
  case 0:
    red_on = 0;
    green_on = 0;
    break;
  case 1:
    red_on = 0;
    green_on = 1;
    break;
  case 2:
    red_on = 1;
    green_on = 0;
    break;
  case 3:
     red_on = 1;
    green_on = 1;
    break;
  }
}
 

void update_blink_and_buzz(int frequency)
{
  buzzer_set_period(frequency);
  //binary_count_state_advance();
  //led_update();
  cur_note ++;
}
 

void canon_in_D_state_advance() /* Plays canon in D */
{ 
  switch (cur_note) {
  case 0:
    update_blink_and_buzz(A5);
    break;
  case 1:
    update_blink_and_buzz(0);
    break;
  case 2:
    update_blink_and_buzz(F5_SHARP);
    break;
  case 3:
    update_blink_and_buzz(0);
    break;
  case 4:
    update_blink_and_buzz(G5);
    break;
  case 5:
    update_blink_and_buzz(0);
    break;
  case 6:
    update_blink_and_buzz(A5);
    break;
  case 7:
    update_blink_and_buzz(0);
    break;
  case 8:
    update_blink_and_buzz(F5_SHARP);
    break;
  case 9:
    update_blink_and_buzz(0);
    break;
  case 10:
    update_blink_and_buzz(G5);
    break;
  case 11:
    update_blink_and_buzz(0);
    break;
  case 12:
    update_blink_and_buzz(A5);
    break;
  case 13:
    update_blink_and_buzz(0);
    break;
  case 14:
    update_blink_and_buzz(A4);
    break;
  case 15:
    update_blink_and_buzz(0);
    break;
  case 16:
    update_blink_and_buzz(B4);
    break;
  case 17:
    update_blink_and_buzz(0);
    break;
  case 18:
    update_blink_and_buzz(Db5);
    break;
  case 19:
    update_blink_and_buzz(0);
    break;
  case 20:
    update_blink_and_buzz(D5);
    break;
  case 21:
    update_blink_and_buzz(0);
    break;
  case 22:
    update_blink_and_buzz(E5);
    break;
  case 23:
    update_blink_and_buzz(0);
    break;
  case 24:
    update_blink_and_buzz(F5_SHARP);
    break;
  case 25:
    update_blink_and_buzz(0);
    break;
  case 26:
    update_blink_and_buzz(G5);
    break;
  case 27:
    update_blink_and_buzz(0);
    break;
  case 28:
    update_blink_and_buzz(F5_SHARP);
    break;
  case 29:
    update_blink_and_buzz(0);
    break;
  case 30:
    update_blink_and_buzz(D5);  
    break;
  case 31:
    update_blink_and_buzz(0);
    break;
  case 32:
    update_blink_and_buzz(E5);
    break;
  case 33:
    update_blink_and_buzz(0);
    break;
  case 34:
    update_blink_and_buzz(F5_SHARP);
    break;
  case 35:
    update_blink_and_buzz(0);
    break;
  case 36:
    update_blink_and_buzz(F4_SHARP);
    break;
  case 37:
    update_blink_and_buzz(0);
    break;
  case 38:
    update_blink_and_buzz(G4);
    break;
  case 39:
    update_blink_and_buzz(0);
    break;
  case 40:
    update_blink_and_buzz(A4);
    break;
  case 41:
    update_blink_and_buzz(0);
    break;
  case 42:
    update_blink_and_buzz(B4);
    break;
  case 43:
    update_blink_and_buzz(0);
    break;
  case 44:
    update_blink_and_buzz(A4);
    break;
  case 45:
    update_blink_and_buzz(0);
    break;
  case 46:
    update_blink_and_buzz(G4);
    break;
  case 47:
    update_blink_and_buzz(0);
    break;
  case 48:
    update_blink_and_buzz(A4);
    break;
  case 49:
    update_blink_and_buzz(0);
    break;
  case 50:
    update_blink_and_buzz(F4_SHARP);
    break;
  case 51:
    update_blink_and_buzz(0);
    break;
  case 52:
    update_blink_and_buzz(G4);
    break;
  case 53:
    update_blink_and_buzz(0);
    break;
  case 54:
    update_blink_and_buzz(A4);
    break;
  case 55:
    update_blink_and_buzz(0);
    break;
  case 56:
    update_blink_and_buzz(G4);
    break;
  case 57:
    update_blink_and_buzz(0);
    break;
  case 58:
    update_blink_and_buzz(B4);
    break;
  case 59:
    update_blink_and_buzz(0);
    break;
  case 60:
    update_blink_and_buzz(A4);
    break;
  case 61:
    update_blink_and_buzz(0);
    break;
  case 62:
    update_blink_and_buzz(G4);
    break;
  case 63:
    update_blink_and_buzz(0);
    break;
  case 64:
    update_blink_and_buzz(F4_SHARP);
    break;
  case 65:
    update_blink_and_buzz(0);
    break;
  case 66:
    update_blink_and_buzz(E4);
    break;
  case 67:
    update_blink_and_buzz(0);
    break;
  case 68:
    update_blink_and_buzz(F4_SHARP);
    break;
  case 69:
    update_blink_and_buzz(0);
    break;
  case 70:
    update_blink_and_buzz(E4);
    break;
  case 71:
    update_blink_and_buzz(0);
    break;
  case 72:
    update_blink_and_buzz(D4);
    break;
  case 73:
    update_blink_and_buzz(0);
    break;
  case 74:
    update_blink_and_buzz(E4);
    break;
  case 75:
    update_blink_and_buzz(0);
    break;
  case 76:
    update_blink_and_buzz(F4_SHARP);
    break;
  case 77:
    update_blink_and_buzz(0);
    break;
  case 78:
    update_blink_and_buzz(G4);
    break;
  case 79:
    update_blink_and_buzz(0);
    break;
  case 80:
    update_blink_and_buzz(A4);
    break;
  case 81:
    update_blink_and_buzz(0);
    break;
  case 82:
    update_blink_and_buzz(B4);
    break;
  case 83:
    update_blink_and_buzz(0);
    break;
  case 84:
    update_blink_and_buzz(G4);
    break;
  case 85:
    update_blink_and_buzz(0);
    break;
  case 86:
    update_blink_and_buzz(B4);
    break;
  case 87:
    update_blink_and_buzz(0);
    break;
  case 88:
    update_blink_and_buzz(A4);
    break;
  case 89:
    update_blink_and_buzz(0);
    break;
  case 90:
    update_blink_and_buzz(B4);
    break;
  case 91:
    update_blink_and_buzz(0);
    break;
  case 92:
    update_blink_and_buzz(Db5);
    break;
  case 93:
    update_blink_and_buzz(0);
    break;
  case 94:
    update_blink_and_buzz(D5);
    break;
  case 95:
    update_blink_and_buzz(0);
    break;
  case 96:
    update_blink_and_buzz(A4);
    break;
  case 97:
    update_blink_and_buzz(0);
    break;
  case 98:
    update_blink_and_buzz(B4);
    break;
  case 99:
    update_blink_and_buzz(0);
    break;
  case 100:
    update_blink_and_buzz(Db5);
    break;
  case 101:
    update_blink_and_buzz(0);
    break;
  case 102:
    update_blink_and_buzz(D5);
    break;
  case 103:
    update_blink_and_buzz(0);
    break;
  case 104:
    update_blink_and_buzz(E5);
    break;
  case 105:
    update_blink_and_buzz(0);
    break;
  case 106:
    update_blink_and_buzz(F5_SHARP);
    break;
  case 107:
    update_blink_and_buzz(0);
    break;
  case 108:
    update_blink_and_buzz(G5);
    break;
  case 109:
    update_blink_and_buzz(0);
    break;
  case 110:
    update_blink_and_buzz(A5);
    break;
  case 111:
    update_blink_and_buzz(0);
    cur_note = 0;
    break;
  } 
}
