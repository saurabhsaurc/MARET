//This tab contains the functions to run the motors via PWM

void runMotors(int L1_speed, int L2_speed)
{
  //Speed will be given as pwm. But it can be negative. Also check for cap
  //L1,M1 - left, L2,M2 - right
  if(L1_speed < 0)
  {
    digitalWrite(M1_pin_A,LOW);
    digitalWrite(M1_pin_B,HIGH);
    L1_speed = -L1_speed;
  }
  else
  {
    digitalWrite(M1_pin_A,HIGH);
    digitalWrite(M1_pin_B,LOW);
  }
  
  if(L1_speed > 255)
    L1_speed = 255;
  
  analogWrite(M1_pin_PWM , L1_speed);
  
  if(L2_speed < 0)
  {
    digitalWrite(M2_pin_A,HIGH);
    digitalWrite(M2_pin_B,LOW);
    L2_speed = -L2_speed;
  }
  else
  {
    digitalWrite(M2_pin_A,LOW);
    digitalWrite(M2_pin_B,HIGH);
  }
  
  if(L2_speed > 255)
    L2_speed = 255;
  
  analogWrite(M2_pin_PWM , L2_speed);
    
}
