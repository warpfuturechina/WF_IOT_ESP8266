#ifndef __WF_IOT_SDK_H__
#define __WF_IOT_SDK_H__

#include <stdbool.h>
#include <stdint.h>
#include <esp_err.h>
#include <freertos/event_groups.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t wf_tag_t;
typedef uint16_t wf_length_t;
typedef uint8_t wf_valut_t;

#pragma pack(push,1)
typedef struct {
  wf_tag_t tag;
  wf_length_t len;
  wf_valut_t value[0];
} wf_tlv_t;
#pragma pack(pop)

typedef void (*wf_tlv_callback_t)(wf_tlv_t *tlvs[], uint16_t count);

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

typedef struct {
  char *address;
  uint16_t port;
  char *product_id;
  char *product_key;

  char *ssid;
  char *pwd;
  char *firmware_ver;
  uint16_t random;

  wf_tlv_callback_t tlv_callback;
  wf_timer_callback_t timer_callback;
  wf_ota_callback_t ota_callback;
} wf_iot_config_t;

typedef struct {
  uint16_t mqtt_task_stack_size;
  uint8_t mqtt_task_priority;
  uint16_t other_task_stack_size;
  uint8_t other_task_priority;
  uint16_t ota_task_stack_size;
  uint8_t ota_task_priority;
  uint8_t publish_qos;
  uint8_t sntp_max_retry_count;
  uint32_t min_retry_delay_ms;
  uint32_t max_retry_delay_ms;
  uint32_t mqtt_timeout;
  uint32_t mqtt_keepalive_interval_s;
  uint32_t mqtt_sendbuf_len;
  uint32_t mqtt_recvbuf_len;
} wf_iot_init_config_t;

#define WF_IOT_INIT_DEFAULT_PARAM { \
    .mqtt_task_stack_size = 3072, \
    .mqtt_task_priority = tskIDLE_PRIORITY + 2, \
    .other_task_stack_size = 4096, \
    .other_task_priority = tskIDLE_PRIORITY + 2, \
    .ota_task_stack_size = 4096, \
    .ota_task_priority = tskIDLE_PRIORITY + 2, \
    .publish_qos = 2, \
    .sntp_max_retry_count = 10, \
    .min_retry_delay_ms = 500, \
    .max_retry_delay_ms = 3000, \
    .mqtt_timeout = 5 * 1000, \
    .mqtt_keepalive_interval_s = 20, \
    .mqtt_sendbuf_len = 512, \
    .mqtt_recvbuf_len = 512, \
  } \

const char* wf_iot_get_version();

/**
 * @brief  Init the sdk
 */
esp_err_t wf_iot_init(const wf_iot_init_config_t *init_config);

esp_err_t wf_iot_start(const wf_iot_config_t *config);

esp_err_t wf_iot_stop();

esp_err_t wf_iot_report(wf_tlv_t *data[], uint8_t count);

esp_err_t wf_iot_report_one(wf_tlv_t *data);

int16_t wf_tlv_get_int16(wf_valut_t *in_buf);
uint16_t wf_tlv_get_uint16(wf_valut_t *in_buf);

int32_t wf_tlv_get_int32(wf_valut_t *in_buf);
uint32_t wf_tlv_get_uint32(wf_valut_t *in_buf);

#ifdef __cplusplus
}
#endif
#endif