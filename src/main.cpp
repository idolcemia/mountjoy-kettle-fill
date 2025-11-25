/*
 * Mountjoy Kettle fill / Temp gauge using the following components:
 * Arduino Giga R1 M7
 * Giga Display Shield (800 x 480)
 * LvGL 9.x
 * 20251125 tested good.
 * Enhanced with WiFi debug, retries, RSSI, MAC, and encryption info
 */

#include <Arduino.h>
#include "mbed_error.h"

#include <lv_conf.h>
#include <lvgl.h>

#include "Arduino_H7_Video.h"
#include "Arduino_GigaDisplayTouch.h"
#include "ui/ui.h"

// --- Internal libs ---
// #include <HttpResponse.h>
// #include <Diagnostic.h>

#include "config.h"
// #include "Globals.h"

Arduino_H7_Video Display(800, 480, GigaDisplayShield);
Arduino_GigaDisplayTouch TouchDetector;

void _getUsers();
void _log();

// void lvglLogCallback(lv_log_level_t level, const char *buf)
// {
//     Serial.print("[LVGL] ");
//     Serial.println(buf);
// }

void setup()
{
    // HAL_Init();
    // SDRAM_Init();

    Serial.begin(BAUD_RATE);
    while (!Serial)
    {
        delay(10);
    }

    delay(300);
    Serial.println("GIGA alive!");

    delay(2000);

    // logger->begin();
    // logger->info("Starting log....");

    // network->setRemote(server, port);
    // network->begin();
    // network->printStatus();

    // wifiClient.begin(&logger);
    // users = new Users(wifiClient, &logger);
    // _getUsers();

    Display.begin();
    TouchDetector.begin();

    // lv_init();
    // lv_log_register_print_cb(lvglLogCallback);
    // ui_init();

    // initGlobalsAfterUI();
}

void loop()
{
    // lv_timer_handler();

    // Only update once LVGL is stable
    if (millis() > 3000) // wait 3s after boot
    {
        // Diagnostic::updateDefault();
    }

    delay(16);
}

void _log()
{
    // StaticJsonDocument<512> doc;

    // // Database ID
    // // doc["database_id"] = DB_ID;

    // // Title property
    // doc["Entry"] = "Log Entry 1";

    // // Number property
    // doc["Temperature (C)"] = 23.5;

    // // Timestamp property (Notion date)
    // // char timestampStr[25];
    // // unsigned long now = millis() / 1000;
    // // snprintf(timestampStr, sizeof(timestampStr), "2025-10-30T21:%02lu:00Z", (now / 60) % 60);

    // // doc["Timestamp"] = timestampStr;

    // // Serialize JSON
    // String output;
    // serializeJson(doc, output);

    // // POST
    // const char *host = "3.136.200.179";
    // const int port = 8000;
    // const char *url = API_PATH;
    // logger->info("[HTTP_LOG] " + output);

    // HttpResponse resp = wifiClient.http().post(host, port, url, output);
    // logger->info("[POST RESPONSE - FULL] " + resp.full());
}

void _getUsers()
{
    // const char *host = "3.136.200.179";
    // const int port = 8888;
    // const char *url = "/notion-api/integrations/notion/consoleIntegration/users?include=name,id&excludeNames=Mountjoy+Sparkling,Ritual+Coffee+Roasters,n2y+integration,Console,Product+Management";

    // // HttpResponse resp = wifiClient.http().get(host, port, url);
    // // logger->info("[RESPONSE - BODY] " + resp.body());

    // HttpResponse resp = users->fetch(host, port, url);
    // logger->info("[RESPONSE - BODY] " + resp.body());
    // users->parse(resp.body());
    // users->printUsers();
}

extern "C" void mbed_error_hook(const mbed_error_ctx *ctx)
{
    Serial.println(">>> MBED HARDFAULT <<<");

    if (ctx)
    {
        Serial.print("error_status = 0x");
        Serial.println(ctx->error_status, HEX);

        Serial.print("error_value  = 0x");
        Serial.println(ctx->error_value, HEX);

        // Serial.print("info         = 0x");
        // Serial.println(ctx->info, HEX);

        // Serial.print("location     = 0x");
        // Serial.println(ctx->location, HEX);

        // Serial.print("caller       = 0x");
        // Serial.println(ctx->caller, HEX);
    }

    while (1)
    {
    }
}
