//For testing encoders

void testenc(){

  runMotors(200*encoderLdirection,100*encoderRdirection);

  //Determining position x,y,phi
  
  float d_thetaL = thetaL - prev_thetaL;
  prev_thetaL = thetaL;
  float d_thetaR = thetaR - prev_thetaR;
  prev_thetaR = thetaR;  

  long currentTime = millis();
  float delta_t = ( currentTime - prevTimeEnc )/1000.0; //deltat in seconds
  prevTimeEnc = currentTime;

  pos_phi = pos_phi + (d_thetaR - d_thetaL)*radius_wheel/(2*radius_bot);
  pos_x = pos_x - sin(pos_phi)* (d_thetaL + d_thetaR)*radius_wheel/2 ;
  pos_y = pos_y + cos(pos_phi)* (d_thetaL + d_thetaR)*radius_wheel/2 ;
  
  Serial.print(thetaL);
  Serial.print(" ");
  Serial.print(thetaR);
  Serial.print(" ");
  Serial.print(pos_x);
  Serial.print(" ");
  Serial.print(pos_y);
  Serial.print(" ");
  Serial.println(pos_phi); 

  delay(20);
}

