This part moves from making the ESP32 visible over BLE to sending commands from a phone to control the
onboard RGB LED.
BLE advertising is how a BLE device announces its presence. A phone can scan for these advertisements and
display the device name.
The ESP32 creates a service with a writable characteristic. Your phone writes R,
G, W, B or O, and the ESP32 changes its onboard RGB LED.
In my circuit the Red and Green properties are swapped that's why the slight change in the code.
