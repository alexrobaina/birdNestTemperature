// Real time Library
#include <ThreeWire.h>  
#include <RtcDS1302.h>

#define PIN_RTC_CLK   5
#define PIN_RTC_DATA  4
#define PIN_RTC_RST   2

ThreeWire myWire(PIN_RTC_DATA, PIN_RTC_CLK, PIN_RTC_RST);
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
      Serial.begin(57600);
}

void loop() {
    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();
      
    if (!now.IsValid()) {
         Serial.println("Error en Fecha y Hora");
    }
     delay(1000);
}


#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}
