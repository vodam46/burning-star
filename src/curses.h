#if defined(__CYGWIN__)
#include <ncurses/ncurses.h>
#elif defined(unix)
#include <ncurses.h>
#else
#error "Unknown platform"
#endif
