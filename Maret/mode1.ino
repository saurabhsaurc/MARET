/*Mode 1 - PID control demonstration using the ultrasonic sensor
 *Input P,I,D and commanded distance ( in mm ) as the variables from main loop. Use a low pass filter to reduce noise.
 */
 
 void pidControlDistance( float Kp, float Ki, float Kd, float dist_c )
 {
    long distance = ultrasonicMeasurement();
    
    //Exponential moving average filter applied ( digital low pass filter )
    dist = (1-alpha)*dist + alpha*distance;
    
    float dist_e = dist_c - dist;
    long currentTime = millis();
    float delta_t = ( currentTime - prevTimeUltrasonic )/1000.0; //deltat in seconds
    prevTimeUltrasonic = currentTime;
  
    float deriv_error = ( dist_e - prevDistErrorUltrasonic )/delta_t; //Euclidean derivative
    prevDistErrorUltrasonic = dist_e;
  
    if( abs(dist_e) < 60 ) //This prevents integral windup
      errorSumUltrasonic = errorSumUltrasonic + dist_e*delta_t;
    else
      errorSumUltrasonic = 0;
    
    float K = 9.0/200; //Conversion factor
    float V_out = -K*( Kp*dist_e + Ki*errorSumUltrasonic + Kd*deriv_error );  
    int pwm_out = (int)( (V_out/9.0)*255 ) ;
    
    runMotors(pwm_out,pwm_out);
    
    delay(10); //10ms delay
 }
    
    
