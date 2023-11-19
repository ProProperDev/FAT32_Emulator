#pragma once

#include <stdio.h>

#include "input_processing.h"

static const char* default_backgr_color = "\033[0m";   // Прозрачный фон
static const char* backgr_color = "\033[40m";         // Чёрный фон
static const char* filename_color = "\033[92m";        // Зелёный текст
static const char* dirname_color = "\033[94m";         // Синий текст

void print_dirname(const char dirname[]);

void print_filename(const char filename[]);

int print_help(const char* params[]);

