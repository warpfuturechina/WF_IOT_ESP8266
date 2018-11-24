#ifndef __WF_AIRKISS_H__
#define __WF_AIRKISS_H__

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
} wf_airkiss_result_t;

typedef struct {
    void (*scandone)();
    void (*find_channel)(int);
    void (*complete)(wf_airkiss_result_t*);
    void (*timeout)();
} wf_airkiss_callback_t;

esp_err_t wf_airkiss_start(uint8_t timeout_s, wf_airkiss_callback_t callback);

void wf_airkiss_stop();

void wf_airkiss_send_ack();

const char *wf_airkiss_version();

#ifdef __cplusplus
}
#endif

#endif
