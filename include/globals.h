// file: globals.h

#ifdef __SENSIBLE_MODIFIERS__
#define staticf protected
#define staticv nosave
#else
#define staticf static
#define staticv static
#endif

#include "tests.h"

#define SINGLE_DIR "/single"
#define CONFIG_DIR "/etc"
#define LOG_DIR    "/log"

#define VIRTUAL_D  "/single/virtual"
#define MOVE_D     "/single/movement"
#define ALIAS_D    "/single/alias"
#define LOOK_D    "/single/look"

#define LOGIN_OB   "/clone/login"
#define USER_OB    "/clone/user"
#define USER_TERM  "/clone/user/terminal"
#define VOID_OB    "/single/void"
#define ROOM_OB    "/inherit/room"
#define COLOR_OB   "/clone/user/color"

#define START_ROOM "/domain/wiz/workshop"

#define ROOT_UID     "Root"
#define BACKBONE_UID "Backbone"

#define BASE            "/inherit/base"
#define OVERRIDES_FILE  "/single/simul_efun"

#define COMMAND_PREFIX "/command/"

// Seconds delay between autosave calls.
#define SAVE_PERIOD 300

// classes for message() efun.
#define M_STATUS "status"
#define M_SAY    "say"

#define CLEAN_UP "/inherit/clean_up"
