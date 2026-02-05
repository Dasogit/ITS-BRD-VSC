/**
 * @file io.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-02-03
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "io.h"
#include "LCD_GUI.h"
#include "delay.h"
#include "stm32f429xx.h"
#include "timer.h"
#include <stdint.h>


uint8_t getButtons(void){
//uint8_t getButton(){
    return ~(GPIOF->IDR);
}

void setOn(uint16_t leds){
    GPIOD->BSRR = leds & 0xff;
    GPIOE->BSRR = (leds >> 8) & 0xff;
}

void setOff(uint16_t leds){
    GPIOD->BSRR = (leds & 0xff) << 16;
    GPIOE->BSRR = ((leds >> 8) & 0xff) << 16;
}

uint8_t buttons_pressed_events(void){
//bool buttonEntprellen(uint8_t button){
    
    /* if(button < 0 || button > 8){
        return false;
    }
    int mask = (1u << button);
    for(int i = 0; i <LESEVERSUCHE; ++i ){
        bool taste = getButton();
        delay(500);
        if(taste == getButton()){
            return true;
        }
    }
    return false; */
    
}
uint32_t zeitDiff(uint32_t z1, uint32_t z2){
    uint32_t diff = (z2 > z1) ? z2 - z1 : INT32_MAX - z1 + z2;
    return diff/90000000; 
}

//void button_update_1ms(int arr[], int size ){
void button_update_1ms(){
}

