module;

export module win_cpp;
import std;
import win;
import win_enums;

using windowproc_f = win::t::LRESULT(*)(win::t::HWND hWnd, win::t::UINT uMsg, win::t::WPARAM wParam, win::t::LPARAM lParam);

export namespace win_cpp {
	using WindowStyle = win::e::WindowStyle;
	using ExtendedWindowStyle = win::e::ExtendedWindowStyle;
	using WindowClassStyle = win::e::WindowClassStyle;
	using CompressionEnumeration = win::e::CompressionEnumeration;
	using SystemMetrics = win::e::SystemMetrics;
	using ShowWindowCommands = win::e::ShowWindowCommands;
	using LR_Flags = win::e::LR_Flags;
	using ImageType = win::e::ImageType;
	using StandardIcons = win::e::StandardIcons;
	using StandardCursors = win::e::StandardCursors;
	using MultimonitorAPI = win::e::MultimonitorAPI;
	using VirtualKeysStandardSet = win::e::VirtualKeysStandardSet;
	using MapVirtualKeyType = win::e::MapVirtualKeyType;
	using CodePageTypes = win::e::CodePageTypes;
	using WC = win::e::WC;
	using Edges = win::e::Edges;
	using PlatformID = win::e::PlatformID;
	using OSProductType = win::e::OSProductType;
	using OSVersionBitwiseCond = win::e::OSVersionBitwiseCond;
	using OSVersionFlags = win::e::OSVersionFlags;
	using SetWindowPosFlags = win::e::SetWindowPosFlags;
	using WindowZOrder = win::e::WindowZOrder;
	using WindowMessage = win::e::WM;
	using RawInputDevFunc = win::e::RawInputDevFunc;
	using HIDUsagePage = win::e::HID::HIDUsagePage;
	using MouseActiveRetVal = win::e::MouseActiveRetVal;
	using SystemMenuCommand = win::e::SystemMenuCommand;
	using KeyHighwordFlags = win::e::KeyHighwordFlags;
	using DWM_BlurBehindFlags = win::e::DWM_BlurBehindFlags;
	using ExecutionState = win::e::ExecutionState;
	using SystemParametersInfoValues = win::e::SystemParametersInfoValues;
	using StartupFlags = win::e::StartupFlags;
	using ConsoleAttibutesFlags = win::e::ConsoleAttibutesFlags;
	using WindowsScancode = win::e::WindowsScancode;
	using TrackMouseEventFlags = win::e::TrackMouseEventFlags;
	using MouseKeysFlags = win::e::MouseKeysFlags;
	using C_File_Options = win::e::C_File_Options;
	namespace hid = win::e::HID;

	win::t::LRESULT windowProc(win::t::HWND hWnd, win::t::UINT uMsg, win::t::WPARAM wParam, win::t::LPARAM lParam) {
		return win::f::DefWindowProcW(static_cast<win::t::HWND>(hWnd), uMsg, wParam, lParam);
	}

	void SetStdOutMode(C_File_Options mode) {
		win::f::set_stdio_mode(std::to_underlying(mode));
	}

	bool SystemParametersInfoUnicode(win_cpp::SystemParametersInfoValues uiAction, unsigned uiParam, void* pvParam, unsigned fWinIni) {
		unsigned uiAction_ = std::to_underlying(uiAction);
		return win::f::SystemParametersInfoW(uiAction_, uiParam, pvParam, fWinIni);
	}
	
	struct PolymorphismByWindows {
		unsigned long long wParam;
		long long lParam;
	};

	const win::t::GUID _glfw_GUID_DEVINTERFACE_HID = { 0x4d1e55b2,0xf16f,0x11cf,{0x88,0xcb,0x00,0x11,0x11,0x00,0x00,0x30} };

	int GetKeyState(VirtualKeysStandardSet key) {
		return win::f::GetKeyState(std::to_underlying(key));
	}

	enum class WindowsKeyState : bool {
		released = false,
		pressed = true
	};

	WindowsKeyState GetAsyncKeyState(win_cpp::VirtualKeysStandardSet key) {
		short state = win::f::GetAsyncKeyState(std::to_underlying(key));
		if ((state & 0x8000) != 0) {
			return WindowsKeyState::pressed;
		}
		return WindowsKeyState::released;
	}

	std::pair<short, short> GetMousePosition(long long lParam) {
		auto x = win::f::HIWORD(lParam);
		auto y = win::f::LOWORD(lParam);
		return std::make_pair(x, y);
	}

	std::wstring MultiByteToWideChar(std::string_view str) {
		auto encode_type = std::to_underlying(win_cpp::CodePageTypes::CP_UTF8);
		auto len = win::f::MultiByteToWideChar(encode_type, 0, str.data(), -1, nullptr, 0);
		std::wstring wide_str(len, L'\0');
		win::f::MultiByteToWideChar(encode_type, 0, str.data(), -1, wide_str.data(), len);
		return wide_str;
	}

	std::string WideCharToMultiByte(std::wstring_view wstr) {
		if (wstr.empty()) return {};
		auto encode_type = std::to_underlying(win_cpp::CodePageTypes::CP_UTF8);
		int len = win::f::WideCharToMultiByte(encode_type, 0, wstr.data(), -1, nullptr, 0, nullptr, nullptr);
		if (len == 0) throw std::runtime_error("WideCharToMultiByte failed");
		std::string utf8(len - 1, '\0');
		win::f::WideCharToMultiByte(encode_type, 0, wstr.data(), -1, utf8.data(), len, nullptr, nullptr);
		return utf8;
	}

	struct Title {
		private:
			std::wstring _title;

		public:
			Title(std::wstring_view str) : _title(str) {}
			Title(std::string_view str) : _title(win_cpp::MultiByteToWideChar(str)) {}
			Title(std::string str) : Title(std::string_view(str)) {}
			Title(const char* str) : Title(std::string_view(str)) {}

		public:
			std::wstring get_w() const { return _title; }
			std::string get_c() const { return win_cpp::WideCharToMultiByte(_title); }
	};

	struct DefaultInstance {};

	struct Instance {
	public:
		using type = win::t::HINSTANCE;

	private:
		type _instance = nullptr;

	public:
		// explicit operator const type& () const { return _instance; }
		// explicit operator type& () { return _instance; }
		explicit operator type() const { return _instance; }


	public:
		// Instance() = default;
		Instance(const Instance&) = default;
		Instance& operator=(const Instance&) = default;
		Instance() : _instance(nullptr) {}
		Instance(const DefaultInstance&) : _instance(win::f::GetModuleHandleW(0)) {}
		Instance(std::wstring_view module_name) : _instance(win::f::GetModuleHandleW(module_name.data())) {}
		Instance(Instance&& instance) : _instance(std::exchange(instance._instance, {})) {}
		Instance& operator=(Instance&& instance) {
			if (&instance == this) { return *this; }
			_instance = std::exchange(instance._instance, {});
			return *this;
		}
	};

	struct Bitmap_V5 {
	private:
		unsigned long bV5Size = sizeof(win::t::BITMAPV5HEADER);
	public:
		long Width = 0;
		long Height = 0;
		unsigned short Planes = 1;
		win::e::BitCount BitCount = win::e::BitCount::BY_COMPRESSOR; // unsigned short BitCount;
		win::e::CompressionEnumeration Compression = win::e::CompressionEnumeration::BI_BITFIELDS;
		unsigned long SizeImage = 0;
		long XPixelsPerMeter = 0;
		long YPixelsPerMeter = 0;
		unsigned long ClrUsed = 0;
		unsigned long ClrImportant = 0;
		unsigned long RedMask = 0;
		unsigned long GreenMask = 0;
		unsigned long BlueMask = 0;
		unsigned long AlphaMask = 0;
		win::e::LogColorSpace CSType = win::e::LogColorSpace::CALIBRATED;
		win::t::CIEXYZTRIPLE Endpoints = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
		unsigned long GammaRed = 0;
		unsigned long GammaGreen = 0;
		unsigned long GammaBlue = 0;
		win::e::GamutMappingIntent Intent = win::e::GamutMappingIntent::LCS_GM_UNKNOWN;
		unsigned long ProfileData = 0;
		unsigned long ProfileSize = 0;
		unsigned long Reserved = 0;

	public:
		win::t::BITMAPV5HEADER get_as_win() const {
			win::t::BITMAPV5HEADER bv5;
			std::memset(&bv5, 0, sizeof(bv5));
			bv5.bV5Size = bV5Size;
			bv5.bV5Width = Width;
			bv5.bV5Height = Height;
			bv5.bV5Planes = Planes;
			bv5.bV5BitCount = std::to_underlying(BitCount);
			bv5.bV5Compression = std::to_underlying(Compression);
			bv5.bV5SizeImage = SizeImage;
			bv5.bV5XPelsPerMeter = XPixelsPerMeter;
			bv5.bV5YPelsPerMeter = YPixelsPerMeter;
			bv5.bV5ClrUsed = ClrUsed;
			bv5.bV5ClrImportant = ClrImportant;
			bv5.bV5RedMask = RedMask;
			bv5.bV5GreenMask = GreenMask;
			bv5.bV5BlueMask = BlueMask;
			bv5.bV5AlphaMask = AlphaMask;
			bv5.bV5CSType = std::to_underlying(CSType);
			bv5.bV5Endpoints = Endpoints;
			bv5.bV5GammaRed = GammaRed;
			bv5.bV5GammaGreen = GammaGreen;
			bv5.bV5GammaBlue = GammaBlue;
			bv5.bV5Intent = std::to_underlying(Intent);
			bv5.bV5ProfileData = ProfileData;
			bv5.bV5ProfileSize = ProfileSize;
			bv5.bV5Reserved = Reserved;
			return bv5;
		}
	};

	struct Bitmap_Info {
	private:
		unsigned long Size = sizeof(win::t::BITMAPINFOHEADER);
	public:
		long Width = 0;
		long Height = 0;
		unsigned short Planes = 1;
		win::e::BitCount BitCount = win::e::BitCount::BY_COMPRESSOR; // unsigned short BitCount;
		win::e::CompressionEnumeration Compression = win::e::CompressionEnumeration::BI_BITFIELDS;
		// unsigned long SizeImage = 0;
		long XPixelsPerMeter = 0;
		long YPixelsPerMeter = 0;
		unsigned long ClrUsed = 0;
		unsigned long ClrImportant = 0;

	public:
		win::t::BITMAPINFO get_as_win() const {
			auto calc_Size = [](auto Width, auto Height, auto BitCount) {
				auto stride = ((((Width * BitCount) + 31) & ~31) >> 3);
				return std::abs(Height) * stride;
				};
			win::t::BITMAPINFO bi = {};
			bi.bmiColors[0].rgbBlue = 0xFF;
			bi.bmiColors[0].rgbGreen = 0x00;
			bi.bmiColors[0].rgbRed = 0x00;
			bi.bmiColors[0].rgbReserved = 0x00;

			// bi.bmiColors = nullptr;
			bi.bmiHeader.biSize = Size;
			bi.bmiHeader.biHeight = Height;
			bi.bmiHeader.biWidth = Width;
			bi.bmiHeader.biCompression = std::to_underlying(Compression);
			bi.bmiHeader.biBitCount = std::to_underlying(BitCount);
			bi.bmiHeader.biSizeImage = 0; //  calc_Size(Width, Height, bi.bmiHeader.biBitCount);
			bi.bmiHeader.biClrImportant = ClrImportant;
			bi.bmiHeader.biClrUsed = ClrUsed;
			bi.bmiHeader.biPlanes = Planes;
			bi.bmiHeader.biXPelsPerMeter = XPixelsPerMeter;
			bi.bmiHeader.biYPelsPerMeter = YPixelsPerMeter;
			return bi;
		}
	};

	int GetSystemMetrics(win::e::SystemMetrics metric) noexcept {
		int _metric = std::to_underlying(metric);
		return win::f::GetSystemMetrics(_metric);
	}

	int GetSystemMetricsForDpi(win::e::SystemMetrics metric, unsigned dpi) noexcept {
		int _metric = std::to_underlying(metric);
		return win::f::GetSystemMetricsForDpi(_metric, dpi);
	}

	win::t::HBITMAP CreateDIBSection(
		const Bitmap_Info& bitmap,
		win::e::DeviceIndependentBitmapColorTable usage,
		std::span<const std::byte> data
	) {
		auto CalculateImageSize = [](long width, long height, unsigned short bitCount) {
			long stride = (((width * bitCount) + 31) & ~31) >> 3;
			return static_cast<size_t>(std::abs(height)) * stride;
			};
		auto bitmap_info = bitmap.get_as_win();
		win::t::HDC dc = win::f::GetDC(0);
		if (dc == nullptr) { throw std::runtime_error("DC is nullptr"); }
		auto Usage = std::to_underlying(usage);

		auto predicted = CalculateImageSize(bitmap.Width, bitmap.Height, bitmap_info.bmiHeader.biBitCount);
		auto real = data.size();
		if (predicted != real) {
			throw std::runtime_error("data size is wrong!");
		}

		std::byte* ppvBits = nullptr;
		auto handle = win::f::CreateDIBSection(dc, &bitmap_info, Usage, reinterpret_cast<void**>(&ppvBits), 0, 0);
		win::f::ReleaseDC(0, dc);
		if (handle == nullptr) { throw std::runtime_error("Handle is nullptr"); }
		std::copy(data.begin(), data.end(), ppvBits);
		return handle;
	}



	struct BitmapColorHandle {
		using type = win::t::HBITMAP;
		explicit operator type() const { return color_handle; }

	protected:
		type color_handle;

	public:
		BitmapColorHandle(BitmapColorHandle&& x) : color_handle(std::exchange(x.color_handle, nullptr)) {}
		BitmapColorHandle(
			const Bitmap_Info& bitmap,
			win::e::DeviceIndependentBitmapColorTable usage,
			std::span<const std::byte> data
		) : color_handle(
			CreateDIBSection(bitmap, usage, data)
		)
		{
		}

		~BitmapColorHandle() { win::f::DeleteObject(color_handle); }
	};

	win::t::HBITMAP CreateBitmap(int width, int height, unsigned nBitCount, const void* data = nullptr) {
		return win::f::CreateBitmap(width, height, 1, nBitCount, data);
	}

	struct BitmapMaskHandle {
		using type = win::t::HBITMAP;
		explicit operator type() const { return mask_handle; }
	protected:
		type mask_handle;
	public:
		BitmapMaskHandle(BitmapMaskHandle&& mask) : mask_handle(std::exchange(mask.mask_handle, nullptr)) {}
		BitmapMaskHandle(const BitmapMaskHandle&) = delete;
		BitmapMaskHandle(int width, int height, unsigned nBitCount, const void* data = nullptr) : mask_handle(CreateBitmap(width, height, nBitCount, data)) {}
		~BitmapMaskHandle() { win::f::DeleteObject(mask_handle); }
	};

	struct IconCreateInfo {
		bool icon;
		int xhot;
		int yhot;

		win::t::ICONINFO get_as_win() const {
			win::t::ICONINFO ii = {};
			ii.fIcon = icon;
			ii.xHotspot = xhot;
			ii.yHotspot = yhot;
			ii.hbmColor = nullptr;
			ii.hbmMask = nullptr;
			return ii;
		}
	};

	win::t::HICON CreateIconIndirect(
		const BitmapColorHandle& color,
		const BitmapMaskHandle& mask,
		const IconCreateInfo& info
	) {
		auto ii = info.get_as_win();
		ii.hbmMask = BitmapColorHandle::type(mask);
		ii.hbmColor = BitmapMaskHandle::type(color);
		return win::f::CreateIconIndirect(&ii);
	}

	struct LoadImageInfo {
		int cx = 0;
		int cy = 0;
		win::e::LR_Flags fuLoad;
	};

	struct LoadImageStandardInfo : LoadImageInfo {
		protected:
			Instance instance = Instance{};
		public:
			Instance get_instance() const {
				return instance;
			}
	};

	struct LoadImageFromModuleInfo : LoadImageStandardInfo {
		Instance instance;
		std::wstring_view image_name;
	};

	struct LoadCursorImageFromModuleInfo : LoadImageFromModuleInfo {
		protected:
			win::e::ImageType image_type = win::e::ImageType::IMAGE_CURSOR;
		public:
			StandardCursors standard_cursor;
			win::e::ImageType get_ImageType() const {
				return image_type;
			}
	};

	struct LoadIconImageFromModuleInfo : LoadImageFromModuleInfo {
		protected:
			win::e::ImageType image_type = win::e::ImageType::IMAGE_ICON;
		public:
			StandardIcons standard_icon;
			win::e::ImageType get_ImageType() const {
				return image_type;
			}
	};

	struct LoadImageStandardIconInfo : LoadImageStandardInfo {
		protected:
			win::e::ImageType image_type = win::e::ImageType::IMAGE_ICON;
		public:
			StandardIcons standard_icon;
			win::e::ImageType get_ImageType() const {
				return image_type;
			}
	};

	struct LoadImageStandardCursorInfo : LoadImageStandardInfo {
		protected:
			win::e::ImageType image_type = win::e::ImageType::IMAGE_CURSOR;
		public:
			StandardCursors standard_cursor;
			win::e::ImageType get_ImageType() const {
				return image_type;
			}
	};

	win::t::HANDLE loadImageW(
		const LoadImageStandardIconInfo& info
	) {
		win::t::HINSTANCE hInst = Instance::type(info.get_instance());
		win::t::LPCWSTR name =
			reinterpret_cast<win::t::LPCWSTR>(
				win::f::MAKEINTRESOURCE(
					std::to_underlying(info.standard_icon)
				)
			);
		win::t::UINT type = std::to_underlying(info.get_ImageType());
		win::t::UINT fuLoad = LR_Flags::MaskType(info.fuLoad);
		auto res = win::f::LoadImageW(
			hInst,
			name,
			type,
			info.cx,
			info.cy,
			fuLoad
		);
		if (!res) {
			throw std::runtime_error("Image not loaded!");
		}
		return res;
	}

	win::t::HANDLE loadImageW(
		const LoadImageStandardCursorInfo& info
	) {
		win::t::HINSTANCE hInst = Instance::type(info.get_instance());
		win::t::LPCWSTR name =
			reinterpret_cast<win::t::LPCWSTR>(
				win::f::MAKEINTRESOURCE(
					std::to_underlying(info.standard_cursor)
				)
			);
		win::t::UINT type = std::to_underlying(info.get_ImageType());
		win::t::UINT fuLoad = LR_Flags::MaskType(info.fuLoad);
		auto res = win::f::LoadImageW(
			hInst,
			name,
			type,
			info.cx,
			info.cy,
			fuLoad
		);
		if (!res) {
			throw std::runtime_error("Image not loaded!");
		}
		return res;
	}

	win::t::HANDLE loadImageW(
		const LoadCursorImageFromModuleInfo& info
	) {
		win::t::HINSTANCE hInst = Instance::type(info.instance);
		win::t::LPCWSTR name = info.image_name.data();
		win::t::UINT type = std::to_underlying(info.get_ImageType());
		win::t::UINT fuLoad = LR_Flags::MaskType(info.fuLoad);
		auto res = win::f::LoadImageW(
			hInst,
			name,
			type,
			info.cx,
			info.cy,
			fuLoad
		);
		if (!res) {
			throw std::runtime_error("Image not loaded!");
		}
		return res;
	}

	win::t::HANDLE loadImageW(
		const LoadIconImageFromModuleInfo& info
	) {
		win::t::HINSTANCE hInst = Instance::type(info.instance);
		win::t::LPCWSTR name = info.image_name.data();
		win::t::UINT type = std::to_underlying(info.get_ImageType());
		win::t::UINT fuLoad = LR_Flags::MaskType(info.fuLoad);
		auto res = win::f::LoadImageW(
			hInst,
			name,
			type,
			info.cx,
			info.cy,
			fuLoad
		);
		if (!res) {
			throw std::runtime_error("Image not loaded!");
		}
		return res;
	}

	struct Icon {
	public:
		using color_base = BitmapColorHandle;
		using mask_base = BitmapMaskHandle;
		using type = win::t::HICON;
		explicit operator type() const { return icon_handle; }

		// private:
			// using color_base::color_handle;
			// using mask_base::mask_handle;

	private:
		type icon_handle;

	public:
		Icon() : icon_handle(nullptr) {}

		Icon(const color_base& color, const mask_base& mask, const IconCreateInfo& info)
			// : color_base(std::forward<std::add_rvalue_reference_t<color_base>>(color))
			// , mask_base(std::forward<std::add_rvalue_reference_t<mask_base>>(mask))
			: icon_handle(CreateIconIndirect(color, mask, info))
		{
		}

		Icon(const LoadCursorImageFromModuleInfo& info) : icon_handle(
			reinterpret_cast<type>(loadImageW(info))
		) {}

		Icon(const LoadIconImageFromModuleInfo& info) : icon_handle(
			reinterpret_cast<type>(loadImageW(info))
		) {}

		Icon(const LoadImageStandardIconInfo& info) : icon_handle(
			reinterpret_cast<type>(loadImageW(info))
		) {}

		Icon(const LoadImageStandardCursorInfo& info) : icon_handle(
			reinterpret_cast<type>(loadImageW(info))
		) {}

		win::t::HICON get_handle() const { return icon_handle; };
	};

	struct MainClassCreateInfo {
		win::e::WindowClassStyle window_style;
		win::t::WNDPROC wnd_proc;
		StandardCursors cursor_style;
		std::wstring_view ClassName;
		LR_Flags lr_flag;
		void* hbrBackground;
		Icon cursor;
		Icon icon;
		Instance instance;

		win::t::WNDCLASSEXW get_as_win() const {
			auto _style = win::e::WindowClassStyle::MaskType(window_style);
			auto _instance = Instance::type(instance);
			win::t::WNDCLASSEXW x;
			x.cbClsExtra = 0;
			x.cbSize = sizeof(win::t::WNDCLASSEXW);
			x.cbWndExtra = 0;
			x.hbrBackground = nullptr;
			x.hCursor = Icon::type(cursor);
			x.hIcon = Icon::type(icon);
			x.hIconSm = 0;
			x.hInstance = _instance;
			x.lpfnWndProc = wnd_proc;
			x.lpszClassName = ClassName.data();
			x.lpszMenuName = nullptr;
			x.style = _style;

			return x;
		}
	};

	win::t::ATOM RegisterClassExW(const MainClassCreateInfo& info) {
		auto res = info.get_as_win();
		return win::f::RegisterClassExW(&res);
	}

	struct MainClass {
		using type = win::t::ATOM;
		explicit operator type() const { return main_class_handle; }

	private:
		type main_class_handle;

	public:
		MainClass() : main_class_handle(0) {}
		MainClass(const MainClassCreateInfo& info) : main_class_handle(RegisterClassExW(info)) {}
	};

	struct WindowCreateInfo {
	private:
		void* parent = nullptr;
		void* menu_handle = nullptr;
		void* lpParam = nullptr;

	public:
		Instance instance;
		WindowStyle dwStyle;
		ExtendedWindowStyle dwExStyle;
		MainClass main_class;// std::wstring_view lpClassName;
		std::wstring lpWindowName;
		int X;
		int Y;
		int nWidth;
		int nHeight;
	};

	win::t::HWND CreateWindowExW(
		const WindowCreateInfo& Info
	) {
		win::t::DWORD dwExStyle = ExtendedWindowStyle::MaskType(Info.dwExStyle);
		win::t::LPCWSTR lpClassName =
			reinterpret_cast<win::t::LPCWSTR>(
				win::f::MAKEINTATOM(
					MainClass::type(Info.main_class) // Info.lpClassName.data();
				)
				);
		win::t::LPCWSTR lpWindowName = Info.lpWindowName.data();
		win::t::DWORD dwStyle = WindowStyle::MaskType(Info.dwStyle);
		int X = Info.X;
		int Y = Info.Y;
		int nWidth = Info.nWidth;
		int nHeight = Info.nHeight;
		win::t::HWND nWndParent = nullptr; // Info.parent;
		win::t::HMENU hMenu = nullptr; // Info.menu_handle;
		win::t::HINSTANCE hInstance = Instance::type(Info.instance);
		void* lpParam = nullptr;
		return win::f::CreateWindowExW(
			dwExStyle,
			lpClassName,
			lpWindowName,
			dwStyle,
			X, Y,
			nWidth, nHeight,
			nWndParent,
			hMenu,
			hInstance,
			lpParam
		);
	}

	struct Monitor;
	struct Rect;
	template<typename T> concept AllowedEnum = std::true_type::value;
//	void RegisterRawInputDevice(const Window& window, RawInputDevFunc dev_func, HIDUsagePage usage_page, AllowedEnum auto hid_usage);

	
	struct StandardInput {
		using type = win::t::HANDLE;
		private:
			type handle;
		public:
			StandardInput(type&& x) : handle(x) {}
	};
	
	struct StartupInfo {
		std::wstring_view workstation_name;
		std::wstring_view title;
		StartupFlags startup_flags;
		ConsoleAttibutesFlags dwFillAttribute;
		unsigned long dwX, dwY;
		unsigned long dwXsize, dwYsize;
		StandardInput stdin, stdout, stderr;
		ShowWindowCommands wShowWindow;
	};

	StartupInfo GetStartupInfo() {
		win::t::STARTUPINFOW si = { sizeof(si) };
		win::f::GetStartupInfoW(&si);
		return StartupInfo{
			.workstation_name = si.lpDesktop,
			.title = si.lpTitle,
			.startup_flags = StartupFlags(si.dwFlags),
			.dwFillAttribute = ConsoleAttibutesFlags(si.dwFillAttribute),
			.dwX = si.dwX,
			.dwY = si.dwY,
			.dwXsize = si.dwXSize,
			.dwYsize = si.dwYSize,
			.stdin = std::move(si.hStdInput),
			.stdout = std::move(si.hStdOutput),
			.stderr = std::move(si.hStdError),
			.wShowWindow = static_cast<ShowWindowCommands>(si.wShowWindow)
		};
	}

	struct Window {
		using type = win::t::HWND;
		explicit operator type() const { return window_handle; }

	private:
		win::t::HWND window_handle;

	public:
		Window() : window_handle(nullptr) {}
		Window(const WindowCreateInfo& info) : window_handle(CreateWindowExW(info)) {
			// win::f::SetPropW(window_handle, L"GLFW", this);
		}

		~Window() {
			win::f::DestroyWindow(window_handle);
		}

		WindowStyle getStyle() const {
			auto x = std::to_underlying(win::e::WindowFieldsOffset::GWL_STYLE);
			auto y = win::f::GetWindowLongPtrW(window_handle, x);
			return static_cast<WindowStyle>(y);
		}

		WindowStyle GetWindowStyle() const {
			return getStyle();
		}

		ExtendedWindowStyle getExtendedStyle() const {
			auto x = std::to_underlying(win::e::WindowFieldsOffset::GWL_EXSTYLE);
			auto y = win::f::GetWindowLongPtrW(window_handle, x);
			return static_cast<ExtendedWindowStyle>(y);
		}

		ExtendedWindowStyle GetWindowExStyle() const {
			return getExtendedStyle();
		}

		unsigned GetDpiForWindow() const {
			return win::f::GetDpiForWindow(window_handle);
		}

		void SetWindowPosition(WindowZOrder w_order, win_cpp::Rect rect, SetWindowPosFlags PosFlags) const;

		void RegisterRawInputDevice(HIDUsagePage usage_page, AllowedEnum auto hid_usage, RawInputDevFunc dev_func) const {
			// RegisterRawInputDevice(*this, dev_func, usage_page, hid_usage);
			win::t::RAWINPUTDEVICE rid = {};
			rid.usUsagePage = std::to_underlying(usage_page);
			rid.usUsage = std::to_underlying(hid_usage);
			rid.dwFlags = std::to_underlying(dev_func);
			rid.hwndTarget = window_handle;

			auto res = win::f::RegisterRawInputDevices(&rid, 1, sizeof(rid));
			if (!res) {
				throw;
			}
		}

		void set_Title(const win_cpp::Title& title);
		win_cpp::Title get_Title() const;

		Rect GetClientRect() const noexcept;
		Rect GetWindowRect() const noexcept;
		Monitor GetMonitor(win_cpp::MultimonitorAPI mm_api) const;

		std::pair<long, long> ClientToScreen(long x, long y) const {
			win::t::POINT p{x, y};
			win::f::ClientToScreen(window_handle, &p);
			return std::make_pair(p.x, p.y);
		}

		void SetWindowProc(windowproc_f func) const {
			auto field_offset = std::to_underlying(win::e::WindowFieldsOffset::GWL_WNDPROC);
			win::f::SetWindowLongPtrA(window_handle, field_offset, reinterpret_cast<long long>(func));
		}

		win_cpp::WindowStyle SetWindowStyle(win_cpp::WindowStyle style_) const {
			auto current = GetWindowStyle();
			current |= style_;
			auto field_offset = std::to_underlying(win::e::WindowFieldsOffset::GWL_WNDPROC);
			auto style = win_cpp::WindowStyle::MaskType(current);
			win::f::SetWindowLongPtrA(window_handle, field_offset, style);
			return current;
		};

		win_cpp::ExtendedWindowStyle SetWindowExtendedStyle(win_cpp::ExtendedWindowStyle style_) const {
			auto current = GetWindowExStyle();
			current |= style_;
			auto field_offset = std::to_underlying(win::e::WindowFieldsOffset::GWL_WNDPROC);
			auto style = win_cpp::ExtendedWindowStyle::MaskType(current);
			win::f::SetWindowLongPtrA(window_handle, field_offset, style);
			return current;
		};

		bool IsThePointCapturedByTheWindowRegion(long x, long) const;

		void show() const {
			constexpr auto x = std::to_underlying(win_cpp::ShowWindowCommands::SW_SHOW);
			win::f::ShowWindow(window_handle, x);
		}

		void show_na() const {
			constexpr auto x = std::to_underlying(win_cpp::ShowWindowCommands::SW_SHOWNA);
			win::f::ShowWindow(window_handle, x);
		}

		void show_default() const {
			auto si = win_cpp::GetStartupInfo();
			if (si.startup_flags & win_cpp::StartupFlags::values::STARTF_USESHOWWINDOW) {
				win::f::ShowWindow(window_handle, std::to_underlying(si.wShowWindow));
				return;
			}

			constexpr auto x = std::to_underlying(win_cpp::ShowWindowCommands::SW_SHOWNA);
			win::f::ShowWindow(window_handle, x);
		}

		void setFlashWindow() const {
			win::f::FlashWindow(window_handle, true);
		}

		void unsetFlashWindow() const {
			win::f::FlashWindow(window_handle, false);
		}

		void hide() {
			constexpr auto x = std::to_underlying(win_cpp::ShowWindowCommands::SW_HIDE);
			win::f::ShowWindow(window_handle, x);
		}

		void maximize() {
			constexpr auto x = std::to_underlying(win_cpp::ShowWindowCommands::SW_MAXIMIZE);
			win::f::ShowWindow(window_handle, x);
		}

		void BringWindowToTop() {
			win::f::BringWindowToTop(window_handle);
		}

		void SetForegroundWindow() {
			win::f::SetForegroundWindow(window_handle);
		}

		void SetFocus() {
			win::f::SetFocus(window_handle);
		}

#if 1
		/* FIX ME */
		void focus() {
			BringWindowToTop();
			SetForegroundWindow();
			SetFocus();
		}
#endif
	};


	win_cpp::Title GetWindowTextUnicode(const win_cpp::Window& window) {
		auto size = win::f::GetWindowTextLengthW(win_cpp::Window::type(window));
		std::wstring name;
		name.reserve(size);
		win::f::GetWindowTextW(win_cpp::Window::type(window), name.data(), size);
		return win_cpp::Title(name);
	}

	win_cpp::Title win_cpp::Window::get_Title() const {
		return GetWindowTextUnicode(*this);
	}

	void SetWindowText(const win_cpp::Window& window, const win_cpp::Title& title) {
		win::f::SetWindowTextW(win_cpp::Window::type(window), title.get_w().c_str());
	}

	void win_cpp::Window::set_Title(const win_cpp::Title& title) {
			win_cpp::SetWindowText(*this, title);
	}

	bool DwmIsCompositionEnabled() {
		constexpr auto S_OK = 0L;
		int x = false;
		auto res = win::f::DwmIsCompositionEnabled(&x);
		if (res != S_OK || x > 1) {
			throw std::runtime_error("DwmIsCompositionEnabled failed!");
		}
		return x ? true : false;
	}

	std::pair<unsigned long, bool> DwmGetColorizationColor() {
		constexpr auto S_OK = 0L;
		win::t::DWORD color = 0L;
		win::t::BOOL opaque = 0;
		auto res = win::f::DwmGetColorizationColor(&color, &opaque);
		if (res != S_OK) {
			throw std::runtime_error("DwmIsCompositionEnabled failed!");
		}
		return std::make_pair(color, static_cast<bool>(opaque));
	}

	win::t::MSG GetMessage(const Window& window) {
		win::t::MSG msg = {};
		win::f::GetMessageA(&msg, Window::type(window), 0, 0);
		return msg;
	}

	win::t::MSG GetMessage() {
		win::t::MSG msg = {};
		win::f::GetMessageA(&msg, nullptr, 0, 0);
		return msg;
	}

	win::t::MSG PeekMessage(const Window& window) {
		win::t::MSG msg = {};
		constexpr int PM_REMOVE = 1;
		win::f::PeekMessageA(&msg, Window::type(window), 0, 0, PM_REMOVE);
		return msg;
	}

	win::t::MSG PeekMessageWithRemove() {
		win::t::MSG msg = {};
		constexpr int PM_REMOVE = 1;
		win::f::PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE);
		return msg;
	}

	win::t::MSG PeekMessageWithoutRemove() {
		win::t::MSG msg = {};
		constexpr int PM_NOREMOVE = 0;
		win::f::PeekMessageA(&msg, nullptr, 0, 0, PM_NOREMOVE);
		return msg;
	}
	
	struct Message {
		using type = win::t::MSG;
		explicit operator type() { return message; }

		private:
			type message;

		public:
			void translate() {
				win::f::TranslateMessage(&message);
			}
			void dispatch() {
				win::f::DispatchMessageA(&message);
			}
			WindowMessage get_msg(const Window& window) {
				message = GetMessage(window);
				return static_cast<WindowMessage>(message.message);
			}
			WindowMessage peek_msg(const Window& window) {
				message = PeekMessage(window);
				return static_cast<WindowMessage>(message.message);
			}
			WindowMessage get_msg() {
				message = GetMessage();
				return static_cast<WindowMessage>(message.message);
			}
			WindowMessage peek_msg_with_remove() {
				message = PeekMessageWithRemove();
				return static_cast<WindowMessage>(message.message);
			}
			WindowMessage peek_msg_without_remove() {
				message = PeekMessageWithRemove();
				return static_cast<WindowMessage>(message.message);
			}
			unsigned long long get_wParam() const {
				return message.wParam;
			}
			long long get_lParam() const {
				return message.lParam;
			}
			unsigned long get_time() const {
				return message.time;
			}

	};

	long GetMessageTime() {
		return win::f::GetMessageTime();
	}

	std::pair<long, long> GetCursorPos() {
		win::t::POINT p = {};
		win::f::GetCursorPos(&p);
		return std::make_pair(p.x, p.y);
	}

	bool IsThePointCapturedByTheWindowRegion(const Window& window, long x, long y) {
		win::t::POINT p{x, y};
		return win::f::WindowFromPoint(p) == Window::type(window);
	}

	bool Window::IsThePointCapturedByTheWindowRegion(long x, long y) const {
		return win_cpp::IsThePointCapturedByTheWindowRegion(*this, x, y);
	}

#if 0
	void RegisterRawInputDevice(const Window& window, RawInputDevFunc dev_func, HIDUsagePage usage_page, AllowedEnum auto hid_usage) {
		win::t::RAWINPUTDEVICE rid = {
			.usUsagePage = std::to_underlying(usage_page),
			.usUsage = std::to_underlying(hid_usage),
			.dwFlags = std::to_underlying(dev_func),
			.hwndTarget = Window::type(window)
		};
		auto res = win::f::RegisterRawInputDevices(&rid, 1, sizeof(rid));
		if (!res) {
			throw;
		}
	}
#endif

	struct MonitorInfo;


	struct Monitor {
		using type = win::t::HMONITOR;
		explicit operator type() const { return monitor_handle; }

	private:
		type monitor_handle;

	public:
#if 0
		Monitor(
			const Instance& instance,
			win::e::MultimonitorAPI target
		) : monitor_handle(
			MonitorFromWindow(
				instance,
				target
			)
		) {	}
#endif
		Monitor(const Window& window, win::e::MultimonitorAPI target)
			: monitor_handle(
				win::f::MonitorFromWindow(Window::type(window), std::to_underlying(target))
			) {}

		MonitorInfo get_Info() const;
	};

	struct Rect {
		using type = win::t::RECT;
		explicit operator const type& () const { return _rect; }
		explicit operator type& () { return _rect; }
		explicit operator type() { return _rect; }

	private:
		type _rect;

	public:
		bool PtInPos(long x, long y) const;

	public:
		constexpr const long& get_top() const noexcept { return _rect.top; }
		constexpr long& get_top() noexcept { return _rect.top; }

		constexpr const long& get_bottom() const noexcept { return _rect.bottom; }
		constexpr long& get_bottom() noexcept { return _rect.bottom; }

		constexpr const long& get_right() const noexcept { return _rect.right; }
		constexpr long& get_right() noexcept { return _rect.right; }

		constexpr const long& get_left() const noexcept { return _rect.left; }
		constexpr long& get_left() noexcept { return _rect.left; }

	public:
		void SetWindowPosition(const Window& window, WindowZOrder w_order, SetWindowPosFlags PosFlags) {
			auto window_handle = Window::type(window);
			auto order = reinterpret_cast<win::t::HWND>(std::to_underlying(w_order));
			auto swp = SetWindowPosFlags::MaskType(PosFlags);
			win::f::SetWindowPos(
				window_handle,
				order,
				get_left(),
				get_top(),
				get_right() - get_left(),
				get_bottom() - get_top(),
				swp
			);
		}

		void MoveWindow(const Window& window, bool repaint) {
			auto hwnd = Window::type(window);
			win::f::MoveWindow(
				hwnd,
				get_left(),
				get_top(),
				get_right() - get_left(),
				get_bottom() - get_top(),
				repaint
			);
		};

		void AdjustWindowRectExForDpi(bool menu, unsigned dpi, win_cpp::WindowStyle, win_cpp::ExtendedWindowStyle);
		void AdjustWindowRectEx(bool menu, win_cpp::WindowStyle, win_cpp::ExtendedWindowStyle);

		void OffsetRect(int dx, int dy) {
			win::f::OffsetRect(&_rect, dx, dy);
		};
#if 0
		Rect OffsetRect(int dx, int dy) const {
			auto copy = *this;
			auto& r = static_cast<type&>(copy);
			win::f::OffsetRect(&r, dx, dy);
			return copy;
		};
#endif

	public:
		Rect() = default;
		Rect(long left, long top, long right, long bottom) : _rect({ left, top, right, bottom }) {}
		Rect(const Window& window) : Rect(window.GetClientRect()) {}
	};

	Rect GetWindowRect(const win_cpp::Window& window) noexcept {
		win::t::RECT rect;
		win::f::GetWindowRect(win_cpp::Window::type(window), &rect);
		return win_cpp::Rect{ rect.left, rect.top, rect.right, rect.bottom };
	}

	Rect Window::GetWindowRect() const noexcept {
		return win_cpp::GetWindowRect(*this);
	}

	void Window::SetWindowPosition(WindowZOrder w_order, win_cpp::Rect rect, SetWindowPosFlags PosFlags) const {
		win::t::HWND order = reinterpret_cast<win::t::HWND>(std::to_underlying(w_order));
		auto swp = SetWindowPosFlags::MaskType(PosFlags);
		win::f::SetWindowPos(
			window_handle,
			order,
			rect.get_left(),
			rect.get_top(),
			rect.get_right() - rect.get_left(),
			rect.get_bottom() - rect.get_top(),
			swp
		);
	}

	bool PtInPos(const win_cpp::Rect& rect, long x, long y) {
		const win::t::RECT& w_rect = static_cast<const win_cpp::Rect::type&>(rect);
		win::t::POINT point{ x, y };
		return win::f::PtInRect(&w_rect, point);
	}

	bool Rect::PtInPos(long x, long y) const {
		return win_cpp::PtInPos(*this, x, y);
	}

	Rect Window::GetClientRect() const noexcept {
		win::t::RECT rect;
		win::f::GetClientRect(window_handle, &rect);
		return Rect{rect.left, rect.top, rect.right, rect.bottom};
	}

	win_cpp::Rect AdjustWindowRectExForDpi(
		const Rect& inital,
		bool menu,
		unsigned dpi,
		win_cpp::WindowStyle style_,
		win_cpp::ExtendedWindowStyle extended_style_
	) {
		win::t::RECT frame = static_cast<win_cpp::Rect::type>(inital);
		auto style = win_cpp::WindowStyle::MaskType(style_);
		auto extended_style = win_cpp::ExtendedWindowStyle::MaskType(extended_style_);
		auto res = win::f::AdjustWindowRectExForDpi(&frame, style, menu, extended_style, dpi);
		if (!res) {
			throw std::runtime_error("AdjustWindowRectExForDpi failed");
		}
		return Rect(frame.left, frame.top, frame.right, frame.bottom);
	}

	win_cpp::Rect AdjustWindowRectEx(
		const win_cpp::Rect& inital,
		bool menu,
		win_cpp::WindowStyle style_,
		win_cpp::ExtendedWindowStyle extended_style_
	) {
		win::t::RECT frame = static_cast<win_cpp::Rect::type>(inital);
		auto style = win_cpp::WindowStyle::MaskType(style_);
		auto extended_style = win_cpp::ExtendedWindowStyle::MaskType(extended_style_);
		auto res = win::f::AdjustWindowRectEx(&frame, style, menu, extended_style);
		if (!res) {
			throw std::runtime_error("AdjustWindowRectEx failed");
		}
		return win_cpp::Rect(frame.left, frame.top, frame.right, frame.bottom);
	}

	void Rect::AdjustWindowRectExForDpi(
		bool menu,
		unsigned dpi,
		win_cpp::WindowStyle style_,
		win_cpp::ExtendedWindowStyle extended_style_
	) {
		auto x = win_cpp::AdjustWindowRectExForDpi(*this, menu, dpi, style_, extended_style_);
		win::t::RECT z = static_cast<win_cpp::Rect::type>(x);
		_rect = z;
	}

	void Rect::AdjustWindowRectEx(
		bool menu,
		win_cpp::WindowStyle style_,
		win_cpp::ExtendedWindowStyle extended_style_
	) {
		auto x = win_cpp::AdjustWindowRectEx(*this, menu, style_, extended_style_);
		win::t::RECT z = static_cast<win_cpp::Rect::type>(x);
		_rect = z;
	}

	struct RectRegion {
		using type = win::t::HRGN;
		explicit operator type() { return region; }
		explicit operator type&() { return region; }
		explicit operator const type&() const { return region; }

		private:
			type region;

		public:
			RectRegion(long x1, long y1, long x2, long y2) : region(win::f::CreateRectRgn(x1, y1, x2, y2)) {}
			~RectRegion() { win::f::DeleteObject(region); }
	};
	
	void DwmEnableBlurBehindWindow(
		const Window& window,
		const RectRegion& rect_region,
		DWM_BlurBehindFlags flags,
		bool fEnable,
		bool fTransitionOnMaximized
	) {
		/* TODO */
		win::t::DWM_BLURBEHIND bb = {};
		bb.dwFlags = DWM_BlurBehindFlags::MaskType(flags);
		bb.fEnable = fEnable;
		bb.fTransitionOnMaximized = fTransitionOnMaximized;
		bb.hRgnBlur = static_cast<RectRegion::type>(rect_region);
		auto res = win::f::DwmEnableBlurBehindWindow(Window::type(window), &bb);
	}

	void DwmEnableBlurBehindWindow(
		const Window& window,
		DWM_BlurBehindFlags flags
	) {
		/* TODO */
		win::t::DWM_BLURBEHIND bb = {};
		bb.dwFlags = DWM_BlurBehindFlags::MaskType(flags);
		win::f::DwmEnableBlurBehindWindow(Window::type(window), &bb);
	}

	struct MonitorInfo {
		win_cpp::Rect rect;
		win_cpp::Rect work;
		bool isPrimary;
	};

	MonitorInfo GetMonitorInfo(const Monitor& monitor) {
		win::t::MONITORINFO mi = {};
		mi.cbSize = sizeof(win::t::MONITORINFO);
		auto res = win::f::GetMonitorInfoW(Monitor::type(monitor), &mi);
		if (!res) {
			throw std::runtime_error("GetMonitorInfo failed");
		}
		MonitorInfo MI;
		MI.rect = win_cpp::Rect(mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right, mi.rcMonitor.bottom);
		MI.work = win_cpp::Rect(mi.rcWork.left, mi.rcWork.top, mi.rcWork.right, mi.rcWork.bottom);
		MI.isPrimary = mi.dwFlags;
		return MI;
	}

	MonitorInfo Monitor::get_Info() const {
		return win_cpp::GetMonitorInfo(*this);
	}

	Monitor Window::GetMonitor(win_cpp::MultimonitorAPI mm_api = win_cpp::MultimonitorAPI::MONITOR_DEFAULTTONEAREST) const {
		return Monitor(*this, mm_api);
	}

	ExecutionState SetThreadExecutionState(win_cpp::ExecutionState execution_state) {
		win::t::EXECUTION_STATE es = win_cpp::ExecutionState::MaskType(execution_state);
		return win_cpp::ExecutionState(win::f::SetThreadExecutionState(es));
	}

	void ClipCursor(const Rect& rect) {
		const win::t::RECT& _rect = static_cast<const Rect::type&>(rect);
		win::f::ClipCursor(&_rect);
	}

	void UnClipCursor() {
		win::f::ClipCursor(nullptr);
	}
	
	win_cpp::WindowsScancode map_virtual_key_to_scancode(win_cpp::VirtualKeysStandardSet virtualKey) {
		return static_cast<WindowsScancode>(win::f::MapVirtualKeyW(
			std::to_underlying(virtualKey),
			std::to_underlying(win_cpp::MapVirtualKeyType::MAPVK_VK_TO_VSC)
		));
	}

	int ToUnicode(
		win::e::VirtualKeysStandardSet VirtualKey,
		unsigned scancode,
		std::span<const std::byte> lpKeyState,
		std::span<wchar_t> pwszBuff
	) {
		auto vk = std::to_underlying(VirtualKey);

		return win::f::ToUnicode(
			vk,
			scancode,
			reinterpret_cast<const win::t::BYTE*>(lpKeyState.data()),
			reinterpret_cast<win::t::LPWSTR>(pwszBuff.data()),
			pwszBuff.size(),
			0
		);
	}

#if 1
	int WideCharToMultiByte(
		CodePageTypes codepage,
		// WC dwFlags,
		std::wstring_view lpWideCharString,
		std::span<std::byte> lpMultiByteStr
		// std::string_view lpDefaultChar
		// bool& lpUsedDefaultChar
	) {
#if 0
		if (codepage == CodePageTypes::CP_UTF7 || codepage == CodePageTypes::CP_UTF8) {
			if (lpDefaultChar.data() || lpUsedDefaultChar) {
				throw std::runtime_error("Wrong params!");
			}
		}
#endif
	
		return win::f::WideCharToMultiByte(
			std::to_underlying(codepage),
			0, // std::to_underlying(dwFlags),
			lpWideCharString.data(),
			lpWideCharString.size(),
			reinterpret_cast<char*>(lpMultiByteStr.data()),
			lpMultiByteStr.size(),
			0, // lpDefaultChar.data(),
			0 // &lpUsedDefaultChar
		);
	}
#endif

	unsigned GetDpiForWindow(const Window& window) {
		return win::f::GetDpiForWindow(Window::type(window));
	}

	struct OsVersionInfo {
		const unsigned Major;
		const unsigned Minor;
		const unsigned BuildNumber;
		const PlatformID Platform_ID;
		OsVersionInfo(unsigned major, unsigned minor, unsigned build_number, PlatformID platform_id)
			: Major(major)
			, Minor(minor)
			, BuildNumber(build_number)
			, Platform_ID(platform_id){}
	};

	OsVersionInfo GetOSVersion() {
		win::t::OSVERSIONINFOW info;
		info.dwOSVersionInfoSize = sizeof(win::t::OSVERSIONINFOW);
		win::f::RtlGetVersion(&info);
		auto platform_id = static_cast<PlatformID>(info.dwPlatformId);
		return OsVersionInfo(info.dwMajorVersion, info.dwMinorVersion, info.dwBuildNumber, platform_id);
	}

#if 1
	unsigned long long VerSetConditionMask(
		unsigned long long prev_result_,
		OSVersionFlags mask_type_,
		OSVersionBitwiseCond condition_
	) {
		unsigned long long mask = prev_result_;
		unsigned long mask_type = OSVersionFlags::MaskType(mask_type_);
		unsigned char condition = std::to_underlying(condition_);
		return win::f::VerSetConditionMask(mask, mask_type, condition);
	};
#endif

	bool RtlVerifyVersionInfo(
		unsigned char major,
		unsigned char minor,
		unsigned char sp,
		unsigned build_number,
		PlatformID platform_id,
		OSVersionFlags mask,
		unsigned long long cond// OSVersionBitwiseCond cond
	) {
		win::t::OSVERSIONINFOEXW osvi = {};
		osvi.dwOSVersionInfoSize = sizeof(osvi);
		osvi.dwMajorVersion = major;
		osvi.dwMinorVersion = minor;
		osvi.dwBuildNumber = build_number;
		osvi.dwPlatformId = std::to_underlying(platform_id);
		//osvi.szCSDVersion = { 0 };
		osvi.wServicePackMajor = sp;
		return win::f::RtlVerifyVersionInfo(
			&osvi,
			OSVersionFlags::MaskType(mask),
			cond
		);
	}

	template <typename Type, template <typename...> typename Template> constexpr bool is_specialization_v = false;
	template <template <typename...> typename Template, typename... Types> constexpr bool is_specialization_v<Template<Types...>, Template> = true;
	template <typename Type, template <typename...> typename Template> struct is_specialization : std::bool_constant<is_specialization_v<Type, Template>> {};
	template <typename T> constexpr bool is_duration_v = is_specialization_v<T, std::chrono::duration>;
	template <typename T> concept is_duration = is_specialization_v<T, std::chrono::duration>;
	
	bool TrackMouseEvent(
		const win_cpp::Window& window,
		win_cpp::TrackMouseEventFlags tme_event,
		const is_duration auto& dur = std::chrono::milliseconds(0)
	) {
		using ul_milli = std::chrono::duration<unsigned long, std::chrono::milliseconds::period>;
		win::t::TRACKMOUSEEVENT tme = {};
		tme.cbSize = sizeof(win::t::TRACKMOUSEEVENT);
		tme.hwndTrack = win_cpp::Window::type(window);
		tme.dwFlags = win_cpp::TrackMouseEventFlags::MaskType(tme_event);
		if (tme_event & win_cpp::TrackMouseEventFlags::values::TME_HOVER) {
			auto ms = std::chrono::duration_cast<ul_milli>(dur);
			if (ms.count() != 0) {
				tme.dwHoverTime = ms.count();
			}
		}
		auto result = win::f::TrackMouseEvent(&tme);
		return (result != 0);
	}

	struct Mouse {
		private:
			bool _isTracking = false;
		public:
			bool isTracking() const { return _isTracking; }

			void StartTracking(
				const win_cpp::Window& window,
				win_cpp::TrackMouseEventFlags tme_events,
				const is_duration auto& dur
			) noexcept {
				if(tme_events & win_cpp::TrackMouseEventFlags::values::TME_CANCEL) { /// ?
					tme_events &= ~(win_cpp::TrackMouseEventFlags::values::TME_CANCEL);
				}
				_isTracking = win_cpp::TrackMouseEvent(window, tme_events, dur);
			}

			void StartTracking(
				const win_cpp::Window& window,
				win_cpp::TrackMouseEventFlags tme_events
			) {
				auto x = std::chrono::milliseconds{ 0 };
				StartTracking(window, tme_events, x);
			}

			void StopTracking() {
				win::t::TRACKMOUSEEVENT tme = {};
				tme.cbSize = sizeof(win::t::TRACKMOUSEEVENT);
				tme.dwFlags = std::to_underlying(win_cpp::TrackMouseEventFlags::values::TME_CANCEL);
				win::f::TrackMouseEvent(&tme);
				_isTracking = false;
			}
	};

	unsigned get_SPI_GETMOUSETRAILS() {
		unsigned mouseTrailSize = 0;
		win_cpp::SystemParametersInfoUnicode(win_cpp::SystemParametersInfoValues::SPI_GETMOUSETRAILS, 0, &mouseTrailSize, 0);
		return mouseTrailSize;
	};

	void set_SPI_SETMOUSETRAILS(unsigned mouseTrailSize, bool write_to_user_profile) {
		win_cpp::SystemParametersInfoUnicode(win_cpp::SystemParametersInfoValues::SPI_SETMOUSETRAILS, mouseTrailSize, nullptr, write_to_user_profile);
	};

};