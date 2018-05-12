// written by Dylon Jamna (ME!)
// include the library code

#include <EEPROM.h>
#include <LiquidCrystal.h>// include the library code
#include "DHT.h"

//------------------------------E/S

int led = 13; // led de encedido/apagado
int swtu = 7;  // Pulsador seteo en pin 7
int swtd = 6;   // Pulsador seteo en pin 6

//------------------------------DHT

#define DHTPIN 6 // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

//------------------------------Variables

float settemp; //Variable seteo Temperatura
float h ;// Humedad
float t ; // Grados Celsius
float f ; // Grados Farenheit

//-----------------------------Monitor        

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Configuracion de los pines del lcd 12,11,5,4,3,2 -  Configurar para IC2!!!!!!!!!!!!!!!!!!!


/**************Seteo de Tiempos*************/ 

//------------------------------Monitor

unsigned long previousMillis = 0;
const long interval = 50 ;// Se achico el tiempo para que se pueda ver el segundero del RTC

//------------------------------Seteo

unsigned long previousMillis_1 = 0 ;
const long interval_1 = 10;



void setup() {

//------------------------------Config Salidas

  pinMode (led, OUTPUT); // LED de encendido / apagado

//------------------------------Config DHT

  float h = dht.readHumidity(); // Humedad
  float t = dht.readTemperature(); // Celcius
  float f = dht.readTemperature(true); // Fahrenheit

//------------------------------Iniciamos DHT

  if (isnan(h) || isnan(t) || isnan(f))
    lcd.print("error sensor DHT !");
  return;

  //----Mensaje de Bienvenida----//
  
  lcd.setCursor(4, 0);
  lcd.print("LAMyEN");

  lcd.setCursor(2, 1);
  lcd.print(" Cargando.");
  delay(1000);
  lcd.setCursor(2, 1);
  lcd.print(" Cargando..");
  delay(1000);
  lcd.setCursor(2, 1);
  lcd.print(" Cargando...");
  delay(1000);
  lcd.clear();

  lcd.setCursor(4, 0);
  lcd.print("LAMyEN");

  lcd.setCursor(2, 1);
  lcd.print(" Cargando.");
  delay(1000);
  lcd.setCursor(2, 1);
  lcd.print(" Cargando..");
  delay(1000);
  lcd.setCursor(2, 1);
  lcd.print(" Cargando...");
  delay(100);
  lcd.clear();

}

void loop() {

//------------------------------Monitor
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Monitor ();
  }

//------------------------------Seteo

  unsigned long currentMillis_1 = millis();

  if (currentMillis_1 - previousMillis_1 >= interval_1) {
    previousMillis_1 = currentMillis_1;
    Seteo (); 
  //delay (5000); 
  } 
}

/**************Funciones*************/

  void Seteo () {
  
  //----------Configuramos la EEPROM
      
  settemp = EEPROM.read(1); // lee settemp en la EEPROM
  EEPROM.write (1, settemp); //escribe en la EEPROM del atmega, dirección 1
  EEPROM.read (1); // lee en la EEPROM del atmega, dirección 1

  //----------Seteo mediante pulsador
  
  if (digitalRead(swtu) == 1) // si el pulsador se activa, setea 1 grado
                  {
                    (settemp ++);  // esta es la temperatura seteada
                  }
            /*        else
                    { // sino, no hacer nada
                    }*/

  if (digitalRead (swtd) == 1) // si el otro pulsador se activa, setea 1 grado
                  {
                    (settemp--);// pero quita 1 grado del settemp
                  }
            /*
              else
              {
                // sino, no hacer nada
              }*/

  if (t > settemp) // si la temperatura excede el valor seteado

                {
                  digitalWrite (led, HIGH); // prender 
                }
  else 
                {
                  digitalWrite (led, LOW); // apagar
                }      
      
      }

 void Monitor () { 
      
                lcd.setCursor (0, 0); // set the cursor to 0,0
                lcd.print (t);  // Imprime tamperatura en Grados Celsius
                lcd.print ('C');
                lcd.setCursor (0, 1); // setear el cursor a 0,1
                lcd.print ("Set a"); // imprimir el valor en grados celsius
                lcd.print (settemp);
                lcd.print ('C');
  }

