/*
 * @Author: zgw
 * @email: liang.zhang@tuya.com
 * @LastEditors: zgw
 * @file name: sht21.h
 * @Description: SHT21 IIC drive src file
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2020-12-16 18:51:29
 * @LastEditTime: 2021-03-12 18:34:27
 */

#include "app_control.h"
#include "tuya_gpio.h"
#include "tuya_uart.h"
#include "BkDriverUart.h"
#include "sys_timer.h"
#include "uni_time.h"
#include "app_key.h"
/***********************************************************
*************************types define***********************
***********************************************************/
typedef enum
{
    LOW = 0,
    HIGH,
}default_level;


APP_CTRL_DATA_T app_ctrl_data = {0};

UINT8_T key_buf = 0;
UINT8_T key_old = 0;
UINT8_T key_delay_cont = 0;

UINT8_T key_trg = 0x00;
UINT8_T key_cont = 0x00;
/***********************************************************
*************************IO control device define***********
***********************************************************/


/***********************************************************
*************************about adc init*********************
***********************************************************/


/***********************************************************
*************************about iic init*********************
***********************************************************/


/***********************************************************
*************************function***************************
***********************************************************/

STATIC VOID __ctrl_gpio_init(CONST TY_GPIO_PORT_E port, CONST BOOL_T high)
{   
    //Set IO port as output mode
    tuya_gpio_inout_set(port, FALSE);
    //Set IO port level
    tuya_gpio_write(port, high);
}


VOID app_device_init(VOID)
{
    INT_T op_ret = 0;

    app_key_init();
}

STATIC VOID app_key_event(UINT8_T key_event)
{
    if(key_event == KEY_CODE_1) {
        PR_NOTICE("--------------key 1 short press-------------");
        app_ctrl_data.key_state = key_1_short;
    }else if(key_event == KEY_CODE_2) {
        PR_NOTICE("--------------key 2 short press-------------");
        app_ctrl_data.key_state = key_2_short;
    }else if(key_event == KEY_CODE_3) {
        PR_NOTICE("--------------key 3 short press-------------");
        app_ctrl_data.key_state = key_3_short;
    }else if(key_event == KEY_CODE_4) {
        PR_NOTICE("--------------key 4 short press-------------");
        app_ctrl_data.key_state = key_4_short;
    }else if(key_event == KEY_CODE_1_2) {
        PR_NOTICE("--------------key 1 and key 2 comb-------------");
        app_ctrl_data.key_state = key_1_2_comb;
    }else if(key_event == KEY_CODE_3_4) {
        PR_NOTICE("--------------key 3 and key 4 comb-------------");
        app_ctrl_data.key_state = key_3_4_comb;
    }
}

VOID app_key_poll(VOID)
{
    app_key_scan(&key_trg,&key_cont);

    switch (key_cont)
    {
    case KEY_CODE_RELEASE:
        if(key_buf != 0) {
            app_key_event(key_buf);
        }
        key_buf = 0;
        key_old = KEY_CODE_RELEASE;
        break;
    case KEY_CODE_1:
        if(key_old == KEY_CODE_1) {
            key_delay_cont++;
        }else{
            key_delay_cont = 0;
        }

        if(key_delay_cont >= 2) {
            key_buf = KEY_CODE_1;
        }

        if(key_delay_cont >= 40) {
            key_buf = 0;
            app_ctrl_data.key_state = key_1_long;
        }
        
        key_old = KEY_CODE_1;        
        break;
    case KEY_CODE_2:
        if(key_old == KEY_CODE_2) {
            key_delay_cont++;
        }else{
            key_delay_cont = 0;
        }

        if(key_delay_cont >= 2) {
            key_buf = KEY_CODE_2;
        }

        if(key_delay_cont >= 40) {
            key_buf = 0;
            app_ctrl_data.key_state = key_2_long;
        }
        
        key_old = KEY_CODE_2;        
        break;
    case KEY_CODE_3:
        if(key_old == KEY_CODE_3) {
            key_delay_cont++;
        }else{
            key_delay_cont = 0;
        }

        if(key_delay_cont >= 2) {
            key_buf = KEY_CODE_3;
        }

        if(key_delay_cont >= 40) {
            key_buf = 0;
            app_ctrl_data.key_state = key_3_long;
        }
        
        key_old = KEY_CODE_3;
        break;
    case KEY_CODE_4:
        if(key_old == KEY_CODE_4) {
            key_delay_cont++;
        }else{
            key_delay_cont = 0;
        }

        if(key_delay_cont >= 2) {
            key_buf = KEY_CODE_4;
        }

        if(key_delay_cont >= 40) {
            key_buf = 0;
            app_ctrl_data.key_state = key_4_long;
        }
        
        key_old = KEY_CODE_4;        
        break;
    case KEY_CODE_1_2:
        if(key_old == KEY_CODE_1_2) {
            key_delay_cont++;
        }else{
            key_delay_cont = 0;
        }

        if(key_delay_cont >= 2) {
            key_buf = KEY_CODE_1_2;
        }
 
        key_old = KEY_CODE_1_2;        
        break;
    case KEY_CODE_3_4:
        if(key_old == KEY_CODE_3_4) {
            key_delay_cont++;
        }else{
            key_delay_cont = 0;
        }

        if(key_delay_cont >= 2) {
            key_buf = KEY_CODE_3_4;
        }
 
        key_old = KEY_CODE_3_4;        
        break;          
    default:
        break;
    }
 
}

VOID app_get_sensor_data(VOID)
{   

}

VOID app_ctrl_handle(VOID)
{   

}

VOID app_ctrl_all_off(VOID)
{   

}

 