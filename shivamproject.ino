#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial rfid_reader(9, 10);
LiquidCrystal lcd(13, 12, 11, 6, 5, 4, 3);  /* For 4-bit mode */

int count = 0;                                          // count = 0
char input[12];                                         // character array of size 12
boolean flag = 0;

String card1 = "27002223AE88";
String card2 = "2700228D58D0";
String card3 = "270022245E7F";
String name1 = "Welcome Shivam!";
String name2 = "Welcome Sharjil!";
String name3 = "Welcome Person X";
String unknown = "Unauthorized Access!";

void setup()
{
  rfid_reader.begin(9600); // Setting the baud rate of Software Serial Library
  Serial.begin(9600);  //Setting the baud rate of Serial Monitor
  
  lcd.begin(16,2);  /* Initialize 16x2 LCD */
  lcd.clear();  /* Clear the LCD */
  
  lcd.print("AttendanceSystem");
}

void print_to_lcd(String msg, String card_id) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(msg);
    lcd.setCursor(0,1);
    lcd.print(card_id);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AttendanceSystem");
}

void identify_card(String card_id) {
  if (card_id.equals(card1)) {
    print_to_lcd(name1, card_id);
  }
  else if (card_id.equals(card2)) {
    print_to_lcd(name2, card_id);
  }
  //  else if(card_id.equals(card3)) {
//        print_to_lcd(name3, card_id);
  //  }
  else {
    print_to_lcd(unknown, card_id);
  }
}



void loop()
{
  if (rfid_reader.available())
  {
    count = 0;
    while (rfid_reader.available() && count < 12)         // Read 12 characters and store them in input array
    {
      input[count] = rfid_reader.read();
      count++;
      delay(5);
    }
    
    String card_id = String(input);
    card_id = card_id.substring(0, 12);
    Serial.println("\nYour card ID : " + card_id);
    identify_card(card_id);
  }
}
