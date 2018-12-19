# 曲速智能 IOT ESP8266 SDK 说明文档
---

* [1、SDK API](#1)
 * [1.1、初始化](#2)
 * [1.2、启动sdk](#3)
 * [1.3、暂停sdk](#4)
 * [1.4、上报数据：多个数据](#5)
 * [1.5、上报数据：一个数据](#6)
 * [1.6、TLV 数据解析工具方法](#7)
 * [1.7、当前SDK版本号](#8)
* [2、AirKiss配网](#9)
 * [2.1、进入配网模式](#10)
 * [2.2、停止配网](#11)
 * [2.3、响应客户端配网请求并返回随机数](#12)
 * [2.4、当前`AirKiss`配网`API`版本号](#13)
* [3、AP配网](#14)
 * [3.1、进入配网模式](#15)
 * [3.2、停止配网](#16)
 * [3.3、当前`AP`配网`API`版本号](#17)
* [4、QuickStart](#18)

<br>

<h2 id="1">1、SDK API</h3>

<h3 id="2">1.1、初始化</h3>

使用sdk前需要先调用以下函数进行初始化，初始化成功后才能继续其它操作

`wf_iot_init(const wf_iot_init_config_t *init_config);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|init_config|const wf_iot_init_config_t *|否|初始化配置参数|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|esp_err_t|是|初始化失败返回的错误信息|

<h3 id="3">1.2、启动sdk</h3>

sdk初始成功后调用以下函数进行启动

`wf_iot_start(const wf_iot_config_t *config);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|config|const wf_iot_config_t *|否|sdk启动所需要传递的参数|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|esp_err_t|是|启动失败返回的错误信息|

<h3 id="4">1.3、暂停sdk</h3>

启动后需要停止sdk工作,调用以下函数暂停sdk

`wf_iot_stop();`

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|esp_err_t|是|暂停失败返回的错误信息|

<h3 id="5">1.4、上报数据：多个数据</h3>

sdk成功启动后，需要上报数据时调用以下函数进行数据上报，该函数可以上报一个或多个数据块

`wf_iot_report(wf_tlv_t *data[], uint8_t count);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|data|wf_tlv_t *指针数组|否|数据块数组指针|
|count|uint8_t|否|上报数据块个数|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|esp_err_t|是|上报失败返回的错误信息|

<h3 id="6">1.5、上报数据：一个数据</h3>

sdk成功启动后，需要上报数据时调用以下函数进行数据上报，该函数一次只能上报一个数据块

`wf_iot_report_one(wf_tlv_t *data);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|data|wf_tlv_t *|否|数据块指针|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|esp_err_t|是|上报失败返回的错误信息|

<h3 id="7">1.6、TLV 数据解析工具方法</h3>

约定sdk与曲速Iot云之间传输的数据通信协议为tlv格式及编码方式。

• 从`tlv`中取出`int16_t`类型的数值：

`wf_tlv_get_int16(wf_valut_t *in_buf);`

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

`wf_tlv_get_uint16(wf_valut_t *in_buf);`

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

`wf_tlv_get_int32(wf_valut_t *in_buf);`

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

`wf_tlv_get_uint32(wf_valut_t *in_buf);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|in_buf|wf_valut_t *|否|tlv数据|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|uint32_t|否|返回值|

<h3 id="8">1.7、当前SDK版本号</h3>

用于获取当前`SDK`版本号

`wf_iot_get_version();`

---

<h2 id="9">2、AirKiss配网</h3>

<h3 id="10">2.1、进入配网模式</h3>

sdk成功启动后，可以调用以下函数开始进入`AirKiss`配网模式，并等待客户端发起配网请求，收到配网请求及参数后执行回调函数

`wf_airkiss_start(uint8_t timeout_s, wf_airkiss_callback_t callback);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|timeout_s|uint8_t|否|配网超时时间，多少秒之后配网不成功就自动关闭，单位为秒|
|callback|wf_airkiss_callback_t|否|收到配网请求及配网参数的结果回调函数|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|esp_err_t|是|调用错误返回值|

<h3 id="11">2.2、停止配网</h3>

开启配网模式后，需要停止配网，调用以下函数

`wf_airkiss_stop();`

<h3 id="12">2.3、响应客户端配网请求并返回随机数</h3>

收到配网成功回调后， <strong>必须</strong> 调用以下函数，将回调结果中的 <strong>result->random_num</strong> 发生回去。<br>
收到配网成功回调后， <strong>必须</strong> 调用以下函数，将回调结果中的 <strong>result->random_num</strong> 发生回去。<br>
收到配网成功回调后， <strong>必须</strong> 调用以下函数，将回调结果中的 <strong>result->random_num</strong> 发生回去。<br>

`wf_airkiss_send_ack();`

<h3 id="13">2.4、当前`AirKiss`配网`API`版本号</h3>

用于获取当前`AirKiss`配网API版本号

`wf_airkiss_version();`

</br>

---

<h2 id="14">3、AP配网</h3>

<h3 id="15">3.1、进入配网模式</h3>

sdk成功启动后，可以调用以下函数开始进入`AP`配网模式，并等待客户端发起配网请求，收到配网请求及参数后执行回调函数

`wf_ap_start(const char *ap_ssid_prefix, const char *ap_password, wf_ap_callback_t callback);`

参数说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|ap_ssid_prefix|const char *|否|Wi-Fi名称|
|ap_password|const char *|否|Wi-Fi密码|
|callback|wf_ap_callback_t|否|成功或失败回调|

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|esp_err_t|是|调用错误返回值|

<h3 id="16">3.2、停止配网</h3>


开启`AP`配网模式后，需要停止配网，调用以下函数

`wf_ap_stop();`

<h3 id="17">3.3、当前`AP`配网`API`版本号</h3>

用于获取当前`P`配网API版本号

`wf_ap_version();`

---

<h2 id="18">3、QuickStart</h3>

使用 [示例链接](https://github.com/warpfuturechina/WF_IOT_ESP8266/blob/master/doc/example.md).
