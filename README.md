# Arduino-Blumenbewaesserung
Dieses Projekt wurde im Rahmen des Girlsdays 2019 der Westfälischen Hochschule für den Fachbereich  2/Elektrotechnik erstellt. Dieses Projekt bietet die Möglichkeit eine Zimmerpflanze mit einem Feuchtigkeitssensor zu versehen, diesen Sensor zyklisch auszulesen, und dann ggf. eine Pumpe anzusteuern, welche die Pflanze bewässert.
Im laufe dieses Projekts wird die Fähigkeit erwoben, einfache Schaltungen auzuzeichnen, mit vorgefertigten Steckverbindungen zusammen zu schalten, und eine kleine Transistorschaltung zu löten.
##An Hardware benötigen wir:
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
##An Werkzeug und Verbrauchsmaterial brauchen wir:
* Lötkolben incl. Zubehör wie Lot, Entlötlitze
* Isolierten Draht zum Verbinden der Bauteile und Löten der Schaltung auf der Lochrasterplatine
