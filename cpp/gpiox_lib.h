/*
 * 
 * (c) Derya Y. iiot2k@gmail.com
 *
 * Raspberry Pi gpio c++ library
 *
 * the library uses the gpio character devices interface (V2) from the Linux operating system
 * to prevent mermory leaks, when library is unloaded function deinit_gpio is called for all pins
 * 
 * link library with your application
 * libgpiox_arm32.a on 32bit OS
 * libgpiox_arm64.a on 64bit OS
 *
 * gpiox_lib.h
 *
 */

#pragma once

#include <vector>
#include <string>
using namespace std;

#include <stdint.h>

namespace gpiox {

/************** Helper functions **************/

/**
 * @brief timeout callback function
 */
typedef void (*timeout_cb)();

/**
 * @brief calls callback function after timeout as thread (same as node.js setTimeout)
 * @param cb timeout callback function
 * @param timeout_ms timeout in ms
 * @param id storage of id used in clear_timeout()
 * @param wait if true waits until functions return, on false returns immediately
 */
void set_timeout(timeout_cb cb, uint32_t timeout_ms, int32_t* id = NULL, bool wait = true);

/**
 * @brief stops timeout
 * @param id - id returned by set_timeout
 */
void clear_timeout(int32_t id);

/**
 * @brief interval callback function
 */
typedef void (*interval_cb)();

/**
 * @brief calls callback function in interval as thread (same as node.js setInterval)
 * @param cb interval callback function
 * @param timeout_ms timeout in ms
 * @param id storage of id used in clear_interval()
 * @param wait if true waits until functions return, on false returns immediately
 */
void set_interval(timeout_cb cb, uint32_t timeout_ms, int32_t* id = NULL, bool wait = true);

/**
 * @brief stops interval
 * @param id returned by set_interval
 */
void clear_interval(int32_t id);

/**
 * @brief gets error text after call functions
 * @returns error text
 */
const char* error_text();

/************** GPIO initialization functions **************/

/**
 * @brief gpio modes
 * @note floating input/output is used when the pin is connected to another pin
 * input voltages more than +3.3V can destroy the input
 * Hi-Z refers to an output signal state in which the signal is not being driven
 * please do not init gpio pins with special functions (i2c, spi, uart..)
 * gpio output current is limited
 * use ULN2803A (low switch) or TBD62783 (high switch) for drive output
 */
enum {
    GPIO_MODE_INPUT_NOPULL = 0, // floating input (used in init_gpio or change_gpio)
    GPIO_MODE_INPUT_PULLDOWN,   // pulldown resistor input (used in init_gpio or change_gpio)
    GPIO_MODE_INPUT_PULLUP,     // pullup resistor input (used in init_gpio or change_gpio)
    GPIO_MODE_OUTPUT,           // output (used in init_gpio or change_gpio)
    GPIO_MODE_OUTPUT_SOURCE,    // output source (Hi-Z on 0) (used in init_gpio or change_gpio)
    GPIO_MODE_OUTPUT_SINK,      // output sink (Hi-Z on 0) (used in init_gpio or change_gpio)
    GPIO_MODE_PWM,              // pwm output pulse (used in init_pwm)
    GPIO_MODE_PWM_REALTIME,     // pwm output pulse in realtime (used in init_pwm)
    GPIO_MODE_COUNTER_NOPULL,   // floating input counter (used in init_counter_pin)
    GPIO_MODE_COUNTER_PULLDOWN, // pulldown resistor input counter (used in init_counter_pin)
    GPIO_MODE_COUNTER_PULLUP,   // pullup resistor input counter (used in init_counter_pin)
    GPIO_MODE_SENSOR,           // output sink (used internal in function init_sensor)
};

/**
 * @brief init gpio input/output with mode
 * @param pin gpio pin (2..27)
 * @param mode GPIO_MODE_INPUT_.. or GPIO_MODE_OUTPUT..
 * @param setval debounce time in us for inputs, 0/1 or true/false for output
 * @returns true on ok, false on error (error_text() returns reason)
 * @note gpio should not be initialized before with a mode
 * @note setval 0 for inputs disables debounce
 */
bool init_gpio(uint32_t pin, uint32_t mode, uint32_t setval);

/**
 * @brief changes mode of input/output gpio
 * @param pin gpio pin (2..27)
 * @param mode GPIO_MODE_INPUT_.. or GPIO_MODE_OUTPUT..
 * @param setval debounce time in us for inputs, 0/1 or true/false for output
 * @returns true on ok, false on error (error_text() returns reason)
 * @note gpio should not be initialized with mode GPIO_MODE_INPUT_.. or GPIO_MODE_OUTPUT..
 * @note setval 0 for inputs disables debounce
 */
bool change_gpio(uint32_t pin, uint32_t mode, uint32_t setval);

/**
 * @brief deinit gpio (for all modes)
 * @param pin gpio pin (2..27)
 * @returns true on ok, false on error (error_text() returns reason)
 * @note should be called after the end of the program
 * @note stops also all background threads (blink, pwm..)
 */
bool deinit_gpio(uint32_t pin);

/************** GPIO input watch functions **************/

/**
 * @brief watch input callback function
 * @param state input state 0/1
 * @param edge GPIO_EDGE_RISING or GPIO_EDGE_FALLING
 * @param pin gpio pin (2..27)
 */
typedef void (*watch_cb)(uint32_t state, uint32_t edge, uint32_t pin);

/**
 * @brief gpio input edges used in function watch_gpio
 */
enum {
    GPIO_EDGE_RISING = 0,   // check for change from 0 to 1
    GPIO_EDGE_FALLING,      // check for change from 1 to 0
    GPIO_EDGE_BOTH,         // check for change from 0 to 1 or 1 to 0
};

/**
 * @brief watch gpio input for changes
 * @param pin gpio pin (2..27)
 * @param mode GPIO_MODE_INPUT_..
 * @param debounce time in us
 * @param edge GPIO_EDGE_RISING, GPIO_EDGE_FALLING or GPIO_EDGE_BOTH
 * @param cb watch input callback function
 * @note gpio should not be initialized with a mode
 * @note value 0 disables debounce
 * @returns true on ok, false on error (error_text() returns reason)
 * @note function starts background thread and retuns
 */
bool watch_gpio(uint32_t pin, uint32_t mode, uint32_t debounce, uint32_t edge, watch_cb cb);

/************** GPIO Input/Output functions **************/

/**
 * @brief get gpio state
 * @param pin gpio pin (2..27)
 * @returns true on active, false on deactive
 */
bool get_gpio(uint32_t pin);

/**
 * @brief get gpio state as number (0/1)
 * @param pin gpio pin (2..27)
 * @returns 1 on active, 0 on deactive
 */
uint32_t get_gpio_num(uint32_t pin);

/**
 * @brief set gpio output
 * @param pin gpio pin (2..27)
 * @param val 0/1 or true/false
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool set_gpio(uint32_t pin, uint32_t val);

/**
 * @brief toggle (change state) of gpio output
 * @param pin gpio pin (2..27)
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool toggle_gpio(uint32_t pin);

/**
 * @brief blink gpio output on period
 * @param pin gpio pin (2..27)
 * @param period blink period in ms (100..)
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool blink_gpio(uint32_t pin, uint32_t period);

/**
 * @brief stop gpio blink and set output to 0
 * @param pin gpio pin (2..27)
 * @returns true on ok, false on error (error_text() returns reason)
 * @note call of toggle_gpio() or set_gpio() stops also blink
 */
bool stop_blink_gpio(uint32_t pin);

/************** Pulse Wide Modulation (PWM) functions **************
 *
 * pulse Wide Modulation is generated on output
 * PWM can be used for example to adjust the brightness of LEDs
 * because PWM is generated with software, the accuracy of dutycycle is accurate up to approximately 800Hz
 * for better accuracy use mode GPIO_MODE_PWM_REALTIME
 * in GPIO_MODE_PWM_REALTIME mode the CPU load is higher
 * the on+off time is 1/frequency (e.g. 1/100Hz = 10ms)
 * dutycycle means the % time for on
 * for example dutycycle 75% on 100Hz is 7.5ms on and 2.5ms off time
 * a dutycycle of 0% turns output off
 * a dutycycle of 100% turns output on
 */

// pwm constants
#define DUTY_MIN 0      // min. duty cycle (%)
#define DUTY_MAX 100    // max. duty cycle (%)
#define FREQ_MIN 1      // min. pwm frequency (Hz)
#define FREQ_MAX 45000  // max. pwm frequency (Hz)

/**
 * @brief init output as pwm
 * @param pin gpio pin (2..27)
 * @param mode GPIO_MODE_PWM or GPIO_MODE_PWM_REALTIME
 * @param frequency initial pwm frequency in Hz
 * @param dutycycle initial pwm duty cycle in %
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool init_pwm(uint32_t pin, uint32_t mode, uint32_t frequency, uint32_t dutycycle);

/**
 * @brief set pwm parameter
 * @param pin gpio pin (2..27)
 * @param frequency pwm frequency in Hz
 * @param dutycycle pwm duty cycle in %
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool set_pwm(uint32_t pin, uint32_t frequency, uint32_t dutycycle);

/**
 * @brief gets pwm frequency
 * @param pin gpio pin (2..27)
 * @returns pwm frequency in Hz
 */
uint32_t get_pwm_frequency(uint32_t pin);

/**
 * @brief gets pwm duty-cycle
 * @param pin gpio pin (2..27)
 * @returns pwm duty cycle in %
 */
uint32_t get_pwm_dutycycle(uint32_t pin);

/************** GPIO Counter functions **************
 *
 * implements high speed software counter
 * counts up/down on each edge changes of input
 * optional can be assign a reset and output hardware pin
 */

// counter constants
#define COUNTER_MIN 0           // min. counter value
#define COUNTER_MIN_HIGH 1      // min. counter high value
#define COUNTER_MAX 4294967294  // max. counter value

/**
 * @brief counter modes used in function init_counter and set_counter
 */
enum {
    C_UP = 0, // count up
    C_DOWN    // count down
};

/**
 * @brief init counter input pin
 * @param pin gpio counter pin (2..27)
 * @param mode GPIO_MODE_COUNTER_..
 * @param debounce time in us
 * @param edge GPIO_EDGE_RISING, GPIO_EDGE_FALLING or GPIO_EDGE_BOTH
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool init_counter_pin(uint32_t pin, uint32_t mode, uint32_t debounce, uint32_t edge);

/**
 * @brief init counter reset pin
 * @param pin gpio counter pin (2..27)
 * @param pin_reset gpio counter reset pin (2..27)
 * @param mode GPIO_MODE_INPUT_..
 * @param debounce time in us
 * @param edge GPIO_EDGE_RISING, GPIO_EDGE_FALLING or GPIO_EDGE_BOTH
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool init_counter_reset_pin(uint32_t pin, uint32_t pin_reset, uint32_t mode, uint32_t debounce, uint32_t edge);

/**
 * @brief init counter output pin
 * @param pin gpio counter pin (2..27)
 * @param pin_output gpio counter output pin (2..27)
 * @param mode GPIO_MODE_OUTPUT_..
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool init_counter_output_pin(uint32_t pin, uint32_t pin_output, uint32_t mode);

/**
 * @brief counter callback function
 * @param counter actual counter value
 * @param onlimit true: counter on limit (0 or counter_high)
 * @param mode C_UP or C_DOWN
 * @param high counter high limit (1..4294967294)
 * @param pin gpio counter pin (2..27)
 */
typedef void (*counter_cb)(uint32_t counter, bool onlimit, uint32_t mode, uint32_t high, uint32_t pin);

/**
 * @brief init and start counter
 * @param pin gpio counter pin (2..27)
 * @param counter_high counter high limit (1..4294967294)
 * @param cnt_mode gpio counter direction C_UP or C_DOWN
 * @param cb counter callback function
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool init_counter(uint32_t pin, uint32_t counter_high, uint32_t cnt_mode, counter_cb cb);

/**
 * @brief set counter parameter
 * @param pin gpio counter pin (2..27)
 * @param counter_high counter high limit (1..4294967294)
 * @param cnt_mode gpio counter direction C_UP or C_DOWN
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool set_counter(uint32_t pin, uint32_t counter_high, uint32_t cnt_mode);

/**
 * @brief reset counter
 * @param pin gpio counter pin (2..27)
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool reset_counter(uint32_t pin);

/**
 * @brief get counter value
 * @param pin gpio counter pin (2..27)
 * @returns actual counter value
 */
uint32_t get_counter(uint32_t pin);

/**
 * @brief get counter high limit
 * @param pin gpio counter pin (2..27)
 * @returns counter high limit (1..4294967294)
 */
uint32_t get_counter_high(uint32_t pin);

/**
 * @brief get counter direction (mode)
 * @param pin gpio counter pin (2..27)
 * @returns C_UP or C_DOWN
 */
uint32_t get_counter_mode(uint32_t pin);

/**
 * @brief check if counter on limit
 * @param pin gpio counter pin (2..27)
 * @returns true: counter on limit (0 or counter_high)
 */
bool is_counter_onlimit(uint32_t pin);

/************** Sensor Functions **************
 * the functions reads the DS18B20 sensor temperatures
 * you can connect multiple sensors in parallel
 * it is important that a 4.7k pullup resistor is connected
 * the library does not support the parasite mode
 * please do not activate the linux 1-wire subsystem of the raspberry pi
 * for high-performance reading, all sensors must have set to the same resolution
 *
 * Resolution|Conversion Time|Temp. Steps|
 * ----------|---------------|-----------|
 * 9 bit     |94ms           |0.5°       |
 * 10 bit    |187ms          |0.25°      |
 * 11 bit    |375ms          |0.125°     |
 * 12 bit    |750ms          |0.0625°    |
 */

// sensor resolution
enum {
    RES_SENSOR_9 = 0, // 9 bit
    RES_SENSOR_10,    // 10 bit
    RES_SENSOR_11,    // 11 bit
    RES_SENSOR_12,    // 12 bit
};

// ivalid temperature used in sensor functions
#define INV_TEMP -9999.0

/**
 * @brief init sensor pin and resolution
 * @param pin gpio sensor pin (2..27)
 * @param res RES_SENSOR_..
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool init_sensor(uint32_t pin, uint32_t res);

/**
 * @brief scan for sensors on pin and store in internal list
 * @param pin gpio sensor pin (2..27)
 * @returns true on ok, false on error (error_text() returns reason)
 * @note init_sensor must called before
 */
bool scan_sensor(uint32_t pin);

/**
 * @brief list all found sensors
 * @param pin gpio sensor pin (2..27)
 * @param sensor_list list of sensors id's in format 28-HHHHHHHHHHHH (hex)
 * @returns true on ok, false on error (error_text() returns reason)
 * @note init_sensor and scan_sensor must called before
 */
bool list_sensor(uint32_t pin, vector<string>& sensor_list);

/**
 * @brief get count of found sensors
 * @param pin gpio sensor pin (2..27)
 * @returns true on ok, false on error (error_text() returns reason)
 * @note init_sensor and scan_sensor must called before
 */
bool get_sensor_count(uint32_t pin, uint32_t& sensor_count);

/**
* @brief read all sensors in internal list
* @param pin gpio sensor pin (2..27)
* @param fh false: output is celsius, true: output is fahrenheit
* @param temp_data sensor temperatures
* @returns true on ok, false on error (error_text() returns reason)
* @note init_sensor and scan_sensor must called before
*/
bool read_sensor(uint32_t pin, bool fh, vector<double>& temp_data);

/**
 * @brief read one sensor with given id
 * @param pin gpio sensor pin (2..27)
 * @param id id of sensor in format 28-HHHHHHHHHHHH (hex)
 * @param fh false: output is celsius, true: output is fahrenheit
 * @param temp_data sensor temperature
 * @returns true on ok, false on error (error_text() returns reason)
 * @note init_sensor must called before
 */
bool read_one_sensor(uint32_t pin, const char* id, bool fh, double& temp_data);

} // namespace
