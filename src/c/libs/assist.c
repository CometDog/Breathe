#include "pebble.h"
#include "@smallstoneapps/utils/macros.h"
#include "assist.h"

char *concat(const char *s1, const char *s2) {
  if (!s1 || !s2) {
    return "Unknown";
  }
  else {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);

    strcpy(result, s1);
    strcat(result, " ");
    strcat(result, s2);

    return result;
  }
}

char *upcase(char *str) {
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 0x20;
        }
    }
    return str;
}

char *buf_from_int(int in) {
  snprintf(buf, sizeof(buf), "%d", in);
  return buf;
}