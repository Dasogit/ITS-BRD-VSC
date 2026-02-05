/**
 * @file model.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-02-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef _MODEL_H
#define _MODEL_H
#include <stdbool.h>
#include <stdint.h>

typedef enum {CMD_RED = 0, CMD_BLUE = 1, CMD_GREEN = 2 } DrawCMD;

void model_init(void);

void model_on_button_event(uint8_t pressedMask);

bool model_s7(void);
bool model_nextDraw(DrawCMD *cmd, uint16_t *number);
void model_clears7(void);

#endif