// Define I2C Address where the PCF8574* is


// Initialize LiquadCrystal with pin setup
;

int LDR_Pin = A0; //analog pin 0
int led = 13;

// 10k between GND and A0
// LDR between 5V and A0

// настроить чувствительность фотоэлемента
#define LEVEL_LDR 150

#define MORSE_EMPTY 0

// Этими символами мы будем обозначать точки и тире.
#define MORSE_DOT '*'
#define MORSE_DASH '-'

//Длина точки и тире для 24 слов в минуту (wpm) = 150 мс и 700 мс,
// Для 12 wpm = 700 и 1200

#define MORSE_TIME_DOT 700
#define MORSE_TIME_DASH 1200

// Максимальная длина символа азбуки Морзе (в точках и тире)
#define MAX_MORSE_SYMBOL_LENGTH 8
char* morseSymbol[MAX_MORSE_SYMBOL_LENGTH];
unsigned int morseSymbolLen;
char* newMorseSignal; // Новый введенный сигнал - точка или тире.

// Таблица кодов Морзе. N-ный элемент кода соответствует n-ному символу раскладки.
char* code[] = {
"*-","-***","*--","--*","-**","*","***-","--**","**","*---",
"-*-","*-**","--","-*","---","*--*","*-*","***","-","**-",
"**-*","****","-*-*","---*","----","--*-","-*--","-**-","**-**","**--",
"*-*-",
"*----","**---","***--","****-","*****","-****","--***","---**","----*","-----",
"......","*-*-*-","---***","-*-*-","-*--*-","*----*","*-**-*","-****-","-**-*","**--**","--**--",
"-***-","********","*--*-*","**-*-",
""
};

// Латинская раскладка.
char* layoutLatin[] = {
"a","b","w","g","d","e","v","z","i","j",
"k","l","m","n","o","p","r","s","t","u",
"f","h","c","ö","ch","q","y","x","é","ü",
"ä",
"1","2","3","4","5","6","7","8","9","0",
".",",",":",";","(","\'","\"","-","/","?","!",
" *DELIMITER* "," *ERR* ","@"," *END* ",
""
};

void setup(){
  Serial.begin(9600);




// Print Hello World
// lcd.print("GOTOV priem"); 



  pinMode(led, OUTPUT); 

  morseSymbolLen = 0;


  newMorseSignal = MORSE_EMPTY;

}
  int counter_high = 0;
  int counter_low = 0;
  int i;
  void loop(){
    
    int LDRReading = analogRead(LDR_Pin);
//Serial.println(LDRReading);
//delay(100); 
    if (LDRReading >= LEVEL_LDR ){
      counter_high++ ;
      if (counter_low > MORSE_TIME_DASH) {
        sendMorseSymbol();
        morseSymbolLen=0;
      }

      counter_low=0;
      digitalWrite(led, HIGH);


    } else {
      counter_low++;
      if(counter_high > 0){
      if ( (counter_high < MORSE_TIME_DASH ) &&( counter_high >MORSE_TIME_DOT)){
        //Serial.print(".");
        newMorseSignal="*";
        morseSymbol[morseSymbolLen++] = newMorseSignal;
      }
      if ( counter_high > MORSE_TIME_DASH ){
        //Serial.print("-");
        newMorseSignal="-";
        morseSymbol[morseSymbolLen++] = newMorseSignal;

      }

      counter_high=0;
      digitalWrite(led, LOW);

     }
      

    }
   if((counter_low == 0) &&(counter_high == 0)&& (morseSymbolLen > 0)) {
      sendMorseSymbol();
      morseSymbolLen = 0;
      Serial.println("");
    }
      
  }
void sendMorseSymbol() 
{
  
//Serial.println("enter");

boolean est;
int i, j;
est=false;
if (morseSymbolLen < 1) 
{
  //Serial.print("exit");
  

return;
}



// Символ из таблицы кодов Морзе соответствует введенному символу.
// Отправим символ на компьютер.

String str1;
  str1="";
for (i=0;i<morseSymbolLen;i++)
{ 
str1=str1+morseSymbol[i];
} 
//Serial.println(str1);
for (i=0;i<56;i++)
{
String str2(code[i]);
if (str1.compareTo(str2)==0)
{
//Serial.print(str2);
est=true;
break;
}
}

if (est!=false)
{
Serial.print(layoutLatin[i]);
}

// Вывод символа на LCD экран

morseSymbolLen = 0;
return;

}

