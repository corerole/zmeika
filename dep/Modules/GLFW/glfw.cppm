module;

export module glfw;
import std;
import glfw_enums;

export namespace glfw {
	using CharModsFlags = glfw_enums::CharModsFlags;
	using Key = glfw_enums::Key;
	using KeyState = glfw_enums::KeyState;
	using AspectRatioFormats = glfw_enums::AspectRatioFormats;
	using Orientation = glfw_enums::Orientation;
	using FrameActionState = glfw_enums::FrameActionState;
	using GLFWKeyState = glfw_enums::GLFWKeyState;
	using CursorState = glfw_enums::CursorState;
	using CursorRawInput = glfw_enums::CursorRawInput;
	using FrameActionState = glfw_enums::FrameActionState;
	using glfw_enums::scancode_key_state;

	struct Rect;

	using CharModsCallbackF = std::function<void(const std::pair<wchar_t, wchar_t>&, CharModsFlags)>;
	using CharacterCallbackF = std::function<void(const std::pair<wchar_t, wchar_t>&)>;
	using KeyCallbackF = std::function<void(Key, unsigned, KeyState, CharModsFlags)>;

	using WindowRectCallbackF = std::function<void(const glfw::Rect&)>;

	using CursorStateCallbackT = std::function<void(const glfw::CursorState&)>;
	using CursorPositionCallbackT = std::function<void(const std::pair<int, int>&)>;

	template<typename WindowType, typename WindowCreateInfo> concept windowLike =
		requires(
		WindowType& window,
		const WindowType & const_window,
		const WindowCreateInfo& cfg,
		CharModsCallbackF&& cmc,
		CharacterCallbackF&& cc,
		KeyCallbackF&& kc,
		CursorStateCallbackT&& csct,
		CursorPositionCallbackT&& cpct,
		WindowRectCallbackF&& wrc
		)
	{
		{ WindowType(cfg) };
		{ const_window.isResizable() } -> std::same_as<bool>;
		{ window.set_key_mods_callback(std::forward<decltype(cmc)>(std::move(cmc))) } -> std::same_as<void>;
		{ window.set_character_callback(std::forward<decltype(cc)>(std::move(cc))) }-> std::same_as<void>;
		{ window.set_key_callback(std::forward<decltype(kc)>(std::move(kc))) } -> std::same_as<void>;
		{ window.set_cursor_position_callback(std::forward<decltype(cpct)>(std::move(cpct))) } -> std::same_as<void>;
		{ window.set_cursor_state_callback(std::forward<decltype(csct)>(std::move(csct))) } -> std::same_as<void>;
		{ window.set_window_rect_callback(std::forward<decltype(wrc)>(std::move(wrc))) } -> std::same_as<void>;
	};

	struct wResizable {
		private:
			bool resizable = false;

		public:
			wResizable(bool x) : resizable(x) {}

		public:
			bool isResizable() const { return resizable; }
			void setResizable(bool x) { resizable = x; }
	};

	struct wVisible {
		private:
			bool visible;

		public:	
			wVisible(bool x) : visible(x) {}

		public:
			bool isVisible() const { return visible;  }
			void setVisible(bool x) { visible = x; }
	};

	struct wDecorated {
		private:
			bool decorated;

		public:
			wDecorated(bool x) : decorated(x) {}

		public:
			bool isDecorated() const { return decorated;  }
			void setDecorated(bool x) { decorated = x; }
	};

	struct wFocused {
		private:
			bool focused;

		public:
			wFocused(bool x) : focused(x) {}

		public:
			bool isFocused() const { return focused;  }
			void setFocused(bool x) { focused = x; }
	};

	struct wAutoiconify {
		private:
			bool autoiconify;

		public:
			wAutoiconify(bool x) : autoiconify(x) {}

		public:
			bool isAutoiconify() const { return autoiconify;  }
			void setAutoiconify(bool x) { autoiconify = x; }
	};

	struct wFloating {
		private:
			bool floating;

		public:
			wFloating(bool x) : floating(x) {}

		public:
			bool isFloating() const { return floating;  }
			void setFloating(bool x) { floating = x; }
	};

	struct wMaximized {
		private:
			bool maximized;

		public:
			wMaximized(bool x) : maximized(x) {}

		public:
			bool isMaximized() const { return maximized;  }
			void setMaximized(bool x) { maximized = x; }
	};

	struct wCenterCursor {
		private:
			bool centerCursor;

		public:	
			wCenterCursor(bool x) : centerCursor(x) {}

		public:
			bool isCenterCursor() const { return centerCursor;  }
			void setCenterCursor(bool x) { centerCursor = x; }
	};

	struct wTransparent {
		private:
			bool transparent;

		public:
			wTransparent(bool x) : transparent(x) {}

		public:
			bool isTransparent() const { return transparent;  }
			void setTransparent(bool x) { transparent = x; }
	};

	struct wFocusOnShow {
		private:
			bool focusOnShow;

		public:
			wFocusOnShow(bool x) : focusOnShow(x) {}

		public:
			bool isFocusOnShow() const { return focusOnShow;  }
			void setFocusOnShow(bool x) { focusOnShow = x; }
	};

	struct wScaleToMonitor {
		private:
			bool scaleToMonitor;

		public:
			wScaleToMonitor(bool x) : scaleToMonitor(x) {}

		public:
			bool isScaleToMonitor() const { return scaleToMonitor;  }
			void setScaleToMonitor(bool x) { scaleToMonitor = x; }
	};

	struct Icon {};

	/* template<typename value_type> */
	struct Rect {
		private:
			long left, top, right, bottom;

		public:
			const long& get_top() const { return top; }
			long& get_top() { return top; }

			const long& get_bottom() const { return bottom; }
			long& get_bottom() { return bottom; }

			const long& get_right() const { return right; }
			long& get_right() { return right; }

			const long& get_left() const { return left; }
			long& get_left() { return left; }

			Rect(long left = 0, long top = 0, long right = 0, long bottom = 0) : left(left), top(top), right(right), bottom(bottom) {}
	};

	struct SizeLimits {
		private:
			long height, width;

		public:
			SizeLimits() : height(0), width(0) {}
			SizeLimits(long height, long width) : height(height), width(width) {}

	};

	std::wstring StringToWString(std::string_view sv) {
		return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(sv.data(), sv.data() + sv.size());
	}

	struct Title {
		private:
			std::string title;
		public:
			Title() : title(" ") {}
			Title(std::string_view str) : title(str) {}

		public:
			std::string_view get_sv() const { return std::string_view(title); }
	};

	using Opacity_type = float;

	struct WindowCreateInfo {
		Rect rect = Rect(25, 25, 400, 400);
		Title title = Title("App");
		bool resizable;
		bool decorated;
		bool visible;
		bool focused;
		bool floating;
		bool maximized;
		bool autoiconify;
		bool center_cursor;
		bool transparent;
		bool focus_on_show;
		bool scale_to_monitor;
	};

	template<typename T> concept WindowLikeWithDefaultConfig = windowLike<T, WindowCreateInfo>;
	template<WindowLikeWithDefaultConfig NativeWindow> struct Window {
		explicit operator const NativeWindow& () const { return window; }

		private:
			NativeWindow window;

		public:
			Window(const WindowCreateInfo& info) : window(info) {}
			Window() : window(WindowCreateInfo{}) {}

		public:
			bool isResizable() const { return window.isResizable(); }
			void setResizable(bool state) { window.setResizable(state); }
			bool isDecorated() const { return window.isDecorated(); }
			void setDecorated(bool state) { window.setDecorated(state); }
			bool isVisible() const { return window.isVisible(); }
			void setVisible(bool state) { window.setVisible(state); }
			bool isFocused() const { return window.isFocused(); }
			void setFocused(bool state) { window.setFocused(state); }
			bool isFloating() const { return window.isFloating(); }
			void setFloating(bool state) { window.setFloating(state); }
			bool isMaximized() const { return window.isMaximized(); }
			void setMaximized(bool state) { window.setMaximized(state); }
			bool isAutoiconify() const { return window.isAutoiconify(); }
			void setAutoiconify(bool state) { window.setAutoiconify(state); }
			bool isCenterCursor() const { return window.isCenterCursor(); }
			void setCenterCursor(bool state) { window.setCenterCursor(state); }
			bool isTransparent() const { return window.isTransparent(); }
			void setTransparent(bool state) { window.setTransparent(state); }
			bool isFocusOnShow() const { return window.isFocusOnShow(); } 
			void setFocusOnShow(bool state) { window.setFocusOnShow(state); }
			bool isScaleToMonitor() const { return window.isScaleToMonitor(); }
			void setScaleToMonitor(bool state) { window.setScaleToMonitor(state); }

			Title get_Title() const { return window.get_Title(); }
			void set_Title(Title title) { window.set_Title(title); }
#if 0
			Icon get_Icon() const { window.get_Icon(); }
#endif
			void set_Icon(const Icon& icon) { window.set_Icon(icon); }

			Rect get_Position() const { return window.get_Position(); }
			void set_Position(const Rect& rect) { window.set_Position(rect); } // Absolute or relative 

			SizeLimits get_SizeLimits() const { return window.get_SizeLimits(); }
			void set_SizeLimits(const SizeLimits& s_limits) { window.set_SizeLimits(s_limits); }
#if 0 /* TODO*/
			AspectRatio get_AspectRatio() const { return window.get_AspectRatio(); }
			void set_AspectRation(const AspectRatio& aspect_ratio) { window.set_AspectRatio(aspect_ratio); }
#endif		
			Opacity_type get_Opacity() const { window.get_Opacity(); }
			void set_Opacity(const Opacity_type& opacity) { window.set_Opacity(); }

			void maximize() { window.maximize(); }
			void show() { window.show(); }
			void hide() { window.hide(); }
			void focus() { window.focus(); }

		public:
			void set_key_mods_callback(CharModsCallbackF&& cmc) { 
				window.set_key_mods_callback(std::forward<decltype(cmc)>(cmc));
			}
			void set_character_callback(CharacterCallbackF&& cc) {
				window.set_character_callback(std::forward<decltype(cc)>(cc));
			}
			void set_key_callback(KeyCallbackF&& kc) {
				window.set_key_callback(std::forward<decltype(kc)>(kc));
			}
			void set_cursor_position_callback(CursorPositionCallbackT&& cpct) {
				window.set_cursor_position_callback(std::forward<decltype(cpct)>(cpct));
			}
			void set_cursor_state_callback(CursorStateCallbackT&& csct) {
				window.set_cursor_state_callback(std::forward<decltype(csct)>(csct));
			}
			void set_window_rect_callback(glfw::WindowRectCallbackF&& wrb) {
				window.set_window_rect_callback(std::forward<decltype(wrb)>(wrb));
			}
	};

	template<typename ValueType>
	struct AR : std::pair<ValueType, ValueType> {
		using Base = std::pair<ValueType, ValueType>;
		using Base::Base;
		using ft = Base::first_type;
		using st = Base::second_type;
		using Base::first;
		using Base::second;
		using nominator_type = std::add_lvalue_reference_t<ft>;
		using const_nominator_type = std::add_const_t<nominator_type>;
		using denominator_type = std::add_lvalue_reference_t<st>;
		using const_denominator_type = std::add_const_t<denominator_type>;

		const_nominator_type nominator() const { return first; }
		nominator_type nominator() { return first; }

		const_denominator_type denominator() const { return second; }
		denominator_type denominator() { return second; }
	};

	struct AspectRatio {
		using value_type = float;
		using ValueHolder = glfw_enums::AspectRaitoFormatsMapType;
		using AR_type = AR <value_type>;
		private:
			ValueHolder val = glfw_enums::AspectRatioStandardFormats;
			AspectRatioFormats formats = AspectRatioFormats::Square;
			Orientation orientaton = Orientation::Landscape;

		public:
			AR_type get() const { 
				auto it = val.find(formats);
				if(it != val.end()) {
					if (std::to_underlying(orientaton)) {
						return AR_type{ it->first, it->second };
					}	else {
						return AR_type{ it->second, it->first };
					}
				}
				throw std::runtime_error(" There is no such format ");
			}

			void set_format(AspectRatioFormats fmt) {
				formats = fmt;
			}

			void set_orientation(Orientation orient) {
				orientaton = orient;
			}

			double get_Ratio() const {
				auto res = get();
				return res.nominator() / res.denominator();
			}

			AspectRatio(
				AspectRatioFormats format = AspectRatioFormats::Square,
				Orientation orient = Orientation::Landscape
			) : formats(format), orientaton(orient) {}
	};

	struct FrameAction {
		using state = FrameActionState;
		private:
			state state_ = state::disabled;

		public:
			constexpr state get_state() const noexcept { return state_; }
			constexpr void set_state(const state& state) noexcept { state_ = state; }
	};

} // ns glfw

