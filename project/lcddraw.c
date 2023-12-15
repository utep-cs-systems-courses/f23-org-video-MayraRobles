/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"


/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}


/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

/** Draw robot
 *  It draws a cool little robot
 */
void drawRobot()
{
  fillRectangle(45, 55, 40, 10, COLOR_RED);    // Body
  fillRectangle(48, 65, 34, 35, COLOR_RED);    // Body
  fillRectangle(50, 19, 28, 28, COLOR_RED);    // Head
  fillRectangle(59, 47, 11, 9, COLOR_PINK);    // Neck
  fillRectangle(85, 55, 10, 40, COLOR_YELLOW); // Right arm
  fillRectangle(35, 55, 10, 40, COLOR_YELLOW); // Left arm
  fillRectangle(50, 100, 12, 15, COLOR_FOREST_GREEN); // Left leg
  fillRectangle(67, 100, 12, 15, COLOR_FOREST_GREEN); // Right leg
  fillRectangle(52, 115, 9, 18, COLOR_GREEN);  // Left leg p2
  fillRectangle(68, 115, 9, 18, COLOR_GREEN);  // Right leg p2
  fillRectangle(46, 133, 15, 8, COLOR_RED);    // Left foot
  fillRectangle(68, 133, 15, 8, COLOR_RED);    // Right foot
  fillRectangle(42, 25, 8, 15, COLOR_GREEN);   // Left ear
  fillRectangle(78, 25, 8, 15, COLOR_GREEN);   // Right ear
  fillRectangle(59, 38, 10, 4, COLOR_BLACK);   // Mouth
  fillRectangle(54, 25, 8, 8, COLOR_BLACK);    // Left eye
  fillRectangle(67, 25, 8, 8, COLOR_BLACK);    // Right eye
}

/*
 * Draw little squares in the background
 */
void drawStarryBackground1()
{
  fillRectangle(5, 5, 4, 4, COLOR_WHITE);
  fillRectangle(15, 8, 4, 4, COLOR_BLUE);
  fillRectangle(90, 5, 4, 4, COLOR_WHITE);
  fillRectangle(5, 100, 4, 4, COLOR_BLUE);
  fillRectangle(100, 100, 4, 4, COLOR_WHITE);
  fillRectangle(10, 50, 4, 4, COLOR_BLUE);
  fillRectangle(110, 20, 4, 4, COLOR_WHITE);
  fillRectangle(120, 150, 4, 4, COLOR_BLUE);
  fillRectangle(30, 120, 4, 4, COLOR_WHITE);
  fillRectangle(150, 140, 4, 4, COLOR_BLUE);
  fillRectangle(25, 140, 4, 4, COLOR_WHITE);
  fillRectangle(100, 140, 4, 4, COLOR_BLUE);
  fillRectangle(115, 70, 4, 4, COLOR_WHITE);
}

/*
 * Draw littles squared in the background
 */
void drawStarryBackground2()
{
  fillRectangle(5, 5, 4, 4, COLOR_BLUE);
  fillRectangle(15, 8, 4, 4, COLOR_WHITE);
  fillRectangle(90, 5, 4, 4, COLOR_BLUE);
  fillRectangle(5, 100, 4, 4, COLOR_WHITE);
  fillRectangle(100, 100, 4, 4, COLOR_BLUE);
  fillRectangle(10, 50, 4, 4, COLOR_WHITE);
  fillRectangle(110, 20, 4, 4, COLOR_BLUE);
  fillRectangle(120, 150, 4, 4, COLOR_WHITE);
  fillRectangle(30, 120, 4, 4, COLOR_BLUE);
  fillRectangle(150, 140, 4, 4, COLOR_WHITE);
  fillRectangle(25, 140, 4, 4, COLOR_BLUE);
  fillRectangle(100, 140, 4, 4, COLOR_WHITE);
  fillRectangle(115, 70, 4, 4, COLOR_BLUE);
}

/*
 * Show a dramatic Nietzsche quote
 */
void nietzscheDramaticQuote()
{
  drawString5x7(8, 45, "HE WHO HAS A WHY", COLOR_BLACK, COLOR_YELLOW);
  drawString5x7(8, 65, "TO LIVE FOR CAN BEAR", COLOR_BLACK, COLOR_YELLOW);
  drawString5x7(8, 85, "ALMOST ANY HOW", COLOR_BLACK, COLOR_YELLOW);
}


/*
 * Draws circles
 */
void drawCircle(short row, short col, u_int r, u_int colorBGR)
{
  int sr = 0;
  for (int j = 1; j <=r; j++)
    sr += j;
  int x = r;
  int y = 0;
  int sx = sr;
  int sy = 0;
  while (y <= (r/2)) { // rows less than r/2
    drawPixel(x+col, y+row, colorBGR);
    drawPixel(x+col, -y+row, colorBGR);
    drawPixel(-x+col, y+row, colorBGR);
    drawPixel(-x+col, -y+row, colorBGR);
    drawPixel(y+col, x+row, colorBGR);
    drawPixel(y+col, -x+row, colorBGR);
    drawPixel(-y+col, x+row, colorBGR);
    drawPixel(-y+col, -x+row, colorBGR);
    y+=1; sy+=y;
    if ((sx + sy) > sr) { // if outside the circle
      sx -= x;  x -= 1;  // decrease x
    }
  }
}
