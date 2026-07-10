module;

#include "win_def.hpp"
#undef CHAR_BIT

export module win;
export import win_enums;
import std;

export namespace win {
	namespace e {
		/* Enums */
		using MonitorDPIType = ::MONITOR_DPI_TYPE;
	}
	
	namespace t {
		/* types */
		using LPWSTR = ::LPWSTR;
		using HMENU = ::HMENU;
		using CIEXYZTRIPLE = ::CIEXYZTRIPLE;
		using LPCCH = ::LPCCH;
		using WNDPROC = ::WNDPROC;
		using HCURSOR = ::HCURSOR;
		using LONG = ::LONG;
		using HRGN = ::HRGN;
		using BOOL = ::BOOL;
		using HRESULT = ::HRESULT;
		using WINDOWPLACEMENT = ::WINDOWPLACEMENT;
		using ULONG_PTR = ::ULONG_PTR;
		using LPVOID = ::LPVOID;
		using LPTSTR = ::LPTSTR;
		using RECT = ::RECT;
		using HMONITOR = ::HMONITOR;
		using MONITORINFO = ::MONITORINFO;
		using BITMAPINFO = ::BITMAPINFO;
		using HCURSOR = ::HCURSOR;
		using HDC = ::HDC;
		using HBITMAP = ::HBITMAP;
		using BITMAPV5HEADER = ::BITMAPV5HEADER;
		using BITMAPINFOHEADER = ::BITMAPINFOHEADER;
		using ICONINFO = ::ICONINFO;
		using ATOM = ::ATOM;
		// using GUID = ::GUID;
		using WCHAR = ::WCHAR;
		using LPCWSTR = ::LPCWSTR;
		using LPSTR = ::LPSTR;
		using BYTE = ::BYTE;
		using WORD = ::WORD;
		using UINT = ::UINT;
		using DWORD = ::DWORD;
		using ULONG = ::ULONG;
		using ULONGLONG = ::ULONGLONG;
		using LRESULT = ::LRESULT;
		using HWND = ::HWND;
		using WPARAM = ::WPARAM;
		using LPARAM = ::LPARAM;
		using CREATESTRUCTW = ::CREATESTRUCTW;
		using OSVERSIONINFOEXW = ::OSVERSIONINFOEXW;
		using PRTL_OSVERSIONINFOEXW = ::PRTL_OSVERSIONINFOEXW;
		using WNDCLASSEXW = ::WNDCLASSEXW;
		using HINSTANCE = ::HINSTANCE;
		using HICON = ::HICON;
		using HANDLE = ::HANDLE;
		using DWM_BLURBEHIND = ::DWM_BLURBEHIND;
		using MSG = ::MSG;
		using LPCCH = ::LPCCH;
		using LPBOOL = ::LPBOOL;
		using RAWINPUTDEVICE = ::RAWINPUTDEVICE;
		using PCRAWINPUTDEVICE = ::PCRAWINPUTDEVICE;
		using RAWINPUT = ::RAWINPUT;
		using HRAWINPUT = ::HRAWINPUT;
		using RAWINPUTHEADER = ::RAWINPUTHEADER;
		using RAWKEYBOARD = ::RAWKEYBOARD;
		using TCHAR = ::TCHAR;
		using PAINTSTRUCT = ::PAINTSTRUCT;
		using OSVERSIONINFOW = ::OSVERSIONINFOW;
		using HBRUSH = ::HBRUSH;
		using COLORREF = ::COLORREF;
		using LPPOINT = ::LPPOINT;
		using POINT = ::POINT;
		using HRGN = ::HRGN;
		using DWM_BLURBEHIND = ::DWM_BLURBEHIND;
		using EXECUTION_STATE = ::EXECUTION_STATE;
		using STARTUPINFOW = ::STARTUPINFOW;
		using TRACKMOUSEEVENT = ::TRACKMOUSEEVENT;
		using PUINT = ::PUINT;
		using RAWMOUSE = ::RAWMOUSE;
		using RAWKEYBOARD = ::RAWKEYBOARD;
		using RAWHID = ::RAWHID;
	}
	
	namespace f {
		using ::SetPropW;
		using ::GetPropW;
		using ::VerSetConditionMask;
		using ::RtlVerifyVersionInfo;
		using ::RtlGetVersion;
		using ::DefWindowProcW;
		using ::EnableNonClientDpiScaling;
		using ::MapVirtualKeyW;
		using ::ToUnicode;
		using ::WideCharToMultiByte;
		using ::LoadCursorW;
		using ::LoadImageW;
		using ::GetModuleHandleW;
		using ::RegisterClassExW;
		using ::GetSystemMetrics;
		using ::GetDC;
		using ::CreateDIBSection;
		using ::ReleaseDC;
		using ::CreateBitmap;
		using ::DeleteObject;
		using ::CreateIconIndirect;
		using ::GetMonitorInfoW;
		using ::AdjustWindowRectEx;
		using ::MultiByteToWideChar;
		using ::CreateWindowExW;
		using ::ChangeWindowMessageFilterEx;
		using ::MonitorFromWindow;
		using ::GetDpiForMonitor;
		using ::GetDeviceCaps;
		using ::AdjustWindowRectExForDpi;
		using ::GetDpiForWindow;
		using ::GetWindowPlacement;
		using ::OffsetRect;
		using ::SetWindowPlacement;
		using ::SetWindowPos;
		using ::DragAcceptFiles;
		using ::DwmIsCompositionEnabled;
		using ::DwmGetColorizationColor;
		using ::CreateRectRgn;
		using ::DwmEnableBlurBehindWindow;
		using ::GetClientRect;
		using ::EnumDisplayMonitors;
		using ::MonitorFromPoint;
		using ::MonitorFromRect;
		using ::ShowWindow;
		using ::UpdateWindow;
		using ::DispatchMessageA;
		using ::TranslateMessage;
		using ::GetMessageA;
		using ::DestroyWindow;
		using ::ClipCursor;
		using ::WideCharToMultiByte;
		using ::RegisterRawInputDevices;
		using ::GetRawInputData;
		using ::GetKeyNameTextA;
		using ::StringCchPrintfA;
		using ::OutputDebugStringA;
		using ::BeginPaint;
		using ::DrawTextA;
		using ::EndPaint;
		using ::PostQuitMessage;
		using ::GetDpiForWindow;
		using ::GetWindowLongPtrW;
		using ::MoveWindow;
		// using ::GetVersionExA;
		// using ::GetVersionExW;
		using ::CreateSolidBrush;
		using ::FillRect;
		using ::PostQuitMessage;
		using ::PeekMessageA;
		using ::GetClipboardFormatNameW;
		using ::InvalidateRect;
		using ::SetWindowLongPtrA;
		using ::PostMessageA;
		using ::GetKeyState;
		using ::ClientToScreen;
		using ::WindowFromPoint;
		using ::GetCursorPos;
		using ::PtInRect;
		using ::DwmIsCompositionEnabled;
		using ::DwmGetColorizationColor;
		using ::CreateRectRgn;
		using ::SetThreadExecutionState;
		using ::SystemParametersInfoW;
		using ::SystemParametersInfoA;
		using ::GetSystemMetricsForDpi;
		using ::SetWindowTextW;
		using ::GetStartupInfoW;
		using ::FlashWindow;
		using ::BringWindowToTop;
		using ::SetForegroundWindow;
		using ::SetFocus;
		using ::GetMessageTime;
		using ::GetAsyncKeyState;
		using ::TrackMouseEvent;
		using ::GetWindowTextW;
		using ::GetWindowTextLengthW;
		using ::GetWindowTextA;
		using ::GetWindowTextLengthA;
		using ::GetWindowRect;
		using ::DispatchMessageW;
		
		#undef MAKEWORD
		constexpr std::uint16_t MAKEWORD(std::uint8_t a, std::uint8_t b) noexcept {
			return (static_cast<std::uint16_t>(a) & 0xFFu) | (static_cast<std::uint16_t>(b) << 8u);
		}

		#undef MAKELONG
		constexpr std::int32_t MAKELONG(std::uint16_t a, std::uint16_t b) noexcept {
			return static_cast<std::int32_t>((static_cast<std::uint32_t>(a) & 0xFFFFu) | (static_cast<std::uint32_t>(b) << 16u));
		}
		
		#undef MAKELPARAM
#if 0		
		constexpr std::int32_t MAKELPARAM(std::uint16_t low, std::uint16_t high) noexcept {
			return static_cast<int32_t>(
				(static_cast<std::uint32_t>(low)) | (static_cast<std::uint32_t>(high) << 16);
			);
		}
#else
		constexpr t::LPARAM MAKELPARAM(std::uint16_t low, std::uint16_t high) noexcept {
			return static_cast<t::LPARAM>(MAKELONG(low, high));
		}
#endif

		#undef LOWORD
		template<std::integral T> constexpr std::uint16_t LOWORD(T l) noexcept {
			return static_cast<std::uint16_t>(static_cast<std::uintptr_t>(l) & 0xFFFFu);
		}

		#undef HIWORD
		template<std::integral T> constexpr std::uint16_t HIWORD(T l) noexcept {
			return static_cast<std::uint16_t>((static_cast<std::uintptr_t>(l) >> 16u) & 0xFFFFu);
		}

		#undef LOBYTE
		template<std::integral T> constexpr std::uint8_t LOBYTE(T w) noexcept {
			return static_cast<std::uint8_t>(static_cast<std::uintptr_t>(w) & 0xFFu);
		}

		#undef HIBYTE
		template<std::integral T> constexpr std::uint8_t HIBYTE(T w) noexcept {
			return static_cast<std::uint8_t>((static_cast<std::uintptr_t>(w) >> 8u) & 0xFFu);
		}
		
		#undef MAKEINTRESOURCE
		constexpr win::t::LPSTR MAKEINTRESOURCE(int i) noexcept {
			// ((LPSTR)((ULONG_PTR)((WORD)(i))))
			auto res0 = static_cast<win::t::WORD>(i);
			auto res1 = static_cast<win::t::ULONG_PTR>(res0);
			auto res2 = reinterpret_cast<win::t::LPSTR>(res1);
			return res2;
		}

		#undef ZeroMemory
		void ZeroMemory(void* Destination, size_t Length) {
			std::memset((Destination), 0, (Length));
		}

		#undef MAKEINTATOM
		constexpr win::t::LPTSTR MAKEINTATOM(int i) noexcept {
			// ((LPTSTR)((ULONG_PTR)((WORD)(i))))
			auto res0 = static_cast<win::t::WORD>(i);
			auto res1 = static_cast<win::t::ULONG_PTR>(res0);
			auto res2 = reinterpret_cast<win::t::LPTSTR>(res1);
			return res2;
		}
		
		#undef FAILED
		constexpr bool FAILED(win::t::HRESULT x) noexcept {
			return (x < 0) ? true : false;
		}
		
		#undef SUCCEEDED
		constexpr bool SUCCEEDED(win::t::HRESULT x) noexcept {
			return !FAILED(x);
		}
	}
}