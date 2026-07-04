module;

export module windowProc;
import std;
import win;
import win_cpp;

export namespace window_proc {
	using result_type = std::optional<long long>;

	struct WindowsCharData {
		unsigned repeatCount;
		unsigned scanCode;
		bool extended : 1;
		bool contextCode : 1;
		bool previousState : 1;
		bool transitionState : 1;

		WindowsCharData(long long lParam)
			: repeatCount(static_cast<unsigned>(lParam & 0xFFFF))
			, scanCode(static_cast<unsigned>((lParam >> 16) & 0xFF))
			, extended((lParam& (1 << 24)) != 0)
			, contextCode((lParam& (1 << 29)) != 0)
			, previousState((lParam& (1 << 30)) != 0)
			, transitionState((lParam& (1 << 31)) != 0)
		{
		}
	};

	using WM_UNKNOWN_ONE_callback_T = std::function<result_type()>;
	using WM_ACTIVATE_callback_T = std::function<result_type()>;
	using WM_ACTIVATEAPP_callback_T = std::function<result_type()>;
	using WM_AFXFIRST_callback_T = std::function<result_type()>;
	using WM_AFXLAST_callback_T = std::function<result_type()>;
	using WM_APP_callback_T = std::function<result_type()>;
	using WM_APPCOMMAND_callback_T = std::function<result_type()>;
	using WM_ASKCBFORMATNAME_callback_T = std::function<result_type()>;
	using WM_CANCELJOURNAL_callback_T = std::function<result_type()>;
	using WM_CANCELMODE_callback_T = std::function<result_type()>;
	using WM_CAPTURECHANGED_callback_T = std::function<result_type(bool)>; // TODO
	using WM_CHANGECBCHAIN_callback_T = std::function<result_type()>;
	using WM_CHANGEUISTATE_callback_T = std::function<result_type()>;
	using WM_CHAR_callback_T = std::function<result_type(wchar_t, const WindowsCharData&)>;
	using WM_CHARTOITEM_callback_T = std::function<result_type()>;
	using WM_CHILDACTIVATE_callback_T = std::function<result_type()>;
	using WM_CLEAR_callback_T = std::function<result_type()>;
	using WM_CLIPBOARDUPDATE_callback_T = std::function<result_type()>;
	using WM_CLOAKED_STATE_CHANGED_callback_T = std::function<result_type()>;
	using WM_CLOSE_callback_T = std::function<result_type()>;
	using WM_COMMAND_callback_T = std::function<result_type()>;
	using WM_COMMNOTIFY_callback_T = std::function<result_type()>;
	using WM_COMPACTING_callback_T = std::function<result_type()>;
	using WM_COMPAREITEM_callback_T = std::function<result_type()>;
	using WM_CONTEXTMENU_callback_T = std::function<result_type()>;
	using WM_COPY_callback_T = std::function<result_type()>;
	using WM_COPYDATA_callback_T = std::function<result_type()>;
	using WM_COPYGLOBALDATA_callback_T = std::function<result_type()>;
	using WM_CREATE_callback_T = std::function<result_type()>;
	using WM_CTLCOLORBTN_callback_T = std::function<result_type()>;
	using WM_CTLCOLORDLG_callback_T = std::function<result_type()>;
	using WM_CTLCOLOREDIT_callback_T = std::function<result_type()>;
	using WM_CTLCOLORLISTBOX_callback_T = std::function<result_type()>;
	using WM_CTLCOLORMSGBOX_callback_T = std::function<result_type()>;
	using WM_CTLCOLORSCROLLBAR_callback_T = std::function<result_type()>;
	using WM_CTLCOLORSTATIC_callback_T = std::function<result_type()>;
	using WM_CUT_callback_T = std::function<result_type()>;
	using WM_DEADCHAR_callback_T = std::function<result_type()>;
	using WM_DELETEITEM_callback_T = std::function<result_type()>;
	using WM_DESTROY_callback_T = std::function<result_type()>;
	using WM_DESTROYCLIPBOARD_callback_T = std::function<result_type()>;
	using WM_DEVICECHANGE_callback_T = std::function<result_type()>;
	using WM_DEVMODECHANGE_callback_T = std::function<result_type()>;
	using WM_DISPLAYCHANGE_callback_T = std::function<result_type()>;
	using WM_DPICHANGED_callback_T = std::function<result_type()>;
	using WM_DPICHANGED_AFTERPARENT_callback_T = std::function<result_type()>;
	using WM_DPICHANGED_BEFOREPARENT_callback_T = std::function<result_type()>;
	using WM_DRAWCLIPBOARD_callback_T = std::function<result_type()>;
	using WM_DRAWITEM_callback_T = std::function<result_type()>;
	using WM_DROPFILES_callback_T = std::function<result_type()>;
	using WM_DWMCOLORIZATIONCOLORCHANGED_callback_T = std::function<result_type()>;
	using WM_DWMCOMPOSITIONCHANGED_callback_T = std::function<result_type()>;
	using WM_DWMNCRENDERINGCHANGED_callback_T = std::function<result_type()>;
	using WM_DWMSENDICONICLIVEPREVIEWBITMAP_callback_T = std::function<result_type()>;
	using WM_DWMSENDICONICTHUMBNAIL_callback_T = std::function<result_type()>;
	using WM_DWMWINDOWMAXIMIZEDCHANGE_callback_T = std::function<result_type()>;
	using WM_ENABLE_callback_T = std::function<result_type()>;
	using WM_ENDSESSION_callback_T = std::function<result_type()>;
	using WM_ENTERIDLE_callback_T = std::function<result_type()>;
	using WM_ENTERMENULOOP_callback_T = std::function<result_type()>;
	using WM_ENTERSIZEMOVE_callback_T = std::function<result_type()>;
	using WM_ERASEBKGND_callback_T = std::function<result_type()>;
	using WM_EXITMENULOOP_callback_T = std::function<result_type()>;
	using WM_EXITSIZEMOVE_callback_T = std::function<result_type()>;
	using WM_FONTCHANGE_callback_T = std::function<result_type()>;
	using WM_GESTURE_callback_T = std::function<result_type()>;
	using WM_GESTURENOTIFY_callback_T = std::function<result_type()>;
	using WM_GETDLGCODE_callback_T = std::function<result_type()>;
	using WM_GETDPISCALEDSIZE_callback_T = std::function<result_type()>;
	using WM_GETFONT_callback_T = std::function<result_type()>;
	using WM_GETHOTKEY_callback_T = std::function<result_type()>;
	using WM_GETICON_callback_T = std::function<result_type()>;
	using WM_GETMINMAXINFO_callback_T = std::function<result_type()>;
	using WM_GETOBJECT_callback_T = std::function<result_type()>;
	using WM_GETTEXT_callback_T = std::function<result_type()>;
	using WM_GETTEXTLENGTH_callback_T = std::function<result_type()>;
	using WM_GETTITLEBARINFOEX_callback_T = std::function<result_type()>;
	using WM_HANDHELDFIRST_callback_T = std::function<result_type()>;
	using WM_HANDHELDLAST_callback_T = std::function<result_type()>;
	using WM_HELP_callback_T = std::function<result_type()>;
	using WM_HOTKEY_callback_T = std::function<result_type()>;
	using WM_HSCROLL_callback_T = std::function<result_type()>;
	using WM_HSCROLLCLIPBOARD_callback_T = std::function<result_type()>;
	using WM_ICONERASEBKGND_callback_T = std::function<result_type()>;
	using WM_IME_CHAR_callback_T = std::function<result_type()>;
	using WM_IME_COMPOSITION_callback_T = std::function<result_type()>;
	using WM_IME_COMPOSITIONFULL_callback_T = std::function<result_type()>;
	using WM_IME_CONTROL_callback_T = std::function<result_type()>;
	using WM_IME_ENDCOMPOSITION_callback_T = std::function<result_type()>;
	using WM_IME_KEYDOWN_callback_T = std::function<result_type()>;
	using WM_IME_KEYLAST_callback_T = std::function<result_type()>;
	using WM_IME_KEYUP_callback_T = std::function<result_type()>;
	using WM_IME_NOTIFY_callback_T = std::function<result_type()>;
	using WM_IME_REQUEST_callback_T = std::function<result_type()>;
	using WM_IME_SELECT_callback_T = std::function<result_type()>;
	using WM_IME_SETCONTEXT_callback_T = std::function<result_type()>;
	using WM_IME_STARTCOMPOSITION_callback_T = std::function<result_type()>;
	using WM_INITDIALOG_callback_T = std::function<result_type()>;
	using WM_INITMENU_callback_T = std::function<result_type()>;
	using WM_INITMENUPOPUP_callback_T = std::function<result_type()>;
	using WM_INPUT_callback_T = std::function<result_type()>;
	using WM_INPUTLANGCHANGE_callback_T = std::function<result_type()>;
	using WM_INPUTLANGCHANGEREQUEST_callback_T = std::function<result_type()>;
	using WM_INPUT_DEVICE_CHANGE_callback_T = std::function<result_type()>;
	using WM_INTERCEPTED_WINDOW_ACTION_callback_T = std::function<result_type()>;
	using WM_KEYDOWN_callback_T = std::function<result_type()>;
	using WM_KEYFIRST_callback_T = std::function<result_type()>;
	using WM_KEYLAST_callback_T = std::function<result_type()>;
	using WM_KEYUP_callback_T = std::function<result_type()>;
	using WM_KILLFOCUS_callback_T = std::function<result_type()>;
	using WM_LBUTTONDBLCLK_callback_T = std::function<result_type()>;
	using WM_LBUTTONDOWN_callback_T = std::function<result_type()>;
	using WM_LBUTTONUP_callback_T = std::function<result_type()>;
	using WM_MBUTTONDBLCLK_callback_T = std::function<result_type()>;
	using WM_MBUTTONDOWN_callback_T = std::function<result_type()>;
	using WM_MBUTTONUP_callback_T = std::function<result_type()>;
	using WM_MDIACTIVATE_callback_T = std::function<result_type()>;
	using WM_MDICASCADE_callback_T = std::function<result_type()>;
	using WM_MDICREATE_callback_T = std::function<result_type()>;
	using WM_MDIDESTROY_callback_T = std::function<result_type()>;
	using WM_MDIGETACTIVE_callback_T = std::function<result_type()>;
	using WM_MDIICONARRANGE_callback_T = std::function<result_type()>;
	using WM_MDIMAXIMIZE_callback_T = std::function<result_type()>;
	using WM_MDINEXT_callback_T = std::function<result_type()>;
	using WM_MDIREFRESHMENU_callback_T = std::function<result_type()>;
	using WM_MDIRESTORE_callback_T = std::function<result_type()>;
	using WM_MDISETMENU_callback_T = std::function<result_type()>;
	using WM_MDITILE_callback_T = std::function<result_type()>;
	using WM_MEASUREITEM_callback_T = std::function<result_type()>;
	using WM_MENUCHAR_callback_T = std::function<result_type()>;
	using WM_MENUCOMMAND_callback_T = std::function<result_type()>;
	using WM_MENUDRAG_callback_T = std::function<result_type()>;
	using WM_MENUGETOBJECT_callback_T = std::function<result_type()>;
	using WM_MENURBUTTONUP_callback_T = std::function<result_type()>;
	using WM_MENUSELECT_callback_T = std::function<result_type()>;
	using WM_MOUSEACTIVATE_callback_T = std::function<result_type(win_cpp::WindowMessage, win_cpp::HitTest)>;
	using WM_MOUSEFIRST_callback_T = std::function<result_type()>;
	using WM_MOUSEHOVER_callback_T = std::function<result_type()>;
	using WM_MOUSEHWHEEL_callback_T = std::function<result_type()>;
	using WM_MOUSELAST_callback_T = std::function<result_type()>;
	using WM_MOUSELEAVE_callback_T = std::function<result_type()>;
	using WM_MOUSEMOVE_callback_T = std::function<result_type(const std::pair<short, short>&, win_cpp::MouseKeysFlags)>;
	using WM_MOUSEWHEEL_callback_T = std::function<result_type()>;
	using WM_MOVE_callback_T = std::function<result_type()>;
	using WM_MOVING_callback_T = std::function<result_type()>;
	using WM_NCACTIVATE_callback_T = std::function<result_type()>;
	using WM_NCCALCSIZE_callback_T = std::function<result_type()>;
	using WM_NCCREATE_callback_T = std::function<result_type()>;
	using WM_NCDESTROY_callback_T = std::function<result_type()>;
	using WM_NCHITTEST_callback_T = std::function<result_type()>;
	using WM_NCLBUTTONDBLCLK_callback_T = std::function<result_type()>;
	using WM_NCLBUTTONDOWN_callback_T = std::function<result_type()>;
	using WM_NCLBUTTONUP_callback_T = std::function<result_type()>;
	using WM_NCMBUTTONDBLCLK_callback_T = std::function<result_type()>;
	using WM_NCMBUTTONDOWN_callback_T = std::function<result_type()>;
	using WM_NCMBUTTONUP_callback_T = std::function<result_type()>;
	using WM_NCMOUSEHOVER_callback_T = std::function<result_type()>;
	using WM_NCMOUSELEAVE_callback_T = std::function<result_type()>;
	using WM_NCMOUSEMOVE_callback_T = std::function<result_type()>;
	using WM_NCPAINT_callback_T = std::function<result_type()>;
	using WM_NCPOINTERDOWN_callback_T = std::function<result_type()>;
	using WM_NCPOINTERUP_callback_T = std::function<result_type()>;
	using WM_NCPOINTERUPDATE_callback_T = std::function<result_type()>;
	using WM_NCRBUTTONDBLCLK_callback_T = std::function<result_type()>;
	using WM_NCRBUTTONDOWN_callback_T = std::function<result_type()>;
	using WM_NCRBUTTONUP_callback_T = std::function<result_type()>;
	using WM_NCXBUTTONDBLCLK_callback_T = std::function<result_type()>;
	using WM_NCXBUTTONDOWN_callback_T = std::function<result_type()>;
	using WM_NCXBUTTONUP_callback_T = std::function<result_type()>;
	using WM_NEXTDLGCTL_callback_T = std::function<result_type()>;
	using WM_NEXTMENU_callback_T = std::function<result_type()>;
	using WM_NOTIFY_callback_T = std::function<result_type()>;
	using WM_NOTIFYFORMAT_callback_T = std::function<result_type()>;
	using WM_NULL_callback_T = std::function<result_type()>;
	using WM_PAINT_callback_T = std::function<result_type()>;
	using WM_PAINTCLIPBOARD_callback_T = std::function<result_type()>;
	using WM_PAINTICON_callback_T = std::function<result_type()>;
	using WM_PALETTECHANGED_callback_T = std::function<result_type()>;
	using WM_PALETTEISCHANGING_callback_T = std::function<result_type()>;
	using WM_PARENTNOTIFY_callback_T = std::function<result_type()>;
	using WM_PASTE_callback_T = std::function<result_type()>;
	using WM_PENWINFIRST_callback_T = std::function<result_type()>;
	using WM_PENWINLAST_callback_T = std::function<result_type()>;
	using WM_POINTERACTIVATE_callback_T = std::function<result_type()>;
	using WM_POINTERCAPTURECHANGED_callback_T = std::function<result_type()>;
	using WM_POINTERDEVICECHANGE_callback_T = std::function<result_type()>;
	using WM_POINTERDEVICEINRANGE_callback_T = std::function<result_type()>;
	using WM_POINTERDEVICEOUTOFRANGE_callback_T = std::function<result_type()>;
	using WM_POINTERDOWN_callback_T = std::function<result_type()>;
	using WM_POINTERENTER_callback_T = std::function<result_type()>;
	using WM_POINTERHWHEEL_callback_T = std::function<result_type()>;
	using WM_POINTERLEAVE_callback_T = std::function<result_type()>;
	using WM_POINTERROUTEDAWAY_callback_T = std::function<result_type()>;
	using WM_POINTERROUTEDRELEASED_callback_T = std::function<result_type()>;
	using WM_POINTERROUTEDTO_callback_T = std::function<result_type()>;
	using WM_POINTERUP_callback_T = std::function<result_type()>;
	using WM_POINTERUPDATE_callback_T = std::function<result_type()>;
	using WM_POINTERWHEEL_callback_T = std::function<result_type()>;
	using WM_POWER_callback_T = std::function<result_type()>;
	using WM_POWERBROADCAST_callback_T = std::function<result_type()>;
	using WM_PRINT_callback_T = std::function<result_type()>;
	using WM_PRINTCLIENT_callback_T = std::function<result_type()>;
	using WM_QUERYDRAGICON_callback_T = std::function<result_type()>;
	using WM_QUERYENDSESSION_callback_T = std::function<result_type()>;
	using WM_QUERYNEWPALETTE_callback_T = std::function<result_type()>;
	using WM_QUERYOPEN_callback_T = std::function<result_type()>;
	using WM_QUERYUISTATE_callback_T = std::function<result_type()>;
	using WM_QUEUESYNC_callback_T = std::function<result_type()>;
	using WM_QUIT_callback_T = std::function<result_type()>;
	using WM_RBUTTONDBLCLK_callback_T = std::function<result_type()>;
	using WM_RBUTTONDOWN_callback_T = std::function<result_type()>;
	using WM_RBUTTONUP_callback_T = std::function<result_type()>;
	using WM_RENDERALLFORMATS_callback_T = std::function<result_type()>;
	using WM_RENDERFORMAT_callback_T = std::function<result_type()>;
	using WM_SETCURSOR_callback_T = std::function<result_type()>;
	using WM_SETFOCUS_callback_T = std::function<result_type()>;
	using WM_SETFONT_callback_T = std::function<result_type()>;
	using WM_SETHOTKEY_callback_T = std::function<result_type()>;
	using WM_SETICON_callback_T = std::function<result_type()>;
	using WM_SETREDRAW_callback_T = std::function<result_type()>;
	using WM_SETTEXT_callback_T = std::function<result_type()>;
	using WM_SHOWWINDOW_callback_T = std::function<result_type()>;
	using WM_SIZE_callback_T = std::function<result_type()>;
	using WM_SIZECLIPBOARD_callback_T = std::function<result_type()>;
	using WM_SIZING_callback_T = std::function<result_type(win_cpp::Edges edges, win_cpp::Rect& rect)>;
	using WM_SPOOLERSTATUS_callback_T = std::function<result_type()>;
	using WM_STYLECHANGED_callback_T = std::function<result_type()>;
	using WM_STYLECHANGING_callback_T = std::function<result_type()>;
	using WM_SYNCPAINT_callback_T = std::function<result_type()>;
	using WM_SYSCHAR_callback_T = std::function<result_type()>;
	using WM_SYSCOLORCHANGE_callback_T = std::function<result_type()>;
	using WM_SYSCOMMAND_callback_T = std::function<result_type()>;
	using WM_SYSDEADCHAR_callback_T = std::function<result_type()>;
	using WM_SYSKEYDOWN_callback_T = std::function<result_type()>;
	using WM_SYSKEYUP_callback_T = std::function<result_type()>;
	using WM_TABLET_FIRST_callback_T = std::function<result_type()>;
	using WM_TABLET_LAST_callback_T = std::function<result_type()>;
	using WM_TCARD_callback_T = std::function<result_type()>;
	using WM_THEMECHANGED_callback_T = std::function<result_type()>;
	using WM_TIMECHANGE_callback_T = std::function<result_type()>;
	using WM_TIMER_callback_T = std::function<result_type()>;
	using WM_TOOLTIPDISMISS_callback_T = std::function<result_type()>;
	using WM_TOUCH_callback_T = std::function<result_type()>;
	using WM_TOUCHHITTESTING_callback_T = std::function<result_type()>;
	using WM_UNDO_callback_T = std::function<result_type()>;
	using WM_UNICHAR_callback_T = std::function<result_type()>;
	using WM_UNINITMENUPOPUP_callback_T = std::function<result_type()>;
	using WM_UPDATEUISTATE_callback_T = std::function<result_type()>;
	using WM_USER_callback_T = std::function<result_type()>;
	using WM_USERCHANGED_callback_T = std::function<result_type()>;
	using WM_VKEYTOITEM_callback_T = std::function<result_type()>;
	using WM_VSCROLL_callback_T = std::function<result_type()>;
	using WM_VSCROLLCLIPBOARD_callback_T = std::function<result_type()>;
	using WM_WINDOWPOSCHANGED_callback_T = std::function<result_type()>;
	using WM_WINDOWPOSCHANGING_callback_T = std::function<result_type()>;
	using WM_WININICHANGE_callback_T = std::function<result_type()>;
	using WM_WTSSESSION_CHANGE_callback_T = std::function<result_type()>;
	using WM_XBUTTONDBLCLK_callback_T = std::function<result_type()>;
	using WM_XBUTTONDOWN_callback_T = std::function<result_type()>;
	using WM_XBUTTONUP_callback_T = std::function<result_type()>;
	using WM_CHOOSEFONT_GETLOGFONT_callback_T = std::function<result_type()>;
	using WM_CHOOSEFONT_SETFLAGS_callback_T = std::function<result_type()>;
	using WM_CHOOSEFONT_SETLOGFONT_callback_T = std::function<result_type()>;

	WM_UNKNOWN_ONE_callback_T WM_UNKNOWN_ONE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_ACTIVATE_callback_T WM_ACTIVATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_ACTIVATEAPP_callback_T WM_ACTIVATEAPP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_AFXFIRST_callback_T WM_AFXFIRST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_AFXLAST_callback_T WM_AFXLAST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_APP_callback_T WM_APP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_APPCOMMAND_callback_T WM_APPCOMMAND_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_ASKCBFORMATNAME_callback_T WM_ASKCBFORMATNAME_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CANCELJOURNAL_callback_T WM_CANCELJOURNAL_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CANCELMODE_callback_T WM_CANCELMODE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CAPTURECHANGED_callback_T WM_CAPTURECHANGED_callback = [](bool has_window) constexpr noexcept -> result_type { return std::nullopt; };
	WM_CHANGECBCHAIN_callback_T WM_CHANGECBCHAIN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CHANGEUISTATE_callback_T WM_CHANGEUISTATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CHAR_callback_T WM_CHAR_callback = [](wchar_t, const WindowsCharData&) constexpr noexcept -> result_type { return std::nullopt; };
	WM_CHARTOITEM_callback_T WM_CHARTOITEM_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CHILDACTIVATE_callback_T WM_CHILDACTIVATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CLEAR_callback_T WM_CLEAR_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CLIPBOARDUPDATE_callback_T WM_CLIPBOARDUPDATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CLOAKED_STATE_CHANGED_callback_T WM_CLOAKED_STATE_CHANGED_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CLOSE_callback_T WM_CLOSE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_COMMAND_callback_T WM_COMMAND_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_COMMNOTIFY_callback_T WM_COMMNOTIFY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_COMPACTING_callback_T WM_COMPACTING_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_COMPAREITEM_callback_T WM_COMPAREITEM_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CONTEXTMENU_callback_T WM_CONTEXTMENU_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_COPY_callback_T WM_COPY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_COPYDATA_callback_T WM_COPYDATA_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_COPYGLOBALDATA_callback_T WM_COPYGLOBALDATA_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CREATE_callback_T WM_CREATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CTLCOLORBTN_callback_T WM_CTLCOLORBTN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CTLCOLORDLG_callback_T WM_CTLCOLORDLG_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CTLCOLOREDIT_callback_T WM_CTLCOLOREDIT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CTLCOLORLISTBOX_callback_T WM_CTLCOLORLISTBOX_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CTLCOLORMSGBOX_callback_T WM_CTLCOLORMSGBOX_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CTLCOLORSCROLLBAR_callback_T WM_CTLCOLORSCROLLBAR_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CTLCOLORSTATIC_callback_T WM_CTLCOLORSTATIC_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CUT_callback_T WM_CUT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DEADCHAR_callback_T WM_DEADCHAR_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DELETEITEM_callback_T WM_DELETEITEM_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DESTROY_callback_T WM_DESTROY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DESTROYCLIPBOARD_callback_T WM_DESTROYCLIPBOARD_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DEVICECHANGE_callback_T WM_DEVICECHANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DEVMODECHANGE_callback_T WM_DEVMODECHANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DISPLAYCHANGE_callback_T WM_DISPLAYCHANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DPICHANGED_callback_T WM_DPICHANGED_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DPICHANGED_AFTERPARENT_callback_T WM_DPICHANGED_AFTERPARENT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DPICHANGED_BEFOREPARENT_callback_T WM_DPICHANGED_BEFOREPARENT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DRAWCLIPBOARD_callback_T WM_DRAWCLIPBOARD_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DRAWITEM_callback_T WM_DRAWITEM_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DROPFILES_callback_T WM_DROPFILES_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DWMCOLORIZATIONCOLORCHANGED_callback_T WM_DWMCOLORIZATIONCOLORCHANGED_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DWMCOMPOSITIONCHANGED_callback_T WM_DWMCOMPOSITIONCHANGED_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DWMNCRENDERINGCHANGED_callback_T WM_DWMNCRENDERINGCHANGED_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DWMSENDICONICLIVEPREVIEWBITMAP_callback_T WM_DWMSENDICONICLIVEPREVIEWBITMAP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DWMSENDICONICTHUMBNAIL_callback_T WM_DWMSENDICONICTHUMBNAIL_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_DWMWINDOWMAXIMIZEDCHANGE_callback_T WM_DWMWINDOWMAXIMIZEDCHANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_ENABLE_callback_T WM_ENABLE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_ENDSESSION_callback_T WM_ENDSESSION_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_ENTERIDLE_callback_T WM_ENTERIDLE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_ENTERMENULOOP_callback_T WM_ENTERMENULOOP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_ENTERSIZEMOVE_callback_T WM_ENTERSIZEMOVE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_ERASEBKGND_callback_T WM_ERASEBKGND_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_EXITMENULOOP_callback_T WM_EXITMENULOOP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_EXITSIZEMOVE_callback_T WM_EXITSIZEMOVE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_FONTCHANGE_callback_T WM_FONTCHANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_GESTURE_callback_T WM_GESTURE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_GESTURENOTIFY_callback_T WM_GESTURENOTIFY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_GETDLGCODE_callback_T WM_GETDLGCODE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_GETDPISCALEDSIZE_callback_T WM_GETDPISCALEDSIZE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_GETFONT_callback_T WM_GETFONT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_GETHOTKEY_callback_T WM_GETHOTKEY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_GETICON_callback_T WM_GETICON_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_GETMINMAXINFO_callback_T WM_GETMINMAXINFO_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_GETOBJECT_callback_T WM_GETOBJECT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_GETTEXT_callback_T WM_GETTEXT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_GETTEXTLENGTH_callback_T WM_GETTEXTLENGTH_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_GETTITLEBARINFOEX_callback_T WM_GETTITLEBARINFOEX_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_HANDHELDFIRST_callback_T WM_HANDHELDFIRST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_HANDHELDLAST_callback_T WM_HANDHELDLAST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_HELP_callback_T WM_HELP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_HOTKEY_callback_T WM_HOTKEY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_HSCROLL_callback_T WM_HSCROLL_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_HSCROLLCLIPBOARD_callback_T WM_HSCROLLCLIPBOARD_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_ICONERASEBKGND_callback_T WM_ICONERASEBKGND_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_CHAR_callback_T WM_IME_CHAR_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_COMPOSITION_callback_T WM_IME_COMPOSITION_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_COMPOSITIONFULL_callback_T WM_IME_COMPOSITIONFULL_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_CONTROL_callback_T WM_IME_CONTROL_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_ENDCOMPOSITION_callback_T WM_IME_ENDCOMPOSITION_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_KEYDOWN_callback_T WM_IME_KEYDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_KEYLAST_callback_T WM_IME_KEYLAST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_KEYUP_callback_T WM_IME_KEYUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_NOTIFY_callback_T WM_IME_NOTIFY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_REQUEST_callback_T WM_IME_REQUEST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_SELECT_callback_T WM_IME_SELECT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_SETCONTEXT_callback_T WM_IME_SETCONTEXT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_IME_STARTCOMPOSITION_callback_T WM_IME_STARTCOMPOSITION_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_INITDIALOG_callback_T WM_INITDIALOG_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_INITMENU_callback_T WM_INITMENU_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_INITMENUPOPUP_callback_T WM_INITMENUPOPUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_INPUT_callback_T WM_INPUT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_INPUTLANGCHANGE_callback_T WM_INPUTLANGCHANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_INPUTLANGCHANGEREQUEST_callback_T WM_INPUTLANGCHANGEREQUEST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_INPUT_DEVICE_CHANGE_callback_T WM_INPUT_DEVICE_CHANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_INTERCEPTED_WINDOW_ACTION_callback_T WM_INTERCEPTED_WINDOW_ACTION_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_KEYDOWN_callback_T WM_KEYDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_KEYFIRST_callback_T WM_KEYFIRST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_KEYLAST_callback_T WM_KEYLAST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_KEYUP_callback_T WM_KEYUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_KILLFOCUS_callback_T WM_KILLFOCUS_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_LBUTTONDBLCLK_callback_T WM_LBUTTONDBLCLK_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_LBUTTONDOWN_callback_T WM_LBUTTONDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_LBUTTONUP_callback_T WM_LBUTTONUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MBUTTONDBLCLK_callback_T WM_MBUTTONDBLCLK_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MBUTTONDOWN_callback_T WM_MBUTTONDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MBUTTONUP_callback_T WM_MBUTTONUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MDIACTIVATE_callback_T WM_MDIACTIVATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MDICASCADE_callback_T WM_MDICASCADE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MDICREATE_callback_T WM_MDICREATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MDIDESTROY_callback_T WM_MDIDESTROY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MDIGETACTIVE_callback_T WM_MDIGETACTIVE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MDIICONARRANGE_callback_T WM_MDIICONARRANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MDIMAXIMIZE_callback_T WM_MDIMAXIMIZE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MDINEXT_callback_T WM_MDINEXT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MDIREFRESHMENU_callback_T WM_MDIREFRESHMENU_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MDIRESTORE_callback_T WM_MDIRESTORE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MDISETMENU_callback_T WM_MDISETMENU_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MDITILE_callback_T WM_MDITILE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MEASUREITEM_callback_T WM_MEASUREITEM_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MENUCHAR_callback_T WM_MENUCHAR_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MENUCOMMAND_callback_T WM_MENUCOMMAND_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MENUDRAG_callback_T WM_MENUDRAG_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MENUGETOBJECT_callback_T WM_MENUGETOBJECT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MENURBUTTONUP_callback_T WM_MENURBUTTONUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MENUSELECT_callback_T WM_MENUSELECT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MOUSEACTIVATE_callback_T WM_MOUSEACTIVATE_callback = [](win_cpp::WindowMessage, win_cpp::HitTest) constexpr noexcept -> result_type { return std::nullopt; };
	WM_MOUSEFIRST_callback_T WM_MOUSEFIRST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MOUSEHOVER_callback_T WM_MOUSEHOVER_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MOUSEHWHEEL_callback_T WM_MOUSEHWHEEL_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MOUSELAST_callback_T WM_MOUSELAST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MOUSELEAVE_callback_T WM_MOUSELEAVE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MOUSEMOVE_callback_T WM_MOUSEMOVE_callback = [](const std::pair<short, short>&, win_cpp::MouseKeysFlags) constexpr noexcept -> result_type { return std::nullopt; };
	WM_MOUSEWHEEL_callback_T WM_MOUSEWHEEL_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MOVE_callback_T WM_MOVE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_MOVING_callback_T WM_MOVING_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCACTIVATE_callback_T WM_NCACTIVATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCCALCSIZE_callback_T WM_NCCALCSIZE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCCREATE_callback_T WM_NCCREATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCDESTROY_callback_T WM_NCDESTROY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCHITTEST_callback_T WM_NCHITTEST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCLBUTTONDBLCLK_callback_T WM_NCLBUTTONDBLCLK_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCLBUTTONDOWN_callback_T WM_NCLBUTTONDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCLBUTTONUP_callback_T WM_NCLBUTTONUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCMBUTTONDBLCLK_callback_T WM_NCMBUTTONDBLCLK_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCMBUTTONDOWN_callback_T WM_NCMBUTTONDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCMBUTTONUP_callback_T WM_NCMBUTTONUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCMOUSEHOVER_callback_T WM_NCMOUSEHOVER_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCMOUSELEAVE_callback_T WM_NCMOUSELEAVE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCMOUSEMOVE_callback_T WM_NCMOUSEMOVE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCPAINT_callback_T WM_NCPAINT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCPOINTERDOWN_callback_T WM_NCPOINTERDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCPOINTERUP_callback_T WM_NCPOINTERUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCPOINTERUPDATE_callback_T WM_NCPOINTERUPDATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCRBUTTONDBLCLK_callback_T WM_NCRBUTTONDBLCLK_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCRBUTTONDOWN_callback_T WM_NCRBUTTONDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCRBUTTONUP_callback_T WM_NCRBUTTONUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCXBUTTONDBLCLK_callback_T WM_NCXBUTTONDBLCLK_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCXBUTTONDOWN_callback_T WM_NCXBUTTONDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NCXBUTTONUP_callback_T WM_NCXBUTTONUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NEXTDLGCTL_callback_T WM_NEXTDLGCTL_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NEXTMENU_callback_T WM_NEXTMENU_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NOTIFY_callback_T WM_NOTIFY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NOTIFYFORMAT_callback_T WM_NOTIFYFORMAT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_NULL_callback_T WM_NULL_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_PAINT_callback_T WM_PAINT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_PAINTCLIPBOARD_callback_T WM_PAINTCLIPBOARD_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_PAINTICON_callback_T WM_PAINTICON_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_PALETTECHANGED_callback_T WM_PALETTECHANGED_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_PALETTEISCHANGING_callback_T WM_PALETTEISCHANGING_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_PARENTNOTIFY_callback_T WM_PARENTNOTIFY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_PASTE_callback_T WM_PASTE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_PENWINFIRST_callback_T WM_PENWINFIRST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_PENWINLAST_callback_T WM_PENWINLAST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERACTIVATE_callback_T WM_POINTERACTIVATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERCAPTURECHANGED_callback_T WM_POINTERCAPTURECHANGED_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERDEVICECHANGE_callback_T WM_POINTERDEVICECHANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERDEVICEINRANGE_callback_T WM_POINTERDEVICEINRANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERDEVICEOUTOFRANGE_callback_T WM_POINTERDEVICEOUTOFRANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERDOWN_callback_T WM_POINTERDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERENTER_callback_T WM_POINTERENTER_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERHWHEEL_callback_T WM_POINTERHWHEEL_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERLEAVE_callback_T WM_POINTERLEAVE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERROUTEDAWAY_callback_T WM_POINTERROUTEDAWAY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERROUTEDRELEASED_callback_T WM_POINTERROUTEDRELEASED_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERROUTEDTO_callback_T WM_POINTERROUTEDTO_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERUP_callback_T WM_POINTERUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERUPDATE_callback_T WM_POINTERUPDATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POINTERWHEEL_callback_T WM_POINTERWHEEL_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POWER_callback_T WM_POWER_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_POWERBROADCAST_callback_T WM_POWERBROADCAST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_PRINT_callback_T WM_PRINT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_PRINTCLIENT_callback_T WM_PRINTCLIENT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_QUERYDRAGICON_callback_T WM_QUERYDRAGICON_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_QUERYENDSESSION_callback_T WM_QUERYENDSESSION_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_QUERYNEWPALETTE_callback_T WM_QUERYNEWPALETTE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_QUERYOPEN_callback_T WM_QUERYOPEN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_QUERYUISTATE_callback_T WM_QUERYUISTATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_QUEUESYNC_callback_T WM_QUEUESYNC_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_QUIT_callback_T WM_QUIT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_RBUTTONDBLCLK_callback_T WM_RBUTTONDBLCLK_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_RBUTTONDOWN_callback_T WM_RBUTTONDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_RBUTTONUP_callback_T WM_RBUTTONUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_RENDERALLFORMATS_callback_T WM_RENDERALLFORMATS_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_RENDERFORMAT_callback_T WM_RENDERFORMAT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SETCURSOR_callback_T WM_SETCURSOR_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SETFOCUS_callback_T WM_SETFOCUS_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SETFONT_callback_T WM_SETFONT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SETHOTKEY_callback_T WM_SETHOTKEY_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SETICON_callback_T WM_SETICON_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SETREDRAW_callback_T WM_SETREDRAW_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SETTEXT_callback_T WM_SETTEXT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SHOWWINDOW_callback_T WM_SHOWWINDOW_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SIZE_callback_T WM_SIZE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SIZECLIPBOARD_callback_T WM_SIZECLIPBOARD_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SIZING_callback_T WM_SIZING_callback = [](win_cpp::Edges edges, win_cpp::Rect& rect) constexpr noexcept -> result_type { return std::nullopt; };
	WM_SPOOLERSTATUS_callback_T WM_SPOOLERSTATUS_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_STYLECHANGED_callback_T WM_STYLECHANGED_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_STYLECHANGING_callback_T WM_STYLECHANGING_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SYNCPAINT_callback_T WM_SYNCPAINT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SYSCHAR_callback_T WM_SYSCHAR_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SYSCOLORCHANGE_callback_T WM_SYSCOLORCHANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SYSCOMMAND_callback_T WM_SYSCOMMAND_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SYSDEADCHAR_callback_T WM_SYSDEADCHAR_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SYSKEYDOWN_callback_T WM_SYSKEYDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_SYSKEYUP_callback_T WM_SYSKEYUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_TABLET_FIRST_callback_T WM_TABLET_FIRST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_TABLET_LAST_callback_T WM_TABLET_LAST_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_TCARD_callback_T WM_TCARD_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_THEMECHANGED_callback_T WM_THEMECHANGED_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_TIMECHANGE_callback_T WM_TIMECHANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_TIMER_callback_T WM_TIMER_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_TOOLTIPDISMISS_callback_T WM_TOOLTIPDISMISS_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_TOUCH_callback_T WM_TOUCH_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_TOUCHHITTESTING_callback_T WM_TOUCHHITTESTING_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_UNDO_callback_T WM_UNDO_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_UNICHAR_callback_T WM_UNICHAR_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_UNINITMENUPOPUP_callback_T WM_UNINITMENUPOPUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_UPDATEUISTATE_callback_T WM_UPDATEUISTATE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_USER_callback_T WM_USER_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_USERCHANGED_callback_T WM_USERCHANGED_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_VKEYTOITEM_callback_T WM_VKEYTOITEM_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_VSCROLL_callback_T WM_VSCROLL_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_VSCROLLCLIPBOARD_callback_T WM_VSCROLLCLIPBOARD_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_WINDOWPOSCHANGED_callback_T WM_WINDOWPOSCHANGED_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_WINDOWPOSCHANGING_callback_T WM_WINDOWPOSCHANGING_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_WININICHANGE_callback_T WM_WININICHANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_WTSSESSION_CHANGE_callback_T WM_WTSSESSION_CHANGE_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_XBUTTONDBLCLK_callback_T WM_XBUTTONDBLCLK_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_XBUTTONDOWN_callback_T WM_XBUTTONDOWN_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_XBUTTONUP_callback_T WM_XBUTTONUP_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CHOOSEFONT_GETLOGFONT_callback_T WM_CHOOSEFONT_GETLOGFONT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CHOOSEFONT_SETFLAGS_callback_T WM_CHOOSEFONT_SETFLAGS_callback = []() constexpr noexcept -> result_type { return std::nullopt; };
	WM_CHOOSEFONT_SETLOGFONT_callback_T WM_CHOOSEFONT_SETLOGFONT_callback = []() constexpr noexcept -> result_type { return std::nullopt; };

	win::t::LRESULT __stdcall windowProc(win::t::HWND hWnd, win::t::UINT uMsg, win::t::WPARAM wParam, win::t::LPARAM lParam) {
		auto window_message = static_cast<win_cpp::WindowMessage>(uMsg);
		switch (window_message) {
			case win_cpp::WindowMessage::WM_UNKNOWN_ONE: {  auto res = std::invoke(WM_UNKNOWN_ONE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_ACTIVATE: {  auto res = std::invoke(WM_ACTIVATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_ACTIVATEAPP: {  auto res = std::invoke(WM_ACTIVATEAPP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_AFXFIRST: {  auto res = std::invoke(WM_AFXFIRST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_AFXLAST: {  auto res = std::invoke(WM_AFXLAST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_APP: {  auto res = std::invoke(WM_APP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_APPCOMMAND: {  auto res = std::invoke(WM_APPCOMMAND_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_ASKCBFORMATNAME: {  auto res = std::invoke(WM_ASKCBFORMATNAME_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_CANCELJOURNAL: {  auto res = std::invoke(WM_CANCELJOURNAL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_CANCELMODE: {  auto res = std::invoke(WM_CANCELMODE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
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
				WindowsCharData data(lParam);
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
			case win_cpp::WindowMessage::WM_CLOSE: {  auto res = std::invoke(WM_CLOSE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
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
			case win_cpp::WindowMessage::WM_INPUT: {  auto res = std::invoke(WM_INPUT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_INPUTLANGCHANGE: {  auto res = std::invoke(WM_INPUTLANGCHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_INPUTLANGCHANGEREQUEST: {  auto res = std::invoke(WM_INPUTLANGCHANGEREQUEST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_INPUT_DEVICE_CHANGE: {  auto res = std::invoke(WM_INPUT_DEVICE_CHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_INTERCEPTED_WINDOW_ACTION: {  auto res = std::invoke(WM_INTERCEPTED_WINDOW_ACTION_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_KEYDOWN: {  auto res = std::invoke(WM_KEYDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			// case win_cpp::WindowMessage::WM_KEYFIRST: {  auto res = std::invoke(WM_KEYFIRST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			// case win_cpp::WindowMessage::WM_KEYLAST: {  auto res = std::invoke(WM_KEYLAST_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_KEYUP: {  auto res = std::invoke(WM_KEYUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
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
			case win_cpp::WindowMessage::WM_LBUTTONDOWN: {  auto res = std::invoke(WM_LBUTTONDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_LBUTTONUP: {  auto res = std::invoke(WM_LBUTTONUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_MBUTTONDBLCLK: {  auto res = std::invoke(WM_MBUTTONDBLCLK_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_MBUTTONDOWN: {  auto res = std::invoke(WM_MBUTTONDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_MBUTTONUP: {  auto res = std::invoke(WM_MBUTTONUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
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
			case win_cpp::WindowMessage::WM_QUIT: {  auto res = std::invoke(WM_QUIT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_RBUTTONDBLCLK: {  auto res = std::invoke(WM_RBUTTONDBLCLK_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_RBUTTONDOWN: {  auto res = std::invoke(WM_RBUTTONDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_RBUTTONUP: {  auto res = std::invoke(WM_RBUTTONUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
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
			case win_cpp::WindowMessage::WM_SYSCHAR: {  auto res = std::invoke(WM_SYSCHAR_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_SYSCOLORCHANGE: {  auto res = std::invoke(WM_SYSCOLORCHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_SYSCOMMAND: {  auto res = std::invoke(WM_SYSCOMMAND_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_SYSDEADCHAR: {  auto res = std::invoke(WM_SYSDEADCHAR_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_SYSKEYDOWN: {  auto res = std::invoke(WM_SYSKEYDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_SYSKEYUP: {  auto res = std::invoke(WM_SYSKEYUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
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
			case win_cpp::WindowMessage::WM_UNICHAR: {  auto res = std::invoke(WM_UNICHAR_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_UNINITMENUPOPUP: {  auto res = std::invoke(WM_UNINITMENUPOPUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_UPDATEUISTATE: {  auto res = std::invoke(WM_UPDATEUISTATE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_USER: {  auto res = std::invoke(WM_USER_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_USERCHANGED: {  auto res = std::invoke(WM_USERCHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_VKEYTOITEM: {  auto res = std::invoke(WM_VKEYTOITEM_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_VSCROLL: {  auto res = std::invoke(WM_VSCROLL_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_VSCROLLCLIPBOARD: {  auto res = std::invoke(WM_VSCROLLCLIPBOARD_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_WINDOWPOSCHANGED: {  auto res = std::invoke(WM_WINDOWPOSCHANGED_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_WINDOWPOSCHANGING: {  auto res = std::invoke(WM_WINDOWPOSCHANGING_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_WININICHANGE: {  auto res = std::invoke(WM_WININICHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_WTSSESSION_CHANGE: {  auto res = std::invoke(WM_WTSSESSION_CHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_XBUTTONDBLCLK: {  auto res = std::invoke(WM_XBUTTONDBLCLK_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_XBUTTONDOWN: {  auto res = std::invoke(WM_XBUTTONDOWN_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_XBUTTONUP: {  auto res = std::invoke(WM_XBUTTONUP_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_CHOOSEFONT_GETLOGFONT: {  auto res = std::invoke(WM_CHOOSEFONT_GETLOGFONT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_CHOOSEFONT_SETFLAGS: {  auto res = std::invoke(WM_CHOOSEFONT_SETFLAGS_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			case win_cpp::WindowMessage::WM_CHOOSEFONT_SETLOGFONT: {  auto res = std::invoke(WM_CHOOSEFONT_SETLOGFONT_callback);  if(res.has_value()) { return res.value(); } else { break; } }
			// case win_cpp::WindowMessage::WM_SETTINGCHANGE: {  auto res = std::invoke(WM_SETTINGCHANGE_callback);  if(res.has_value()) { return res.value(); } else { break; } }
		}
		return win::f::DefWindowProcW(hWnd, uMsg, wParam, lParam);
	} // windowProc

} // ns