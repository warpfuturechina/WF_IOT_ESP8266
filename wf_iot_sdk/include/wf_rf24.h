#ifndef __WF_RF24_H__
#define __WF_RF24_H__


typedef enum {
    COMMON_DEVICE = 1,               /* Normal  device */
    RELAY_DEVICE,                    /* Relay   device */
    GATEWAY_DEVICE,                  /* Gateway device */
}wf_rf24_device_type_t;

#endif
