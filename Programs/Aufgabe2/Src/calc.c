
#include "calc.h"
#include "fsm.h"
#include <stdint.h>
#include <timer.h>


/**
 * @brief angle calculation 
 *
 * @return int
 */
double angle_calc(){
    return (step_count()/1200.0 * 360.0); // i thought 300 because of the 300 slits but 1200 is basicaly the amount of slits because 300*4 = 12 hence 1200
}


/**
 * @brief speed calculation of the rotation. 
 * @return int speed of the the rotation
 */
double speed_calc(uint32_t now, double angle)
{
	static double last_angle = 0.0;
	static uint32_t last_time = 0;
  static double cur_speed = 0.0;

  double delta_time = (now - last_time) / 90000000.0; // time diff in sec
  if((delta_time > 0.25 && cur_state() != STATE_NO_ROTATION) ||
    delta_time > 0.5)
  {
    double delta_angle = angle - last_angle;
    if(delta_time != 0) // div 0 check
    {
      cur_speed = delta_angle / delta_time;
    }

    last_angle = angle;
    last_time = now;
  }

  return cur_speed;
}
