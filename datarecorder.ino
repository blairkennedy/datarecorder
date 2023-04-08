/***
Data Recorder sketch
Capture data with the current time and record to a time-series file on SD card.

This sketch will leverage the following components:
** WEMOS D1 mini (8266 based microcontroller board)
** 1306 OLED 128x64 display
** Mini SD Card drive
** DS3231 Timeclock


Author: Blair Kennedy
Date: April 2023
*/

// Library declarations

// I2C and SPI Bus libraries
#include <Adafruit_BusIO_Register.h>
#include <SPI.h>
#include <SD.h>

// 1306 OLED Driver
#include <Adafruit_SSD1306.h>
#include <splash.h> // adafruit splash logo
#include <Adafruit_GFX.h>
#include <wire.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

File myFile; // File handle
const int SD_ChipSelect = 0xD8; //Wemos D1 mini CS pin is 0xD8

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(115200); // serial interface output

  Serial.println(F("Starting datareader sketch"));

   


  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  
  Serial.print("Initializing SD card...");

  if (!SD.begin(SD_ChipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // test SD card reader
  // testFile();
}




String test_string = "Hello World";



void loop() {
  // put your main code here, to run repeatedly:
  
  displayText(test_string);
  

}


void displayText(String message) {
  Serial.println("displayText called with parameter - " + message);
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(SCREEN_WIDTH/2-(sizeof(message)/2*5),0);             // Start at top-left corner
  display.println(message);

  // display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  
  //display.setTextSize(2);             // Draw 2X-scale text
  //display.setTextColor(SSD1306_WHITE);
  //display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
  delay(2000);
}

// Write and delete a file from the SD card
void testFile() {



  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

  // open a new file and immediately close it:
  Serial.println("Creating example.txt...");
  myFile = SD.open("example.txt", FILE_WRITE);
  myFile.close();

  // Check to see if the file exists:
  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

  // delete the file:
  Serial.println("Removing example.txt...");
  SD.remove("example.txt");

  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

}
