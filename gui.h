#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <windows.h>
#include <commctrl.h>
#include "resource.h"

int tssm_gui(int, tssm_service_t *);
void centre_window(HWND);
int configure(HWND, tssm_service_t *, tssm_service_t *);
int install(HWND);
int remove(HWND);
int edit(HWND, tssm_service_t *);
void browse(HWND);
INT_PTR CALLBACK tssm_dlg(HWND, UINT, WPARAM, LPARAM);

#endif
