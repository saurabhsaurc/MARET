/*Mode 2 - Light sensitive robot - demonstration of braitenberg vehicle
 *follow the gradient of the light
 */
 
void moveTowardsLight()
{
  getLightSensors();
  
  float K1 = 2.0; 
  float K2 = 2.0;
  
  float left_motor_speed = K1*( L_front - (L_left+L_right)/2 ) - K2*( L_left - L_right );
  float right_motor_speed = K1*( L_front - (L_left+L_right)/2 ) + K2*( L_left - L_right );
  
  runMotors( (int)left_motor_speed, (int)right_motor_speed );
  
  delay(10);
}
