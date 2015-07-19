byte counter;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2400);
  counter=0;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(counter);
  delay(100);
//  counter++;
//  if(counter > 255){
//    counter=0;
//  }
  

}
