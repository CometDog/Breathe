#include "pebble.h"
#include "@smallstoneapps/utils/macros.h"
#include "c/libs/assist.h"
#include "c/windows/breatheWindow.h"
#include "c/config.h"
#include "c/main.h"

static void reset_circle() {
    seconds = 0;
    countdown = 5;
    breaths = 0;
    seconds_per_breath = 0;
    seconds_in = 0;
    radius = 3;
}

static void count_down() {
    countdown--;
    snprintf(s_ready_buffer, sizeof(s_ready_buffer), "ready... %d", countdown);
    if (countdown <= 0) {
        text_layer_set_text(s_ready_text_layer, "");
    }
}

static void check_remaining_time() {
    DEBUG(buf_from_int(seconds));
    DEBUG(buf_from_int(seconds_in));
    DEBUG(buf_from_int(seconds_per_breath));
    if (seconds <= 0 && seconds_in <= 1) {
        window_stack_remove(window_stack_get_top_window(), true);
    }
}

static void draw_circle(Layer *layer, GContext *context) {
    GRect bounds = layer_get_bounds(layer);
    GPoint center = GPoint(bounds.size.w / 2, bounds.size.h / 2);
    
    if (seconds_in == 0 || seconds_in >= seconds_per_breath) {
        seconds_in = 0;
        radius = 3;
        seconds_in++;
    }
    else if (seconds_in <= seconds_per_breath) {
        if (seconds_in <= 5) {
            radius += 15;
            vibes_double_pulse();
        }
        else if (seconds_in > 5 && seconds_in <= 8) {
            radius -= 25;
        }
        if (radius < 0) {
            radius = 3;
        }
        seconds_in++;
    }
    graphics_draw_circle(context, center, radius);
    graphics_fill_circle(context, center, radius);

    check_remaining_time();
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    if (countdown > 0) {
        count_down();
    }
    else {
        seconds--;
        layer_set_update_proc(s_dot_layer, draw_circle);
    }
    layer_mark_dirty(s_dot_layer);
}

static void calc_seconds() {
    int minutes = get_minutes();
    int breaths_per_minute = get_breaths_per_minute();
    countdown = 5;
    seconds = minutes * 60;
    seconds_per_breath = 60 / breaths_per_minute;
}

void breathe_window_load(Window *window) {
    tick_timer_service_subscribe(SECOND_UNIT, tick_handler);

    calc_seconds();

    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    s_dot_layer = layer_create_fullscreen(window);
    s_ready_text_layer = text_layer_create(GRect(0, bounds.size.h / 2, bounds.size.w, 20));
    text_layer_set_colors(s_ready_text_layer, GColorBlack, GColorClear);
    text_layer_set_text_alignment(s_ready_text_layer, GTextAlignmentCenter);
    text_layer_set_system_font(s_ready_text_layer, FONT_KEY_GOTHIC_18_BOLD);
    text_layer_set_text(s_ready_text_layer, s_ready_buffer);
    layer_add_to_layer(s_dot_layer, window_layer);
    text_layer_add_to_layer(s_ready_text_layer, s_dot_layer);
}

void breathe_window_unload(Window *window) {
    tick_timer_service_unsubscribe();

    vibes_short_pulse();
    reset_circle();

    text_layer_destroy_safe(s_ready_text_layer);
    layer_destroy_safe(s_dot_layer);
}