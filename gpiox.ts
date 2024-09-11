/**
 * Copyright 2024 Derya Y. (iiot2k@gmail.com).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use node file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/

"use strict";
type Enumerate<
  N extends number,
  Acc extends number[] = []
> = Acc["length"] extends N
  ? Acc[number]
  : Enumerate<N, [...Acc, Acc["length"]]>;

type IntRange<F extends number, T extends number> = Exclude<
  Enumerate<T>,
  Enumerate<F>
>;

declare module "@isim/gpiox" {
  function error_test(): string;
  type pin = IntRange<2, 28>;
  type numOrBool = number | boolean;
  type state = 0 | 1 | undefined;
  type boolState = boolean | undefined;
  type pwmFreq = number;
  type dutyCycle = IntRange<0, 101>;
  enum COUNTER {
    MIN,
    MIN_HIGH,
    MAX = 4294967294,
  }
  type counterRange = number;
  enum GPIO_MODE {
    INPUT_NOPULL,
    INPUT_PULLDOWN,
    INPUT_PULLUP,
    OUTPUT,
    OUTPUT_SOURCE,
    OUTPUT_SINK,
    PWM,
    PWM_REALTIME,
    COUNTER_NOPULL,
    COUNTER_PULLDOWN,
    COUNTER_PULLUP,
    SENSOR,
  }
  function init_gpio(pin: pin, mode: GPIO_MODE, setval: numOrBool): boolean;
  function change_gpio(pin: pin, mode: GPIO_MODE, setval: numOrBool): boolean;
  function deinit_gpio(pin: pin): boolean;
  enum GPIO_EDGE {
    RISING,
    FALLING,
    BOTH,
  }
  function watch_gpio(
    pin: pin,
    mode: GPIO_MODE,
    debounce: number,
    edge: GPIO_EDGE,
    callback: (
      state: number,
      edge: Exclude<GPIO_EDGE, GPIO_EDGE.BOTH>,
      pin: pin
    ) => void
  ): state;
  function get_gpio(pin: pin): boolState;
  function get_gpio_num(pin: pin): state;
  function set_gpio(pin: pin, value: state): boolState;
  function toggle_gpio(pin: pin): boolean;
  function blink_gpio(pin: pin, period: number): boolean;
  function stop_blink_gpio(pin: pin): boolean;
  function init_pwn(
    pin: pin,
    mode: GPIO_MODE,
    frequency_hz: pwmFreq,
    dutycycle: dutyCycle
  ): boolean;
  function set_pwn(
    pin: pin,
    frequency_hz: pwmFreq,
    dutycycle: dutyCycle
  ): boolean;
  function get_pwn_frequency(pin: pin): pwmFreq;
  function get_pwm_dutycycle(pin: pin): dutyCycle | undefined;
  enum CNT_MODE {
    C_UP,
    C_DOWN,
  }
  function init_counter_pin(
    pin: pin,
    mode: GPIO_MODE,
    debounce: number,
    edge: GPIO_EDGE
  ): boolean;
  function init_counter_reset_pin(
    pin: pin,
    pin_reset: pin,
    mode: GPIO_MODE,
    debounce: number,
    edge: GPIO_EDGE
  ): boolean;
  function init_counter_output_pin(
    pin: pin,
    pin_output: pin,
    mode: GPIO_MODE
  ): boolean;
  function init_counter(
    pin: pin,
    counter_high: counterRange,
    cnt_mode: CNT_MODE,
    callback: (
      counter: counterRange,
      on_limit: boolean,
      cnt_mode: CNT_MODE,
      counter_high: counterRange,
      pin: pin
    ) => void
  ): boolean;
  function set_counter(
    pin: pin,
    counter_high: counterRange,
    cnt_mode: CNT_MODE
  ): boolean;
  function reset_counter(pin: pin): boolean;
  function get_counter(pin: pin): counterRange | undefined;
  function get_counter_high(pin: pin): counterRange | undefined;
  function get_counter_mode(pin: pin): CNT_MODE | undefined;
  function is_counter_onlimit(pin: pin): boolState;
  enum RES_SENSOR {
    SENSOR_9,
    SENSOR_10,
    SENSOR_11,
    SENSOR_12,
  }
  function init_sensor(pin: pin, res: RES_SENSOR): boolean;
  function scan_sensor(pin: pin, callback: () => boolean): void;
  function scan_sensor_sync(pin: pin): boolean;
  function list_sensor(pin: pin): string[] | undefined;
  function get_sensor_count(pin: pin): number | undefined;
  function read_sensor(
    pin: pin,
    fh: boolean,
    callback: (data: number[] | undefined) => void
  ): void;
  function read_sensor_sync(pin: pin, fh: boolean): number[] | undefined;
  function read_one_sensor(
    pin: pin,
    id: string,
    fh: boolean,
    callback: (data: number[] | void) => void
  ): void;
  function read_one_sensor_sync(
    pin: pin,
    id: string,
    fh: boolean
  ): number | undefined;
}

// Loads driver depends on platform
module.exports = require("./gpiox_arm64.node");
// if (process.platform === "linux") {
//   if (process.arch === "arm64") module.exports = require("./gpiox_arm64.node");
//   else if (process.arch === "arm")
//     module.exports = require("./gpiox_arm32.node");
// }
