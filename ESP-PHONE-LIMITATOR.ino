/*
 * RELAZIONE TPS
 * EL-METKOUL KARIM 4AL
 * https://marcovid-4al.it
 * https://github.com/Ferrar65/Phone-Limitator-ESP8266
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <ESPAsyncTCP.h>
#include <FS.h>
#include <Wire.h>


//SSID / PASSWORD ROUTER
const char* ssid = "Tech4Byte";
const char* password = "**********";

WiFiServer server(80);

const char* endpoint = "http://192.168.0.3/api/MhK4WdkWiu5aqY3JtLGyC1Sai78vuNh3TqyZQvSS/lights/1/state"; //Chiave di accesso per consentire accesso al philps hue bridge

const int output5 = 5;  //definisco i pin D1 in GPIO (INPUT/OUTPUT PIN)
const int output4 = 4;  //definisco i pin D2 in GPIO (INPUT/OUTPUT PIN)


String getDistance() { //FUNZIONE PER RICHIEDERE DISTANZA
  // Read Distance
long durata = pulseIn( echoPort, HIGH);
long distanza = 0.034 * durata / 2;  //Calcolo per ricavare la distanza
Serial.print("Distanza: ");
if (durata > 38000 ){               //se supera il range massimo di lettura = fuori portata
  Serial.println("Fuori Portata");
}
else {
  Serial.print(distanza);   //se funziona tutto corretamente stampo la distanza
  Serial.println(" cm ");
}
  }



void setup(){
  Serial.begin(9600);

  if (! SPIFFS.begin ()) {
    Serial.println ("Non è stato possibile caricare i file integrati del ESP8266 (SPIFFS) "); //se non vengono caricati i file integrati nel ESP8266 scriivi il messaggio di errore
    return;
  }

  WiFi.begin(ssid, password);     //mi connetto al router con le credenziali
  Serial.println("");

  // Aspetto finchè non si instaura una connessione
  while (WiFi.status() != WL_CONNECTED) {       
    delay(500);
    Serial.print(".");
  }

  //se la connnesione è eseguita corretamente allora stampo i dettagli.
  Serial.println("");
  Serial.print("Conesso al ip ");
  Serial.println(ssid);
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());  //stampo l'ip deticato al esp
  Serial.println("HTTP server started");
}


server.on ("/", HTTP_GET, [] (AsyncWebServerRequest * request) { //invia richiesta al server per sync root
  request-> send (SPIFFS, "/index.html"); //la richiesta deve esser inviata alla seguente posizione
});
server.on ("/distance", HTTP_GET, [] (AsyncWebServerRequest * request) { //invia richiesta al server per sync
  request-> send_P (200, "text / plain", getDistance(). c_str ());//la richiesta deve esser inviata alla seguente posizione
});

  server.begin();                  //Avvio il Server
}


TurnOffLight(); 
delay(2000);
TurnOnLight(); //debug per vedere il corretto funzionamento dei led ad ogni accensione
delay(2000);





void loop() {


getDistance();
if ( distance < 34){

String message = "{\"on\":true, \"sat\":254, \"bri\":150,\"hue\":}"; //invio messaggio al hue bridge di impostare la luce su verde
}

if ( distance > 34 ){

  String message = "{\"on\":true, \"sat\":254, \"bri\":150,\"hue\":20000}";//invio messaggio al hue bridge di impostare la luce su rosso
}//invio messaggio al hue bridge di impostare la luce 
}
