# 曲速智能 IOT ESP8266 SDK V2.0 说明文档
---

* [1、SDK API](#1)
  * [1.1、初始化](#2)
  * [1.2、启动sdk](#3)
  * [1.3、停止sdk](#4)
  * [1.4、上报数据：多个数据](#5)
  * [1.5、上报数据：一个数据](#6)
  * [1.6、当前SDK版本号](#7)
* [2、TLV 数据解析工具方法](#8)
  * [2.1、int16_t数据转换](#9)
  * [2.2、uint16_t数据转换](#10)
  * [2.3、int32_t数据转换](#11)
  * [2.4、uint32_t数据转换](#12)
* [4、QuickStart](#18)

<br>

<h2 id="1">1、SDK API</h3>

<h3 id="2">1.1、初始化</h3>


使用sdk前需要先调用以下函数进行初始化，初始化成功后才能继续其它操作

`wf_iot_init();`

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|wf_err_t|是|初始化失败返回的错误信息|

<h3 id="3">1.2、启动sdk</h3>

sdk初始成功后调用以下函数进行启动

`wf_iot_start(const wf_iot_config_t *config);`

参数说明

|名称|字段名|数据类型|是否可空|说明|
|:---|:---|:---|:---|:---|
|config||const wf_iot_config_t *|否|sdk启动所需要传递的参数|
||product_id|const char *|否|Product ID. 从平台控制台中新建产品获取。|
||product_key|const char *|否|Product KEY. 从平台控制台中新建产品获取。|
||network_setup_type|enum|否|配网方式。( AIRKISS / AP )|
||rf24|enum|是|是否支持2.4G通信。（需要硬件支持）|
||rf24_device_type|enum|是|2.4G组网设备类型。（普通节点 / 中继节点 / 网关节点）|
||tlv_callback|function|否|设备控制指令回调。|
||ota_callback|function|否|空中升级指令回调。|
||firmware_ver|const char *|否|当前软件版本号。（用于空中升级）|


```
	const wf_iot_config_t config = {
        .product_id = <Product ID>,
        .product_key = <Product KEY>,
        .network_setup_type = AIRKISS,
        .rf24 = ENABLE,
        .rf24_device_type = COMMON_DEVICE,
        .tlv_callback = wf_tlv_callback,
        .ota_callback = wf_ota_callback,
        .firmware_ver = "v1.0.0",
    };
	wf_iot_start(&config);
```

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|wf_err_t|是|启动失败返回的错误信息|

<h3 id="4">1.3、停止sdk</h3>

启动后需要停止sdk工作,调用以下函数暂停sdk。并释放内存。

`wf_iot_stop();`

返回值说明

|名称|数据类型|是否可空|说明|
|:---|:---|:---|:---|
|无|wf_err_t|是|暂停失败返回的错误信息|

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
|无|wf_err_t|是|上报失败返回的错误信息|

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
|无|wf_err_t|是|上报失败返回的错误信息|


<h3 id="7">1.6、当前SDK版本号</h3>

用于获取当前`SDK`版本号

`wf_iot_get_version();`

---

<h2 id="8">2、TLV 数据解析工具方法</h2>

约定sdk与曲速Iot云之间传输的数据通信协议为tlv格式及编码方式。

<h3 id="9">2.1、int16_t数据转换</h3>

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

<h3 id="10">2.2、uint16_t数据转换</h3>

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

<h3 id="11">2.3、int32_t数据转换</h3>

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

<h3 id="12">2.4、uint32_t数据转换</h3>

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

---

<h2 id="18">3、QuickStart</h3>

使用 [示例链接](https://github.com/warpfuturechina/WF_IOT_ESP8266/blob/master/doc/example.md).
