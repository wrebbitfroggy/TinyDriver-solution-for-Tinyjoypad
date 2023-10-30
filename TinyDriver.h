/*
                             >>>MIT License<<<
Copyright (c) <2023> <Wrebbitfroggy>
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

-> After numerous unsuccessful searches to find a solution to get Tinyjoypad-compatible
 games to work on the standard ATtiny85 microcontroller, I decided to focus on the
 essential steps to make the games work on the ATtiny85. Now that my work is complete,
 I would like to share it with the community ;) Simply replace the TinyDriver.h file with this one!

Contact: https://github.com/wrebbitfroggy
*/

//prototype
void TinyOLED_init(void);
void TinyOLED_Begin(void);
void TinyOLED_End(void);
void TinyOLED_Send(uint8_t byte_);
void TinyOLED_send_command(uint8_t command);
void TinyOLED_Data_Start(uint8_t Y_);
                   
#define OledSDA_LOW  0b11111110
#define OledSDA_HIGH 0b00000001
#define OledSCL_LOW 0b11111011
#define OledSCL_HIGH 0b00000100
#define OledADRESS 0x78

void TinyOLED_init(void){
DDRB = DDRB | OledSDA_HIGH;
DDRB = DDRB | OledSCL_HIGH;
  TinyOLED_send_command(0xAE);//display off
  TinyOLED_send_command(0x00);//Set Memory Addressing Mode
  TinyOLED_send_command(0x10);//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
  TinyOLED_send_command(0x40);//Set Page Start Address for Page Addressing Mode,0-7
  TinyOLED_send_command(0xB0);//Set COM Output Scan Direction
  TinyOLED_send_command(0x81);//---set low column address
  TinyOLED_send_command(0xCF);//---set high column address
  TinyOLED_send_command(0xA1);//--set start line address
  TinyOLED_send_command(0xA6);//--set contrast control register
  TinyOLED_send_command(0xA8);
  TinyOLED_send_command(0x3F);//--set segment re-map 0 to 127
  TinyOLED_send_command(0xC8);//--set normal display
  TinyOLED_send_command(0xD3);//--set multiplex ratio(1 to 64)
  TinyOLED_send_command(0x00);//
  TinyOLED_send_command(0xD5);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
  TinyOLED_send_command(0x80);//-set display offset
  TinyOLED_send_command(0xD9);//-not offset
  TinyOLED_send_command(0xF1);//--set display clock divide ratio/oscillator frequency
  TinyOLED_send_command(0xDA);//--set divide ratio
  TinyOLED_send_command(0x12);//--set pre-charge period
  TinyOLED_send_command(0xDB);//
  TinyOLED_send_command(0x40);//--set com pins hardware configuration
  TinyOLED_send_command(0x8D);//--set vcomh
  TinyOLED_send_command(0x14);//0x20,0.77xVcc
  TinyOLED_send_command(0xAF);//--set DC-DC enable
  TinyOLED_send_command(0xAF);//--turn on oled panel 
}

void TinyOLED_Begin(void){
PORTB = PORTB | OledSDA_HIGH;
PORTB = PORTB | OledSCL_HIGH;
PORTB = PORTB & OledSDA_LOW;
PORTB = PORTB & OledSCL_LOW;
}

void TinyOLED_End(void){
PORTB = PORTB & OledSDA_LOW;
PORTB = PORTB & OledSCL_LOW;
PORTB = PORTB | OledSDA_HIGH;
PORTB = PORTB | OledSCL_HIGH;
}

void TinyOLED_Send(uint8_t byte_){
uint8_t t_;
for (t_ = 0; t_ < 8; t_++){ 
PORTB=((byte_ << t_) & 0x80)?(PORTB | OledSDA_HIGH):(PORTB & OledSDA_LOW);
PORTB = PORTB | OledSCL_HIGH;
PORTB = PORTB & OledSCL_LOW;
}
PORTB = PORTB | OledSDA_HIGH;
PORTB = PORTB | OledSCL_HIGH;
PORTB = PORTB & OledSCL_LOW;
}

void TinyOLED_send_command(uint8_t command_){
TinyOLED_Begin();
TinyOLED_Send(OledADRESS);
TinyOLED_Send(0x00);
TinyOLED_Send(command_);
TinyOLED_End();
}

void TinyOLED_Data_Start(uint8_t Y_){
TinyOLED_send_command(0xb0 + Y_);
TinyOLED_send_command(0x00);
TinyOLED_send_command(0x10);
TinyOLED_Begin();
TinyOLED_Send(OledADRESS);
TinyOLED_Send(0x40);
}


