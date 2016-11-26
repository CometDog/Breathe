#pragma once

static Layer *s_dot_layer;

static TextLayer *s_ready_text_layer;

static int seconds = 0;
static int countdown = 5;
static int breaths = 0;
static int seconds_per_breath = 0;
static int seconds_in = 0;

static int radius = 3;

static char s_ready_buffer[] = "ready... 5";