/*
 * Arduino LEDs Control
 * 
 */
#include <Matrix.h>
#include <Sprite.h>

const int numChips = 1;
int state,x,y;
char input;
String str="";

//                   DIN, CLK, LOAD, #chips
Matrix myLeds = Matrix(9, 2, 3, numChips);

int rgbbias[] = {100, 15, 0}; //sets the bias for the illuminated RGB LED: higher number = less intense (max 255)

int rgbds[] = {255, 255, 255};
int maxwhite[] = {773, 624, 542};
int minblack[] = {309, 134, 104};

long previousMillis = 0; 
int c = 0;
int d = 0;
int count=0;
int val = 0;       // variable to store the data from the serial port
int bits[16];
long interval = 100;
String currentBitValue = "00000000";
String binary="0";
char binaryValue;
String binaryString = "";
unsigned char binaryResult;
String commandString = "";
int pinNumbers[] = {A8,A5,A3,A17,A9,A6,A4,A14,22,23,26,27,28,29,30,31,32};
int pinReadBias[] = {620,680,710,770,895,1015,915,880,680,725,725,725,725,725,725,725};
int bitsUsed = 8;
int pinArr1[] = {A8,A5,A3,A17,A9,A6,A4,A14};
int arr1[] = {0,0,0,0,0,0,0,0};
int flipBit = 0;
unsigned long prevTime=0;
boolean flip = true;


void setup() {
  myLeds.clear();
  myLeds.setBrightness(15);
  Serial.begin(9600);        // connect to the serial port
}

void loop () {
  while(Serial.available()){
    input=Serial.read();
    str.concat(input);
    
   // Serial.write(input);
  }
  String binStr="";
if(str.length()>0){
  
 // Define 
//String str = "Bet"; 

// Length (with one extra character for the null terminator)
int str_len = str.length() + 1; 
// Prepare the character array (the buffer) 
char char_array[str_len];

// Copy it over 

str.toCharArray(char_array, str_len);
//myLeds.write(0,6,HIGH);
for(int i=0; i<str_len-1; i++){
  for(int w=7;w>=0;w--){
  byte bytes = bitRead(char_array[i],w);
  binStr=binStr + bytes;
  
  }
  binLight(binStr);
  binStr="";
  delay(50);
  myLeds.clear();
  delay(50);
}


str="";
}
    for(int w=0;w<8;w++){
     arr1[w]= getRVal(analogRead(pinArr1[w]));
    }
     if(230<arr1[0]){
      
       for(int w=1;w<8;w++){
        Serial.print(arr1[w]); 
        Serial.print(",");
       }
       Serial.println();  
     }
}
  
    
 
int getRVal(int sensVal){
 for(int i = 0; i < 3; i++){
  rgbds[i] = constrain(sensVal, minblack[i], maxwhite[i]);
  rgbds[i] = map(rgbds[i], minblack[i], maxwhite[i], 0, 255);
  if(i==0){
    return rgbds[i];
  }
  }   
  return 0;
}

String debinaryStringify(String source) {
    String result = "";
    int idxStart = 0;
    do {
        char val = 0;
        for (int i=0; i<8; i++) {
            val += ((source.charAt(idxStart+i) == '1') << (7-i)); // Trick: Assignment of an evaluation result
        }
        result.concat(val);
        idxStart = source.indexOf(' ') + 1;
    } while ( (idxStart > 0) && (idxStart < source.length() - 7) );
    return result;
}

void binLightOff(String bin){
  int str_len = bin.length() + 1; 
// Prepare the character array (the buffer) 
char char_array[str_len];

// Copy it over 

bin.toCharArray(char_array, str_len);
  /*if(char_array[0]=='1'){
    myLeds.write(0,6,LOW);
  }*/
  if(char_array[1]=='1'){
    myLeds.write(7,6,LOW);
  }
  if(char_array[2]=='1'){
    myLeds.write(6,6,LOW);
  }
  if(char_array[3]=='1'){
    myLeds.write(5,6,LOW);
  }
  if(char_array[4]=='1'){
    myLeds.write(4,6,LOW);
  }
  if(char_array[5]=='1'){
    myLeds.write(3,6,LOW);
  }
  if(char_array[6]=='1'){
    myLeds.write(2,6,LOW);
  }
  if(char_array[7]=='1'){
    myLeds.write(1,6,LOW);
  }
  
  
}

void binLight(String bin){
  int str_len = bin.length() + 1; 
// Prepare the character array (the buffer) 
char char_array[str_len];

// Copy it over 

bin.toCharArray(char_array, str_len);
 /* if(char_array[0]=='1'){
    myLeds.write(0,6,HIGH);
  }*/
  if(char_array[1]=='1'){
    myLeds.write(7,6,HIGH);
  }
  if(char_array[2]=='1'){
    myLeds.write(6,6,HIGH);
  }
  if(char_array[3]=='1'){
    myLeds.write(5,6,HIGH);
  }
  if(char_array[4]=='1'){
    myLeds.write(4,6,HIGH);
  }
  if(char_array[5]=='1'){
    myLeds.write(3,6,HIGH);
  }
  if(char_array[6]=='1'){
    myLeds.write(2,6,HIGH);
  }
  if(char_array[7]=='1'){
    myLeds.write(1,6,HIGH);
  }
}

char getBit(int pinNumber, int readBounds) {
  
    d=analogRead(pinNumber);
    c = d;
    
    if (d>=readBounds)
      binaryValue = '1';
    else
      binaryValue = '0';
      testPinBias(d, binaryValue);
    //Serial.print(binaryValue);
    //Serial.print("\n");
    return binaryValue;
  
}

void testPinBias (int d, int binaryValue) {
  //Serial.print(d);
  //Serial.print("   ");
}


