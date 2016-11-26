#include "pebble.h"
#include "@smallstoneapps/utils/macros.h"
#include "c/libs/assist.h"
#include "c/windows/configWindow.h"
#include "c/main.h"
#include "c/config.h"

static void push_breathe_window() {
    s_breathe_window = window_create();
    window_handlers(s_breathe_window, breathe_window_load, breathe_window_unload);
    window_stack_push(s_breathe_window, true);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    text_layer_set_text(s_minutes_text_layer, concat(increase_minutes(), "min"));
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    push_breathe_window();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    text_layer_set_text(s_breaths_text_layer, concat(increase_breaths(), "bpm"));
}

void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void config_action_bar_load(Window *window) {
    s_plus_bitmap = gbitmap_create_with_resource(RESOURCE_ID_PLUS_ICON);
    s_check_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CHECK_ICON);

    action_bar_layer_create_in_window(s_action_layer, window);
    action_bar_layer_set_click_config_provider(s_action_layer, click_config_provider);

    action_bar_layer_set_icon(s_action_layer, BUTTON_ID_UP, s_plus_bitmap);
    action_bar_layer_set_icon(s_action_layer, BUTTON_ID_SELECT, s_check_bitmap);
    action_bar_layer_set_icon(s_action_layer, BUTTON_ID_DOWN, s_plus_bitmap);

    s_config_layer = layer_create_fullscreen(window);
}

void config_window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    config_action_bar_load(window);

    s_minutes_text_layer = text_layer_create(GRect(0, bounds.size.h / 8, bounds.size.w - 40, 20));
    s_breaths_text_layer = text_layer_create(GRect(0, (bounds.size.h / 4) * 3, bounds.size.w - 40, 20));
    s_start_text_layer = text_layer_create(GRect(0, (bounds.size.h / 7) * 3, bounds.size.w - 40, 20));

    text_layer_set_colors(s_minutes_text_layer, GColorBlack, GColorClear);
    text_layer_set_colors(s_breaths_text_layer, GColorBlack, GColorClear);
    text_layer_set_colors(s_start_text_layer, GColorBlack, GColorClear);

    text_layer_set_text_alignment(s_minutes_text_layer, GTextAlignmentRight);
    text_layer_set_text_alignment(s_breaths_text_layer, GTextAlignmentRight);
    text_layer_set_text_alignment(s_start_text_layer, GTextAlignmentRight);

    text_layer_set_system_font(s_minutes_text_layer, FONT_KEY_GOTHIC_18_BOLD);
    text_layer_set_system_font(s_breaths_text_layer, FONT_KEY_GOTHIC_18_BOLD);
    text_layer_set_system_font(s_start_text_layer, FONT_KEY_GOTHIC_18_BOLD);

    text_layer_set_text(s_minutes_text_layer, concat(increase_minutes(), "min"));
    text_layer_set_text(s_breaths_text_layer, concat(increase_breaths(), "bpm"));
    text_layer_set_text(s_start_text_layer, "breathe...");

    layer_add_to_layer(s_config_layer, window_layer);
    text_layer_add_to_layer(s_minutes_text_layer, s_config_layer);
    text_layer_add_to_layer(s_breaths_text_layer, s_config_layer);
    text_layer_add_to_layer(s_start_text_layer, s_config_layer);
}

void config_window_unload(Window *window) {
    text_layer_destroy_safe(s_minutes_text_layer);
    text_layer_destroy_safe(s_breaths_text_layer);
    text_layer_destroy_safe(s_start_text_layer);

    layer_destroy_safe(s_config_layer);

    action_bar_layer_destroy_safe(s_action_layer);

    gbitmap_destroy_safe(s_plus_bitmap);
    gbitmap_destroy_safe(s_check_bitmap);
}