#define SCREEN_WIDTH 128  
#define SCREEN_HEIGHT 64  

#define DISPLAY_HZ 20 //max refresh rate for the display

#define OLED_RESET -1        
#define SCREEN_ADDRESS 0x3C  

#define SMALL_30_TO_0_TIME_FONT 0  

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long displayLastUpdate = 0;

void displayOnLoop(){
 // if(millis() - displayLastUpdate >= 1000/DISPLAY_HZ){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(1);
    display.setTextSize(2);
    display.printf("%2.2f kph\n", linearVelocity*3.6);
    int displayCurrTimeRecordIdx = 0;
    for(int i = 0; i < 3; i++){
    //  Serial.println(displayCurrTimeRecordIdx + 1);
    display.fillRect(0, 15*(i+1), SCREEN_WIDTH, 15,0);
      display.setCursor(0, 15*(i+1));
      display.setTextSize(2);
      display.printf("%2.2f;", launchTotalTime[i][0]);
      display.setTextSize(2-SMALL_30_TO_0_TIME_FONT);
      display.printf("%2.2f\n", launchTotalTime[i][1]);
      //displayCurrTimeRecordIdx++;
    }
    display.display();
    displayLastUpdate = millis();
 // }
}