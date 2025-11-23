#pragma once

#include <MenuManager.h>
#include "ui/screens/ui_WiFiConnect.h"
#include "ui/screens/ui_DebugLogScreen.h"
#include "ui/screens/ui_UserSelectionScreen.h"

class RumpshiftLogger;

class Menus
{
public:
    // MenuManager menus;

    Menus(RumpshiftLogger *logger = nullptr)
        : _logger(logger)
    {
        if (_logger)
            _logger->info("[Menus] Menus object created (LVGL not used yet)");
        // Do NOT call setupMenus() here
    }

    void init() // call this AFTER LVGL is ready
    {
        if (_logger)
            _logger->info("[Menus] Initializing menus now...");
        setupMenus();
    }

private:
    RumpshiftLogger *_logger = nullptr; // moved here + renamed

    void setupMenus()
    {
        // if (_logger)
        //     _logger->info("[Menus] Adding WiFi Connect menu");
        // menus.addMenu("WiFi Connect", ui_WiFiConnect_screen_init);

        // if (_logger)
        //     _logger->info("[Menus] Adding Debug Log menu");
        // menus.addMenu("Debug Log", ui_DebugLog_screen_init);

        // if (_logger)
        //     _logger->info("[Menus] Adding User Selection menu");
        // menus.addMenu("User Selection", ui_UserSelection_screen_init);

        // if (_logger)
        //     _logger->info("[Menus] All menus added successfully");
    }
};
