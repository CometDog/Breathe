#include "pebble.h"
#include "@smallstoneapps/utils/macros.h"
#include "c/libs/assist.h"
#include "c/config.h"

static char *update_counters(char *buffer, char *printAs, int type) {
  snprintf(buffer, sizeof(buffer), printAs, type);
  return buffer;
}

char *increase_minutes() {
  if (minutes != MAX_MINUTES) {
    minutes += 1;
    s_minutes_buffer = update_counters("s_minutes_buffer", "%d", minutes);
  }
  return s_minutes_buffer;
}

char *increase_breaths() {
  if (breaths_per_minute != MAX_BREATHS) {
    breaths_per_minute += 1;
    s_breaths_buffer = update_counters("s_breaths_buffer", "%d", breaths_per_minute);
  }
  return s_breaths_buffer;
}

int get_minutes() {
  return minutes;
}

int get_breaths_per_minute() {
  return breaths_per_minute;
}