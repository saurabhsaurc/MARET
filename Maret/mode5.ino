//For testing encoders

void testenc(){

  runMotors(255*encoderLdirection,100*encoderRdirection);  

  //Determining position x,y,phi
  float d_thetaL = thetaL - prev_thetaL;
  prev_thetaL = thetaL;
  float d_thetaR = thetaR - prev_thetaR;
  prev_thetaR = thetaR;  

  pos_phi = pos_phi + (d_thetaL - d_thetaR)*radius_wheel/(2*radius_bot);
  pos_x = pos_x + cos(pos_phi)* (d_thetaL + d_thetaR)*radius_wheel/2 ;
  pos_y = pos_y + sin(pos_phi)* (d_thetaL + d_thetaR)*radius_wheel/2 ;
  
  Serial.print("thetaL: ");
  Serial.print(thetaL);
  Serial.print(" thetaR: ");
  Serial.print(thetaR);
  Serial.print(" x: ");
  Serial.print(pos_x);
  Serial.print(" y: ");
  Serial.print(pos_y);
  Serial.print(" phi: ");
  Serial.println(pos_phi); 

  delay(100);
}

