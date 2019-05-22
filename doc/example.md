# QuickStart
---

```c
#include <stdlib.h>
#include <string.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_ota_ops.h>
#include <freertos/FreeRTOS.h>
#include <freertos/esp_freertos_hooks.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <wf_airkiss.h>
#include <wf_iot_sdk.h>

#define TAG "wf-demo"

#define WF_PROD_ID "<Your Product ID>"
#define WF_PROD_KEY "<Your Product KEY>"

void wf_tlv_callback(wf_tlv_t *tlvs[], uint16_t count)
{
    for (uint16_t i = 0; i < count; i++)
    {
        wf_tlv_t *tlv = tlvs[i];
        ESP_LOGI(TAG, "=========================");
        ESP_LOGI(TAG, "Tag is %d", tlv->tag);
        ESP_LOGI(TAG, "Len is %d", tlv->len);
        ESP_LOGI(TAG, "Value is %d", *((uint8_t *)(tlv->value)));
        ESP_LOGI(TAG, "=========================");
    }
}

wf_ota_status_t wf_ota_callback(wf_ota_stage_t stage, const void *buf, uint16_t len)
{
    static esp_ota_handle_t update_handle = 0;
    static const esp_partition_t *update_partition = NULL;
    switch (stage)
    {
    case WF_OTA_BEGIN:
    {
        esp_err_t err;
        const esp_partition_t *configured = esp_ota_get_boot_partition();
        const esp_partition_t *running = esp_ota_get_running_partition();
        ESP_LOGI(TAG, "OTA begin");

        if (configured != running)
        {
            ESP_LOGW(TAG, "Configured OTA boot partition at offset 0x%08x, but running from offset 0x%08x",
                     configured->address, running->address);
            ESP_LOGW(TAG, "(This can happen if either the OTA boot data or preferred boot image become corrupted somehow.)");
        }
        ESP_LOGI(TAG, "Running partition type %d subtype %d (offset 0x%08x)",
                 running->type, running->subtype, running->address);

        update_partition = esp_ota_get_next_update_partition(NULL);
        ESP_LOGI(TAG, "Writing to partition subtype %d at offset 0x%x",
                 update_partition->subtype, update_partition->address);
        assert(update_partition != NULL);

        err = esp_ota_begin(update_partition, OTA_SIZE_UNKNOWN, &update_handle);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "esp_ota_begin failed, error=%d", err);
            return WF_OTA_REJECT;
        }
        ESP_LOGI(TAG, "esp_ota_begin succeeded");
        break;
    }
    case WF_OTA_FAILD:
        ESP_LOGI(TAG, "OTA faild");
        break;
    case WF_OTA_FINISH:
    {
        esp_err_t err;
        ESP_LOGI(TAG, "OTA finish");
        if (esp_ota_end(update_handle) != ESP_OK)
        {
            ESP_LOGE(TAG, "esp_ota_end failed!");
        }
        err = esp_ota_set_boot_partition(update_partition);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "esp_ota_set_boot_partition failed! err=0x%x", err);
        }
        ESP_LOGI(TAG, "Prepare to restart system!");
        esp_restart();
        break;
    }
    case WF_OTA_WRITE_DATA:
    {
        esp_err_t err;
        ESP_LOGI(TAG, "OTA write data");
        err = esp_ota_write(update_handle, (const void *)buf, len);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "Error: esp_ota_write failed! err=0x%x", err);
        }
        break;
    }
    }
    return WF_OTA_ACCEPT;
}


void app_main()
{
    // 1. Configuration
    const wf_iot_config_t config = {
        .product_id = WF_PROD_ID,             // Product ID
        .product_key = WF_PROD_KEY,           // Product KEY
        .network_setup_type = AIRKISS,        // Network configuration. ( AIRKISS / AP_MODE )
        .rf24 = ENABLE,                       // Is enable RF2.4G module.
        .rf24_device_type = COMMON_DEVICE,    // Device type in 2.4G network. ( COMMON_DEVICE / RELAY_DEVICE / GATEWAY_DEVICE )
        .tlv_callback = wf_tlv_callback,      // Control command callback function.
        .ota_callback = wf_ota_callback,      // Update firmware command callback function.
        .firmware_ver = "v1.0.0",             // Software version.
    };

    // 2. SDK Initialization
    wf_iot_init();

    // 3. User Product Initialization
    // TODO(...)

    // 4. Start SDK
    wf_iot_start(&config);

    
    ESP_LOGI(TAG,"Helloworld! WF Iot SDK is running. Version:%s", wf_iot_get_version());
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
        ESP_LOGI(TAG, "Free heap size: %d", esp_get_free_heap_size());
    }

    // 5. Stop SDK
    wf_iot_stop();
}

```
