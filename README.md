# TP-Link Tapo P110
Random information about the TP-Link Tapo P110 smart plug.<br>

## YouTube Videos
- [Part 1: Initial teardown & serial port logs](https://youtu.be/b5snm9TfyWc)
- [Part 2: Further serial interface testing]()

## [Images](/Images)
Photos of the board and components.<br>

## [Serial Logs](/Serial_Logs)
Outputs from the serial debugging port on the Realtek chip captured via the Test Points.  I'm currently using an Arduino Mega with two hardware serial ports - one to capture the serial from the Realtek chip and a second to pass to my computer.<br>

The Realtek chip requires 3.3V ... this can be powered from the Arduino Mega and its serial TX doesn't require a 3.3V-to-5V level shifter.<br>

## Main Parts
- U1: Silergy SY22841 buck regulator
- U2: Realtek RTL8710CF ARM Cortex-M3 microcontroller
- U7: Shanghai Belling BL0937 energy meter

## [Schematic](/Schematic)
A perhaps-never-to-be-completed schematic (KiCad) of the board.  My main interest is how they handle the 240VAC-to-DC conversion so I can implement something similar in my own project.<br>

## Microcontroller Daughterboard
The P110 uses a custom daughterboard labelled KB-6160 and ZSL-1 containing a Realtek RTL8170CF ARM Cortex-M3 microcontroller.<br>

The daughterboard has 12 contacts to the main board.<br>

This is what I can determine: Pxx are the daughterboard pins and CONxx are the main board pins.<br>

| Motherboard | Daughterboard | Purpose            |
|-------------|---------------|--------------------|
| P1          | CON1          | BL0937 CF1 (pin 7) |
| P2          | CON12         | +3.3V              |
| P3          | CON3          | LED via R33        |
| P4          | CON4          | LED via R34        |
| P5          | CON5          |                    |
| P6          | CON6          |                    |
| P7          | CON7          |                    |
| P8          | CON8          |                    |
| P9          | CON9          |                    |
| P10         | CON10         | BL0937 CF (pin 6)  | 
| P11         | CON11         | BL0937 SEL (pin 8) |
| P12         | CON2          | GND                |

(yes, it seems they mislabelled/swapped P12/CON2 and P2/CON12).<br>

It also has six Test Points:
- TP1
- TP2 (pulled high ... download image)
- TP3 (+3.3V)
- TP4 (GND)
- TP5 (serial receive, 115200bps, 8N1)
- TP6 (serial transmit, 115200bps, 8N1)
