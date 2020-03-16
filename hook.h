#ifndef HOOK_H
#define HOOK_H

#define TSSM_HOOK_EVENT_START _T("Start")
#define TSSM_HOOK_EVENT_STOP _T("Stop")
#define TSSM_HOOK_EVENT_EXIT _T("Exit")
#define TSSM_HOOK_EVENT_POWER _T("Power")
#define TSSM_HOOK_EVENT_ROTATE _T("Rotate")

#define TSSM_HOOK_ACTION_PRE _T("Pre")
#define TSSM_HOOK_ACTION_POST _T("Post")
#define TSSM_HOOK_ACTION_CHANGE _T("Change")
#define TSSM_HOOK_ACTION_RESUME _T("Resume")

/* Hook name will be "<service> (<event>/<action>)" */
#define HOOK_NAME_LENGTH SERVICE_NAME_LENGTH * 2

#define TSSM_HOOK_VERSION 1

/* Hook ran successfully. */
#define TSSM_HOOK_STATUS_SUCCESS 0
/* No hook configured. */
#define TSSM_HOOK_STATUS_NOTFOUND 1
/* Hook requested abort. */
#define TSSM_HOOK_STATUS_ABORT 99
/* Internal error launching hook. */
#define TSSM_HOOK_STATUS_ERROR 100
/* Hook was not run. */
#define TSSM_HOOK_STATUS_NOTRUN 101
/* Hook timed out. */
#define TSSM_HOOK_STATUS_TIMEOUT 102
/* Hook returned non-zero. */
#define TSSM_HOOK_STATUS_FAILED 111

/* Version 1. */
#define TSSM_HOOK_ENV_VERSION _T("TSSM_HOOK_VERSION")
#define TSSM_HOOK_ENV_IMAGE_PATH _T("TSSM_EXE")
#define TSSM_HOOK_ENV_TSSM_CONFIGURATION _T("TSSM_CONFIGURATION")
#define TSSM_HOOK_ENV_TSSM_VERSION _T("TSSM_VERSION")
#define TSSM_HOOK_ENV_BUILD_DATE _T("TSSM_BUILD_DATE")
#define TSSM_HOOK_ENV_PID _T("TSSM_PID")
#define TSSM_HOOK_ENV_DEADLINE _T("TSSM_DEADLINE")
#define TSSM_HOOK_ENV_SERVICE_NAME _T("TSSM_SERVICE_NAME")
#define TSSM_HOOK_ENV_SERVICE_DISPLAYNAME _T("TSSM_SERVICE_DISPLAYNAME")
#define TSSM_HOOK_ENV_COMMAND_LINE _T("TSSM_COMMAND_LINE")
#define TSSM_HOOK_ENV_APPLICATION_PID _T("TSSM_APPLICATION_PID")
#define TSSM_HOOK_ENV_EVENT _T("TSSM_EVENT")
#define TSSM_HOOK_ENV_ACTION _T("TSSM_ACTION")
#define TSSM_HOOK_ENV_TRIGGER _T("TSSM_TRIGGER")
#define TSSM_HOOK_ENV_LAST_CONTROL _T("TSSM_LAST_CONTROL")
#define TSSM_HOOK_ENV_START_REQUESTED_COUNT _T("TSSM_START_REQUESTED_COUNT")
#define TSSM_HOOK_ENV_START_COUNT _T("TSSM_START_COUNT")
#define TSSM_HOOK_ENV_THROTTLE_COUNT _T("TSSM_THROTTLE_COUNT")
#define TSSM_HOOK_ENV_EXIT_COUNT _T("TSSM_EXIT_COUNT")
#define TSSM_HOOK_ENV_EXITCODE _T("TSSM_EXITCODE")
#define TSSM_HOOK_ENV_RUNTIME _T("TSSM_RUNTIME")
#define TSSM_HOOK_ENV_APPLICATION_RUNTIME _T("TSSM_APPLICATION_RUNTIME")

typedef struct {
  TCHAR name[HOOK_NAME_LENGTH];
  HANDLE thread_handle;
} hook_thread_data_t;

typedef struct {
  hook_thread_data_t *data;
  int num_threads;
} hook_thread_t;

bool valid_hook_name(const TCHAR *, const TCHAR *, bool);
void await_hook_threads(hook_thread_t *, SERVICE_STATUS_HANDLE, SERVICE_STATUS *, unsigned long);
int tssm_hook(hook_thread_t *, tssm_service_t *, TCHAR *, TCHAR *, unsigned long *, unsigned long, bool);
int tssm_hook(hook_thread_t *, tssm_service_t *, TCHAR *, TCHAR *, unsigned long *, unsigned long);
int tssm_hook(hook_thread_t *, tssm_service_t *, TCHAR *, TCHAR *, unsigned long *);

#endif
