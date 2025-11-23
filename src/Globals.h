#ifndef GLOBALS_H
#define GLOBALS_H

#include <RumpshiftLogger.h>
#include <Users.h>
#include <NetworkManager.h>
#include <WiFi/WiFiNetworkManager.h>
// #include <WiFi/WiFiClientWrapper.h>
// #include "ui/menus.h"
#include "lvgl.h"
#include "config.h"

// --- Network credentials ---
extern const char *ssid;
extern const char *password;
extern const char *server;
extern const int port;

// --- Global objects ---
// Constructed at global scope only if safe (no LVGL objects)
extern RumpshiftLogger *logger;
extern Users *users;
extern NetworkManager *network;
extern WiFiClientWrapper wifiClient;

// Menus will be created after setup, so use a pointer
// extern Menus *menus;

// --- Global LVGL labels ---
// Keep as pointers; objects created later safely in setup
// struct GlobalLabels
// {
//     lv_obj_t *networkStatusLabel = nullptr;
//     lv_obj_t *menuDisplayLabel = nullptr;
//     // add more labels as needed
// };
// extern GlobalLabels gLabels;

// --- Helpers ---
// lv_obj_t *createGlobalLabel(
//     lv_obj_t *parent,
//     lv_align_t align,
//     int x = 0,
//     int y = 0,
//     const char *text = "",
//     const lv_font_t *font = &lv_font_montserrat_14);

// Only call after LVGL is initialized
// void updateNetworkStatus();

void initGlobalsAfterUI();

#endif
