#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "Your WIFI";
const char* password = "Your WIFI code";

// Set up a static IP address
IPAddress local_ip(192, 168, 1, 100);  // Change to your desired static IP
IPAddress gateway(192, 168, 1, 1);     // Change to your network's gateway
IPAddress subnet(255, 255, 255, 0);    // Change to your network's subnet

// Buzzer pin
const int buzzerPin = 12;

WebServer server(80); // Create a web server on port 80

// Variables for buzzer control
bool buzzerActive = false;
unsigned long buzzerStartTime = 0;
const unsigned long buzzerDuration = 20000; // 20 seconds
const unsigned long beepInterval = 500;      // Beep every 500 ms

void setup() {
  // Start the Serial
  Serial.begin(115200);
  
  // Set the buzzer pin as OUTPUT
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); // Ensure the buzzer is off initially

  // Connect to Wi-Fi
  WiFi.config(local_ip, gateway, subnet);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Define the API endpoint
  server.on("/trigger", HTTP_POST, handlePost);

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient(); // Handle incoming clients

  // Control the buzzer
  if (buzzerActive) {
    unsigned long currentTime = millis();
    
    // Check if it's time to beep
    if ((currentTime - buzzerStartTime) < buzzerDuration) {
      if ((currentTime / beepInterval) % 2 == 0) {
        digitalWrite(buzzerPin, HIGH); // Turn the buzzer on
      } else {
        digitalWrite(buzzerPin, LOW);  // Turn the buzzer off
      }
    } else {
      // Stop the buzzer after the duration
      buzzerActive = false;
      digitalWrite(buzzerPin, LOW); // Ensure the buzzer is off
    }
  }
}

// Function to handle POST requests
void handlePost() {
  // Check if the request is empty
  if (server.args() == 0) {
    buzzerActive = true;          // Activate the buzzer
    buzzerStartTime = millis();   // Record the start time
    server.send(200, "text/plain", "Buzzer triggered!"); // Respond with success
  } else {
    server.send(400, "text/plain", "Bad Request"); // Respond with error
  }
}
