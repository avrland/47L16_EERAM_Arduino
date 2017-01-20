#include <Wire.h>
// 47L16-I/SN domyślnie A1,A0=0 zgłaszał się pod adresami 
// dla pamięci 0x50
// dla rejestrów 0x18
// http://www.esp8266.com/viewtopic.php?f=19&t=12427 sprawdzić
void setup()
{
  Wire.begin();
 
  Serial.begin(9600);
  Serial.println("Ladujemy do pamieci 47L16-I/SN");

}
 
 
void loop()
{
        if (Serial.available()>0) {
                // read the incoming byte:
                String incomingByte = Serial.readString();
                // say what you got:
                if(incomingByte == "R"){
                  Serial.println("Podaj znak:");
                  while(Serial.available()==0) {}                  
                    char literka = Serial.read();
                    Wire.beginTransmission(0x50);
                    Wire.write(0xA0);
                    Wire.write(0x00);
                    Wire.write(0x00);
                    Wire.write(literka);
                    int error = Wire.endTransmission();
                    Serial.print("Wyslano: ");
                    Serial.print(literka);
                    Serial.print(" Wynik: ");
                    Serial.println(error);
                }
                if(incomingByte == "A") {
                    Wire.beginTransmission(0x50);
                    Wire.write(0xA1);
                    Wire.write(0x00);
                    Wire.write(0x00);
                    int error1 = Wire.endTransmission();
                    Serial.print("Zlecono odczyt, wynik:");
                    Serial.println(error1);

                 //   Wire.beginTransmission(0x50);
                    Wire.requestFrom(0x50, 2);    // request 6 bytes from slave device #2
                    while(Wire.available())   // slave may send less than requested
                     {
                                 Serial.print("Odebrano: ");
                                 char c = Wire.read();    // receive a byte as character
                                 Serial.println(c);         // print the character
                     }
                   
                   int error = Wire.endTransmission();
              }
       }
}
