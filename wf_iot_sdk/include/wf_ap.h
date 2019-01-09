#ifndef __WF_AP_H__
#define __WF_AP_H__

#include <stdbool.h>
#include <stdint.h>
#include <esp_err.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  char *ssid;
  char *password;
  uint8_t random_num;
} wf_ap_result_t;

typedef enum {
  ERR_MANUAL_STOP = 0,
} wf_ap_error_t;

typedef struct {
    void (*complete)(wf_ap_result_t*);
    void (*error)(wf_ap_error_t);
} wf_ap_callback_t;

esp_err_t wf_ap_start(const char *ap_ssid, const char *ap_password, wf_ap_callback_t callback);

void wf_ap_stop();

const char *wf_ap_version();

#ifdef __cplusplus
}
#endif

#endif
