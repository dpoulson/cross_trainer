
#define TENSION_SENSOR_PIN  A5
#define RPM_SENSOR_PIN      12
#define MOTOR_OUTPUT_PIN1   11
#define MOTOR_OUTPUT_PIN2   10

#define VARIANCE            10

#define NUM_LEVELS          10

int levels[NUM_LEVELS] = { 0, 100, 200, 300, 400, 500, 600, 700, 800, 900 };

int current_level = 0;
int rpm;

void setup() {
  Serial.begin(115200);

  pinMode(TENSION_SENSOR_PIN, INPUT);
  pinMode(RPM_SENSOR_PIN, INPUT);
  pinMode(MOTOR_OUTPUT_PIN1, OUTPUT);
  pinMode(MOTOR_OUTPUT_PIN2, OUTPUT);

  // Find current tension sensor value, and work out what level that is
  Serial.print("Current sensor value: ");
  int tension = analogRead(TENSION_SENSOR_PIN);
  Serial.println(tension);
  for(int i = 0; i < NUM_LEVELS; i++) {
    Serial.print("Checking level: ");
    Serial.println(i);
    current_level = i;
    if (tension < levels[i])
      break;
  }
  Serial.print("Current tension level: ");
  Serial.println(current_level);

}

void loop() {
  int val = analogRead(TENSION_SENSOR_PIN);
  Serial.print(val);
  Serial.print(",");
  Serial.print(rpm);
  Serial.print(",");
  Serial.println(current_level);
  delay(500);

}

void set_level(int level) {
  // Set tension to level
  int request_value = levels[level-1];
  Serial.print("Setting Tension Level to: ");
  Serial.print(level);
  Serial.print(" Sensor value: ");
  Serial.println(request_value);
  while(request_value < analogRead(TENSION_SENSOR_PIN)-VARIANCE || request_value > analogRead(TENSION_SENSOR_PIN)+VARIANCE) {
    if (request_value > analogRead(TENSION_SENSOR_PIN) ) {
      // Request is higher, turn motor
      digitalWrite(MOTOR_OUTPUT_PIN1, HIGH);
      digitalWrite(MOTOR_OUTPUT_PIN2, LOW);
      
    } else {
      // Request is lower, turn motor
      digitalWrite(MOTOR_OUTPUT_PIN1, LOW);
      digitalWrite(MOTOR_OUTPUT_PIN2, HIGH);      
    }
  }
}
