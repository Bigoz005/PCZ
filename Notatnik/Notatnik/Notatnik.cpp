// Notatnik.cpp : Definiuje punkt wejścia dla aplikacji.
//

#include "stdafx.h"
#include "Notatnik.h"
#include <CommCtrl.h>
#include <CommDlg.h>
#include "resource.h"
#include "resource1.h"
#include <windows.h>

#define MAX_LOADSTRING 100


// Zmienne globalne:
HWND hWnd;
HINSTANCE hInst;                                // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna głównego
RECT rect;
HWND hEdit1, hStatusBar;

OPENFILENAME ofn;
CHAR fileName[MAX_PATH] = " ";

LPWSTR Bufor;
DWORD dwRozmiar, dwPrzeczyt, dwZapisane;
HANDLE hPlik;

HFONT selFont;

// Przekaż dalej deklaracje funkcji dołączone w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Inicjuj ciągi globalne
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_NOTATNIK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Wykonaj inicjowanie aplikacji:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NOTATNIK));

	MSG msg;

	// Główna pętla komunikatów:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  PRZEZNACZENIE: Rejestruje klasę okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NOTATNIK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_NOTATNIK);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   PRZEZNACZENIE: Zapisuje dojście wystąpienia i tworzy okno główne
//
//   KOMENTARZE:
//
//        W tej funkcji dojście wystąpienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyświetlane okno główne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Przechowuj dojście wystąpienia w naszej zmiennej globalnej

	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	GetWindowRect(hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	hEdit1 = CreateWindowEx(0, _T("Edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_WANTRETURN, 0, 0, width, height - 100, hWnd, NULL, NULL, NULL);

	//hStatusBar = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	//SetWindowTextA(hStatusBar, "Status Bar");

	RECT client_rect;
	GetClientRect(hWnd, &client_rect);
	hStatusBar = CreateWindowEx(0, STATUSCLASSNAME, _T(""), WS_CHILD | WS_VISIBLE | WS_EX_TOPMOST, 0, client_rect.bottom - client_rect.top - 20, client_rect.right - client_rect.left, 20, hWnd, NULL, NULL, NULL);
	int iStatusBarWidths[] = { -1 };
	SendMessageW(hStatusBar, SB_SETPARTS, 1, (LPARAM)iStatusBarWidths);
	SetWindowTextA(hStatusBar, "Loaded program.");


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PRZEZNACZENIE: Przetwarza komunikaty dla okna głównego.
//
//  WM_COMMAND  - przetwarzaj menu aplikacji
//  WM_PAINT    - Maluj okno główne
//  WM_DESTROY  - opublikuj komunikat o wyjściu i wróć
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Analizuj zaznaczenia menu:
		switch (wmId)
		{
		case IDM_ABOUT:
			//CTRL+I
			SetWindowTextA(hStatusBar, "Otwarto informacje o aplikacji.");
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			//CTRL+Q
			DestroyWindow(hWnd);
			break;
		case IDM_PLIK_ZAPISZ:
			//CTRL+S

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.lpstrFilter = L"Pliki tekstowe (*.txt)\0*.txt\0Wszystkie pliki\0*.*\0";
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrFile = (LPWSTR)fileName;
			ofn.lpstrDefExt = _T("txt");
			ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
			if (GetSaveFileName(&ofn)) {
				hPlik = CreateFile((LPCWSTR)ofn.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				MessageBox(NULL, ofn.lpstrFile, _T("Sciezka pliku"), MB_ICONEXCLAMATION);
				//TODO: nie zapisuje pod wpisana nazwa
				//hPlik = CreateFileA("ddd.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
				if (hPlik == INVALID_HANDLE_VALUE) {
					MessageBoxA(NULL, "Nie można otworzyć pliku.", "ERROR", MB_ICONEXCLAMATION);
				}
				else {
					dwRozmiar = GetWindowTextLength(hWnd);
					if (dwRozmiar == 0) {
						MessageBoxA(NULL, "Nieprawidłowy rozmiar pliku!", "ERROR", MB_ICONEXCLAMATION);
					}
					else {
						Bufor = (LPWSTR)GlobalAlloc(GPTR, dwRozmiar + 1);
						if (Bufor == NULL) {
							MessageBoxA(NULL, "Za mało pamięci!", "ERROR", MB_ICONEXCLAMATION);
						}
						else {
							GetWindowText(hEdit1, (LPWSTR)Bufor, dwRozmiar); // skopiuj do bufora tekst z jakiegoś okna
							Bufor[dwRozmiar] = 0; // dodaj zero na końcu stringa
							if (!WriteFile(hPlik, (LPWSTR)Bufor, dwRozmiar, &dwZapisane, NULL)) {
								MessageBoxA(NULL, "Błąd zapisu do pliku", "ERROR", MB_ICONEXCLAMATION);
							}
							else {
								SetWindowTextA(hStatusBar, "Zapisano plik.");
							}
						}
						GlobalFree(Bufor); // Zwolnij bufor
					}
				}
				CloseHandle(hPlik); // Zamknij plik
			}
			break;
		case IDM_PLIK_OTWORZ:
			//CTRL+O

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.lpstrFilter = L"Pliki tekstowe (*.txt)\0*.txt\0Wszystkie pliki\0*.*\0";
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrFile = (LPWSTR) fileName;
			ofn.lpstrDefExt = _T("txt");
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			if (GetOpenFileName(&ofn)) {
				hPlik = CreateFile((LPCWSTR)ofn.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
			
				MessageBox(NULL, ofn.lpstrFile, _T("Sciezka pliku"), MB_ICONEXCLAMATION);
				//hPlik = CreateFileA("klklk.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
				if (hPlik == INVALID_HANDLE_VALUE) {
					MessageBoxA(NULL, "Nie można otworzyć pliku.", "Error", MB_ICONEXCLAMATION);
				}
				else {
					dwRozmiar = GetFileSize(hPlik, NULL);
					if (dwRozmiar == 0xFFFFFFFF) {
						MessageBoxA(NULL, "Nieprawidłowy rozmiar pliku!", "Error", MB_ICONEXCLAMATION);
					}
					else {
						Bufor = (LPWSTR)GlobalAlloc(GPTR, dwRozmiar + 1);
						if (Bufor == NULL) {
							MessageBoxA(NULL, "Za mało pamięci!", "Error", MB_ICONEXCLAMATION);
						}
						else {
							if (!ReadFile(hPlik, Bufor, dwRozmiar, &dwPrzeczyt, NULL)) {
								MessageBoxA(NULL, "Błąd czytania z pliku", "Error", MB_ICONEXCLAMATION);
							}
							else {
								Bufor[dwRozmiar] = 0; // dodaj zero na końcu stringa
								SetWindowText(hEdit1, (LPWSTR)Bufor); // wyświetl tekst
								
								SetWindowTextA(hStatusBar, "Wczytano plik.");
							}
						}
						GlobalFree(Bufor); // Zwolnij bufor
					}
				}
				CloseHandle(hPlik); // Zamknij plik
			}
			break;
		case IDM_EDYCJA_ZAZNACZWSZYSTKO:
			//CTRL+A
			SendMessage(hEdit1, EM_SETSEL, 0, -1);
			SetWindowTextA(hStatusBar, "Zaznaczono cały tekst.");
			break;
		case IDM_EDYCJA_WYCZYSC:
			//CTRL+D
			SetWindowTextA(hEdit1, "");
			SetWindowTextA(hStatusBar, "Wyczyszczono pole.");
			break;
		case IDM_EDYCJA_ZMIEN:
			//CTRL+U
			selFont = (HFONT)SendMessage(hEdit1, WM_GETFONT, 0, 0);

			if (selFont == NULL) {
				selFont = (HFONT)GetStockObject(SYSTEM_FONT);
			}
			LOGFONT lf;
			GetObject(selFont, sizeof(LOGFONT), &lf);

			CHOOSEFONT cfnt;
			ZeroMemory(&cfnt, sizeof(cfnt));
			cfnt.lStructSize = sizeof(cfnt);
			cfnt.hwndOwner = hWnd;
			cfnt.Flags = CF_EFFECTS | CF_FORCEFONTEXIST | CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
			cfnt.lpLogFont = &lf;

			if (!ChooseFont(&cfnt)) {
				DWORD error = CommDlgExtendedError();
				if (error) {
					MessageBox(hWnd, L"Wystąpił błąd w zmianie czcionki!", NULL, MB_ICONEXCLAMATION);
				}
			}
			else {
				if (selFont != NULL) {
					DeleteObject(selFont);
				}
				selFont = CreateFontIndirect(cfnt.lpLogFont);
				if (selFont != NULL) {
					SendMessage(hEdit1, WM_SETFONT, (WPARAM)selFont, MAKELPARAM(TRUE, 0));
				}
			}
			SetWindowTextA(hStatusBar, "Zmieniono czcionke.");
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_SIZE:
		MoveWindow(hEdit1, 0, 0, LOWORD(lParam), HIWORD(lParam), 1);
		ShowWindow(hEdit1, SW_SHOWNORMAL);
		MoveWindow(hStatusBar, 0, 0, LOWORD(lParam), HIWORD(lParam), 1);
		ShowWindow(hStatusBar, SW_SHOWNORMAL);

		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Tutaj dodaj kod rysujący używający elementu hdc...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Procedura obsługi komunikatów dla okna informacji o programie.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
