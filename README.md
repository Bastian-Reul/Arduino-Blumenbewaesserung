# Arduino-Blumenbewaesserung
Dieses Projekt wurde im Rahmen des Girlsdays 2019 der Westfälischen Hochschule für den Fachbereich  2/Elektrotechnik erstellt. Dieses Projekt bietet die Möglichkeit eine Zimmerpflanze mit einem Feuchtigkeitssensor zu versehen, diesen Sensor zyklisch auszulesen, und dann ggf. eine Pumpe anzusteuern, welche die Pflanze bewässert.
Im laufe dieses Projekts wird die Fähigkeit erwoben, einfache Schaltungen auzuzeichnen, mit vorgefertigten Steckverbindungen zusammen zu schalten, und eine kleine Transistorschaltung zu löten.

## An Hardware benötigen wir:
* Einen Arduino UNO R3 oder ein Arduino UNO R3 kompatibles Board incl. einem passenden USB Kabel
  Ein kompatibles Arduino UNO R3 wäre zum beispiel dieses: [Himalaya basic UNO R3](https://www.conrad.de/de/himalaya-basic-uno-r3-atmega328p-board-atmega16u2-mit-usb-kabel-arduino-uno-r3-kompatibel-802287391.html)
* Einen Feuchtigkeitssensor den man in die Erde der Topfpflanze stecken kann
  Zum Beispiel dieser: [Seeed Studio Grove - Moisture Sensor 3.3-5V](https://www.conrad.de/de/himalaya-basic-uno-r3-atmega328p-board-atmega16u2-mit-usb-kabel-arduino-uno-r3-kompatibel-802287391.html)
* Eine Pumpe um das Wasser von einem Vorratsbehältnis in den Topf zu pumpen. Die Pumpe benötigt nur eine sehr geringe Förderleistung um muss mit 9V Gleichspannung (DC) arbeiten. 
**Keinesfalls darf eine 230V (Aquariums-)Pumpe an diese Schaltung angeschlossen werden. Es besteht LEBENSGEFAHR!!!**
Zum Beispiel kann diese Pumpe verwendet werden: [Makeblock Water Pump Motor - DC 12V 370-04PM](https://www.conrad.de/de/makeblock-water-pump-motor-dc-12v-370-04pm-802556245.html)
* Ein Mosfet Transisor
* Eine Freilaufdiode
* Ein 5000 Ohm Widerstand
* Ein Paar Pinheader
* Ein Stück Lochrasterplatine
* Schlauch um das Vorratsbehältnis mit der Pumpe, und die Pumpe mit dem Topf zu verbinden
* Den aus dem 3D Drucker stammenden Bewässerungshaken. Alternativ reicht hier auf eine Wäscheklammer

## An Werkzeug und Verbrauchsmaterial brauchen wir:
* Lötkolben incl. Zubehör wie Lot, Entlötlitze
* Isolierten Draht zum Verbinden der Bauteile und Löten der Schaltung auf der Lochrasterplatine
* Seitenschneider, Pinzette, Abisolierzange, etc.

## Benötigte Software
* Um den von diesem Git-Repository heruntergeladenen C++ Code (eigentlich ein Pseudo-Code, aber das führt zu weit) zu kompilieren und auf das Arduino Board zu bekommen, benötigt ihr die  [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* Und natürlich braucht ihr dieses Repository mit dem Quellcode und der 3D Druck Datei. Klickt hierfür einfach oben rechts auf dieser Seite auf den grünen **Clone or Download** Button und dann auf **Download ZIP**. Diese ZIP Datei könnt ihr dann irgendwo auf eurem Rechner hin entpacken und anschließend die Datei Arduino-Blumenbewaesserung.ino mit einem Doppelklick öffnen. Jetzt sollte sich die Arduino IDE mit dem Quellcode des Projekts öffen. Schaut euch den Quellcode ruhig einmal an und danach könnt ihr ihn mit **Speichern unter** so speichern, dass die Arduino IDE mit den im Hintergrund benötigten Bibliotheken zurecht kommt. Habt ihr nun die IDE korrekt konfiguriert, und das Arduino Board per USB mit dem Computer verbunden, könnt ihr den **Sketch** (das Programm) -> **Hochladen**. Hierbei wird der Quellcode kompiliert und anschließend auf den Arduino hochgeladen. 
