import std;
import win_cpp;
import glfw_win32_window;
import glfw;
import vulkan;
import vulkan_helpers;

using namespace std::chrono_literals;

glfw::CharModsCallbackF charmod_default_callback = [](const std::pair<wchar_t, wchar_t>& sp, glfw::CharModsFlags charmod) {
	auto& [ch1, ch2] = sp;
	if (ch2 == 0) {
		std::wcout << ch1;
	}	else {
		std::wcout << ch1 << ch2;
	}
};

glfw::CharacterCallbackF character_default_callback = [](const auto& sp) {
	auto& [ch1, ch2] = sp;
	if (ch2 == 0) {
		std::wcout << ch1;
	}	else {
		std::wcout << ch1 << ch2;
	}
};

glfw::KeyCallbackF key_default_callback = [](
	glfw::Key key,
	unsigned scancode, // ?
	glfw::KeyState action,
	glfw::CharModsFlags mods
	) {
		std::cout << std::hex << "Key: " << scancode
			<< " | action: " << std::to_underlying(action)
			<< " | mods: " << glfw::CharModsFlags::MaskType(mods)
			<< std::endl;
};

glfw::CursorPositionCallbackT cursor_position_default_callback = [](const std::pair<int, int>& pos) {
	auto&& [x, y] = pos;
	std::cout << "cpos | x=" << x << " | y=" << y << " |\n";
};

glfw::CursorStateCallbackT cursor_state_default_callback = [](const glfw::CursorState& state) {
	std::cout << "cstate: " << std::to_underlying(state) << "\n";
};

/* ------------------  VK_TEST ----------------------- */
constexpr std::string_view AppName = "AppName";
constexpr std::string_view VkEngineName = "EngineName";

vk::ApplicationInfo AppInfo(
	AppName.data(),
	vk::supp::myVK_MAKE_VERSION(1, 0, 0),
	VkEngineName.data(),
	vk::supp::myVK_MAKE_VERSION(1, 0, 0),
	vk::ApiVersion14
);

vk::InstanceCreateFlags instance_create_flags;

const std::vector<const char*> EnabledLayers = {
	"VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> EnabledExtensions = {
	"VK_KHR_surface",
	"VK_KHR_win32_surface"
};

vk::InstanceCreateInfo InstanceInfo(
	instance_create_flags,
	&AppInfo,
	EnabledLayers,
	EnabledExtensions
);

vk::raii::Context context;
vk::raii::Instance instance(context, InstanceInfo);

/* ------------------  VK_TEST ----------------------- */

int main() {
	glfw::WindowCreateInfo info = {};
	info.title = glfw::Title(AppName);
	info.rect = glfw::Rect(25, 25, 400, 400);
	using window_type = glfw::Window<win32_window::GLFW_Window_Win>;
	window_type window;
	window.set_key_mods_callback(std::move(charmod_default_callback));
	window.set_character_callback(std::move(character_default_callback));
	window.set_key_callback(std::move(key_default_callback));
	window.set_cursor_position_callback(std::move(cursor_position_default_callback));
	window.set_cursor_state_callback(std::move(cursor_state_default_callback));

	vk::raii::SurfaceKHR surface = win32_window::get_vk_raii_SurfaceKHR(instance, window);
	auto PhisicalDevices = instance.enumeratePhysicalDevices();
	const vk::raii::PhysicalDevice& physical_device = PhisicalDevices[0];
	auto GaPq = vk::supp::get_QueueFamilies(physical_device, surface);
	vk::raii::Device logical_device = vk::supp::get_LogicalDevice(physical_device, GaPq);
	vk::raii::CommandPool commandpool = vk::supp::get_CommandPool(logical_device, GaPq);
	vk::raii::Queue graphics_queue(logical_device, GaPq.first, 0);
	vk::raii::Queue present_queue(logical_device, GaPq.second, 0);
	vk::SurfaceFormatKHR surface_format = vk::supp::get_SurfaceFormatKHR(physical_device, surface);

	glfw::Rect glfw_rect = window.get_Position();
	glfw::WindowRectCallbackF rect_callback = [&glfw_rect](const glfw::Rect& rect) {
		glfw_rect = rect;
	};
	window.set_window_rect_callback(std::move(rect_callback));
	unsigned width = glfw_rect.get_right() - glfw_rect.get_left();
	unsigned height = glfw_rect.get_bottom() - glfw_rect.get_top();

	vk::SurfaceCapabilitiesKHR capabilities = physical_device.getSurfaceCapabilitiesKHR(surface);
	vk::Extent2D extent;
	extent.width = vk::supp::myclamp(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
	extent.height = vk::supp::myclamp(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

	vk::raii::RenderPass renderpass = vk::supp::get_RenderPass(logical_device, surface_format.format);
}
