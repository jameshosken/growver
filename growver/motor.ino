void setupMotor() {
  //motor setup

  pinMode(MOTOR_PIN, OUTPUT);

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);

  myMotor2->setSpeed(150);
  myMotor2->run(FORWARD);
  // turn on motor
  myMotor2->run(RELEASE);
}

void handleMotor(int ldr1, int ldr2, int ldr3, int ldr4) {
  
  if (spd < max_spd) {
    if (millis() % 1 == 0) {
      spd++;
      delay(1);
    }
    myMotor->setSpeed(spd);
    myMotor2->setSpeed(spd);
  }
  Serial.print("CumulativeLDR: ");
  Serial.println((ldr1 + ldr2 + ldr3 + ldr4) / 4) ;
  if ( (ldr1 + ldr2 + ldr3 + ldr4) / 4 > goodLightThreshold) {
    stopGoing();
    return;
  }

  if(millis() - checkpoint > interval){
    checkpoint = millis();
    interval = random(5000,10000);
    //Choose random direction:
    int r = random(0,3);
    switch(r){
      case 0:
        goForward();
        break;
      case 1:
        goLeft();
        break;
      case 2:
        goRight();
        break;
      default:
        //Nothing
        break;
    }
  }
}


void goLeft() {
  Serial.println("GOING LEFT");
  myMotor->run(BACKWARD);
  myMotor2->run(FORWARD);
  current_direction = LEFT;
}
void goRight() {
  Serial.println("GOING RIGHT");
  myMotor->run(FORWARD);
  myMotor2->run(BACKWARD);
  current_direction = RIGHT;
}
void goForward() {
  Serial.println("GOING FWD");
  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);
  current_direction = FWD;
}

void stopGoing() {
  Serial.println("STOP");
  spd = 0;
  myMotor->run(RELEASE);
  myMotor2->run(RELEASE);
  current_direction = OFF;
}
