# QuickStart
---

```c
#include <stdlib.h>
#include <string.h>

#include <driver/gpio.h>
#include <driver/pwm.h>
#include <esp_event_loop.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <esp_ota_ops.h>
#include <freertos/FreeRTOS.h>
#include <freertos/esp_freertos_hooks.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <nvs_flash.h>
#include <tcpip_adapter.h>

#include <wf_airkiss.h>
#include <wf_iot_sdk.h>

#define TAG "wf_example_main"

#define WF_OUT_CTL_GPIO GPIO_NUM_4

/* FreeRTOS event group to signal when we are connected & ready to make a
 * request */
static EventGroupHandle_t wifi_event_group;

/* The event group allows multiple bits for each event,
   but we only care about one event - are we connected
   to the AP with an IP? */
static const int CONNECTED_BIT = BIT0;

#define STORAGE_NAMESPACE "storage"

#define WF_PROD_ID "your_product_id"
#define WF_PROD_KEY "your_product_key"
#define WF_BROKER_ADDR "iot-mqtt.warpiot.com"
#define WF_BROKER_PORT 1883

static wifi_config_t wifi_config;
static uint8_t random_number;

esp_err_t save_random_number(uint8_t random_num);

esp_err_t read_random_number(uint8_t *random_num);


static void wf_airkiss_scandone_callback() {
  ESP_LOGI(TAG, "WF airkiss scandone");
}

static void wf_airkiss_find_channel(int channel) {
  ESP_LOGI(TAG, "WF airkiss find channel %d", channel);
}

static void wf_airkiss_complete(wf_airkiss_result_t* result) {
  ESP_LOGI(TAG, "WF airkiss complete");
  ESP_LOGI(TAG, "Phone ip: %d.%d.%d.%d", result->phone_ip[0],
            result->phone_ip[1], result->phone_ip[2],result->phone_ip[3]);
  ESP_LOGI(TAG, "Random number is %d", result->random_num);
  ESP_LOGI(TAG, "SSID %s", result->ssid);
  ESP_LOGI(TAG, "Password %s", result->password);
  save_random_number(result->random_num);
  random_number = result->random_num;
  
  
  /* require, send notification */
  wf_airkiss_send_ack(random_number);
  

  wifi_config_t wifi_config;
  memset(&wifi_config, 0, sizeof(wifi_config_t));

  strcpy((char *)wifi_config.sta.ssid, result->ssid);
  strcpy((char *)wifi_config.sta.password, result->password);
  ESP_ERROR_CHECK(esp_wifi_stop());
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_start());
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
  ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
  ESP_ERROR_CHECK(esp_wifi_connect());
}

static void wf_airkiss_timeout() {
  ESP_LOGI(TAG, "WF airkiss timeout");
}

static esp_err_t event_handler(void *ctx, system_event_t *event) {
  switch (event->event_id) {
    case SYSTEM_EVENT_STA_GOT_IP:
      xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      esp_wifi_connect();
      xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
      break;
    default:
      break;
  }
  return ESP_OK;
}

static void initialise_wifi(void) {
  tcpip_adapter_init();
  wifi_event_group = xEventGroupCreate();
  ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

  ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
  ESP_ERROR_CHECK(esp_wifi_start());

  ESP_ERROR_CHECK(esp_wifi_get_config(ESP_IF_WIFI_STA, &wifi_config));
  if (wifi_config.sta.ssid[0] != 0) {
    if (read_random_number(&random_number) == ESP_OK) {
      ESP_ERROR_CHECK(esp_wifi_connect());
      return;
    }
  }


  /* AirKiss */
  wf_airkiss_callback_t airkiss_callback = {
      .scandone = wf_airkiss_scandone_callback,
      .find_channel = wf_airkiss_find_channel,
      .complete = wf_airkiss_complete,
      .timeout = wf_airkiss_timeout,
  };

   /**
   * @brief AirKiss Start
   * @param timeout_s timeout seconds
   * @param callback result callback
   */
   wf_airkiss_start(30, airkiss_callback);
}

esp_err_t save_random_number(uint8_t random_num) {
  nvs_handle my_handle;
  esp_err_t err;

  // Open
  err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
  if (err != ESP_OK) return err;

  // Write
  err = nvs_set_u8(my_handle, "random_num", random_num);
  if (err != ESP_OK) return err;

  // Commit written value.
  err = nvs_commit(my_handle);
  if (err != ESP_OK) return err;

  // Close
  nvs_close(my_handle);
  return ESP_OK;
}

esp_err_t read_random_number(uint8_t *random_num) {
  nvs_handle my_handle;
  esp_err_t err;

  // Open
  err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
  if (err != ESP_OK) return err;

  // Read
  err = nvs_get_u8(my_handle, "random_num", random_num);
  if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) return err;

  // Close
  nvs_close(my_handle);
  return ESP_OK;
}

uint8_t last_light = UINT8_MAX;
uint8_t last_pwr = 0;

void wf_tlv_callback(wf_tlv_t *tlvs[], uint16_t count) {
  for (uint16_t i = 0; i < count; i++) {
    wf_tlv_t *tlv = tlvs[i];
    ESP_LOGI(TAG, "=========================");
    ESP_LOGI(TAG, "Tag is %d", tlv->tag);
    ESP_LOGI(TAG, "Len is %d", tlv->len);
    if (tlv->tag == 1) {
      if (*((uint8_t *)(tlv->value))) {
        last_pwr = 1;
        gpio_set_level(WF_OUT_CTL_GPIO, 1);
        ESP_LOGI(TAG, "Power on");
      } else {
        last_pwr = 0;
        gpio_set_level(WF_OUT_CTL_GPIO, 0);
        ESP_LOGI(TAG, "Power off");
      }
    } else if (tlv->tag == 2) {
      last_light = *((uint8_t *)(tlv->value));
      ESP_LOGI(TAG, "Light is %d", last_light);
      pwm_set_duty(0, last_light);
    } else if (tlv->tag == 3) {
      uint8_t tmp = *((uint8_t *)(tlv->value));
      ESP_LOGI(TAG, "Tmp is %d", tmp);
      pwm_set_duty(1, tmp);
    }
    ESP_LOGI(TAG, "=========================");
  }
}

wf_ota_status_t wf_ota_callback(wf_ota_stage_t stage, const void *buf, uint16_t len) {
  static esp_ota_handle_t update_handle = 0 ;
  static const esp_partition_t *update_partition = NULL;
  switch (stage) {
    case WF_OTA_BEGIN: {
      esp_err_t err;
      const esp_partition_t *configured = esp_ota_get_boot_partition();
      const esp_partition_t *running = esp_ota_get_running_partition();
      ESP_LOGI(TAG, "OTA begin");

      if (configured != running) {
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
      if (err != ESP_OK) {
          ESP_LOGE(TAG, "esp_ota_begin failed, error=%d", err);
          return WF_OTA_REJECT;
      }
      ESP_LOGI(TAG, "esp_ota_begin succeeded");
      break;
    }
    case WF_OTA_FAILD:
      ESP_LOGI(TAG, "OTA faild");
      break;
    case WF_OTA_FINISH: {
      esp_err_t err;
      ESP_LOGI(TAG, "OTA finish");
      if (esp_ota_end(update_handle) != ESP_OK) {
        ESP_LOGE(TAG, "esp_ota_end failed!");
      }
      err = esp_ota_set_boot_partition(update_partition);
      if (err != ESP_OK) {
          ESP_LOGE(TAG, "esp_ota_set_boot_partition failed! err=0x%x", err);
      }
      ESP_LOGI(TAG, "Prepare to restart system!");
      esp_restart();
      break;
    }
    case WF_OTA_WRITE_DATA: {
      esp_err_t err;
      ESP_LOGI(TAG, "OTA write data");
      err = esp_ota_write(update_handle, (const void *)buf, len);
      if (err != ESP_OK) {
          ESP_LOGE(TAG, "Error: esp_ota_write failed! err=0x%x", err);
      }
      break;
    }
  }
  return WF_OTA_ACCEPT;
}

void app_main() {

  initialise_wifi();
  /* Wait for WiFI to show as connected */
  xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);

  /* SDK Start */

  // setup
  wf_iot_init_config_t init_config = WF_IOT_INIT_DEFAULT_PARAM;
  wf_iot_init(&init_config);

  wf_iot_config_t config = {
    .address = WF_BROKER_ADDR,
    .port = WF_BROKER_PORT,
    .product_id = WF_PROD_ID,
    .product_key = WF_PROD_KEY,
    .ssid = (char *)wifi_config.sta.ssid,
    .pwd = (char *)wifi_config.sta.password,
    .random = random_number,
    .tlv_callback = wf_tlv_callback,
    .timer_callback = NULL,
    .ota_callback = wf_ota_callback,
    .firmware_ver = "0.0.1-bete+0x1000",
  };

  /**
  * @brief SDK Start
  * @param config setup to sdk
  */
  wf_iot_start(&config);

  int cnt = 0;
  for (;;) {
    ESP_LOGI(TAG, "Free heap size: %d", esp_get_free_heap_size());
    vTaskDelay(pdMS_TO_TICKS(10000));
    extern void esp_task_wdt_reset(void);
    esp_task_wdt_reset();
    cnt++;
  }
}
```
