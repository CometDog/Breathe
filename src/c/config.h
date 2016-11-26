#pragma once

extern char *increase_minutes();
extern char *increase_breaths();
extern int get_minutes();
extern int get_breaths_per_minute();

static int MAX_MINUTES = 9;
static int MAX_BREATHS = 7;

static int minutes = 1 - 1;
static int breaths_per_minute = 4 - 1;

static char *s_minutes_buffer = "X", *s_breaths_buffer = "X";