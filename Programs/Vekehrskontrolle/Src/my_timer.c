/**
 ******************************************************************************
 * @file    my_timer.c
 * @author  <I H R  N A M E>
 * @date    22.01.2020
 * @brief   Dieses Modul implementiert einfache Funktionen zur Behandlung von
 *          Zeitspannen. Es basiert auf dem dem Modul timer, das den Timer TIM2
 *          verwendet.
 ******************************************************************************
 */

// #include "HAW_timer.h"
#include "my_timer.h"
#include "stm32f4xx_hal.h"
#include "timer.h"
#include <stdint.h>

/**
 ******************************************************************************
 * @brief  Diese Funktion initialisiert das Modul.
 *         Insbesondere wird das timer Modul initialisiert.
 *
 * @retval None
 ******************************************************************************/
extern void initMyTimer(void) { initTimer(); }

/**
 ******************************************************************************
 * @brief  Diese Funktion liefert den aktuellen Zeitstempel von TIM2 zurueck.
 *
 * @retval Aktueller Time Stamp von TIM2
 *****************************************************************************/
extern uint32_t getTS(void) {
  return getTimeStamp();
} // Timestamp in Timer-Ticks (wie im Test verwendet)

/**
 ******************************************************************************
 * @brief  Diese Funktion verzoegert die Programmausfuehrung - wartet - fuer
 *         timeInUs Microsekunden.
 *
 * @param  timeInUs Verzoegerungszeit in us
 *
 * @retval Bei fehlerfreier Ausfuehrung wird eine 0 zurueckgegeben. Ist die
 *         Verzoegerungszeit groesser gleich der Zeitspanne, die das
 * Timerregister speichern kann, verzoegert die Funktion nicht und liefert -1
 * zurueck.
 *****************************************************************************/
extern int wait(unsigned int timeInUs) {
  // Guard: "zu groß" erkennen, damit wait(UINT32_MAX) im Test als Fehler
  // erkannt wird. maxUs = maximal darstellbare Tick-Differenz / TICKS_PER_US
  // (Tick-Diff ist uint32_t modulo 2^32)
  if (TICKS_PER_US == 0U) {
    return -1;
  }

  // Wenn timeInUs * TICKS_PER_US nicht in uint32_t passt -> Fehler (würde sonst
  // overflowen)
  if ((uint32_t)timeInUs > (UINT32_MAX / (uint32_t)TICKS_PER_US)) {
    return -1;
  }

  uint32_t start = TIM2->CNT;
  uint32_t ticks = (uint32_t)timeInUs * (uint32_t)TICKS_PER_US;
  while ((uint32_t)(TIM2->CNT - start) < ticks) {
  }
  return 0;
}

/**
 ******************************************************************************
 * @brief  Diese Funktion liefert die Zeitspanne zwischen den Zeitstempeln
 *         ts2 und ts1 in us zurueck.
 *
 * @param  ts1 Zeitstempel des ersten Zeitpunkts.
 *
 * @param  ts2 Zeitstempel des zweiten Zeitpunkts.
 *
 * @retval Zeitspanne zwischen ts1 und ts2 in us.
 *****************************************************************************/
extern uint32_t getTimeSpan(uint32_t ts1, uint32_t ts2) {
  // Test erwartet: Rückgabe in µs (weil danach /1_000_000 -> Sekunden)
  // ts1/ts2 sind Timer-Ticks -> erst Tick-Differenz, dann durch TICKS_PER_US
  // teilen.
  if (TICKS_PER_US == 0U) {
    return 0;
  }

  uint32_t dtTicks = (uint32_t)(ts2 - ts1); // wraparound-safe
  return dtTicks / (uint32_t)TICKS_PER_US;  // -> µs
}
// EOF
