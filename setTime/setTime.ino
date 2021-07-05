// Real time Library
#include <ThreeWire.h>  
#include <RtcDS1302.h>

// CONNECTIONS:
// DS1302 CLK/SCLK --> 5
// DS1302 DAT/IO --> 4
// DS1302 RST/CE --> 2
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND

#define PIN_RTC_CLK   5
#define PIN_RTC_DATA  4
#define PIN_RTC_RST   2

ThreeWire myWire(PIN_RTC_DATA, PIN_RTC_CLK, PIN_RTC_RST);
RtcDS1302<ThreeWire> Rtc(myWire);

void setup () 
{
    Serial.begin(57600);

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();
}

void loop () 
{
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
