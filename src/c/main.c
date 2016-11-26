#include "pebble.h"
#include "@smallstoneapps/utils/macros.h"
#include "c/libs/assist.h"
#include "c/main.h"
#include "c/windows/configWindow.h"

static void init() {
    s_config_window = window_create();
    window_set_click_config_provider(s_config_window, click_config_provider);
    window_handlers(s_config_window, config_window_load, config_window_unload);
    window_stack_push(s_config_window, true);
}

static void deinit() {
  window_destroy_safe(s_breathe_window);
  window_destroy_safe(s_config_window);
}

int main() {
    init();

    APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", s_config_window);

    app_event_loop();
    deinit();
}
