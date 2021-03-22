/*
 * @file name: app_key.c
 * @Descripttion: 
 * @Author: zgw
 * @email: wuls@tuya.com
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-03-03 10:44:56
 * @LastEditors: zgw
 * @LastEditTime: 2021-03-08 11:07:26
 */
#include "app_key.h"
#include "tuya_gpio.h"
#include "tuya_key.h"

#define KEY_SWITCH_PIN                TY_GPIOA_26 //开关按键引脚
#define KEY_SET_PIN                   TY_GPIOA_28 //开关按键引脚
#define KEY_UP_PIN                    TY_GPIOA_7  //开关按键引脚
#define KEY_DOWN_PIN                  TY_GPIOA_8  //开关按键引脚 

void app_key_init(void)
{
    tuya_gpio_inout_set(KEY_SWITCH_PIN, TRUE);
    tuya_gpio_inout_set(KEY_SET_PIN, TRUE);
    tuya_gpio_inout_set(KEY_UP_PIN, TRUE);
    tuya_gpio_inout_set(KEY_DOWN_PIN, TRUE);
}

void app_key_scan(unsigned char *trg,unsigned char *cont)
{
    unsigned char read_data = 0x00;
    read_data = (tuya_gpio_read(KEY_SWITCH_PIN)<<3)|(tuya_gpio_read(KEY_SET_PIN)<<2)|(tuya_gpio_read(KEY_UP_PIN)<<1)|(tuya_gpio_read(KEY_DOWN_PIN));
    *trg = (read_data & (read_data ^ (*cont)));
    *cont = read_data;

}