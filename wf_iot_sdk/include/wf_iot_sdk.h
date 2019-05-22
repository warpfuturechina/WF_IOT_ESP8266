#ifndef __WF_IOT_SDK_H__
#define __WF_IOT_SDK_H__

#include <stdbool.h>
#include <stdint.h>
#include "wf_err.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "wf_rf24.h"

typedef uint16_t wf_tag_t;
typedef uint16_t wf_length_t;
typedef uint8_t wf_valut_t;


#define DEVICES_ID_SIZE     6
#define DEVICES_ID_STR_SIZE (3*DEVICES_ID_SIZE)
typedef uint8_t device_id_t [DEVICES_ID_SIZE];
typedef char device_str_t[DEVICES_ID_STR_SIZE];

#pragma pack(push,1)
typedef struct {
  wf_tag_t tag;
  wf_length_t len;
  wf_valut_t value[0];
} wf_tlv_t;
#pragma pack(pop)

typedef void (*wf_tlv_callback_t)(wf_tlv_t *tlvs[], uint16_t count);
typedef void (*wf_dispatch_tlv_callback_t)(device_id_t device_id,wf_tlv_t *tlvs[], uint16_t count);

typedef enum {
  WF_TIMER_EXECED,
  WF_TIMER_NO_RESOURCE,
  WF_TIMER_UNKNOW_ERROR,
} wf_timer_exec_status_t;

typedef wf_timer_exec_status_t (*wf_timer_callback_t)(wf_tlv_t *tlvs[], uint16_t count);

typedef enum {
  WF_OTA_BEGIN = 0,
  WF_OTA_WRITE_DATA,
  WF_OTA_FAILD,
  WF_OTA_FINISH
} wf_ota_stage_t;

typedef enum {
  WF_OTA_ACCEPT = 0,
  WF_OTA_REJECT
} wf_ota_status_t;

typedef wf_ota_status_t (*wf_ota_callback_t)(wf_ota_stage_t stage, const void *buf, uint16_t len);

typedef void (*wf_report_done_callback_t)(uint8_t result);

typedef enum{
    AIRKISS = 0,
    AP_MODE,
} network_setup_type_t;

typedef enum{
  DISABLE,
  ENABLE,
} model_selection_t;

typedef struct {

  char *product_id;
  char *product_key;

  char *firmware_ver;

  network_setup_type_t network_setup_type;

  model_selection_t rf24;
  wf_rf24_device_type_t rf24_device_type;

  wf_tlv_callback_t tlv_callback;
  wf_timer_callback_t timer_callback;
  wf_ota_callback_t ota_callback;
} wf_iot_config_t;

typedef struct {
  uint16_t mqtt_task_stack_size;
  uint8_t  mqtt_task_priority;
  uint16_t other_task_stack_size;
  uint8_t  other_task_priority;
  uint16_t ota_task_stack_size;
  uint8_t  ota_task_priority;
  uint16_t rf24_task_stack_size;
  uint8_t  rf24_task_priority;
  uint8_t  publish_qos;
  uint8_t  sntp_max_retry_count;
  uint32_t min_retry_delay_ms;
  uint32_t max_retry_delay_ms;
  uint32_t mqtt_timeout;
  uint32_t mqtt_keepalive_interval_s;
  uint32_t mqtt_sendbuf_len;
  uint32_t mqtt_recvbuf_len;
} wf_iot_init_config_t;

#define WF_RF24_INIT_PARAM .rf24_task_stack_size = 4096, \
                           .rf24_task_priority = tskIDLE_PRIORITY + 2,

#define WF_IOT_INIT_PARAM .mqtt_task_stack_size = 2560, \
                          .mqtt_task_priority = tskIDLE_PRIORITY + 2, \
                          .other_task_stack_size = 1024, \
                          .other_task_priority = tskIDLE_PRIORITY + 2, \
                          .ota_task_stack_size = 4096, \
                          .ota_task_priority = tskIDLE_PRIORITY + 2, \
                          .publish_qos = 1, \
                          .sntp_max_retry_count = 10, \
                          .min_retry_delay_ms = 500, \
                          .max_retry_delay_ms = 3000, \
                          .mqtt_timeout = 15 * 1000, \
                          .mqtt_keepalive_interval_s = 15, \
                          .mqtt_sendbuf_len = 512, \
                          .mqtt_recvbuf_len = 512,

#define WF_IOT_INIT_DEFAULT_PARAM { \
    WF_IOT_INIT_PARAM \
    WF_RF24_INIT_PARAM \
  } \

const char* wf_iot_get_version();

/**
 * @brief  Init the sdk
 */
wf_err_t wf_iot_init();

wf_err_t wf_iot_start(const wf_iot_config_t *config);

wf_err_t wf_iot_stop();

wf_err_t wf_iot_recovery();

wf_err_t wf_iot_report(wf_tlv_t *data[], uint8_t count);

wf_err_t wf_iot_report_one(wf_tlv_t *data);

wf_err_t wf_status_report(wf_tlv_t *data[], uint8_t count);

wf_err_t wf_status_report_one(wf_tlv_t *data);

int16_t wf_tlv_get_int16(wf_valut_t *in_buf);
uint16_t wf_tlv_get_uint16(wf_valut_t *in_buf);

int32_t wf_tlv_get_int32(wf_valut_t *in_buf);
uint32_t wf_tlv_get_uint32(wf_valut_t *in_buf);

#ifdef __cplusplus
}
#endif
#endif
