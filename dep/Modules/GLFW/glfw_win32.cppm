module;

export module glfw_win32;
import std;
import flags;
import win_cpp;
// import windowProc;
import glfw_base;
import vulkan; // REMOVE IT!

using translate_map_type = std::unordered_map<win_cpp::WindowsScancode, glfw_base::Key>;
translate_map_type windows_keyboard_keys_to_glfw_keys = {
			{ win_cpp::WindowsScancode::NULL, glfw_base::Key::NULL },
			{ win_cpp::WindowsScancode::vA, glfw_base::Key::vA },
			{ win_cpp::WindowsScancode::vB, glfw_base::Key::vB },
			{ win_cpp::WindowsScancode::vC, glfw_base::Key::vC },
			{ win_cpp::WindowsScancode::vD, glfw_base::Key::vD },
			{ win_cpp::WindowsScancode::vE, glfw_base::Key::vE },
			{ win_cpp::WindowsScancode::vF, glfw_base::Key::vF },
			{ win_cpp::WindowsScancode::vG, glfw_base::Key::vG },
			{ win_cpp::WindowsScancode::vH, glfw_base::Key::vH },
			{ win_cpp::WindowsScancode::vI, glfw_base::Key::vI },
			{ win_cpp::WindowsScancode::vJ, glfw_base::Key::vJ },
			{ win_cpp::WindowsScancode::vK, glfw_base::Key::vK },
			{ win_cpp::WindowsScancode::vL, glfw_base::Key::vL },
			{ win_cpp::WindowsScancode::vM, glfw_base::Key::vM },
			{ win_cpp::WindowsScancode::vN, glfw_base::Key::vN },
			{ win_cpp::WindowsScancode::vO, glfw_base::Key::vO },
			{ win_cpp::WindowsScancode::vP, glfw_base::Key::vP },
			{ win_cpp::WindowsScancode::vQ, glfw_base::Key::vQ },
			{ win_cpp::WindowsScancode::vR, glfw_base::Key::vR },
			{ win_cpp::WindowsScancode::vS, glfw_base::Key::vS },
			{ win_cpp::WindowsScancode::vT, glfw_base::Key::vT },
			{ win_cpp::WindowsScancode::vU, glfw_base::Key::vU },
			{ win_cpp::WindowsScancode::vV, glfw_base::Key::vV },
			{ win_cpp::WindowsScancode::vW, glfw_base::Key::vW },
			{ win_cpp::WindowsScancode::vX, glfw_base::Key::vX },
			{ win_cpp::WindowsScancode::vY, glfw_base::Key::vY },
			{ win_cpp::WindowsScancode::vZ, glfw_base::Key::vZ },
			{ win_cpp::WindowsScancode::v1_and_Bang, glfw_base::Key::v1_and_Bang },
			{ win_cpp::WindowsScancode::v2_and_At, glfw_base::Key::v2_and_At },
			{ win_cpp::WindowsScancode::v3_and_Hash, glfw_base::Key::v3_and_Hash },
			{ win_cpp::WindowsScancode::v4_and_Dollar, glfw_base::Key::v4_and_Dollar },
			{ win_cpp::WindowsScancode::v5_and_Percent, glfw_base::Key::v5_and_Percent },
			{ win_cpp::WindowsScancode::v6_and_Caret, glfw_base::Key::v6_and_Caret },
			{ win_cpp::WindowsScancode::v7_and_Ampersand, glfw_base::Key::v7_and_Ampersand },
			{ win_cpp::WindowsScancode::v8_and_Star, glfw_base::Key::v8_and_Star },
			{ win_cpp::WindowsScancode::v9_and_Left_Bracket, glfw_base::Key::v9_and_Left_Bracket },
			{ win_cpp::WindowsScancode::v0_and_Right_Brackert, glfw_base::Key::v0_and_Right_Brackert },
			{ win_cpp::WindowsScancode::vReturnEnter, glfw_base::Key::vReturnEnter },
			{ win_cpp::WindowsScancode::vEscape, glfw_base::Key::vEscape },
			{ win_cpp::WindowsScancode::vDelete, glfw_base::Key::vDelete },
			{ win_cpp::WindowsScancode::vTab, glfw_base::Key::vTab },
			{ win_cpp::WindowsScancode::vSpaceBar, glfw_base::Key::vSpaceBar },
			{ win_cpp::WindowsScancode::vDash_and_underscore, glfw_base::Key::vDash_and_underscore },
			{ win_cpp::WindowsScancode::vEquals_and_Plus, glfw_base::Key::vEquals_and_Plus },
			{ win_cpp::WindowsScancode::vLeft_Brace, glfw_base::Key::vLeft_Brace },
			{ win_cpp::WindowsScancode::vRight_Brace, glfw_base::Key::vRight_Brace },
			{ win_cpp::WindowsScancode::vBackslash_and_Pipe, glfw_base::Key::vBackslash_and_Pipe },
			{ win_cpp::WindowsScancode::vNonUS_Slash_and_Tilde, glfw_base::Key::vNonUS_Slash_and_Tilde }, // orig,  
			{ win_cpp::WindowsScancode::vSemiColon_and_Colon, glfw_base::Key::vSemiColon_and_Colon },
			{ win_cpp::WindowsScancode::vApostrophe_and_Double_Quotation_Mark, glfw_base::Key::vApostrophe_and_Double_Quotation_Mark },
			{ win_cpp::WindowsScancode::vGrave_Accent_and_Tilde, glfw_base::Key::vGrave_Accent_and_Tilde },
			{ win_cpp::WindowsScancode::vComma_and_LessThen, glfw_base::Key::vComma_and_LessThen },
			{ win_cpp::WindowsScancode::vPeriod_and_GreaterThen, glfw_base::Key::vPeriod_and_GreaterThen },
			{ win_cpp::WindowsScancode::vForwardSlash_and_QuestionMark, glfw_base::Key::vForwardSlash_and_QuestionMark },
			{ win_cpp::WindowsScancode::vCapsLock, glfw_base::Key::vCapsLock },
			{ win_cpp::WindowsScancode::vF1, glfw_base::Key::vF1 },
			{ win_cpp::WindowsScancode::vF2, glfw_base::Key::vF2 },
			{ win_cpp::WindowsScancode::vF3, glfw_base::Key::vF3 },
			{ win_cpp::WindowsScancode::vF4, glfw_base::Key::vF4 },
			{ win_cpp::WindowsScancode::vF5, glfw_base::Key::vF5 },
			{ win_cpp::WindowsScancode::vF6, glfw_base::Key::vF6 },
			{ win_cpp::WindowsScancode::vF7, glfw_base::Key::vF7 },
			{ win_cpp::WindowsScancode::vF8, glfw_base::Key::vF8 },
			{ win_cpp::WindowsScancode::vF9, glfw_base::Key::vF9 },
			{ win_cpp::WindowsScancode::vF10, glfw_base::Key::vF10 },
			{ win_cpp::WindowsScancode::vF11, glfw_base::Key::vF11 },
			{ win_cpp::WindowsScancode::vF12, glfw_base::Key::vF12 },
			{ win_cpp::WindowsScancode::vPrintScreen, glfw_base::Key::vPrintScreen },
			{ win_cpp::WindowsScancode::vScrollLock, glfw_base::Key::vScrollLock },
			{ win_cpp::WindowsScancode::vPause, glfw_base::Key::vPause },
			{ win_cpp::WindowsScancode::vInsert, glfw_base::Key::vInsert },
			{ win_cpp::WindowsScancode::vHome, glfw_base::Key::vHome },
			{ win_cpp::WindowsScancode::vPageUp, glfw_base::Key::vPageUp },
			{ win_cpp::WindowsScancode::vDeleteForward, glfw_base::Key::vDeleteForward },
			{ win_cpp::WindowsScancode::vEnd, glfw_base::Key::vEnd },
			{ win_cpp::WindowsScancode::vPageDown, glfw_base::Key::vPageDown },
			{ win_cpp::WindowsScancode::vRightArrow, glfw_base::Key::vRightArrow },
			{ win_cpp::WindowsScancode::vLeftArrow, glfw_base::Key::vLeftArrow },
			{ win_cpp::WindowsScancode::vDownArrow, glfw_base::Key::vDownArrow },
			{ win_cpp::WindowsScancode::vUpArrow, glfw_base::Key::vUpArrow },
			{ win_cpp::WindowsScancode::vNumLock_and_Clear, glfw_base::Key::vNumLock_and_Clear },
			{ win_cpp::WindowsScancode::vForwardSlash, glfw_base::Key::vForwardSlash },
			{ win_cpp::WindowsScancode::vStar, glfw_base::Key::vStar },
			{ win_cpp::WindowsScancode::vDash, glfw_base::Key::vDash },
			{ win_cpp::WindowsScancode::vPlus, glfw_base::Key::vPlus },
			{ win_cpp::WindowsScancode::vEnter, glfw_base::Key::vEnter },
			{ win_cpp::WindowsScancode::v1_and_End, glfw_base::Key::v1_and_End },
			{ win_cpp::WindowsScancode::v2_and_Down_Arrow, glfw_base::Key::v2_and_Down_Arrow },
			{ win_cpp::WindowsScancode::v3_and_PageDn, glfw_base::Key::v3_and_PageDn },
			{ win_cpp::WindowsScancode::v4_and_Left_Arrow, glfw_base::Key::v4_and_Left_Arrow },
			{ win_cpp::WindowsScancode::v5_, glfw_base::Key::v5_ },
			{ win_cpp::WindowsScancode::v6_and_Right_Arrow, glfw_base::Key::v6_and_Right_Arrow },
			{ win_cpp::WindowsScancode::v7_and_Home, glfw_base::Key::v7_and_Home },
			{ win_cpp::WindowsScancode::v8_and_Up_Arrow, glfw_base::Key::v8_and_Up_Arrow },
			{ win_cpp::WindowsScancode::v9_and_PageUp, glfw_base::Key::v9_and_PageUp },
			{ win_cpp::WindowsScancode::v0_and_Insert, glfw_base::Key::v0_and_Insert },
			{ win_cpp::WindowsScancode::vPeriod_and_Delete, glfw_base::Key::vPeriod_and_Delete },
			{ win_cpp::WindowsScancode::vNonUS_Backslash_and_Pipe, glfw_base::Key::vNonUS_Backslash_and_Pipe },
			{ win_cpp::WindowsScancode::vApplication, glfw_base::Key::vApplication },
			{ win_cpp::WindowsScancode::vPower, glfw_base::Key::vPower },
			{ win_cpp::WindowsScancode::vEquals, glfw_base::Key::vEquals },
			{ win_cpp::WindowsScancode::vF13, glfw_base::Key::vF13 },
			{ win_cpp::WindowsScancode::vF14, glfw_base::Key::vF14 },
			{ win_cpp::WindowsScancode::vF15, glfw_base::Key::vF15 },
			{ win_cpp::WindowsScancode::vF16, glfw_base::Key::vF16 },
			{ win_cpp::WindowsScancode::vF17, glfw_base::Key::vF17 },
			{ win_cpp::WindowsScancode::vF18, glfw_base::Key::vF18 },
			{ win_cpp::WindowsScancode::vF19, glfw_base::Key::vF19 },
			{ win_cpp::WindowsScancode::vF20, glfw_base::Key::vF20 },
			{ win_cpp::WindowsScancode::vF21, glfw_base::Key::vF21 },
			{ win_cpp::WindowsScancode::vF22, glfw_base::Key::vF22 },
			{ win_cpp::WindowsScancode::vF23, glfw_base::Key::vF23 },
			{ win_cpp::WindowsScancode::vF24, glfw_base::Key::vF24 },
			{ win_cpp::WindowsScancode::vComma, glfw_base::Key::vComma },
			{ win_cpp::WindowsScancode::vInternational1, glfw_base::Key::vInternational1 },
			{ win_cpp::WindowsScancode::vInternational2, glfw_base::Key::vInternational2 },
			{ win_cpp::WindowsScancode::vInternational3, glfw_base::Key::vInternational3 },
			{ win_cpp::WindowsScancode::vInternational4, glfw_base::Key::vInternational4 },
			{ win_cpp::WindowsScancode::vInternational5, glfw_base::Key::vInternational5 },
			{ win_cpp::WindowsScancode::vInternational6, glfw_base::Key::vInternational6 },
			{ win_cpp::WindowsScancode::vLANG1, glfw_base::Key::vLANG1 },
			{ win_cpp::WindowsScancode::vLANG2, glfw_base::Key::vLANG2 },
			{ win_cpp::WindowsScancode::vLANG3, glfw_base::Key::vLANG3 },
			{ win_cpp::WindowsScancode::vLANG4, glfw_base::Key::vLANG4 },
			{ win_cpp::WindowsScancode::vLANG5, glfw_base::Key::vLANG5 },
			{ win_cpp::WindowsScancode::vLeftControl, glfw_base::Key::vLeftControl },
			{ win_cpp::WindowsScancode::vLeftShift, glfw_base::Key::vLeftShift },
			{ win_cpp::WindowsScancode::vLeftAlt, glfw_base::Key::vLeftAlt },
			{ win_cpp::WindowsScancode::vLeftGUI, glfw_base::Key::vLeftGUI },
			{ win_cpp::WindowsScancode::vRightControl, glfw_base::Key::vRightControl },
			{ win_cpp::WindowsScancode::vRightShift, glfw_base::Key::vRightShift },
			{ win_cpp::WindowsScancode::vRightAlt, glfw_base::Key::vRightAlt },
			{ win_cpp::WindowsScancode::vRightGUI, glfw_base::Key::vRightGUI },
			{ win_cpp::WindowsScancode::vScanNextTrack, glfw_base::Key::vScanNextTrack },
			{ win_cpp::WindowsScancode::vScanPreviosTrack, glfw_base::Key::vScanPreviosTrack },
			{ win_cpp::WindowsScancode::vStop, glfw_base::Key::vStop },
			{ win_cpp::WindowsScancode::vPlay_Pause, glfw_base::Key::vPlay_Pause },
			{ win_cpp::WindowsScancode::vMute, glfw_base::Key::vMute },
			{ win_cpp::WindowsScancode::vVolumeIncrement, glfw_base::Key::vVolumeIncrement },
			{ win_cpp::WindowsScancode::vVolumeDecrement, glfw_base::Key::vVolumeDecrement },
			{ win_cpp::WindowsScancode::vAL_Consumer_Control_Configuration, glfw_base::Key::vAL_Consumer_Control_Configuration },
			{ win_cpp::WindowsScancode::vAL_EmailReader, glfw_base::Key::vAL_EmailReader },
			{ win_cpp::WindowsScancode::vAL_Calculator, glfw_base::Key::vAL_Calculator },
			{ win_cpp::WindowsScancode::vAL_LocalMachineBrowser, glfw_base::Key::vAL_LocalMachineBrowser },
			{ win_cpp::WindowsScancode::vAC_Search, glfw_base::Key::vAC_Search },
			{ win_cpp::WindowsScancode::vAC_Home, glfw_base::Key::vAC_Home },
			{ win_cpp::WindowsScancode::vAC_Back, glfw_base::Key::vAC_Back },
			{ win_cpp::WindowsScancode::vAC_Forward, glfw_base::Key::vAC_Forward },
			{ win_cpp::WindowsScancode::vAC_Stop, glfw_base::Key::vAC_Stop },
			{ win_cpp::WindowsScancode::vAC_Refresh, glfw_base::Key::vAC_Refresh },
			{ win_cpp::WindowsScancode::vAC_Bookmarks, glfw_base::Key::vAC_Bookmarks }
};

glfw_base::Key to_glfw_key(win_cpp::WindowsScancode key) {
	auto end = windows_keyboard_keys_to_glfw_keys.end();
	auto res = windows_keyboard_keys_to_glfw_keys.find(key);
	return (res != end) ? res->second : glfw_base::Key::NULL;
}

glfw_base::CharModsFlags getKeyMods() {
	glfw_base::CharModsFlags mods;

	// if (win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_SHIFT) & 0x8000u) {
	if (std::to_underlying(win_cpp::GetAsyncKeyState(win_cpp::VirtualKeysStandardSet::VK_SHIFT))) {
		mods |= glfw_base::CharModsFlags::values::shift;
	}
	// if (win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_CONTROL) & 0x8000u) {
	if (std::to_underlying(win_cpp::GetAsyncKeyState(win_cpp::VirtualKeysStandardSet::VK_CONTROL))) {
		mods |= glfw_base::CharModsFlags::values::control;
	}
	// if (win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_MENU) & 0x8000u) {
	if (std::to_underlying(win_cpp::GetAsyncKeyState(win_cpp::VirtualKeysStandardSet::VK_MENU))) {
		mods |= glfw_base::CharModsFlags::values::alt;
	}
	// if ((win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_LWIN) | win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_RWIN)) & 0x8000u) {
	if (std::to_underlying(win_cpp::GetAsyncKeyState(win_cpp::VirtualKeysStandardSet::VK_LWIN))
		| std::to_underlying(win_cpp::GetAsyncKeyState(win_cpp::VirtualKeysStandardSet::VK_RWIN))) {
		mods |= glfw_base::CharModsFlags::values::super;
	}

	if (win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_CAPITAL) & 1u) { /* TODO */
		mods |= glfw_base::CharModsFlags::values::caps_lock;
	}

	if (win_cpp::GetKeyState(win_cpp::VirtualKeysStandardSet::VK_NUMLOCK) & 1u) { /* TODO */
		mods |= glfw_base::CharModsFlags::values::num_lock;
	}

	return mods;
}

glfw_base::CharModsCallbackF charmod_default_callback = [](unsigned, glfw_base::CharModsFlags charmod) {};
glfw_base::CharacterCallbackF character_default_callback = [](unsigned) {};
glfw_base::KeyCallbackF key_default_callback = [](glfw_base::Key key, unsigned scancode, glfw_base::KeyState action, glfw_base::CharModsFlags mods) {};

struct Input {
	private:
		glfw_base::KeyStateMap key_state = glfw_base::inital_key_state;
		bool sticky_keys = false;
		bool lockKeyMods = false;
		glfw_base::CharModsCallbackF _charmod = charmod_default_callback;
		glfw_base::CharacterCallbackF _character = character_default_callback;
		glfw_base::KeyCallbackF key_callback = key_default_callback;

	private:
		constexpr glfw_base::CharModsFlags apply_KeyMods(glfw_base::CharModsFlags mods) const noexcept {
			if (!lockKeyMods) {
				constexpr glfw_base::CharModsFlags caps_lock_int_represent = glfw_base::CharModsFlags::values::caps_lock;
				constexpr glfw_base::CharModsFlags num_lock_int_represent = glfw_base::CharModsFlags::values::num_lock;
				constexpr glfw_base::CharModsFlags res = ~(caps_lock_int_represent | num_lock_int_represent);
				mods &= res;
			}
			return mods;
		}

	public:
		constexpr void set_LockKeyMods(bool x) noexcept { lockKeyMods = x; }
		constexpr bool get_LockKeyMods() const noexcept { return lockKeyMods; }

		void process_Char(unsigned codepoint, glfw_base::CharModsFlags mods, bool plain) const {
			// if (codepoint < 32 || (codepoint > 126 && codepoint < 160)) {
				// return;
			// }
			mods = apply_KeyMods(mods);
			std::invoke(_charmod, codepoint, mods);

			if (plain) {
				std::invoke(_character, codepoint);
			}
		}

		void process_Key(glfw_base::Key key, unsigned scancode, glfw_base::KeyState action, glfw_base::CharModsFlags mods) {
			if (true) {
				bool repeated = 0;

				if (action == glfw_base::KeyState::release && key_state[key] == glfw_base::KeyState::release) {
					return;
				}

				if (action == glfw_base::KeyState::press && key_state[key] == glfw_base::KeyState::press) {
					repeated = true;
				}

				if (action == glfw_base::KeyState::release && sticky_keys) {
					key_state[key] = glfw_base::KeyState::stick;
				}	else {
					key_state[key] = action;
				}

				if (repeated) {
					action = glfw_base::KeyState::repeat;
				}
			}

			mods = apply_KeyMods(mods);

			if (key_callback) {
				std::invoke(key_callback, key, scancode, action, mods);
			}
		}

		void set_key_mods_callback(glfw_base::CharModsCallbackF&& cmc) {
			_charmod = std::forward<decltype(cmc)>(cmc);
		};
		void set_character_callback(glfw_base::CharacterCallbackF&& cc) {
			_character = std::forward<decltype(cc)>(cc);
		};
		void set_key_callback(glfw_base::KeyCallbackF&& kc) {
			key_callback = std::forward<decltype(kc)>(kc);
		};

		Input() noexcept : _charmod(charmod_default_callback), _character(character_default_callback) {}
		Input(
			glfw_base::CharModsCallbackF&& charmod_f,
			glfw_base::CharacterCallbackF&& character_f,
			glfw_base::KeyCallbackF&& key_f
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

glfw_base::CursorStateCallbackT dummy_state_callback = [](const glfw_base::CursorState&) noexcept {};
glfw_base::CursorPositionCallbackT dummy_pos_callback = [](const std::pair<int, int>& pos) noexcept {};
struct Cursor {
	private:
		glfw_base::CursorState state_ = glfw_base::CursorState::normal;
		glfw_base::CursorRawInputState raw_input_state = glfw_base::CursorRawInputState::disabled;
		glfw_base::CursorStateCallbackT cursor_state_callback_f = dummy_state_callback;
		glfw_base::CursorPositionCallbackT cursor_position_callback_f = dummy_pos_callback;
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
		glfw_base::CursorRawInputState get_RawInputState() { return raw_input_state; }
		glfw_base::CursorState get_state() const noexcept { return state_; }

		void set_cursor_position_callback(glfw_base::CursorPositionCallbackT&& cpct) {
			cursor_position_callback_f = std::forward<decltype(cpct)>(cpct);
		}

		void set_cursor_state_callback(glfw_base::CursorStateCallbackT&& csct) {
			cursor_state_callback_f = std::forward<decltype(csct)>(csct);
		}

#if 1
		void set_state(const glfw_base::CursorState& state) {
			if (cursor_state_callback_f) {
				std::invoke(cursor_state_callback_f, state);
			}
			state_ = state;
		};
#endif

#if 0
 		glfw_base::CursorState get_state() const noexcept {
 			return state_;
		}
#endif

		void release(const win_cpp::Window& window) {
			win_cpp::UnClipCursor();
			state_ = glfw_base::CursorState::normal;
		}

		void enable(const win_cpp::Window& window) {
			if(raw_input_state == glfw_base::CursorRawInputState::enabled) {
				mri.reset();
				raw_input_state = glfw_base::CursorRawInputState::disabled;
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
			if (raw_input_state == glfw_base::CursorRawInputState::enabled) {
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
	const glfw_base::AspectRatio& aspect_raito
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
	} else if (edge == win_cpp::Edges::WMSZ_TOPLEFT || edge == win_cpp::Edges::WMSZ_TOPRIGHT) {
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
glfw_base::WindowRectCallbackF dummy_window_rect_callback = [](const glfw_base::Rect&) constexpr noexcept {};
glfw_base::WindowCloseCallbackF dummy_window_close_callback = []() constexpr noexcept {};

#if 1

struct Config  {
	glfw_base::AspectRatio ar;
	bool ar_used;
	glfw_base::FrameAction fa;
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

	glfw_base::WindowRectCallbackF window_rect_callback = dummy_window_rect_callback;
	void set_window_rect_callback(glfw_base::WindowRectCallbackF&& wrcb) {
		window_rect_callback = std::forward<decltype(wrcb)>(wrcb);
	}

	glfw_base::WindowCloseCallbackF window_close_callback = dummy_window_close_callback;
	void set_window_close_callback(glfw_base::WindowCloseCallbackF&& wcc) {
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
	cfg.window_rect_callback(glfw_base::Rect(rect.get_left(), rect.get_top(), rect.get_right(), rect.get_bottom()));
	return true;
};

auto cWM_MOUSEACTIVATE = [](Config& cfg, const win_cpp::Window& window, win_cpp::WindowMessage wmsg, win_cpp::HitTest ht) -> win_cpp::window_proc_callback_result_type  {
	if (wmsg == win_cpp::WindowMessage::WM_LBUTTONDOWN) {
		if (ht != win_cpp::HitTest::HTCLIENT) {
			cfg.fa.set_state(glfw_base::FrameActionState::enabled);
		}
	}
	return std::nullopt;
};

auto cWM_CAPTURECHANGED = [](Config& cfg, const win_cpp::Window& window, bool has_parent_window) -> win_cpp::window_proc_callback_result_type {
	if (!has_parent_window && std::to_underlying(cfg.fa.get_state())) {
		if (cfg.cursor.get_state() == glfw_base::CursorState::disabled) {
			cfg.cursor.disable(window);
		}	else if (cfg.cursor.get_state() == glfw_base::CursorState::captured) {
			cfg.cursor.capture(window);
		}
		cfg.fa.set_state(glfw_base::FrameActionState::disabled);
	}
	return std::nullopt;
};

auto cWM_SETFOCUS = [](Config& cfg, const win_cpp::Window& window) -> win_cpp::window_proc_callback_result_type {
	cfg.focus.isFocused = true;
	if (cfg.fa.get_state() == glfw_base::FrameActionState::enabled) {
		if (cfg.cursor.get_state() == glfw_base::CursorState::disabled) {
			cfg.cursor.disable(window);
		} else if (cfg.cursor.get_state() == glfw_base::CursorState::captured) {
			cfg.cursor.capture(window);
		}
	}
	return std::nullopt;
	// return 0;
};

auto cWM_KILLFOCUS = [](Config& cfg, const win_cpp::Window& window) -> win_cpp::window_proc_callback_result_type {
	if (cfg.fa.get_state() == glfw_base::FrameActionState::enabled) {
		if (cfg.cursor.get_state() == glfw_base::CursorState::disabled) {
			cfg.cursor.disable(window);
		}	else if (cfg.cursor.get_state() == glfw_base::CursorState::captured) {
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
	glfw_base::KeyState action = glfw_base::KeyState::press;
	glfw_base::CharModsFlags mods = getKeyMods();
	glfw_base::Key key = to_glfw_key(data.scanCode);
	cfg.input.process_Key(key, std::to_underlying(data.scanCode), action, mods);
	return 0;
};

auto cWM_SYSKEYDOWN = [](Config& cfg, const win_cpp::Window& window, win_cpp::VirtualKeysStandardSet vk, const win_cpp::WindowsKeyData& data) -> win_cpp::window_proc_callback_result_type {
	glfw_base::KeyState action = glfw_base::KeyState::press;
	glfw_base::CharModsFlags mods = getKeyMods();
	glfw_base::Key key = to_glfw_key(data.scanCode);
	cfg.input.process_Key(key, std::to_underlying(data.scanCode), action, mods);
	return 0;
};

auto cWM_KEYUP = [](Config& cfg, const win_cpp::Window& window, win_cpp::VirtualKeysStandardSet vk, const win_cpp::WindowsKeyData& data) -> win_cpp::window_proc_callback_result_type {
	glfw_base::KeyState action = glfw_base::KeyState::release;
	glfw_base::CharModsFlags mods = getKeyMods();
	glfw_base::Key key = to_glfw_key(data.scanCode);
	cfg.input.process_Key(key, std::to_underlying(data.scanCode), action, mods);
	return 0;
};

auto cWM_SYSKEYUP = [](Config& cfg, const win_cpp::Window& window, win_cpp::VirtualKeysStandardSet vk, const win_cpp::WindowsKeyData& data) -> win_cpp::window_proc_callback_result_type {
	glfw_base::KeyState action = glfw_base::KeyState::release;
	glfw_base::CharModsFlags mods = getKeyMods();
	glfw_base::Key key = to_glfw_key(data.scanCode);
	cfg.input.process_Key(key, std::to_underlying(data.scanCode), action, mods);
	return 0;
};

auto cWM_MOUSEMOVE = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type  {
	auto&& [x, y] = m_pos;

	if (!cfg.wmouse.isTracking()) {
		cfg.wmouse.StartTracking(window, win_cpp::TrackMouseEventFlags::values::TME_LEAVE);
		cfg.cursor.enter();
	}

	if (cfg.cursor.get_state() == glfw_base::CursorState::disabled) {
		auto [lx, ly] = cfg.cursor.get_position();
		auto dx = x - lx;
		auto dy = y - ly;
		if (cfg.cursor.get_RawInputState() == glfw_base::CursorRawInputState::enabled) {
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
	auto action = glfw_base::KeyState::press;
	auto key = glfw_base::Key::vLMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_MBUTTONDOWN = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type {
	auto action = glfw_base::KeyState::press;
	auto key = glfw_base::Key::vMMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_RBUTTONDOWN = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type {
	auto action = glfw_base::KeyState::press;
	auto key = glfw_base::Key::vRMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_XBUTTONDOWN = [](Config& cfg, const win_cpp::Window& window, unsigned n_button, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_keys_down) -> win_cpp::window_proc_callback_result_type {
		return 0;
};

auto cWM_LBUTTONUP = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type {
	auto action = glfw_base::KeyState::release;
	auto key = glfw_base::Key::vLMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_MBUTTONUP = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type {
	auto action = glfw_base::KeyState::release;
	auto key = glfw_base::Key::vMMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_RBUTTONUP = [](Config& cfg, const win_cpp::Window& window, const std::pair<short, short>& m_pos, win_cpp::MouseKeysFlags m_botton_down) -> win_cpp::window_proc_callback_result_type {
	auto action = glfw_base::KeyState::release;
	auto key = glfw_base::Key::vRMB;
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
		if (cfg.fa.get_state() == glfw_base::FrameActionState::enabled) {
		return 0;
	}
	if (cfg.cursor.get_state() == glfw_base::CursorState::disabled) {
		cfg.cursor.enable(window);
	}	else if (cfg.cursor.get_state() == glfw_base::CursorState::captured) {
		cfg.cursor.capture(window);
	}
	return 0;
};

auto cWM_ENTERMENULOOP = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
	if (cfg.fa.get_state() == glfw_base::FrameActionState::enabled) {
		return 0;
	}
	if (cfg.cursor.get_state() == glfw_base::CursorState::disabled) {
		cfg.cursor.enable(window);
	}	else if (cfg.cursor.get_state() == glfw_base::CursorState::captured) {
		cfg.cursor.capture(window);
	}
	return 0;
};

auto cWM_EXITSIZEMOVE = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long  {
	if (cfg.fa.get_state() == glfw_base::FrameActionState::enabled) {
		return 0;
	}
	if (cfg.cursor.get_state() == glfw_base::CursorState::disabled) {
		cfg.cursor.disable(window);
	}	else if (cfg.cursor.get_state() == glfw_base::CursorState::captured) {
		cfg.cursor.release(window);
	}
	return 0;
};

auto cWM_EXITMENULOOP = [](const win_cpp::Window& window, Config& cfg win_cpp::PolymorphismByWindows&& windowData) -> long long {
		if (cfg.fa.get_state() == glfw_base::FrameActionState::enabled) {
		return 0;
	}
	if (cfg.cursor.get_state() == glfw_base::CursorState::disabled) {
		cfg.cursor.disable(window);
	}	else if (cfg.cursor.get_state() == glfw_base::CursorState::captured) {
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
	// window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_CHAR>([cfg = rc, wnd = rw, cWM_CHARc = cWM_CHAR](wchar_t character, const win_cpp::WindowsKeyData& data) { return std::invoke(cWM_CHARc, cfg.get(), wnd.get(), character, data); });
	// window.SetWindowMessageCallback<win_cpp::WindowMessage::WM_SYSCHAR>([cfg = rc, wnd = rw, cWM_SYSCHARc = cWM_SYSCHAR](wchar_t character, const win_cpp::WindowsKeyData& data) { return std::invoke(cWM_SYSCHARc, cfg.get(), wnd.get(), character, data); });
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

win_cpp::WindowStyle get_WindowStyle(const glfw_base::WindowCreateInfo& glfw_window_info) {
	/* TODO */
	return win_cpp::WindowStyle::values::WS_OVERLAPPEDWINDOW;
}

win_cpp::ExtendedWindowStyle get_WindowStyleEX(const glfw_base::WindowCreateInfo& glfw_window_info) {
	/* TODO */
	return win_cpp::ExtendedWindowStyle::values::WS_EX_TOPMOST;
}

win_cpp::Rect to_win_rect(const glfw_base::Rect& glfw_rect) {
	return win_cpp::Rect{ glfw_rect.get_left(), glfw_rect.get_top(), glfw_rect.get_right(), glfw_rect.get_bottom() };
}

win_cpp::Title to_win_title(const glfw_base::Title& title) {
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

namespace glfw_win32 {
	win_cpp::Instance instance;
	win_cpp::MainClass main_class{ get_mainclass_info(instance) };

	export struct Window
		: glfw_base::wVisible
		, glfw_base::wResizable
		, glfw_base::wDecorated
		, glfw_base::wFocused
		, glfw_base::wAutoiconify
		, glfw_base::wFloating
		, glfw_base::wMaximized
		, glfw_base::wCenterCursor
		, glfw_base::wTransparent
		, glfw_base::wFocusOnShow
		, glfw_base::wScaleToMonitor
	{
		private:
			Config config;
			win_cpp::Window window;

		public:
			Window(const glfw_base::WindowCreateInfo& info)
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
			glfw_base::Title get_Title() const {
				return glfw_base::Title(window.get_Title().get_c()); 
			}
			void set_Title(const glfw_base::Title& title) { 
				window.set_Title(win_cpp::Title{ title.get_sv() });
			}

			// glfw_base::Icon get_Icon() const { get_Icon(); } 
			void set_Icon(const glfw_base::Icon& icon) { }

			glfw_base::Rect get_Position() const {
				auto win_rect = window.GetClientRect();
				return glfw_base::Rect(win_rect.get_left(), win_rect.get_top(), win_rect.get_right(), win_rect.get_bottom());
			}
			void set_Position(const glfw_base::Rect& rect) { 
				win_cpp::Rect wrect(rect.get_left(), rect.get_top(), rect.get_right(), rect.get_bottom());
				win_cpp::WindowZOrder order = win_cpp::WindowZOrder::HWND_TOPMOST;
				win_cpp::SetWindowPosFlags swp = win_cpp::SetWindowPosFlags::values::SWP_NOZORDER;
				window.SetWindowPosition(order, wrect, swp);
			}

			glfw_base::SizeLimits get_SizeLimits() const { return glfw_base::SizeLimits(0, 0); }
			void set_SizeLimits(const glfw_base::SizeLimits& s_limits) {} // set_SizeLimits(s_limits); }
#if 0 /* TODO*/
			glfw_base::AspectRatio get_AspectRatio() const { return get_AspectRatio(); }
			void set_AspectRation(const glfw_base::AspectRatio& aspect_ratio) { set_AspectRatio(aspect_ratio); }
#endif		
			// glfw_base::Opacity_type get_Opacity() const { get_Opacity(); }
			// void set_Opacity(const glfw_base::Opacity_type& opacity) { set_Opacity(); }

			void maximize() { window.maximize(); }
			void show() { window.show(); }
			void hide() { window.hide(); }
			void focus() { window.focus(); }
			void close() { win_cpp::WindowClose(window); }

		public:
			void set_key_mods_callback(glfw_base::CharModsCallbackF&& cmc) {
				config.input.set_key_mods_callback(std::forward<decltype(cmc)>(cmc));
			}
			void set_character_callback(glfw_base::CharacterCallbackF&& cc) {
				config.input.set_character_callback(std::forward<decltype(cc)>(cc));
			}
			void set_key_callback(glfw_base::KeyCallbackF&& kc) {
				config.input.set_key_callback(std::forward<decltype(kc)>(kc));
			}
			void set_cursor_position_callback(glfw_base::CursorPositionCallbackT&& cpct) {
				config.cursor.set_cursor_position_callback(std::forward<decltype(cpct)>(cpct));
			}
			void set_cursor_state_callback(glfw_base::CursorStateCallbackT&& csct) {
				config.cursor.set_cursor_state_callback(std::forward<decltype(csct)>(csct));
			}
			void set_window_rect_callback(glfw_base::WindowRectCallbackF&& wrb) {
				config.set_window_rect_callback(std::forward<decltype(wrb)>(wrb));
			}
			void set_window_close_callback(glfw_base::WindowCloseCallbackF&& wcc) {
				config.set_window_close_callback(std::forward<decltype(wcc)>(wcc));
			}

			vk::raii::SurfaceKHR get_vulkan_surface(const vk::raii::Instance& vk_instance) const {
				auto win32_window_handle = win_cpp::Window::type(window);
				auto win32_instance_handle = win_cpp::Instance::type(instance);
				vk::Win32SurfaceCreateInfoKHR Win32SurfaceCreateInfo = {};
				Win32SurfaceCreateInfo.setHinstance(win32_instance_handle);
				Win32SurfaceCreateInfo.setHwnd(win32_window_handle);
				return vk::raii::SurfaceKHR(vk_instance, Win32SurfaceCreateInfo);
			}
	}; // struct GLFW_Window_Win
	static_assert(glfw_base::WindowLikeWithDefaultConfig<Window>);
	
} // ns 
