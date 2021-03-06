/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>
#include <xcb/xproto.h>

#define LEN(x) sizeof(x) / sizeof(*x)

/*
 * Applications configuration
 */
#define TERMINAL "st"
#define APPLICATIONS_MENU "dmenu_run"

/*
 * Masks name helpers
 */
#define META_MASK XCB_MOD_MASK_4
#define ALT_MASK XCB_MOD_MASK_1
#define SHIFT_MASK XCB_MOD_MASK_SHIFT
#define CONTROL XCB_MOD_MASK_CONTROL

/*
 * Border attributes 0xRRGGBB
 */
#define BORDER_COLOR 0x6e760f /* inverse color (bar) #170f76 */
#define BORDER_COLOR_UNFOCUS 0x363908
#define BORDER_PIXEL 1

/*
 * Basic events masks to projet.
 * these events only one window can have (the window manager).
 * if a error occurs to set, other window manager are running.
 */

typedef struct {
	xcb_mod_mask_t modifiers;
	int key;
} Keybind;

typedef struct {
	xcb_mod_mask_t modfiers;
	xcb_cursor_t cursor;
} ButtonAction;

typedef struct {
	unsigned int x;
	unsigned int y;
} Pointer;

typedef struct {
	unsigned int x;
	unsigned int y;
} Cord;

typedef struct {
	xcb_drawable_t id;
	int16_t x, y;
	uint16_t width, height;
	int16_t toggle_x, toggle_y;
	uint16_t max_width, max_height, min_width,
		min_height, width_inc, height_inc,
		base_width, base_height;
} Window;

typedef struct {
	int len, max_len;
	Window *window_array;
} Windows;

Windows *init_windows();
Windows *add_window(Window *win);
int find_window(xcb_drawable_t id, Windows *windows);
void remove_window(xcb_drawable_t id, Windows *windows);

int new_process(char *programm);
void key_press_handler(xcb_key_press_event_t *ev);
void map_request_handler(xcb_map_request_event_t *mrev);
void motion_notify_handler(xcb_motion_notify_event_t *mnev);
void configure_request_handler(xcb_configure_request_event_t *crev);
xcb_get_geometry_reply_t *get_geometry(xcb_drawable_t window, bool exit);
xcb_query_pointer_reply_t *query_pointer(xcb_drawable_t window);
xcb_window_t *setup_window(xcb_window_t *window);
