#include "Watchy_vumeter.h"

#define DARKMODE false

int UteZ = 0;
int UteM = 0;
int8_t batLev;

void Watchyvumeter::drawWatchFace(){
    display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    drawTime();
    drawBattery();
    
}
void Watchyvumeter::drawTime(){

  // reset step counter at midnight
    if (currentTime.Hour == 00 && currentTime.Minute == 00){
      sensor.resetStepCounter();
              //turn off radios
      WiFi.mode(WIFI_OFF);
      btStop();
    }
	// time adjustment of 15,5 seconds each day (Watchy runs too fast)

    if (currentTime.Hour == 00 && currentTime.Minute == 30){
        
        RTC.read(currentTime);
        int8_t sekunde = currentTime.Second;
        int8_t minute = currentTime.Minute;
        int8_t hour = currentTime.Hour;
        int8_t day = currentTime.Day;
        int8_t month = currentTime.Month;
        int8_t year = tmYearToY2k(currentTime.Year);

        delay(15500);

        tmElements_t tm;
        tm.Month = month;
        tm.Day = day;
        tm.Year = y2kYearToTm(year);
        tm.Hour = hour;
        tm.Minute = minute ;
        tm.Second = sekunde;

        RTC.set(tm);
                
         }
	// end of time adjustment, if you don't like a time adjustment, just delete above lines
  
    int8_t Stunde = currentTime.Hour ;
        
    int8_t Minute = currentTime.Minute;
    
    display.setFont(&FreeSans8pt7b);
    display.writeFastVLine(14, 20, 180, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setCursor(38, 17);
    display.println("5");
    display.writeFastVLine(44, 20, 180, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    display.setCursor(65, 17);
    display.println("10");
    display.writeFastVLine(74, 20, 180, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    display.setCursor(95, 17);
    display.println("15");
    display.writeFastVLine(104, 20, 120, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    display.setCursor(125, 17);
    display.println("20");
    display.writeFastVLine(134, 20, 120, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);


    display.setCursor(155, 17);
    display.println("25");
    display.writeFastVLine(164, 20, 120, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    display.setCursor(185, 17);
    display.println("30");
    display.writeFastVLine(194, 20, 120, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    display.writeFastHLine(14, 20, 186, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setCursor(0, 35);
    display.println("h");
    display.writeFastHLine(0, 40, 200, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setCursor(0, 65);
    display.println("m");
    display.writeFastHLine(0, 80, 200, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setCursor(0, 95);
    display.println("D");
    display.writeFastHLine(0, 100, 200, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setCursor(0, 115);
    display.println("M");
    display.writeFastHLine(0, 120, 200, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.writeFastHLine(0, 140, 200, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setCursor(0, 135);
    display.println("B");
    display.writeFastHLine(14, 200, 60, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.setCursor(0, 155);
    display.println("S");
    display.setCursor(0, 170);
    display.println("T");
    display.setCursor(0, 185);
    display.println("E");
    display.setCursor(0, 200);
    display.println("P");


    for (int n = 1; n <= Stunde; n++) {
        display.fillRect((8 + (n * 6)), 25, 5, 10, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
            }
   

    if (Minute > 30) {
        UteM = Minute - 30;
        Minute = 30;
    }
    else UteM = 0;


        for (int n = 1; n <= Minute; n++) {
            display.fillRect((8 + (n * 6)), 45, 5, 10, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        }

    for (int n = 1; n <= UteM; n++) {
        display.fillRect((8 + (n * 6)), 65, 5, 10, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    
    for (int n = 1; n <= currentTime.Day; n++) {
        display.fillRect((8 + (n * 6)), 85, 5, 10, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    
    for (int n = 1; n <= currentTime.Month; n++) {
        display.fillRect((8 + (n * 6)), 105, 5, 10, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    
}
void Watchyvumeter::drawBattery() {

    float VBAT = getBatteryVoltage();

    if (VBAT > 4.15) {
        batLev = 100;
    }
    else batLev = 100 - ((4.15 - VBAT) * 100);
    UteM = batLev / 3.33;

    for (int n = 1; n <= UteM; n++) {
        display.fillRect((8 + (n * 6)), 125, 5, 10, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

          
        uint32_t stepCount = sensor.getCounter();
        UteZ = stepCount / 10000;
        
        for (int n = 1; n <= UteZ; n++) {
          display.fillRect((8 + (n * 6)), 145, 5, 10, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        }
        stepCount = stepCount - (UteZ * 10000);
        UteZ = stepCount / 1000;
        for (int n = 1; n <= UteZ; n++) {
            display.fillRect((8 + (n * 6)), 165, 5, 10, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        }
        stepCount = stepCount - (UteZ * 1000);
        UteZ = stepCount / 100;
        for (int n = 1; n <= UteZ; n++) {
            display.fillRect((8 + (n * 6)), 185, 5, 10, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        }
        UteZ = currentTime.Wday;
               
        if (UteZ == 1) {
            display.drawBitmap(100, 140, son, 70, 60, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);            
        }

        if (UteZ == 2) {
            display.drawBitmap(100, 140, mon, 70, 60, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        }

        if (UteZ == 3) {
            display.drawBitmap(100, 140, die, 70, 60, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        }

        if (UteZ == 4) {
            display.drawBitmap(100, 140, mit, 70, 60, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        }

        if (UteZ == 5) {
            display.drawBitmap(100, 140, don, 70, 60, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        }

        if (UteZ == 6) {
            display.drawBitmap(100, 140, fre, 70, 60, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        }

        if (UteZ == 7) {
            display.drawBitmap(100, 140, sam, 70, 60, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        }

}


