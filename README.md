# esp32-manager-example

**esp32-manager** helps with the configuration and management of settings on ESP32.

## Features

- Simplifies reading from and writing to flash using NVS for any variable in your application. Just register any variable with esp32_manager and you will get simple read and write functions for NVS.
- Easy WiFi connection to networks or creation of APs. Automatic AP creation for WiFi configuration.
- Creates a web interface to configure any setting in your application registered with *esp32_manager*.
- Easily publish values to MQTT in a structured and consistent way.

## Usage

### Setup workspace

This is an ESP-IDF project that includes `esp32-manager` as a submodule. Clone it using:

    git clone --recurse-submodules https://github.com/pablobacho/esp32-manager-example.git

### ESP-IDF component

`esp32-manager` is vailable as an ESP-IDF component. To include it in your project, you can clone the repository below into the *components* folder in your project.

Check out its repository at [https://github.com/pablobacho/esp32-manager](https://github.com/pablobacho/esp32-manager)
    
