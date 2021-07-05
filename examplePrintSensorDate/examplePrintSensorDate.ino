#include <Arduino.h>

void examplePrint(const RtcDateTime& dt, temperature)
{

   Serial.print("Temperature");
   Serial.print(",");
   Serial.print("Date");
   Serial.print(",");
   Serial.print("Time");
    
   Serial.println();
   Serial.print(temperature);
   Serial.print(",");
   
   char dateString[20];
   char hourString[20];
    
   snprintf_P(dateString, 
       countof(dateString),
       PSTR("%02u/%02u/%04u"),
       dt.Day(),
       dt.Month(),
       dt.Year());
  
   Serial.print(dateString);
   Serial.print(",");
   snprintf_P(hourString, 
       countof(hourString),
       PSTR("%02u:%02u"),
       dt.Hour(),
       dt.Minute());
   Serial.print(hourString);
   Serial.println();
 
   Serial.print("Temperature");
   Serial.print(",");
   Serial.print("Date");
   Serial.print(",");
   Serial.print("Time");
  
  Serial.println();
}
