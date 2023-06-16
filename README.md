# Eigenes Projekt Parkhilfe

## Einparkhilfe - Ultraschallsensor

Die Ziel des Projekts ist, eine Einparkhilfe mittels Ultraschallsensor zu bauen, welche die Nähe zu einem Objekt durch zwei verschiedene LEDs (niedrige Frequenz = größere Distanz, hohe Frequenz = kleinere distanz, durchgehendes Leuchten = unmittelbare Nähe) und einem Webserver ausgibt.

## Schaltplan

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/6371d7f1-7027-4067-9d1e-54ca091eb457/Untitled.png)

## Aufbau

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/4f25b000-535d-47a0-8db7-97d610e5a453/Untitled.png)

Code:

```jsx
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
const char* ssid = ""; // SSID des WLANs eintragen
const char* password = ""; // Passwort des WLANs eintragen
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
```

## Dokumentation

Der Ultraschallsensor besteht aus zwei Pins: dem Trig-Pin, der für die Ausgabe des Ultraschallimpulses zuständig ist, und dem Echo-Pin, der die Laufzeit des Echosignals misst. Diese Pins werden als Variablen `trigPin`und `echoPin` definiert.
Es gibt zwei LED-Pins, `led1` und `led2` , die als visuelle Indikatoren für die Abstandsmessung dienen.
Die WLAN-Zugangsdaten (SSID und Passwort) werden als Zeichenketten in den Variablen `ssid`und
`password` gespeichert.
Ein WiFiServer-Objekt mit dem Port 80 wird erstellt, um eingehende HTTP-Anfragen zu verarbeiten. Ein WiFiClient-Objekt wird ebenfalls deklariert, um die Verbindung zu einem Client herzustellen.
Die Funktion `handleRoot()` wird aufgerufen, wenn ein Client eine Verbindung herstellt und eine Anfrage an den Server sendet. In dieser Funktion wird die Distanz gemessen, indem der Ultraschallsensor aktiviert wird und die Laufzeit des Echosignals gemessen wird. Die gemessene Distanz wird dann in eine HTML-Antwort eingefügt und an den Client gesendet. Der HTML-Code enthält auch einen JavaScript-Code, der die Seite
alle 1 Sekunde neu lädt, um die Distanz automatisch zu aktualisieren.
In der `setup()` -Funktion werden die Pins und der Serial Monitor initialisiert. Der ESP32 stellt eine
Verbindung zum WLAN-Netzwerk her und der Webserver wird gestartet. Die IP-Adresse des Servers wird
auf dem Serial Monitor ausgegeben.
In der `loop()` -Funktion wird überprüft, ob ein Client verbunden ist. Wenn ja, wird die Funktion `handleRoot()`aufgerufen und die gemessene Distanz wird an den Client gesendet. Anschließend wird die Verbindung geschlossen und die Funktion `loop()` kehrt zurück, um den Ultraschallsensor zu lesen und die LEDs entsprechend der gemessenen Distanz zu steuern. Der Ultraschallsensor wird periodisch aktiviert, um die Laufzeit des Echosignals zu messen und die Distanz zu berechnen. Die berechnete Distanz wird dann über den Serial Monitor und Webserver ausgegeben. Basierend auf der gemessenen Distanz werden die LEDs `led1` und `led2` entsprechend gesteuert. Die LED
`led2` leuchtet auf, wenn die Distanz kleiner oder gleich 5 cm ist. Die LED `led1` blinkt mit verschiedenen Geschwindigkeiten, abhängig von der gemessenen Distanz.
