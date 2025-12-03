Warum macht man interne Funktionen static?
1. Weil sie NUR im decoder-Modul gebraucht werden

Beispiel:
putPixelClipped, getColorFromPalette oder decodeRLE8 sind Hilfsfunktionen, die außerhalb des Decoders niemand braucht.

Wenn du sie public machst (ohne static):

Sie tauchen in der globalen Funktionsliste auf

Andere Module könnten sie versehentlich aufrufen

Das macht Kopfschmerzen beim Debuggen

Mit static sagst du dem Compiler:

„Diese Funktion gehört NUR dieser Datei.
Niemals von außen aufrufbar.“

2. Kollisionen mit anderen Namen werden verhindert

Wenn du eine interne Funktion putPixelClipped hast,
und später jemand in einem anderen Modul zufällig auch putPixelClipped schreibt:

ohne static → Linkerfehler (entweder „multiple definitions“ oder „redefinition“)

mit static → kein Problem, weil jede Datei eine private Version hat

Das ist ein riesiger Vorteil in Embedded-Projekten.

3. Der Compiler kann besser optimieren

Wenn eine Funktion static ist, weiß der Compiler:

Sie wird NUR in dieser Datei benutzt.

Er darf sie inline setzen.

Er darf aggressiver optimieren, weil sie nirgendwo anders abhängt.

Das führt zu kleinerem und schnellerem Code.

4. Public API klar halten

Dein Modul soll NACH AUSSEN nur 1 sichtbare Funktion anbieten:

decodeAndDisplayRLE(...)

Alles andere ist interne Logik und wird versteckt.

Dadurch entsteht eine klare, einfache API:

main.c ruft nur decodeAndDisplayRLE auf.

Alle Details wie RLE-Processing, Palette, Pixel-Clipping bleiben intern.

Das ist „gute Modul-Architektur“.


Kurz: Warum Static
Grund                      |           Bedeutung
-----------------------------------------------------------------------------------------------
Encapsulation              | Funktionen gehören NUR zu decoder.c niemand sonst darf sie nutzen
Sicherheit                 | Andere Module können sie nicht aus Versehen verwenden
Namensschutz               | Keine Kollisionen zwischen Modulen
Optimierung                | Compiler kann sie extermer optimieren
Klare API                  | Nur eine Funktion ist öffentlich; der Rest ist intern



Fazit
Sie müssen NICHT static sein

—ABER

Sie SOLLEN static sein

um ein sauberes, professionelles Modul zu bauen.

Damit ist dein decoder-Modul schön isoliert, wie es in Embedded-C üblich ist.