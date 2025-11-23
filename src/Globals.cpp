#include "Globals.h"

// Network credentials
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASS;
const char *server = LAN_IP;
const int port = 8000;

// Global objects
RumpshiftLogger *logger = nullptr;
Users *users = nullptr;
NetworkManager *network = nullptr;
// NetworkManager *network =
//     new WiFiNetworkManager(
//         ssid,
//         password,
//         WiFiImpl::ARDUINO_WIFI,
//         &logger);
WiFiClientWrapper wifiClient;

// Menus is a pointer; only create after LVGL & UI init
// Menus *menus = nullptr;

// Global labels
// GlobalLabels gLabels;

// // --- Helper: create a global label ---
// lv_obj_t *createGlobalLabel(
//     lv_obj_t *parent,
//     lv_align_t align,
//     int x,
//     int y,
//     const char *text,
//     const lv_font_t *font)
// {
//     if (!parent)
//         return nullptr; // Safety check
//     lv_obj_t *lbl = lv_label_create(parent);
//     lv_label_set_text(lbl, text);
//     lv_obj_set_style_text_font(lbl, font, LV_PART_MAIN | LV_STATE_DEFAULT);
//     lv_obj_align(lbl, align, x, y);
//     return lbl;
// }

// // --- Helper: update network status label ---
// void updateNetworkStatus()
// {
//     if (!gLabels.networkStatusLabel)
//         return;

//     if (network && network->isConnected())
//     {
//         lv_label_set_text(gLabels.networkStatusLabel, "Network: Connected");
//         lv_obj_set_style_text_color(gLabels.networkStatusLabel, lv_color_hex(0x00FF00),
//                                     LV_PART_MAIN | LV_STATE_DEFAULT);
//     }
//     else
//     {
//         lv_label_set_text(gLabels.networkStatusLabel, "Network: Disconnected");
//         lv_obj_set_style_text_color(gLabels.networkStatusLabel, lv_color_hex(0xFF0000),
//                                     LV_PART_MAIN | LV_STATE_DEFAULT);
//     }
// }

void initGlobals()
{
    logger = new RumpshiftLogger(BAUD_RATE, DEBUG_LEVEL, true);

    network = new WiFiNetworkManager(
        ssid,
        password,
        WiFiImpl::ARDUINO_WIFI,
        logger);
}

// --- Initialize LVGL-dependent globals ---
void initGlobalsAfterUI()
{
    // Instantiate menus only after LVGL is initialized
    // if (!menus) {
    //     menus = new Menus(&logger);
    //     menus->init();
    // }

    // Create any global labels if needed
    // Example:
    // gLabels.networkStatusLabel = createGlobalLabel(lv_scr_act(), LV_ALIGN_TOP_LEFT, 10, 10, "Network: ...");
}
