/*Mode 4- obstacle avoidance
 *Avoid obstacles on the left side by turning right when obstacle is detected, then turn left when obstacle not detected.
 *Use a delay of 10ms in between
 */
 
void avoidObstacles()
{
    getObstacleSensors();
    
    //Default: go ahead
    if( prox1 ==0 && prox2 ==0 && prox3 ==0 && prox4 ==0 && prox5 ==0 )
      runMotors(200,200);
      
    //Soft left or right
    if( prox1 == 1)
      runMotors(255,100);
      
    if( prox5 == 1)
      runMotors(100,255);
      
    //Moderate left or right
    if( prox2 == 1)
      runMotors(255,0);
      
    if( prox4 == 1)
      runMotors(0,255);
     
    //Hard left or hard right
    if(prox3 == 1)
    {
      if( prox2 == 1)
        runMotors(255,-255);
      else
        runMotors(-255,255);
    }
      
    delay(10);
}
