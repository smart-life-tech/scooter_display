// simple turbo boost gauge for Arduino, 128x64 OLED display and a potentiometer
//
// based on the "u8glib_progress_bar" project by urish - https://wokwi.com/arduino/projects/300867986768527882
//
// created by upir
// full-length youtube tutorial: https://youtu.be/JXmw1xOlBdk

// links for tools used for this project:
// WOWKI emulator: https://wokwi.com/
// Start project from urish: https://wokwi.com/arduino/projects/300867986768527882
// Photopea (online graphics editor): https://www.photopea.com/ 
// Gamer font: https://www.dafont.com/gamer-2.font?text=-1+2+3+4+5+6+7+8+TURBO+turbo+boost 
// Image2CPP tool: https://javl.github.io/image2cpp/
// Pressure sensor with Arduino: https://www.youtube.com/watch?v=MRNc7XUHBks


#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI
// U8GLIB_SSD1306_128X64 u8g(13, 11, 8, 9, 10); // SPI connection
// for SPI connection, use this wiring:
// GND > GND
// VCC > 5V
// SCL > 13
// SDA > 11
// RES > 10
// DC > 9
// CS > 8
// 'Új projekt', 128x64px




// 'anim_frame_1', 16x9px
// spinning inner part of the turbocharher icon, frame 1
const unsigned char epd_bitmap_anim_frame_1 [] PROGMEM = {
	0x01, 0x00, 0x09, 0x20, 0x05, 0x40, 0x03, 0x80, 0x1f, 0xf0, 0x03, 0x80, 0x05, 0x40, 0x09, 0x20, 
	0x01, 0x00
};
// 'anim_frame_2', 16x9px
// spinning inner part of the turbocharher icon, frame 2
const unsigned char epd_bitmap_anim_frame_2 [] PROGMEM = {
	0x00, 0x80, 0x04, 0x80, 0x02, 0xa0, 0x1f, 0xc0, 0x03, 0x80, 0x07, 0xf0, 0x0a, 0x80, 0x02, 0x40, 
	0x02, 0x00
};
// 'anim_frame_3', 16x9px
// spinning inner part of the turbocharher icon, frame 3
const unsigned char epd_bitmap_anim_frame_3 [] PROGMEM = {
	0x02, 0x00, 0x02, 0x40, 0x0a, 0x80, 0x07, 0xf0, 0x03, 0x80, 0x1f, 0xc0, 0x02, 0xa0, 0x04, 0x80, 
	0x00, 0x80
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 144)
const int epd_bitmap_allArray_LEN = 3;

const unsigned char* epd_bitmap_allArray[3] = {
	epd_bitmap_anim_frame_1,
	epd_bitmap_anim_frame_2,
	epd_bitmap_anim_frame_3
};



//int progress = 0;   // progress of the gauge
int frame = 0;      // frame for the inner part of the icon

void setup() {
  //u8g.setFont(u8g_font_tpssb);  // no need to set the font, as we are not drawing any strings
  u8g.setColorIndex(1);  // set the color to white

}

void loop() {
  u8g.firstPage();
  do {
  
      u8g.setColorIndex(1); // white color

      u8g.setColorIndex(1);                                      // white color      
      //u8g.drawBox(2, 13, map(progress, 0, 1023, 0, 124), 10);    // actual gauge fill, remapped from 0-1023 to 0-124 (maximum rectangle size)

      // draw the animated inside part of the icon
       u8g.drawBitmapP(5, 39, 16/8, 9, epd_bitmap_allArray[frame]); 



  } while ( u8g.nextPage() );


  frame = frame+1;            // increase the frame for the inner part of the icon
  if (frame > 2) {frame = 0;} // there are total of 3 frames for the animation

  // if (progress < 100) {    // automatically increase the progress value (not driven by potentiometer)
  //   progress++;
  // } else {
  //   progress = 0;
  // }


}

