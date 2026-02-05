/**
 * @file controller.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-02-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "controller.h"
#include "LCD_GUI.h"
#include "io.h"

void app_init(void) {}

void app_tick(void) {}

COLOR getColorFromButton() {
  uint16_t c;
  switch (getButton()) {
  case 0:
    c = RED;
    break;
  case 1:
    c = BLUE;
    break;
  case 2:
    c = GREEN;
    break;
  }
  return c;
}