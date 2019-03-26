/* Arduino-Blumenbewaesserung Version 0.1.a
 * Datum: 26.03.2019
 * Autor: Bastian Reul
 * Kontakt: Bastian Reul@w-hs.de
 * Site: https://github.com/Bastian-Reul/Arduino-Blumenbewaesserung
 * Notes: millis() erzeugt nach 49 Tagen einen Überlauf und fängt wieder bei 0 an zu zählen. Das resultiert zwar dann nach 49 Tagen in EINEM nicht richtig gemessenen Intervall, für die Lesbarkeit dieses Anfängerprogramms wird
 * jedoch darauf verzichtet, diesen Überlauf abzufangen.
 * Der Feuchtigkeitssensor wird immer ausgeschaltet wenn er nicht benötigt wird, da die Elektroden sich sonst schnell (innerhalb von zwei Monaten) durch elektrochemische Prozesse auflösen würden.
 * 
 * To-Do:
 * Pins noch auf die endgültigen verlöteten anpassen
 * 
 */
int FeuchteZielWert = 500;                              //Dieser Wert bestimmt am Ende, wie feucht oder trocken es die Pflanze haben soll. Typische Werte für Pflanzen sind
/*    https://www.123zimmerpflanzen.de/pflege/giessen
 *     Die hier gelisteten Werte sind erstmal nur Schätzwerte und müssen noch angepasst werden
 *     
 *     Wasserverbrauch viel:  FeuchteZielWert = 600;
 *      Ficus, Schefflera, Gummibaum
 *      
 *     Wasserverbrauch mäßig: FeuchteZielWert = 500;
 *      Drachenbaum, Zimmertanne, Kolbenfaden, Philodendron, manche Orchideen
 *     
 *     Wasserverbrauch gering: FeuchteZielWert = 400;
 *      Bogenhanf, Agave, Kakteen, Palmfarne, Palmlilien. Elefantenfuß, Geldbaum
 * 
 */

byte VersorgungFeuchteSensorPin = 13;                  // Der Sensor für Trockenheitsmessung darf nicht dauerthaft mit Spannung versorgt werden, da ansonsten die Leiterbahnen durch elektrochemische Prozesse wegkorrodieren
                                                       // Daher wird der Sensor nur eingeschaltet, wenn er für eine Messung benötigt wird.

int AnalogWertFeuchtePin = A3;                        // An diesem Pin liegt die Ausgangsspannung des Feuchtesensors an. Ist Sie hoch (> 4V) ist das Erdreich feucht. Der Analoge Spannungswert wird über diesen PIN in den ADC des
                                                       // Arduino eingelesen
                                                       
byte VersorgungMotorPin = 11;                          // Ist die Erde zu trocken, wird über diesen PIN der Transistor und die damit verbundene Pumpe eingeschaltet

boolean MotorStatus = LOW;                             // Um sich zu merken ob die Pumpe aktuell pumpt oder ausgeschaltet ist, wird diese Mekervariable benötigt
int FeuchteGemessen = 0;                               // Wenn die Feuchte gemessen wurde, wird der Digitale Wert in dieser Variablen abgespeichert


unsigned long previousMillis = 0;                       // wieviele Millisekunden sind seit dem letzten Feuchtemessungsintervall vergangen. Dieser Wert steht in dieser Variablen
unsigned long interval = 14400000;                          // Wie häufig soll die Feuchte der Erde gemessen und ggf. bewässert werden? Wert in Millisekunden. 
/*  1 Stunde : 1000 x 60 x 60     -> interval =  3600000;
 *  2 Stunden: 1000 x 60 x 60 * 2 -> interval =  7200000;
 *  4 Stunden: 1000 x 60 x 60 * 4 -> interval = 14400000;
 */
 
void setup()
{
  pinMode(VersorgungFeuchteSensorPin, OUTPUT);          // Der Pin für die Spannungsversorgung des Feuchtesensors ist aus der Sicht des Arduinos ein Ausgang
  pinMode(VersorgungMotorPin, OUTPUT);                  // Der Pin der den Motor ein und ausschaltet ist ein Ausgang
  pinMode(AnalogWertFeuchtePin, INPUT);                   // Der Pin über den die Spannung für den Feuchtigkeitswert eingelesen wird, ist ein Eingang
}
 
void loop() //Diese Schleife wird mehrere 100 male während einer Sekunde aufgerufen solange der Timer nicht abgelaufen ist
{
  if (millis() - previousMillis > interval) {
    previousMillis = millis();   // Das Warteintervall ist abgelaufen, der previousMillis Wert wird auf die aktuell abgelaufenen millisekunden gesetzt. Damit ergibt für die nächste Prüfung: millis() - previousMillis = 0 (oder zumindest nahe 0)
   
    digitalWrite(VersorgungFeuchteSensorPin, HIGH); // Die Spannung an dem Feuchtesensor einschalten
    delay(2000);      //Zwei Sekunden warten bis sich die Spannung für den Feuchtewert stabilisiert hat
    FeuchteGemessen = analogRead(AnalogWertFeuchtePin); //Den Spannungswert auslesen, der vom Feuchtesensor ausgegeben wird, und die digitale Umwandlung dieses Wertes in der Variablen "FeuchteGemessen" abspeichern
    digitalWrite(VersorgungFeuchteSensorPin, LOW); // Da die Spannung für die Feuchtigkeit der Erde jetzt eingelesen wurde, kann die Spannung zur Versorgung des Sensors wieder ausgeschaltet werden, um ein "abrosten" des Sensors zu vermeiden
    
    if(FeuchteGemessen < FeuchteZielWert) //Ist die Erde zu trocken?
      {//ja, es muss bewässert werden
        digitalWrite(VersorgungMotorPin, HIGH); // Schalte die Pumpe ein
        delay(60000); //Warte eine Minute, die Pumpe läuft während dieser Zeit
        digitalWrite(VersorgungMotorPin, LOW); // Schalte die Pumpe aus
      }
      else
      {//nein, die Erde ist noch feucht genug
      //Hier könnten andere Sachen gemacht werden, die passieren sollen wenn die Feuchte gemessen wurde, die Erde aber noch feucht genug ist. Beispielsweise kann der Feuchtigkeitswert über die Serielle Schnittstelle ausgegeben werden
      }

  }
}

