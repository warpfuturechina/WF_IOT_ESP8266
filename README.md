# 曲速智联IOT ESP8266 SDK说明文档
---

## SDK API

### 1. 初始化

使用sdk前需要先调用以下函数进行初始化，初始化成功后才能继续其它操作

`esp_err_t wf_iot_init(const wf_iot_init_config_t *init_config);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|init_config|const wf_iot_init_config_t *|否|初始化配置参数|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|esp_err_t|是|初始化失败返回的错误信息|

### 2. 启动sdk

sdk初始成功后调用以下函数进行启动

`esp_err_t wf_iot_start(const wf_iot_config_t *config);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|config|const wf_iot_config_t *|否|sdk启动所需要传递的参数|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|esp_err_t|是|启动失败返回的错误信息|

### 3. 暂停sdk

启动后需要停止sdk工作,调用以下函数暂停sdk

`void wf_iot_stop();`

### 4. 销毁sdk

当不再需要sdk提供服务时调用以下函数来销毁sdk

`void wf_iot_deinit();`

### 5. 上报数据：多个数据

sdk成功启动后，需要上报数据时调用以下函数进行数据上报，该函数可以上报一个或多个数据块

`esp_err_t wf_iot_report(wf_tlv_t *data[], uint8_t count, wf_report_done_callback_t callback);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|data|wf_tlv_t *指针数组|否|数据块数组指针|
|count|uint8_t|否|上报数据块个数|
|callback|function|否|上报结果回调函数|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|esp_err_t|是|上报失败返回的错误信息|

### 6. 上报数据：一个数据

sdk成功启动后，需要上报数据时调用以下函数进行数据上报，该函数一次只能上报一个数据块

`esp_err_t wf_iot_report_one(wf_tlv_t *data, wf_report_done_callback_t callback);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|data|wf_tlv_t *|否|数据块指针|
|callback|function|否|上报结果回调函数|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|esp_err_t|是|上报失败返回的错误信息|

### 7. TLV 数据解析工具方法

约定sdk与曲速Iot云之间传输的数据通信协议为tlv格式及编码方式。

• 从`tlv`中取出`int16_t`类型的数值：

`int16_t wf_tlv_get_int16(wf_valut_t *in_buf);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|in_buf|wf_valut_t *|否|tlv数据|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|int16_t|否|返回值|

</br>

• 从`tlv`中取出`uint16_t`类型的数值：

`uint16_t wf_tlv_get_uint16(wf_valut_t *in_buf);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|in_buf|wf_valut_t *|否|tlv数据|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|uint16_t|否|返回值|

</br>

• 从`tlv`中取出`int32_t`类型的数值：

`int32_t wf_tlv_get_int32(wf_valut_t *in_buf);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|in_buf|wf_valut_t *|否|tlv数据|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|int32_t|否|返回值|

</br>

• 从`tlv`中取出`uint32_t`类型的数值：

`uint32_t wf_tlv_get_uint32(wf_valut_t *in_buf);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|in_buf|wf_valut_t *|否|tlv数据|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|uint32_t|否|返回值|

---

## AirKiss配网

### 1. 进入配网模式

sdk成功启动后，可以调用以下函数开始进入`AirKiss`配网模式，并等待客户端发起配网请求，收到配网请求及参数后执行回调函数

`esp_err_t wf_airkiss_start(uint8_t timeout_s, wf_airkiss_callback_t callback);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|timeout_s|uint8_t|否|配网超时时间，多少秒之后配网不成功就自动关闭，单位为秒|
|callback|wf_airkiss_callback_t|否|收到配网请求及配网参数的结果回调函数|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|esp_err_t|是|调用错误返回值|

### 2. 停止配网

开启配网模式后，需要停止配网，调用以下函数

`void wf_airkiss_stop();`

### 3. 响应客户端配网请求并返回随机数

收到客户端发送过来的配网请求后，调用以下函数响应客户端

`void wf_airkiss_send_ack();`

### 4. 当前`AirKiss`配网`API`版本号

用于获取当前`AirKiss`配网API版本号

`const char *wf_airkiss_version();`
