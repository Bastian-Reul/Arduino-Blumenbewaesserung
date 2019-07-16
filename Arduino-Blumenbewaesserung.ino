/* Arduino-Blumenbewaesserung Version 0.1.b
 * Datum: 01.04.2019
 * Autor: Bastian Reul
 * Kontakt: Bastian Reul@w-hs.de
 * Site: https://github.com/Bastian-Reul/Arduino-Blumenbewaesserung
 * 
 * Notes: millis() erzeugt nach 49 Tagen einen Überlauf und fängt wieder bei 0 an zu zählen. Das resultiert zwar dann nach 49 Tagen in EINEM nicht richtig gemessenen Intervall, für die Lesbarkeit dieses Anfängerprogramms wird
 * jedoch darauf verzichtet, diesen Überlauf abzufangen.
 * Der Feuchtigkeitssensor wird immer ausgeschaltet wenn er nicht benötigt wird, da die Elektroden sich sonst schnell (innerhalb von zwei Monaten) durch elektrochemische Prozesse auflösen würden.
 * 
 * To-Do:
 * Man könnte noch einstellen, dass beim Einschalten sofort eine Messung und ggf. Bewaesserung durchgeführt wird.
 * 
 */
int FeuchteZielWert = 200;                              //Dieser Wert bestimmt am Ende, wie feucht oder trocken es die Pflanze haben soll. Typische Werte für Pflanzen sind
/*    https://www.123zimmerpflanzen.de/pflege/giessen
 *     Die hier gelisteten Werte sind erstmal nur Schätzwerte und müssen noch angepasst werden
 *     
 *     Wasserverbrauch viel:  FeuchteZielWert = 400;
 *      Ficus, Schefflera, Gummibaum
 *      
 *     Wasserverbrauch mäßig: FeuchteZielWert = 200;
 *      Drachenbaum, Zimmertanne, Kolbenfaden, Philodendron, manche Orchideen
 *     
 *     Wasserverbrauch gering: FeuchteZielWert = 80;
 *      Bogenhanf, Agave, Kakteen, Palmfarne, Palmlilien. Elefantenfuß, Geldbaum
 * 
 */

byte VersorgungFeuchteSensorPin = 13;                  // Der Sensor für Trockenheitsmessung darf nicht dauerthaft mit Spannung versorgt werden, da ansonsten die Leiterbahnen durch elektrochemische Prozesse wegkorrodieren
                                                       // Daher wird der Sensor nur eingeschaltet, wenn er für eine Messung benötigt wird. Hierbei gab es bei den verschiedenen Teilnehmerinnen verschieden Lötausführungen.
                                                       //Die Zahl für den "VersorgungFeuchteSensorPin" muss wie folgt aussehen: (Kabelfarbe = Rot)
                                                       //Tutor = 13;
                                                       //Studentin 1 = 13;
                                                       //Studentin 2 = 13;
                                                       //Studentin 3 = 12;

int AnalogWertFeuchtePin = A0;                        // An diesem Pin liegt die Ausgangsspannung des Feuchtesensors an. Ist Sie hoch (> 4V) ist das Erdreich feucht. Der Analoge Spannungswert wird über diesen PIN in den ADC des
                                                       // Arduino eingelesen. Diesen Pin haben alle Teilnehmerinnen an den gleichen Pin A3 gelötet. (Kabelfarbe = Gelb)
                                                       
byte VersorgungMotorPin = 12;                          // Ist die Erde zu trocken, wird über diesen PIN der Transistor und die damit verbundene Pumpe eingeschaltet. Hierbei gab es bei den verschiedenen Teilnehmerinnen verschieden Lötausführungen.
                                                       //Die Zahl für den "VersorgungMotorPin" muss wie folgt aussehen: (Geht über den Widerstand an den MOSFET Transistor)
                                                       //Tutor = 12;
                                                       //Studentin 1 = 11;
                                                       //Studentin 2 = 12;
                                                       //Studentin 3 = 13;

boolean MotorStatus = LOW;                             // Um sich zu merken ob die Pumpe aktuell pumpt oder ausgeschaltet ist, wird diese Mekervariable benötigt
int FeuchteGemessen = 0;                               // Wenn die Feuchte gemessen wurde, wird der Digitale Wert in dieser Variablen abgespeichert


unsigned long previousMillis = 0;                       // wieviele Millisekunden sind seit dem letzten Feuchtemessungsintervall vergangen. Dieser Wert steht in dieser Variablen
unsigned long interval = 14400000;                      // Wie häufig soll die Feuchte der Erde gemessen und ggf. bewässert werden? Wert in Millisekunden. 
                                                        //Kann zum Debugging auf 1 Minute (unsigned long interval = 60000;) gestellt werden. Dann muss jedoch auch die Pumpendauer angepasst werden!!!
/*  1 Stunde : 1000 x 60 x 60     -> interval =  3600000;
 *  2 Stunden: 1000 x 60 x 60 * 2 -> interval =  7200000;
 *  4 Stunden: 1000 x 60 x 60 * 4 -> interval = 14400000;
 *  6 Stunden: 1000 x 60 x 60 * 6 -> interval = 21600000;
 *  6 Stunden: 1000 x 60 x 60 * 8 -> interval = 28800000;
 */
 
void setup(){
  pinMode(VersorgungFeuchteSensorPin, OUTPUT);          // Der Pin für die Spannungsversorgung des Feuchtesensors ist aus der Sicht des Arduinos ein Ausgang
  pinMode(VersorgungMotorPin, OUTPUT);                  // Der Pin der den Motor ein und ausschaltet ist ein Ausgang
  pinMode(AnalogWertFeuchtePin, INPUT);                   // Der Pin über den die Spannung für den Feuchtigkeitswert eingelesen wird, ist ein Eingang
  
  //Debugging oder Auslesen den Sensorwertes der Feuchtigkeit. Will man den Sensor Wert auf dem Computer angezeigt bekommen, muss man unter der Arduino IDE auf Werkzeuge-> Serieller Monitor klicken, und die Baudrate auf 9600 Baud eingestellt sein muss
  Serial.begin(9600);
  Serial.println("https://github.com/Bastian-Reul/Arduino-Blumenbewaesserung"); 
      Serial.println("Es wird gemessen"); 
    digitalWrite(VersorgungFeuchteSensorPin, HIGH); // Die Spannung an dem Feuchtesensor einschalten
    delay(2000);      //Zwei Sekunden warten bis sich die Spannung für den Feuchtewert stabilisiert hat
    FeuchteGemessen = analogRead(AnalogWertFeuchtePin); //Den Spannungswert auslesen, der vom Feuchtesensor ausgegeben wird, und die digitale Umwandlung dieses Wertes in der Variablen "FeuchteGemessen" abspeichern
    Serial.println(FeuchteGemessen); //Ausgeben des Wertes, der bei der Feuchtigkeit herausgekommen ist. Das ist der Wert der Analog / Digital Konvertierung. Er kann zwischen 0 (Erde ist sehr trocken/ Sensor hängt in der Luft) und ca 450 (Erde ist sehr feucht/ Sensor steckt in einem Wassglas)
    digitalWrite(VersorgungFeuchteSensorPin, LOW); // Da die Spannung für die Feuchtigkeit der Erde jetzt eingelesen wurde, kann die Spannung zur Versorgung des Sensors wieder ausgeschaltet werden, um ein "abrosten" des Sensors zu vermeiden
    
    if(FeuchteGemessen < FeuchteZielWert) //Ist die Erde zu trocken?
      {//ja, es muss bewässert werden
        Serial.println("Es ist zu trocken"); 
         Serial.println("Motor wird eingeschaltet"); 
        digitalWrite(VersorgungMotorPin, HIGH); // Schalte die Pumpe ein
        delay(60000); //Warte eine Minute, die Pumpe läuft während dieser Zeit //Muss zum Debugging kleiner als das Intervall sein. Bspw. Intervall = 60000, Pumendauer = 10000 (10 Sekunden))
        Serial.println("Motor wird ausgeschaltet");
        digitalWrite(VersorgungMotorPin, LOW); // Schalte die Pumpe aus
      }
      else
      {//nein, die Erde ist noch feucht genug
      //Hier könnten andere Sachen gemacht werden, die passieren sollen wenn die Feuchte gemessen wurde, die Erde aber noch feucht genug ist. Beispielsweise kann der Feuchtigkeitswert über die Serielle Schnittstelle ausgegeben werden
      Serial.println("Es ist feucht genug"); 
      }
}
 
void loop(){ //Diese Schleife wird mehrere 100 male während einer Sekunde aufgerufen solange der Timer nicht abgelaufen ist
  if (millis() - previousMillis > interval) {
    Serial.println("Es wird gemessen"); 
    previousMillis = millis();   // Das Warteintervall ist abgelaufen, der previousMillis Wert wird auf die aktuell abgelaufenen millisekunden gesetzt. Damit ergibt für die nächste Prüfung: millis() - previousMillis = 0 (oder zumindest nahe 0)
   
    digitalWrite(VersorgungFeuchteSensorPin, HIGH); // Die Spannung an dem Feuchtesensor einschalten
    delay(2000);      //Zwei Sekunden warten bis sich die Spannung für den Feuchtewert stabilisiert hat
    FeuchteGemessen = analogRead(AnalogWertFeuchtePin); //Den Spannungswert auslesen, der vom Feuchtesensor ausgegeben wird, und die digitale Umwandlung dieses Wertes in der Variablen "FeuchteGemessen" abspeichern
    Serial.println(FeuchteGemessen); //Ausgeben des Wertes, der bei der Feuchtigkeit herausgekommen ist. Das ist der Wert der Analog / Digital Konvertierung. Er kann zwischen 0 (Erde ist sehr trocken/ Sensor hängt in der Luft) und ca 450 (Erde ist sehr feucht/ Sensor steckt in einem Wassglas)
    digitalWrite(VersorgungFeuchteSensorPin, LOW); // Da die Spannung für die Feuchtigkeit der Erde jetzt eingelesen wurde, kann die Spannung zur Versorgung des Sensors wieder ausgeschaltet werden, um ein "abrosten" des Sensors zu vermeiden
    
    if(FeuchteGemessen < FeuchteZielWert) //Ist die Erde zu trocken?
      {//ja, es muss bewässert werden
        Serial.println("Es ist zu trocken"); 
         Serial.println("Motor wird eingeschaltet"); 
        digitalWrite(VersorgungMotorPin, HIGH); // Schalte die Pumpe ein
        delay(60000); //Warte eine Minute, die Pumpe läuft während dieser Zeit //Muss zum Debugging kleiner als das Intervall sein. Bspw. Intervall = 60000, Pumendauer = 10000 (10 Sekunden))
        Serial.println("Motor wird ausgeschaltet");
        digitalWrite(VersorgungMotorPin, LOW); // Schalte die Pumpe aus
      }
      else
      {//nein, die Erde ist noch feucht genug
      //Hier könnten andere Sachen gemacht werden, die passieren sollen wenn die Feuchte gemessen wurde, die Erde aber noch feucht genug ist. Beispielsweise kann der Feuchtigkeitswert über die Serielle Schnittstelle ausgegeben werden
      Serial.println("Es ist feucht genug"); 
      }

  }
}
