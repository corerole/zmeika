module;

export module glfw;
import glfw_base;
#ifdef __WINDOWS
import glfw_win32;
#endif
#ifdef __X11
import glfw_x11;
#endif
#ifdef __WAYLAND
import glfw_wayland;
#endif
#ifdef __ANDROID
import glfw_Android;
#endif

export namespace glfw {
	using KeyStateMap = glfw_base::KeyStateMap;
	using glfw_base::inital_key_state;

	using CharModsFlags = glfw_base::CharModsFlags;
	using Key = glfw_base::Key;
	using KeyState = glfw_base::KeyState;
	using AspectRatioFormats = glfw_base::AspectRatioFormats;
	using Orientation = glfw_base::Orientation;
	using FrameActionState = glfw_base::FrameActionState;
	using CursorState = glfw_base::CursorState;
	using CursorRawInputState = glfw_base::CursorRawInputState;
	using FrameActionState = glfw_base::FrameActionState;

	using CharModsCallbackF = glfw_base::CharModsCallbackF;
	using CharacterCallbackF = glfw_base::CharacterCallbackF;
	using KeyCallbackF = glfw_base::KeyCallbackF;

	using WindowRectCallbackF = glfw_base::WindowRectCallbackF;
	using WindowCloseCallbackF = glfw_base::WindowCloseCallbackF;

	using CursorStateCallbackT = glfw_base::CursorStateCallbackT;
	using CursorPositionCallbackT = glfw_base::CursorPositionCallbackT;

	using Rect = glfw_base::Rect;
	using Icon = glfw_base::Icon;
	using SizeLimits = glfw_base::SizeLimits;
	using Title = glfw_base::Title;
	using OpacityType = glfw_base::OpacityType;
	template<typename T> using AR = glfw_base::AR<T>;
	using AspectRatio = glfw_base::AspectRatio;
	using WindowCreateInfo = glfw_base::WindowCreateInfo;

	// -----------------------------------------------------------

#ifdef __WINDOWS
	using Window = glfw_base::Window<glfw_win32::Window>;
#elifdef __X11
	using Window = glfw_base::Window<glfw_x11::Window>;
#elifdef  __WAYLAND
	using Window = glfw_base::Window<glfw_wayland::Window>;
#elifdef __ANDROID	
	using Window = glfw_base::Window<glfw_Android::Window>;
#else
#	error "Platform not defined"	
#endif

	// -----------------------------------------------------------
}