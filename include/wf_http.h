#ifndef __WF_HTTP_H__
#define __WF_HTTP_H__

#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <esp_err.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WF_HTTP_NO_ERR = 0,
    WF_HTTP_NO_MEM_ERR,
    WF_HTTP_LOAD_CERT_ERR,
    WF_HTTP_DNS_ERR,
    WF_HTTP_CONNECT_ERR,
    WF_HTTP_SOCKET_ERR,
    WF_HTTP_TLS_ERR,
    WF_HTTP_MANUAL_STOP_ERR,
} wf_http_err_t;

typedef void* wf_http_handle_t;

esp_err_t wf_http_get(const char *url, void (*on_data)(void *, const uint8_t *, size_t), void (*on_error)(void *, wf_http_err_t), void *param, wf_http_handle_t *handler);

void wf_http_stop(wf_http_handle_t handler);

#ifdef __cplusplus
}
#endif

#endif