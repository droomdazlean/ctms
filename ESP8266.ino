#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WiFi credentials
const char* ssid = "ProjectOfVimbai2025";
const char* password = "1234567890";

// I2C LCD setup
#define LCD_SDA 4  // GPIO4 (D2)
#define LCD_SCL 5  // GPIO5 (D1)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Use 0x3F if 0x27 doesn't work

// LED GPIOs
const int whiteLed = 16; // D0
const int yellowLed = 0;  // D3
const int greenLed = 2;   // D4
const int orangeLed = 14; // D5
const int redLed = 12;    // D6

ESP8266WebServer server(80);

// Blinking state variables
bool blinkRed = false;
bool blinkGreen = false;
bool blinkOrange = false;
bool blinkYellow = false;
bool blinkWhite = false;

// Helper function to add CORS headers to every response
void sendCorsHeaders() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");
}

// Handler for OPTIONS requests to support CORS preflight
void handleOptions() {
  sendCorsHeaders();
  server.send(204); // No Content
}

void setup() {
  Serial.begin(115200);
  
  // Initialize LEDs as output and set LOW initially
  pinMode(whiteLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(orangeLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  digitalWrite(whiteLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(orangeLed, LOW);
  digitalWrite(redLed, LOW);

  // Initialize I2C and LCD
  Wire.begin(LCD_SDA, LCD_SCL);
  lcd.init();
  lcd.backlight();

  // Initialization messages on LCD
  lcd.setCursor(0, 0);
  lcd.print("Sys Initializing");
  lcd.setCursor(0, 1);
  lcd.print(".... wait ....");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Vimbai Project");
  lcd.setCursor(0, 1);
  lcd.print("2025 ...");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Cyber Threats");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring Sys");
  delay(5000);
  lcd.clear();

  // Connect to WiFi showing progressive status on LCD
  lcd.setCursor(0, 0);
  lcd.print("Remote ...");
  lcd.setCursor(0, 1);
  lcd.print("Web Dashboard");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Establishing");
  lcd.setCursor(0, 1);
  lcd.print("Connection ....");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Wifi Connecting");
  lcd.setCursor(0, 1);
  lcd.print(".... Please Wait...");
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(1000);
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dashboard");
    lcd.setCursor(0, 1);
    lcd.print("Has Failed ...");
    delay(3000);
    ESP.restart();
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WELCOME");
    lcd.setCursor(0, 1);
    lcd.print("DASH SUCCESS");
    delay(5000);
    lcd.clear();
  
    // After printing "Activated" and "Server Monitor"
lcd.setCursor(0, 0);
lcd.print("Activated");
lcd.setCursor(0, 1);
lcd.print("Server Monitor");
delay(10000);
lcd.clear();

// Now display WiFi IP address
IPAddress ip = WiFi.localIP();
lcd.setCursor(0, 0);
lcd.print("IP Address:");
lcd.setCursor(0, 1);
lcd.print(ip.toString());
delay(5000);
lcd.noBacklight();
lcd.setCursor(0, 0);
lcd.print("Listening ...");
  }

  // Define OPTIONS handler on all endpoints to handle CORS preflight
  server.onNotFound([]() {
    if (server.method() == HTTP_OPTIONS) {
      handleOptions();
    } else {
      server.send(404);
    }
  });

  // Define all endpoints with proper CORS headers

  server.on("/turnWhiteOn", HTTP_GET, []() {
    sendCorsHeaders();
    digitalWrite(whiteLed, HIGH);
    server.send(200, "text/plain", "success");
  });
  server.on("/turnWhiteOff", HTTP_GET, []() {
    sendCorsHeaders();
    digitalWrite(whiteLed, LOW);
    server.send(200, "text/plain", "success");
  });

  server.on("/turnYellowOn", HTTP_GET, []() {
    sendCorsHeaders();
    digitalWrite(yellowLed, HIGH);
    server.send(200, "text/plain", "success");
  });
  server.on("/turnYellowOff", HTTP_GET, []() {
    sendCorsHeaders();
    digitalWrite(yellowLed, LOW);
    server.send(200, "text/plain", "success");
  });

  server.on("/turnGreenOn", HTTP_GET, []() {
    sendCorsHeaders();
    digitalWrite(greenLed, HIGH);
    server.send(200, "text/plain", "success");
  });
  server.on("/turnGreenOff", HTTP_GET, []() {
    sendCorsHeaders();
    digitalWrite(greenLed, LOW);
    server.send(200, "text/plain", "success");
  });

  server.on("/turnOrangeOn", HTTP_GET, []() {
    sendCorsHeaders();
    digitalWrite(orangeLed, HIGH);
    server.send(200, "text/plain", "success");
  });
  server.on("/turnOrangeOff", HTTP_GET, []() {
    sendCorsHeaders();
    digitalWrite(orangeLed, LOW);
    server.send(200, "text/plain", "success");
  });

  server.on("/turnRedOn", HTTP_GET, []() {
    sendCorsHeaders();
    digitalWrite(redLed, HIGH);
    server.send(200, "text/plain", "success");
  });
  server.on("/turnRedOff", HTTP_GET, []() {
    sendCorsHeaders();
    digitalWrite(redLed, LOW);
    server.send(200, "text/plain", "success");
  });

  // Blinking endpoints

  server.on("/startBlinkingWhite", HTTP_GET, []() {
    sendCorsHeaders();
    blinkWhite = true;
    server.send(200, "text/plain", "success");
  });
  server.on("/stopBlinkingWhite", HTTP_GET, []() {
    sendCorsHeaders();
    blinkWhite = false;
    digitalWrite(whiteLed, LOW);
    server.send(200, "text/plain", "success");
  });

  server.on("/startBlinkingYellow", HTTP_GET, []() {
    sendCorsHeaders();
    blinkYellow = true;
    server.send(200, "text/plain", "success");
  });
  server.on("/stopBlinkingYellow", HTTP_GET, []() {
    sendCorsHeaders();
    blinkYellow = false;
    digitalWrite(yellowLed, LOW);
    server.send(200, "text/plain", "success");
  });

  server.on("/startBlinkingGreen", HTTP_GET, []() {
    sendCorsHeaders();
    blinkGreen = true;
    server.send(200, "text/plain", "success");
  });
  server.on("/stopBlinkingGreen", HTTP_GET, []() {
    sendCorsHeaders();
    blinkGreen = false;
    digitalWrite(greenLed, LOW);
    server.send(200, "text/plain", "success");
  });

  server.on("/startBlinkingOrange", HTTP_GET, []() {
    sendCorsHeaders();
    blinkOrange = true;
    server.send(200, "text/plain", "success");
  });
  server.on("/stopBlinkingOrange", HTTP_GET, []() {
    sendCorsHeaders();
    blinkOrange = false;
    digitalWrite(orangeLed, LOW);
    server.send(200, "text/plain", "success");
  });

  server.on("/startBlinkingRed", HTTP_GET, []() {
    sendCorsHeaders();
    blinkRed = true;
    server.send(200, "text/plain", "success");
  });
  server.on("/stopBlinkingRed", HTTP_GET, []() {
    sendCorsHeaders();
    blinkRed = false;
    digitalWrite(redLed, LOW);
    server.send(200, "text/plain", "success");
  });

  // LCD message endpoint
  server.on("/displayMessageOnLCD", HTTP_GET, []() {
    sendCorsHeaders();
    String line1 = server.arg("line1");
    String line2 = server.arg("line2");
    if (line1.length() <= 16 && line2.length() <= 16) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(line1);
      lcd.setCursor(0, 1);
      lcd.print(line2);
      server.send(200, "text/plain", "success");
      
    } else {
      server.send(400, "text/plain", "failed");
    }
  });

  // LCD backlight control
  server.on("/turnLCDBacklightOn", HTTP_GET, []() {
    sendCorsHeaders();
    lcd.backlight();
    server.send(200, "text/plain", "success");
  });
  server.on("/turnLCDBacklightOff", HTTP_GET, []() {
    sendCorsHeaders();
    lcd.noBacklight();
    server.send(200, "text/plain", "success");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  // Blinking logic with delay optimized to prevent blocking multiple LEDs
  if (blinkWhite) {
    digitalWrite(whiteLed, !digitalRead(whiteLed));
    delay(100);
  }
  if (blinkYellow) {
    digitalWrite(yellowLed, !digitalRead(yellowLed));
    delay(100);
  }
  if (blinkGreen) {
    digitalWrite(greenLed, !digitalRead(greenLed));
    delay(100);
  }
  if (blinkOrange) {
    digitalWrite(orangeLed, !digitalRead(orangeLed));
    delay(100);
  }
  if (blinkRed) {
    digitalWrite(redLed, !digitalRead(redLed));
    delay(100);
  }

}
