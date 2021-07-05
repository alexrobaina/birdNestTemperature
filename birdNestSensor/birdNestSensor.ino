/******************** BIRD NEST TEMPERATURE SENSOR ********************/

/* This project is created for to measure temperature in birds nests.

/**********************************************************************/

/************************ STATE DEFINED *******************************/
/*********************** ENDSTATE DEFINED *****************************/

/************************ IMPORT LIBRARIES *******************************/
/* SD Library */
#include <SPI.h>
#include <SD.h>

// Temperature sensor
#include <DHT.h>

// Clock real tyme
#include <ThreeWire.h>
#include <RtcDS1302.h>

/*********************** END IMPORT LIBRARYS ****************************/

/************************ DEFINE PIN CONSTANTS ****************************/

/* The circuit: SD card
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
*/

#define CONST_PIN_RTC_CLK 5
#define CONST_PIN_RTC_DATA 4
#define CONST_PIN_RTC_RST 2
#define CONST_DHT_PIN 8

/********************** END DEFINE PIN CONSTANTS ***************************/

/************************ DEFINE VARIABLES ****************************/

// Define pin constants
File dataFile;
int activateTypeTime;
int iterationCount;

/************************ END DEFINE VARIABLES ****************************/

/************************ START LIBRARIES ***************************/
// Clock Real time
ThreeWire myWire(CONST_PIN_RTC_DATA, CONST_PIN_RTC_CLK, CONST_PIN_RTC_RST);
RtcDS1302<ThreeWire> Rtc(myWire);

// Temperature sensor
DHT dht(CONST_DHT_PIN, DHT11);

/********************** END START LIBRARIES *************************/

void setup()
{
  Serial.begin(9600);

  dht.begin();

  if (!SD.begin(10))
  {
    Serial.println("SD initialization failed!");
    while (1)
      ;
  }

  createHeaderFile(dataFile);

  Serial.println("SD initialization done.");
  Serial.println("Welcome to temperature gauge");

  delay(1000);
}

void loop()
{
  delay(60000);
  iterationCount++;
  float temperature = dht.readTemperature();

  if (isnan(temperature))
  {
    saveError("Error in temperature sensor, dataFile);
    Serial.println("Error in temperature sensor");
    return;
  }

  RtcDateTime now = Rtc.GetDateTime();

  if (!now.IsValid())
  {
    saveError("Error in clock module", dataFile);
  }

  saveTemperatureData(now, dataFile, temperature);
  // examplePrint(now, temperature);
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void saveError(char errorMessage[250], File dataFile) 
{
  dataFile = SD.open("temp.txt", FILE_WRITE);
  dataFile.print(iterationCount);
  dataFile.print(",");
  dataFile.print(errorMessage);
  dataFile.println();
  dataFile.close();
}

void saveTemperatureData(const RtcDateTime &dt, File dataFile, float temperature)
{
  char dateString[20];
  char hourString[20];
  const char *hourType;
  int hourFormatted;

  if (dt.Hour() >= 12)
  {
    activateTypeTime = 1;
    hourFormatted = dt.Hour() - 12 * 1;
  }

  if (activateTypeTime == 1)
  {
    hourType = "PM";
  }
  else
  {
    hourType = "AM";
  }

  dataFile = SD.open("temp.txt", FILE_WRITE);

  if (dataFile)
  {
    dataFile.print(iterationCount);
    dataFile.print(",");

    snprintf_P(dateString,
               countof(dateString),
               PSTR("%02u/%02u/%04u %02u:%02u"),
               dt.Day(),
               dt.Month(),
               dt.Year(),
               hourFormatted,
               dt.Minute());

    dataFile.print(dateString);
    dataFile.print(" ");
    dataFile.print(hourType);

    dataFile.print(",");
    dataFile.print(temperature);

    dataFile.println();

    dataFile.close();
    Serial.println("Save success.");
  }
  else
  {
    Serial.println("error opening temp.txt");
  }
}

void createHeaderFile(File dataFile)
{
  dataFile = SD.open("temp.txt", FILE_WRITE);
  if (dataFile)
  {
    dataFile.print("#");
    dataFile.print(",");
    dataFile.print("Date Time");
    dataFile.print(",");
    dataFile.print("Temp *C");

    dataFile.println();

    dataFile.close();
    Serial.println("Print header done.");
  }
  else
  {
    Serial.println("Error opening test.txt");
  }
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void examplePrint(const RtcDateTime &dt, float temperature)
{
  char dateString[20];
  char hourString[20];
  int hourFormatted;

  if (dt.Hour() >= 12)
  {
    activateTypeTime = 1;
    hourFormatted = dt.Hour() - 12;
  }

  const char *hourType;

  if (activateTypeTime == 1)
  {
    hourType = "PM";
  }
  else
  {
    hourType = "AM";
  }

  Serial.print("#");
  Serial.print(",");
  Serial.print("Date Time");
  Serial.print(",");
  Serial.print("Temp *C");

  Serial.println();
  Serial.print(iterationCount);
  Serial.print(",");

  snprintf_P(dateString,
             countof(dateString),
             PSTR("%02u/%02u/%04u %02u:%02u"),
             dt.Day(),
             dt.Month(),
             dt.Year(),
             hourFormatted,
             dt.Minute());

  Serial.print(dateString);
  Serial.print(" ");
  Serial.print(hourType);
  Serial.print(",");
  Serial.print(temperature);

  Serial.println();
}
