#include <Wire.h>
#include <MPU6050_tockn.h>   // MPU6050 Library
#include <Adafruit_GFX.h>    // OLED Display Library
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
#define OLED_RESET    -1     // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MPU6050 mpu6050(Wire); // Initialize MPU6050

bool fallDetected = false;  // Flag to track fall detection
unsigned long fallTime = 0; // Timestamp when fall occurs

void setup() {
    Serial.begin(115200);
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);  // Calibrate Gyroscope

    // Initialize OLED Display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // OLED I2C Address 0x3C
        Serial.println("SSD1306 OLED display failed to start!");
        for (;;);
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 10);
    display.println("Fall Detection System");
    display.display();
    delay(2000);

    displayNormal();  // Initially show "You are fine"
}

void loop() {
    mpu6050.update();  // Update MPU6050 Sensor Readings

    float Ax = mpu6050.getAccX() * 9.81;  // Convert to m/s²
    float Ay = mpu6050.getAccY() * 9.81;
    float Az = mpu6050.getAccZ() * 9.81;
    float Gx = mpu6050.getGyroX();  // Angular velocity (°/s)
    float Gy = mpu6050.getGyroY();

    // Check if 10 seconds have passed since the fall
    if (fallDetected && (millis() - fallTime > 10000)) {
        fallDetected = false;  // Reset fall detection
        displayNormal();  // Return to "You are fine" message
    }

    // FALL DETECTION LOGIC
    if (!fallDetected && (abs(Az) < 2.5) && (abs(Ax) > 25 || abs(Ay) > 25) && (abs(Gx) > 80 || abs(Gy) > 80)) {
        fallDetected = true;
        fallTime = millis();  // Store time of fall detection
        Serial.println("🚨 Fall Detected!");
        displayFallAlert();  // Show fall alert for 10 seconds
    }

    delay(100); // Optimized delay
}

// OLED Display Functions
void displayFallAlert() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(10, 20);
    display.println("YOU HAVE");
    display.setCursor(10, 40);
    display.println("FALLEN 😢");
    display.display();
}

void displayNormal() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(20, 20);
    display.println("YOU ARE");
    display.setCursor(20, 40);
    display.println("FINE");
    display.display();
}

