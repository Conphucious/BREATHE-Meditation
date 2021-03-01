/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(1000);

  displayMenu();
  delay(3000);
  displayAnim();
  
}

void loop() {
  
}

void setText(String text, int textSize, int x, int y) {
  display.setTextSize(textSize);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.println(text);
}

void prepareDisplay() {
  display.clearDisplay();
  display.setRotation(2);
  display.setTextWrap(false);
}

void displayMenu() {
  String title = "BREATHE";
  String desc = "By Jimmy Nguyen";
  String ver = "V1.0";
  prepareDisplay();
  setText(title, 3, 0, 0);
  display.drawFastHLine(0, 25, (SCREEN_WIDTH - 5), WHITE);
  setText(desc, 1, 22, 30);
  setText(ver, 1, (SCREEN_WIDTH / 2) - 10, 55);
  display.display(); 
}

void displayAnim() {
  prepareDisplay();
  display.drawCircle(50, 50, 5, WHITE);
  display.display();
  delay(1000);
  display.fillCircle(50, 50, 5, BLACK);
}

void findCenter() {
  display.setCursor((SCREEN_WIDTH / 2), (SCREEN_HEIGHT) - 10);
  display.println("x");
}
