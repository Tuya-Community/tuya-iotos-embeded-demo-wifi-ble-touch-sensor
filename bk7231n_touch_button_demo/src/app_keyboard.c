/*
 * @Author: zgw
 * @email: liang.zhang@tuya.com
 * @LastEditors: zgw
 * @file name: app_plant.c
 * @Description: light init process include file
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2020-12-21 11:30:03
 * @LastEditTime: 2021-03-12 18:36:13
 */

#include "app_keyboard.h"
#include "app_control.h"
#include "uni_time_queue.h"
#include "sys_timer.h"
#include "tuya_iot_wifi_api.h"
#include "FreeRTOS.h"
#include "tuya_hal_thread.h"
#include "uni_thread.h"
#include "queue.h"
#include "semphr.h"

#define TASKDELAY_SEC         1000



extern APP_CTRL_DATA_T app_ctrl_data;

STATIC VOID key_scan_thread(PVOID_T pArg);
STATIC VOID sensor_data_report_thread(PVOID_T pArg);







OPERATE_RET app_key_init(IN APP_KEY_MODE mode)
{
    OPERATE_RET op_ret = OPRT_OK;

    if(APP_NORMAL == mode) {
        app_device_init();

        //create ADC sensor data collection thread
        tuya_hal_thread_create(NULL, "key_scan_thread", 512*4, TRD_PRIO_4, key_scan_thread, NULL);

        tuya_hal_thread_create(NULL, "thread_data_report", 512*4, TRD_PRIO_4, sensor_data_report_thread, NULL);
    }else {
        //not factory test mode
    }

    return op_ret;
}

STATIC VOID key_scan_thread(PVOID_T pArg)
{   
    while(1) {
        app_key_poll();
        tuya_hal_system_sleep(25);
    }
}


STATIC VOID sensor_data_report_thread(PVOID_T pArg)
{   
    while(1) {
        app_report_all_dp_status();
        tuya_hal_system_sleep(TASKDELAY_SEC);
    }
}


VOID app_report_all_dp_status(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    INT_T dp_cnt = 0;
    dp_cnt = 1;

    TY_OBJ_DP_S *dp_arr = (TY_OBJ_DP_S *)Malloc(dp_cnt*SIZEOF(TY_OBJ_DP_S));
    if(NULL == dp_arr) {
        PR_ERR("malloc failed");
        return;
    }

    memset(dp_arr, 0, dp_cnt*SIZEOF(TY_OBJ_DP_S));

    dp_arr[0].dpid = DPID_KEY_STATE;
    dp_arr[0].type = PROP_ENUM;
    dp_arr[0].time_stamp = 0;
    dp_arr[0].value.dp_value = app_ctrl_data.key_state;

    op_ret = dev_report_dp_json_async(NULL,dp_arr,dp_cnt);
    Free(dp_arr);
    if(OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_json_async relay_config data error,err_num",op_ret);
    }

    PR_DEBUG("dp_query report_all_dp_data");
    return;
}


VOID deal_dp_proc(IN CONST TY_OBJ_DP_S *root)
{
    UCHAR_T dpid;

    dpid = root->dpid;
    PR_DEBUG("dpid:%d",dpid);
    
    switch (dpid) {
    
    case 0:

        break;

    default:
        break;
    }
    
    app_report_all_dp_status();

    return;

}
