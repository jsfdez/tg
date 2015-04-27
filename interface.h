/*
    This file is part of telegram-client.

    Telegram-client is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Telegram-client is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this telegram-client.  If not, see <http://www.gnu.org/licenses/>.

    Copyright Vitaly Valtman 2013
*/
#ifndef __INTERFACE_H__
#define __INTERFACE_H__
#include "structures.h"

#ifdef _WIN32
typedef void* HANDLE;
extern int color_normal;
extern HANDLE console_handle;
#define COLOR_RED FOREGROUND_RED
#define COLOR_REDB FOREGROUND_RED + FOREGROUND_INTENSITY
#define COLOR_NORMAL color_normal
#define COLOR_GREEN FOREGROUND_GREEN
#define COLOR_GREY 8
#define COLOR_YELLOW FOREGROUND_RED + FOREGROUND_GREEN
#define COLOR_BLUE FOREGROUND_BLUE
#define COLOR_MAGENTA 14
#define COLOR_CYAN 11
#define COLOR_LCYAN 11

#define COLOR_INVERSE 22
#else
#define COLOR_RED "\033[0;31m"
#define COLOR_REDB "\033[1;31m"
#define COLOR_NORMAL "\033[0m"
#define COLOR_GREEN "\033[32;1m"
#define COLOR_GREY "\033[37;1m"
#define COLOR_YELLOW "\033[33;1m"
#define COLOR_BLUE "\033[34;1m"
#define COLOR_MAGENTA "\033[35;1m"
#define COLOR_CYAN "\033[36;1m"
#define COLOR_LCYAN "\033[0;36m"

#define COLOR_INVERSE "\033[7m"
#endif

char *get_default_prompt (void);
char *complete_none (const char *text, int state);
char **complete_text (char *text, int start, int end);
void interpreter (char *line);

void rprintf (const char *format, ...) __attribute__ ((format (printf, 1, 2)));
void logprintf (const char *format, ...) __attribute__ ((format (printf, 1, 2)));
void hexdump (int *in_ptr, int *in_end);

struct message;
union peer;
void print_message (struct message *M);
void print_chat_name (peer_id_t id, union peer *C);
void print_user_name (peer_id_t id, union peer *U);
void print_encr_chat_name_full (peer_id_t id, peer_t *C);
void print_encr_chat_name (peer_id_t id, peer_t *C);
//void print_media (struct message_media *M);
void pop_color (void);
#ifdef _WIN32
void push_color(int color);
#else
void push_color (const char *color);
#endif
void print_start (void);
void print_end (void);
void print_date_full (long t);
void print_date (long t);

void play_sound (void);
void update_prompt (void);
void set_interface_callbacks (void);
#endif
