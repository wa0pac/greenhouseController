
#include "Actuator.h"
#include "AsyncDelay.h"

int  actuatorStatus;
unsigned long currentPosition = 0;  //in millis
unsigned long extendTime = 50000; 
unsigned long retractTime = 60000;
AsyncDelay ActuatorMoveTimer;

void initActuator(){
  // set pins
  Serial.println("initActuator()");
  pinMode(ACTUATOR_EXTEND_PIN, OUTPUT);
  digitalWrite(ACTUATOR_EXTEND_PIN, LOW);
  pinMode(ACTUATOR_RETRACT_PIN, OUTPUT);
  digitalWrite(ACTUATOR_RETRACT_PIN, LOW);
  
//  // close Actuator
//  digitalWrite(ACTUATOR_RETRACT_PIN, HIGH);
//  delay(retractTime);  // 5000 for testing. 55000 
//  digitalWrite(ACTUATOR_RETRACT_PIN, LOW);
//  currentPosition = 0;

  ActuatorMoveTimer.start(0, AsyncDelay::MILLIS);
  // set status
  actuatorStatus = ACTUATOR_STATUS_EXTENDED;
  //set Timer to expired

  retractActuator();
}

int getActuatorStatus() {
  return actuatorStatus;
}

void extendActuator(){
  if(actuatorStatus != ACTUATOR_STATUS_EXTENDED){
    if(ActuatorMoveTimer.isExpired() || ActuatorMoveTimer.isStopped()){
      digitalWrite(ACTUATOR_RETRACT_PIN, LOW);
      digitalWrite(ACTUATOR_EXTEND_PIN, HIGH);
      ActuatorMoveTimer.start( extendTime, AsyncDelay::MILLIS);
      actuatorStatus = ACTUATOR_STATUS_EXTENDING;  
      Serial.println("Extend Actuator");  
    }
  }

}

void retractActuator(){
  if( actuatorStatus != ACTUATOR_STATUS_RETRACTED){
    if(ActuatorMoveTimer.isExpired() || ActuatorMoveTimer.isStopped()){
      digitalWrite(ACTUATOR_EXTEND_PIN, LOW);
      digitalWrite(ACTUATOR_RETRACT_PIN, HIGH);
      ActuatorMoveTimer.start( retractTime, AsyncDelay::MILLIS);
      actuatorStatus = ACTUATOR_STATUS_RETRACTING;
    }
  }
}

void stopActuator(){
  digitalWrite(ACTUATOR_EXTEND_PIN, LOW);
  digitalWrite(ACTUATOR_RETRACT_PIN, LOW);
  if( actuatorStatus == ACTUATOR_STATUS_EXTENDING ){
      actuatorStatus = ACTUATOR_STATUS_EXTENDED;
      currentPosition = extendTime;
    }
  if( actuatorStatus == ACTUATOR_STATUS_RETRACTING ){
      currentPosition = 0;
      actuatorStatus = ACTUATOR_STATUS_RETRACTED;
    }
}

void checkActuator(){
  if( ActuatorMoveTimer.isExpired() ) {
    stopActuator();
    ActuatorMoveTimer.stop();
  }
}