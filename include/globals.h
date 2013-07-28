// file: globals.h

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#ifdef __SENSIBLE_MODIFIERS__
#define staticf protected
#define staticv nosave
#else
#define staticf static
#define staticv static
#endif

#include "tests.h"

#define DEB(X) printf(#X ": %O\n", X)

#define SINGLE_DIR              "/single"
#define CONFIG_DIR              "/etc"
#define LOG_DIR                 "/log"
#define VERB_DIR                "/command/verb"
#define DATA_DIR                "/data"
#define PASSWORD_DIR            "/u/passwords"

#define VIRTUAL_D               "/single/virtual"
#define MOVE_D                  "/single/movement"
#define ALIAS_D                 "/single/alias"
#define BIRTH_D                 "/single/birth"
#define LOOK_D                  "/single/look"
#define MESSAGE_D               "/single/messaging"
#define WIZ_D                   "/single/wiz"
#define PICK_D                  "/single/pick"
#define VERB_D                  "/single/verb"

#define LOGIN_OB                "/clone/login"
#define USER_OB                 "/clone/user"
#define USER_TERM               "/clone/user/terminal"
#define VOID_OB                 "/single/void"
#define ROOM_OB                 "/inherit/room"
#define COMMAND_OB              "/inherit/command_queue"
#define COLOR_OB                "/clone/user/color"
#define VERB_OB                 "/inherit/verb"
#define ITEM_OB                 "/inherit/item"
#define EDITOR_OB               "/clone/editor"
#define PAGER_OB                "/clone/pager"

#define ED_HANDLER              "/single/ed-handler"

#define SAVABLE                 "/inherit/savable"

#define START_ROOM              "/domain/wiz/workshop"

#define ROOM_TEMPLATE           "/template/new-room.c"

#define ROOT_UID                "Root"
#define BACKBONE_UID            "Backbone"

#define BASE                    "/inherit/base"
#define OVERRIDES_FILE          "/single/simul_efun"

#define COMMAND_PREFIX          "/command/"
#define USER_PATH               "/command/user"
#define WIZ_PATH                "/command/wizard"

// Seconds delay between autosave calls.
#define SAVE_PERIOD             300

// Number of executions per heartbeat
#define DEFAULT_SPEED           6

// classes for message() efun.
#define M_STATUS                "status"
#define M_SAY                   "say"

#define SUBTLE                  "subtle"
#define LEAVE                   "leave"
#define ARRIVE                  "arrive"

#define CLEAN_UP                "/inherit/clean_up"

#endif
