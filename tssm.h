#ifndef TSSM_H
#define TSSM_H

/*
  MSDN says, basically, that the maximum length of a path is 260 characters,
  which is represented by the constant MAX_PATH.  Except when it isn't.

  The maximum length of a directory path is MAX_PATH - 12 because it must be
  possible to create a file in 8.3 format under any valid directory.

  Unicode versions of filesystem API functions accept paths up to 32767
  characters if the first four (wide) characters are L"\\?\" and each component
  of the path, separated by L"\", does not exceed the value of
  lpMaximumComponentLength returned by GetVolumeInformation(), which is
  probably 255.  But might not be.

  Relative paths are always limited to MAX_PATH because the L"\\?\" prefix
  is not valid for a relative path.

  Note that we don't care about the last two paragraphs because we're only
  concerned with allocating buffers big enough to store valid paths.  If the
  user tries to store invalid paths they will fit in the buffers but the
  application will fail.  The reason for the failure will end up in the
  event log and the user will realise the mistake.

  So that's that cleared up, then.
*/
#ifdef UNICODE
#define PATH_LENGTH 32767
#else
#define PATH_LENGTH MAX_PATH
#endif
#define DIR_LENGTH PATH_LENGTH - 12

#define _WIN32_WINNT 0x0500

#define APSTUDIO_HIDDEN_SYMBOLS
#include <windows.h>
#include <prsht.h>
#undef APSTUDIO_HIDDEN_SYMBOLS
#include <commctrl.h>
#include <tchar.h>
#ifndef TSSM_COMPILE_RC
#include <fcntl.h>
#include <io.h>
#include <shlwapi.h>
#include <stdarg.h>
#include <stdio.h>
#include "utf8.h"
#include "service.h"
#include "account.h"
#include "console.h"
#include "env.h"
#include "event.h"
#include "hook.h"
#include "imports.h"
#include "messages.h"
#include "process.h"
#include "registry.h"
#include "settings.h"
#include "io.h"
#include "gui.h"
#endif

void tssm_exit(int);
int str_equiv(const TCHAR *, const TCHAR *);
int quote(const TCHAR *, TCHAR *, size_t);
void strip_basename(TCHAR *);
int str_number(const TCHAR *, unsigned long *, TCHAR **);
int str_number(const TCHAR *, unsigned long *);
int num_cpus();
int usage(int);
const TCHAR *tssm_unquoted_imagepath();
const TCHAR *tssm_imagepath();
const TCHAR *tssm_exe();

#define TSSM _T("TSSM")
#ifdef _WIN64
#define TSSM_ARCHITECTURE _T("64-bit")
#else
#define TSSM_ARCHITECTURE _T("32-bit")
#endif
#ifdef _DEBUG
#define TSSM_DEBUG _T(" debug")
#else
#define TSSM_DEBUG _T("")
#endif
#define TSSM_CONFIGURATION TSSM_ARCHITECTURE TSSM_DEBUG
#include "version.h"

/*
  Throttle the restart of the service if it stops before this many
  milliseconds have elapsed since startup.  Override in registry.
*/
#define TSSM_RESET_THROTTLE_RESTART 1500

/*
  How many milliseconds to wait for the application to die after sending
  a Control-C event to its console.  Override in registry.
*/
#define TSSM_KILL_CONSOLE_GRACE_PERIOD 1500
/*
  How many milliseconds to wait for the application to die after posting to
  its windows' message queues.  Override in registry.
*/
#define TSSM_KILL_WINDOW_GRACE_PERIOD 1500
/*
  How many milliseconds to wait for the application to die after posting to
  its threads' message queues.  Override in registry.
*/
#define TSSM_KILL_THREADS_GRACE_PERIOD 1500

/* How many milliseconds to pause after rotating logs. */
#define TSSM_ROTATE_DELAY 0

/* Margin of error for service status wait hints in milliseconds. */
#define TSSM_WAITHINT_MARGIN 2000

/* Methods used to try to stop the application. */
#define TSSM_STOP_METHOD_CONSOLE (1 << 0)
#define TSSM_STOP_METHOD_WINDOW (1 << 1)
#define TSSM_STOP_METHOD_THREADS (1 << 2)
#define TSSM_STOP_METHOD_TERMINATE (1 << 3)

/* Startup types. */
#define TSSM_STARTUP_AUTOMATIC 0
#define TSSM_STARTUP_DELAYED 1
#define TSSM_STARTUP_MANUAL 2
#define TSSM_STARTUP_DISABLED 3

/* Exit actions. */
#define TSSM_EXIT_RESTART 0
#define TSSM_EXIT_IGNORE 1
#define TSSM_EXIT_REALLY 2
#define TSSM_EXIT_UNCLEAN 3
#define TSSM_NUM_EXIT_ACTIONS 4

/* Process priority. */
#define TSSM_REALTIME_PRIORITY 0
#define TSSM_HIGH_PRIORITY 1
#define TSSM_ABOVE_NORMAL_PRIORITY 2
#define TSSM_NORMAL_PRIORITY 3
#define TSSM_BELOW_NORMAL_PRIORITY 4
#define TSSM_IDLE_PRIORITY 5

/* How many milliseconds to wait before updating service status. */
#define TSSM_SERVICE_STATUS_DEADLINE 20000

/* User-defined service controls can be in the range 128-255. */
#define TSSM_SERVICE_CONTROL_START 0
#define TSSM_SERVICE_CONTROL_ROTATE 128

/* How many milliseconds to wait for a hook. */
#define TSSM_HOOK_DEADLINE 60000

/* How many milliseconds to wait for outstanding hooks. */
#define TSSM_HOOK_THREAD_DEADLINE 80000

/* How many milliseconds to wait for closing logging thread. */
#define TSSM_CLEANUP_LOGGERS_DEADLINE 1500

#endif
