/*
 * @file name: 
 * @Descripttion: 
 * @Author: zgw
 * @email: liang.zhang@tuya.com
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-03-01 10:44:58
 * @LastEditors: zgw
 * @LastEditTime: 2021-03-12 18:06:15
 */
#ifndef __APP_CONTROL_H__
#define __APP_CONTROL_H__

#include "uni_log.h"
#include "tuya_cloud_error_code.h"

typedef enum {
    none = 0,
    key_1_long,
    key_1_short,
    key_2_long,
    key_2_short,
    key_3_long,
    key_3_short,
    key_4_long,
    key_4_short,
    key_1_2_comb,
    key_3_4_comb,
}KEY_STATE;

typedef struct {
    KEY_STATE key_state;
}APP_CTRL_DATA_T;

/********************************************************************************
 * FUNCTION:       plant_device_init
 * DESCRIPTION:    device initialization
 * INPUT:          none
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-01-12
 *******************************************************************************/
VOID app_device_init(VOID);

/********************************************************************************
 * FUNCTION:       plant_get_adc_sensor_data
 * DESCRIPTION:    Get ADC sensor data
 * INPUT:          none
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-01-12
 *******************************************************************************/
VOID app_get_sensor_data(VOID);

/********************************************************************************
 * FUNCTION:       plant_ctrl_handle
 * DESCRIPTION:    sensor data deal handle
 * INPUT:          none
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-01-12
 *******************************************************************************/
VOID app_ctrl_handle(VOID);

/********************************************************************************
 * FUNCTION:       plant_ctrl_all_off
 * DESCRIPTION:    Close all control components
 * INPUT:          none
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-01-12
 *******************************************************************************/
VOID app_ctrl_all_off(VOID);

#endif