/**
 ******************************************************************************
 * @file    kniffel.c
 * @author  Franz Korf
 *          HAW-Hamburg
 *          Labor fuer technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.1
 *
 * @date    20. Jan. 2025
 * @brief   Dieses Modul speichert den Zustand der W�rfel.
 *
 ******************************************************************************
 */

#include "kniffel.h"
#include "main.h"
#include "random.h"
#include <stdlib.h>

static int arr[NO_DICE] = {1, 1, 1, 1, 1}; // speichert die Augenzahlen
static int rra = 0;                        // speicher ob fixiert

/**
 * @brief Diese Funktion liefert den aktuellen Wert eines W�rfels.
 *
 * @param  die Der Würfel, dessen Wert bestimmt wird.
 *
 * @retval Der Wert des Würfels.
 */
uint8_t getDie(uint8_t die) { return arr[die]; }

/**
 * @brief Diese Funktion überprüft, ob alle Würfel den Wert 1 haben - also
 * ein Kniffel vorliegt.
 *
 * @retval true gdw. ein Kniffel liegt vor.
 */
bool isKniffel(void) {
  for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
    if (arr[i] != arr[0]) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Diese Funktion überprüft, ob die Werte der Würfel eine Strasse ergeben
 *        also eintweder 1 2 3 4 5 oder 2 3 4 5 6 sind.
 *                       2 4 3 5 1
 * @retval true gdw. eine Strasse liegt vor.
 */
bool isStreet(void) {
  /* int ass[6] = {0};
  for (int i = 0; i < NO_DICE; i++) {
    ass[getDie(i) - 1]++;
  }
   for (int j = 0; j < 6; j++) {
    if (ass[j] > 1) {
      return false;
    }
  }

  return true; */
  int ass[6] = {0};

  for (int i = 0; i < NO_DICE; i++) {
    int v = getDie(i);
    if (v < 1 || v > 6)
      return false;
    ass[v - 1]++;
    if (ass[v - 1] > 1)
      return false; // Duplikat sofort killen
  }

  // Prüfe 1-5 oder 2-6
  int sum1 = ass[0] + ass[1] + ass[2] + ass[3] + ass[4];
  int sum2 = ass[1] + ass[2] + ass[3] + ass[4] + ass[5];

  return (sum1 == 5) || (sum2 == 5);
}

/**
 * @brief Diese Funktion fixiert den Würfel mit der Nummer die. Ein fixierter
 *        Würfel wird beim nächsten Wurf nicht geworfen / gewürfelt.
 *
 * @param  die Die Nummer des Würfels, der fixiert wird.
 */
void fixDie(uint8_t die) { rra |= 1 << die; }

/**
 * @brief Diese Funktion löst die Fixierung aller Würfel auf, so dass alle
 *        Würfel beim nüchsten Wurf mit gewürfelt werden.
 */
void releaseDice(void) { rra = 0; }

/**
 * @brief Diese Funktion überprüft, ob der Würfel mit der Nummer die fixiert
 * ist.
 *
 * @param  die Die Nummer des Würfels, der überprüft wird.
 *
 * @retval true gdw. der Würfel mit der Nummer die ist fixiert.
 */
bool isFixed(uint8_t die) { return rra & (1 << die); }

/**
 * @brief Diese Funktion würfelt die Würfel, die nicht fixiert sind. Somit
 *        erhalten diese Würfel einen neuen Wert.
 */
void rollDice(void) {
  for (int i = 0; i < NO_DICE; i++) {
    if (!isFixed(i)) {
      arr[i] = abs(nxtRandNumber() % 6) + 1;
    }
  }
}

// EOF