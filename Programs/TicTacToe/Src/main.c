#include "LCD_Demos.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "TFT_board.h"
#include "delay.h"
#include "error.h"
#include "fontsFLASH.h"
#include "init.h"
#include "io.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"
#include "test.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


static int checkWinner(int map[9]) {
  for (int i = 0; i <= 6; i += 3) {
    if (map[i] != 0 && map[i] == map[i + 1] && map[i + 1] == map[i + 2]) {
      return map[i];
    }
  }
  for (int i = 0; i < 3; i++) {
    if (map[i] != 0 && map[i] == map[i + 3] && map[i + 3] == map[i + 6]) {
      return map[i];
    }
  }
  if (map[4] != 0) {
    if (map[0] == map[4] && map[4] == map[8])
      return map[4];
    if (map[2] == map[4] && map[4] == map[6])
      return map[4];
  }
  return 0;
}

static bool boardFull(int map[9]) {
  for (int i = 0; i < 9; i++) {
    if (map[i] == 0)
      return false;
  }
  return true;
}

int main(void) {
  initITSboard();
  GUI_init(DEFAULT_BRIGHTNESS);
  TP_Init(false);

  if (!checkVersionFlashFonts()) {
    Error_Handler();
  }

  // testIO();
  // testBoard();
  // testTouch();

#if 0
  while (1) {
    int map[9] = {0,0,0,0,0,0,0,0,0};
    int currentPlayer = 1; // 1 = Kreis (grün), 2 = Quadrat (blau)
    int winner = 0;

    drawNewBoard();

    while (1) {
      // Reset jederzeit
      if (buttonPressed(0)) {
        break; // neues Spiel
      }

      // Wenn GameOver: Touch ignorieren, nur auf Reset warten
      if (winner != 0) {
        continue;
      }

      // Unentschieden: ebenfalls GameOver-Phase (nur Reset)
      if (winner == 0 && boardFull(map)) {
        // optional: irgendein LED-Muster fürs Draw
        // z.B. beide Farben oder alles aus/an
        // Hier: alles an als "fertig"
        switchLEDsOn(0xFFFF);
        winner = -1; // markiere "game over" (draw)
        continue;
      }

      // "Am Zug" LEDs anzeigen (vor Touch)
      switchLEDsOff(0xFFFF);
      if (currentPlayer == 1) {
        // Player 1: grün D20-D23 => OUT12-OUT15 => 0xF000
        switchLEDsOn(0xF000);
      } else {
        // Player 2: blau D8-D11 => OUT0-OUT3 => 0x000F
        switchLEDsOn(0x000F);
      }

      // Auf gültigen Touch warten
      int pos = -1;
      while (pos == -1) {
        if (buttonPressed(0)) break;   // Reset bricht warten ab
        pos = getTouch();
      }
      if (buttonPressed(0)) {
        break;
      }

      // Feld belegt: ignorieren, kein Spielerwechsel
      if (pos < 0 || pos > 8) {
        continue;
      }
      if (map[pos] != 0) {
        continue;
      }

      // Zug ausführen + zeichnen
      map[pos] = currentPlayer;
      if (currentPlayer == 1) {
        drawCycle(pos); // grün
      } else {
        drawQuad(pos);  // blau
      }

      // Gewinner prüfen
      winner = checkWinner(map);
      if (winner == 1) {
        // Player 1 gewonnen: grün D16-D23 => OUT8-OUT15 => 0xFF00
        switchLEDsOff(0xFFFF);
        switchLEDsOn(0xFF00);
        // ab jetzt: winner != 0 => Touch wird ignoriert, nur Reset
      } else if (winner == 2) {
        // Player 2 gewonnen: blau D8-D15 => OUT0-OUT7 => 0x00FF
        switchLEDsOff(0xFFFF);
        switchLEDsOn(0x00FF);
      } else {
        // kein Gewinner: Spieler wechseln
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
      }

      delay(150); // kleines Debounce/Anti-Doppeltap, nicht riesig
    }
  }
#endif

  int map[9] = {0};
  int currentPlayer = 1; // 1 = Kreis (grün), 2 = Quadrat (blau)
  int winner = 0;

  drawNewBoard();

  for (;;) {
    bool draw = false;
    int ledState = 0;

    // == Read input ==
    bool resetGame = buttonPressed(0);
    int pos = getTouch();

    // == Calculation ==
    if (resetGame) {
      memset(map, 0, sizeof(map));
      winner = 0;
      currentPlayer = 1;
    }

    if (winner == 0 && pos >= 0 && map[pos] == 0) {
      map[pos] = currentPlayer;
      winner = checkWinner(map);
      currentPlayer = (currentPlayer == 1) ? 2 : 1;
      draw = true;
    }

    if (winner == 1) {
      ledState = 0xFF00; // Player 1 gewonnen: D16-D23 an
    } else if (winner == 2) {
      ledState = 0x00FF; // Player 2 gewonnen: D8-D15 an
    } else if (winner == 0 && boardFull(map)) {
      ledState = 0xFFFF; // Alle LEDs an
      winner = -1;       // Unentschieden
    } else if (currentPlayer == 1) {
      ledState = 0xF000; // Player 1 am Zug: D20-D23 an
    } else if (currentPlayer == 2) {
      ledState = 0x000F; // Player 2 am Zug: D8-D11 an
    }

    // == Output ==
    if (resetGame) {
      drawNewBoard();
    }

    if (draw) {
      if (currentPlayer == 1) {
        drawCycle(pos); // grün
      } else if (currentPlayer == 2) {
        drawQuad(pos); // blau
      }
    }

    switchLEDsOff(~ledState);
    switchLEDsOn(ledState);
  }
}
