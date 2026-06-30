#include <string>
#include <string_view>

#if 0
template<typename Ftype>
Ftype get_function_address(win_def::HMODULE handle, std::string_view f_name) {
	win_def::FARPROC procAddress = win_def::GetProcAddress(handle, f_name.data());
	if (!procAddress) { return nullptr; }
	return reinterpret_cast<Ftype>(procAddress);
}
#endif

namespace win_def {
	#include<windows.h>
	#include<windef.h>
	#include<sdkddkver.h>
	#include<wingdi.h>
	#include<winuser.h>
	#include<xinput.h>
	#include<dwmapi.h>
	#include<shellscalingapi.h>
	#include<strsafe.h>
	#include<wingdi.h>
	#include<io.h>
	#include<fcntl.h>
	#include<stdio.h>

	inline void set_stdio_mode(int x) noexcept {
		_setmode(_fileno(stdout), x);
	}

	win_def::HMODULE my_module_loader(std::wstring_view mod_name) {
		win_def::HMODULE module_ = win_def::GetModuleHandleW(mod_name.data());
		if (!module_) {
			module_ = win_def::LoadLibraryW(L"ntdll.dll");
			if (!module_) {
				abort();
			}
		}
		return module_;
	}

	constexpr std::wstring_view n_ntdll = L"ntdll.dll";
	constexpr std::wstring_view n_shcore = L"shcore.dll";
	constexpr std::wstring_view n_dwmapi = L"dwmapi.dll";
	constexpr std::wstring_view n_user32 = L"user32.dll";
	constexpr std::wstring_view n_xinput = L"xinput.dll";
	constexpr std::wstring_view n_dinput8 = L"dinput8.dll";
	win_def::HMODULE m_ntdll = my_module_loader(n_ntdll);
	win_def::HMODULE m_shcore = my_module_loader(n_shcore);
	win_def::HMODULE m_dwmapi = my_module_loader(n_dwmapi);
	win_def::HMODULE m_user32 = my_module_loader(n_user32);
	win_def::HMODULE m_xinput = my_module_loader(n_xinput);
	win_def::HMODULE m_dinput8 = my_module_loader(n_dinput8);


	// xinput.dll
	using PFN_XInputGetCapabilities = DWORD(WINAPI*)(DWORD, DWORD, XINPUT_CAPABILITIES*);
	using PFN_XInputGetState =  DWORD(WINAPI*)(DWORD, XINPUT_STATE*);
	// PFN_XInputGetCapabilities XInputGetCapabilities = (PFN_XInputGetCapabilities)win_def::GetProcAddress(m_xinput, "XInputGetCapabilities");
	// PFN_XInputGetState XInputGetState = (PFN_XInputGetState)win_def::GetProcAddress(m_xinput, "XInputGetState");

	// dinput8.dll function pointer usings
	using PFN_DirectInput8Create = HRESULT(WINAPI*)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
	PFN_DirectInput8Create DirectInput8Create = (PFN_DirectInput8Create)win_def::GetProcAddress(m_dinput8, "DirectInput8Create");

	// user32.dll function pointer usings
	using PFN_EnableNonClientDpiScaling = BOOL(WINAPI*)(HWND);
	using PFN_SetProcessDpiAwarenessContext = BOOL(WINAPI*)(HANDLE);
	using PFN_GetDpiForWindow = UINT(WINAPI*)(HWND);
	using PFN_AdjustWindowRectExForDpi = BOOL(WINAPI*)(LPRECT, DWORD, BOOL, DWORD, UINT);
	using PFN_GetSystemMetricsForDpi = int(WINAPI*)(int, UINT);
	// PFN_EnableNonClientDpiScaling EnableNonClientDpiScaling = (PFN_EnableNonClientDpiScaling)win_def::GetProcAddress(m_user32, "EnableNonClientDpiScaling");
	// PFN_SetProcessDpiAwarenessContext SetProcessDpiAwarenessContext = (PFN_SetProcessDpiAwarenessContext)win_def::GetProcAddress(m_user32, "SetProcessDpiAwarenessContext");
	// PFN_GetDpiForWindow GetDpiForWindow = (PFN_GetDpiForWindow)win_def::GetProcAddress(m_user32, "GetDpiForWindow");
	// PFN_AdjustWindowRectExForDpi AdjustWindowRectExForDpi = (PFN_AdjustWindowRectExForDpi)win_def::GetProcAddress(m_user32, "AdjustWindowRectExForDpi");
	// PFN_GetSystemMetricsForDpi GetSystemMetricsForDpi = (PFN_GetSystemMetricsForDpi)win_def::GetProcAddress(m_user32, "GetSystemMetricsForDpi");

	// dwmapi.dll function pointer usings
	using PFN_DwmIsCompositionEnabled = HRESULT(WINAPI*)(BOOL*);
	using PFN_DwmFlush = HRESULT(WINAPI*)(VOID);
	using PFN_DwmEnableBlurBehindWindow = HRESULT(WINAPI*)(HWND, const DWM_BLURBEHIND*);
	using PFN_DwmGetColorizationColor = HRESULT(WINAPI*)(DWORD*, BOOL*);
	// PFN_DwmIsCompositionEnabled DwmIsCompositionEnabled = (PFN_DwmIsCompositionEnabled)win_def::GetProcAddress(m_dwmapi, "DwmIsCompositionEnabled");
	// PFN_DwmFlush DwmFlush = (PFN_DwmFlush)win_def::GetProcAddress(m_dwmapi, "DwmFlush");
	// PFN_DwmEnableBlurBehindWindow DwmEnableBlurBehindWindow = (PFN_DwmEnableBlurBehindWindow)win_def::GetProcAddress(m_dwmapi, "DwmEnableBlurBehindWindow");
	// PFN_DwmGetColorizationColor DwmGetColorizationColor = (PFN_DwmGetColorizationColor)win_def::GetProcAddress(m_dwmapi, "DwmGetColorizationColor");

	// shcore.dll function pointer usings
	using PFN_SetProcessDpiAwareness = HRESULT(WINAPI*)(PROCESS_DPI_AWARENESS);
	using PFN_GetDpiForMonitor = HRESULT(WINAPI*)(HMONITOR, MONITOR_DPI_TYPE, UINT*, UINT*);
	// PFN_SetProcessDpiAwareness SetProcessDpiAwareness = (PFN_SetProcessDpiAwareness)win_def::GetProcAddress(m_shcore, "SetProcessDpiAwareness");
	// PFN_GetDpiForMonitor GetDpiForMonitor = (PFN_GetDpiForMonitor)win_def::GetProcAddress(m_shcore, "GetDpiForMonitor");

	// ntdll.dll function pointer usings
	using PFN_RtlVerifyVersionInfo = NTSTATUS(NTAPI*)(PRTL_OSVERSIONINFOEXW VersionInfo, ULONG TypeMask, ULONGLONG ConditionMask);
	using PFN_RtlGetVersion = LONG(WINAPI*)(PRTL_OSVERSIONINFOW);
	PFN_RtlVerifyVersionInfo RtlVerifyVersionInfo = (PFN_RtlVerifyVersionInfo)win_def::GetProcAddress(m_ntdll, "RtlVerifyVersionInfo");
	PFN_RtlGetVersion RtlGetVersion = (PFN_RtlGetVersion)win_def::GetProcAddress(m_ntdll, "RtlGetVersion");
}
