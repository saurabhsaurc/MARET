/*Mode 3 - line following 
 *Simple line follower, black on white
 */
 
void lineFollow()
{
    readLineSensor();
    
    if( lf1==0 && lf2==0 && lf3==0 && lf4==0 && lf5==0 )
      runMotors(0,0);
    
    if( ( lf2 == 1 && lf3 == 1 && lf4 == 1 ) || ( lf2 == 0 && lf3 == 1 && lf4 == 0 ) )
    {
      //Just go straight
      runMotors(100,100);
    }
    else
    {
    
        if( lf2 == 1 )
        {
          //Turn left
          runMotors(50,150);
        }
        
        if( lf4 == 1 )
        {
          //Turn right
          runMotors(150,50);
        }
        
        if( lf1 == 1 )
        {
          //hard left
          runMotors(-50,150);
        }
        
        if( lf5 == 1 )
        {
          //hard right
          runMotors(150,-50);
        }
    
    }
    
    delay(10);
}
    
