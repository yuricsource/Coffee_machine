#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "MqttClient.h"
#include "mqtt_client.h"
#include "Logger.h"

#define MQTT_DEBUG

namespace Protocols
{
using Utilities::Logger;
static const uint8_t *localVariableUri;
static const uint16_t *localVariablePort;
static const uint8_t *localVariableUser;
static const uint8_t *localVariablePassword;


static void log_error_if_nonzero(const char *message, int error_code)
{
#ifdef MQTT_DEBUG
    if (error_code != 0) {
        Logger::LogError(Logger::LogSource::Mqtt, "Last error %s: 0x%x", message, error_code);
    }
#endif
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
#ifdef MQTT_DEBUG
    Logger::LogInfo(Logger::LogSource::Mqtt, "Event dispatched from event loop base=%s, event_id=%" PRIi32 "", base, event_id);
#endif
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
#ifdef MQTT_DEBUG
        Logger::LogInfo(Logger::LogSource::Mqtt, "MQTT_EVENT_CONNECTED");
#endif
        msg_id = esp_mqtt_client_publish(client, "/topic/qos1", "data_3", 0, 1, 0);
#ifdef MQTT_DEBUG
        Logger::LogInfo(Logger::LogSource::Mqtt, "sent publish successful, msg_id=%d", msg_id);
#endif
        msg_id = esp_mqtt_client_subscribe(client, "/topic/qos0", 0);
#ifdef MQTT_DEBUG
        Logger::LogInfo(Logger::LogSource::Mqtt, "sent subscribe successful, msg_id=%d", msg_id);
#endif
        msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
#ifdef MQTT_DEBUG
        Logger::LogInfo(Logger::LogSource::Mqtt, "sent subscribe successful, msg_id=%d", msg_id);
#endif
        msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
#ifdef MQTT_DEBUG
        Logger::LogInfo(Logger::LogSource::Mqtt, "sent unsubscribe successful, msg_id=%d", msg_id);
#endif
        break;
    case MQTT_EVENT_DISCONNECTED:
#ifdef MQTT_DEBUG
        Logger::LogInfo(Logger::LogSource::Mqtt, "MQTT_EVENT_DISCONNECTED");
#endif
        break;

    case MQTT_EVENT_SUBSCRIBED:
#ifdef MQTT_DEBUG
        Logger::LogInfo(Logger::LogSource::Mqtt, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
#endif
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
#ifdef MQTT_DEBUG
        Logger::LogInfo(Logger::LogSource::Mqtt, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
#endif
        break;
    case MQTT_EVENT_PUBLISHED:
#ifdef MQTT_DEBUG
        Logger::LogInfo(Logger::LogSource::Mqtt, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
#endif
        break;
    case MQTT_EVENT_DATA:
#ifdef MQTT_DEBUG
        Logger::LogInfo(Logger::LogSource::Mqtt, "MQTT_EVENT_DATA");
        Logger::LogInfo(Logger::LogSource::Mqtt, "TOPIC=%.*s", event->topic_len, event->topic);
        Logger::LogInfo(Logger::LogSource::Mqtt, "DATA=%.*s", event->data_len, event->data);
#endif
        break;
    case MQTT_EVENT_ERROR:
        Logger::LogInfo(Logger::LogSource::Mqtt, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            Logger::LogError(Logger::LogSource::Mqtt,"Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));

        }
        break;
    default:
        Logger::LogInfo(Logger::LogSource::Mqtt, "Other event id:%d", event->event_id);
        break;
    }
}

void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {};
    mqtt_cfg.broker.address.uri = (const char*)localVariableUri;
    mqtt_cfg.broker.address.port = *localVariablePort;
    mqtt_cfg.credentials.username = (const char*)localVariableUser;
    mqtt_cfg.credentials.authentication.password = (const char*)localVariablePassword;

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, (esp_mqtt_event_id_t)ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);

    const char* configMessage = " { \
    \"name\": \"Coffee Machine\",\
    \"uniq_id\": \"Coffee_Machine\",\
    \"dev\": {\
        \"ids\": \"ecda3bbff2cc0000\",\
        \"name\": \"Coffee Machine\",\
        \"sw\": \"1.0.0\"\
    },\
    \"stat_t\": \"aha/ecda3bbff2cc0000/Coffee_Machine/stat_t\",\
    \"cmd_t\": \"aha/ecda3bbff2cc0000/Coffee_Machine/cmd_t\"\
    }"; 

    // int msg_id = esp_mqtt_client_subscribe(client, "homeassistant/switch/ecda3bbff2cc0000/Coffee Machine/config", 1);
    int msg_id = esp_mqtt_client_subscribe(client, "aha/ecda3bbff2cc0000/Coffee_Machine/stat_t", 1);
    Logger::LogInfo(Logger::LogSource::Mqtt, "sent subscribe successful, msg_id=%d", msg_id);
    msg_id = esp_mqtt_client_subscribe(client, "aha/ecda3bbff2cc0000/Coffee_Machine/cmd_t", 1);
    Logger::LogInfo(Logger::LogSource::Mqtt, "sent subscribe successful, msg_id=%d", msg_id);
    msg_id = esp_mqtt_client_publish(client, "homeassistant/switch/ecda3bbff2cc0000/Coffee Machine/config", configMessage, 0, 0, 0);
    Logger::LogInfo(Logger::LogSource::Mqtt, "sent publish successful, msg_id=%d", msg_id);
}

MqttClient::MqttClient(MqttBrokerAddress brokerAddress, MqttConnectionName name, ConnectionPassword password, uint16_t connectionPort) 
{
    memcpy(_brokerAddress.data(), brokerAddress.data(), _brokerAddress.size());
    memcpy(_connectionName.data(), name.data(), _connectionName.size());
    memcpy(_connectionPassword.data(), password.data(), _connectionPassword.size());
    _connectionPort = connectionPort;

    localVariableUri = _brokerAddress.data();
    localVariablePort = &_connectionPort;
    localVariableUser = _connectionName.data();
    localVariablePassword = _connectionPassword.data();

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());

    mqtt_app_start();
}

} // namespace Protocol