#include "ui_WiFiConnect.h"
#include "lvgl.h"
#include "NetworkManager.h"
#include "Globals.h"

lv_obj_t *ui_WiFiConnectScreen = nullptr;
lv_obj_t *ui_WiFiDropdown = nullptr;
lv_obj_t *ui_ConnectWiFiButton = nullptr;
lv_obj_t *ui_SelectSSIDLabel = nullptr;
lv_obj_t *ui_WiFiStatusLabel = nullptr;

void ui_WiFiConnect_screen_init(void)
{
    ui_WiFiConnectScreen = lv_obj_create(NULL); // create a new screen

    // Label for SSID selection
    ui_SelectSSIDLabel = lv_label_create(ui_WiFiConnectScreen);
    lv_label_set_text(ui_SelectSSIDLabel, "Select WiFi:");
    lv_obj_align(ui_SelectSSIDLabel, LV_ALIGN_TOP_MID, 0, 10);

    // Dropdown for networks
    ui_WiFiDropdown = lv_dropdown_create(ui_WiFiConnectScreen);
    lv_obj_set_width(ui_WiFiDropdown, 200);
    lv_obj_align(ui_WiFiDropdown, LV_ALIGN_TOP_MID, 0, 50);
    lv_obj_add_event_cb(ui_WiFiDropdown, ui_event_wifi_dropdown, LV_EVENT_VALUE_CHANGED, NULL);

    // Connect button
    ui_ConnectWiFiButton = lv_btn_create(ui_WiFiConnectScreen);
    lv_obj_align(ui_ConnectWiFiButton, LV_ALIGN_BOTTOM_MID, 0, -50);
    lv_obj_add_event_cb(ui_ConnectWiFiButton, ui_event_ConnectWiFiButton, LV_EVENT_CLICKED, NULL);
    lv_obj_t *label = lv_label_create(ui_ConnectWiFiButton);
    lv_label_set_text(label, "Connect");

    // Status label
    ui_WiFiStatusLabel = lv_label_create(ui_WiFiConnectScreen);
    lv_label_set_text(ui_WiFiStatusLabel, "Status: Idle");
    lv_obj_align(ui_WiFiStatusLabel, LV_ALIGN_BOTTOM_MID, 0, -10);

    // Populate dropdown with scanned networks
    if (network)
    {
        // network->scanNetworks(); // fills logger with network info
        lv_dropdown_clear_options(ui_WiFiDropdown);
        int n = WiFi.scanNetworks();
        for (int i = 0; i < n; i++)
        {
            String ssid = WiFi.SSID(i);
            lv_dropdown_add_option(ui_WiFiDropdown, ssid.c_str(), LV_DROPDOWN_POS_LAST);
        }
    }

    lv_scr_load(ui_WiFiConnectScreen);
}

void ui_WiFiConnect_screen_destroy(void)
{
    if (ui_WiFiConnectScreen)
        lv_obj_del(ui_WiFiConnectScreen);
    ui_WiFiConnectScreen = nullptr;
}

void ui_event_wifi_dropdown(lv_event_t *e)
{
    lv_obj_t *dd = (lv_obj_t *)lv_event_get_target(e); // cast void* -> lv_obj_t*

    char buf[64]; // buffer to receive selected string
    lv_dropdown_get_selected_str(dd, buf, sizeof(buf));

    if (ui_WiFiStatusLabel)
    {
        lv_label_set_text_fmt(ui_WiFiStatusLabel, "Selected: %s", buf);
    }
}

void ui_event_ConnectWiFiButton(lv_event_t *e)
{
    if (!ui_WiFiDropdown)
        return;

    char ssid[64]; // buffer for selected SSID
    lv_dropdown_get_selected_str(ui_WiFiDropdown, ssid, sizeof(ssid));

    if (strlen(ssid) == 0)
        return;

    if (ui_WiFiStatusLabel)
        lv_label_set_text(ui_WiFiStatusLabel, "Connecting...");

    logger.info(String("[WiFiScreen] Connecting to: ") + ssid);

    network->begin();       // assumes _ssid/_password already set; TODO: extend to ask for password
    network->printStatus(); // print all network info to logger

    if (ui_WiFiStatusLabel)
    {
        lv_label_set_text_fmt(ui_WiFiStatusLabel, "Status: %s",
                              WiFi.status() == WL_CONNECTED ? "Connected" : "Failed");
    }
}
