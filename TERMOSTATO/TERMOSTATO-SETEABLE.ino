// written by Dylon Jamna (ME!)
// include the library code

#include <EEPROM.h>
#include <LiquidCrystal.h>// include the library code
#include "DHT.h"

int led =13; // Pn para el led
float settemp; //varible de seteo para temperatura ideal
int swtu = 7;  // Pulsador seteo en pin 7
int swtd = 6;   // Pulsador seteo en pin 6

#define DHTPIN 6 // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

float h ;// Humedad
float t ; // Grados Celsius
float f ; // Grados Farenheit

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Configuracion de los pines del lcd 12,11,5,4,3,2

void setup() {
  
  pinMode (led,1);  // Poner como salida el led 13
 
  float h = dht.readHumidity(); // Humedad
  float t = dht.readTemperature(); // Celcius
  float f = dht.readTemperature(true); // Fahrenheit
 
  if (isnan(h) || isnan(t) || isnan(f)) 
  lcd.print("Failed to read from DHT sensor!");
  return;
 
  lcd.begin(16,2); 
  lcd.setCursor(0,0); // Seteo de columna y linea
  lcd.print("Laboratorio"); // Display de bienvenida
  lcd.setCursor(0,1);
  lcd.print("LAMyEN");
  lcd.clear(); // clear the lcd
 
  EEPROM.read (1); // make the eeprom or atmega328 memory address 1
}

void loop() {
  
  lcd.setCursor (0,0); // set the cursor to 0,0
  lcd.print (t);  // Imprime tamperatura en Grados Celsius
  lcd.print ('C');
  settemp = EEPROM.read(1); // lee settemp en la EEPROM
 
             if (digitalRead(swtu)==1)// si el pulsador se activa, setea 1 grado
             {
             (settemp ++);  // esta es la temperatura seteada 
             }
              
             else
             {// sino, no hacer nada
             }

            if(digitalRead (swtd)==1)// si el otro pulsador se activa, setea 1 grado
            {
            (settemp--);// pero quita 1 grado del settemp
            }
            
            else   
            { 
            // sino, no hacer nada
            }

if (t > settemp) // si la temperatura excede el valor seteado
      
      {
      digitalWrite (led,1); // prender el led
      }
      
      else // si eso no ocurre, apagar el led
      
      {
      digitalWrite (led,0);
      }

lcd.setCursor (0,1); // setear el cursor a 0,1
lcd.print ("Set a"); // imprimir el valor en grados celsius
lcd.print (settemp);
lcd.print ('C');

EEPROM.write (1,settemp); /* se escribe el seteo de temperatrua de modo q quede grabado con la eeprom!*/
 
delay (5000); // esperar 250 milisegundos



} // Terminado
