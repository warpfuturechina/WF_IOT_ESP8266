#ifndef __WF_HTTP_H__
#define __WF_HTTP_H__

#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "wf_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WF_HTTP_NO_ERR 0
#define WF_HTTP_NO_MEM_ERR -1
#define WF_HTTP_URL_ERR -2
#define WF_HTTP_LOAD_CERT_ERR -3
#define WF_HTTP_DNS_ERR -4
#define WF_HTTP_CONNECT_ERR -5
#define WF_HTTP_SOCKET_ERR -6
#define WF_HTTP_TLS_ERR -7

typedef void* wf_http_handle_t;

int wf_http_get(const char *url, void (*on_data)(void *, const uint8_t *, size_t), void *param, wf_http_handle_t *handler);

int wf_http_start(wf_http_handle_t handler);

ssize_t wf_http_yield(wf_http_handle_t handler);

void wf_http_clean(wf_http_handle_t handler);

#ifdef __cplusplus
}
#endif

#endif