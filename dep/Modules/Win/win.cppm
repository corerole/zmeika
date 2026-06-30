module;

#include "win_def.hpp"
#undef CHAR_BIT

export module win;
export import win_enums;
import std;

export namespace win {
	namespace e {
		/* Enums */
		using MonitorDPIType = win_def::MONITOR_DPI_TYPE;
	}

	namespace t {
		/* types */
		using LPWSTR = win_def::LPWSTR;
		using HMENU = win_def::HMENU;
		using CIEXYZTRIPLE = win_def::CIEXYZTRIPLE;
		using LPCCH = win_def::LPCCH;
		using WNDPROC = win_def::WNDPROC;
		using HCURSOR = win_def::HCURSOR;
		using LONG = win_def::LONG;
		using HRGN = win_def::HRGN;
		using BOOL = win_def::BOOL;
		using HRESULT = win_def::HRESULT;
		using WINDOWPLACEMENT = win_def::WINDOWPLACEMENT;
		using ULONG_PTR = win_def::ULONG_PTR;
		using LPVOID = win_def::LPVOID;
		using LPTSTR = win_def::LPTSTR;
		using RECT = win_def::RECT;
		using HMONITOR = win_def::HMONITOR;
		using MONITORINFO = win_def::MONITORINFO;
		using BITMAPINFO = win_def::BITMAPINFO;
		using HCURSOR = win_def::HCURSOR;
		using HDC = win_def::HDC;
		using HBITMAP = win_def::HBITMAP;
		using BITMAPV5HEADER = win_def::BITMAPV5HEADER;
		using BITMAPINFOHEADER = win_def::BITMAPINFOHEADER;
		using ICONINFO = win_def::ICONINFO;
		using ATOM = win_def::ATOM;
		using GUID = win_def::_GUID;
		using WCHAR = win_def::WCHAR;
		using LPCWSTR = win_def::LPCWSTR;
		using LPSTR = win_def::LPSTR;
		using BYTE = win_def::BYTE;
		using WORD = win_def::WORD;
		using UINT = win_def::UINT;
		using DWORD = win_def::DWORD;
		using ULONG = win_def::ULONG;
		using ULONGLONG = win_def::ULONGLONG;
		using LRESULT = win_def::LRESULT;
		using HWND = win_def::HWND;
		using WPARAM = win_def::WPARAM;
		using LPARAM = win_def::LPARAM;
		using CREATESTRUCTW = win_def::CREATESTRUCTW;
		using OSVERSIONINFOEXW = win_def::OSVERSIONINFOEXW;
		using PRTL_OSVERSIONINFOEXW = win_def::PRTL_OSVERSIONINFOEXW;
		using WNDCLASSEXW = win_def::WNDCLASSEXW;
		using HINSTANCE = win_def::HINSTANCE;
		using HICON = win_def::HICON;
		using HANDLE = win_def::HANDLE;
		using DWM_BLURBEHIND = win_def::DWM_BLURBEHIND;
		using MSG = win_def::MSG;
		using LPCCH = win_def::LPCCH;
		using LPBOOL = win_def::LPBOOL;
		using RAWINPUTDEVICE = win_def::RAWINPUTDEVICE;
		using PCRAWINPUTDEVICE = win_def::PCRAWINPUTDEVICE;
		using RAWINPUT = win_def::RAWINPUT;
		using HRAWINPUT = win_def::HRAWINPUT;
		using RAWINPUTHEADER = win_def::RAWINPUTHEADER;
		using RAWKEYBOARD = win_def::RAWKEYBOARD;
		using TCHAR = win_def::TCHAR;
		using PAINTSTRUCT = win_def::PAINTSTRUCT;
		using OSVERSIONINFOW = win_def::OSVERSIONINFOW;
		using HBRUSH = win_def::HBRUSH;
		using COLORREF = win_def::COLORREF;
		using LPPOINT = win_def::LPPOINT;
		using POINT = win_def::POINT;
		using HRGN = win_def::HRGN;
		using DWM_BLURBEHIND = win_def::DWM_BLURBEHIND;
		using EXECUTION_STATE = win_def::EXECUTION_STATE;
		using STARTUPINFOW = win_def::STARTUPINFOW;
		using TRACKMOUSEEVENT = win_def::TRACKMOUSEEVENT;
	}
	
	namespace f {
		using win_def::SetPropW;
		using win_def::GetPropW;
		using win_def::VerSetConditionMask;
		using win_def::RtlVerifyVersionInfo;
		using win_def::RtlGetVersion;
		using win_def::DefWindowProcW;
		using win_def::EnableNonClientDpiScaling;
		using win_def::MapVirtualKeyW;
		using win_def::ToUnicode;
		using win_def::WideCharToMultiByte;
		using win_def::LoadCursorW;
		using win_def::LoadImageW;
		using win_def::GetModuleHandleW;
		using win_def::RegisterClassExW;
		using win_def::GetSystemMetrics;
		using win_def::GetDC;
		using win_def::CreateDIBSection;
		using win_def::ReleaseDC;
		using win_def::CreateBitmap;
		using win_def::DeleteObject;
		using win_def::CreateIconIndirect;
		using win_def::GetMonitorInfoW;
		using win_def::AdjustWindowRectEx;
		using win_def::MultiByteToWideChar;
		using win_def::CreateWindowExW;
		using win_def::ChangeWindowMessageFilterEx;
		using win_def::MonitorFromWindow;
		using win_def::GetDpiForMonitor;
		using win_def::GetDeviceCaps;
		using win_def::AdjustWindowRectExForDpi;
		using win_def::GetDpiForWindow;
		using win_def::GetWindowPlacement;
		using win_def::OffsetRect;
		using win_def::SetWindowPlacement;
		using win_def::SetWindowPos;
		using win_def::DragAcceptFiles;
		using win_def::DwmIsCompositionEnabled;
		using win_def::DwmGetColorizationColor;
		using win_def::CreateRectRgn;
		using win_def::DwmEnableBlurBehindWindow;
		using win_def::GetClientRect;
		using win_def::EnumDisplayMonitors;
		using win_def::MonitorFromPoint;
		using win_def::MonitorFromRect;
		using win_def::ShowWindow;
		using win_def::UpdateWindow;
		using win_def::DispatchMessageA;
		using win_def::TranslateMessage;
		using win_def::GetMessageA;
		using win_def::DestroyWindow;
		using win_def::ClipCursor;
		using win_def::WideCharToMultiByte;
		using win_def::RegisterRawInputDevices;
		using win_def::GetRawInputData;
		using win_def::GetKeyNameTextA;
		using win_def::StringCchPrintfA;
		using win_def::OutputDebugStringA;
		using win_def::BeginPaint;
		using win_def::DrawTextA;
		using win_def::EndPaint;
		using win_def::PostQuitMessage;
		using win_def::GetDpiForWindow;
		using win_def::GetWindowLongPtrW;
		using win_def::MoveWindow;
		// using win_def::GetVersionExA;
		// using win_def::GetVersionExW;
		using win_def::CreateSolidBrush;
		using win_def::FillRect;
		using win_def::PostQuitMessage;
		using win_def::PeekMessageA;
		using win_def::GetClipboardFormatNameW;
		using win_def::InvalidateRect;
		using win_def::SetWindowLongPtrA;
		using win_def::PostMessageA;
		using win_def::GetKeyState;
		using win_def::ClientToScreen;
		using win_def::WindowFromPoint;
		using win_def::GetCursorPos;
		using win_def::PtInRect;
		using win_def::DwmIsCompositionEnabled;
		using win_def::DwmGetColorizationColor;
		using win_def::CreateRectRgn;
		using win_def::SetThreadExecutionState;
		using win_def::SystemParametersInfoW;
		using win_def::SystemParametersInfoA;
		using win_def::GetSystemMetricsForDpi;
		using win_def::SetWindowTextW;
		using win_def::GetStartupInfoW;
		using win_def::FlashWindow;
		using win_def::BringWindowToTop;
		using win_def::SetForegroundWindow;
		using win_def::SetFocus;
		using win_def::GetMessageTime;
		using win_def::GetAsyncKeyState;
		using win_def::TrackMouseEvent;
		using win_def::GetWindowTextW;
		using win_def::GetWindowTextLengthW;
		using win_def::GetWindowTextA;
		using win_def::GetWindowTextLengthA;
		using win_def::GetWindowRect;
		using win_def::set_stdio_mode; // My
		
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