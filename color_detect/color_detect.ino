int rgbbias[] = {100, 15, 0}; //sets the bias for the illuminated RGB LED: higher number = less intense (max 255)

int rgbds[] = {255, 255, 255};
int maxwhite[] = {773, 624, 542};
int minblack[] = {309, 134, 104};
int sensorValue = 0;
long previousMillis = 0; 

int speed = 5;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > 66) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
for(int i = 0; i < 3; i++){
sensorValue = analogRead(A8);
rgbds[i] = constrain(sensorValue, minblack[i], maxwhite[i]);
rgbds[i] = map(rgbds[i], minblack[i], maxwhite[i], 0, 255);
printresults(i);
//if(i==0){
//  Serial.println(rgbds[i]);
//}
rgbds[i] = (255 + rgbbias[i]) - rgbds[i];
rgbds[i] = constrain(rgbds[i], 0, 255);

}

}
}
void printresults(int i){
if(i == 0) Serial.print("RED:   ");
if(i == 1) Serial.print("GREEN: ");
if(i == 2) Serial.print("BLUE:  ");
Serial.println(rgbds[i]);
}
