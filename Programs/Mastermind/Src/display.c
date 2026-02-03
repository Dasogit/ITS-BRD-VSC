/**
 * @file display.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-01-31
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "display.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "keypad.h"
#include "terminal.h"

static Terminal t;

/**
 * @brief Diese Funktion initialisiert das LCD Display, die Touch
 * Funktionalitaet und das KeyPad.
 */
void initDisplay(void) { t = makeKeyPad(); }

/**
 * @brief Diese Funktion gibt einen farbigen String auf KeyPad-Terminal aus.
 *
 * @param  s String, der ausgegeben wird.
 *
 * @param  c Textfarbe des zu druckende Strings.
 */
void printStr(char *s, COLOR c) {
  setTextColorTerm(c, &t);
  printTerm(s, &t);
}

/**
 * @brief Diese Funktion loescht das KeyPad-Terminal.
 */
void clearDisplay(void) { clearTerm(&t); }

/**
 * @brief Diese Funktion liest die nächste Eingabe vom KeyPad.
 * Sie kann eine genau size Zeichen lange Zahl sein oder eine der Reset
 * Eingaben (C oder *). Ein Reset-Key (C oder *) kann an beliebiger Stelle
 * stehen und beendet sofort die Eingabe. Eine Zahl wird mit dem Enter-Key (Key
 * ohne Aufschrift) abgeschlossen. Während des Eingabeprozesses werden alle
 * nicht gueltigen Zeichen verworfen. Werden mehr als size Ziffern eingegeben,
 * werden die überzähligen auch verworfen. Die gültigen eingegebenen Ziffer '0'
 * bis '9' werden auf dem KeyPad-Terminal ausgegeben.
 *
 * @param resetOnly = true: Als Eingabe wird nur ein Reset-Key akzeptiert.
 * Dies wird z.B. benoetigt, wenn das Spiel beendet ist und der Spieler nur einen Reset-Key eingeben darf.
 *
 * @param size Laenge des Felds a und somit Anzahl der Ziffern, die eingelesen
 * werden.
 *
 * @param a Feld der Laenge size. Die Ziffern (0 bis 9) der eingelesenen Zahl werden in diesem Feld zuueckgegeben.
 *
 * @retval RESET_KEY, RESET_AND_HELP_KEY oder NEXT_GUESS_READ (s. defines)
 */
char nextInput(bool resetOnly, int size, uint8_t *a) {
  int index = 0;

  /* if (sizeof(input) != sizeof(size) || input != RESET_KEY ||
      input != RESET_AND_HELP_KEY || input != NEXT_GUESS_READ) {
  }
 */
  for (;;) {
    char input = getKeyPadInput();
    if (resetOnly) {
      if (input == RESET_KEY || input == RESET_AND_HELP_KEY) {
        return input;
      }
    } else {
      if (input == RESET_KEY || input == RESET_AND_HELP_KEY) {
        return input;
      } else if (input >= '0' && input <= '9') {
        if (index < size) {
          printChar('\n', &t);
          printChar(input, &t);
          a[index] = input - '0';
          ++index;
        } else if(index >= size){
          continue;
        }
      } else if (input == NEXT_GUESS_READ) {
        if (index == size) {
          return input;
        }
      }
    }
  }
}
// EOF