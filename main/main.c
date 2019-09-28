#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp32_manager.h"

static const char * TAG = "esp32-manager-example";

#define EXAMPLE_NAMESPACE_KEY       "example"
#define EXAMPLE_NAMESPACE_FRIENDLY  "Example"

#define EXAMPLE_COUNTER_KEY         "counter"
#define EXAMPLE_COUNTER_FRIENDLY    "Counter"

#define EXAMPLE_DELAY_KEY           "delay"
#define EXAMPLE_DELAY_FRIENDLY      "Delay"

#define EXAMPLE_ENTRIES_MAX         2

int16_t counter = 0;
uint32_t delay = 1000;

esp32_manager_entry_t * example_entries[EXAMPLE_ENTRIES_MAX];

esp32_manager_namespace_t example_namespace = {
    .key = EXAMPLE_NAMESPACE_KEY,
    .friendly = EXAMPLE_NAMESPACE_FRIENDLY,
    .entries = example_entries,
    .entries_size = EXAMPLE_ENTRIES_MAX
};

esp32_manager_entry_t counter_entry = {
    .key = EXAMPLE_COUNTER_KEY,
    .friendly = EXAMPLE_COUNTER_FRIENDLY,
    .type = i16,
    .value = (void *) &counter,
    .attributes = ESP32_MANAGER_ATTR_READ
};

esp32_manager_entry_t delay_entry = {
    .key = EXAMPLE_DELAY_KEY,
    .friendly = EXAMPLE_DELAY_FRIENDLY,
    .type = u32,
    .value = (void *) &delay,
    .attributes = ESP32_MANAGER_ATTR_READWRITE
};

void app_main(void)
{
    esp_err_t e;

    // Silence system logs
    esp_log_level_set("intr_alloc", ESP_LOG_WARN);
    esp_log_level_set("clk", ESP_LOG_WARN);
    esp_log_level_set("stack_chk", ESP_LOG_WARN);
    esp_log_level_set("heap_init", ESP_LOG_WARN);
    esp_log_level_set("nvs", ESP_LOG_WARN);
    esp_log_level_set("event", ESP_LOG_WARN);
    esp_log_level_set("wifi", ESP_LOG_WARN);
    esp_log_level_set("phy_init", ESP_LOG_WARN);
    esp_log_level_set("httpd", ESP_LOG_WARN);
    esp_log_level_set("httpd_sess", ESP_LOG_WARN);
    esp_log_level_set("httpd_txrx", ESP_LOG_WARN);
    esp_log_level_set("httpd_parse", ESP_LOG_WARN);
    esp_log_level_set("httpd_uri", ESP_LOG_WARN);

    // Initialize esp32_manager
    esp32_manager_init();

    // Register namespace
    e = esp32_manager_register_namespace(&example_namespace);
    if(e == ESP_OK) {
        ESP_LOGD(TAG, "%s namespace registered", EXAMPLE_NAMESPACE_KEY);
    } else {
        ESP_LOGE(TAG, "Error registering namespace: %s", esp_err_to_name(e));
    }

    // Register entries with esp32_manager
    e = esp32_manager_register_entry(&example_namespace, &counter_entry);
    if(e == ESP_OK) {
        ESP_LOGD(TAG, "%s.%s registered", example_namespace.key, counter_entry.key);
    } else {
        ESP_LOGE(TAG, "Error registering %s.%s", example_namespace.key, counter_entry.key);
    }

    e = esp32_manager_register_entry(&example_namespace, &delay_entry);
    if(e == ESP_OK) {
        ESP_LOGD(TAG, "%s.%s registered", example_namespace.key, delay_entry.key);
    } else {
        ESP_LOGE(TAG, "Error registering %s.%s", example_namespace.key, delay_entry.key);
    }

    // Read settings from NVS if any exist
    e = esp32_manager_read_from_nvs(&example_namespace);
    if(e == ESP_OK) {
        ESP_LOGD(TAG, "%s namespace entries loaded", example_namespace.key);
    } else {
        ESP_LOGE(TAG, "Error reading entries from namespace %s: %s", example_namespace.key, esp_err_to_name(e));
    }

    e = esp32_manager_network_wifi_start(AUTO);
    if(e == ESP_OK) {
        ESP_LOGD(TAG, "WiFi started");
    } else {
        ESP_LOGE(TAG, "Error starting WiFi: %s", esp_err_to_name(e));
    }

    while(1) {
        ++counter;
        ESP_LOGI(TAG, "Counter: %d, Delay: %d", counter, delay);
        vTaskDelay(delay / portTICK_PERIOD_MS);
    }
}

