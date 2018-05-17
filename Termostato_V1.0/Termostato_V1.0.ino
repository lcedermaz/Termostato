

 /* LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints Hello World! to the LCD
 and shows the time.

  The circuit
  LCD RS pin to digital pin 12
  LCD Enable pin to digital pin 11
  LCD D4 pin to digital pin 5
  LCD D5 pin to digital pin 4
  LCD D6 pin to digital pin 3
  LCD D7 pin to digital pin 2
  LCD RW pin to ground
  LCD VSS pin to ground
  LCD VCC pin to 5V
  10K resistor
  ends to +5V and ground
  wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (httpwww.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 httpwww.arduino.ccenTutorialLiquidCrystal
 
*/

//include the library code

#include LiquidCrystal.h
#include DHT.h
#include EEPROM.h

#define DHTPIN 6  what digital pin we're connected to
#define DHTTYPE DHT22    DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

int msg= 0; Barrera para el mensaje de bienvenida

int led =13;  Pin para el led
int settemp; varible de seteo para temperatura ideal (TMIN)
int settemp1 ; varible de seteo para temperatura ideal (TMAX)

int swtu = 7;   Pulsador seteo en pin 7 (TMIN)
int swtd = 8;    Pulsador seteo en pin 8 (TMIN)

int swtu1 = 9;   Pulsador seteo en pin 9 (TMAX)
int swtd1 = 10;    Pulsador seteo en pin 10 (TMAX)

int h ;  humedad (Número entero)
float t ;  Temperatura (Celsius)
float f ;  Temperatura (Farenheit)



LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  
  lcd.begin(16,2);  Print a message to the LCD. 
  dht.begin();
}

void loop()       {
    
-----------------------MENSAJE DE INICIO-----------------------        
       if(msg==0)  { 
       lcd.setCursor(0,0);
       lcd.print(  Laboratorio);
       lcd.setCursor(1,1);
       lcd.print(    LAMyEN);
       delay(2000);
       msg = 1;
       lcd.clear();
     }
-----------------------COMIENZO DEL PROGRAMA--------------------

  delay(250);
  int h = dht.readHumidity();  Humedad (Se cambio a número entero para los fines de ahorrar espacio en la pantalla LCD)
  float t = dht.readTemperature();  Celcius
  float f = dht.readTemperature(true);  Fahrenheit
 

 
  EEPROM.read (1);  Hacer la dirección 1 de la memoria EEPROM en el atmega 168   
  EEPROM.read (2);  Hacer la dirección 1 de la memoria EEPROM en el atmega 168 
  
  if (isnan(h)  isnan(t)  isnan(f)) {
    lcd.print(ERROR EN EL SENSOR!);
    return;
}

  lcd.setCursor(0, 0);
  lcd.print(T);
  lcd.print(t);
  lcd.print ((char)223);
  lcd.print(C); 
  lcd.print(  H);
  lcd.print(h);
  lcd.print(%); 
----------------VALORES SETEADOS----------------

  lcd.setCursor (0,1);  setear el cursor a 0,1
  lcd.print (T1);  imprimir el valor en grados celsius
  lcd.print (settemp);  valor 1
  lcd.print ((char)223);
  lcd.print ('C');
  lcd.print (  T2);  imprimir el valor en grados celsius
  lcd.print (settemp1);  valor 2
  lcd.print ((char)223); 
  lcd.print ('C');
  
-----------------ASIGNACIÓN DE LAS DIRECCIONES EN LA EEPROM-----------------
  
  settemp = EEPROM.read(1);  lee settemp en la EEPROM (TMIN)
  settemp1 = EEPROM.read(2);  lee settemp1 en la EEPROM (TMAX)

-----------------------------SET (TMIN)-------------------------------------

             if (digitalRead (swtu1)==1) si el pulsador se activa, setea 1 grado
             {
             (settemp++);   esta es la temperatura seteada 
             }
              
             else
             { sino, no hacer nada
             }

            if(digitalRead (swtd1)==1) si el otro pulsador se activa, setea 1 grado
            {
            (settemp--); pero quita 1 grado del settemp
            }
            
            else   
            { 
             sino, no hacer nada
            }     
-----------------------------SET(TMAX)----------------------------
        
             if (digitalRead (swtu)==1) si el pulsador se activa, setea 1 grado
             {
             (settemp1++);   esta es la temperatura seteada 
             }
              
             else
             { sino, no hacer nada
             }

            if(digitalRead (swtd)==1) si el otro pulsador se activa, setea 1 grado
            {
            (settemp1--); pero quita 1 grado del settemp
            }
            
            else   
            { 
             sino, no hacer nada
            }
-----------------------------CONDICION DE ESTADO----------------------------

if (( settemp  t )  ( t  settemp1 ))  si la temperatura esta dentro de los valores seteados
      
      {
      digitalWrite (led,1);  prender el led
      }
      
      else  si eso no ocurre, apagar el led
      
      {
      digitalWrite (led,0);
      }
      
EEPROM.write (1,settemp); 
EEPROM.write (2,settemp1); 

}
 finaliza el programa

