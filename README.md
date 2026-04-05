# TP-Link Tapo P110
Random information about the TP-Link Tapo P110 smart switch.<br>

## YouTube Videos
- [Part 1: Initial teardown & serial port logs](https://youtu.be/b5snm9TfyWc)

## [Images](/Images)
Photos of the board and components.<br>

## [Schematic](/Schematic)
A perhaps-never-completed schematic (KiCad) of the board.  My main interest is how the handle the 240VAC-to-DC conversion so I can implement something similar in my own project.<br>

## Microcontroller Daughterboard
The P110 uses a custom daughterboard labelled KB-6160 and ZSL-1 containing a Realtek RTL8170CF ARM Cortex-M3 microcontroller.<br>

The daughterboard has 12 contacts to the main board.<br>

On the front (MCU side), labelled from left-to-right:
- P11
- P9
- P6
- P1
- P12 (GND)
- P2 (+3.3V)

On the back, labelled from left-to-right:
- P3
- P4
- P5
- P7
- P8
- P10

It also has six Test Points:
- TP1
- TP2
- TP3 (+3.3V)
- TP4 (GND)
- TP5 (serial receive?)
- TP6 (serial transmit, 115200kbps, 8N1)
