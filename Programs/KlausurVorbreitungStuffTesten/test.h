// tests.c

#ifndef _TEST_H
#define _TEST_H


// -----------------------------------------------------
// TEST 1: LED-Hardwaretest (läuft komplett ohne Buttons)
// Erwartung: LEDs laufen der Reihe nach durch
// -----------------------------------------------------
void test_leds_chase(void);

// -----------------------------------------------------
// TEST 2: Buttons roh -> LEDs spiegeln
// Erwartung: Drückst du Si, geht LED i an.
// (i=0..7 => D8..D15), (i=8..14 existiert nicht als Button)
// -----------------------------------------------------
void test_buttons_raw_mirror(void);
// -----------------------------------------------------
// TEST 3: Debounced Mirror (Prof-Hinweis: Gruppe stabil)
// Erwartung:
// - kurze Prell-Spikes sollen nicht als Flackern sichtbar sein
// - stable Wert wird angezeigt
// -----------------------------------------------------
void test_buttons_debounced_mirror(void);

void test_buttons_to_bar(void);


// -----------------------------------------------------
// TEST 5: Pressed-Events (jede Taste toggelt eigene LED)
// Erwartung: Ein Druck toggelt genau einmal (nicht mehrfach beim Prellen)
// -----------------------------------------------------
void test_pressed_toggles_leds(void);


#endif
// EOP