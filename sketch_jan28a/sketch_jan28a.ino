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

typedef struct BreathingTechnique {
  unsigned short inhaleIterations;
  unsigned short holdInterations;
  unsigned short exhaleIterations;
} BreathingTechnique;

#define fse (BreathingTechnique) {.inhaleIterations = 4, .holdInterations = 7, .exhaleIterations = 8}
#define fff (BreathingTechnique) {.inhaleIterations = 4, .holdInterations = 4, .exhaleIterations = 4}
#define tst (BreathingTechnique) {.inhaleIterations = 1, .holdInterations = 1, .exhaleIterations = 1}

#define cbt {fse, fff, tst}

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(1000);

//  displayTitle();
//  delay(5000);
//  displayMenu();
//  displayAnim();
    startTechnique(tst);
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

void displayTitle() {
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

void displayMenu() {
  prepareDisplay();

  String techniqueName = String(cbt.inhaleIterations) + "-" + String(cbt.holdIteartions) + "-" + String(cbt.exhaleIterations);
  setText(techniqueName, 2, 36, 0);
  setText("Technique", 1, 39, 25);
  display.drawFastHLine(0, 50, SCREEN_WIDTH, WHITE);
  setText("Start", 1, 0, 55);
  setText("Cycle", 1, (SCREEN_WIDTH - 29), 55);
  display.display(); 
}

void startTechnique(BreathingTechnique bt) {
  int iterations = 0;
  for (;;) {
    setText("Iteration: " + String(iterations++), 1, 46, 0);
    display.display();
    delay(1500);
    displayTechnique(bt.inhaleIterations, "INHALE");
    displayTechnique(bt.holdInterations, "-HOLD-");
    displayTechnique(bt.exhaleIterations, "EXHALE");
  }
}

void displayTechnique(unsigned short iterations, String type) {
  int circleX = (SCREEN_WIDTH / 2);
  int circleY = (SCREEN_HEIGHT / 2) - 10;
  int circleRadius = 20;
  for (int i = 1; i < iterations + 1; i++) {
    prepareDisplay();
    setText(type, 1, 46, 55);
    display.fillCircle(circleX, circleY, circleRadius, WHITE);
    display.display();
    delay(500);

    prepareDisplay();
    setText(type, 1, 46, 55);
    display.drawCircle(circleX, circleY, circleRadius, WHITE);
    int textXPosition = i >= 10 ? circleX - 5 : circleX - 2;
    setText(String(i), 1, textXPosition, circleY - 2);
    display.display();
    delay(500);
  }
}

void findCenter() {
  display.setCursor((SCREEN_WIDTH / 2), (SCREEN_HEIGHT) - 10);
  display.println("x");
  display.display();
}
