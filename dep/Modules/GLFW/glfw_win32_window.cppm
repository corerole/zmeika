module;

export module glfw_win32_window;
import std;
import flags;
import madmap;
import win_cpp;
// import windowProc;
import glfw;
import vulkan;

using translate_map_type = std::unordered_map<win_cpp::WindowsScancode, glfw::Key>;
translate_map_type windows_keyboard_keys_to_glfw_keys = {
			{ win_cpp::WindowsScancode::NULL, glfw::Key::NULL },
			{ win_cpp::WindowsScancode::vA, glfw::Key::vA },
			{ win_cpp::WindowsScancode::vB, glfw::Key::vB },
			{ win_cpp::WindowsScancode::vC, glfw::Key::vC },
			{ win_cpp::WindowsScancode::vD, glfw::Key::vD },
			{ win_cpp::WindowsScancode::vE, glfw::Key::vE },
			{ win_cpp::WindowsScancode::vF, glfw::Key::vF },
			{ win_cpp::WindowsScancode::vG, glfw::Key::vG },
			{ win_cpp::WindowsScancode::vH, glfw::Key::vH },
			{ win_cpp::WindowsScancode::vI, glfw::Key::vI },
			{ win_cpp::WindowsScancode::vJ, glfw::Key::vJ },
			{ win_cpp::WindowsScancode::vK, glfw::Key::vK },
			{ win_cpp::WindowsScancode::vL, glfw::Key::vL },
			{ win_cpp::WindowsScancode::vM, glfw::Key::vM },
			{ win_cpp::WindowsScancode::vN, glfw::Key::vN },
			{ win_cpp::WindowsScancode::vO, glfw::Key::vO },
			{ win_cpp::WindowsScancode::vP, glfw::Key::vP },
			{ win_cpp::WindowsScancode::vQ, glfw::Key::vQ },
			{ win_cpp::WindowsScancode::vR, glfw::Key::vR },
			{ win_cpp::WindowsScancode::vS, glfw::Key::vS },
			{ win_cpp::WindowsScancode::vT, glfw::Key::vT },
			{ win_cpp::WindowsScancode::vU, glfw::Key::vU },
			{ win_cpp::WindowsScancode::vV, glfw::Key::vV },
			{ win_cpp::WindowsScancode::vW, glfw::Key::vW },
			{ win_cpp::WindowsScancode::vX, glfw::Key::vX },
			{ win_cpp::WindowsScancode::vY, glfw::Key::vY },
			{ win_cpp::WindowsScancode::vZ, glfw::Key::vZ },
			{ win_cpp::WindowsScancode::v1_and_Bang, glfw::Key::v1_and_Bang },
			{ win_cpp::WindowsScancode::v2_and_At, glfw::Key::v2_and_At },
			{ win_cpp::WindowsScancode::v3_and_Hash, glfw::Key::v3_and_Hash },
			{ win_cpp::WindowsScancode::v4_and_Dollar, glfw::Key::v4_and_Dollar },
			{ win_cpp::WindowsScancode::v5_and_Percent, glfw::Key::v5_and_Percent },
			{ win_cpp::WindowsScancode::v6_and_Caret, glfw::Key::v6_and_Caret },
			{ win_cpp::WindowsScancode::v7_and_Ampersand, glfw::Key::v7_and_Ampersand },
			{ win_cpp::WindowsScancode::v8_and_Star, glfw::Key::v8_and_Star },
			{ win_cpp::WindowsScancode::v9_and_Left_Bracket, glfw::Key::v9_and_Left_Bracket },
			{ win_cpp::WindowsScancode::v0_and_Right_Brackert, glfw::Key::v0_and_Right_Brackert },
			{ win_cpp::WindowsScancode::vReturnEnter, glfw::Key::vReturnEnter },
			{ win_cpp::WindowsScancode::vEscape, glfw::Key::vEscape },
			{ win_cpp::WindowsScancode::vDelete, glfw::Key::vDelete },
			{ win_cpp::WindowsScancode::vTab, glfw::Key::vTab },
			{ win_cpp::WindowsScancode::vSpaceBar, glfw::Key::vSpaceBar },
			{ win_cpp::WindowsScancode::vDash_and_underscore, glfw::Key::vDash_and_underscore },
			{ win_cpp::WindowsScancode::vEquals_and_Plus, glfw::Key::vEquals_and_Plus },
			{ win_cpp::WindowsScancode::vLeft_Brace, glfw::Key::vLeft_Brace },
			{ win_cpp::WindowsScancode::vRight_Brace, glfw::Key::vRight_Brace },
			{ win_cpp::WindowsScancode::vBackslash_and_Pipe, glfw::Key::vBackslash_and_Pipe },
			{ win_cpp::WindowsScancode::vNonUS_Slash_and_Tilde, glfw::Key::vNonUS_Slash_and_Tilde }, // orig,  
			{ win_cpp::WindowsScancode::vSemiColon_and_Colon, glfw::Key::vSemiColon_and_Colon },
			{ win_cpp::WindowsScancode::vApostrophe_and_Double_Quotation_Mark, glfw::Key::vApostrophe_and_Double_Quotation_Mark },
			{ win_cpp::WindowsScancode::vGrave_Accent_and_Tilde, glfw::Key::vGrave_Accent_and_Tilde },
			{ win_cpp::WindowsScancode::vComma_and_LessThen, glfw::Key::vComma_and_LessThen },
			{ win_cpp::WindowsScancode::vPeriod_and_GreaterThen, glfw::Key::vPeriod_and_GreaterThen },
			{ win_cpp::WindowsScancode::vForwardSlash_and_QuestionMark, glfw::Key::vForwardSlash_and_QuestionMark },
			{ win_cpp::WindowsScancode::vCapsLock, glfw::Key::vCapsLock },
			{ win_cpp::WindowsScancode::vF1, glfw::Key::vF1 },
			{ win_cpp::WindowsScancode::vF2, glfw::Key::vF2 },
			{ win_cpp::WindowsScancode::vF3, glfw::Key::vF3 },
			{ win_cpp::WindowsScancode::vF4, glfw::Key::vF4 },
			{ win_cpp::WindowsScancode::vF5, glfw::Key::vF5 },
			{ win_cpp::WindowsScancode::vF6, glfw::Key::vF6 },
			{ win_cpp::WindowsScancode::vF7, glfw::Key::vF7 },
			{ win_cpp::WindowsScancode::vF8, glfw::Key::vF8 },
			{ win_cpp::WindowsScancode::vF9, glfw::Key::vF9 },
			{ win_cpp::WindowsScancode::vF10, glfw::Key::vF10 },
			{ win_cpp::WindowsScancode::vF11, glfw::Key::vF11 },
			{ win_cpp::WindowsScancode::vF12, glfw::Key::vF12 },
			{ win_cpp::WindowsScancode::vPrintScreen, glfw::Key::vPrintScreen },
			{ win_cpp::WindowsScancode::vScrollLock, glfw::Key::vScrollLock },
			{ win_cpp::WindowsScancode::vPause, glfw::Key::vPause },
			{ win_cpp::WindowsScancode::vInsert, glfw::Key::vInsert },
			{ win_cpp::WindowsScancode::vHome, glfw::Key::vHome },
			{ win_cpp::WindowsScancode::vPageUp, glfw::Key::vPageUp },
			{ win_cpp::WindowsScancode::vDeleteForward, glfw::Key::vDeleteForward },
			{ win_cpp::WindowsScancode::vEnd, glfw::Key::vEnd },
			{ win_cpp::WindowsScancode::vPageDown, glfw::Key::vPageDown },
			{ win_cpp::WindowsScancode::vRightArrow, glfw::Key::vRightArrow },
			{ win_cpp::WindowsScancode::vLeftArrow, glfw::Key::vLeftArrow },
			{ win_cpp::WindowsScancode::vDownArrow, glfw::Key::vDownArrow },
			{ win_cpp::WindowsScancode::vUpArrow, glfw::Key::vUpArrow },
			{ win_cpp::WindowsScancode::vNumLock_and_Clear, glfw::Key::vNumLock_and_Clear },
			{ win_cpp::WindowsScancode::vForwardSlash, glfw::Key::vForwardSlash },
			{ win_cpp::WindowsScancode::vStar, glfw::Key::vStar },
			{ win_cpp::WindowsScancode::vDash, glfw::Key::vDash },
			{ win_cpp::WindowsScancode::vPlus, glfw::Key::vPlus },
			{ win_cpp::WindowsScancode::vEnter, glfw::Key::vEnter },
			{ win_cpp::WindowsScancode::v1_and_End, glfw::Key::v1_and_End },
			{ win_cpp::WindowsScancode::v2_and_Down_Arrow, glfw::Key::v2_and_Down_Arrow },
			{ win_cpp::WindowsScancode::v3_and_PageDn, glfw::Key::v3_and_PageDn },
			{ win_cpp::WindowsScancode::v4_and_Left_Arrow, glfw::Key::v4_and_Left_Arrow },
			{ win_cpp::WindowsScancode::v5_, glfw::Key::v5_ },
			{ win_cpp::WindowsScancode::v6_and_Right_Arrow, glfw::Key::v6_and_Right_Arrow },
			{ win_cpp::WindowsScancode::v7_and_Home, glfw::Key::v7_and_Home },
			{ win_cpp::WindowsScancode::v8_and_Up_Arrow, glfw::Key::v8_and_Up_Arrow },
			{ win_cpp::WindowsScancode::v9_and_PageUp, glfw::Key::v9_and_PageUp },
			{ win_cpp::WindowsScancode::v0_and_Insert, glfw::Key::v0_and_Insert },
			{ win_cpp::WindowsScancode::vPeriod_and_Delete, glfw::Key::vPeriod_and_Delete },
			{ win_cpp::WindowsScancode::vNonUS_Backslash_and_Pipe, glfw::Key::vNonUS_Backslash_and_Pipe },
			{ win_cpp::WindowsScancode::vApplication, glfw::Key::vApplication },
			{ win_cpp::WindowsScancode::vPower, glfw::Key::vPower },
			{ win_cpp::WindowsScancode::vEquals, glfw::Key::vEquals },
			{ win_cpp::WindowsScancode::vF13, glfw::Key::vF13 },
			{ win_cpp::WindowsScancode::vF14, glfw::Key::vF14 },
			{ win_cpp::WindowsScancode::vF15, glfw::Key::vF15 },
			{ win_cpp::WindowsScancode::vF16, glfw::Key::vF16 },
			{ win_cpp::WindowsScancode::vF17, glfw::Key::vF17 },
			{ win_cpp::WindowsScancode::vF18, glfw::Key::vF18 },
			{ win_cpp::WindowsScancode::vF19, glfw::Key::vF19 },
			{ win_cpp::WindowsScancode::vF20, glfw::Key::vF20 },
			{ win_cpp::WindowsScancode::vF21, glfw::Key::vF21 },
			{ win_cpp::WindowsScancode::vF22, glfw::Key::vF22 },
			{ win_cpp::WindowsScancode::vF23, glfw::Key::vF23 },
			{ win_cpp::WindowsScancode::vF24, glfw::Key::vF24 },
			{ win_cpp::WindowsScancode::vComma, glfw::Key::vComma },
			{ win_cpp::WindowsScancode::vInternational1, glfw::Key::vInternational1 },
			{ win_cpp::WindowsScancode::vInternational2, glfw::Key::vInternational2 },
			{ win_cpp::WindowsScancode::vInternational3, glfw::Key::vInternational3 },
			{ win_cpp::WindowsScancode::vInternational4, glfw::Key::vInternational4 },
			{ win_cpp::WindowsScancode::vInternational5, glfw::Key::vInternational5 },
			{ win_cpp::WindowsScancode::vInternational6, glfw::Key::vInternational6 },
			{ win_cpp::WindowsScancode::vLANG1, glfw::Key::vLANG1 },
			{ win_cpp::WindowsScancode::vLANG2, glfw::Key::vLANG2 },
			{ win_cpp::WindowsScancode::vLANG3, glfw::Key::vLANG3 },
			{ win_cpp::WindowsScancode::vLANG4, glfw::Key::vLANG4 },
			{ win_cpp::WindowsScancode::vLANG5, glfw::Key::vLANG5 },
			{ win_cpp::WindowsScancode::vLeftControl, glfw::Key::vLeftControl },
			{ win_cpp::WindowsScancode::vLeftShift, glfw::Key::vLeftShift },
			{ win_cpp::WindowsScancode::vLeftAlt, glfw::Key::vLeftAlt },
			{ win_cpp::WindowsScancode::vLeftGUI, glfw::Key::vLeftGUI },
			{ win_cpp::WindowsScancode::vRightControl, glfw::Key::vRightControl },
			{ win_cpp::WindowsScancode::vRightShift, glfw::Key::vRightShift },
			{ win_cpp::WindowsScancode::vRightAlt, glfw::Key::vRightAlt },
			{ win_cpp::WindowsScancode::vRightGUI, glfw::Key::vRightGUI },
			{ win_cpp::WindowsScancode::vScanNextTrack, glfw::Key::vScanNextTrack },
			{ win_cpp::WindowsScancode::vScanPreviosTrack, glfw::Key::vScanPreviosTrack },
			{ win_cpp::WindowsScancode::vStop, glfw::Key::vStop },
			{ win_cpp::WindowsScancode::vPlay_Pause, glfw::Key::vPlay_Pause },
			{ win_cpp::WindowsScancode::vMute, glfw::Key::vMute },
			{ win_cpp::WindowsScancode::vVolumeIncrement, glfw::Key::vVolumeIncrement },
			{ win_cpp::WindowsScancode::vVolumeDecrement, glfw::Key::vVolumeDecrement },
			{ win_cpp::WindowsScancode::vAL_Consumer_Control_Configuration, glfw::Key::vAL_Consumer_Control_Configuration },
			{ win_cpp::WindowsScancode::vAL_EmailReader, glfw::Key::vAL_EmailReader },
			{ win_cpp::WindowsScancode::vAL_Calculator, glfw::Key::vAL_Calculator },
			{ win_cpp::WindowsScancode::vAL_LocalMachineBrowser, glfw::Key::vAL_LocalMachineBrowser },
			{ win_cpp::WindowsScancode::vAC_Search, glfw::Key::vAC_Search },
			{ win_cpp::WindowsScancode::vAC_Home, glfw::Key::vAC_Home },
			{ win_cpp::WindowsScancode::vAC_Back, glfw::Key::vAC_Back },
			{ win_cpp::WindowsScancode::vAC_Forward, glfw::Key::vAC_Forward },
			{ win_cpp::WindowsScancode::vAC_Stop, glfw::Key::vAC_Stop },
			{ win_cpp::WindowsScancode::vAC_Refresh, glfw::Key::vAC_Refresh },
			{ win_cpp::WindowsScancode::vAC_Bookmarks, glfw::Key::vAC_Bookmarks }
};

glfw::Key to_glfw_key(win_cpp::WindowsScancode key) {
	auto end = windows_keyboard_keys_to_glfw_keys.end();
	auto res = windows_keyboard_keys_to_glfw_keys.find(key);
	return (res != end) ? res->second : glfw::Key::NULL;
}

glfw::CharModsFlags getKeyMods() {
	glfw::CharModsFlags mods;

	// if (win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_SHIFT) & 0x8000u) {
	if (std::to_underlying(win_cpp::GetAsyncKeyState(win_cpp::VirtualKeysStandardSet::VK_SHIFT))) {
		mods |= glfw::CharModsFlags::values::shift;
	}
	// if (win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_CONTROL) & 0x8000u) {
	if (std::to_underlying(win_cpp::GetAsyncKeyState(win_cpp::VirtualKeysStandardSet::VK_CONTROL))) {
		mods |= glfw::CharModsFlags::values::control;
	}
	// if (win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_MENU) & 0x8000u) {
	if (std::to_underlying(win_cpp::GetAsyncKeyState(win_cpp::VirtualKeysStandardSet::VK_MENU))) {
		mods |= glfw::CharModsFlags::values::alt;
	}
	// if ((win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_LWIN) | win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_RWIN)) & 0x8000u) {
	if (std::to_underlying(win_cpp::GetAsyncKeyState(win_cpp::VirtualKeysStandardSet::VK_LWIN))
		| std::to_underlying(win_cpp::GetAsyncKeyState(win_cpp::VirtualKeysStandardSet::VK_RWIN))) {
		mods |= glfw::CharModsFlags::values::super;
	}

	if (win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_CAPITAL) & 1u) { /* TODO */
		mods |= glfw::CharModsFlags::values::caps_lock;
	}

	if (win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_NUMLOCK) & 1u) { /* TODO */
		mods |= glfw::CharModsFlags::values::num_lock;
	}

	return mods;
}

glfw::CharModsCallbackF charmod_default_callback = [](unsigned, glfw::CharModsFlags charmod) {};
glfw::CharacterCallbackF character_default_callback = [](unsigned) {};
glfw::KeyCallbackF key_default_callback = [](glfw::Key key, unsigned scancode, glfw::KeyState action, glfw::CharModsFlags mods) {};

struct Input {
	private:
		glfw::GLFWKeyState key_state = glfw::scancode_key_state;
		bool sticky_keys = false;
		bool lockKeyMods = false;
		glfw::CharModsCallbackF _charmod = charmod_default_callback;
		glfw::CharacterCallbackF _character = character_default_callback;
		glfw::KeyCallbackF key_callback = key_default_callback;

	private:
		constexpr glfw::CharModsFlags apply_KeyMods(glfw::CharModsFlags mods) const noexcept {
			if (!lockKeyMods) {
				constexpr glfw::CharModsFlags caps_lock_int_represent = glfw::CharModsFlags::values::caps_lock;
				constexpr glfw::CharModsFlags num_lock_int_represent = glfw::CharModsFlags::values::num_lock;
				constexpr glfw::CharModsFlags res = ~(caps_lock_int_represent | num_lock_int_represent);
				mods &= res;
			}
			return mods;
		}

	public:
		constexpr void set_LockKeyMods(bool x) noexcept { lockKeyMods = x; }
		constexpr bool get_LockKeyMods() const noexcept { return lockKeyMods; }

		void process_Char(unsigned codepoint, glfw::CharModsFlags mods, bool plain) const {
			// if (codepoint < 32 || (codepoint > 126 && codepoint < 160)) {
				// return;
			// }
			mods = apply_KeyMods(mods);
			std::invoke(_charmod, codepoint, mods);

			if (plain) {
				std::invoke(_character, codepoint);
			}
		}

		void process_Key(glfw::Key key, unsigned scancode, glfw::KeyState action, glfw::CharModsFlags mods) {
			if (true) {
				bool repeated = 0;

				if (action == glfw::KeyState::release && key_state[key] == glfw::KeyState::release) {
					return;
				}

				if (action == glfw::KeyState::press && key_state[key] == glfw::KeyState::press) {
					repeated = true;
				}

				if (action == glfw::KeyState::release && sticky_keys) {
					key_state[key] = glfw::KeyState::stick;
				}	else {
					key_state[key] = action;
				}

				if (repeated) {
					action = glfw::KeyState::repeat;
				}
			}

			mods = apply_KeyMods(mods);

			if (key_callback) {
				std::invoke(key_callback, key, scancode, action, mods);
			}
		}

		void set_key_mods_callback(glfw::CharModsCallbackF&& cmc) {
			_charmod = std::forward<decltype(cmc)>(cmc);
		};
		void set_character_callback(glfw::CharacterCallbackF&& cc) {
			_character = std::forward<decltype(cc)>(cc);
		};
		void set_key_callback(glfw::KeyCallbackF&& kc) {
			key_callback = std::forward<decltype(kc)>(kc);
		};

		Input() noexcept : _charmod(charmod_default_callback), _character(character_default_callback) {}
		Input(
			glfw::CharModsCallbackF&& charmod_f,
			glfw::CharacterCallbackF&& character_f,
			glfw::KeyCallbackF&& key_f
		) noexcept : _charmod(charmod_f), _character(character_f), key_callback(key_f)
		{

		}

	};

bool IsWindows8OrGreater() {
	auto version_info = win_cpp::GetOSVersion();
	if (version_info.Major >= 8) {
		return true;
	}
	return false;
}

bool IsWindows8Point1OrGreater() {
	auto version_info = win_cpp::GetOSVersion();
	if (version_info.Major >= 8 && version_info.Minor >= 10) {
		return true;
	}
	return false;
}

bool IsWindows10Version1607OrGreaterWin32() {
	auto version_info = win_cpp::GetOSVersion();
	if (version_info.BuildNumber >= 14393) {
		return true;
	}
	return false;
}

bool IsWindows10Version1703OrGreaterWin32() {
	auto version_info = win_cpp::GetOSVersion();
	if (version_info.BuildNumber >= 15063) {
		return true;
	}
	return false;
}

struct GLFW_Monitor_Win32 {
	private:
		win_cpp::Monitor monitor;

	public:
		void FitToMonitor(const win_cpp::Window& window) {
			auto mi = monitor.get_Info();
			window.SetWindowPosition(
				win_cpp::WindowZOrder::HWND_TOPMOST,
				mi.rect,
				win_cpp::SetWindowPosFlags::values::SWP_NOZORDER
				| win_cpp::SetWindowPosFlags::values::SWP_NOACTIVATE
				| win_cpp::SetWindowPosFlags::values::SWP_NOCOPYBITS
			);
		}
};

glfw::CursorStateCallbackT dummy_state_callback = [](const glfw::CursorState&) noexcept {};
glfw::CursorPositionCallbackT dummy_pos_callback = [](const std::pair<int, int>& pos) noexcept {};
struct Cursor {
	private:
		glfw::CursorState state_ = glfw::CursorState::disabled;
		glfw::CursorRawInputState raw_input_state = glfw::CursorRawInputState::disabled;
		glfw::CursorStateCallbackT cursor_state_callback_f = dummy_state_callback;
		glfw::CursorPositionCallbackT cursor_position_callback_f = dummy_pos_callback;
		std::unique_ptr<win_cpp::MouseRawInput> mri;
		std::pair<int, int> position = { 0, 0 };

	public:
		Cursor() = default;

	public:
		void set_position(int x, int y) noexcept {
			position.first = x; position.second = y;
			if (cursor_position_callback_f) {
				std::invoke(cursor_position_callback_f, position);
			}
		}

		std::pair<int, int> get_position() const noexcept { return position; }
		glfw::CursorRawInputState get_RawInputState() { return raw_input_state; }
		glfw::CursorState get_state() const noexcept { return state_; }

		void set_cursor_position_callback(glfw::CursorPositionCallbackT&& cpct) {
			cursor_position_callback_f = std::forward<decltype(cpct)>(cpct);
		}

		void set_cursor_state_callback(glfw::CursorStateCallbackT&& csct) {
			cursor_state_callback_f = std::forward<decltype(csct)>(csct);
		}

#if 1
		void set_state(const glfw::CursorState& state) {
			if (cursor_state_callback_f) {
				std::invoke(cursor_state_callback_f, state);
			}
			state_ = state;
		};
#endif

#if 0
 		glfw::CursorState get_state() const noexcept {
 			return state_;
		}
#endif

		void release(const win_cpp::Window& window) {
			win_cpp::UnClipCursor();
			state_ = glfw::CursorState::normal;
		}

		void enable(const win_cpp::Window& window) {
			if(raw_input_state == glfw::CursorRawInputState::enabled) {
				mri.reset();
				raw_input_state = glfw::CursorRawInputState::disabled;
			}
			
			release(window);
#if 0
			// _glfwSetCursorPosWin32(window,
				// _glfw.win32.restoreCursorPosX,
				// _glfw.win32.restoreCursorPosY);
			// updateCursorImage(window);
#endif
		}

		void capture(const win_cpp::Window& window) {
			auto rect = window.GetClientRect();
			auto [lx, ty] = window.ClientToScreen(std::pair(rect.get_left(), rect.get_top()));
			auto [rx, by] = window.ClientToScreen(std::pair(rect.get_right(), rect.get_bottom()));
			rect = win_cpp::Rect(lx, ty, rx, by);
			win_cpp::ClipCursor(rect);
		}

		void disable(const win_cpp::Window& window) {
#if 0
			// _glfw.win32.disabledCursorWindow = window;
			// _glfwGetCursorPosWin32(window,
				// &_glfw.win32.restoreCursorPosX,
				// &_glfw.win32.restoreCursorPosY);
				
			// updateCursorImage(window);
			// _glfwCenterCursorInContentArea(window);
#endif
			auto rect = window.GetClientRect();
			auto height = rect.get_top() - rect.get_left();
			auto width = rect.get_bottom() - rect.get_right();
			set_position(width / 2, height / 2);

			capture(window);
			if (raw_input_state == glfw::CursorRawInputState::enabled) {
				mri.reset(new win_cpp::MouseRawInput(window));
			}
		}

		void enter() {
			std::cout << "Cursor enter" << std::endl;
		}
};

win_cpp::Rect applyAspectRatio(
	const win_cpp::Window& window,
	win_cpp::Edges edge,
	const win_cpp::Rect& area_,
	const glfw::AspectRatio& aspect_raito
) {
	win_cpp::Rect area(area_);

	const auto ratio = aspect_raito.get_Ratio();
	win_cpp::Rect frame;
	win_cpp::Rect wndrect(window);
	if (IsWindows10Version1607OrGreaterWin32()) {
		frame = win_cpp::AdjustWindowRectExForDpi(wndrect, 0, window.GetDpiForWindow(), window.getStyle(), window.getExtendedStyle());
	}	else {
		frame = win_cpp::AdjustWindowRectEx(wndrect, false, window.getStyle(), window.getExtendedStyle());
	}

	if (edge == win_cpp::Edges::WMSZ_LEFT
		|| edge == win_cpp::Edges::WMSZ_BOTTOMLEFT
		|| edge == win_cpp::Edges::WMSZ_RIGHT
		|| edge == win_cpp::Edges::WMSZ_BOTTOMRIGHT
		) {
		area.get_bottom() =
			area.get_top()
			+ (frame.get_bottom() - frame.get_top())
			+ (((area.get_right() - area.get_left())
				- (frame.get_right() - frame.get_left())) / ratio);
	}	else if (edge == win_cpp::Edges::WMSZ_TOPLEFT || edge == win_cpp::Edges::WMSZ_TOPRIGHT) {
		area.get_top() =
			area.get_bottom()
			- (frame.get_bottom() - frame.get_top())
			- (((area.get_right() - area.get_left())
				- (frame.get_right() - frame.get_left())) / ratio);
	} else if (edge == win_cpp::Edges::WMSZ_TOP || edge == win_cpp::Edges::WMSZ_BOTTOM) {
		area.get_right() =
			area.get_left()
			+ (frame.get_right() - frame.get_left())
			+ (((area.get_bottom() - area.get_top())
				- (frame.get_bottom() - frame.get_top())) * ratio);
	}
	return area;
}

bool cursorInContentArea(const win_cpp::Window& window) {
	auto [x, y] = win_cpp::GetCursorPos();
	if (!window.IsThePointCapturedByTheWindowRegion(x, y)) {
		return false;
	}
	auto rect = window.GetClientRect();
	auto [lx, ty] = window.ClientToScreen(rect.get_left(), rect.get_top());
	auto [rx, by] = window.ClientToScreen(rect.get_right(), rect.get_bottom());
	rect = win_cpp::Rect(lx, ty, rx, by);
	return PtInPos(rect, x, y);
}

void updateWindowStyles(const win_cpp::Window& window) {
	auto rect = window.GetClientRect();
	auto style = window.getStyle();
	style &= ~(win_cpp::WindowStyle::values::WS_OVERLAPPEDWINDOW | win_cpp::WindowStyle::values::WS_POPUP);
	if (IsWindows10Version1607OrGreaterWin32()) {
		rect = AdjustWindowRectExForDpi(rect, false, window.GetDpiForWindow(),	style, window.getExtendedStyle());
	}	else {
		rect = AdjustWindowRectEx(rect, false, style, window.getExtendedStyle());
	}

	auto [rlx, rty] = window.ClientToScreen(rect.get_left(), rect.get_top());
	auto [rrx, rby] = window.ClientToScreen(rect.get_right(), rect.get_bottom());
	window.SetWindowStyle(style);
	window.SetWindowPosition(
		win_cpp::WindowZOrder::HWND_TOP,
		rect,
		win_cpp::SetWindowPosFlags::values::SWP_FRAMECHANGED
		| win_cpp::SetWindowPosFlags::values::SWP_NOACTIVATE
		| win_cpp::SetWindowPosFlags::values::SWP_NOZORDER
	);
}

void updateFramebufferTransparency(const win_cpp::Window& window) {
	// BOOL composition, opaque;
	auto composition = win_cpp::DwmIsCompositionEnabled();
	if (!composition) {
		return;
	}

	auto&& [color, opaque] = win_cpp::DwmGetColorizationColor();

	if (IsWindows8OrGreater() || !opaque) {
		win_cpp::RectRegion rr(0, 0, -1, -1);
		win_cpp::DwmEnableBlurBehindWindow(
			window,
			rr,
			win_cpp::DWM_BlurBehindFlags::values::ENABLE | win_cpp::DWM_BlurBehindFlags::values::BLURREGION,
			true,
			false
		);
	}	else {
		// HACK: Disable framebuffer transparency on Windows 7 when the
		//       colorization color is opaque, because otherwise the window
		//       contents is blended additively with the previous frame instead
		//       of replacing it
		win_cpp::DwmEnableBlurBehindWindow(window, win_cpp::DWM_BlurBehindFlags::values::ENABLE);
	}
}
glfw::WindowRectCallbackF dummy_window_rect_callback = [](const glfw::Rect&) constexpr noexcept {};
glfw::WindowCloseCallbackF dummy_window_close_callback = []() constexpr noexcept {};

#if 1

struct Config  {
	glfw::AspectRatio ar;
	bool ar_used;
	glfw::FrameAction fa;
	Input input;
	Cursor cursor;
	win_cpp::Mouse wmouse;

	struct Focus {
		bool isFocused = false;
	} focus;
	struct Monitor {
		bool state = false;
	} monitor;
	struct KeyMenu {
		bool state = false;
	} keymenu;
	bool autoIconify = false;
	short keycodes[512];

	glfw::WindowRectCallbackF window_rect_callback = dummy_window_rect_callback;
	void set_window_rect_callback(glfw::WindowRectCallbackF&& wrcb) {
		window_rect_callback = std::forward<decltype(wrcb)>(wrcb);
	}

	glfw::WindowCloseCallbackF window_close_callback = dummy_window_close_callback;
	void set_window_close_callback(glfw::WindowCloseCallbackF&& wcc) {
		window_close_callback = std::forward<decltype(wcc)>(wcc);
	}

	Config()
		: ar()
		, ar_used(false)
		, fa()
		, input()
		, cursor()
		, wmouse()
		, focus(false)
		, monitor(false)
		, keymenu(false)
		, autoIconify(false)
		, keycodes()
		, window_rect_callback(dummy_window_rect_callback)
		, window_close_callback(dummy_window_close_callback)
	{}
};

/* TODO remove window */
#if 0
auto cSC_SIZE = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1;
};

auto cSC_MOVE = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1;
};

auto cSC_MINIMIZE = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1;
};

auto cSC_MAXIMIZE = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1;
};

auto cSC_NEXTWINDOW = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_PREVWINDOW = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1;
};

auto cSC_CLOSE = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_VSCROLL = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_HSCROLL = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_MOUSEMENU = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_KEYMENU = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
	if (!cfg.keymenu.state) {
		return 0;
	}
	return 1;
};

auto cSC_ARRANGE = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_RESTORE = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_TASKLIST = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_SCREENSAVE = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		if (cfg.monitor.state) {
		return 0;
	}
	return 1;
};

auto cSC_HOTKEY = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_DEFAULT = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_MONITORPOWER = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		if (cfg.monitor.state) {
		return 0;
	}
	return 1; 
};

auto cSC_CONTEXTHELP = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_SEPARATOR = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

SysMenuCMDcallbacks<Config> syscmd_callbacks = {
	{ win_cpp::SystemMenuCommand::SC_SIZE, cSC_SIZE },
	{ win_cpp::SystemMenuCommand::SC_MOVE, cSC_MOVE },
	{ win_cpp::SystemMenuCommand::SC_MINIMIZE, cSC_MINIMIZE },
	{ win_cpp::SystemMenuCommand::SC_MAXIMIZE, cSC_MAXIMIZE },
	{ win_cpp::SystemMenuCommand::SC_NEXTWINDOW, cSC_NEXTWINDOW },
	{ win_cpp::SystemMenuCommand::SC_PREVWINDOW, cSC_PREVWINDOW },
	{ win_cpp::SystemMenuCommand::SC_CLOSE, cSC_CLOSE },
	{ win_cpp::SystemMenuCommand::SC_VSCROLL, cSC_VSCROLL },
	{ win_cpp::SystemMenuCommand::SC_HSCROLL, cSC_HSCROLL },
	{ win_cpp::SystemMenuCommand::SC_MOUSEMENU, cSC_MOUSEMENU },
	{ win_cpp::SystemMenuCommand::SC_KEYMENU, cSC_KEYMENU },
	{ win_cpp::SystemMenuCommand::SC_ARRANGE, cSC_ARRANGE },
	{ win_cpp::SystemMenuCommand::SC_RESTORE, cSC_RESTORE },
	{ win_cpp::SystemMenuCommand::SC_TASKLIST, cSC_TASKLIST },
	{ win_cpp::SystemMenuCommand::SC_SCREENSAVE, cSC_SCREENSAVE },
	{ win_cpp::SystemMenuCommand::SC_HOTKEY, cSC_HOTKEY },
	{ win_cpp::SystemMenuCommand::SC_DEFAULT, cSC_DEFAULT },
	{ win_cpp::SystemMenuCommand::SC_MONITORPOWER, cSC_MONITORPOWER },
	{ win_cpp::SystemMenuCommand::SC_CONTEXTHELP, cSC_CONTEXTHELP },
	{ win_cpp::SystemMenuCommand::SC_SEPARATOR, cSC_SEPARATOR }
};

auto cWM_PAINT = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long  {
#if 0
	win::t::PAINTSTRUCT ps;
	win::t::HBRUSH hBrush = win::f::CreateSolidBrush(0x00F0F0F0);
	win::t::HDC hdc = win::f::BeginPaint(win_cpp::Window::type(window), &ps);
	win::t::RECT rect;
	win::f::GetClientRect(win_cpp::Window::type(window), &rect);
	win::f::FillRect(hdc, &rect, hBrush);
	win::f::DeleteObject(hBrush);
	win::e::DrawTextFormatFlags flags =
		win::e::DrawTextFormatFlags::values::DT_CENTER
		| win::e::DrawTextFormatFlags::values::DT_VCENTER
		| win::e::DrawTextFormatFlags::values::DT_SINGLELINE;

	win::f::DrawTextA(hdc, "Hello World!", -1, &rect,
		win::e::DrawTextFormatFlags::MaskType(flags)
	);

	win::f::EndPaint(win_cpp::Window::type(window), &ps);
#endif
	return 0;
};
#endif

auto cWM_CLOSE = [](Config& cfg, const win_cpp::Window& window) -> win_cpp::window_proc_callback_result_type  {
	std::invoke(cfg.window_close_callback);
	return 0;
};

auto cWM_QUIT = []() -> win_cpp::window_proc_callback_result_type {
	return 0;
};

#if 0
auto cWM_CREATE = []( Config& cfg, const win_cpp::Window& window, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		return 0;
};

auto cWM_SIZE = []( Config& cfg, const win_cpp::Window& window, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		return 0;
};
#endif

auto cWM_SIZING = [](Config& cfg, const win_cpp::Window& window, win_cpp::Edges edges, win_cpp::Rect& rect) -> win_cpp::window_proc_callback_result_type {
	if (cfg.ar_used) {
		rect = applyAspectRatio(window, edges, rect, cfg.ar);
	}
	cfg.window_rect_callback(glfw::Rect(rect.get_left(), rect.get_top(), rect.get_right(), rect.get_bottom()));
	return true;
};

auto cWM_MOUSEACTIVATE = [](Config& cfg, const win_cpp::Window& window, win_cpp::WindowMessage wmsg, win_cpp::HitTest ht) -> win_cpp::window_proc_callback_result_type  {
	if (wmsg == win_cpp::WindowMessage::WM_LBUTTONDOWN) {
		if (ht != win_cpp::HitTest::HTCLIENT) {
			cfg.fa.set_state(glfw::FrameActionState::enabled);
		}
	}
	return std::nullopt;
};

auto cWM_CAPTURECHANGED = [](Config& cfg, const win_cpp::Window& window, bool has_parent_window) -> win_cpp::window_proc_callback_result_type {
	if (!has_parent_window && std::to_underlying(cfg.fa.get_state())) {
		if (cfg.cursor.get_state() == glfw::CursorState::disabled) {
			cfg.cursor.disable(window);
		}	else if (cfg.cursor.get_state() == glfw::CursorState::captured) {
			cfg.cursor.capture(window);
		}
		cfg.fa.set_state(glfw::FrameActionState::disabled);
	}
	return std::nullopt;
};

auto cWM_SETFOCUS = [](Config& cfg, const win_cpp::Window& window) -> win_cpp::window_proc_callback_result_type {
	cfg.focus.isFocused = true;
	if (cfg.fa.get_state() == glfw::FrameActionState::enabled) {
		if (cfg.cursor.get_state() == glfw::CursorState::disabled) {
			cfg.cursor.disable(window);
		} else if (cfg.cursor.get_state() == glfw::CursorState::captured) {
			cfg.cursor.capture(window);
		}
	}
	return std::nullopt;
	// return 0;
};

auto cWM_KILLFOCUS = [](Config& cfg, const win_cpp::Window& window) -> win_cpp::window_proc_callback_result_type {
	if (cfg.fa.get_state() == glfw::FrameActionState::enabled) {
		if (cfg.cursor.get_state() == glfw::CursorState::disabled) {
			cfg.cursor.disable(window);
		}	else if (cfg.cursor.get_state() == glfw::CursorState::captured) {
			cfg.cursor.capture(window);
		}
	}
	if (cfg.monitor.state && cfg.autoIconify) {
		auto iconify = []() {};
		iconify();
	}
	cfg.focus.isFocused = true;
	return 0;
};

#if 0
auto cWM_SYSCOMMAND = [cbs = syscmd_callbacks]( Config& cfg, const win_cpp::Window& window, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
	auto x = static_cast<win_cpp::SystemMenuCommand>(windowData.wParam & 0xfff0);
	auto it = cbs.find(x);

	if (it != cbs.end()) {
		auto res = std::invoke(it->second, window, cfg, windowData);
		if (!res) {	return 0;	}
	}

	return win::f::DefWindowProcW(
		win_cpp::Window::type(window),
		std::to_underlying(win_cpp::WindowMessage::WM_SYSCOMMAND),
		windowData.wParam,
		windowData.lParam
	);
};
#endif

#if 0
auto cWM_INPUTLANGCHANGE = []( Config& cfg, const win_cpp::Window& window, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
	auto UpdateKeyNames = []() {};
	UpdateKeyNames();
	return win::f::DefWindowProcW(
		win_cpp::Window::type(window),
		std::to_underlying(win_cpp::WindowMessage::WM_INPUTLANGCHANGE),
		windowData.wParam,
		windowData.lParam
	);
};
#endif

#if 0
auto cWM_CHAR = [](Config& cfg, const win_cpp::Window& window, wchar_t character, const win_cpp::WindowsKeyData& data) -> win_cpp::window_proc_callback_result_type {
	// ranges of UTF-16 surrogate pair 
	constexpr unsigned short SURROGATE_HIGH_START		= 0xD800;
	constexpr unsigned short SURROGATE_HIGH_END			= 0xDBFF;
	constexpr unsigned short SURROGATE_LOW_START		= 0xDC00;
	constexpr unsigned short SURROGATE_LOW_END			= 0xDFFF;
	// basic shift for translate surrogate pait into codepoint
	constexpr unsigned int   SURROGATE_OFFSET				= 0x10000;
	// nBits for shift high surrogate
	constexpr int            SURROGATE_SHIFT_BITS		= 10;

	thread_local static wchar_t high_surrogate = 0;

	if (character >= SURROGATE_HIGH_START && character <= SURROGATE_HIGH_END) {
		high_surrogate = character;
	} else {
		std::pair<wchar_t, wchar_t> charPair;

		if (character >= SURROGATE_LOW_START && character <= SURROGATE_LOW_END) {
			if (high_surrogate != 0) {
				charPair = { high_surrogate, character };
			} else {
				charPair = { character, 0 };
			}
		} else {
			charPair = { character, 0 };
		}
		high_surrogate = 0;
		cfg.input.process_Char(charPair, getKeyMods(), true);
	}

	return 0;
};

auto cWM_SYSCHAR = [](Config& cfg, const win_cpp::Window& window, wchar_t character, const win_cpp::WindowsKeyData& data) -> win_cpp::window_proc_callback_result_type {
	// ranges of UTF-16 surrogate pair 
	constexpr unsigned short SURROGATE_HIGH_START		= 0xD800;
	constexpr unsigned short SURROGATE_HIGH_END			= 0xDBFF;
	constexpr unsigned short SURROGATE_LOW_START		= 0xDC00;
	constexpr unsigned short SURROGATE_LOW_END			= 0xDFFF;
	// basic shift for translate surrogate pait into codepoint
	constexpr unsigned int   SURROGATE_OFFSET				= 0x10000;
	// nBits for shift high surrogate
	constexpr int            SURROGATE_SHIFT_BITS		= 10;

	thread_local static wchar_t high_surrogate = 0;
	if (character >= SURROGATE_HIGH_START && character <= SURROGATE_HIGH_END) {
		high_surrogate = character;
	} else {
		std::pair<wchar_t, wchar_t> charPair;

		if (character >= SURROGATE_LOW_START && character <= SURROGATE_LOW_END) {
			if (high_surrogate != 0) {
				charPair = { high_surrogate, character };
			} else {
				charPair = { character, 0 };
			}
		} else {
			charPair = { character, 0 };
		}
		high_surrogate = 0;
		cfg.input.process_Char(charPair, getKeyMods(), false);
	}

	if(cfg.keymenu.state) {
		return std::nullopt;
	}

	return 0;
};
#endif
auto cWM_UNICHAR = [](Config& cfg, const win_cpp::Window& window, unsigned codepoint, const win_cpp::WindowsKeyData& data) -> long long  {
	if (codepoint == 0xFFFF) {
		return true;
	}

	cfg.input.process_Char(codepoint, getKeyMods(), true);
	return 0;
};

auto cWM_KEYDOWN = [](Config& cfg, const win_cpp::Window& window, win_cpp::VirtualKeysStandardSet vk, const win_cpp::WindowsKeyData& data) -> win_cpp::window_proc_callback_result_type {
	glfw::KeyState action = glfw::KeyState::press;
	glfw::CharModsFlags mods = getKeyMods();
	glfw::Key key = to_glfw_key(data.scanCode);
	cfg.input.process_Key(key, std::to_underlying(data.scanCode), action, mods);
	return 0;
};

auto cWM_SYSKEYDOWN = [](Config& cfg, const win_cpp::Window& window, win_cpp::VirtualKeysStandardSet vk, const win_cpp::WindowsKeyData& data) -> win_cpp::window_proc_callback_result_type {
	glfw::KeyState action = glfw::KeyState::press;
	glfw::CharModsFlags mods = getKeyMods();
	glfw::Key key = to_glfw_key(data.scanCode);
	cfg.input.process_Key(key, std::to_underlying(data.scanCode), action, mods);
	return 0;
};

auto cWM_KEYUP = [](Config& cfg, const win_cpp::Window& window, win_cpp::VirtualKeysStandardSet vk, const win_cpp::WindowsKeyData& data) -> win_cpp::window_proc_callback_result_type {
	glfw::KeyState action = glfw::KeyState::release;
	glfw::CharModsFlags mods = getKeyMods();
	glfw::Key key = to_glfw_key(data.scanCode);
	cfg.input.process_Key(key, std::to_underlying(data.scanCode), action, mods);
	return 0;
};

auto cWM_SYSKEYUP = [](Config& cfg, const win_cpp::Window& window, win_cpp::VirtualKeysStandardSet vk, const win_cpp::WindowsKeyData& data) -> win_cpp::window_proc_callback_result_type {
	glfw::KeyState action = glfw::KeyState::release;
	glfw::CharModsFlags mods = getKeyMods();
	glfw::Key key = to_glfw_key(data.scanCode);
	cfg.input.process_Key(key, std::to_underlying(data.scanCode), action, mods);
	return 0;
};

auto cWM_MOUSEMOVE = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type  {
	auto&& [x, y] = m_pos;

	if (!cfg.wmouse.isTracking()) {
		cfg.wmouse.StartTracking(window, win_cpp::TrackMouseEventFlags::values::TME_LEAVE);
		cfg.cursor.enter();
	}

	if (cfg.cursor.get_state() == glfw::CursorState::disabled) {
		auto [lx, ly] = cfg.cursor.get_position();
		auto dx = x - lx;
		auto dy = y - ly;
		if (cfg.cursor.get_RawInputState() == glfw::CursorRawInputState::enabled) {
			return 0; // ?
		}
		
		// set virtual pos
	}
	cfg.cursor.set_position(x, y);

	return 0;
};

auto cWM_RAW_INPUT_MOUSE = [](Config& cfg, const win_cpp::Window& window, win_cpp::RawInputType rit, const win_cpp::RawInputMouseData& data) -> win_cpp::window_proc_callback_result_type {
	std::pair<long, long> dxy;
	auto& [dx, dy] = dxy;
	if (data.dwFlags & win_cpp::MouseIndicatorFlags::values::MOUSE_MOVE_ABSOLUTE) {
		std::pair<long, long> point;
		auto& [x, y] = point;
		int width, height;
		if (data.dwFlags & win_cpp::MouseIndicatorFlags::values::MOUSE_VIRTUAL_DESKTOP) {
			x += win_cpp::GetSystemMetrics(win_cpp::SystemMetrics::SM_XVIRTUALSCREEN);
			y += win_cpp::GetSystemMetrics(win_cpp::SystemMetrics::SM_YVIRTUALSCREEN);
			width = win_cpp::GetSystemMetrics(win_cpp::SystemMetrics::SM_CXVIRTUALSCREEN);
			height = win_cpp::GetSystemMetrics(win_cpp::SystemMetrics::SM_CYVIRTUALSCREEN);
		}	else {
			width = win_cpp::GetSystemMetrics(win_cpp::SystemMetrics::SM_CXSCREEN);
			height = win_cpp::GetSystemMetrics(win_cpp::SystemMetrics::SM_CYSCREEN);
		}
		auto& [lx, ly] = data.lLastXY;
		constexpr float magic = 65535.0f;
		x += (lx / magic) * width;
		y += (ly / magic) * height;
		window.ClientToScreen(point);

		auto&& [px, py] = cfg.cursor.get_position();
		dx = x - px;
		dy = y - py;
	} else {
		dxy = data.lLastXY;
	}
	std::cout << "RawMouseInput: | x " << dxy.first << " | y " << dxy.second << std::endl;
	cfg.cursor.set_position(dxy.first, dxy.second);
	return std::nullopt;
};

auto cWM_MOUSELEAVE = [](Config& cfg, const win_cpp::Window& window) -> win_cpp::window_proc_callback_result_type {
	if (cfg.wmouse.isTracking()) {
		cfg.wmouse.StopTracking();
	}

	return 0;
};

auto cWM_RAW_INPUT_KEYBOARD = [](Config& cfg, const win_cpp::Window& window, win_cpp::RawInputType tir, const win_cpp::RawInputKeyboardData& data) -> win_cpp::window_proc_callback_result_type { 
	return std::nullopt;
};

auto cWM_RAW_INPUT_HID = [](Config& cfg, const win_cpp::Window& window, win_cpp::RawInputType rit, const win_cpp::RawInputHIDData&) -> win_cpp::window_proc_callback_result_type {
	return std::nullopt;
};

auto cWM_LBUTTONDOWN = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type {
	auto action = glfw::KeyState::press;
	auto key = glfw::Key::vLMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_MBUTTONDOWN = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type {
	auto action = glfw::KeyState::press;
	auto key = glfw::Key::vMMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_RBUTTONDOWN = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type {
	auto action = glfw::KeyState::press;
	auto key = glfw::Key::vRMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_XBUTTONDOWN = [](Config& cfg, const win_cpp::Window& window, unsigned n_button, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_keys_down) -> win_cpp::window_proc_callback_result_type {
		return 0;
};

auto cWM_LBUTTONUP = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type {
	auto action = glfw::KeyState::release;
	auto key = glfw::Key::vLMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_MBUTTONUP = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type {
	auto action = glfw::KeyState::release;
	auto key = glfw::Key::vMMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_RBUTTONUP = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type {
	auto action = glfw::KeyState::release;
	auto key = glfw::Key::vRMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_XBUTTONUP = [](Config& cfg, const win_cpp::Window& window, unsigned n_button, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_keys_down) -> win_cpp::window_proc_callback_result_type {
	return 0;
};

#if 0
auto cWM_MOUSEHWHEEL = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		// _glfwInputScroll(window, 0.0, (SHORT)HIWORD(wParam) / (double)WHEEL_DELTA);
	return 0;
};

auto cWM_MOUSEVWHEEL = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		// _glfwInputScroll(window, -((SHORT)HIWORD(wParam) / (double)WHEEL_DELTA), 0.0);
	return 0;
};

auto cWM_ENTERSIZEMOVE = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		if (cfg.fa.get_state() == glfw::FrameActionState::enabled) {
		return 0;
	}
	if (cfg.cursor.get_state() == glfw::CursorState::disabled) {
		cfg.cursor.enable(window);
	}	else if (cfg.cursor.get_state() == glfw::CursorState::captured) {
		cfg.cursor.capture(window);
	}
	return 0;
};

auto cWM_ENTERMENULOOP = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
	if (cfg.fa.get_state() == glfw::FrameActionState::enabled) {
		return 0;
	}
	if (cfg.cursor.get_state() == glfw::CursorState::disabled) {
		cfg.cursor.enable(window);
	}	else if (cfg.cursor.get_state() == glfw::CursorState::captured) {
		cfg.cursor.capture(window);
	}
	return 0;
};

auto cWM_EXITSIZEMOVE = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long  {
	if (cfg.fa.get_state() == glfw::FrameActionState::enabled) {
		return 0;
	}
	if (cfg.cursor.get_state() == glfw::CursorState::disabled) {
		cfg.cursor.disable(window);
	}	else if (cfg.cursor.get_state() == glfw::CursorState::captured) {
		cfg.cursor.release(window);
	}
	return 0;
};

auto cWM_EXITMENULOOP = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		if (cfg.fa.get_state() == glfw::FrameActionState::enabled) {
		return 0;
	}
	if (cfg.cursor.get_state() == glfw::CursorState::disabled) {
		cfg.cursor.disable(window);
	}	else if (cfg.cursor.get_state() == glfw::CursorState::captured) {
		cfg.cursor.release(window);
	}
	return 0;
};
#endif
#endif

#if 1
void setup_callbacks(Config& cfgx, const win_cpp::Window& window) {
	auto rc = std::ref(cfgx);
	auto rw = std::ref(window);
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_CLOSE>([cfg = rc, wnd = rw , cWM_CLOSEc = cWM_CLOSE]() { return std::invoke(cWM_CLOSEc, cfg.get(), wnd.get()); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_QUIT>([cWM_QUITc = cWM_QUIT]() { return std::invoke(cWM_QUITc); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_SIZING>([cfg = rc, wnd = rw, cWM_SIZINGc = cWM_SIZING](win_cpp::Edges edges, win_cpp::Rect& rect) { return std::invoke(cWM_SIZINGc, cfg.get(), wnd.get(), edges, rect); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_MOUSEACTIVATE>([cfg = rc, wnd = rw, cWM_MOUSEACTIVATEc = cWM_MOUSEACTIVATE](win_cpp::WindowMessage wmsg, win_cpp::HitTest ht) { return std::invoke(cWM_MOUSEACTIVATEc, cfg.get(), wnd.get(), wmsg, ht); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_CAPTURECHANGED>([cfg = rc, wnd = rw, cWM_CAPTURECHANGEDc = cWM_CAPTURECHANGED](bool has_parent_window) { return std::invoke(cWM_CAPTURECHANGEDc, cfg.get(), wnd.get(), has_parent_window); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_SETFOCUS>([cfg = rc, wnd = rw, cWM_SETFOCUSc = cWM_SETFOCUS]() { return std::invoke(cWM_SETFOCUSc, cfg.get(), wnd.get()); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_KILLFOCUS>([cfg = rc, wnd = rw, cWM_KILLFOCUSc = cWM_KILLFOCUS]() { return std::invoke(cWM_KILLFOCUSc, cfg.get(), wnd.get()); });
//cbh.WM_CHAR_callback								= [cfg = rc, wnd = rw, cWM_CHARc = cWM_CHAR](wchar_t character, const win_cpp::WindowsKeyData& data) { return std::invoke(cWM_CHARc, cfg.get(), wnd.get(), character, data); };
//cbh.WM_SYSCHAR_callback							= [cfg = rc, wnd = rw, cWM_SYSCHARc = cWM_SYSCHAR](wchar_t character, const win_cpp::WindowsKeyData& data) { return std::invoke(cWM_SYSCHARc, cfg.get(), wnd.get(), character, data); };
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_UNICHAR>([cfg = rc, wnd = rw, cWM_UNICHARc = cWM_UNICHAR](unsigned codepoint, const win_cpp::WindowsKeyData& data) { return std::invoke(cWM_UNICHARc, cfg.get(), wnd.get(), codepoint, data); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_MOUSEMOVE>([cfg = rc, wnd = rw, cWM_MOUSEMOVEc = cWM_MOUSEMOVE](const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) { return std::invoke(cWM_MOUSEMOVEc, cfg.get(), wnd.get(), m_pos, m_botton_down); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_SYSKEYDOWN>([cfg = rc, wnd = rw, cWM_SYSKEYDOWNc = cWM_SYSKEYDOWN](win_cpp::VirtualKeysStandardSet vk, const win_cpp::WindowsKeyData& data) { return std::invoke(cWM_SYSKEYDOWNc, cfg.get(), wnd.get(), vk, data); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_SYSKEYUP>([cfg = rc, wnd = rw, cWM_SYSKEYUPc = cWM_SYSKEYUP](win_cpp::VirtualKeysStandardSet vk, const win_cpp::WindowsKeyData& data) {return std::invoke(cWM_SYSKEYUPc, cfg.get(), wnd.get(), vk, data); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_KEYDOWN>([cfg = rc, wnd = rw, cWM_KEYDOWNc = cWM_KEYDOWN](win_cpp::VirtualKeysStandardSet vk, const win_cpp::WindowsKeyData& data) {return std::invoke(cWM_KEYDOWNc, cfg.get(), wnd.get(), vk, data); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_KEYUP>([cfg = rc, wnd = rw, cWM_KEYUPc = cWM_KEYUP](win_cpp::VirtualKeysStandardSet vk, const win_cpp::WindowsKeyData& data) {return std::invoke(cWM_KEYUPc, cfg.get(), wnd.get(), vk, data); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_LBUTTONDOWN>([cfg = rc, wnd = rw, cWM_LBUTTONDOWNc = cWM_LBUTTONDOWN](const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) { return std::invoke(cWM_LBUTTONDOWNc, cfg.get(), wnd.get(), m_pos, m_botton_down); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_LBUTTONUP>([cfg = rc, wnd = rw, cWM_LBUTTONUPc = cWM_LBUTTONUP](const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) { return std::invoke(cWM_LBUTTONUPc, cfg.get(), wnd.get(), m_pos, m_botton_down); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_MBUTTONDOWN>([cfg = rc, wnd = rw, cWM_MBUTTONDOWNc = cWM_MBUTTONDOWN](const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) { return std::invoke(cWM_MBUTTONDOWNc, cfg.get(), wnd.get(), m_pos, m_botton_down); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_MBUTTONUP>([cfg = rc, wnd = rw, cWM_MBUTTONUPc = cWM_MBUTTONUP](const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) { return std::invoke(cWM_MBUTTONUPc, cfg.get(), wnd.get(), m_pos, m_botton_down); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_RBUTTONDOWN>([cfg = rc, wnd = rw, cWM_RBUTTONDOWNc = cWM_RBUTTONDOWN](const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) { return std::invoke(cWM_RBUTTONDOWNc, cfg.get(), wnd.get(), m_pos, m_botton_down); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_RBUTTONUP>([cfg = rc, wnd = rw, cWM_RBUTTONUPc = cWM_RBUTTONUP](const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) { return std::invoke(cWM_RBUTTONUPc, cfg.get(), wnd.get(), m_pos, m_botton_down); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_XBUTTONDOWN>([cfg = rc, wnd = rw, cWM_XBUTTONDOWNc = cWM_XBUTTONDOWN](unsigned n_key, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) { return std::invoke(cWM_XBUTTONDOWNc, cfg.get(), wnd.get(), n_key, m_pos, m_botton_down); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_XBUTTONUP>([cfg = rc, wnd = rw, cWM_XBUTTONUPc = cWM_XBUTTONUP](unsigned n_key, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) { return std::invoke(cWM_XBUTTONUPc, cfg.get(), wnd.get(), n_key, m_pos, m_botton_down); });
	window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_MOUSELEAVE>([cfg = rc, wnd = rw, cWM_MOUSELEAVEc = cWM_MOUSELEAVE]() { return std::invoke(cWM_MOUSELEAVEc, cfg.get(), wnd.get()); });
	/* TODO */
	// cbh.WM_RAW_INPUT_MOUSE_callback			= [cfg = r, cWM_WM_RAW_INPUT_MOUSEc = cWM_RAW_INPUT_MOUSE](win_cpp::RawInputType rit, win_cpp::RawInputMouseData data) { return std::invoke(cWM_WM_RAW_INPUT_MOUSEc, cfg.get(), rit, data); };
	// cbh.WM_RAW_INPUT_KEYBOARD_callback	= [cfg = r, cWM_RAW_INPUT_KEYBOARDc = cWM_RAW_INPUT_KEYBOARD](win_cpp::RawInputType rit, win_cpp::RawInputKeyboardData data) { return std::invoke(cWM_RAW_INPUT_KEYBOARDc, cfg.get(), rit, data); };
	// cbh.WM_RAW_INPUT_HID_callback				= [cfg = r, cWM_RAW_INPUT_HIDc = cWM_RAW_INPUT_HID](win_cpp::RawInputType rit, win_cpp::RawInputHIDData data) { return std::invoke(cWM_RAW_INPUT_HIDc, cfg.get(), rit, data); };
}
#endif

win_cpp::MainClassCreateInfo get_mainclass_info(const win_cpp::Instance& instance) {
	win_cpp::LoadImageStandardCursorInfo cursor_image_info = {};
	cursor_image_info.cx = 0;
	cursor_image_info.cy = 0;
	cursor_image_info.fuLoad =
		win_cpp::LR_Flags::values::LR_DEFAULTSIZE
		| win_cpp::LR_Flags::values::LR_SHARED;
	cursor_image_info.standard_cursor = win_cpp::StandardCursors::IDC_ARROW;
	win_cpp::Icon cursor(cursor_image_info);

	win_cpp::LoadImageStandardIconInfo icon_image_info = {};
	icon_image_info.cx = 0;
	icon_image_info.cy = 0;
	icon_image_info.fuLoad =
		win_cpp::LR_Flags::values::LR_DEFAULTSIZE
		| win_cpp::LR_Flags::values::LR_SHARED;
	icon_image_info.standard_icon = win_cpp::StandardIcons::IDI_APPLICATION;
	win_cpp::Icon icon(icon_image_info);

	win_cpp::MainClassCreateInfo mainclass_info = {};
	mainclass_info.window_style =
		win_cpp::WindowClassStyle::values::CS_HREDRAW
		| win_cpp::WindowClassStyle::values::CS_VREDRAW
		| win_cpp::WindowClassStyle::values::CS_OWNDC;

	mainclass_info.ClassName = L"WINDOW_CLASS";
	mainclass_info.instance = instance;
	mainclass_info.cursor = cursor;
	mainclass_info.icon = icon;

	return mainclass_info;
}

win_cpp::WindowStyle get_WindowStyle(const glfw::WindowCreateInfo& glfw_window_info) {
	/* TODO */
	return win_cpp::WindowStyle::values::WS_OVERLAPPEDWINDOW;
}

win_cpp::ExtendedWindowStyle get_WindowStyleEX(const glfw::WindowCreateInfo& glfw_window_info) {
	/* TODO */
	return win_cpp::ExtendedWindowStyle::values::WS_EX_TOPMOST;
}

win_cpp::Rect to_win_rect(const glfw::Rect& glfw_rect) {
	return win_cpp::Rect{ glfw_rect.get_left(), glfw_rect.get_top(), glfw_rect.get_right(), glfw_rect.get_bottom() };
}

win_cpp::Title to_win_title(const glfw::Title& title) {
	return win_cpp::Title(title.get_sv());
}

win_cpp::WindowCreateInfo win32_window_create_info(
	const win_cpp::Instance& instance,
	const win_cpp::MainClass& main_class,
	const win_cpp::Rect& rect,
	const win_cpp::Title& title,
	win_cpp::WindowStyle style,
	win_cpp::ExtendedWindowStyle ExStyle
) {
	win_cpp::WindowCreateInfo window_info = {};
	window_info.dwStyle = style;
	window_info.dwExStyle = ExStyle;
	window_info.instance = instance;
	window_info.lpWindowName = title.get_w();
	window_info.main_class = main_class;
	window_info.X = rect.get_left();
	window_info.Y = rect.get_top();
	window_info.nHeight = rect.get_right() - rect.get_left();
	window_info.nWidth = rect.get_bottom() - rect.get_top();
	return window_info;
}

namespace win32_window {
	win_cpp::Instance instance;
	win_cpp::MainClass main_class{ get_mainclass_info(instance) };

	export struct GLFW_Window_Win
		: glfw::wVisible
		, glfw::wResizable
		, glfw::wDecorated
		, glfw::wFocused
		, glfw::wAutoiconify
		, glfw::wFloating
		, glfw::wMaximized
		, glfw::wCenterCursor
		, glfw::wTransparent
		, glfw::wFocusOnShow
		, glfw::wScaleToMonitor
	{
		private:
			Config config;
			win_cpp::Window window;

		public:
			GLFW_Window_Win(const glfw::WindowCreateInfo& info)
				: wVisible(info.visible)
				, wResizable(info.resizable)
				, wDecorated(info.decorated)
				, wFocused(info.focused)
				, wAutoiconify(info.autoiconify)
				, wFloating(info.floating)
				, wMaximized(info.maximized)
				, wCenterCursor(info.center_cursor)
				, wTransparent(info.transparent)
				, wFocusOnShow(info.focus_on_show)
				, wScaleToMonitor(info.scale_to_monitor)
				, config() 
				, window(win32_window_create_info(
						instance,
						main_class,
						to_win_rect(info.rect),
						to_win_title(info.title),
						get_WindowStyle(info),
						get_WindowStyleEX(info)
					)
				)
			{
				setup_callbacks(config, window);
				window.show();
			} // ctor

		public:
			glfw::Title get_Title() const {
				return glfw::Title(window.get_Title().get_c()); 
			}
			void set_Title(const glfw::Title& title) { 
				window.set_Title(win_cpp::Title{ title.get_sv() });
			}

			// glfw::Icon get_Icon() const { get_Icon(); } 
			void set_Icon(const glfw::Icon& icon) { }

			glfw::Rect get_Position() const {
				auto win_rect = window.GetClientRect();
				return glfw::Rect(win_rect.get_left(), win_rect.get_top(), win_rect.get_right(), win_rect.get_bottom());
			}
			void set_Position(const glfw::Rect& rect) { 
				win_cpp::Rect wrect(rect.get_left(), rect.get_top(), rect.get_right(), rect.get_bottom());
				win_cpp::WindowZOrder order = win_cpp::WindowZOrder::HWND_TOPMOST;
				win_cpp::SetWindowPosFlags swp = win_cpp::SetWindowPosFlags::values::SWP_NOZORDER;
				window.SetWindowPosition(order, wrect, swp);
			}

			glfw::SizeLimits get_SizeLimits() const { return glfw::SizeLimits(0, 0); }
			void set_SizeLimits(const glfw::SizeLimits& s_limits) {} // set_SizeLimits(s_limits); }
#if 0 /* TODO*/
			glfw::AspectRatio get_AspectRatio() const { return get_AspectRatio(); }
			void set_AspectRation(const glfw::AspectRatio& aspect_ratio) { set_AspectRatio(aspect_ratio); }
#endif		
			// glfw::Opacity_type get_Opacity() const { get_Opacity(); }
			// void set_Opacity(const glfw::Opacity_type& opacity) { set_Opacity(); }

			void maximize() { window.maximize(); }
			void show() { window.show(); }
			void hide() { window.hide(); }
			void focus() { window.focus(); }

		public:
			void set_key_mods_callback(glfw::CharModsCallbackF&& cmc) {
				config.input.set_key_mods_callback(std::forward<decltype(cmc)>(cmc));
			}
			void set_character_callback(glfw::CharacterCallbackF&& cc) {
				config.input.set_character_callback(std::forward<decltype(cc)>(cc));
			}
			void set_key_callback(glfw::KeyCallbackF&& kc) {
				config.input.set_key_callback(std::forward<decltype(kc)>(kc));
			}
			void set_cursor_position_callback(glfw::CursorPositionCallbackT&& cpct) {
				config.cursor.set_cursor_position_callback(std::forward<decltype(cpct)>(cpct));
			}
			void set_cursor_state_callback(glfw::CursorStateCallbackT&& csct) {
				config.cursor.set_cursor_state_callback(std::forward<decltype(csct)>(csct));
			}
			void set_window_rect_callback(glfw::WindowRectCallbackF&& wrb) {
				config.set_window_rect_callback(std::forward<decltype(wrb)>(wrb));
			}
			void set_window_close_callback(glfw::WindowCloseCallbackF&& wcc) {
				config.set_window_close_callback(std::forward<decltype(wcc)>(wcc));
			}

			const win_cpp::Window& get_win_window() const {
				if (!win_cpp::Window::type(window)) { throw; }
				return window;
			}
	}; // struct GLFW_Window_Win

	static_assert(glfw::WindowLikeWithDefaultConfig<GLFW_Window_Win>);

	export vk::raii::SurfaceKHR get_vk_raii_SurfaceKHR(
		const vk::raii::Instance& vk_instance,
		const glfw::Window<GLFW_Window_Win>& glfw_window
	) {
		const GLFW_Window_Win& n_window = static_cast<const GLFW_Window_Win&>(glfw_window);
		const win_cpp::Window& window = n_window.get_win_window();
		vk::Win32SurfaceCreateInfoKHR Win32SurfaceCreateInfo = {};
		vk::Win32SurfaceCreateFlagBitsKHR create_flags = {};
		using vk_hinstance_type = decltype(Win32SurfaceCreateInfo.hinstance);
		using vk_hwnd_type = decltype(Win32SurfaceCreateInfo.hwnd);
		// static_assert(std::same_as<vk_hinstance_type, win_Instance_type>);
		auto vp_i = static_cast<void*>(win_cpp::Instance::type(instance));
		auto vp_h = static_cast<void*>(win_cpp::Window::type(window));
		Win32SurfaceCreateInfo.setHinstance((win_cpp::HINSTANCE)vp_i);
		Win32SurfaceCreateInfo.setHwnd((win_cpp::HWND)vp_h);
		Win32SurfaceCreateInfo.setFlags(create_flags);
		return vk::raii::SurfaceKHR(vk_instance, Win32SurfaceCreateInfo);
	}

} // ns 
