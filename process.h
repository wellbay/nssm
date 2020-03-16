#ifndef PROCESS_H
#define PROCESS_H

#include <psapi.h>
#include <tlhelp32.h>

typedef struct {
  TCHAR *name;
  HANDLE process_handle;
  unsigned long depth;
  unsigned long pid;
  unsigned long exitcode;
  unsigned long stop_method;
  unsigned long kill_console_delay;
  unsigned long kill_window_delay;
  unsigned long kill_threads_delay;
  SERVICE_STATUS_HANDLE status_handle;
  SERVICE_STATUS *status;
  FILETIME creation_time;
  FILETIME exit_time;
  int signalled;
} kill_t;

typedef int (*walk_function_t)(tssm_service_t *, kill_t *);

HANDLE get_debug_token();
void service_kill_t(tssm_service_t *, kill_t *);
int get_process_creation_time(HANDLE, FILETIME *);
int get_process_exit_time(HANDLE, FILETIME *);
int check_parent(kill_t *, PROCESSENTRY32 *, unsigned long);
int CALLBACK kill_window(HWND, LPARAM);
int kill_threads(tssm_service_t *, kill_t *);
int kill_threads(kill_t *);
int kill_console(tssm_service_t *, kill_t *);
int kill_console(kill_t *);
int kill_process(tssm_service_t *, kill_t *);
int kill_process(kill_t *);
int print_process(tssm_service_t *, kill_t *);
int print_process(kill_t *);
void walk_process_tree(tssm_service_t *, walk_function_t, kill_t *, unsigned long);
void kill_process_tree(kill_t *, unsigned long);

#endif
