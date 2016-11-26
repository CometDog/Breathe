#pragma once

extern void breathe_window_load(Window *window);
extern void breathe_window_unload(Window *window);

extern void click_config_provider(void *context);
extern void config_window_load(Window *window);
extern void config_window_unload(Window *window);

static Window *s_config_window;
static Window *s_breathe_window;