#include <stdint.h>
#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>
#include <xcb/xproto.h>

#define LEN(x) sizeof(x) / sizeof(*x)
#define TERMINAL "st"
#define APPLICATIONS_MENU "dmenu_run"

#define META_MASK XCB_MOD_MASK_4
#define ALT_MASK XCB_MOD_MASK_1
#define SHIFT_MASK XCB_MOD_MASK_SHIFT
#define CONTROL XCB_MOD_MASK_CONTROL

/*
 * Border attributes 0xRRGGBB
 */
#define BORDER_COLOR 0xFFFFFF
#define BORDER_PIXEL 1

/*
 * !TODO move to a singleton struct
 */
int run;
unsigned short window_width, window_height;
xcb_connection_t *con;
xcb_screen_iterator_t screen;
xcb_window_t window;
xcb_generic_event_t *ev;
xcb_key_symbols_t *keysyms;

/*
 * Basic events masks to projet.
 * these events only one window can have (the window manager).
 * if a error occurs to set, other window manager are running.
 */
uint32_t masks[] = {
    XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT | XCB_EVENT_MASK_STRUCTURE_NOTIFY |
    XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | XCB_EVENT_MASK_PROPERTY_CHANGE
};

struct Keybind {
  xcb_mod_mask_t modifiers;
  xcb_keycode_t *key;
} Keybind;

int new_process(char *programm);
void key_press_handler(xcb_key_press_event_t *ev);
void map_request_handler(xcb_map_request_event_t *mrev);
