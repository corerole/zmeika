module;

export module glfw_win32_window;
import std;
import madmap;
import win_cpp;
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

glfw::CharModsCallbackF charmod_default_callback = [](const std::pair<wchar_t, wchar_t>&, glfw::CharModsFlags charmod) {};
glfw::CharacterCallbackF character_default_callback = [](const std::pair<wchar_t, wchar_t>& sp) {};
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

			void process_Char(const auto& codepoint, glfw::CharModsFlags mods, bool plain) const {
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
			) noexcept : _charmod(charmod_f), _character(character_f), key_callback(key_f) {
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

struct Cursor {
	using RawInput_state = glfw::CursorRawInput;

	glfw::CursorStateCallbackT dummy_state_callback = [](const glfw::CursorState&) noexcept {};
	glfw::CursorPositionCallbackT dummy_pos_callback = [](const std::pair<int, int>& pos) noexcept {};

	private:
		glfw::CursorState state_ = glfw::CursorState::normal;
		RawInput_state ri_state = RawInput_state::disabled;
		glfw::CursorStateCallbackT cursor_state_callback_f = dummy_state_callback;
		glfw::CursorPositionCallbackT cursor_position_callback_f = dummy_pos_callback;
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
		RawInput_state get_RawInputState() { return ri_state; }
		glfw::CursorState get_state() const noexcept { return state_; }

		void set_cursor_position_callback(glfw::CursorPositionCallbackT&& cpct) {
			cursor_position_callback_f = std::forward<decltype(cpct)>(cpct);
		}

		void set_cursor_state_callback(glfw::CursorStateCallbackT&& csct) {
			cursor_state_callback_f = std::forward<decltype(csct)>(csct);
		}

#if 0
		void set_state(const glfw::CursorState& state) noexcept {
			if (cursor_state_callback_f) {
				std::invoke(cursor_state_callback_f, state);
			}
			state_ = state;
		};
#endif

		void release(const win_cpp::Window& window) {
			win_cpp::UnClipCursor();
			state_ = glfw::CursorState::normal;
		}

		void enable(const win_cpp::Window& window) {
			// if (window->rawMouseMotion) {
				// disableRawMouseMotion(window);
			// }

			// _glfw.win32.disabledCursorWindow = NULL;
			release(window);
			// _glfwSetCursorPosWin32(window,
				// _glfw.win32.restoreCursorPosX,
				// _glfw.win32.restoreCursorPosY);
			// updateCursorImage(window);
		}

		void capture(const win_cpp::Window& window) {
			auto rect = window.GetClientRect();
			auto [lx, ty] = window.ClientToScreen(rect.get_left(), rect.get_top());
			auto [rx, by] = window.ClientToScreen(rect.get_right(), rect.get_bottom());
			rect = win_cpp::Rect(lx, ty, rx, by);
			win_cpp::ClipCursor(rect);
		}

		void disable(const win_cpp::Window& window) {
			// _glfw.win32.disabledCursorWindow = window;
			// _glfwGetCursorPosWin32(window,
				// &_glfw.win32.restoreCursorPosX,
				// &_glfw.win32.restoreCursorPosY);
			// updateCursorImage(window);
			// _glfwCenterCursorInContentArea(window);
			capture(window);

			// if (window->rawMouseMotion)
				// enableRawMouseMotion(window);
		}

		void enter() {}
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
glfw::WindowRectCallbackF dummy_window_rect_callback = [](const glfw::Rect&) {};
struct Config {
	glfw::AspectRatio ar;
	glfw::FrameAction fa;
	bool ready = false;
	Input input;
	Cursor cursor;
	win_cpp::Mouse wmouse;
	win_cpp::Window window;

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
};

template<typename UserData> using sysmenucmd_f = std::function<long long(const win_cpp::Window& window, UserData&, win_cpp::PolymorphismByWindows)>;
template<typename UserData> struct SysMenuCMDcallbacks : std::unordered_map<win_cpp::SystemMenuCommand, sysmenucmd_f<UserData>> {
	using Base = std::unordered_map<win_cpp::SystemMenuCommand, sysmenucmd_f<UserData>>;
	using Base::Base;
};
/* TODO remove window */
auto cSC_SIZE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1;
};

auto cSC_MOVE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1;
};

auto cSC_MINIMIZE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1;
};

auto cSC_MAXIMIZE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1;
};

auto cSC_NEXTWINDOW = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_PREVWINDOW = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1;
};

auto cSC_CLOSE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_VSCROLL = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_HSCROLL = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_MOUSEMENU = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_KEYMENU = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		if (!cfg.keymenu.state) {
		return 0;
	}
	return 1;
};

auto cSC_ARRANGE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_RESTORE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_TASKLIST = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_SCREENSAVE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		if (cfg.monitor.state) {
		return 0;
	}
	return 1;
};

auto cSC_HOTKEY = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_DEFAULT = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_MONITORPOWER = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		if (cfg.monitor.state) {
		return 0;
	}
	return 1; 
};

auto cSC_CONTEXTHELP = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 1; 
};

auto cSC_SEPARATOR = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
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

auto cWM_PAINT = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
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

auto cWM_CLOSE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		win::f::PostQuitMessage(0);
	return 0;
};

auto cWM_QUIT = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		return 0;
};

auto cWM_CREATE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		return 0;
};

auto cWM_SIZE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		return 0;
};

auto cWM_SIZING = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		auto edges = win_cpp::Edges(windowData.wParam);
	auto pre_rect = reinterpret_cast<win::t::RECT*>(windowData.lParam);
	auto rect = win_cpp::Rect(pre_rect->left, pre_rect->top, pre_rect->right, pre_rect->bottom);
	rect = applyAspectRatio(window, edges, rect, cfg.ar);
	*pre_rect = static_cast<win_cpp::Rect::type>(rect);
	cfg.window_rect_callback(glfw::Rect(pre_rect->left, pre_rect->top, pre_rect->right, pre_rect->bottom));
	return true;
};

auto cWM_MOUSEACTIVATE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		if (win::f::HIWORD(windowData.lParam)) {
		if (win::f::LOWORD(windowData.lParam)) {
			cfg.fa.set_state(glfw::FrameActionState::enabled);
		}
	}
	return win::f::DefWindowProcW(
		win_cpp::Window::type(window),
		std::to_underlying(win_cpp::WindowMessage::WM_MOUSEACTIVATE),
		windowData.wParam,
		windowData.lParam
	); // std::to_underlying(win_cpp::MouseActiveRetVal::MA_ACTIVATE);
};

auto cWM_CAPTURECHANGED = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		if (windowData.lParam == 0 && std::to_underlying(cfg.fa.get_state())) {
		if (cfg.cursor.get_state() == glfw::CursorState::disabled) {
			cfg.cursor.disable(window);
		}	else if (cfg.cursor.get_state() == glfw::CursorState::captured) {
			cfg.cursor.capture(window);
		}
		cfg.fa.set_state(glfw::FrameActionState::disabled);
	}
	return win::f::DefWindowProcW(
		win_cpp::Window::type(window),
		std::to_underlying(win_cpp::WindowMessage::WM_MOUSEACTIVATE),
		windowData.wParam,
		windowData.lParam
	);
};

auto cWM_SETFOCUS = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		cfg.focus.isFocused = true;
	if (cfg.fa.get_state() == glfw::FrameActionState::enabled) {
		if (cfg.cursor.get_state() == glfw::CursorState::disabled) {
			cfg.cursor.disable(window);
		} else if (cfg.cursor.get_state() == glfw::CursorState::captured) {
			cfg.cursor.capture(window);
		}
	}
	return win::f::DefWindowProcW(
		win_cpp::Window::type(window),
		std::to_underlying(win_cpp::WindowMessage::WM_MOUSEACTIVATE),
		windowData.wParam,
		windowData.lParam
	);
};

auto cWM_KILLFOCUS = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
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

auto cWM_SYSCOMMAND = [cbs = syscmd_callbacks](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
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

auto cWM_INPUTLANGCHANGE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		auto UpdateKeyNames = []() {};
	UpdateKeyNames();
	return win::f::DefWindowProcW(
		win_cpp::Window::type(window),
		std::to_underlying(win_cpp::WindowMessage::WM_INPUTLANGCHANGE),
		windowData.wParam,
		windowData.lParam
	);
};

auto cWM_CHAR = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
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
#if 0
	if (windowData.wParam >= SURROGATE_HIGH_START && windowData.wParam <= SURROGATE_HIGH_END) {
		high_surrogate = windowData.wParam;
	} else {
		unsigned codepoint = 0;

		if (windowData.wParam >= SURROGATE_LOW_START && windowData.wParam <= SURROGATE_LOW_END) {
			if(high_surrogate) {
				codepoint += (high_surrogate - SURROGATE_HIGH_START) << SURROGATE_SHIFT_BITS;
				codepoint += windowData.wParam - SURROGATE_LOW_START;
				codepoint += SURROGATE_OFFSET;
			}
		}	else {
			codepoint = windowData.wParam;
		}

		high_surrogate = 0;
		cfg.input.process_Char(codepoint, getKeyMods(), true);
	}
#else
	if (windowData.wParam >= SURROGATE_HIGH_START && windowData.wParam <= SURROGATE_HIGH_END) {
		high_surrogate = windowData.wParam;
	} else {
		std::pair<wchar_t, wchar_t> charPair;

		if (windowData.wParam >= SURROGATE_LOW_START && windowData.wParam <= SURROGATE_LOW_END) {
			if (high_surrogate != 0) {
				charPair = { high_surrogate, windowData.wParam };
			} else {
				charPair = { windowData.wParam, 0 };
			}
		} else {
			charPair = { windowData.wParam, 0 };
		}
		high_surrogate = 0;
		cfg.input.process_Char(charPair, getKeyMods(), true);
	}
#endif

	return 0;
};

auto cWM_SYSCHAR = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
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
#if 0
	if (windowData.wParam >= SURROGATE_HIGH_START && windowData.wParam <= SURROGATE_HIGH_END) {
		// cfg.hs.set(windowData.wParam);
		high_surrogate = windowData.wParam;
	} else {
		unsigned codepoint = 0;

		if (windowData.wParam >= SURROGATE_LOW_START && windowData.wParam <= SURROGATE_LOW_END) {
			// if (cfg.hs.get()) {
			if(high_surrogate) {
				// codepoint += (cfg.hs.get() - SURROGATE_HIGH_START) << SURROGATE_SHIFT_BITS;
				codepoint += (high_surrogate - SURROGATE_HIGH_START) << SURROGATE_SHIFT_BITS;
				codepoint += windowData.wParam - SURROGATE_LOW_START;
				codepoint += SURROGATE_OFFSET;
			}
		}	else {
			codepoint = windowData.wParam;
		}

		high_surrogate = 0;
		cfg.input.process_Char(codepoint, getKeyMods(), false);
	}
#else
	if (windowData.wParam >= SURROGATE_HIGH_START && windowData.wParam <= SURROGATE_HIGH_END) {
		high_surrogate = windowData.wParam;
	} else {
		std::pair<wchar_t, wchar_t> charPair;

		if (windowData.wParam >= SURROGATE_LOW_START && windowData.wParam <= SURROGATE_LOW_END) {
			if (high_surrogate != 0) {
				charPair = { high_surrogate, windowData.wParam };
			} else {
				charPair = { windowData.wParam, 0 };
			}
		} else {
			charPair = { windowData.wParam, 0 };
		}
		high_surrogate = 0;
		cfg.input.process_Char(charPair, getKeyMods(), false);
	}
#endif

	if(cfg.keymenu.state) {
		return win::f::DefWindowProcW(
			win_cpp::Window::type(window),
			std::to_underlying(win_cpp::WindowMessage::WM_SYSCHAR),
			windowData.wParam,
			windowData.lParam
		);
	}

	return 0;
};

auto cWM_UNICHAR = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		if (windowData.wParam == 0xFFFF) { // UNICODE_NOCHAR
		return true;
	}
	std::pair<wchar_t, wchar_t> symbol(windowData.wParam, 0);
	cfg.input.process_Char(symbol, getKeyMods(), true);
	return 0;
};

auto cWM_KEYDOWN = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		auto scancode = static_cast<win_cpp::WindowsScancode>((windowData.lParam >> 16) & 0xFF);
	bool extended = (windowData.lParam >> 24) & 1;
	glfw::KeyState action = glfw::KeyState::press;
	glfw::CharModsFlags mods = getKeyMods();
	glfw::Key key = to_glfw_key(scancode);
	cfg.input.process_Key(key, std::to_underlying(scancode), action, mods);
	return 0;
};

auto cWM_SYSKEYDOWN = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		auto scancode = static_cast<win_cpp::WindowsScancode>((windowData.lParam >> 16) & 0xFF);
	bool extended = (windowData.lParam >> 24) & 1;
	glfw::KeyState action = glfw::KeyState::press;
	glfw::CharModsFlags mods = getKeyMods();
	glfw::Key key = to_glfw_key(scancode);
	cfg.input.process_Key(key, std::to_underlying(scancode), action, mods);
	return 0;
};

auto cWM_KEYUP = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
	auto scancode = static_cast<win_cpp::WindowsScancode>((windowData.lParam >> 16) & 0xFF);
	bool extended = (windowData.lParam >> 24) & 1;
	glfw::KeyState action = glfw::KeyState::release;
	glfw::CharModsFlags mods = getKeyMods();
	glfw::Key key = to_glfw_key(scancode);
	cfg.input.process_Key(key, std::to_underlying(scancode), action, mods);
	return 0;
};

auto cWM_SYSKEYUP = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
	auto scancode = static_cast<win_cpp::WindowsScancode>((windowData.lParam >> 16) & 0xFF);
	bool extended = (windowData.lParam >> 24) & 1;
	glfw::KeyState action = glfw::KeyState::release;
	glfw::CharModsFlags mods = getKeyMods();
	glfw::Key key = to_glfw_key(scancode);
	cfg.input.process_Key(key, std::to_underlying(scancode), action, mods);
	return 0;
};

auto cWM_MOUSEMOVE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
	// 	auto [x, y] = win_cpp::GetMousePosition(windowData.lParam);
#if 0
	if (!cfg.wmouse.isTracking()) {
		cfg.wmouse.StartTracking(window, win_cpp::TrackMouseEventFlags::values::TME_LEAVE);
		cfg.cursor.enter();
	}

	if (cfg.cursor.get_state() == glfw::CursorState::disabled) {
		auto [lx, ly] = cfg.cursor.get_position();
		auto dx = x - lx;
		auto dy = y - ly;
		if (cfg.cursor.get_RawInputState() == glfw::CursorRawInput::enabled) {
			return 0; // ?
		}
		// set virtual pos
	}
	cfg.cursor.set_position(x, y);
#endif
	return 0;
};

auto cWM_INPUT = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 0;
};

auto cWM_LBUTTONDOWN = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		
	auto action = glfw::KeyState::press;
	auto key = glfw::Key::vLMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_MBUTTONDOWN = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		auto action = glfw::KeyState::press;
	auto key = glfw::Key::vMMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_RBUTTONDOWN = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		auto action = glfw::KeyState::press;
	auto key = glfw::Key::vRMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_XBUTTONDOWN = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 0;
};

auto cWM_LBUTTONUP = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		auto action = glfw::KeyState::release;
	auto key = glfw::Key::vLMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_MBUTTONUP = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		auto action = glfw::KeyState::release;
	auto key = glfw::Key::vMMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_RBUTTONUP = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		auto action = glfw::KeyState::release;
	auto key = glfw::Key::vRMB;
	constexpr unsigned scancode = 0u;
	cfg.input.process_Key(key, scancode, action, getKeyMods());
	return 0;
};

auto cWM_XBUTTONUP = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		return 0;
};

auto cWM_MOUSELEAVE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
	if (cfg.wmouse.isTracking()) {
		cfg.wmouse.StopTracking();
	}

	return 0;
};

auto cWM_MOUSEHWHEEL = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
		// _glfwInputScroll(window, 0.0, (SHORT)HIWORD(wParam) / (double)WHEEL_DELTA);
	return 0;
};

auto cWM_MOUSEVWHEEL = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
		// _glfwInputScroll(window, -((SHORT)HIWORD(wParam) / (double)WHEEL_DELTA), 0.0);

	return 0;
};

auto cWM_ENTERSIZEMOVE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
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

auto cWM_ENTERMENULOOP = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
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

auto cWM_EXITSIZEMOVE = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long  {
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

auto cWM_EXITMENULOOP = [](const win_cpp::Window& window, Config& cfg, win_cpp::PolymorphismByWindows&& windowData) -> long long {
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


	template<typename UserData> using callback = std::function<long long(const win_cpp::Window&, UserData&, win_cpp::PolymorphismByWindows)>;
	template<typename UserData> struct CallbacksHolder : std::unordered_map<win_cpp::WindowMessage, callback<UserData>> {
		using Base = std::unordered_map<win_cpp::WindowMessage, callback<UserData>>;
		using Base::Base;
	};

	CallbacksHolder<Config> callbacks = {
		{ win_cpp::WindowMessage::WM_PAINT, cWM_PAINT },
		{ win_cpp::WindowMessage::WM_CREATE, cWM_CREATE },
		{ win_cpp::WindowMessage::WM_SIZING, cWM_SIZING },
		{ win_cpp::WindowMessage::WM_SIZE, cWM_SIZE },
		{ win_cpp::WindowMessage::WM_MOUSEACTIVATE, cWM_MOUSEACTIVATE },
		{ win_cpp::WindowMessage::WM_CAPTURECHANGED, cWM_CAPTURECHANGED },
		{ win_cpp::WindowMessage::WM_SETFOCUS, cWM_SETFOCUS },
		{ win_cpp::WindowMessage::WM_KILLFOCUS, cWM_KILLFOCUS },
		{ win_cpp::WindowMessage::WM_SYSCOMMAND, cWM_SYSCOMMAND },
		{ win_cpp::WindowMessage::WM_INPUTLANGCHANGE, cWM_INPUTLANGCHANGE },
		{ win_cpp::WindowMessage::WM_CHAR, cWM_CHAR },
		{ win_cpp::WindowMessage::WM_SYSCHAR, cWM_SYSCHAR },
		{ win_cpp::WindowMessage::WM_UNICHAR, cWM_UNICHAR },
		{ win_cpp::WindowMessage::WM_KEYDOWN, cWM_KEYDOWN },
		{ win_cpp::WindowMessage::WM_SYSKEYDOWN, cWM_SYSKEYDOWN },
		{ win_cpp::WindowMessage::WM_KEYUP, cWM_KEYUP },
		{ win_cpp::WindowMessage::WM_SYSKEYUP, cWM_SYSKEYUP },
		{ win_cpp::WindowMessage::WM_MOUSEMOVE, cWM_MOUSEMOVE },
		{ win_cpp::WindowMessage::WM_MOUSELEAVE, cWM_MOUSELEAVE },
		{ win_cpp::WindowMessage::WM_MOUSEHWHEEL, cWM_MOUSEHWHEEL },
		{ win_cpp::WindowMessage::WM_MOUSEWHEEL, cWM_MOUSEVWHEEL },
		{ win_cpp::WindowMessage::WM_ENTERSIZEMOVE, cWM_ENTERSIZEMOVE },
		{ win_cpp::WindowMessage::WM_ENTERMENULOOP, cWM_ENTERMENULOOP },
		{ win_cpp::WindowMessage::WM_EXITSIZEMOVE, cWM_EXITSIZEMOVE },
		{ win_cpp::WindowMessage::WM_EXITMENULOOP, cWM_EXITMENULOOP },
		{ win_cpp::WindowMessage::WM_CLOSE, cWM_CLOSE },
		{ win_cpp::WindowMessage::WM_QUIT, cWM_QUIT },
		{ win_cpp::WindowMessage::WM_LBUTTONDOWN, cWM_LBUTTONDOWN },
		{ win_cpp::WindowMessage::WM_RBUTTONDOWN, cWM_RBUTTONDOWN },
		{ win_cpp::WindowMessage::WM_MBUTTONDOWN, cWM_MBUTTONDOWN },
		{ win_cpp::WindowMessage::WM_XBUTTONDOWN, cWM_XBUTTONDOWN },
		{ win_cpp::WindowMessage::WM_LBUTTONUP, cWM_LBUTTONUP },
		{ win_cpp::WindowMessage::WM_RBUTTONUP, cWM_RBUTTONUP },
		{ win_cpp::WindowMessage::WM_MBUTTONUP, cWM_MBUTTONUP },
		{ win_cpp::WindowMessage::WM_XBUTTONUP, cWM_XBUTTONUP }
	};


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
	mainclass_info.wnd_proc = win_cpp::windowProc;
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
	export win_cpp::Instance instance{ win_cpp::DefaultInstance{} };
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
			std::jthread process;

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
				, config({}) // (info)
				, process(
					[
						window_info = win32_window_create_info(
							instance,
							main_class,
							to_win_rect(info.rect),
							to_win_title(info.title),
							get_WindowStyle(info),
							get_WindowStyleEX(info)
						),
						callbacks_ = callbacks,
						userdata_ = std::ref(config)
					]() mutable
					{
						const auto& cbs = callbacks_;
						auto& userdata = userdata_.get();
						win_cpp::Window prewnd(window_info);
						userdata.window = std::move(prewnd);
						userdata.ready = true;
						auto& window = userdata.window;
						auto x = [&cbs, &window, &userdata](win_cpp::WindowMessage wmsg, win_cpp::PolymorphismByWindows&& WindowData) -> long long {
							auto it = cbs.find(wmsg);
							if (it != cbs.end()) {
								auto res = std::invoke(it->second, window, userdata, WindowData);
								return res;
							}
							return win::f::DefWindowProcW(win_cpp::Window::type(window), std::to_underlying(wmsg), WindowData.wParam, WindowData.lParam);
						};

						using ltype = decltype(x);
						using ltype_ptr = decltype(&x);
						win::f::SetPropW(win_cpp::Window::type(window), L"GLFW", (&x));

						auto mywproc = [](
							win::t::HWND hWnd,
							win::t::UINT uMsg,
							win::t::WPARAM wParam,
							win::t::LPARAM lParam) -> win::t::LRESULT
						{
								ltype_ptr lmbd_ptr = static_cast<ltype_ptr>(win::f::GetPropW(hWnd, L"GLFW"));
								if (lmbd_ptr) {
									ltype& lmbd = *lmbd_ptr;
									return lmbd(static_cast<win_cpp::WindowMessage>(uMsg), win_cpp::PolymorphismByWindows{ wParam, lParam });
								}
								return win::f::DefWindowProcW(hWnd, uMsg, wParam, lParam);
						};

						window.SetWindowProc(mywproc);
#if 1
						window.show();
#endif
						win_cpp::Message msg;
						while (true) {
							auto wmsg = msg.get_msg();
							if (wmsg == win_cpp::WindowMessage::WM_NULL) {
								continue;
							}
							if (wmsg == win_cpp::WindowMessage::WM_QUIT) {
								break;
							}
							msg.translate();
							msg.dispatch();
						}
					} // lmbd
				) // process
			{
				while(!config.ready) {}
			} // ctor

		public:
			glfw::Title get_Title() const {
				return glfw::Title(config.window.get_Title().get_c()); 
			}
			void set_Title(const glfw::Title& title) { 
				config.window.set_Title(win_cpp::Title{ title.get_sv() });
			}

			// glfw::Icon get_Icon() const { get_Icon(); } 
			void set_Icon(const glfw::Icon& icon) { }

			glfw::Rect get_Position() const {
				auto win_rect = config.window.GetClientRect();
				return glfw::Rect(win_rect.get_left(), win_rect.get_top(), win_rect.get_right(), win_rect.get_bottom());
			}
			void set_Position(const glfw::Rect& rect) { 
				win_cpp::Rect wrect(rect.get_left(), rect.get_top(), rect.get_right(), rect.get_bottom());
				win_cpp::WindowZOrder order = win_cpp::WindowZOrder::HWND_TOPMOST;
				win_cpp::SetWindowPosFlags swp = win_cpp::SetWindowPosFlags::values::SWP_NOZORDER;
				config.window.SetWindowPosition(order, wrect, swp);
			}

			glfw::SizeLimits get_SizeLimits() const { return glfw::SizeLimits(0, 0); }
			void set_SizeLimits(const glfw::SizeLimits& s_limits) {} // set_SizeLimits(s_limits); }
#if 0 /* TODO*/
			glfw::AspectRatio get_AspectRatio() const { return get_AspectRatio(); }
			void set_AspectRation(const glfw::AspectRatio& aspect_ratio) { set_AspectRatio(aspect_ratio); }
#endif		
			// glfw::Opacity_type get_Opacity() const { get_Opacity(); }
			// void set_Opacity(const glfw::Opacity_type& opacity) { set_Opacity(); }

			void maximize() { config.window.maximize(); }
			void show() { config.window.show(); }
			void hide() { config.window.hide(); }
			void focus() { config.window.focus(); }

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

			const win_cpp::Window& get_win_window() const {
				if (!win_cpp::Window::type(config.window)) { throw; }
				return config.window;
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
		Win32SurfaceCreateInfo.setHinstance((HINSTANCE)vp_i);
		Win32SurfaceCreateInfo.setHwnd((HWND)vp_h);
		Win32SurfaceCreateInfo.setFlags(create_flags);
		return vk::raii::SurfaceKHR(vk_instance, Win32SurfaceCreateInfo);
	}

} // ns 
