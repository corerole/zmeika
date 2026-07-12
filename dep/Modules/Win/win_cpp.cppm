module;

export module win_cpp;
import std;
import win;
import win_enums;

export namespace win_cpp {
	using windowproc_f = win::t::LRESULT(*)(win::t::HWND hWnd, win::t::UINT uMsg, win::t::WPARAM wParam, win::t::LPARAM lParam);

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
	using WindowMessage = win::e::WindowMessage;
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
	using RawInputDeviceStructType = win::e::RawInputDeviceStructType;
	using RawInputDeviceType = win::e::RawInputDeviceType;
	using HitTest = win::e::HitTest;
	using RawInputType = win::e::RawInputType;
	using MouseIndicatorFlags = win::e::MouseIndicatorFlags;
	using RawInputMouseButtonsFlags = win::e::RawInputMouseButtonsFlags;
	using KeyboardInputDataTypeFlags = win::e::KeyboardInputDataTypeFlags;



	struct Rect;
	struct RawInputMouseData;
	struct RawInputKeyboardData;
	struct RawInputHIDData;

	struct WindowsKeyData {
		unsigned repeatCount;
		win_cpp::WindowsScancode scanCode;
		bool contextCode;
		bool previousState;
		bool transitionState;

		WindowsKeyData(long long lParam)
			: repeatCount(static_cast<unsigned>(lParam & 0xFFFF))
			, scanCode(static_cast<win_cpp::WindowsScancode>(
					((lParam& (1 << 24)) ? 0xE000 : 0) | ((lParam >> 16) & 0xFF)
				))
			, contextCode((lParam& (1 << 29)) != 0)
			, previousState((lParam& (1 << 30)) != 0)
			, transitionState((lParam& (1 << 31)) != 0)
		{
		}
	};


	using window_proc_callback_result_type = std::optional<long long>;

	using WM_UNKNOWN_ONE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_ACTIVATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_ACTIVATEAPP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_AFXFIRST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_AFXLAST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_APP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_APPCOMMAND_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_ASKCBFORMATNAME_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CANCELJOURNAL_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CANCELMODE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CAPTURECHANGED_callback_T = std::function<win_cpp::window_proc_callback_result_type(bool)>; // TODO
	using WM_CHANGECBCHAIN_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CHANGEUISTATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CHAR_callback_T = std::function<win_cpp::window_proc_callback_result_type(wchar_t, const WindowsKeyData&)>;
	using WM_CHARTOITEM_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CHILDACTIVATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CLEAR_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CLIPBOARDUPDATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CLOAKED_STATE_CHANGED_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CLOSE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_COMMAND_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_COMMNOTIFY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_COMPACTING_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_COMPAREITEM_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CONTEXTMENU_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_COPY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_COPYDATA_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_COPYGLOBALDATA_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CREATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CTLCOLORBTN_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CTLCOLORDLG_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CTLCOLOREDIT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CTLCOLORLISTBOX_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CTLCOLORMSGBOX_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CTLCOLORSCROLLBAR_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CTLCOLORSTATIC_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CUT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DEADCHAR_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DELETEITEM_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DESTROY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DESTROYCLIPBOARD_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DEVICECHANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DEVMODECHANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DISPLAYCHANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DPICHANGED_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DPICHANGED_AFTERPARENT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DPICHANGED_BEFOREPARENT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DRAWCLIPBOARD_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DRAWITEM_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DROPFILES_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DWMCOLORIZATIONCOLORCHANGED_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DWMCOMPOSITIONCHANGED_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DWMNCRENDERINGCHANGED_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DWMSENDICONICLIVEPREVIEWBITMAP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DWMSENDICONICTHUMBNAIL_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_DWMWINDOWMAXIMIZEDCHANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_ENABLE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_ENDSESSION_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_ENTERIDLE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_ENTERMENULOOP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_ENTERSIZEMOVE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_ERASEBKGND_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_EXITMENULOOP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_EXITSIZEMOVE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_FONTCHANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_GESTURE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_GESTURENOTIFY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_GETDLGCODE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_GETDPISCALEDSIZE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_GETFONT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_GETHOTKEY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_GETICON_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_GETMINMAXINFO_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_GETOBJECT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_GETTEXT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_GETTEXTLENGTH_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_GETTITLEBARINFOEX_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_HANDHELDFIRST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_HANDHELDLAST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_HELP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_HOTKEY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_HSCROLL_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_HSCROLLCLIPBOARD_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_ICONERASEBKGND_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_CHAR_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_COMPOSITION_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_COMPOSITIONFULL_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_CONTROL_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_ENDCOMPOSITION_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_KEYDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_KEYLAST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_KEYUP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_NOTIFY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_REQUEST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_SELECT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_SETCONTEXT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_IME_STARTCOMPOSITION_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_INITDIALOG_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_INITMENU_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_INITMENUPOPUP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	//using WM_INPUT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_RAW_INPUT_MOUSE_callback_T = std::function<win_cpp::window_proc_callback_result_type(win_cpp::RawInputType, const win_cpp::RawInputMouseData&)>; // MY
	using WM_RAW_INPUT_KEYBOARD_callback_T = std::function<win_cpp::window_proc_callback_result_type(win_cpp::RawInputType, const win_cpp::RawInputKeyboardData&)>; // MY
	using WM_RAW_INPUT_HID_callback_T = std::function<win_cpp::window_proc_callback_result_type(win_cpp::RawInputType, const win_cpp::RawInputHIDData&)>; // MY
	using WM_INPUTLANGCHANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_INPUTLANGCHANGEREQUEST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_INPUT_DEVICE_CHANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_INTERCEPTED_WINDOW_ACTION_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_KEYDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type(win_cpp::VirtualKeysStandardSet, const WindowsKeyData&)>;
	using WM_KEYFIRST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_KEYLAST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_KEYUP_callback_T = std::function<win_cpp::window_proc_callback_result_type(win_cpp::VirtualKeysStandardSet, const WindowsKeyData&)>;
	using WM_KILLFOCUS_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_LBUTTONDBLCLK_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_LBUTTONDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type(const std::pair<short, short>&, win_cpp::MouseKeysFlags)>;
	using WM_LBUTTONUP_callback_T = std::function<win_cpp::window_proc_callback_result_type(const std::pair<short, short>&, win_cpp::MouseKeysFlags)>;
	using WM_MBUTTONDBLCLK_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MBUTTONDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type(const std::pair<short, short>&, win_cpp::MouseKeysFlags)>;
	using WM_MBUTTONUP_callback_T = std::function<win_cpp::window_proc_callback_result_type(const std::pair<short, short>&, win_cpp::MouseKeysFlags)>;
	using WM_MDIACTIVATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MDICASCADE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MDICREATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MDIDESTROY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MDIGETACTIVE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MDIICONARRANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MDIMAXIMIZE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MDINEXT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MDIREFRESHMENU_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MDIRESTORE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MDISETMENU_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MDITILE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MEASUREITEM_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MENUCHAR_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MENUCOMMAND_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MENUDRAG_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MENUGETOBJECT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MENURBUTTONUP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MENUSELECT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MOUSEACTIVATE_callback_T = std::function<win_cpp::window_proc_callback_result_type(win_cpp::WindowMessage, win_cpp::HitTest)>;
	using WM_MOUSEFIRST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MOUSEHOVER_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MOUSEHWHEEL_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MOUSELAST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MOUSELEAVE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MOUSEMOVE_callback_T = std::function<win_cpp::window_proc_callback_result_type(const std::pair<short, short>&, win_cpp::MouseKeysFlags)>;
	using WM_MOUSEWHEEL_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MOVE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_MOVING_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCACTIVATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCCALCSIZE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCCREATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCDESTROY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCHITTEST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCLBUTTONDBLCLK_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCLBUTTONDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCLBUTTONUP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCMBUTTONDBLCLK_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCMBUTTONDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCMBUTTONUP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCMOUSEHOVER_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCMOUSELEAVE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCMOUSEMOVE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCPAINT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCPOINTERDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCPOINTERUP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCPOINTERUPDATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCRBUTTONDBLCLK_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCRBUTTONDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCRBUTTONUP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCXBUTTONDBLCLK_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCXBUTTONDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NCXBUTTONUP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NEXTDLGCTL_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NEXTMENU_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NOTIFY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NOTIFYFORMAT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_NULL_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_PAINT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_PAINTCLIPBOARD_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_PAINTICON_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_PALETTECHANGED_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_PALETTEISCHANGING_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_PARENTNOTIFY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_PASTE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_PENWINFIRST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_PENWINLAST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERACTIVATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERCAPTURECHANGED_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERDEVICECHANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERDEVICEINRANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERDEVICEOUTOFRANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERENTER_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERHWHEEL_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERLEAVE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERROUTEDAWAY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERROUTEDRELEASED_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERROUTEDTO_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERUP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERUPDATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POINTERWHEEL_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POWER_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_POWERBROADCAST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_PRINT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_PRINTCLIENT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_QUERYDRAGICON_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_QUERYENDSESSION_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_QUERYNEWPALETTE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_QUERYOPEN_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_QUERYUISTATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_QUEUESYNC_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_QUIT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_RBUTTONDBLCLK_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_RBUTTONDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type(const std::pair<short, short>&, win_cpp::MouseKeysFlags)>;
	using WM_RBUTTONUP_callback_T = std::function<win_cpp::window_proc_callback_result_type(const std::pair<short, short>&, win_cpp::MouseKeysFlags)>;
	using WM_RENDERALLFORMATS_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_RENDERFORMAT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SETCURSOR_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SETFOCUS_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SETFONT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SETHOTKEY_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SETICON_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SETREDRAW_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SETTEXT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SHOWWINDOW_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SIZE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SIZECLIPBOARD_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SIZING_callback_T = std::function<win_cpp::window_proc_callback_result_type(win_cpp::Edges edges, win_cpp::Rect& rect)>;
	using WM_SPOOLERSTATUS_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_STYLECHANGED_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_STYLECHANGING_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SYNCPAINT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SYSCHAR_callback_T = std::function<win_cpp::window_proc_callback_result_type(wchar_t, const WindowsKeyData&)>;
	using WM_SYSCOLORCHANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SYSCOMMAND_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SYSDEADCHAR_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_SYSKEYDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type(win_cpp::VirtualKeysStandardSet, const WindowsKeyData&)>;
	using WM_SYSKEYUP_callback_T = std::function<win_cpp::window_proc_callback_result_type(win_cpp::VirtualKeysStandardSet, const WindowsKeyData&)>;
	using WM_TABLET_FIRST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_TABLET_LAST_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_TCARD_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_THEMECHANGED_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_TIMECHANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_TIMER_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_TOOLTIPDISMISS_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_TOUCH_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_TOUCHHITTESTING_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_UNDO_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_UNICHAR_callback_T = std::function<win_cpp::window_proc_callback_result_type(unsigned codepoint, const WindowsKeyData& data)>;
	using WM_UNINITMENUPOPUP_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_UPDATEUISTATE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_USER_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_USERCHANGED_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_VKEYTOITEM_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_VSCROLL_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_VSCROLLCLIPBOARD_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_WINDOWPOSCHANGED_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_WINDOWPOSCHANGING_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_WININICHANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_WTSSESSION_CHANGE_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_XBUTTONDBLCLK_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_XBUTTONDOWN_callback_T = std::function<win_cpp::window_proc_callback_result_type(unsigned, const std::pair<short, short>&, win_cpp::MouseKeysFlags)>;
	using WM_XBUTTONUP_callback_T = std::function<win_cpp::window_proc_callback_result_type(unsigned, const std::pair<short, short>&, win_cpp::MouseKeysFlags)>;
	using WM_CHOOSEFONT_GETLOGFONT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CHOOSEFONT_SETFLAGS_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;
	using WM_CHOOSEFONT_SETLOGFONT_callback_T = std::function<win_cpp::window_proc_callback_result_type()>;

	struct AtomicFlagMutex {
		private:
			std::atomic_flag flag{}; // include <atomic> is it? ATOMIC_FLAG_INIT = {}
		public:
			void lock() { while(flag.test_and_set()) { std::this_thread::yield(); } }
			// bool try_lock() { return !flag.test_and_set(std::memory_order_acquire); }
			bool try_lock() { return !flag.test_and_set(); }
			// void unlock() { flag.clear(std::memory_order_release); }
			void unlock() { flag.clear(); }
	};

	struct CallbackHolder {
	private:
		mutable AtomicFlagMutex mutex;
		WM_UNKNOWN_ONE_callback_T WM_UNKNOWN_ONE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_ACTIVATE_callback_T WM_ACTIVATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_ACTIVATEAPP_callback_T WM_ACTIVATEAPP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_AFXFIRST_callback_T WM_AFXFIRST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_AFXLAST_callback_T WM_AFXLAST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_APP_callback_T WM_APP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_APPCOMMAND_callback_T WM_APPCOMMAND_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_ASKCBFORMATNAME_callback_T WM_ASKCBFORMATNAME_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CANCELJOURNAL_callback_T WM_CANCELJOURNAL_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CANCELMODE_callback_T WM_CANCELMODE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CAPTURECHANGED_callback_T WM_CAPTURECHANGED_callback = [](bool has_window) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CHANGECBCHAIN_callback_T WM_CHANGECBCHAIN_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CHANGEUISTATE_callback_T WM_CHANGEUISTATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CHAR_callback_T WM_CHAR_callback = [](wchar_t, const WindowsKeyData&) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CHARTOITEM_callback_T WM_CHARTOITEM_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CHILDACTIVATE_callback_T WM_CHILDACTIVATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CLEAR_callback_T WM_CLEAR_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CLIPBOARDUPDATE_callback_T WM_CLIPBOARDUPDATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CLOAKED_STATE_CHANGED_callback_T WM_CLOAKED_STATE_CHANGED_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CLOSE_callback_T WM_CLOSE_callback = []() -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_COMMAND_callback_T WM_COMMAND_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_COMMNOTIFY_callback_T WM_COMMNOTIFY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_COMPACTING_callback_T WM_COMPACTING_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_COMPAREITEM_callback_T WM_COMPAREITEM_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CONTEXTMENU_callback_T WM_CONTEXTMENU_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_COPY_callback_T WM_COPY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_COPYDATA_callback_T WM_COPYDATA_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_COPYGLOBALDATA_callback_T WM_COPYGLOBALDATA_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CREATE_callback_T WM_CREATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CTLCOLORBTN_callback_T WM_CTLCOLORBTN_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CTLCOLORDLG_callback_T WM_CTLCOLORDLG_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CTLCOLOREDIT_callback_T WM_CTLCOLOREDIT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CTLCOLORLISTBOX_callback_T WM_CTLCOLORLISTBOX_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CTLCOLORMSGBOX_callback_T WM_CTLCOLORMSGBOX_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CTLCOLORSCROLLBAR_callback_T WM_CTLCOLORSCROLLBAR_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CTLCOLORSTATIC_callback_T WM_CTLCOLORSTATIC_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CUT_callback_T WM_CUT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DEADCHAR_callback_T WM_DEADCHAR_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DELETEITEM_callback_T WM_DELETEITEM_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DESTROY_callback_T WM_DESTROY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DESTROYCLIPBOARD_callback_T WM_DESTROYCLIPBOARD_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DEVICECHANGE_callback_T WM_DEVICECHANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DEVMODECHANGE_callback_T WM_DEVMODECHANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DISPLAYCHANGE_callback_T WM_DISPLAYCHANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DPICHANGED_callback_T WM_DPICHANGED_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DPICHANGED_AFTERPARENT_callback_T WM_DPICHANGED_AFTERPARENT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DPICHANGED_BEFOREPARENT_callback_T WM_DPICHANGED_BEFOREPARENT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DRAWCLIPBOARD_callback_T WM_DRAWCLIPBOARD_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DRAWITEM_callback_T WM_DRAWITEM_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DROPFILES_callback_T WM_DROPFILES_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DWMCOLORIZATIONCOLORCHANGED_callback_T WM_DWMCOLORIZATIONCOLORCHANGED_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DWMCOMPOSITIONCHANGED_callback_T WM_DWMCOMPOSITIONCHANGED_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DWMNCRENDERINGCHANGED_callback_T WM_DWMNCRENDERINGCHANGED_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DWMSENDICONICLIVEPREVIEWBITMAP_callback_T WM_DWMSENDICONICLIVEPREVIEWBITMAP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DWMSENDICONICTHUMBNAIL_callback_T WM_DWMSENDICONICTHUMBNAIL_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_DWMWINDOWMAXIMIZEDCHANGE_callback_T WM_DWMWINDOWMAXIMIZEDCHANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_ENABLE_callback_T WM_ENABLE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_ENDSESSION_callback_T WM_ENDSESSION_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_ENTERIDLE_callback_T WM_ENTERIDLE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_ENTERMENULOOP_callback_T WM_ENTERMENULOOP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_ENTERSIZEMOVE_callback_T WM_ENTERSIZEMOVE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_ERASEBKGND_callback_T WM_ERASEBKGND_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_EXITMENULOOP_callback_T WM_EXITMENULOOP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_EXITSIZEMOVE_callback_T WM_EXITSIZEMOVE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_FONTCHANGE_callback_T WM_FONTCHANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_GESTURE_callback_T WM_GESTURE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_GESTURENOTIFY_callback_T WM_GESTURENOTIFY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_GETDLGCODE_callback_T WM_GETDLGCODE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_GETDPISCALEDSIZE_callback_T WM_GETDPISCALEDSIZE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_GETFONT_callback_T WM_GETFONT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_GETHOTKEY_callback_T WM_GETHOTKEY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_GETICON_callback_T WM_GETICON_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_GETMINMAXINFO_callback_T WM_GETMINMAXINFO_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_GETOBJECT_callback_T WM_GETOBJECT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_GETTEXT_callback_T WM_GETTEXT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_GETTEXTLENGTH_callback_T WM_GETTEXTLENGTH_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_GETTITLEBARINFOEX_callback_T WM_GETTITLEBARINFOEX_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_HANDHELDFIRST_callback_T WM_HANDHELDFIRST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_HANDHELDLAST_callback_T WM_HANDHELDLAST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_HELP_callback_T WM_HELP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_HOTKEY_callback_T WM_HOTKEY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_HSCROLL_callback_T WM_HSCROLL_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_HSCROLLCLIPBOARD_callback_T WM_HSCROLLCLIPBOARD_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_ICONERASEBKGND_callback_T WM_ICONERASEBKGND_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_CHAR_callback_T WM_IME_CHAR_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_COMPOSITION_callback_T WM_IME_COMPOSITION_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_COMPOSITIONFULL_callback_T WM_IME_COMPOSITIONFULL_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_CONTROL_callback_T WM_IME_CONTROL_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_ENDCOMPOSITION_callback_T WM_IME_ENDCOMPOSITION_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_KEYDOWN_callback_T WM_IME_KEYDOWN_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_KEYLAST_callback_T WM_IME_KEYLAST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_KEYUP_callback_T WM_IME_KEYUP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_NOTIFY_callback_T WM_IME_NOTIFY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_REQUEST_callback_T WM_IME_REQUEST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_SELECT_callback_T WM_IME_SELECT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_SETCONTEXT_callback_T WM_IME_SETCONTEXT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_IME_STARTCOMPOSITION_callback_T WM_IME_STARTCOMPOSITION_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_INITDIALOG_callback_T WM_INITDIALOG_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_INITMENU_callback_T WM_INITMENU_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_INITMENUPOPUP_callback_T WM_INITMENUPOPUP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		// WM_INPUT_callback_T WM_INPUT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_RAW_INPUT_MOUSE_callback_T WM_RAW_INPUT_MOUSE_callback = [](win_cpp::RawInputType, const win_cpp::RawInputMouseData&) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_RAW_INPUT_KEYBOARD_callback_T WM_RAW_INPUT_KEYBOARD_callback = [](win_cpp::RawInputType, const win_cpp::RawInputKeyboardData&) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_RAW_INPUT_HID_callback_T WM_RAW_INPUT_HID_callback = [](win_cpp::RawInputType, const win_cpp::RawInputHIDData&) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_INPUTLANGCHANGE_callback_T WM_INPUTLANGCHANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_INPUTLANGCHANGEREQUEST_callback_T WM_INPUTLANGCHANGEREQUEST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_INPUT_DEVICE_CHANGE_callback_T WM_INPUT_DEVICE_CHANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_INTERCEPTED_WINDOW_ACTION_callback_T WM_INTERCEPTED_WINDOW_ACTION_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_KEYDOWN_callback_T WM_KEYDOWN_callback = [](win_cpp::VirtualKeysStandardSet, const WindowsKeyData&) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_KEYFIRST_callback_T WM_KEYFIRST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_KEYLAST_callback_T WM_KEYLAST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_KEYUP_callback_T WM_KEYUP_callback = [](win_cpp::VirtualKeysStandardSet, const WindowsKeyData&) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_KILLFOCUS_callback_T WM_KILLFOCUS_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_LBUTTONDBLCLK_callback_T WM_LBUTTONDBLCLK_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_LBUTTONDOWN_callback_T WM_LBUTTONDOWN_callback = [](const std::pair<short, short>&, win_cpp::MouseKeysFlags) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_LBUTTONUP_callback_T WM_LBUTTONUP_callback = [](const std::pair<short, short>&, win_cpp::MouseKeysFlags) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MBUTTONDBLCLK_callback_T WM_MBUTTONDBLCLK_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MBUTTONDOWN_callback_T WM_MBUTTONDOWN_callback = [](const std::pair<short, short>&, win_cpp::MouseKeysFlags) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MBUTTONUP_callback_T WM_MBUTTONUP_callback = [](const std::pair<short, short>&, win_cpp::MouseKeysFlags) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MDIACTIVATE_callback_T WM_MDIACTIVATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MDICASCADE_callback_T WM_MDICASCADE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MDICREATE_callback_T WM_MDICREATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MDIDESTROY_callback_T WM_MDIDESTROY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MDIGETACTIVE_callback_T WM_MDIGETACTIVE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MDIICONARRANGE_callback_T WM_MDIICONARRANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MDIMAXIMIZE_callback_T WM_MDIMAXIMIZE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MDINEXT_callback_T WM_MDINEXT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MDIREFRESHMENU_callback_T WM_MDIREFRESHMENU_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MDIRESTORE_callback_T WM_MDIRESTORE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MDISETMENU_callback_T WM_MDISETMENU_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MDITILE_callback_T WM_MDITILE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MEASUREITEM_callback_T WM_MEASUREITEM_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MENUCHAR_callback_T WM_MENUCHAR_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MENUCOMMAND_callback_T WM_MENUCOMMAND_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MENUDRAG_callback_T WM_MENUDRAG_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MENUGETOBJECT_callback_T WM_MENUGETOBJECT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MENURBUTTONUP_callback_T WM_MENURBUTTONUP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MENUSELECT_callback_T WM_MENUSELECT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MOUSEACTIVATE_callback_T WM_MOUSEACTIVATE_callback = [](win_cpp::WindowMessage, win_cpp::HitTest) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MOUSEFIRST_callback_T WM_MOUSEFIRST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MOUSEHOVER_callback_T WM_MOUSEHOVER_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MOUSEHWHEEL_callback_T WM_MOUSEHWHEEL_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MOUSELAST_callback_T WM_MOUSELAST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MOUSELEAVE_callback_T WM_MOUSELEAVE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MOUSEMOVE_callback_T WM_MOUSEMOVE_callback = [](const std::pair<short, short>&, win_cpp::MouseKeysFlags) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MOUSEWHEEL_callback_T WM_MOUSEWHEEL_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MOVE_callback_T WM_MOVE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_MOVING_callback_T WM_MOVING_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCACTIVATE_callback_T WM_NCACTIVATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCCALCSIZE_callback_T WM_NCCALCSIZE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCCREATE_callback_T WM_NCCREATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCDESTROY_callback_T WM_NCDESTROY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCHITTEST_callback_T WM_NCHITTEST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCLBUTTONDBLCLK_callback_T WM_NCLBUTTONDBLCLK_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCLBUTTONDOWN_callback_T WM_NCLBUTTONDOWN_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCLBUTTONUP_callback_T WM_NCLBUTTONUP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCMBUTTONDBLCLK_callback_T WM_NCMBUTTONDBLCLK_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCMBUTTONDOWN_callback_T WM_NCMBUTTONDOWN_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCMBUTTONUP_callback_T WM_NCMBUTTONUP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCMOUSEHOVER_callback_T WM_NCMOUSEHOVER_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCMOUSELEAVE_callback_T WM_NCMOUSELEAVE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCMOUSEMOVE_callback_T WM_NCMOUSEMOVE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCPAINT_callback_T WM_NCPAINT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCPOINTERDOWN_callback_T WM_NCPOINTERDOWN_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCPOINTERUP_callback_T WM_NCPOINTERUP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCPOINTERUPDATE_callback_T WM_NCPOINTERUPDATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCRBUTTONDBLCLK_callback_T WM_NCRBUTTONDBLCLK_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCRBUTTONDOWN_callback_T WM_NCRBUTTONDOWN_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCRBUTTONUP_callback_T WM_NCRBUTTONUP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCXBUTTONDBLCLK_callback_T WM_NCXBUTTONDBLCLK_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCXBUTTONDOWN_callback_T WM_NCXBUTTONDOWN_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NCXBUTTONUP_callback_T WM_NCXBUTTONUP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NEXTDLGCTL_callback_T WM_NEXTDLGCTL_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NEXTMENU_callback_T WM_NEXTMENU_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NOTIFY_callback_T WM_NOTIFY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NOTIFYFORMAT_callback_T WM_NOTIFYFORMAT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_NULL_callback_T WM_NULL_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_PAINT_callback_T WM_PAINT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_PAINTCLIPBOARD_callback_T WM_PAINTCLIPBOARD_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_PAINTICON_callback_T WM_PAINTICON_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_PALETTECHANGED_callback_T WM_PALETTECHANGED_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_PALETTEISCHANGING_callback_T WM_PALETTEISCHANGING_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_PARENTNOTIFY_callback_T WM_PARENTNOTIFY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_PASTE_callback_T WM_PASTE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_PENWINFIRST_callback_T WM_PENWINFIRST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_PENWINLAST_callback_T WM_PENWINLAST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERACTIVATE_callback_T WM_POINTERACTIVATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERCAPTURECHANGED_callback_T WM_POINTERCAPTURECHANGED_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERDEVICECHANGE_callback_T WM_POINTERDEVICECHANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERDEVICEINRANGE_callback_T WM_POINTERDEVICEINRANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERDEVICEOUTOFRANGE_callback_T WM_POINTERDEVICEOUTOFRANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERDOWN_callback_T WM_POINTERDOWN_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERENTER_callback_T WM_POINTERENTER_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERHWHEEL_callback_T WM_POINTERHWHEEL_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERLEAVE_callback_T WM_POINTERLEAVE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERROUTEDAWAY_callback_T WM_POINTERROUTEDAWAY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERROUTEDRELEASED_callback_T WM_POINTERROUTEDRELEASED_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERROUTEDTO_callback_T WM_POINTERROUTEDTO_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERUP_callback_T WM_POINTERUP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERUPDATE_callback_T WM_POINTERUPDATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POINTERWHEEL_callback_T WM_POINTERWHEEL_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POWER_callback_T WM_POWER_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_POWERBROADCAST_callback_T WM_POWERBROADCAST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_PRINT_callback_T WM_PRINT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_PRINTCLIENT_callback_T WM_PRINTCLIENT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_QUERYDRAGICON_callback_T WM_QUERYDRAGICON_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_QUERYENDSESSION_callback_T WM_QUERYENDSESSION_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_QUERYNEWPALETTE_callback_T WM_QUERYNEWPALETTE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_QUERYOPEN_callback_T WM_QUERYOPEN_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_QUERYUISTATE_callback_T WM_QUERYUISTATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_QUEUESYNC_callback_T WM_QUEUESYNC_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_QUIT_callback_T WM_QUIT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_RBUTTONDBLCLK_callback_T WM_RBUTTONDBLCLK_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_RBUTTONDOWN_callback_T WM_RBUTTONDOWN_callback = [](const std::pair<short, short>&, win_cpp::MouseKeysFlags) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_RBUTTONUP_callback_T WM_RBUTTONUP_callback = [](const std::pair<short, short>&, win_cpp::MouseKeysFlags) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_RENDERALLFORMATS_callback_T WM_RENDERALLFORMATS_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_RENDERFORMAT_callback_T WM_RENDERFORMAT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SETCURSOR_callback_T WM_SETCURSOR_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SETFOCUS_callback_T WM_SETFOCUS_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SETFONT_callback_T WM_SETFONT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SETHOTKEY_callback_T WM_SETHOTKEY_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SETICON_callback_T WM_SETICON_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SETREDRAW_callback_T WM_SETREDRAW_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SETTEXT_callback_T WM_SETTEXT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SHOWWINDOW_callback_T WM_SHOWWINDOW_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SIZE_callback_T WM_SIZE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SIZECLIPBOARD_callback_T WM_SIZECLIPBOARD_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SIZING_callback_T WM_SIZING_callback = [](win_cpp::Edges edges, win_cpp::Rect& rect) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SPOOLERSTATUS_callback_T WM_SPOOLERSTATUS_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_STYLECHANGED_callback_T WM_STYLECHANGED_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_STYLECHANGING_callback_T WM_STYLECHANGING_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SYNCPAINT_callback_T WM_SYNCPAINT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SYSCHAR_callback_T WM_SYSCHAR_callback = [](wchar_t, const WindowsKeyData&) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SYSCOLORCHANGE_callback_T WM_SYSCOLORCHANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SYSCOMMAND_callback_T WM_SYSCOMMAND_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SYSDEADCHAR_callback_T WM_SYSDEADCHAR_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SYSKEYDOWN_callback_T WM_SYSKEYDOWN_callback = [](win_cpp::VirtualKeysStandardSet, const WindowsKeyData&) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_SYSKEYUP_callback_T WM_SYSKEYUP_callback = [](win_cpp::VirtualKeysStandardSet, const WindowsKeyData&) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_TABLET_FIRST_callback_T WM_TABLET_FIRST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_TABLET_LAST_callback_T WM_TABLET_LAST_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_TCARD_callback_T WM_TCARD_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_THEMECHANGED_callback_T WM_THEMECHANGED_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_TIMECHANGE_callback_T WM_TIMECHANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_TIMER_callback_T WM_TIMER_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_TOOLTIPDISMISS_callback_T WM_TOOLTIPDISMISS_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_TOUCH_callback_T WM_TOUCH_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_TOUCHHITTESTING_callback_T WM_TOUCHHITTESTING_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_UNDO_callback_T WM_UNDO_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_UNICHAR_callback_T WM_UNICHAR_callback = [](unsigned codepoint, const win_cpp::WindowsKeyData& data) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_UNINITMENUPOPUP_callback_T WM_UNINITMENUPOPUP_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_UPDATEUISTATE_callback_T WM_UPDATEUISTATE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_USER_callback_T WM_USER_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_USERCHANGED_callback_T WM_USERCHANGED_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_VKEYTOITEM_callback_T WM_VKEYTOITEM_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_VSCROLL_callback_T WM_VSCROLL_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_VSCROLLCLIPBOARD_callback_T WM_VSCROLLCLIPBOARD_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_WINDOWPOSCHANGED_callback_T WM_WINDOWPOSCHANGED_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_WINDOWPOSCHANGING_callback_T WM_WINDOWPOSCHANGING_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_WININICHANGE_callback_T WM_WININICHANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_WTSSESSION_CHANGE_callback_T WM_WTSSESSION_CHANGE_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_XBUTTONDBLCLK_callback_T WM_XBUTTONDBLCLK_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_XBUTTONDOWN_callback_T WM_XBUTTONDOWN_callback = [](unsigned, const std::pair<short, short>&, win_cpp::MouseKeysFlags) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_XBUTTONUP_callback_T WM_XBUTTONUP_callback = [](unsigned, const std::pair<short, short>&, win_cpp::MouseKeysFlags) constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CHOOSEFONT_GETLOGFONT_callback_T WM_CHOOSEFONT_GETLOGFONT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CHOOSEFONT_SETFLAGS_callback_T WM_CHOOSEFONT_SETFLAGS_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };
		WM_CHOOSEFONT_SETLOGFONT_callback_T WM_CHOOSEFONT_SETLOGFONT_callback = []() constexpr noexcept -> win_cpp::window_proc_callback_result_type { return std::nullopt; };

	public:
		win::t::LRESULT windowProc(win::t::HWND hWnd, win::t::UINT uMsg, win::t::WPARAM wParam, win::t::LPARAM lParam);
#if 1
		template<win_cpp::WindowMessage MSG> void SetMessageFunc(auto&& F) {
			// std::lock_guard<AtomicFlagMutex> lk(mutex);
			if constexpr (MSG == win_cpp::WindowMessage::WM_UNKNOWN_ONE) { WM_UNKNOWN_ONE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_ACTIVATE) { WM_ACTIVATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_ACTIVATEAPP) { WM_ACTIVATEAPP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_AFXFIRST) { WM_AFXFIRST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_AFXLAST) { WM_AFXLAST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_APP) { WM_APP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_APPCOMMAND) { WM_APPCOMMAND_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_ASKCBFORMATNAME) { WM_ASKCBFORMATNAME_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CANCELJOURNAL) { WM_CANCELJOURNAL_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CANCELMODE) { WM_CANCELMODE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CAPTURECHANGED) { WM_CAPTURECHANGED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CHANGECBCHAIN) { WM_CHANGECBCHAIN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CHANGEUISTATE) { WM_CHANGEUISTATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CHAR) { WM_CHAR_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CHARTOITEM) { WM_CHARTOITEM_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CHILDACTIVATE) { WM_CHILDACTIVATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CLEAR) { WM_CLEAR_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CLIPBOARDUPDATE) { WM_CLIPBOARDUPDATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CLOAKED_STATE_CHANGED) { WM_CLOAKED_STATE_CHANGED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CLOSE) { WM_CLOSE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_COMMAND) { WM_COMMAND_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_COMMNOTIFY) { WM_COMMNOTIFY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_COMPACTING) { WM_COMPACTING_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_COMPAREITEM) { WM_COMPAREITEM_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CONTEXTMENU) { WM_CONTEXTMENU_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_COPY) { WM_COPY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_COPYDATA) { WM_COPYDATA_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_COPYGLOBALDATA) { WM_COPYGLOBALDATA_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CREATE) { WM_CREATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CTLCOLORBTN) { WM_CTLCOLORBTN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CTLCOLORDLG) { WM_CTLCOLORDLG_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CTLCOLOREDIT) { WM_CTLCOLOREDIT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CTLCOLORLISTBOX) { WM_CTLCOLORLISTBOX_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CTLCOLORMSGBOX) { WM_CTLCOLORMSGBOX_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CTLCOLORSCROLLBAR) { WM_CTLCOLORSCROLLBAR_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CTLCOLORSTATIC) { WM_CTLCOLORSTATIC_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CUT) { WM_CUT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DEADCHAR) { WM_DEADCHAR_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DELETEITEM) { WM_DELETEITEM_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DESTROY) { WM_DESTROY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DESTROYCLIPBOARD) { WM_DESTROYCLIPBOARD_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DEVICECHANGE) { WM_DEVICECHANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DEVMODECHANGE) { WM_DEVMODECHANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DISPLAYCHANGE) { WM_DISPLAYCHANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DPICHANGED) { WM_DPICHANGED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DPICHANGED_AFTERPARENT) { WM_DPICHANGED_AFTERPARENT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DPICHANGED_BEFOREPARENT) { WM_DPICHANGED_BEFOREPARENT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DRAWCLIPBOARD) { WM_DRAWCLIPBOARD_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DRAWITEM) { WM_DRAWITEM_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DROPFILES) { WM_DROPFILES_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DWMCOLORIZATIONCOLORCHANGED) { WM_DWMCOLORIZATIONCOLORCHANGED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DWMCOMPOSITIONCHANGED) { WM_DWMCOMPOSITIONCHANGED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DWMNCRENDERINGCHANGED) { WM_DWMNCRENDERINGCHANGED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DWMSENDICONICLIVEPREVIEWBITMAP) { WM_DWMSENDICONICLIVEPREVIEWBITMAP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DWMSENDICONICTHUMBNAIL) { WM_DWMSENDICONICTHUMBNAIL_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_DWMWINDOWMAXIMIZEDCHANGE) { WM_DWMWINDOWMAXIMIZEDCHANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_ENABLE) { WM_ENABLE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_ENDSESSION) { WM_ENDSESSION_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_ENTERIDLE) { WM_ENTERIDLE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_ENTERMENULOOP) { WM_ENTERMENULOOP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_ENTERSIZEMOVE) { WM_ENTERSIZEMOVE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_ERASEBKGND) { WM_ERASEBKGND_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_EXITMENULOOP) { WM_EXITMENULOOP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_EXITSIZEMOVE) { WM_EXITSIZEMOVE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_FONTCHANGE) { WM_FONTCHANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_GESTURE) { WM_GESTURE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_GESTURENOTIFY) { WM_GESTURENOTIFY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_GETDLGCODE) { WM_GETDLGCODE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_GETDPISCALEDSIZE) { WM_GETDPISCALEDSIZE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_GETFONT) { WM_GETFONT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_GETHOTKEY) { WM_GETHOTKEY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_GETICON) { WM_GETICON_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_GETMINMAXINFO) { WM_GETMINMAXINFO_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_GETOBJECT) { WM_GETOBJECT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_GETTEXT) { WM_GETTEXT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_GETTEXTLENGTH) { WM_GETTEXTLENGTH_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_GETTITLEBARINFOEX) { WM_GETTITLEBARINFOEX_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_HANDHELDFIRST) { WM_HANDHELDFIRST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_HANDHELDLAST) { WM_HANDHELDLAST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_HELP) { WM_HELP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_HOTKEY) { WM_HOTKEY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_HSCROLL) { WM_HSCROLL_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_HSCROLLCLIPBOARD) { WM_HSCROLLCLIPBOARD_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_ICONERASEBKGND) { WM_ICONERASEBKGND_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_CHAR) { WM_IME_CHAR_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_COMPOSITION) { WM_IME_COMPOSITION_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_COMPOSITIONFULL) { WM_IME_COMPOSITIONFULL_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_CONTROL) { WM_IME_CONTROL_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_ENDCOMPOSITION) { WM_IME_ENDCOMPOSITION_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_KEYDOWN) { WM_IME_KEYDOWN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_KEYLAST) { WM_IME_KEYLAST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_KEYUP) { WM_IME_KEYUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_NOTIFY) { WM_IME_NOTIFY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_REQUEST) { WM_IME_REQUEST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_SELECT) { WM_IME_SELECT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_SETCONTEXT) { WM_IME_SETCONTEXT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_IME_STARTCOMPOSITION) { WM_IME_STARTCOMPOSITION_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_INITDIALOG) { WM_INITDIALOG_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_INITMENU) { WM_INITMENU_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_INITMENUPOPUP) { WM_INITMENUPOPUP_callback = std::forward<decltype(F)>(F); return; }
			// if constexpr (MSG == win_cpp::WindowMessage::WM_INPUT) { WM_INPUT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_INPUTLANGCHANGE) { WM_INPUTLANGCHANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_INPUTLANGCHANGEREQUEST) { WM_INPUTLANGCHANGEREQUEST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_INPUT_DEVICE_CHANGE) { WM_INPUT_DEVICE_CHANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_INTERCEPTED_WINDOW_ACTION) { WM_INTERCEPTED_WINDOW_ACTION_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_KEYDOWN) { WM_KEYDOWN_callback = std::forward<decltype(F)>(F); return; }
			// if constexpr (MSG == win_cpp::WindowMessage::WM_KEYFIRST) { WM_KEYFIRST_callback = std::forward<decltype(F)>(F); return; }
			// if constexpr (MSG == win_cpp::WindowMessage::WM_KEYLAST) { WM_KEYLAST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_KEYUP) { WM_KEYUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_KILLFOCUS) { WM_KILLFOCUS_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_LBUTTONDBLCLK) { WM_LBUTTONDBLCLK_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_LBUTTONDOWN) { WM_LBUTTONDOWN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_LBUTTONUP) { WM_LBUTTONUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MBUTTONDBLCLK) { WM_MBUTTONDBLCLK_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MBUTTONDOWN) { WM_MBUTTONDOWN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MBUTTONUP) { WM_MBUTTONUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MDIACTIVATE) { WM_MDIACTIVATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MDICASCADE) { WM_MDICASCADE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MDICREATE) { WM_MDICREATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MDIDESTROY) { WM_MDIDESTROY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MDIGETACTIVE) { WM_MDIGETACTIVE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MDIICONARRANGE) { WM_MDIICONARRANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MDIMAXIMIZE) { WM_MDIMAXIMIZE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MDINEXT) { WM_MDINEXT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MDIREFRESHMENU) { WM_MDIREFRESHMENU_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MDIRESTORE) { WM_MDIRESTORE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MDISETMENU) { WM_MDISETMENU_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MDITILE) { WM_MDITILE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MEASUREITEM) { WM_MEASUREITEM_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MENUCHAR) { WM_MENUCHAR_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MENUCOMMAND) { WM_MENUCOMMAND_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MENUDRAG) { WM_MENUDRAG_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MENUGETOBJECT) { WM_MENUGETOBJECT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MENURBUTTONUP) { WM_MENURBUTTONUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MENUSELECT) { WM_MENUSELECT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MOUSEACTIVATE) { WM_MOUSEACTIVATE_callback = std::forward<decltype(F)>(F); return; }
//			if constexpr (MSG == win_cpp::WindowMessage::WM_MOUSEFIRST) { WM_MOUSEFIRST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MOUSEHOVER) { WM_MOUSEHOVER_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MOUSEHWHEEL) { WM_MOUSEHWHEEL_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MOUSELAST) { WM_MOUSELAST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MOUSELEAVE) { WM_MOUSELEAVE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MOUSEMOVE) { WM_MOUSEMOVE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MOUSEWHEEL) { WM_MOUSEWHEEL_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MOVE) { WM_MOVE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_MOVING) { WM_MOVING_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCACTIVATE) { WM_NCACTIVATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCCALCSIZE) { WM_NCCALCSIZE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCCREATE) { WM_NCCREATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCDESTROY) { WM_NCDESTROY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCHITTEST) { WM_NCHITTEST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCLBUTTONDBLCLK) { WM_NCLBUTTONDBLCLK_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCLBUTTONDOWN) { WM_NCLBUTTONDOWN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCLBUTTONUP) { WM_NCLBUTTONUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCMBUTTONDBLCLK) { WM_NCMBUTTONDBLCLK_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCMBUTTONDOWN) { WM_NCMBUTTONDOWN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCMBUTTONUP) { WM_NCMBUTTONUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCMOUSEHOVER) { WM_NCMOUSEHOVER_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCMOUSELEAVE) { WM_NCMOUSELEAVE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCMOUSEMOVE) { WM_NCMOUSEMOVE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCPAINT) { WM_NCPAINT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCPOINTERDOWN) { WM_NCPOINTERDOWN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCPOINTERUP) { WM_NCPOINTERUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCPOINTERUPDATE) { WM_NCPOINTERUPDATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCRBUTTONDBLCLK) { WM_NCRBUTTONDBLCLK_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCRBUTTONDOWN) { WM_NCRBUTTONDOWN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCRBUTTONUP) { WM_NCRBUTTONUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCXBUTTONDBLCLK) { WM_NCXBUTTONDBLCLK_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCXBUTTONDOWN) { WM_NCXBUTTONDOWN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NCXBUTTONUP) { WM_NCXBUTTONUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NEXTDLGCTL) { WM_NEXTDLGCTL_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NEXTMENU) { WM_NEXTMENU_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NOTIFY) { WM_NOTIFY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NOTIFYFORMAT) { WM_NOTIFYFORMAT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_NULL) { WM_NULL_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_PAINT) { WM_PAINT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_PAINTCLIPBOARD) { WM_PAINTCLIPBOARD_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_PAINTICON) { WM_PAINTICON_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_PALETTECHANGED) { WM_PALETTECHANGED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_PALETTEISCHANGING) { WM_PALETTEISCHANGING_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_PARENTNOTIFY) { WM_PARENTNOTIFY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_PASTE) { WM_PASTE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_PENWINFIRST) { WM_PENWINFIRST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_PENWINLAST) { WM_PENWINLAST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERACTIVATE) { WM_POINTERACTIVATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERCAPTURECHANGED) { WM_POINTERCAPTURECHANGED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERDEVICECHANGE) { WM_POINTERDEVICECHANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERDEVICEINRANGE) { WM_POINTERDEVICEINRANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERDEVICEOUTOFRANGE) { WM_POINTERDEVICEOUTOFRANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERDOWN) { WM_POINTERDOWN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERENTER) { WM_POINTERENTER_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERHWHEEL) { WM_POINTERHWHEEL_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERLEAVE) { WM_POINTERLEAVE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERROUTEDAWAY) { WM_POINTERROUTEDAWAY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERROUTEDRELEASED) { WM_POINTERROUTEDRELEASED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERROUTEDTO) { WM_POINTERROUTEDTO_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERUP) { WM_POINTERUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERUPDATE) { WM_POINTERUPDATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POINTERWHEEL) { WM_POINTERWHEEL_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POWER) { WM_POWER_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_POWERBROADCAST) { WM_POWERBROADCAST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_PRINT) { WM_PRINT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_PRINTCLIENT) { WM_PRINTCLIENT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_QUERYDRAGICON) { WM_QUERYDRAGICON_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_QUERYENDSESSION) { WM_QUERYENDSESSION_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_QUERYNEWPALETTE) { WM_QUERYNEWPALETTE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_QUERYOPEN) { WM_QUERYOPEN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_QUERYUISTATE) { WM_QUERYUISTATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_QUEUESYNC) { WM_QUEUESYNC_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_QUIT) { WM_QUIT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_RBUTTONDBLCLK) { WM_RBUTTONDBLCLK_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_RBUTTONDOWN) { WM_RBUTTONDOWN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_RBUTTONUP) { WM_RBUTTONUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_RENDERALLFORMATS) { WM_RENDERALLFORMATS_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_RENDERFORMAT) { WM_RENDERFORMAT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SETCURSOR) { WM_SETCURSOR_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SETFOCUS) { WM_SETFOCUS_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SETFONT) { WM_SETFONT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SETHOTKEY) { WM_SETHOTKEY_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SETICON) { WM_SETICON_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SETREDRAW) { WM_SETREDRAW_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SETTEXT) { WM_SETTEXT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SHOWWINDOW) { WM_SHOWWINDOW_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SIZE) { WM_SIZE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SIZECLIPBOARD) { WM_SIZECLIPBOARD_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SIZING) { WM_SIZING_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SPOOLERSTATUS) { WM_SPOOLERSTATUS_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_STYLECHANGED) { WM_STYLECHANGED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_STYLECHANGING) { WM_STYLECHANGING_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SYNCPAINT) { WM_SYNCPAINT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SYSCHAR) { WM_SYSCHAR_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SYSCOLORCHANGE) { WM_SYSCOLORCHANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SYSCOMMAND) { WM_SYSCOMMAND_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SYSDEADCHAR) { WM_SYSDEADCHAR_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SYSKEYDOWN) { WM_SYSKEYDOWN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_SYSKEYUP) { WM_SYSKEYUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_TABLET_FIRST) { WM_TABLET_FIRST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_TABLET_LAST) { WM_TABLET_LAST_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_TCARD) { WM_TCARD_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_THEMECHANGED) { WM_THEMECHANGED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_TIMECHANGE) { WM_TIMECHANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_TIMER) { WM_TIMER_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_TOOLTIPDISMISS) { WM_TOOLTIPDISMISS_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_TOUCH) { WM_TOUCH_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_TOUCHHITTESTING) { WM_TOUCHHITTESTING_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_UNDO) { WM_UNDO_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_UNICHAR) { WM_UNICHAR_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_UNINITMENUPOPUP) { WM_UNINITMENUPOPUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_UPDATEUISTATE) { WM_UPDATEUISTATE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_USER) { WM_USER_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_USERCHANGED) { WM_USERCHANGED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_VKEYTOITEM) { WM_VKEYTOITEM_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_VSCROLL) { WM_VSCROLL_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_VSCROLLCLIPBOARD) { WM_VSCROLLCLIPBOARD_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_WINDOWPOSCHANGED) { WM_WINDOWPOSCHANGED_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_WINDOWPOSCHANGING) { WM_WINDOWPOSCHANGING_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_WININICHANGE) { WM_WININICHANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_WTSSESSION_CHANGE) { WM_WTSSESSION_CHANGE_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_XBUTTONDBLCLK) { WM_XBUTTONDBLCLK_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_XBUTTONDOWN) { WM_XBUTTONDOWN_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_XBUTTONUP) { WM_XBUTTONUP_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CHOOSEFONT_GETLOGFONT) { WM_CHOOSEFONT_GETLOGFONT_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CHOOSEFONT_SETFLAGS) { WM_CHOOSEFONT_SETFLAGS_callback = std::forward<decltype(F)>(F); return; }
			if constexpr (MSG == win_cpp::WindowMessage::WM_CHOOSEFONT_SETLOGFONT) { WM_CHOOSEFONT_SETLOGFONT_callback = std::forward<decltype(F)>(F); return; }
			// if constexpr (MSG == win_cpp::WindowMessage::WM_SETTINGCHANGE) { WM_SETTINGCHANGE_callback = std::forward<decltype(F)>(F); return; }
		} // SetWindowMessageFunc
#endif
	};

	using win::f::PostQuitMessage;
	
	template<typename T> concept is_pointer = std::is_pointer_v<T>;

#if 0
	using win::f::GetPropW; // REMOVE IT
	using win::t::UINT; // REMOVE IT
	using win::t::WPARAM; // REMOVE IT
	using win::t::LPARAM; // REMOVE IT
	using win::t::LRESULT; // REMOVE IT
#endif
	using win::t::HWND; // REMOVE IT
	using win::t::HINSTANCE; // REMOVE IT

	win::t::LRESULT windowProc(win::t::HWND hWnd, win::t::UINT uMsg, win::t::WPARAM wParam, win::t::LPARAM lParam) {
		return win::f::DefWindowProcW(static_cast<win::t::HWND>(hWnd), uMsg, wParam, lParam);
	}

	void SetStdOutMode(C_File_Options mode) {
//		win::f::set_stdio_mode(std::to_underlying(mode));
	}

	bool SystemParametersInfoUnicode(win_cpp::SystemParametersInfoValues uiAction, unsigned uiParam, void* pvParam, unsigned fWinIni) {
		unsigned uiAction_ = std::to_underlying(uiAction);
		return win::f::SystemParametersInfoW(uiAction_, uiParam, pvParam, fWinIni);
	}

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
		auto x = win::f::LOWORD(lParam);
		auto y = win::f::HIWORD(lParam);
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

	struct Instance {
		public:
			using type = win::t::HINSTANCE;

		private:
			type _instance = nullptr;

		public:
			explicit operator type() const { return _instance; }

		public:
			Instance() : _instance(win::f::GetModuleHandleW(0)) {}
			Instance(std::wstring_view module_name) : _instance(win::f::GetModuleHandleW(module_name.data())) {}
			Instance(std::string_view module_name) : _instance(win::f::GetModuleHandleA(module_name.data())) {}
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
		ii.hbmMask = BitmapMaskHandle::type(mask);
		ii.hbmColor = BitmapColorHandle::type(color);
		return win::f::CreateIconIndirect(&ii);
	}

	struct LoadImageInfo {
		int cx = 0;
		int cy = 0;
		win::e::LR_Flags fuLoad;
	};

	struct LoadImageStandardInfo : LoadImageInfo {};

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
		win::t::HINSTANCE hInst = nullptr;
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
		win::t::HINSTANCE hInst = nullptr;
		win::t::LPCWSTR name =
				win::f::MAKEINTRESOURCE(
					std::to_underlying(info.standard_cursor)
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
		using type = win::t::HICON;
		explicit operator type() const { return icon_handle; }

	private:
		type icon_handle;

	public:
		Icon() : icon_handle(nullptr) {}

		Icon(const BitmapColorHandle& color, const BitmapMaskHandle& mask, const IconCreateInfo& info)
			: icon_handle(CreateIconIndirect(color, mask, info))
		{}

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
	};

	struct MainClassCreateInfo {
		private:
			win::t::WNDPROC wnd_proc = win_cpp::windowProc;

		public:
			win::e::WindowClassStyle window_style;
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
		if (!hInstance) { throw; }
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

	// void RegisterRawInputDevice(const Window& window, RawInputDevFunc dev_func, HIDUsagePage usage_page, AllowedEnum auto hid_usage);
	
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

	auto dummy_window_proc = [](win::t::HWND hWnd, win::t::UINT uMsg, win::t::WPARAM wParam, win::t::LPARAM lParam) -> win::t::LRESULT {
		return win::f::DefWindowProcW(hWnd, uMsg, wParam, lParam);
	};



	auto thin_window_proc = [](win::t::HWND hWnd, win::t::UINT uMsg, win::t::WPARAM wParam, win::t::LPARAM lParam) -> win::t::LRESULT {
		using CBH_T = win_cpp::CallbackHolder;
		using P_CBH_T = std::add_pointer_t<CBH_T>;
		auto userdata = std::to_underlying(win::e::WindowFieldsOffset::GWL_USERDATA);
		auto void_ptr = win::f::GetWindowLongPtrW(hWnd, userdata);
		if (!void_ptr) { throw; }
		P_CBH_T pcbh = reinterpret_cast<P_CBH_T>(void_ptr);
		auto& cbh = *pcbh;
		return std::invoke(&CBH_T::windowProc, cbh, hWnd, uMsg, wParam, lParam);
	};

	struct Window;

	win::t::MSG PeekMessageWithoutRemove();
	win::t::MSG GetMessage(const Window& window);
	win::t::MSG GetMessage();
	win::t::MSG PeekMessage(const Window& window);
	win::t::MSG PeekMessageWithRemove();

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

	void message_process(const std::stop_token& stoken) {
		win_cpp::Message msg = {};
		while (!stoken.stop_requested()) {
			auto wmsg = msg.peek_msg_without_remove();
			if (wmsg == win_cpp::WindowMessage::WM_NULL) {
				continue;
			}
			if (wmsg == win_cpp::WindowMessage::WM_QUIT) {
				break;
			}
			msg.translate();
			msg.dispatch();
		}
	}

	struct Window {
		using type = win::t::HWND;
		explicit operator type() const { return window_handle; }

	private:
		win::t::HWND window_handle;
		std::jthread process;

	private:
		win_cpp::windowproc_f GetWindowProc() {
			auto x = std::to_underlying(win::e::WindowFieldsOffset::GWL_WNDPROC);
			auto y = win::f::GetWindowLongPtrW(window_handle, x);
			return reinterpret_cast<win_cpp::windowproc_f>(y);
		}

		void* GetWindowUserptr() const {
			auto field_offset = std::to_underlying(win::e::WindowFieldsOffset::GWL_USERDATA);
			return reinterpret_cast<void*>(win::f::GetWindowLongPtrW(window_handle, field_offset));
		}

		void SetWindowProc(windowproc_f func) const { // what if is set
			auto field_offset = std::to_underlying(win::e::WindowFieldsOffset::GWL_WNDPROC);
			win::f::SetWindowLongPtrW(window_handle, field_offset, reinterpret_cast<win::t::LONG_PTR>(func));
		}

		void SetWindowUserptr(void* ptr) const { // what if is set
			auto field_offset = std::to_underlying(win::e::WindowFieldsOffset::GWL_USERDATA);
			win::f::SetWindowLongPtrW(window_handle, field_offset, reinterpret_cast<win::t::LONG_PTR>(ptr));
		}

	public:
		Window(const WindowCreateInfo& info) : window_handle(0), process() {
			std::promise<void> pr;
			auto future = pr.get_future();
			process = std::jthread([this, info, promise = std::move(pr)](std::stop_token stoken) mutable {
					window_handle = CreateWindowExW(info);
					win_cpp::CallbackHolder callbacks;
					SetWindowUserptr(&callbacks);
					SetWindowProc(thin_window_proc);
					promise.set_value();
					message_process(stoken);
					SetWindowProc(windowProc);
					SetWindowUserptr(nullptr);
				}
			);
			future.wait();
		}

		// Window() : Window(WindowCreateInfo{}) {} // empty instance warning

		~Window() {
			if (!process.joinable()) {
				process.request_stop();
			}
			if (window_handle) {
				win::f::DestroyWindow(window_handle);
			}
		}
		Window(const Window&) = delete;
		Window(Window&& wnd)
			: window_handle(std::exchange(wnd.window_handle, nullptr))
			, process(std::exchange(wnd.process, {})) {
		}
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&& wnd) { 
			if (&wnd == this) { return *this; }
			window_handle = std::exchange(wnd.window_handle, {});
			process = std::exchange(wnd.process, {});
			return *this;
		};

#if 1
		template<win_cpp::WindowMessage MSG> void SetWindowMessageCallback(auto&& F) const {
			using CBH_T = win_cpp::CallbackHolder;
			using P_CBH_T = std::add_pointer_t<CBH_T>;
			auto void_ptr = GetWindowUserptr();
			if (!void_ptr) { throw; }
			P_CBH_T cbh_ptr = static_cast<P_CBH_T>(void_ptr);
			auto& cbh = *cbh_ptr;
			cbh.SetMessageFunc<MSG>(std::forward<decltype(F)>(F));
		}
#endif

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

		std::pair<long, long> ClientToScreen(const std::pair<long, long>& pxy) const {
			auto&& [x, y] = pxy;
			win::t::POINT p{x, y};
			win::f::ClientToScreen(window_handle, &p);
			return std::make_pair(p.x, p.y);
		}

		std::pair<long, long> ClientToScreen(long x, long y) const {
			win::t::POINT p{ x, y };
			win::f::ClientToScreen(window_handle, &p);
			return std::make_pair(p.x, p.y);
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

		bool IsThePointCapturedByTheWindowRegion(long, long) const;

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

	void SetPropW(const Window& window, std::wstring_view name, is_pointer auto p) {
		auto res = win::f::SetPropW(win_cpp::Window::type(window), name.data(), p);
		if (!res) { throw; }
	}

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


	win::t::MSG PeekMessageWithoutRemove() {
		win::t::MSG msg = {};
		constexpr int PM_NOREMOVE = 0;
		win::f::PeekMessageA(&msg, nullptr, 0, 0, PM_NOREMOVE);
		return msg;
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

	void RegisterRawInputDevice(const Window& window, RawInputDevFunc dev_func, HIDUsagePage usage_page, AllowedEnum auto hid_usage) {
		win::t::RAWINPUTDEVICE rid = {
			.usUsagePage = std::to_underlying(usage_page),
			.usUsage = std::to_underlying(hid_usage),
			.dwFlags = RawInputDevFunc::MaskType(dev_func),
			.hwndTarget = Window::type(window)
		};
		auto res = win::f::RegisterRawInputDevices(&rid, 1, sizeof(rid));
		if (!res) {
			throw;
		}
	}

	void UnRegisterRawInputDevice(HIDUsagePage usage_page, AllowedEnum auto hid_usage) {
		constexpr win_cpp::RawInputDevFunc v = win_cpp::RawInputDevFunc::values::RIDEV_REMOVE;
		constexpr auto flag = win_cpp::RawInputDevFunc::MaskType(v);
		win::t::RAWINPUTDEVICE rid = {
			.usUsagePage = std::to_underlying(usage_page),
			.usUsage = std::to_underlying(hid_usage),
			.dwFlags = flag,
			.hwndTarget = nullptr
		};

		auto res = win::f::RegisterRawInputDevices(&rid, 1, sizeof(rid));
		if (!res) {
			throw;
		}
	}

	struct MouseRawInput {
		public:
			MouseRawInput(const Window& window) {
				auto dev_func = win_cpp::RawInputDevFunc{};
				auto usage_page = win_cpp::hid::HIDUsagePage::GENERIC;
				auto hid_usage = win_cpp::hid::HID_USAGE_GENERIC::MOUSE;
				RegisterRawInputDevice(window, dev_func, usage_page, hid_usage);
			}

			~MouseRawInput() {
				auto usage_page = win_cpp::hid::HIDUsagePage::GENERIC;
				auto hid_usage = win_cpp::hid::HID_USAGE_GENERIC::MOUSE;
				UnRegisterRawInputDevice(usage_page, hid_usage);
			}
	};

	enum class RawInputDeviceTypeStructSize : unsigned {
		MouseStructSize = 24u, // sizeof(win::t::RAWMOUSE),
		KeyboardStructSize = 16u, // sizeof(win::t::RAWKEYBOARD),
		HIDStructSize = 12u, // sizeof(win::t::RAWHID),
	};

	using RawInputDeviceTypeStructSize_to_RawInputDeviceType = std::unordered_map<win_cpp::RawInputDeviceTypeStructSize, win_cpp::RawInputDeviceType>;
	RawInputDeviceTypeStructSize_to_RawInputDeviceType convert_RawInputDeviceTypeStructSize_to_RawInputDeviceType = {
		{ win_cpp::RawInputDeviceTypeStructSize::MouseStructSize, win_cpp::RawInputDeviceType::RIM_TYPEMOUSE },
		{ win_cpp::RawInputDeviceTypeStructSize::KeyboardStructSize, win_cpp::RawInputDeviceType::RIM_TYPEKEYBOARD },
		{ win_cpp::RawInputDeviceTypeStructSize::HIDStructSize, win_cpp::RawInputDeviceType::RIM_TYPEHID },
	};
	using RawInputDeviceType_to_RawInputDeviceTypeStructSize = std::unordered_map<RawInputDeviceType, RawInputDeviceTypeStructSize>;
	RawInputDeviceType_to_RawInputDeviceTypeStructSize convert_RawInputDeviceType_to_RawInputDeviceTypeStructSize = {
		{ win_cpp::RawInputDeviceType::RIM_TYPEMOUSE, win_cpp::RawInputDeviceTypeStructSize::MouseStructSize },
		{ win_cpp::RawInputDeviceType::RIM_TYPEKEYBOARD, win_cpp::RawInputDeviceTypeStructSize::KeyboardStructSize},
		{ win_cpp::RawInputDeviceType::RIM_TYPEHID, win_cpp::RawInputDeviceTypeStructSize::HIDStructSize},
	};

	using RawInputHandle = win::t::HRAWINPUT;
	win_cpp::RawInputDeviceType GetRawInputDeviceType(RawInputHandle handle) { // , RawInputDeviceStructType uiCommand
		unsigned size = 0;
		constexpr win::t::RAWINPUT* data = nullptr;
		constexpr win::t::UINT cbSizeHeader = sizeof(win::t::RAWINPUTHEADER);
		constexpr unsigned st = std::to_underlying(win_cpp::RawInputDeviceStructType::RID_HEADER);
		std::ignore = win::f::GetRawInputData(handle, st, data, &size, cbSizeHeader);
		constexpr unsigned MouseStructSize = sizeof(win::t::RAWMOUSE);
		constexpr unsigned KeyboardStructSize = sizeof(win::t::RAWKEYBOARD);
		constexpr unsigned HIDStructSize = sizeof(win::t::RAWHID);
		auto x = static_cast<RawInputDeviceTypeStructSize>(size);
		auto res = convert_RawInputDeviceTypeStructSize_to_RawInputDeviceType.find(x);
		auto end = convert_RawInputDeviceTypeStructSize_to_RawInputDeviceType.end();
		if (res != end) {
			return res->second;
		}
		throw;
	}
	
	struct RawInputMouseData {
		std::pair<long, long> lLastXY;
		MouseIndicatorFlags dwFlags;
		RawInputMouseButtonsFlags usButtonFlags;
		unsigned short usButtonData; // if mouse wheel flag is a distance
		unsigned long ulRawButtons; 
		unsigned long ulExtraInformation;
		bool IsPenEvent;
	};
	using RawInputMouseHandle = RawInputHandle;
	RawInputMouseData GetRawInputMouseData(RawInputMouseHandle handle) {
		constexpr unsigned uiCommand = std::to_underlying(RawInputDeviceStructType::RID_HEADER);
		unsigned size = static_cast<unsigned>(win_cpp::RawInputDeviceTypeStructSize::MouseStructSize);
		win::t::RAWINPUT data;
		constexpr win::t::UINT cbSizeHeader = sizeof(win::t::RAWINPUTHEADER);
		std::ignore = win::f::GetRawInputData(handle, uiCommand, &data, &size, cbSizeHeader);
		
		auto dwFlags = win_cpp::MouseIndicatorFlags(data.data.mouse.usFlags);
		unsigned long ulRawButtons = data.data.mouse.ulRawButtons;
		auto usButtonFlags = win_cpp::RawInputMouseButtonsFlags(data.data.mouse.usButtonFlags);
		unsigned short usButtonData = data.data.mouse.usButtonData;
		unsigned long ulExtraInformation = (data.data.mouse.ulExtraInformation);
		constexpr unsigned MI_WP_SIGNATURE = 0xFF515700;
		constexpr unsigned SIGNATURE_MASK = 0xFFFFFF00;
		bool IsPenEvent = ((ulExtraInformation & SIGNATURE_MASK) == MI_WP_SIGNATURE);

		RawInputMouseData m_data = {
			{ data.data.mouse.lLastX, data.data.mouse.lLastY },
			dwFlags,
			usButtonFlags,
			usButtonData,
			ulExtraInformation,
			IsPenEvent
		};

		return m_data;
	}

	struct RawInputKeyboardData {
		win_cpp::WindowsScancode scancode;
		win_cpp::KeyboardInputDataTypeFlags Flags;
		win_cpp::VirtualKeysStandardSet vk;
		unsigned long ExtraInformation;
		// bool state; // 0 is release; 1 is pressed
		win_cpp::WindowMessage message;
	};
	using RawInputKeyboardHandle = RawInputHandle;
	RawInputKeyboardData GetRawInputKeyboardData(RawInputKeyboardHandle handle) {
		constexpr unsigned uiCommand = std::to_underlying(RawInputDeviceStructType::RID_HEADER);
		unsigned size = static_cast<unsigned>(win_cpp::RawInputDeviceTypeStructSize::KeyboardStructSize);
		win::t::RAWINPUT data;
		constexpr win::t::UINT cbSizeHeader = sizeof(win::t::RAWINPUTHEADER);
		std::ignore = win::f::GetRawInputData(handle, uiCommand, &data, &size, cbSizeHeader);
		win_cpp::WindowsScancode scancode = static_cast<win_cpp::WindowsScancode>(data.data.keyboard.MakeCode);
		win_cpp::KeyboardInputDataTypeFlags flags = KeyboardInputDataTypeFlags(data.data.keyboard.Flags);
		win_cpp::VirtualKeysStandardSet vk = static_cast<win_cpp::VirtualKeysStandardSet>(data.data.keyboard.VKey);
		unsigned long ExtraInformation = data.data.keyboard.ExtraInformation;
		win_cpp::WindowMessage wm = static_cast<win_cpp::WindowMessage>(data.data.keyboard.Message);
		// bool state = (wm == win_cpp::WindowMessage::WM_KEYDOWN) || (wm == win_cpp::WindowMessage::WM_SYSKEYDOWN); 	// win_cpp::WindowMessage::WM_KEYUP / win_cpp::WindowMessage::WM_SYSKEYUP
		RawInputKeyboardData k_data = {
			scancode,
			flags,
			vk,
			ExtraInformation,
			wm
		};

		return k_data;
	}


	struct RawInputHIDData {
		unsigned n_reports;
		std::span<const std::byte> data;
	};
	RawInputHIDData GetRawInputHIDData(RawInputHandle handle) {
		constexpr unsigned uiCommand = std::to_underlying(RawInputDeviceStructType::RID_HEADER);
		unsigned size = static_cast<unsigned>(win_cpp::RawInputDeviceTypeStructSize::HIDStructSize);
		win::t::RAWINPUT data;
		constexpr win::t::UINT cbSizeHeader = sizeof(win::t::RAWINPUTHEADER);
		std::ignore = win::f::GetRawInputData(handle, uiCommand, &data, &size, cbSizeHeader);
		std::span<const std::byte> rih_data(
			reinterpret_cast<const std::byte*>(&(data.data.hid.bRawData)),
			((data.data.hid.dwSizeHid) * (data.data.hid.dwCount))
		);
		unsigned n_reports = data.data.hid.dwCount;
		RawInputHIDData h_data = {
			n_reports,
			rih_data
		};

		return h_data;
	}

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

		win::t::LRESULT CallbackHolder::windowProc(win::t::HWND hWnd, win::t::UINT uMsg, win::t::WPARAM wParam, win::t::LPARAM lParam) {
			// std::lock_guard<AtomicFlagMutex> lk(mutex);
			auto window_message = static_cast<win_cpp::WindowMessage>(uMsg);
			switch (window_message) {
				case win_cpp::WindowMessage::WM_UNKNOWN_ONE: {  auto res = std::invoke(WM_UNKNOWN_ONE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				// case win_cpp::WindowMessage::WM_ACTIVATE: {  auto res = std::invoke(WM_ACTIVATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_ACTIVATEAPP: {  auto res = std::invoke(WM_ACTIVATEAPP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_AFXFIRST: {  auto res = std::invoke(WM_AFXFIRST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_AFXLAST: {  auto res = std::invoke(WM_AFXLAST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_APP: {  auto res = std::invoke(WM_APP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_APPCOMMAND: {  auto res = std::invoke(WM_APPCOMMAND_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_ASKCBFORMATNAME: {  auto res = std::invoke(WM_ASKCBFORMATNAME_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CANCELJOURNAL: {  auto res = std::invoke(WM_CANCELJOURNAL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				// case win_cpp::WindowMessage::WM_CANCELMODE: {  auto res = std::invoke(WM_CANCELMODE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CAPTURECHANGED: {
					// lParam:	A handle to the window gaining the mouse capture.
					// TODO : parent widow work in other thread
	#if 0
					auto window_handle = reinterpret_cast<win::t::HWND>(lParam);
					auto w_ptr = reinterpret_cast<win_cpp::Window*>(win::f::GetPropW(window_handle, L"GLFW"));
					if (window_handle) {
						const win_cpp::Window& wnd = *w_ptr;
						auto res = std::invoke(WM_CAPTURECHANGED_callback, wnd);
						if (res.has_value()) {
							return res.value();
						}	else {
							break;
						}
					}	else {
					
					}
	#else 
					bool x = lParam; // has window like
					auto res = std::invoke(WM_CAPTURECHANGED_callback, x);
					if (res.has_value()) {
						return res.value();
					}	else {
						break;
					}
	#endif 
				}
				case win_cpp::WindowMessage::WM_CHANGECBCHAIN: {  auto res = std::invoke(WM_CHANGECBCHAIN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CHANGEUISTATE: {  auto res = std::invoke(WM_CHANGEUISTATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CHAR: {
					wchar_t character = static_cast<wchar_t>(wParam);
					WindowsKeyData data(lParam);
					auto res = std::invoke(WM_CHAR_callback, character, data);
					if(res.has_value()) {
						return res.value();
					} else {
						break;
					}
				}
				case win_cpp::WindowMessage::WM_CHARTOITEM: {  auto res = std::invoke(WM_CHARTOITEM_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CHILDACTIVATE: {  auto res = std::invoke(WM_CHILDACTIVATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CLEAR: {  auto res = std::invoke(WM_CLEAR_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CLIPBOARDUPDATE: {  auto res = std::invoke(WM_CLIPBOARDUPDATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CLOAKED_STATE_CHANGED: {  auto res = std::invoke(WM_CLOAKED_STATE_CHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CLOSE: {
					auto res = std::invoke(WM_CLOSE_callback);
					win_cpp::PostQuitMessage(0); // ???
					if(res.has_value()) {
						return res.value();
					} else {
						return 0; // TODO: mb break;
					} 
				}
				case win_cpp::WindowMessage::WM_COMMAND: {  auto res = std::invoke(WM_COMMAND_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_COMMNOTIFY: {  auto res = std::invoke(WM_COMMNOTIFY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_COMPACTING: {  auto res = std::invoke(WM_COMPACTING_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_COMPAREITEM: {  auto res = std::invoke(WM_COMPAREITEM_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CONTEXTMENU: {  auto res = std::invoke(WM_CONTEXTMENU_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_COPY: {  auto res = std::invoke(WM_COPY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_COPYDATA: {  auto res = std::invoke(WM_COPYDATA_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_COPYGLOBALDATA: {  auto res = std::invoke(WM_COPYGLOBALDATA_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CREATE: {  auto res = std::invoke(WM_CREATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CTLCOLORBTN: {  auto res = std::invoke(WM_CTLCOLORBTN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CTLCOLORDLG: {  auto res = std::invoke(WM_CTLCOLORDLG_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CTLCOLOREDIT: {  auto res = std::invoke(WM_CTLCOLOREDIT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CTLCOLORLISTBOX: {  auto res = std::invoke(WM_CTLCOLORLISTBOX_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CTLCOLORMSGBOX: {  auto res = std::invoke(WM_CTLCOLORMSGBOX_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CTLCOLORSCROLLBAR: {  auto res = std::invoke(WM_CTLCOLORSCROLLBAR_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CTLCOLORSTATIC: {  auto res = std::invoke(WM_CTLCOLORSTATIC_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CUT: {  auto res = std::invoke(WM_CUT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DEADCHAR: {  auto res = std::invoke(WM_DEADCHAR_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DELETEITEM: {  auto res = std::invoke(WM_DELETEITEM_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DESTROY: {  auto res = std::invoke(WM_DESTROY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DESTROYCLIPBOARD: {  auto res = std::invoke(WM_DESTROYCLIPBOARD_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DEVICECHANGE: {  auto res = std::invoke(WM_DEVICECHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DEVMODECHANGE: {  auto res = std::invoke(WM_DEVMODECHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DISPLAYCHANGE: {  auto res = std::invoke(WM_DISPLAYCHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DPICHANGED: {  auto res = std::invoke(WM_DPICHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DPICHANGED_AFTERPARENT: {  auto res = std::invoke(WM_DPICHANGED_AFTERPARENT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DPICHANGED_BEFOREPARENT: {  auto res = std::invoke(WM_DPICHANGED_BEFOREPARENT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DRAWCLIPBOARD: {  auto res = std::invoke(WM_DRAWCLIPBOARD_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DRAWITEM: {  auto res = std::invoke(WM_DRAWITEM_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DROPFILES: {  auto res = std::invoke(WM_DROPFILES_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DWMCOLORIZATIONCOLORCHANGED: {  auto res = std::invoke(WM_DWMCOLORIZATIONCOLORCHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DWMCOMPOSITIONCHANGED: {  auto res = std::invoke(WM_DWMCOMPOSITIONCHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DWMNCRENDERINGCHANGED: {  auto res = std::invoke(WM_DWMNCRENDERINGCHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DWMSENDICONICLIVEPREVIEWBITMAP: {  auto res = std::invoke(WM_DWMSENDICONICLIVEPREVIEWBITMAP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DWMSENDICONICTHUMBNAIL: {  auto res = std::invoke(WM_DWMSENDICONICTHUMBNAIL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_DWMWINDOWMAXIMIZEDCHANGE: {  auto res = std::invoke(WM_DWMWINDOWMAXIMIZEDCHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_ENABLE: {  auto res = std::invoke(WM_ENABLE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_ENDSESSION: {  auto res = std::invoke(WM_ENDSESSION_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_ENTERIDLE: {  auto res = std::invoke(WM_ENTERIDLE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_ENTERMENULOOP: {  auto res = std::invoke(WM_ENTERMENULOOP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_ENTERSIZEMOVE: {  auto res = std::invoke(WM_ENTERSIZEMOVE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_ERASEBKGND: {  auto res = std::invoke(WM_ERASEBKGND_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_EXITMENULOOP: {  auto res = std::invoke(WM_EXITMENULOOP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_EXITSIZEMOVE: {  auto res = std::invoke(WM_EXITSIZEMOVE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_FONTCHANGE: {  auto res = std::invoke(WM_FONTCHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_GESTURE: {  auto res = std::invoke(WM_GESTURE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_GESTURENOTIFY: {  auto res = std::invoke(WM_GESTURENOTIFY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_GETDLGCODE: {  auto res = std::invoke(WM_GETDLGCODE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_GETDPISCALEDSIZE: {  auto res = std::invoke(WM_GETDPISCALEDSIZE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_GETFONT: {  auto res = std::invoke(WM_GETFONT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_GETHOTKEY: {  auto res = std::invoke(WM_GETHOTKEY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_GETICON: {  auto res = std::invoke(WM_GETICON_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_GETMINMAXINFO: {  auto res = std::invoke(WM_GETMINMAXINFO_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_GETOBJECT: {  auto res = std::invoke(WM_GETOBJECT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_GETTEXT: {  auto res = std::invoke(WM_GETTEXT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_GETTEXTLENGTH: {  auto res = std::invoke(WM_GETTEXTLENGTH_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_GETTITLEBARINFOEX: {  auto res = std::invoke(WM_GETTITLEBARINFOEX_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_HANDHELDFIRST: {  auto res = std::invoke(WM_HANDHELDFIRST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_HANDHELDLAST: {  auto res = std::invoke(WM_HANDHELDLAST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_HELP: {  auto res = std::invoke(WM_HELP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_HOTKEY: {  auto res = std::invoke(WM_HOTKEY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_HSCROLL: {  auto res = std::invoke(WM_HSCROLL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_HSCROLLCLIPBOARD: {  auto res = std::invoke(WM_HSCROLLCLIPBOARD_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_ICONERASEBKGND: {  auto res = std::invoke(WM_ICONERASEBKGND_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_IME_CHAR: {  auto res = std::invoke(WM_IME_CHAR_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_IME_COMPOSITION: {  auto res = std::invoke(WM_IME_COMPOSITION_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_IME_COMPOSITIONFULL: {  auto res = std::invoke(WM_IME_COMPOSITIONFULL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_IME_CONTROL: {  auto res = std::invoke(WM_IME_CONTROL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_IME_ENDCOMPOSITION: {  auto res = std::invoke(WM_IME_ENDCOMPOSITION_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_IME_KEYDOWN: {  auto res = std::invoke(WM_IME_KEYDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				// case win_cpp::WindowMessage::WM_IME_KEYLAST: {  auto res = std::invoke(WM_IME_KEYLAST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_IME_KEYUP: {  auto res = std::invoke(WM_IME_KEYUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_IME_NOTIFY: {  auto res = std::invoke(WM_IME_NOTIFY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_IME_REQUEST: {  auto res = std::invoke(WM_IME_REQUEST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_IME_SELECT: {  auto res = std::invoke(WM_IME_SELECT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_IME_SETCONTEXT: {  auto res = std::invoke(WM_IME_SETCONTEXT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_IME_STARTCOMPOSITION: {  auto res = std::invoke(WM_IME_STARTCOMPOSITION_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_INITDIALOG: {  auto res = std::invoke(WM_INITDIALOG_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_INITMENU: {  auto res = std::invoke(WM_INITMENU_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_INITMENUPOPUP: {  auto res = std::invoke(WM_INITMENUPOPUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_INPUT: {
					auto rit = static_cast<win_cpp::RawInputType>(wParam & 0xff);
					auto raw_input_handle = reinterpret_cast<win_cpp::RawInputHandle>(lParam);
					auto ridt = win_cpp::GetRawInputDeviceType(raw_input_handle);

					switch(ridt) {
						case win_cpp::RawInputDeviceType::RIM_TYPEMOUSE: {
							auto data = win_cpp::GetRawInputMouseData(raw_input_handle);
							auto res = std::invoke(WM_RAW_INPUT_MOUSE_callback, rit, data);
							if (res.has_value()) {
								return res.value();
							} else {
								break;
							}
							break;
						}
						case win_cpp::RawInputDeviceType::RIM_TYPEKEYBOARD: { 
							auto data = win_cpp::GetRawInputKeyboardData(raw_input_handle);
							auto res = std::invoke(WM_RAW_INPUT_KEYBOARD_callback, rit, data);
							if(res.has_value()) { 
								return res.value();
							} else { 
								break; 
							} 
							break; 
						}
						case win_cpp::RawInputDeviceType::RIM_TYPEHID: {
							auto data = win_cpp::GetRawInputHIDData(raw_input_handle);
							auto res = std::invoke(WM_RAW_INPUT_HID_callback, rit, data);
							if(res.has_value()) { 
								return res.value();
							} else { 
								break; 
							} 
							break; 
						}						
					}
				}
				case win_cpp::WindowMessage::WM_INPUTLANGCHANGE: {  auto res = std::invoke(WM_INPUTLANGCHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_INPUTLANGCHANGEREQUEST: {  auto res = std::invoke(WM_INPUTLANGCHANGEREQUEST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_INPUT_DEVICE_CHANGE: {  auto res = std::invoke(WM_INPUT_DEVICE_CHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_INTERCEPTED_WINDOW_ACTION: {  auto res = std::invoke(WM_INTERCEPTED_WINDOW_ACTION_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_KEYDOWN: {
					auto vk = static_cast<win_cpp::VirtualKeysStandardSet>(wParam);
					WindowsKeyData data(lParam);
					auto res = std::invoke(WM_KEYDOWN_callback, vk, data);
					if(res.has_value()) { 
						return res.value(); 
					} else { 
						break; 
					} 
				}
				// case win_cpp::WindowMessage::WM_KEYFIRST: {  auto res = std::invoke(WM_KEYFIRST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				// case win_cpp::WindowMessage::WM_KEYLAST: {  auto res = std::invoke(WM_KEYLAST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_KEYUP: {
					auto vk = static_cast<win_cpp::VirtualKeysStandardSet>(wParam);
					WindowsKeyData data(lParam);
					auto res = std::invoke(WM_KEYUP_callback, vk, data); 
					if(res.has_value()) { 
						return res.value(); 
					} else { 
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_KILLFOCUS: {
					// wParam : A handle to the window that receives the keyboard focus.This parameter can be NULL.
					// lParam : This parameter is not used.
					// retval : An application should return zero if it processes this message.

					auto res = std::invoke(WM_KILLFOCUS_callback);
					if(res.has_value()) {
						return res.value();
					} else {
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_LBUTTONDBLCLK: {  auto res = std::invoke(WM_LBUTTONDBLCLK_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_LBUTTONDOWN: {
					auto m_pos = win_cpp::GetMousePosition(lParam);
					auto m_keys_down = win_cpp::MouseKeysFlags(wParam);
					auto res = std::invoke(WM_LBUTTONDOWN_callback, m_pos, m_keys_down);
					if(res.has_value()) { 
						return res.value();
					} else { 
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_LBUTTONUP: { 
					auto m_pos = win_cpp::GetMousePosition(lParam);
					auto m_keys_down = win_cpp::MouseKeysFlags(wParam);
					auto res = std::invoke(WM_LBUTTONUP_callback, m_pos, m_keys_down);
					if(res.has_value()) { 
						return res.value(); 
					} else {
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_MBUTTONDBLCLK: {  auto res = std::invoke(WM_MBUTTONDBLCLK_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MBUTTONDOWN: {
					auto m_pos = win_cpp::GetMousePosition(lParam);
					auto m_keys_down = win_cpp::MouseKeysFlags(wParam);
					auto res = std::invoke(WM_MBUTTONDOWN_callback, m_pos, m_keys_down);
					if(res.has_value()) { 
						return res.value(); 
					} else { 
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_MBUTTONUP: {
					auto m_pos = win_cpp::GetMousePosition(lParam);
					auto m_keys_down = win_cpp::MouseKeysFlags(wParam);
					auto res = std::invoke(WM_MBUTTONUP_callback, m_pos, m_keys_down);
					if(res.has_value()) { 
						return res.value(); 
					} else { 
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_MDIACTIVATE: {  auto res = std::invoke(WM_MDIACTIVATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MDICASCADE: {  auto res = std::invoke(WM_MDICASCADE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MDICREATE: {  auto res = std::invoke(WM_MDICREATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MDIDESTROY: {  auto res = std::invoke(WM_MDIDESTROY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MDIGETACTIVE: {  auto res = std::invoke(WM_MDIGETACTIVE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MDIICONARRANGE: {  auto res = std::invoke(WM_MDIICONARRANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MDIMAXIMIZE: {  auto res = std::invoke(WM_MDIMAXIMIZE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MDINEXT: {  auto res = std::invoke(WM_MDINEXT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MDIREFRESHMENU: {  auto res = std::invoke(WM_MDIREFRESHMENU_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MDIRESTORE: {  auto res = std::invoke(WM_MDIRESTORE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MDISETMENU: {  auto res = std::invoke(WM_MDISETMENU_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MDITILE: {  auto res = std::invoke(WM_MDITILE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MEASUREITEM: {  auto res = std::invoke(WM_MEASUREITEM_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MENUCHAR: {  auto res = std::invoke(WM_MENUCHAR_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MENUCOMMAND: {  auto res = std::invoke(WM_MENUCOMMAND_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MENUDRAG: {  auto res = std::invoke(WM_MENUDRAG_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MENUGETOBJECT: {  auto res = std::invoke(WM_MENUGETOBJECT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MENURBUTTONUP: {  auto res = std::invoke(WM_MENURBUTTONUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MENUSELECT: {  auto res = std::invoke(WM_MENUSELECT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MOUSEACTIVATE: {
					// TODO : wParam
					// auto window_handle = reinterpret_cast<win::t::HWND>(wParam);
					// auto w_ptr = reinterpret_cast<win_cpp::Window*>(win::f::GetPropW(window_handle, L"GLFW"));
					// const win_cpp::Window& top_level_parent_window = *w_ptr;
					auto mouse_event_message = static_cast<win_cpp::WindowMessage>(win::f::HIWORD(lParam));
					auto hittest_message = static_cast<win_cpp::HitTest>(win::f::LOWORD(lParam));
					auto res = std::invoke(WM_MOUSEACTIVATE_callback, mouse_event_message, hittest_message);
					if(res.has_value()) {
						return res.value();
					} else {
						break; 
					} 
				}
				// case win_cpp::WindowMessage::WM_MOUSEFIRST: {  auto res = std::invoke(WM_MOUSEFIRST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MOUSEHOVER: {  auto res = std::invoke(WM_MOUSEHOVER_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MOUSEHWHEEL: {  auto res = std::invoke(WM_MOUSEHWHEEL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				// case win_cpp::WindowMessage::WM_MOUSELAST: {  auto res = std::invoke(WM_MOUSELAST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MOUSELEAVE: {  auto res = std::invoke(WM_MOUSELEAVE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MOUSEMOVE: {
					auto m_pos = win_cpp::GetMousePosition(lParam);
					auto m_keys_down = win_cpp::MouseKeysFlags(wParam);
					auto res = std::invoke(WM_MOUSEMOVE_callback, m_pos, m_keys_down);
					if(res.has_value()) { 
						return res.value(); 
					} else { 
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_MOUSEWHEEL: {  auto res = std::invoke(WM_MOUSEWHEEL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MOVE: {  auto res = std::invoke(WM_MOVE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_MOVING: {  auto res = std::invoke(WM_MOVING_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCACTIVATE: {  auto res = std::invoke(WM_NCACTIVATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCCALCSIZE: {  auto res = std::invoke(WM_NCCALCSIZE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCCREATE: {  auto res = std::invoke(WM_NCCREATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCDESTROY: {  auto res = std::invoke(WM_NCDESTROY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCHITTEST: {  auto res = std::invoke(WM_NCHITTEST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCLBUTTONDBLCLK: {  auto res = std::invoke(WM_NCLBUTTONDBLCLK_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCLBUTTONDOWN: {  auto res = std::invoke(WM_NCLBUTTONDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCLBUTTONUP: {  auto res = std::invoke(WM_NCLBUTTONUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCMBUTTONDBLCLK: {  auto res = std::invoke(WM_NCMBUTTONDBLCLK_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCMBUTTONDOWN: {  auto res = std::invoke(WM_NCMBUTTONDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCMBUTTONUP: {  auto res = std::invoke(WM_NCMBUTTONUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCMOUSEHOVER: {  auto res = std::invoke(WM_NCMOUSEHOVER_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCMOUSELEAVE: {  auto res = std::invoke(WM_NCMOUSELEAVE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCMOUSEMOVE: {  auto res = std::invoke(WM_NCMOUSEMOVE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCPAINT: {  auto res = std::invoke(WM_NCPAINT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCPOINTERDOWN: {  auto res = std::invoke(WM_NCPOINTERDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCPOINTERUP: {  auto res = std::invoke(WM_NCPOINTERUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCPOINTERUPDATE: {  auto res = std::invoke(WM_NCPOINTERUPDATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCRBUTTONDBLCLK: {  auto res = std::invoke(WM_NCRBUTTONDBLCLK_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCRBUTTONDOWN: {  auto res = std::invoke(WM_NCRBUTTONDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCRBUTTONUP: {  auto res = std::invoke(WM_NCRBUTTONUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCXBUTTONDBLCLK: {  auto res = std::invoke(WM_NCXBUTTONDBLCLK_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCXBUTTONDOWN: {  auto res = std::invoke(WM_NCXBUTTONDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NCXBUTTONUP: {  auto res = std::invoke(WM_NCXBUTTONUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NEXTDLGCTL: {  auto res = std::invoke(WM_NEXTDLGCTL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NEXTMENU: {  auto res = std::invoke(WM_NEXTMENU_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NOTIFY: {  auto res = std::invoke(WM_NOTIFY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NOTIFYFORMAT: {  auto res = std::invoke(WM_NOTIFYFORMAT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_NULL: {  auto res = std::invoke(WM_NULL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_PAINT: {  auto res = std::invoke(WM_PAINT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_PAINTCLIPBOARD: {  auto res = std::invoke(WM_PAINTCLIPBOARD_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_PAINTICON: {  auto res = std::invoke(WM_PAINTICON_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_PALETTECHANGED: {  auto res = std::invoke(WM_PALETTECHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_PALETTEISCHANGING: {  auto res = std::invoke(WM_PALETTEISCHANGING_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_PARENTNOTIFY: {  auto res = std::invoke(WM_PARENTNOTIFY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_PASTE: {  auto res = std::invoke(WM_PASTE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_PENWINFIRST: {  auto res = std::invoke(WM_PENWINFIRST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_PENWINLAST: {  auto res = std::invoke(WM_PENWINLAST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERACTIVATE: {  auto res = std::invoke(WM_POINTERACTIVATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERCAPTURECHANGED: {  auto res = std::invoke(WM_POINTERCAPTURECHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERDEVICECHANGE: {  auto res = std::invoke(WM_POINTERDEVICECHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERDEVICEINRANGE: {  auto res = std::invoke(WM_POINTERDEVICEINRANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERDEVICEOUTOFRANGE: {  auto res = std::invoke(WM_POINTERDEVICEOUTOFRANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERDOWN: {  auto res = std::invoke(WM_POINTERDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERENTER: {  auto res = std::invoke(WM_POINTERENTER_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERHWHEEL: {  auto res = std::invoke(WM_POINTERHWHEEL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERLEAVE: {  auto res = std::invoke(WM_POINTERLEAVE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERROUTEDAWAY: {  auto res = std::invoke(WM_POINTERROUTEDAWAY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERROUTEDRELEASED: {  auto res = std::invoke(WM_POINTERROUTEDRELEASED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERROUTEDTO: {  auto res = std::invoke(WM_POINTERROUTEDTO_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERUP: {  auto res = std::invoke(WM_POINTERUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERUPDATE: {  auto res = std::invoke(WM_POINTERUPDATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POINTERWHEEL: {  auto res = std::invoke(WM_POINTERWHEEL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POWER: {  auto res = std::invoke(WM_POWER_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_POWERBROADCAST: {  auto res = std::invoke(WM_POWERBROADCAST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_PRINT: {  auto res = std::invoke(WM_PRINT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_PRINTCLIENT: {  auto res = std::invoke(WM_PRINTCLIENT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_QUERYDRAGICON: {  auto res = std::invoke(WM_QUERYDRAGICON_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_QUERYENDSESSION: {  auto res = std::invoke(WM_QUERYENDSESSION_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_QUERYNEWPALETTE: {  auto res = std::invoke(WM_QUERYNEWPALETTE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_QUERYOPEN: {  auto res = std::invoke(WM_QUERYOPEN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_QUERYUISTATE: {  auto res = std::invoke(WM_QUERYUISTATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_QUEUESYNC: {  auto res = std::invoke(WM_QUEUESYNC_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				// case win_cpp::WindowMessage::WM_QUIT: {  auto res = std::invoke(WM_QUIT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_RBUTTONDBLCLK: {  auto res = std::invoke(WM_RBUTTONDBLCLK_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_RBUTTONDOWN: {
					auto m_pos = win_cpp::GetMousePosition(lParam);
					auto m_keys_down = win_cpp::MouseKeysFlags(wParam);
					auto res = std::invoke(WM_RBUTTONDOWN_callback, m_pos, m_keys_down);
					if(res.has_value()) { 
						return res.value(); 
					} else { 
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_RBUTTONUP: {
					auto m_pos = win_cpp::GetMousePosition(lParam);
					auto m_keys_down = win_cpp::MouseKeysFlags(wParam);
					auto res = std::invoke(WM_RBUTTONUP_callback, m_pos, m_keys_down);
					if(res.has_value()) { 
						return res.value(); 
					} else { 
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_RENDERALLFORMATS: {  auto res = std::invoke(WM_RENDERALLFORMATS_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_RENDERFORMAT: {  auto res = std::invoke(WM_RENDERFORMAT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SETCURSOR: {  auto res = std::invoke(WM_SETCURSOR_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SETFOCUS: {
					// wParam : A handle to the window that has lost the keyboard focus.This parameter can be NULL.
					// lParam :	This parameter is not used.
					// retval : An application should return zero if it processes this message.
					auto res = std::invoke(WM_SETFOCUS_callback);
					if(res.has_value()) {
						return res.value(); 
					} else {
						break; 
					}
				}
				case win_cpp::WindowMessage::WM_SETFONT: {  auto res = std::invoke(WM_SETFONT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SETHOTKEY: {  auto res = std::invoke(WM_SETHOTKEY_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SETICON: {  auto res = std::invoke(WM_SETICON_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SETREDRAW: {  auto res = std::invoke(WM_SETREDRAW_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SETTEXT: {  auto res = std::invoke(WM_SETTEXT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SHOWWINDOW: {  auto res = std::invoke(WM_SHOWWINDOW_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SIZE: {  auto res = std::invoke(WM_SIZE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SIZECLIPBOARD: {  auto res = std::invoke(WM_SIZECLIPBOARD_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SIZING: {
					win_cpp::Edges edges = win_cpp::Edges(wParam);
					win::t::RECT* r_ptr = reinterpret_cast<win::t::RECT*>(lParam);
					win_cpp::Rect rect(r_ptr->left, r_ptr->top, r_ptr->right, r_ptr->bottom);
					auto res = std::invoke(WM_SIZING_callback, edges, rect);
					r_ptr->left = rect.get_left();
					r_ptr->top = rect.get_top();
					r_ptr->right = rect.get_right();
					r_ptr->bottom = rect.get_bottom();
					if(res.has_value()) {
						return res.value();
					} else {
						break;
					} 
				}
				case win_cpp::WindowMessage::WM_SPOOLERSTATUS: {  auto res = std::invoke(WM_SPOOLERSTATUS_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_STYLECHANGED: {  auto res = std::invoke(WM_STYLECHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_STYLECHANGING: {  auto res = std::invoke(WM_STYLECHANGING_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SYNCPAINT: {  auto res = std::invoke(WM_SYNCPAINT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SYSCHAR: {
					wchar_t character = static_cast<wchar_t>(wParam);
					WindowsKeyData data(lParam);
					auto res = std::invoke(WM_SYSCHAR_callback, character, data);
					if(res.has_value()) {
						return res.value();
					} else {
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_SYSCOLORCHANGE: {  auto res = std::invoke(WM_SYSCOLORCHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SYSCOMMAND: {  auto res = std::invoke(WM_SYSCOMMAND_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SYSDEADCHAR: {  auto res = std::invoke(WM_SYSDEADCHAR_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_SYSKEYDOWN: {
					auto vk = static_cast<win_cpp::VirtualKeysStandardSet>(wParam);
					WindowsKeyData data(lParam);
					auto res = std::invoke(WM_SYSKEYDOWN_callback, vk, data);
					if(res.has_value()) {
						return res.value(); 
					} else {
						break;
					} 
				}
				case win_cpp::WindowMessage::WM_SYSKEYUP: {
					auto vk = static_cast<win_cpp::VirtualKeysStandardSet>(wParam);
					WindowsKeyData data(lParam);
					auto res = std::invoke(WM_SYSKEYUP_callback, vk, data);
					if(res.has_value()) {
						return res.value();
					} else { 
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_TABLET_FIRST: {  auto res = std::invoke(WM_TABLET_FIRST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_TABLET_LAST: {  auto res = std::invoke(WM_TABLET_LAST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_TCARD: {  auto res = std::invoke(WM_TCARD_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_THEMECHANGED: {  auto res = std::invoke(WM_THEMECHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_TIMECHANGE: {  auto res = std::invoke(WM_TIMECHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_TIMER: {  auto res = std::invoke(WM_TIMER_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_TOOLTIPDISMISS: {  auto res = std::invoke(WM_TOOLTIPDISMISS_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_TOUCH: {  auto res = std::invoke(WM_TOUCH_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_TOUCHHITTESTING: {  auto res = std::invoke(WM_TOUCHHITTESTING_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_UNDO: {  auto res = std::invoke(WM_UNDO_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_UNICHAR: {
					auto codepoint = static_cast<unsigned>(wParam);
					auto data = WindowsKeyData(lParam);
					auto res = std::invoke(WM_UNICHAR_callback, codepoint, data);
					if(res.has_value()) { 
						return res.value();
					} else { 
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_UNINITMENUPOPUP: {  auto res = std::invoke(WM_UNINITMENUPOPUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_UPDATEUISTATE: {  auto res = std::invoke(WM_UPDATEUISTATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_USER: {  auto res = std::invoke(WM_USER_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_USERCHANGED: {  auto res = std::invoke(WM_USERCHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_VKEYTOITEM: {  auto res = std::invoke(WM_VKEYTOITEM_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_VSCROLL: {  auto res = std::invoke(WM_VSCROLL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_VSCROLLCLIPBOARD: {  auto res = std::invoke(WM_VSCROLLCLIPBOARD_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_WINDOWPOSCHANGED: {  auto res = std::invoke(WM_WINDOWPOSCHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				// case win_cpp::WindowMessage::WM_WINDOWPOSCHANGING: {  auto res = std::invoke(WM_WINDOWPOSCHANGING_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_WININICHANGE: {  auto res = std::invoke(WM_WININICHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_WTSSESSION_CHANGE: {  auto res = std::invoke(WM_WTSSESSION_CHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_XBUTTONDBLCLK: {  auto res = std::invoke(WM_XBUTTONDBLCLK_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_XBUTTONDOWN: {
					unsigned n_button = win::f::HIWORD(wParam);
					auto m_pos = win_cpp::GetMousePosition(lParam);
					auto m_keys_down = win_cpp::MouseKeysFlags(win::f::LOWORD(wParam));
					auto res = std::invoke(WM_XBUTTONDOWN_callback, n_button, m_pos, m_keys_down);
					if(res.has_value()) { 
						return res.value();
					} else {
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_XBUTTONUP: {
					unsigned n_button = win::f::HIWORD(wParam);
					auto m_pos = win_cpp::GetMousePosition(lParam);
					auto m_keys_down = win_cpp::MouseKeysFlags(win::f::LOWORD(wParam));
					auto res = std::invoke(WM_XBUTTONUP_callback, n_button, m_pos, m_keys_down);
					if(res.has_value()) { 
						return res.value(); 
					} else { 
						break; 
					} 
				}
				case win_cpp::WindowMessage::WM_CHOOSEFONT_GETLOGFONT: {  auto res = std::invoke(WM_CHOOSEFONT_GETLOGFONT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CHOOSEFONT_SETFLAGS: {  auto res = std::invoke(WM_CHOOSEFONT_SETFLAGS_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				case win_cpp::WindowMessage::WM_CHOOSEFONT_SETLOGFONT: {  auto res = std::invoke(WM_CHOOSEFONT_SETLOGFONT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
				// case win_cpp::WindowMessage::WM_SETTINGCHANGE: {  auto res = std::invoke(WM_SETTINGCHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			}
			return win::f::DefWindowProcW(hWnd, uMsg, wParam, lParam);
		} // windowProc

};