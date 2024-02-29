# CFAL12864G/K Demonstration Code 
This is Arduino sample code for the CFAL12864G and CFAL12864K family of displays. These displays are available in sizes of 2.4" and 2.7" respectively and are slim, lightweight, and have low power consumption. The displays use the [Solomon Systech SSD1309](https://www.crystalfontz.com/controllers/Solomon%20Systech/SSD1309/342) display controller and are capable of several interfaces including 8-bit parallel, 4-wire SPI, and I2C. A 31-pin 0.5mm ZIF to header breakout board will be required to interface with the displays. We recommend the [CFA10102](https://www.crystalfontz.com/product/cfa10102-oled-breakout-board) for this purpose as it supports an on-board boost circuit removing the requirement of a power supply to provide the panel driving voltage (VCC) of these displays.

## Connection guide
```
// LCD SPI pins and control lines on Seeeduino:
//  ARD      | Port  | Display pin |  Function - SPI                          |
//-----------+-------+-------------+------------------------------------------+
// 3.3V/5V   |       |             |  POWER 3.3V                              |
// GND       |       |             |  GROUND                                  |
//-----------+-------+-------------+------------------------------------------+
// D8        | PORTB |  17         |  Data/Command                    (DC)    |
// D9        | PORTB |  16         |  Reset                           (Reset) |
// D10       | PORTB |  15         |  Chip select                     (CS)    |
// D11       | PORTB |  21         |  SPI data input                  (SDA)   |
// D13       | PORTB |  20         |  Serial clock                    (SCK)   |
//-----------+-------+-------------+------------------------------------------+
//==============================================================================
// Interface Selection
// BS2 | BS1 | Interface mode        | 
//-----+-----+-----------------------+
// 0   | 0   | 4-wire SPI            |
// 0   | 1   | I2C                   |
// 1   | 1   | 8-bit parallel (8080) |
//-----+-----+-----+------------------+
//==============================================================================
// SD card connection (using CFA10112)
//  ARD      | Port  | Adapter pin |  Function                                |
//-----------+-------+-------------+------------------------------------------+
// 3.3V      |       |  3.3V       |  POWER 3.3V                              |
// GND       |       |  GND        |  GROUND                                  |
//-----------+-------+-------------+------------------------------------------+
// D7        | PORTC |  CS         |  Chip select                     (CS)    |
// D11       | PORTB |  DI         |  Serial data in                  (DI)    |
// D12       | PORTB |  DO         |  Serial data out                 (DO)    |
// D13       | PORTB |  SCK        |  Serial clock                    (SCK)   |
//-----------+-------+-------------+------------------------------------------+
(Micro SD card connection is optional)
```

## Display information
Here are links to our active displays:
+ [CFAL12864G-024W](https://www.crystalfontz.com/product/cfal12864g024w-128x64-2-4inch-white-oled-module): 2.4" display with white pixels
+ [CFAL12864G-024Y](https://www.crystalfontz.com/product/cfal12864g024y-128x64-graphic-oled-2-4inch): 2.4" display with yellow pixels
+ [CFAL12864K-W](https://www.crystalfontz.com/product/cfal12864kw-128x64-white-graphic-oled): 2.7" display with white pixels
+ [CFAL12864K-Y](https://www.crystalfontz.com/product/cfal12864ky-128x64-small-oled-display): 2.7" display with yellow pixels
  

For more information about other OLED offerings, please see our full list [here](https://www.crystalfontz.com/c/oled-displays/29).
