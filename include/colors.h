// The de facto standard colors.  Taken from lima.
// Quoth the mudlib:
//
// Beek - June 20, 1995
// Implements the defacto standard %^ color escapes.  Currently,
// only ANSI is supported, although the extension to other terminal
// types should be trivial.  Ideally, this would interface with
// termcap etc
//
#define RESET "\e[0m"
#define BOLD "\e[1m"
#define FLASH "\e[5m"
#define BLACK "\e[30m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define ORANGE "\e[33m"
#define YELLOW BOLD ORANGE
#define BLUE "\e[34m"
#define CYAN "\e[36m"
#define MAGENTA "\e[35m"
#define WHITE "\e[37m"
#define B_RED "\e[41m"
#define B_GREEN "\e[42m"
#define B_ORANGE "\e[43m"
#define B_YELLOW BOLD B_ORANGE
#define B_BLUE "\e[44m"
#define B_CYAN "\e[46m"
#define B_BLACK "\e[40m"
#define B_WHITE "\e[47m"
#define CLEARLINE "\e[L\e[G"
#define B_MAGENTA "\e[45m"
#define INITTERM "\e[H\e[2J"
#define ENDTERM ""
#define SAVE "\e7"
#define RESTORE "\e8"
#define HOME "\e[H"
