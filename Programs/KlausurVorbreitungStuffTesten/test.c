// tests.c
#include <stdint.h>
#include "io.h"
#include "delay.h"
#include "test.h"

// Kurzes Blink-Signal
static void blinkAll(uint8_t times)
{
    for (uint8_t i = 0; i < times; i++) {
        io_ledAllOn();
        delay(200);
        io_ledAllOff();
        delay(200);
    }
}

// -----------------------------------------------------
// TEST 1: LED-Hardwaretest (läuft komplett ohne Buttons)
// Erwartung: LEDs laufen der Reihe nach durch
// -----------------------------------------------------
void test_leds_chase(void)
{
    io_init();
    io_ledAllOff();

    while (1) {
        for (uint8_t i = 0; i < 15; i++) {
            io_ledAllOff();
            io_ledSet(i, 1);
            delay(150);
        }
        blinkAll(2);
    }
}

// -----------------------------------------------------
// TEST 2: Buttons roh -> LEDs spiegeln
// Erwartung: Drückst du Si, geht LED i an.
// (i=0..7 => D8..D15), (i=8..14 existiert nicht als Button)
// -----------------------------------------------------
void test_buttons_raw_mirror(void)
{
    io_init();

    while (1) {
        uint8_t b = io_buttonsRaw();     // bit0..bit7
        // spiegel auf LED 0..7
        io_ledWriteMask((uint16_t)b);
        delay(20);
    }
}

// -----------------------------------------------------
// TEST 3: Debounced Mirror (Prof-Hinweis: Gruppe stabil)
// Erwartung:
// - kurze Prell-Spikes sollen nicht als Flackern sichtbar sein
// - stable Wert wird angezeigt
// -----------------------------------------------------
void test_buttons_debounced_mirror(void)
{
    io_init();

    uint8_t stable = 0;

    while (1) {
        stable = io_buttonsDebounced(stable);
        io_ledWriteMask((uint16_t)stable);
        delay(20);
    }
}

// -----------------------------------------------------
// TEST 4: "Bargraph" abhängig von Anzahl gedrückter Buttons
// Erwartung: je mehr Buttons gedrückt, desto mehr LEDs an (0..8 LEDs)
// -----------------------------------------------------
static uint8_t popcount8(uint8_t x)
{
    uint8_t c = 0;
    for (uint8_t i = 0; i < 8; i++) {
        c += (uint8_t)((x >> i) & 1u);
    }
    return c;
}

void test_buttons_to_bar(void)
{
    io_init();

    uint8_t stable = 0;

    while (1) {
        stable = io_buttonsDebounced(stable);
        uint8_t n = popcount8(stable); // 0..8

        // Bar auf LEDs 0..(n-1)
        uint16_t mask = 0;
        for (uint8_t i = 0; i < n; i++) mask |= (1u << i);

        io_ledWriteMask(mask);
        delay(20);
    }
}

// -----------------------------------------------------
// TEST 5: Pressed-Events (jede Taste toggelt eigene LED)
// Erwartung: Ein Druck toggelt genau einmal (nicht mehrfach beim Prellen)
// -----------------------------------------------------
void test_pressed_toggles_leds(void)
{
    io_init();

    uint8_t stable = 0;
    uint8_t prevStable = 0;
    uint16_t ledState = 0;

    while (1) {
        prevStable = stable;
        stable = io_buttonsDebounced(stable);

        // Rising edges auf bits 0..7
        uint8_t rising = (uint8_t)((~prevStable) & stable);

        for (uint8_t i = 0; i < 8; i++) {
            if ((rising >> i) & 1u) {
                ledState ^= (1u << i); // toggle LED i
            }
        }

        io_ledWriteMask(ledState);
        delay(20);
    }
}
