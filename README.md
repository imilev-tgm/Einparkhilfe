# Eigenes Projekt Parkhilfe

## Einparkhilfe - Ultraschallsensor

Die Ziel des Projekts ist, eine Einparkhilfe mittels Ultraschallsensor zu bauen, welche die Nähe zu einem Objekt durch zwei verschiedene LEDs (niedrige Frequenz = größere Distanz, hohe Frequenz = kleinere distanz, durchgehendes Leuchten = unmittelbare Nähe) und einem Webserver ausgibt.

## Schaltplan
![image](https://github.com/imilev-tgm/Einparkhilfe/assets/119353531/3e32f5ec-513a-46ce-960b-b3e3e3db82a9)


## Aufbau

![image](https://github.com/imilev-tgm/Einparkhilfe/assets/119353531/a952919b-d0b2-4113-ad10-33d47df5656f)


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
