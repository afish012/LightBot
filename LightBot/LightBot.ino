
//Alex Fisher, Goldsmiths University
//ID 33498506

//These four pins are for the LDRs.
int FORWARD = 11;
int RIGHT = 10;
int LEFT = 9;
int UP = 8;

//This array will store the values each LDR gives each loop.
int LDR_values[4] = {0,0,0,0}; //forward,right,left,up (11,10,9,8)


//These two pins are for each motor. The buggy uses a floating third wheel, so turning both motors on means it will go forwards.
int MOTOR_LEFT = 12;
int MOTOR_RIGHT = 13;


//This variable is how often the buggy does one loop.
int move_delay = 200;

/*
 * This function is used to calculate the values for each LDR. Each LDR is connected to the same ground and analog pin, whilst having different positive pins.
 * The pins are turned on and off sequentially to read the value for each LDR. The values are then added to the array.
 */
void read_pins() {
  digitalWrite(FORWARD, HIGH);
  LDR_values[0] = analogRead(A0);
  digitalWrite(FORWARD, LOW);

  digitalWrite(RIGHT, HIGH);
  LDR_values[1] = analogRead(A0);
  digitalWrite(RIGHT, LOW);

  digitalWrite(LEFT, HIGH);
  LDR_values[2] = analogRead(A0);
  digitalWrite(LEFT, LOW);

  digitalWrite(UP, HIGH);
  LDR_values[3] = analogRead(A0);
  digitalWrite(UP, LOW);
}

/*
 * This function is used to return which LDR gave the highest value in the current loop. It is a simple max function. The function returns
 * the index of the highest value, which maps to the LDRs like so:
 * 0: FORWARD (pin 11)
 * 1: RIGHT (pin 10)
 * 2: LEFT (pin 9)
 * 3: UP (pin 8)
 */
int get_highest_pin() {
  int highest = 0;
  int highest_val = -1;

  for (int i = 0; i < 4; i++) {
    if (LDR_values[i] > highest_val) {
      highest_val = LDR_values[i];
      highest = i;
    }
  }
  
  return highest;
}

/*
 * This function uses the value given by the previous function to determine how to drive the motors for the current loop.
 * The buggy will aim toward the LDR with the highest value. Since there are only two motors, they have to be driven in a specific way.
 */
void drive(int highest_pin) {
  switch (highest_pin) {
    case 0:                         //If the buggy needs to go forwards, both motors are powered.
      analogWrite(MOTOR_LEFT, 255);
      analogWrite(MOTOR_RIGHT, 255);
      break;
    case 1:                         //If the buggy needs to go right, the left motor is powered only.
      analogWrite(MOTOR_LEFT, 255);
      analogWrite(MOTOR_RIGHT, 0);
      break;
    case 2:                         //If the buggy needs to go left, the right motor is powered only.
      analogWrite(MOTOR_LEFT, 0);
      analogWrite(MOTOR_RIGHT, 255);
      break;
    case 3:                         //In the case that the above LDR is the brightest, the buggy does not need to move, so neither motor is powered.
      analogWrite(MOTOR_LEFT, 0);
      analogWrite(MOTOR_RIGHT, 0);
      break;
  }
}

void setup() {
  //set all the required pins for output.
  pinMode(FORWARD, OUTPUT);
  pinMode(RIGHT,OUTPUT);
  pinMode(LEFT,OUTPUT);
  pinMode(UP,OUTPUT);
  
  pinMode(MOTOR_LEFT,OUTPUT);
  pinMode(MOTOR_RIGHT,OUTPUT);

}

void loop() {
  read_pins(); //Load the values for each LDR.
  drive(get_highest_pin()); //Drive the motors accordingly.
  delay(move_delay); //Delay for set amount.
}
