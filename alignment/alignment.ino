
int BASE_PIN_DIRS[4]; // the direction pins for motor
int BASE_PIN_PWMS[4]; // the pwm pins for motor
#define NOS 2 //number of sensors (ultrasonic)
#define THRESHOLD 5 //distance upto which measurements are accurate in cm
int TRIG_PINS[NOS] = {9,11}; 
int ECHO_PINS[NOS] = {10,12};
// defines variables
long DURATIONS[NOS]; //stores the time gap
float DISTANCES[NOS]; //stores the NOS distances of each sensor marked from 1 to NOS acc to anticlockwise conv.


void setup() {
  // put your setup code here, to run once:
  for(int i = 0;i < NOS;i++){
    pinMode(TRIG_PINS[i],OUTPUT);
    pinMode(ECHO_PINS[i],INPUT);
    DISTANCES[i] = 0;
  }
  //Serial.begin(9600);
}

void loop() {
  /* get the first ultra sensor distance*/  
  // put your main code here, to run repeatedly:
  /*for alignment*/
  getDistances();
  while(DISTANCES[4] != DISTANCES[5] && DISTANCES[4] > THRESHOLD){ //coz these two are used for alignment with edge
    if(DISTANCES[4] < DISTANCES[5]){
      rotClock(100,20); //parameters are the pwm and delay respectively
    }
    else if(DISTANCES[5] < DISTANCES[4]){
      rotAntiClock(100,20);
    }
    else{
      movBwd(100,20); //parameters are the pwm and delay respectively
    }
    getDistances(); //for feedback checking
  }
}

void getDistances(){ //for getting the distances from ultrasonics simultaneously
  for(int i = 0;i < NOS;i++){
    digitalWrite(TRIG_PINS[i], LOW);
  }
  delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
  for(int i = 0;i < NOS;i++){
    digitalWrite(TRIG_PINS[i], HIGH);
  }
  delayMicroseconds(10);
  for(int i = 0;i < NOS;i++){
    digitalWrite(TRIG_PINS[i], LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
    DURATIONS[i] = pulseIn(ECHO_PINS[i], HIGH);
// Calculating the distance
    DISTANCES[i]= DURATIONS[i]*0.034/2;
  }
}

void rotClock(int a,int b){ //for rotating the bot clockwise
  for(int i = 0;i < 4;i++){
    digitalWrite(BASE_PIN_DIRS[i],LOW); //assuming LOW moves in -ve direction acc to convention in 4s base
    analogWrite(BASE_PIN_PWMS[i],a); //can be changed depending on the speed you want
  }
  delay(b); //the waiting period for each rotate step
}

void rotAntiClock(int a,int b){ //for rotating the bot anti clockwise
  for(int i = 0;i < 4;i++){
    digitalWrite(BASE_PIN_DIRS[i],HIGH); //assuming LOW moves in -ve direction acc to convention in 4s base
    analogWrite(BASE_PIN_PWMS[i],a); //can be changed depending on the speed you want
  }
  delay(b); //the waiting period for each rotate step
}

void movBwd(int a,int b){
  for(int i = 0;i < 4;i = i++){
    if(i == 0 || i == 2){ //coz zero and 2 are oriented for fwd/bwd motion
      digitalWrite(BASE_PIN_DIRS[i],LOW); //assuming LOW moves in -ve direction acc to convention in 4s base
      analogWrite(BASE_PIN_PWMS[i],a); //a is pwm
    }
    else{
      analogWrite(BASE_PIN_PWMS[i],0); //we dont want the other 2 wheels to rotate as they are not oriented along the curr direction
    }
  }
  delay(b); 
}
