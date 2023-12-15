#include <msp430.h> 
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"
#include "notes.h"

static int cur_note = 0;

void rectangle_inside_rectangle_advance()
{
  static char cur_state = 0;
  switch(cur_state) {
  case 0:
    clearScreen(COLOR_GREEN);
    cur_state ++;
    break;
  case 1:
    fillRectangle(20, 10, 90, 140, COLOR_BLUE);
    cur_state ++;
    break;
  case 2:
    fillRectangle(35, 20, 62, 120, COLOR_PINK);
    cur_state++;
    break;
  case 3:
    fillRectangle(45, 30, 43, 100, COLOR_YELLOW);
    cur_state ++;
    break;
  case 4:
    fillRectangle(55, 38, 24, 85, COLOR_ORANGE);
    cur_state = 0;
    break;
  default:
    cur_state = 0;
    break;
  }
}

void rectangles_two_notes_state_advance()
{
  static char cur_state = 1;
  if (cur_state == 1){
    buzzer_set_period(A5);
    rectangle_inside_rectangle_advance();
    cur_state ++;
  } else if (cur_state == 2){
    buzzer_set_period(G5);
    rectangle_inside_rectangle_advance();
    cur_state = 1;
  }
}
 

void siren_state_advance()
{
  static char siren_state = 0;
  static int cur_cycle = 500;
  
  switch(siren_state) {
  case 0:
    clearScreen(COLOR_MAGENTA);
    cur_cycle = 500;
    siren_state ++;
    break;
  case 1:
  case 2:
    drawCircle(50, 50, 30, COLOR_RED);
    cur_cycle += 300;
    siren_state ++;
    break;
  case 3:
    drawCircle(90, 70, 10, COLOR_ORANGE);
  case 4:
    drawCircle(50, 130, 20, COLOR_PINK);
    cur_cycle += 400;
    siren_state ++;
    break;
  case 5:
  case 6:
    drawCircle(40, 30, 15, COLOR_BLUE);
    siren_state++;
    break;
  case 7:
  case 8:
    drawCircle(10, 85, 30, COLOR_YELLOW);
    cur_cycle -= 500;
    siren_state ++;
    break;
  case 9:
    drawCircle(140, 80, 40, COLOR_GREEN);
    cur_cycle -= 300;
    siren_state ++;
    break;
  case 10:
    drawCircle(100, 50, 20, COLOR_WHITE);
    cur_cycle -= 200;
    siren_state = 0;
    break;
  }
  
  buzzer_set_period(cur_cycle);
}  

void starsBackgroundStateAdvance()
{
  static char cur_state = 0;

  if(cur_state == 0) {
    drawStarryBackground2();
    cur_state ++;
  } else {
    drawStarryBackground1();
    cur_state = 0;
  }
  
}
 

void update_blink_and_buzz(int frequency)
{
  buzzer_set_period(frequency);
  starsBackgroundStateAdvance();
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
