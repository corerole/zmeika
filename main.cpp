import std;
import win_cpp;
import glfw_win32_window;
import glfw;
import vulkan;
import vulkan_helpers;
import vkCube;

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
	unsigned width = glfw_rect.get_right() - glfw_rect.get_left();
	unsigned height = glfw_rect.get_bottom() - glfw_rect.get_top();
	vk::SurfaceCapabilitiesKHR capabilities = physical_device.getSurfaceCapabilitiesKHR(surface);

	vk::Extent2D extent;
	extent.width = vk::supp::myclamp(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
	extent.height = vk::supp::myclamp(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

	glfw::WindowRectCallbackF rect_callback = [&glfw_rect](const glfw::Rect& rect) {
		glfw_rect = rect;
	};
	window.set_window_rect_callback(std::move(rect_callback));

	auto update_extent = [&glfw_rect, &extent, &physical_device, &surface]() {
		unsigned width = glfw_rect.get_right() - glfw_rect.get_left();
		unsigned height = glfw_rect.get_bottom() - glfw_rect.get_top();
		vk::SurfaceCapabilitiesKHR capabilities = physical_device.getSurfaceCapabilitiesKHR(surface);
		extent.width = vk::supp::myclamp(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		extent.height = vk::supp::myclamp(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
	};
	
	vk::raii::SwapchainKHR swapchain = vk::supp::get_Swapchain(logical_device, physical_device, surface, GaPq, surface_format.format, extent);
	vk::raii::RenderPass renderpass = vk::supp::get_RenderPass(logical_device, physical_device, surface_format.format);

	vkCube::vkCubeT vkCube_shader(logical_device, physical_device, renderpass, extent, graphics_queue, commandpool);
	constexpr unsigned frames_in_flight = 2;

#if 1
	auto create_depth_image = [&logical_device, &physical_device, &commandpool, &graphics_queue, &extent]() {
		auto depth_resource = vkCube::createDepthResources(logical_device, physical_device, extent); //, commandpool, graphics_queue);
		vk::raii::ImageView DepthImageView = vkCube::createDepthImageView(logical_device, depth_resource.first);
		return std::pair(std::move(DepthImageView), std::move(depth_resource));
	};

	auto create_color_image = [&logical_device, &physical_device, &commandpool, &graphics_queue, &extent, format = surface_format.format]() {
		auto color_resource = vkCube::createColorResources(logical_device, physical_device, extent, format); //, commandpool, graphics_queue);
		vk::raii::ImageView ColorImageView = vkCube::createColorImageView(logical_device, color_resource.first, format);
		return std::pair(std::move(ColorImageView), std::move(color_resource));
	};

	auto update_color_image = [color_data = create_color_image(), &create_color_image]() mutable -> const vk::raii::ImageView& {
		color_data = create_color_image();
		return color_data.first;
	};

	auto update_depth_image = [depth_data = create_depth_image(), &create_depth_image]() mutable -> const vk::raii::ImageView& {
		depth_data = create_depth_image();
		return depth_data.first;
	};
#endif

	std::vector<vk::Image> swapchain_images;
	auto update_swapchain_images = [&swapchain_images, &swapchain]() {
		swapchain_images = swapchain.getImages();
	};
	update_swapchain_images();

	std::vector<vk::raii::ImageView> swapchain_ImageViews;
	auto update_image_views = [&logical_device, &surface_format, &swapchain_images, &swapchain_ImageViews]() {
		vk::supp::set_ImageViews(
			logical_device,
			surface_format.format,
			swapchain_images,
			swapchain_ImageViews
		);
	};
	update_image_views();
	
	std::vector<vk::raii::Framebuffer> framebuffers;
	auto update_framebuffes = [&framebuffers, &logical_device, &renderpass, &extent, &swapchain_ImageViews, &update_depth_image, &update_color_image]() {
		vk::supp::set_SwapchainFramebuffers(framebuffers, logical_device, renderpass, extent, swapchain_ImageViews, update_color_image(), update_depth_image());
	};
	update_framebuffes();

	std::vector<vk::raii::CommandBuffer> command_buffers;
	auto alloc_command_buffers = [&logical_device, &command_buffers, &commandpool, n_buffs = swapchain_images.size()]() {
		vk::CommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
		allocInfo.commandPool = *commandpool;
		allocInfo.level = vk::CommandBufferLevel::ePrimary;
		allocInfo.commandBufferCount = n_buffs;
		command_buffers = logical_device.allocateCommandBuffers(allocInfo);
	};
	alloc_command_buffers();

	auto update_commandbuffer = [&vkCube_shader, &renderpass, &extent](
			const vk::raii::CommandBuffer& command_buffer,
			const vk::raii::Framebuffer& framebuffer
		) {
		vkCube_shader.update(extent);
		vkCube_shader.setup_command_buffers(command_buffer, framebuffer, renderpass, extent);
	};

	auto update_commandbuffers = [&update_commandbuffer, &command_buffers, &framebuffers]() {
		auto v = std::views::zip(command_buffers, framebuffers);
		for (auto&& [cb, fb] : v) {
			update_commandbuffer(cb, fb);
		}
	};

	auto update_swapchain = [&swapchain, &logical_device, &physical_device, &surface, &GaPq, &surface_format, &extent]() {
		auto newSwapchain	= vk::supp::get_Swapchain(logical_device, physical_device, surface, GaPq, surface_format.format, extent, std::move(swapchain));
		swapchain = std::move(newSwapchain);
	};

	auto recreate_swapchain = [
		&update_swapchain,
		&update_swapchain_images,
		&update_image_views,
		&update_framebuffes
	]() {
		update_swapchain();
		update_swapchain_images();
		update_image_views();
		update_framebuffes();
	};

	vk::supp::Renderer renderer(logical_device, frames_in_flight, swapchain_ImageViews.size());
	auto render_frame = [&renderer, &logical_device, &swapchain, &graphics_queue, &present_queue, &command_buffers, &framebuffers, &update_commandbuffer]() -> bool {
		return renderer.render_frame(logical_device, swapchain, graphics_queue, present_queue, command_buffers, framebuffers, update_commandbuffer);
	};

	while(true) {
		auto res = render_frame();
		if (!res) {
			logical_device.waitIdle();
			update_extent();
			recreate_swapchain();
		}
	}
}
