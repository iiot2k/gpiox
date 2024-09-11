# @isim/gpiox
# Forked from @iiot2k/gpiox

[![platform](https://img.shields.io/badge/platform-Raspberry--Pi-ff69b4)](https://www.raspberrypi.com/)

Raspberry Pi gpiox library

Thank you so much to iiot2k for the great working implementing gpiox in node.js. Please support them with the link below
<a href="https://www.buymeacoffee.com/iiot2ka" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-red.png" height="41" width="174"></a><br>


## Installation
```
npm install @isim/gpiox
```
or add in your ```package.json```:

```json
"dependencies": {
    "@isim/gpiox": "latest"
},
```
[View on npm](https://www.npmjs.com/package/@isim/gpiox)📌<br>
Original:
[View on npm](https://www.npmjs.com/package/@iiot2k/gpiox)📌<br>

[View on GitHub](https://github.com/isim/gpiox)📌<br>
Original:
[View on GitHub](https://github.com/iiot2k/gpiox)📌<br>

[Report any type issues here](https://github.com/isim/gpiox/issues)📌

[Report any functionality issues here](https://github.com/iiot2k/gpiox/issues)📌

## Detail
- This library works on Raspberry Pi with 32bit or 64bit OS
- Works also on Raspberry Pi 5

## Functions
- Read/write/toggle/blink gpio
- Watch gpio changes
- PWM output
- High speed gpio counter
- Reads temperature from sensors (DS18B20) connected on gpio

## Node.js API
Node.js API functions are explained in document **API.md**<br>
Node.js examples are on **examples** folder.<br>

```javascript
// node.js example turns output pin 20 on and after 3000ms off
"use strict";

const gpiox = require("@iiot2k/gpiox");

gpiox.init_gpio(20, gpiox.GPIO_MODE_OUTPUT, 1);

setTimeout(() => {
    gpiox.set_gpio(20, 0);
    gpiox.deinit_gpio(20);
}, 3000);

```
## C++ API
This library uses C++ addon modules as interface to hardware.<br>
Therefore, there is also a C++ interface to the drivers.<br>
Unfortunately the C++ addon modules are not open source.<br>
I provide the C++ static link libraries.<br>
But if you are interested in the sources, I can send them to you.<br>
Please send me an email with your name to iiot2k@gmail.com <br>
I can only provide limited support for the C++ addon modules sources.<br>

I have shown some C++ examples in the **cpp** directory and on [GitHub](https://github.com/iiot2k/gpiox/tree/main/cpp)📌<br>
The C++ API functions are described in the header file **gpiox_lib.h**

```C++
// C++ example turns output on and after 3000ms off

#include <stdio.h>

#include "gpiox_lib.h"

void timeout_callback()
{
    gpiox::set_gpio(20, 0);
    gpiox::deinit_gpio(20);
}

int main()
{
    gpiox::init_gpio(20, gpiox::GPIO_MODE_OUTPUT, 1);
    gpiox::set_timeout(timeout_callback, 3000);

    return 0;
}

```
