#include <Wire.h>
 

void setup()
{
  Wire.begin();
 
  Serial.begin(9600);
  Serial.println("\nLadujemy do pamieci 47L16-I/SN");

}
 
 
void loop()
{
        if (Serial.available()>0) {
                // read the incoming byte:
                String incomingByte = Serial.readString();
                // say what you got:
                if(incomingByte == "R"){
                    Wire.beginTransmission(0x50);
                    Wire.write(0xA0);
                    Wire.write(0x00);
                    Wire.write(0x01);
                    Wire.write(0xAA);
                    int error = Wire.endTransmission();
                    Serial.print("Wyslano, wynik:");
                    Serial.println(error);
                }
                if(incomingByte == "A") {
                    Wire.beginTransmission(0x50);
                    Wire.write(0xA1);
                    Wire.write(0x00);
                    Wire.write(0x01);
                    int error1 = Wire.endTransmission();
                    Serial.print("Zlecono odczyt, wynik:");
                    Serial.println(error1);

                    
                    Wire.requestFrom(0x50, 6);    // request 6 bytes from slave device #2
                    while(Wire.available())   // slave may send less than requested
                     {
                                 Serial.print("Odebrano, wynik:");
                                 char c = Wire.read();    // receive a byte as character
                                 Serial.println(c);         // print the character
                     }
                   
                   //int error = Wire.endTransmission();
                  // Serial.println(error);
              }
       }
}
