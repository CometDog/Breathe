#pragma once

extern char *concat(const char *s1, const char *s2);
extern char *upcase(char *str);
extern char *buf_from_int(int in);

//Window
#define window_mark_dirty(window) layer_mark_dirty(window_get_root_layer(window))
#define window_handlers(window, value1, value2) window_set_window_handlers(window, (WindowHandlers) { .load = value1, .unload = value2})


//Layers
#define layer_add_to_layer(layer1, layer2) layer_add_child(layer2, layer1)

//TextLayers
#define text_layer_add_to_layer(textLayer, layer) layer_add_child(layer, text_layer_get_layer(textLayer))
#define text_layer_mark_dirty(textLayer) layer_mark_dirty(text_layer_get_layer(textLayer))

static char buf[32];