#include <Arduino.h>
#include <WiFi.h>
// Pin-Nummern für den Ultraschallsensor
int trigPin = 2;
int echoPin = 4;
// Pin-Nummern für die LEDs
const int led1 = 33;
const int led2 = 32;
// Variablen zur Messung der Distanz
int duration;
int distance;
// WLAN-Zugangsdaten
const char* ssid = "FortniteLover"; // SSID des WLANs eintragen
const char* password = "sytek123"; // Passwort des WLANs eintragen
WiFiServer server(80);
WiFiClient client;
// Funktion zur Behandlung des HTTP-Root-Anfragen
void handleRoot() {
	// Laufzeitmessung + Distanzberechnung durchführen
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = duration * 0.034 / 2; // Lauzeit * Schallgeschwindigkeit(= 343m/s) / 2 um Distanz in cm zu berechnen
	// HTML-Antwort senden
	String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
	response += "<html><body>";
	response += "<h1>Einparkhilfe</h1>";
	response += "<p id=\"distance\">Distanz: " + String(distance) + " cm</p>";
	response += "<script>setTimeout(function() { location.reload(); }, 1000);</script>";
	response += "</body></html>";
	client.print(response);
}

void setup() {
	Serial.begin(9600);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	// WLAN-Verbindung herstellen
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.println("Connecting to WiFi...");
	}
	Serial.println("Connected to WiFi");
	// Server starten
	server.begin();
	Serial.println("Server started");
	// IP-Adresse des Servers in der seriellen Konsole anzeigen
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}
void loop() {
	// Auf Verbindungen warten
	client = server.available();
	if (client) {
		Serial.println("New client connected");
		handleRoot();
		delay(200);
		client.stop();
		Serial.println("Client disconnected");
	}
	// Laufzeitmessung + Distanzberechnung durchführen
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = duration * 0.034 / 2;
	Serial.println(distance);
	// LED-Status basierend auf der Distanz setzen
	if (distance <= 5) {
		digitalWrite(led2, HIGH);
	} else {
		digitalWrite(led2, LOW);
	}
	if (distance > 5 && distance <= 10) {
		digitalWrite(led1, HIGH);
		delay(50);
		digitalWrite(led1, LOW);
		delay(50);
	} else {
		digitalWrite(led1, LOW);
	}
	if (distance > 10 && distance <= 20) {
		digitalWrite(led1, HIGH);
		delay(250);
		digitalWrite(led1, LOW);
		delay(250);
	} else {
		digitalWrite(led1, LOW);
	}
	if (distance > 20 && distance <= 30) {
		digitalWrite(led1, HIGH);
		delay(500);
		digitalWrite(led1, LOW);
		delay(500);
	} else {
		digitalWrite(led1, LOW);
	}
		delay(100);
}
