/**
 * @file outputHandler.h
 * @author M. Sohrab Danandeh, HAW Hamburg
 * @date Oct 2025
 * @brief Drehgeber
 */


#ifndef outputHandler_h
#define outputHandler_h

#include <stdbool.h>



//output Pins
#define BSRR_MASK_D23		(0x01U << 7)
#define BSRR_MASK_D22		(0x01U << 6)
#define BSRR_MASK_D21		(0x01U << 5)

/**
 * @brief pritns on lcd
 * 
 */
void printInit() ;
    
/**
 * @brief 
 * 
 * @param stepCounter 
 */
void leds_show_step_count(int stepCounter);

/**
 * @brief turns on/off leds on the board
 * 
 */
void led_handler_status(void);


/**
 * @brief handles the movement and movement error leds  
 * 
 */
void led_handler_movement(void);

/**
 * @brief looks up the current angle
 * 
 * @param input from inputHandler
 */
void current_angle_change(double angle);


/**
 * @brief checks if angle speed changed 
 * 
 * @param input 
 * @return true it did then update it  
 * @return false it didnt dont update it 
 */
void current_angle_speed_check(double speed);

/**
 * @brief 
 * 
 */
void led_Error_Off(void);

/**
 * @brief char per loop print
 * 
 * @return int 
 */
void outputLoop(double my_angle, double my_speed);
 

#endif