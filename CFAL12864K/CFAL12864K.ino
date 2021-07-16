
//===========================================================================
//
//  Code written for Seeeduino v4.2 runnung at 3.3v
//
//  CRYSTALFONTZ CFAL12864K 128x64 OLED in SPI mode
//
//  ref: https://www.crystalfontz.com/product/cfal12864k
//
//  The controller is a Solomon Systech SSD1309
//    https://www.crystalfontz.com/controllers/SolomonSystech/SSD1309/
//
// 2021 - 07 - 16 Kelsey Zaches
// 2017 - 03 - 25 Brent A. Crosby
//===========================================================================
//This is free and unencumbered software released into the public domain.
//
//Anyone is free to copy, modify, publish, use, compile, sell, or
//distribute this software, either in source code form or as a compiled
//binary, for any purpose, commercial or non-commercial, and by any
//means.
//
//In jurisdictions that recognize copyright laws, the author or authors
//of this software dedicate any and all copyright interest in the
//software to the public domain. We make this dedication for the benefit
//of the public at large and to the detriment of our heirs and
//successors. We intend this dedication to be an overt act of
//relinquishment in perpetuity of all present and future rights to this
//software under copyright law.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.
//
//For more information, please refer to <http://unlicense.org/>
//===========================================================================

#define ADDR_MODE 2 //0:horizontal, 1:vertical, 2:page

#define SSD1309_VCOMH_DESELECT_0p65xVCC_00     (0x00)
#define SSD1309_COM_CONFIG_SEQUENTIAL_LEFT_02  (0x02)
#define SSD1309_VCOMH_DESELECT_0p71xVCC_10     (0x10)
#define SSD1309_COM_CONFIG_ALTERNATE_LEFT_12   (0x12)
#define SSD1309_DCDC_CONFIG_7p5v_14            (0x14)
#define SSD1309_DCDC_CONFIG_6p0v_15            (0x15)
#define SSD1309_VCOMH_DESELECT_0p77xVCC_20     (0x20)
#define SSD1309_COM_CONFIG_SEQUENTIAL_RIGHT_22 (0x22)
#define SSD1309_DEACTIVATE_SCROLL_2E           (0x2E)  //Missing from Datasheet
#define SSD1309_VCOMH_DESELECT_0p83xVCC_30     (0x30)
#define SSD1309_COM_CONFIG_ALTERNATE_RIGHT_32  (0x32)
#define SSD1309_DISPLAY_START_LINE_40          (0x40)
#define SSD1309_CONTRAST_PREFIX_81             (0x81)
#define SSD1309_DCDC_CONFIG_PREFIX_8D          (0x8D)
#define SSD1309_DCDC_CONFIG_8p5v_94            (0x94)
#define SSD1309_DCDC_CONFIG_9p0v_95            (0x95)
#define SSD1309_SEG0_IS_COL_0_A0               (0xA0)
#define SSD1309_SEG0_IS_COL_127_A1             (0xA1)
#define SSD1309_ENTIRE_DISPLAY_NORMAL_A4       (0xA4)
#define SSD1309_ENTIRE_DISPLAY_FORCE_ON_A5     (0xA5)
#define SSD1309_INVERSION_NORMAL_A6            (0xA6)
#define SSD1309_INVERSION_INVERTED_A7          (0xA7)
#define SSD1309_MULTIPLEX_RATIO_PREFIX_A8      (0xA8)
#define SSD1309_SET_MASTER_CONFIGURATION_AD    (0xAD)  //Missing from Datasheet
#define SSD1309_DISPLAY_OFF_YES_SLEEP_AE       (0xAE)
#define SSD1309_DISPLAY_ON_NO_SLEEP_AF         (0xAF)
#define SSD1309_SCAN_DIR_UP_C0                 (0xC0)
#define SSD1309_SCAN_DIR_DOWN_C8               (0xC8)
#define SSD1309_DISPLAY_OFFSET_PREFIX_D3       (0xD3)
#define SSD1309_CLOCK_DIVIDE_PREFIX_D5         (0xD5)
#define SSD1309_COLOR_AND_LOW_POWER_DISPLAY_MODE_D8 (0xD8)  //Missing from Datasheet
#define SSD1309_PRECHARGE_PERIOD_PREFIX_D9     (0xD9)
#define SSD1309_COM_CONFIG_PREFIX_DA           (0xDA)
#define SSD1309_VCOMH_DESELECT_PREFIX_DB       (0xDB)

//==============================================================================
//  BS0,BS1 interface settings:
//  
//      Interface         | BS1 | BS2 
//  ----------------------+-----+-----
//    I2C                 |  1  |  0  
//    4-wire SPI          |  0  |  0  
//    8-bit 6800 Parallel |  0  |  1  
//    8-bit 8080 Parallel |  1  |  1  
//  Select the interface
//#define SPI_4_WIRE
#define I2C
//==============================================================================

#include <avr/io.h>
#ifdef SPI_4_WIRE
  #include <SPI.h>
// C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\SPI\src\SPI.cpp
// C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\SPI\src\SPI.h
//================================================================================
void sendcommand(uint8_t command)
  {
  // Select the LCD's command register
  CLR_DC;
  // Select the LCD controller
  CLR_CS;

  //Send the command via SPI:
  SPI.transfer(command);
  //deselect the controller
  SET_CS;
  }
//================================================================================
void senddata(uint8_t data)
  {
  //Select the LCD's data register
  SET_DC;
  //Select the LCD controller
  CLR_CS;
  //Send the command via SPI:
  SPI.transfer(data);

  // Deselect the LCD controller
  SET_CS;
  }
#endif
//================================================================================

#ifdef I2C
  #include <Wire.h>
  void sendcommand(uint8_t command)
{
  Wire.beginTransmission(0x3C); //send start & Slave address
  Wire.write(0x00);             //Control Byte - Command
  Wire.write(command);          //payload
  Wire.endTransmission();

}
//============================================================================
void senddata(uint8_t data)
{
  Wire.beginTransmission(0x3C); //send start & Slave address
  Wire.write(0xC0);             //Control Byte - Data (non-continued)
  Wire.write(data);          //payload
  Wire.endTransmission();
}
#endif
//================================================================================



#include <SD.h>
// C:\Program Files (x86)\Arduino\libraries\SD\src\SD.cpp
// C:\Program Files (x86)\Arduino\libraries\SD\src\SD.h

#include "bootlogo1.h"

//============================================================================
/*
The CFAL12864K is a 3.3v device. You need a 3.3v Arduino to operate this
code properly. We used a seeedunio v4.2 set to 3.3v:
https://www.crystalfontz.com/product/cfapn15062-seeeduino-arduino-clone-microprocessor

Connections:
    ==================
    SD Card => Arduino
    ==================
        GND => GND
       MISO => D12
        CLK => D13
       MOSI => D11
         CS => D7
        3V3 => 3V3

   ===============
    Arduino => OLED SPI
    ===============
        3V3 => Pin 11 (also through ~10uF cap to GND)
        GND => Pins 1 and 2
         D8 => Pin 17
         D9 => Pin 16
        D10 => Pin 15
        D11 => Pin 21
        D13 => Pin 20
15v at 40mA => Pin 30

   ===============
    Arduino => OLED I2C
    ===============
        3V3 => Pin 11 (also through ~10uF cap to GND)
        GND => Pins 1 and 2
         D9 => Pin 16
        A4 => Pin 21 and 22 (1k resistor to 3v3)
        A5 => Pin 20 (1k resistor to 3v3)
 15v at 40mA => Pin 30

       ============
       OLED => OLED
       ============
     Pin 12 => (GND for SPI) (3V3 for I2C)
     Pin 13 => GND
     Pin 18 => GND
     Pin 19 => GND
     Pin 28 => ~885Ω to GND
     Pin 29 => ~10uF cap to GND
     Pin 31 => GND
*/
//============================================================================
#define OLED_RESET 4
#define CLR_RESET (digitalWrite(OLED_RESET, LOW))
#define SET_RESET (digitalWrite(OLED_RESET, HIGH))
//============================================================================

#define CLR_RS    (PORTB &= ~(0x01))
#define SET_RS    (PORTB |=  (0x01))
#define CLR_RESET (PORTB &= ~(0x02))
#define SET_RESET (PORTB |=  (0x02))
#define CLR_CS    (PORTB &= ~(0x04))
#define SET_CS    (PORTB |=  (0x04))
#define CLR_MOSI  (PORTB &= ~(0x08))
#define SET_MOSI  (PORTB |=  (0x08))
#define CLR_SCK   (PORTB &= ~(0x20))
#define SET_SCK   (PORTB |=  (0x20))

#define SD_CS ( 7)

//============================================================================
#define HRES 128
#define VRES 64
//============================================================================
//Updated code, 2017-03-27
#if (ADDR_MODE==2)
void setAddr(unsigned char page,unsigned char lCol,unsigned char hCol)
{
  sendcommand(page);//Set Page Start Address
  sendcommand(lCol);//Set Lower Column Start Address
  sendcommand(hCol);//Set Higher Column Start Address
}
#else
void setPageAddr(unsigned char startAddr,unsigned char endAddr)
{
  sendcommand(startAddr);
  sendcommand(endAddr);
}

void setColAddr(unsigned char startAddr,unsigned char endAddr)
{
  sendcommand(startAddr);
  sendcommand(endAddr);
}
#endif

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Instruction Setting
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Set_Start_Column(unsigned char d)
{
  sendcommand(0x00 + d % 16);   // Set Lower Column Start Address for Page Addressing Mode
            //   Default => 0x00
  sendcommand(0x10 + d / 16);   // Set Higher Column Start Address for Page Addressing Mode
            //   Default => 0x10
}

void Set_Column_Address(unsigned char a, unsigned char b)
{
  sendcommand(0x21);      // Set Column Address
  sendcommand(a);     //   Default => 0x00 (Column Start Address)
  sendcommand(b);     //   Default => 0x7F (Column End Address)
}


void Set_Page_Address(unsigned char a, unsigned char b)
{
  sendcommand(0x22);      // Set Page Address
  sendcommand(a);     //   Default => 0x00 (Page Start Address)
  sendcommand(b);     //   Default => 0x07 (Page End Address)
}


void Set_Start_Page(unsigned char d)
{
  sendcommand(0xB0 | d);      // Set Page Start Address for Page Addressing Mode
            //   Default => 0xB0 (0x00)
}


void Home_Addr(void)
{
  #if (ADDR_MODE<2)
    sendcommand(0x22);//Set Page Address
    setPageAddr(0,7);
    sendcommand(0x21);//Set Column Address
    setColAddr(0,127);
  #else
    setAddr(0xb0,0,0x10);
  #endif
}

void init_display(void)
{
  //Thump the reset.  
  _delay_ms(1);
  CLR_RESET;
  _delay_ms(1);
  SET_RESET;
  _delay_ms(1);

  sendcommand(SSD1309_DISPLAY_OFF_YES_SLEEP_AE);//Set Display ON/OFF =>0xae:Display off
  
  sendcommand(0x20);//Set Memory Addressing Mode
  sendcommand(ADDR_MODE);
  Home_Addr();
  
  sendcommand(0x81);//Set contrast Control for BANK0
  sendcommand(0x80);
  
  sendcommand(0x40);//Set Display Start Line
  sendcommand(0xa1);//Set Segment Re-map =>0xa0:column addr. 0 is mapped to SEG0
  sendcommand(0xa4);//Entire Display On =>0xa4:resume to RAM content display
  sendcommand(0xa6);//Set Normal/Inverse Display =>0xa6:Normal,0xa7:inverse 
  
  sendcommand(0xa8);//Set Multiplex Ratio
  sendcommand(0x3f);//63

  sendcommand(0xad);//Master Configuration
  sendcommand(0x8e);

  sendcommand(0xc0);//Set COM Output Scan Direction =>0xc0:scan from COM0 to COM63, 0xc8:scan from COM63 to COM0

  sendcommand(0xd3);//Set Display Offset
  sendcommand(0x00);

  sendcommand(0xd5);//Set Display Clock Divid Ratio/Oscillator Frequency
  sendcommand(0xf0);

  sendcommand(0xd8);//Set Area Color Mode ON/OFF & Low Power Display Mode
  sendcommand(0x05);//0x05:monochrome mode and low power display mode

  sendcommand(0xd9);//Set Pre-charge Period
  sendcommand(0xf1);

  sendcommand(0xda);//Set COM Pins Hardware Configuration
  sendcommand(0x12);

  sendcommand(0xdb);//Set Vcomh Deselect Level
  sendcommand(0x40);

  sendcommand(0x2e);//deactivate scroll
  
  sendcommand(SSD1309_DISPLAY_ON_NO_SLEEP_AF);//Set Display ON/OFF =>0xaf:Display on
}
//----------------------------------------------------------------------------
void show_BMPs_in_root(void)
  {
    //Currently, this demo only works when using SPI interface
  File
    root_dir;
  root_dir = SD.open("/");
  if(0 == root_dir)
    {
    Serial.println("show_BMPs_in_root: Can't open \"root\"");
    }
  File
    bmp_file;

  while(1)
    {
    bmp_file = root_dir.openNextFile();
    if (0 == bmp_file)
      {
      // no more files, break out of while()
      // root_dir will be closed below.
      break;
      }
    //Skip directories (what about volume name?)
    if(0 == bmp_file.isDirectory())
      {
      //The file name must include ".BMP"
      if(0 != strstr(bmp_file.name(),".BMP"))
        {
        //The BMP must be exactly 1088 long
        //(this is correct for 128x64 1-bit)
        if(1088 == bmp_file.size())
          {
          //Jump over BMP header. BMP must be 128x64 1-bit
          bmp_file.seek(0x3E);
    
          //Since we are limited in memory, break the line up from
          // 240*3 = 720 bytes into three chunks of 80 pixels
          // each 80*3 = 240 bytes.
          //Making this static speeds it up slightly (10ms)
          //Reduces flash size by 114 bytes, and uses 240 bytes.
          static uint8_t
            line_buffer[128];
          for(uint8_t line=0;line<8;line++)
            {
            //Set the LCD to the left of this line.
            
            sendcommand(0x00);      //lower column address
            sendcommand(0x10);      //upper column address
            sendcommand(0xB0+line);  //set page address
            
            //Read 8 lines out of the BMP
            bmp_file.read(line_buffer,128);

            //BMPs store data
            //lowest line first -- bottom up.
            //Set_LCD_for_write_at_X_Y(0,line);

            uint8_t
              h_mask;
            h_mask=0x80;
            for(uint8_t col=0;col<128;col++)
              {
              uint8_t
                sub_line;
              uint8_t
                v_mask;
              v_mask=0x01;
              uint8_t
                this_v_byte;
              this_v_byte=0;
              for(sub_line=0;sub_line<8;sub_line++)
                {
                if(line_buffer[(sub_line<<4)+(col>>3)] & h_mask)
                  {
                  this_v_byte|=v_mask;
                  }

                v_mask<<=1;
                }

              senddata(this_v_byte);
              //delay(20);
              
              h_mask>>=1;
              if(0x00 == h_mask)
                h_mask=0x80;
              }
            }
          }
        }
      }
    //Release the BMP file handle
    bmp_file.close();
    delay(2000);
    }
  //Release the root directory file handle
  root_dir.close();
  }
//============================================================================

void fillScreen(uint8_t pattern)
{
  for (uint8_t line = 0; line < 8; line++)
  {
    sendcommand(0x00);      //lower column address
    sendcommand(0x10);      //upper column address
    sendcommand(0xB0 + line);  //set page address
    for (uint8_t x = 0; x < 128; x++)
    {
      senddata(pattern);
    }

  }
}


//================================================================================
// showSplash() takes an image out of flash and puts it on the screen. In this case,
// the image stored in flash is the splash screen
//================================================================================
void showSplash()
{
  uint8_t pixels;
  uint8_t theByte;
  uint16_t coordinate;
  for (uint8_t y = 0; y < 8; y++)
  {
    // Set the starting page and column
    Set_Start_Page(y);
    Set_Start_Column(0x00);
    for (uint8_t x = 0; x < 128 / 8; x++)
    {
      for (uint8_t i = 0; i < 8; i++)
      {
        pixels = 0x00;
        // Since the OLED writes down for each byte, we grab one bit at a time from each of the 
        // eight bytes that make up the page
        for (int j = 0; j < 8; j++)
        {
          // First determine the coordinate of the byte we wish to read from
          coordinate = x + ((y * 8) + j)*HRES / 8;
          // Read the byte
          theByte = pgm_read_byte(&Mono_1BPP[coordinate]);
          // Determine which bit we need to keep and put it in the correct spot
          pixels |= (((theByte << i) & 0x80) >> (7 - j));
        }
        // Send a byte
        senddata(pixels);
      }
    }
    //   delay(1000);
  }
//   Set_Start_Page(7);
//   Set_Start_Column(0x00);
//   for (uint8_t x = 0; x < 128; x++)
//   {
//     senddata(0x00);
//   }
}
//============================================================================

void setup( void )
  {
  DDRB |= 0x2F;

  //Drive the ports to a reasonable starting state.
  CLR_RESET;
  CLR_RS;
  SET_CS;
  CLR_MOSI;
  CLR_SCK;


  //Pin 7 is used for the SD card CS.
  pinMode(SD_CS, OUTPUT);

  //debug console
  Serial.begin(9600);
  Serial.println("setup()");

  #ifdef SPI_4_WIRE
  //SPI begin transactions takes ~2.5us
  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));

  
  // For the Seeduino I am using, the default speed of SPI_HALF_SPEED
  // set in C:\Program Files (x86)\Arduino\libraries\SD\src\SD.cpp
  // results in a 4MHz clock.
  //
  // If you change this function call in SDClass::begin() of SD.cpp
  // from:
  //
  //  return card.init(SPI_HALF_SPEED, csPin) &&
  //         volume.init(card) &&
  //         root.openRoot(volume);
  //
  // to:
  //
  //  return card.init(SPI_FULL_SPEED, csPin) &&
  //         volume.init(card) &&
  //         root.openRoot(volume);
  //
  // That appears to make the SD library talk at 8MHz.
  //
  // Alas, it only improves a full-screen update from a dismally slow
  // time of 1.81 seconds to the nearly hopeless time of 1.35 seconds.
  //
  if (!SD.begin(SD_CS)) 
    {
    Serial.println("Card failed to initialize, or not present");
    //Reset the SPI clock to fast. SD card library does not clean up well.
    //Bump the clock to 8MHz. Appears to be the maximum.
    SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));    
    }
  else
    {
    Serial.println("Card initialized.");
    }
#endif
        
#ifdef I2C
  //
  //Get the I2C going
  Wire.begin();
  //Thanks to Limor / Adafruit for the hint ;-)   
  TWBR = 12; // upgrade to 400KHz!
#endif

  //Fire up the I2C OLED
  Serial.println("init_display()");
  init_display();

  }
//============================================================================
// DEFINES
#define waittime 1000

#define splashdemo  1
#define filldemo    1
#define bmpdemo     0 //only works in SPI

//============================================================================
void loop(void)
{  
#if splashdemo
fillScreen(0x00);
delay(waittime);
  showSplash();
  delay(waittime);
#endif

#if filldemo
  fillScreen(0x0f);
  delay(waittime);
  fillScreen(0xf0);
  delay(waittime);
  fillScreen(0x00);
  delay(waittime);
  fillScreen(0xff);
  delay(waittime);
#endif
#if bmpdemo
  show_BMPs_in_root();    
#endif
}
//============================================================================
