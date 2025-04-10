//-------------------------------------------------------------------------- 
//! \file smart_weather_display.ino
//! \pre Dependencies: Adafruit_BMP280, Adafruit_GFX, Adafruit_SSD1306
//! \author Dhaivat Joshi
//! \version 1.0 \n
//! Copyright (c) 2024-2025 JustElectronicX. All rights reserved \n
//! This file reads temperature data from a BMP280 sensor using I2C 
//! and displays it on a 128x32 OLED. \n
//! \details Processor: ESP8266 (NodeMCU) \n
//-------------------------------------------------------------------------- 

/*
 * Project: Smart Weather Display with BMP280 and OLED using ESP8266
 * Description: This project reads temperature data from the BMP280 sensor using I2C communication 
 *              and displays it on a 128x32 OLED screen.
 * 
 * Connections:
 *   - BMP280 I2C Pins:
 *       SDA -> D2 (GPIO4 on ESP8266)
 *       SCL -> D1 (GPIO5 on ESP8266)
 *   - OLED I2C Pins:
 *       SDA -> D2 (GPIO4 on ESP8266)
 *       SCL -> D1 (GPIO5 on ESP8266)
 *   - Power Connections:
 *       BMP280 -> 3.3V and GND
 *       OLED -> 5V and GND
 *   - Breadboard Power Supply:
 *       Input -> External USB power supply (5V)
 *
 * Note: Ensure to provide 3.3V to the BMP280 sensor as it is a 3.3V version.
 */


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>

// OLED display width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// I2C address of your OLED display
#define OLED_ADDRESS 0x3C

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
Adafruit_BMP280 bmp;

void setup() {

  bmp.begin(); //Start the bmp

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Clear buffer
  display.clearDisplay();

  // Draw splash animation
  splashAnimation();
}

void loop() {

  display.clearDisplay();
  float T = bmp.readTemperature(); //Read temperature in °C
  float P = bmp.readPressure() / 100; //Read Pressure in Pa and conversion to hPa
  float A = bmp.readAltitude(1019.66); //Calculating the Altitude, the "1019.66" is the pressure in (hPa) at sea level at day in your region


  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print("Temp");

  display.setCursor(0, 18);
  display.print(T, 1);
  display.setCursor(50, 17);
  display.setTextSize(1);
  display.print("C");

  display.setTextSize(1);
  display.setCursor(65, 0);
  display.print("Pres");
  display.setCursor(65, 10);
  display.print(P);
  display.setCursor(110, 10);
  display.print("hPa");

  display.setCursor(65, 25);
  display.print("Alt");
  display.setCursor(90, 25);
  display.print(A, 0);
  display.setCursor(110, 25);
  display.print("m");

  display.display();
  delay(2000);
}

void splashAnimation() {

  // Typing effect
  typingEffect("JustElectronicX");

  delay(2000);

  // Wave effect
  waveEffect("JustElectronicX");

  delay(2000);

  // Clear display after animation
  display.clearDisplay();
  display.display();
}

// Helper function to calculate the text width for centering
int calculateTextWidth(const char* text) {
  int width = 0;
  for (int i = 0; i < strlen(text); i++) {
    if (text[i] == 'J' || text[i] == 'E' || text[i] == 'X') {
      width += 14; // Larger width for 'J', 'E', 'X'
    } else {
      width += 7; // Standard width for smaller characters
    }
  }
  return width;
}

// Typing Effect
void typingEffect(const char* text) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  int totalWidth = calculateTextWidth(text);
  int startX = (SCREEN_WIDTH - totalWidth) / 2; // Center horizontally
  int x = startX; // Initial X position

  for (int i = 0; i < strlen(text); i++) {
    if (text[i] == 'J' || text[i] == 'E' || text[i] == 'X') {
      display.setTextSize(2); // Larger font for 'J', 'E', 'X'
      display.setCursor(x, SCREEN_HEIGHT / 2 - 12); // Center vertically
      x += 14; // Adjust spacing for larger characters
    } else {
      display.setTextSize(1); // Default font size
      display.setCursor(x, SCREEN_HEIGHT / 2 - 6); // Center vertically
      x += 7; // Standard spacing for smaller characters
    }
    display.print(text[i]);
    display.display();
    delay(150); // Typing delay
  }
}

// Wave Effect
void waveEffect(const char* text) {
  display.clearDisplay();

  int totalWidth = calculateTextWidth(text);
  int startX = (SCREEN_WIDTH - totalWidth) / 2; // Center horizontally

  for (int offset = 0; offset < 30; offset++) { // Longer duration
    display.clearDisplay();
    int x = startX;

    for (int i = 0; i < strlen(text); i++) {
      int yOffset = 4 * sin((i + offset) * 0.3); // Sinusoidal wave offset
      int baseY = (text[i] == 'J' || text[i] == 'E' || text[i] == 'X')
                  ? SCREEN_HEIGHT / 2 - 12 // Center large text vertically
                  : SCREEN_HEIGHT / 2 - 6; // Center small text vertically
      int yPos = baseY + yOffset;

      if (text[i] == 'J' || text[i] == 'E' || text[i] == 'X') {
        display.setTextSize(2);             // Larger font for 'J', 'E', 'X'
        display.setCursor(x, yPos);
        x += 14;                            // Adjust spacing for larger characters
      } else {
        display.setTextSize(1);             // Default font size
        display.setCursor(x, yPos);
        x += 7;                             // Standard spacing
      }
      display.print(text[i]);
    }

    display.display();
    delay(120); // Wave animation speed
  }
}
