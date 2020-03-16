#ifndef IO_H
#define IO_H

#define TSSM_STDIN_SHARING FILE_SHARE_WRITE
#define TSSM_STDIN_DISPOSITION OPEN_EXISTING
#define TSSM_STDIN_FLAGS FILE_ATTRIBUTE_NORMAL
#define TSSM_STDOUT_SHARING (FILE_SHARE_READ | FILE_SHARE_WRITE)
#define TSSM_STDOUT_DISPOSITION OPEN_ALWAYS
#define TSSM_STDOUT_FLAGS FILE_ATTRIBUTE_NORMAL
#define TSSM_STDERR_SHARING (FILE_SHARE_READ | FILE_SHARE_WRITE)
#define TSSM_STDERR_DISPOSITION OPEN_ALWAYS
#define TSSM_STDERR_FLAGS FILE_ATTRIBUTE_NORMAL

typedef struct {
  TCHAR *service_name;
  TCHAR *path;
  unsigned long sharing;
  unsigned long disposition;
  unsigned long flags;
  HANDLE read_handle;
  HANDLE write_handle;
  __int64 size;
  unsigned long *tid_ptr;
  unsigned long *rotate_online;
  bool timestamp_log;
  __int64 line_length;
  bool copy_and_truncate;
  unsigned long rotate_delay;
} logger_t;

void close_handle(HANDLE *, HANDLE *);
void close_handle(HANDLE *);
int get_createfile_parameters(HKEY, TCHAR *, TCHAR *, unsigned long *, unsigned long, unsigned long *, unsigned long, unsigned long *, unsigned long, bool *);
int set_createfile_parameter(HKEY, TCHAR *, TCHAR *, unsigned long);
int delete_createfile_parameter(HKEY, TCHAR *, TCHAR *);
HANDLE write_to_file(TCHAR *, unsigned long, SECURITY_ATTRIBUTES *, unsigned long, unsigned long);
void rotate_file(TCHAR *, TCHAR *, unsigned long, unsigned long, unsigned long, unsigned long, bool);
int get_output_handles(tssm_service_t *, STARTUPINFO *);
int use_output_handles(tssm_service_t *, STARTUPINFO *);
void close_output_handles(STARTUPINFO *);
void cleanup_loggers(tssm_service_t *);
unsigned long WINAPI log_and_rotate(void *);

#endif
