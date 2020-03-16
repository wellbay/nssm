#ifndef REGISTRY_H
#define REGISTRY_H

#define TSSM_REGISTRY _T("SYSTEM\\CurrentControlSet\\Services\\%s")
#define TSSM_REG_PARAMETERS _T("Parameters")
#define TSSM_REGISTRY_GROUPS _T("SYSTEM\\CurrentControlSet\\Control\\ServiceGroupOrder")
#define TSSM_REG_GROUPS _T("List")
#define TSSM_REG_EXE _T("Application")
#define TSSM_REG_FLAGS _T("AppParameters")
#define TSSM_REG_DIR _T("AppDirectory")
#define TSSM_REG_ENV _T("AppEnvironment")
#define TSSM_REG_ENV_EXTRA _T("AppEnvironmentExtra")
#define TSSM_REG_EXIT _T("AppExit")
#define TSSM_REG_RESTART_DELAY _T("AppRestartDelay")
#define TSSM_REG_THROTTLE _T("AppThrottle")
#define TSSM_REG_STOP_METHOD_SKIP _T("AppStopMethodSkip")
#define TSSM_REG_KILL_CONSOLE_GRACE_PERIOD _T("AppStopMethodConsole")
#define TSSM_REG_KILL_WINDOW_GRACE_PERIOD _T("AppStopMethodWindow")
#define TSSM_REG_KILL_THREADS_GRACE_PERIOD _T("AppStopMethodThreads")
#define TSSM_REG_KILL_PROCESS_TREE _T("AppKillProcessTree")
#define TSSM_REG_STDIN _T("AppStdin")
#define TSSM_REG_STDOUT _T("AppStdout")
#define TSSM_REG_STDERR _T("AppStderr")
#define TSSM_REG_STDIO_SHARING _T("ShareMode")
#define TSSM_REG_STDIO_DISPOSITION _T("CreationDisposition")
#define TSSM_REG_STDIO_FLAGS _T("FlagsAndAttributes")
#define TSSM_REG_STDIO_COPY_AND_TRUNCATE _T("CopyAndTruncate")
#define TSSM_REG_HOOK_SHARE_OUTPUT_HANDLES _T("AppRedirectHook")
#define TSSM_REG_ROTATE _T("AppRotateFiles")
#define TSSM_REG_ROTATE_ONLINE _T("AppRotateOnline")
#define TSSM_REG_ROTATE_SECONDS _T("AppRotateSeconds")
#define TSSM_REG_ROTATE_BYTES_LOW _T("AppRotateBytes")
#define TSSM_REG_ROTATE_BYTES_HIGH _T("AppRotateBytesHigh")
#define TSSM_REG_ROTATE_DELAY _T("AppRotateDelay")
#define TSSM_REG_TIMESTAMP_LOG _T("AppTimestampLog")
#define TSSM_REG_PRIORITY _T("AppPriority")
#define TSSM_REG_AFFINITY _T("AppAffinity")
#define TSSM_REG_NO_CONSOLE _T("AppNoConsole")
#define TSSM_REG_HOOK _T("AppEvents")
#define TSSM_STDIO_LENGTH 29

HKEY open_service_registry(const TCHAR *, REGSAM sam, bool);
long open_registry(const TCHAR *, const TCHAR *, REGSAM sam, HKEY *, bool);
HKEY open_registry(const TCHAR *, const TCHAR *, REGSAM sam, bool);
HKEY open_registry(const TCHAR *, const TCHAR *, REGSAM sam);
HKEY open_registry(const TCHAR *, REGSAM sam);
long enumerate_registry_values(HKEY, unsigned long *, TCHAR *, unsigned long);
int create_messages();
int create_parameters(tssm_service_t *, bool);
int create_exit_action(TCHAR *, const TCHAR *, bool);
int get_environment(TCHAR *, HKEY, TCHAR *, TCHAR **, unsigned long *);
int get_string(HKEY, TCHAR *, TCHAR *, unsigned long, bool, bool, bool);
int get_string(HKEY, TCHAR *, TCHAR *, unsigned long, bool);
int expand_parameter(HKEY, TCHAR *, TCHAR *, unsigned long, bool, bool);
int expand_parameter(HKEY, TCHAR *, TCHAR *, unsigned long, bool);
int set_string(HKEY, TCHAR *, TCHAR *, bool);
int set_string(HKEY, TCHAR *, TCHAR *);
int set_expand_string(HKEY, TCHAR *, TCHAR *);
int set_number(HKEY, TCHAR *, unsigned long);
int get_number(HKEY, TCHAR *, unsigned long *, bool);
int get_number(HKEY, TCHAR *, unsigned long *);
int format_double_null(TCHAR *, unsigned long, TCHAR **, unsigned long *);
int unformat_double_null(TCHAR *, unsigned long, TCHAR **, unsigned long *);
int copy_double_null(TCHAR *, unsigned long, TCHAR **);
int append_to_double_null(TCHAR *, unsigned long, TCHAR **, unsigned long *, TCHAR *, size_t, bool);
int remove_from_double_null(TCHAR *, unsigned long, TCHAR **, unsigned long *, TCHAR *, size_t, bool);
void override_milliseconds(TCHAR *, HKEY, TCHAR *, unsigned long *, unsigned long, unsigned long);
int get_io_parameters(tssm_service_t *, HKEY);
int get_parameters(tssm_service_t *, STARTUPINFO *);
int get_exit_action(const TCHAR *, unsigned long *, TCHAR *, bool *);
int set_hook(const TCHAR *, const TCHAR *, const TCHAR *, TCHAR *);
int get_hook(const TCHAR *, const TCHAR *, const TCHAR *, TCHAR *, unsigned long);

#endif
