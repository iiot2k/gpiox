# API @iiot2k/gpiox

Raspberry Pi gpiox library.

The @iiot2k/gpiox driver uses the gpio character devices interface (V2) from the Linux operating system.<br>
The driver is loaded on call with ```require("@iiot2k/gpiox");```<br>
On 64bit OS the driver ***gpiox_arm64.node*** is loaded.<br>
On 32bit OS the driver ***gpiox_arm32.node*** is loaded.<br>
To prevent mermory leaks, if the driver is unloaded function ```deinit_gpio``` is called for all pins.<br>

## Error function
```error_text()```<br>
***return:*** ```<string>``` error text after call function.<br>

## pin Parameter
The Raspberry Pi has gpio pins from GPIO2 to GPIO27.<br>
Valid ```pin``` parameter values are 2..27.<br>

## mode Parameter
Each gpio pin can be assigned a function.<br>
The following table shows the different modes with ```mode``` parameter.<br>

|Constant|State-0|State-1|function|
|:--|:--|:--|:--|
|GPIO_MODE_INPUT_NOPULL|ground|+3.3V|floating input|
|GPIO_MODE_INPUT_PULLDOWN|open/ground|+3.3V|pulldown resistor input|
|GPIO_MODE_INPUT_PULLUP|open/+3.3V|ground|pullup resistor input|
|GPIO_MODE_OUTPUT|ground|+3.3V|output|
|GPIO_MODE_OUTPUT_SOURCE|Hi-Z|+3.3V|output source|
|GPIO_MODE_OUTPUT_SINK|Hi-Z|ground|output sink|
|GPIO_MODE_PWM|ground|+3.3V|pwm output pulse|
|GPIO_MODE_PWM_REALTIME|ground|+3.3V|pwm output pulse in realtime|
|GPIO_MODE_COUNTER_NOPULL|ground|+3.3V|floating input counter|
|GPIO_MODE_COUNTER_PULLDOWN|open/ground|+3.3V|pulldown resistor input counter|
|GPIO_MODE_COUNTER_PULLUP|open/+3.3V|ground|pullup resistor input counter|
|GPIO_MODE_SENSOR|ground|Hi-Z|output sink|

Floating input/output is used when the pin is connected to another pin.<br>
Input voltages more than +3.3V can destroy the input.<br>
Hi-Z refers to an output signal state in which the signal is not being driven.<br>
Please do not init gpio pins with special functions (i2c, spi, uart..).<br>
GPIO output current is limited.<br>
Use ULN2803A (low switch) or 
[TBD62783](https://toshiba.semicon-storage.com/eu/semiconductor/product/linear-ics/transistor-arrays/detail.TBD62783APG.html) (high switch) for drive output.<br>

## GPIO Initialization functions

> ### Initializes the gpio with the mode.<br>
```init_gpio(pin, mode, setval)```<br>
***pin:*** ```<integer>``` 2..27<br>
***mode:*** ```<integer>``` GPIO_MODE_INPUT... or GPIO_MODE_OUTPUT...<br>
***setval:*** ```<integer>``` or ```<boolean>```<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

The ***setval*** parameter sets the **debounce time** in us for inputs,<br>
and can set to 0 for disable debounce.<br>
For outputs ***setval*** parameter sets initial state (0/1) of ```true/false```. <br>
Only inputs and outputs can be init.<br>

> ### Changes the mode of gpio.<br>
```change_gpio(pin, mode, setval)```<br>
***pin:*** ```<integer>``` 2..27<br>
***mode:*** ```<integer>``` GPIO_MODE_INPUT... or GPIO_MODE_OUTPUT...<br>
***setval:*** ```<integer>``` or ```<boolean>```<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

The pin must be initialized with **init_gpio()**.<br>
The ***setval*** parameter sets the **debounce time** in us for inputs,<br>
and can set to 0 for disable debounce.<br>
For outputs ***setval*** parameter sets initial state (0/1) of ```true/false```.<br>
Only mode of inputs and outputs can be changed.<br>

> ### Deinitializes the gpio and releases all resources.<br>
```deinit_gpio(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

Stops also watch, blink, pwm, and counter thread.<br>

## GPIO Watch functions

## edge Parameter
The ```edge``` parameter sets the watch direction of inputs.<br>
|Constant|Value|Function|
|:--|:--|:--|
|GPIO_EDGE_RISING|0|check for change from 0 to 1|
|GPIO_EDGE_FALLING|1|check for change from 1 to 0|
|GPIO_EDGE_BOTH|2|check for change from 0 to 1 or 1 to 0|

> ### Watch the gpio input for changes.<br>
```watch_gpio(pin, mode, debounce, edge, callback)```<br>
***pin:*** ```<integer>``` 2..27<br>
***mode:*** ```<integer>``` GPIO_MODE_INPUT...<br>
***debounce:*** ```<integer>``` 0..<br>
***edge:*** ```<integer>``` GPIO_EDGE_...<br>
***callback:*** ```<function> (state, edge, pin)```
- **state** ```<integer>``` 0/1,<br> 
- **edge** ```<integer>``` GPIO_EDGE_RISING or GPIO_EDGE_FALLING.<br> 
- **pin** ```<integer>``` 2..27.<br> 

***return:*** ```<number>``` ```0/1``` actual input state, ```undefined``` on error.<br>

The ***debounce*** parameter sets the **debounce time** in us for inputs,<br>
and can set to 0 for disable debounce.<br>
The ***callback*** function is called if input state changes.<br>

## GPIO Input/Output functions

> ### Gets gpio state as boolean.<br>
```get_gpio(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** ```<boolean>``` ```false/true```, ```undefined``` on error.<br>

The pin must be initialized as input or output.<br>

> ### Gets gpio state as number.<br>
```get_gpio_num(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** ```<integer>``` 0/1, ```undefined``` on error.<br>

The pin must be initialized as input or output.<br>

> ### Sets gpio state of output.<br>
```set_gpio(pin, value)```<br>
***pin:*** ```<integer>``` 2..27<br>
***value:*** ```<integer>``` 0/1 or ```<boolean>``` ```true/false```<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

The pin must be initialized as output.<br>

> ### Toggle gpio output.<br>
```toggle_gpio(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

The pin must be initialized as output.<br>

> ### Blink gpio output.<br>
```blink_gpio(pin, period)```<br>
***pin:*** ```<integer>``` 2..27<br>
***period:*** ```<integer>``` 100.. (ms)<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

The pin must be initialized as output.<br>
Call with ***period*** of 0 stops blinking.

> ### Stop blinking gpio output.<br>
```stop_blink_gpio(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

The pin must be initialized as output.<br>
Call of ```toggle_gpio``` or ```set_gpio``` stops also blinking.<br>

## Pulse Wide Modulation (PWM) Functions
Pulse Wide Modulation pulse is generated on output.<br>
PWM can be used for example to adjust the brightness of LEDs.<br>
Because PWM is generated with software, the accuracy of dutycycle is accurate up to approximately 800Hz.<br>
For better accuracy use mode **GPIO_MODE_PWM_REALTIME**.<br>
In **GPIO_MODE_PWM_REALTIME** mode the CPU load is higher.<br>
The on+off time is 1/frequency (e.g. 1/100Hz = 10ms).<br>
Dutycycle means the % time for on.<br>
For example dutycycle 75% on 100Hz is 7.5ms on and 2.5ms off time.<br>
A dutycycle of 0% turns output off.<br>
A dutycycle of 100% turns output on.<br>

> ### Init pwm and sets frequency and dutycycle.<br>
```init_pwm(pin, mode, frequency_hz, dutycycle)```<br>
***pin:*** ```<integer>``` 2..27<br>
***mode:*** ```<integer>``` GPIO_MODE_PWM...<br>
***frequency_hz:*** ```<integer>``` 1..45000 (Hz)<br>
***dutycycle:*** ```<integer>``` 0..100 (%)<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

Starts pwm engine.<br>

> ### Sets pwm frequency and dutycycle.<br>
```set_pwm(pin, frequency_hz, dutycycle)```<br>
***pin:*** ```<integer>``` 2..27<br>
***frequency_hz:*** ```<integer>``` 1..45000 (Hz)<br>
***dutycycle:*** ```<integer>``` 0..100 (%)<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

Function ```init_pwm``` must be called before.<br>

> ### Gets pwm frequency.<br> 
```get_pwm_frequency(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** ```<integer>``` 1..45000 (Hz), ```undefined``` on error.<br>

> ### Gets pwm dutycycle.<br> 
```get_pwm_dutycycle(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** 0..100 (%), ```undefined``` on error.<br>

|Constant|Value|Function|
|:--|:--|:--|
|DUTY_MIN|0|min. duty cycle|
|DUTY_MAX|100|max. duty cycle|
|FREQ_MIN|1|min. frequency|
|FREQ_MAX|45000|max. frequency|

## High Speed Counter Functions
Implements high speed software counter.<br>
Counts on each **edge** changes of input up/down.<br>
Optional can be assign a reset and output hardware pin.<br> 

## cnt_mode Parameter
The ```cnt_mode``` parameter sets the count direction of counter.<br>
|Constant|Value|Function|
|:--|:--|:--|
|C_UP|0|counts up to ```counter_high```|
|C_DOWN|1|counts down to zero|

> ### Init counter pin.<br>
```init_counter_pin(pin, mode, debounce, edge)```<br>
***pin:*** ```<integer>``` 2..27<br>
***mode:*** ```<integer>``` GPIO_MODE_COUNTER...<br>
***debounce:*** ```<integer>``` 0..<br>
***edge:*** ```<integer>``` GPIO_EDGE_...<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

The ***debounce*** parameter sets the **debounce time** in us for inputs,<br>
and can set to 0 for disable debounce.<br>
The counter pin must init before call ```init_counter```.

> ### Init counter reset pin.<br>
```init_counter_reset_pin(pin, pin_reset, mode, debounce, edge)```<br>
***pin:*** ```<integer>``` 2..27<br>
***pin_reset:*** ```<integer>``` 2..27<br>
***mode:*** ```<integer>``` GPIO_MODE_INPUT...<br>
***debounce:*** ```<integer>``` 0..<br>
***edge:*** ```<integer>``` GPIO_EDGE_...<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

The ***debounce*** parameter sets the **debounce time** in us for inputs,<br>
and can set to 0 for disable debounce.<br>
On ***edge:*** of pin the counter is reset.<br>
Parameter ```pin``` is the counter pin used in ```init_counter_pin```.<br>
The counter reset pin should init before call ```init_counter```.<br>

> ### Init counter output pin.<br>
```init_counter_output_pin(pin, pin_output, mode)```<br>
***pin:*** ```<integer>``` 2..27<br>
***pin_output:*** ```<integer>``` 2..27<br>
***mode:*** ```<integer>``` GPIO_MODE_OUTPUT...<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

Parameter ```pin``` is the counter pin used in ```init_counter_pin```.<br>
Output pin is set if counter is on limit.<br> 
The counter output pin should init before call ```init_counter```.<br>

> ### Init counter.<br>
```init_counter(pin, counter_high, cnt_mode, callback)```<br>
***pin:*** ```<integer>``` 2..27<br>
***counter_high:*** ```<integer>``` 1..4294967294<br>
***cnt_mode:*** ```<integer>``` **C_UP**, **C_DOWN**<br>
***callback:*** ```<function> (counter, on_limit, cnt_mode, counter_high, pin)```
- **counter** ```<integer>``` 0..4294967294.<br> 
- **on_limit** ```<boolean>``` true if counter on limit<br> 
- ***cnt_mode:*** ```<integer>``` **C_UP**, **C_DOWN**<br>
- ***counter_high:*** ```<integer>```1..4294967294<br>
- **pin** ```<integer>``` 2..27.<br> 
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

The ```callback``` function is called on any counter changes.<br>
Starts counter engine.<br>
Resets also counter (see reset_counter).<br>

> ### Sets counter.<br>
```set_counter(pin, counter_high, cnt_mode)```<br>
***pin:*** ```<integer>``` 2..27<br>
***counter_high:*** ```<integer>``` 1..4294967294<br>
***cnt_mode:*** ```<integer>``` **C_UP**, **C_DOWN**<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

Resets also counter (see reset_counter).<br>

> ### Resets counter.<br>
```reset_counter(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

cnt_mode = **C_UP**: counter is set to 0.<br>
cnt_mode = **C_DOWN**: counter is set to ```counter_high```.<br>

> ### Gets counter value.<br>
```get_counter(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** ```<integer>``` counter value (0..4294967294), ```undefined``` on error<br>

> ### Gets counter_high value.<br>
```get_counter_high(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** ```<integer>``` ```counter_high``` value (1..4294967294), ```undefined``` on error<br>

> ### Gets counter mode.<br>
```get_counter_mode(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return :*** ```<integer>``` **C_UP**, **C_DOWN**, ```undefined``` on error<br>

> ### Check if counter is on limits.<br>
```is_counter_onlimit(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return :*** ```<boolean>``` ```true/false```, ```undefined``` on error<br>

cnt_mode = **C_UP**: returns ```true``` when counter is equal ***counter_high***.<br>
cnt_mode = **C_DOWN**: returns ```true``` when counter is equal 0.<br>

|Constant|Value|Function|
|:--|:--|:--|
|COUNTER_MIN|0|min. counter value|
|COUNTER_MIN_HIGH|1|min. ```counter_high``` value|
|COUNTER_MAX|4294967294|max. counter value|

## Temperature Sensors with 1-wire protocol
The functions reads the DS18B20 sensor temperature.<br>
You can connect multiple sensors in parallel.<br>
It is important that a 4.7k pullup resistor is connected.<br>
The library does not support the parasite mode.<br>
Please do not activate the 1-wire subsystem of the raspberry pi.<br>
For high-performance reading, all sensors must have set to the same resolution.<br>

## res Parameter
The ```res``` (resolution) parameter sets the resolution of ds18b20 sensors.<br>
|Constant|Value|Resolution|Conversion Time|Temp. Steps|
|:--|:--|:--|:--|:--|
|RES_SENSOR_9|0|9 bit|94ms|0.5°|
|RES_SENSOR_10|1|10 bit|187ms|0.25°|
|RES_SENSOR_11|2|11 bit|375ms|0.125°|
|RES_SENSOR_12|3|12 bit|750ms|0.0625°|

> ### Init all sensors to resolution.<br>

```init_sensor(pin, res)```<br>
***pin:*** ```<integer>``` 2..27<br>
***res:*** ```<integer>``` RES_SENSOR_..<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

> ### Scans all sensors.<br>

```scan_sensor(pin, callback)```<br>
***pin:*** ```<integer>``` 2..27<br>
***callback:*** ```<function> (ret)```<br> 
- **ret** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

The sensor id's are stored in an internal list.<br>

```scan_sensor_sync(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** ```<boolean>``` ```true``` on ok, ```false``` on error.<br>

The sensors id's are stored in an internal list.<br>

> ### List all sensors.<br>

```list_sensor(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** ```<string array>``` list of sensors id in format 28-HHHHHHHHHHHH (hex), ```undefined``` on error.<br> 

List the sensor id's in internal list.<br>
```scan_sensor``` must be called before.<br>

> ### Get sensor count.<br>

```get_sensor_count(pin)```<br>
***pin:*** ```<integer>``` 2..27<br>
***return:*** ```<integer>``` number of sensors, ```undefined``` on error.<br> 

Get sensor count in internal list.<br>
```scan_sensor``` must be called before.<br>

> ### Read all sensors.<br>

```read_sensor(pin, fh, callback)```<br>
***pin:*** ```<integer>``` 2..27<br>
***fh:*** ```<boolean>``` ```false:``` output is celsius, ```true:``` output is fahrenheit.<br>
***callback:*** ```<function> (data)```<br> 
- **data** ```<number array>``` temperature of sensors, ```undefined``` on error.<br>

Reads all sensors stored in internal list.<br>
```scan_sensor``` must be called before.<br>

```read_sensor_sync(pin, fh)```<br>
***pin:*** ```<integer>``` 2..27<br>
***fh:*** ```<boolean>``` ```false:``` output is celsius, ```true:``` output is fahrenheit.<br>
***return:*** ```<number array>``` temperature of sensors, ```undefined``` on error.<br> 

Reads all sensors stored in internal list.<br>
```scan_sensor``` must be called before.<br>

> ### Read one sensor.<br>

```read_one_sensor(pin, id, fh, callback)```<br>
***pin:*** ```<integer>``` 2..27<br>
***id:*** ```<string>``` id of sensor in format 28-HHHHHHHHHHHH (hex).<br>
***fh:*** ```<boolean>``` ```false:``` output is celsius, ```true:``` output is fahrenheit.<br>
***callback:*** ```<function> (data)```<br> 
- **data** ```<number>``` temperature of sensor, ```undefined``` on error.<br>

The sensor is read independently of the internal list.<br>

```read_one_sensor_sync(pin, id, fh)```<br>
***pin:*** ```<integer>``` 2..27<br>
***id:*** ```<string>``` id of sensor in format 28-HHHHHHHHHHHH (hex).<br>
***fh:*** ```<boolean>``` ```false:``` output is celsius, ```true:``` output is fahrenheit.<br>
***return:*** ```<number>``` temperature of sensor, ```undefined``` on error. 

The sensor is read independently of the internal list.<br>
