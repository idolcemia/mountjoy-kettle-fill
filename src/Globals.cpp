#include "Globals.h"

// Network credentials
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASS;
const char *server = LAN_IP;
const int port = 8000;

// Global objects
RumpshiftLogger logger(BAUD_RATE, DEBUG_LEVEL, true);
Users *users = nullptr;
NetworkManager *network =
    new WiFiNetworkManager(
        ssid,
        password,
        WiFiImpl::ARDUINO_WIFI,
        &logger);
WiFiClientWrapper wifiClient;
MenuManager menuManager;

// Global labels
GlobalLabels gLabels;

void initGlobals()
{
    initMenus();
}

void initMenus()
{
    menuManager.setLogger(&logger);
    menuManager.addMenu("Menu Selection", ui_MenuSelection_screen_init, ui_MenuSelection_screen_destroy);
    menuManager.addMenu("WiFi Connect", ui_WiFiConnect_screen_init, ui_WiFiConnect_screen_destroy);
    menuManager.addMenu("Debug Log", ui_DebugLog_screen_init, ui_DebugLog_screen_destroy);
    menuManager.addMenu("User Selection", ui_UserSelection_screen_init, ui_UserSelection_screen_destroy);
}