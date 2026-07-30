import std;
import win_cpp;
import glfw_win32_window;
import glfw;
import vulkan;
import vulkan_helpers;
import CameraUBO;
import vkCube;
import ground_shader;
import skybox_shader;

using namespace std::chrono_literals;

glfw::CharModsCallbackF x_charmod_default_callback = [](unsigned codepoint, glfw::CharModsFlags charmod) constexpr noexcept {};
glfw::CharacterCallbackF x_character_default_callback = [](const auto& sp) constexpr noexcept {};
glfw::KeyCallbackF x_key_default_callback = [](glfw::Key key, unsigned scancode,	glfw::KeyState action, glfw::CharModsFlags mods) noexcept {};
glfw::CursorPositionCallbackT x_cursor_position_default_callback = [](const std::pair<int, int>& pos) noexcept {};
glfw::CursorStateCallbackT x_cursor_state_default_callback = [](const glfw::CursorState& state) noexcept {};

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
	window_type window(info);
	window.set_key_mods_callback(std::move(x_charmod_default_callback));
	window.set_character_callback(std::move(x_character_default_callback));
	window.set_key_callback(std::move(x_key_default_callback));
	std::pair<long, long> m_pos(0, 0);
	window.set_cursor_position_callback(std::move([&m_pos](const std::pair<long, long>& pos) { m_pos = pos; }));
	window.set_cursor_state_callback(std::move(x_cursor_state_default_callback));

	std::atomic<bool> ready{ false };
	std::atomic<bool> called{ false };
	auto close_callback = [r_ready = std::ref(ready), r_called = std::ref(called)]() {
		auto& ready = r_ready.get();
		auto& called = r_called.get();
		called.store(true, std::memory_order_relaxed);
		while (!ready.load(std::memory_order_relaxed)) {
			std::this_thread::yield();
		}
	};
	window.set_window_close_callback(std::move(close_callback));

	{
		vk::raii::SurfaceKHR surface = win32_window::get_vk_raii_SurfaceKHR(instance, window);

		auto PhisicalDevices = instance.enumeratePhysicalDevices();
		// std::cout << "PDs size:" << PhisicalDevices.size() << std::endl;
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
#if 1
			auto get_wh = [&glfw_rect]() {
				unsigned width = glfw_rect.get_right() - glfw_rect.get_left();
				unsigned height = glfw_rect.get_bottom() - glfw_rect.get_top();
				return std::pair{std::move(width), std::move(height)};
			};
			auto pwh = get_wh();
			std::this_thread::sleep_for(100ms);
			auto nwh = get_wh();
			while ((pwh.first != nwh.first) || (pwh.second) != (nwh.second)) {
				pwh = nwh;
				std::this_thread::sleep_for(100ms);
				nwh = get_wh();
			}
			auto& width = nwh.first;
			auto& height = nwh.second;
			
			vk::SurfaceCapabilitiesKHR capabilities = physical_device.getSurfaceCapabilitiesKHR(surface);
			extent.width = vk::supp::myclamp(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			extent.height = vk::supp::myclamp(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
#else
			extent = physical_device.getSurfaceCapabilitiesKHR(surface).currentExtent;
#endif
			};

		auto choice_present_mode = [&physical_device, &surface]() -> vk::PresentModeKHR {
			auto presentModes = physical_device.getSurfacePresentModesKHR(surface);
			auto is_avaible = [&presentModes]<vk::PresentModeKHR PM>() -> char {
				auto pred = [](auto&& it) { return (it == PM) ? true : false; };
				auto res = std::find_if(presentModes.begin(), presentModes.end(), pred);
				auto x = (res == presentModes.end()) ? true : false;
				if (!x) { std::cout << "supported"; } else { std::cout << "unsupported"; }
				return ' ';
			};

			std::cout << "Choice Mode: " << std::endl
				<< "\t1 - eMailbox | " << is_avaible.operator()<vk::PresentModeKHR::eMailbox>() << std::endl
				<< "\t2 - eFifo | " << is_avaible.operator()<vk::PresentModeKHR::eFifo>() << std::endl
				<< "\t3 - eFifoRelaxed | " << is_avaible.operator()<vk::PresentModeKHR::eFifoRelaxed>() << std::endl
				<< "\t4 - eSharedDemandRefresh | " << is_avaible.operator()<vk::PresentModeKHR::eSharedDemandRefresh>() << std::endl
				<< "\t5 - eSharedContinuousRefresh | " << is_avaible.operator()<vk::PresentModeKHR::eSharedContinuousRefresh>() << std::endl
				<< "\t6 - eFifoLatestReady | " << is_avaible.operator()<vk::PresentModeKHR::eFifoLatestReady>() << std::endl
				<< "\t7 - eFifoLatestReadyEXT | " << is_avaible.operator()<vk::PresentModeKHR::eFifoLatestReadyEXT>() << std::endl
				<< "\t8 - eImmediate | " << is_avaible.operator()<vk::PresentModeKHR::eImmediate>() << std::endl
				<< ">> ";

			vk::PresentModeKHR pm = vk::PresentModeKHR::eFifo;
			int mode = 0;
			std::cin >> mode;
			switch (mode) {
				case 1: { pm = vk::PresentModeKHR::eMailbox; break; }
				case 2: { pm = vk::PresentModeKHR::eFifo; break; }
				case 3: { pm = vk::PresentModeKHR::eFifoRelaxed; break; }
				case 4: { pm = vk::PresentModeKHR::eSharedDemandRefresh; break; }
				case 5: { pm = vk::PresentModeKHR::eSharedContinuousRefresh; break; }
				case 6: { pm = vk::PresentModeKHR::eFifoLatestReady; break; }
				case 7: { pm = vk::PresentModeKHR::eFifoLatestReadyEXT; break; }
				case 8: { pm = vk::PresentModeKHR::eImmediate; break; }
				default: { pm = vk::PresentModeKHR::eImmediate; }
			}
			
			return pm;
		};

		vk::PresentModeKHR present_mode = choice_present_mode();
		vk::raii::SwapchainKHR swapchain = vk::supp::get_Swapchain(logical_device, physical_device, surface, GaPq, surface_format.format, extent, present_mode);
		vk::raii::RenderPass renderpass = vk::supp::get_RenderPass(logical_device, physical_device, surface_format.format);

		auto AnisotropySamplerInfo = vk::supp::get_AnisotropySamplerInfo();
		std::vector<vk::SamplerCreateInfo> si = { AnisotropySamplerInfo };
		vk::supp::Samplers_DescriptorSetHolder sdsh(si, logical_device);

		CameraUBO::vkUBO_T camera(extent, logical_device, physical_device);
		vkCube::vkCubeT vkCube_shader(logical_device, camera.get_DescriptorSetLayout(), physical_device, renderpass, extent, graphics_queue, commandpool);
		ground_shader::GroundShader gs(logical_device, camera.get_DescriptorSetLayout(), physical_device, renderpass, extent, graphics_queue, commandpool);
		skybox_shader::SkyBox skybox(logical_device, camera.get_DescriptorSetLayout(), physical_device, renderpass, extent, graphics_queue, commandpool);

		auto create_depth_image = [&logical_device, &physical_device, &commandpool, &graphics_queue, &extent]() {
			auto depth_resource = vk::supp::createDepthResources(logical_device, physical_device, extent);
			vk::raii::ImageView DepthImageView = vkCube::createDepthImageView(logical_device, depth_resource.first);
			return std::pair(std::move(DepthImageView), std::move(depth_resource));
		};

		auto create_color_image = [&logical_device, &physical_device, &commandpool, &graphics_queue, &extent, format = surface_format.format]() {
			auto color_resource = vk::supp::createColorResources(logical_device, physical_device, extent, format);
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
		
		constexpr std::size_t MAX_IMAGES = 32;

		constexpr std::size_t VK_IMAGES_N_ELEMS = MAX_IMAGES;
		constexpr std::size_t VK_IMAGES_SIZE = VK_IMAGES_N_ELEMS * sizeof(vk::raii::Image);
		std::array<std::byte, VK_IMAGES_SIZE> VK_IMAGES_BUFFER = {};
		std::pmr::monotonic_buffer_resource VK_IMAGES_RESOURCE(VK_IMAGES_BUFFER.data(), VK_IMAGES_BUFFER.size(), nullptr);
		std::pmr::vector<vk::Image> swapchain_images(&VK_IMAGES_RESOURCE);
		swapchain_images.reserve(VK_IMAGES_N_ELEMS);
		
		unsigned frames_in_flight = 0;

		auto update_swapchain_images = [&swapchain_images, &swapchain, &frames_in_flight]() {
			swapchain_images.clear();
			auto si = swapchain.getImages();
			for (auto& elem : si) { swapchain_images.emplace_back(std::move(elem)); }
			frames_in_flight = swapchain_images.size();
		};
		update_swapchain_images();

		constexpr std::size_t VK_IMAGE_VIEWS_N_ELEMS = MAX_IMAGES;
		constexpr std::size_t VK_IMAGE_VIEWS_SIZE = VK_IMAGE_VIEWS_N_ELEMS * (sizeof(vk::raii::ImageView) + alignof(vk::raii::ImageView));
		alignas(alignof(vk::raii::ImageView)) std::array<std::byte, VK_IMAGE_VIEWS_SIZE> VK_IMAGE_VIEWS_BUFFER = {};
		std::pmr::monotonic_buffer_resource VK_IMAGE_VIEWS_RESOURCE(VK_IMAGE_VIEWS_BUFFER.data(), VK_IMAGE_VIEWS_BUFFER.size(), nullptr);
		std::pmr::vector<vk::raii::ImageView> swapchain_ImageViews(&VK_IMAGE_VIEWS_RESOURCE);
		swapchain_ImageViews.reserve(VK_IMAGE_VIEWS_N_ELEMS);
		auto update_image_views = [&logical_device, &surface_format, &swapchain_images, &swapchain_ImageViews, &sdsh]() {
			vk::supp::set_ImageViews(
				logical_device,
				surface_format.format,
				swapchain_images,
				swapchain_ImageViews
			);
			sdsh.update_ImageViews(logical_device, swapchain_ImageViews);
		};
		update_image_views();

		constexpr std::size_t VK_FRAMEBUFFERS_N_ELEMS = MAX_IMAGES;
		constexpr std::size_t VK_FRAMEBUFFERS_SIZE = VK_FRAMEBUFFERS_N_ELEMS * (sizeof(vk::raii::Framebuffer) + alignof(vk::raii::Framebuffer));
		alignas(alignof(vk::raii::Framebuffer)) std::array<std::byte, VK_FRAMEBUFFERS_SIZE> VK_FRAMEBUFFERS_BUFFER = {};
		std::pmr::monotonic_buffer_resource VK_FRAMEBUFFERS_RESOURCE(VK_FRAMEBUFFERS_BUFFER.data(), VK_FRAMEBUFFERS_BUFFER.size(), nullptr);
		std::pmr::vector<vk::raii::Framebuffer> framebuffers(&VK_FRAMEBUFFERS_RESOURCE);
		framebuffers.reserve(VK_FRAMEBUFFERS_N_ELEMS);
		auto update_framebuffes = [&framebuffers, &logical_device, &renderpass, &extent, &swapchain_ImageViews, &update_color_image, &update_depth_image]() {
			vk::supp::set_SwapchainFramebuffers(framebuffers, logical_device, renderpass, extent, swapchain_ImageViews, update_color_image(), update_depth_image());
			};
		update_framebuffes();

		constexpr std::size_t VK_COMMANDBUFFERS_N_ELEMS = MAX_IMAGES;
		constexpr std::size_t VK_COMMANDBUFFERS_SIZE = VK_COMMANDBUFFERS_N_ELEMS * (sizeof(vk::raii::CommandBuffer) + alignof(vk::raii::CommandBuffer));
		alignas(alignof(vk::raii::CommandBuffer)) std::array<std::byte, VK_COMMANDBUFFERS_SIZE> VK_COMMANDBUFFERS_BUFFER = {};
		std::pmr::monotonic_buffer_resource VK_COMMANDBUFFERS_RESOURCE(VK_COMMANDBUFFERS_BUFFER.data(), VK_COMMANDBUFFERS_BUFFER.size(), nullptr);
		std::pmr::vector<vk::raii::CommandBuffer> command_buffers(&VK_COMMANDBUFFERS_RESOURCE);
		command_buffers.reserve(VK_COMMANDBUFFERS_N_ELEMS);

		auto alloc_command_buffers = [&logical_device, &command_buffers, &commandpool, n_buffs = swapchain_images.size()]() {
			vk::CommandBufferAllocateInfo allocInfo{};
			allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
			allocInfo.commandPool = *commandpool;
			allocInfo.level = vk::CommandBufferLevel::ePrimary;
			allocInfo.commandBufferCount = n_buffs;
			auto buffs = logical_device.allocateCommandBuffers(allocInfo);
			for (auto& buff : buffs) {
				command_buffers.emplace_back(std::move(buff));
			}
			};
		alloc_command_buffers();

		std::pair<float, float> xz;
		auto key_callback = [xzr = std::ref(xz), wnd = std::ref(window)](glfw::Key key, unsigned scancode, glfw::KeyState key_state, glfw::CharModsFlags mods) {
			auto& [x, z] = xzr.get();
			if (key_state == glfw::KeyState::press) {
				switch (key) {
					case glfw::Key::vW: { z += 1.0f; break; };
					case glfw::Key::vA: { x -= 1.0f; break; };
					case glfw::Key::vS: { z -= 1.0f; break; };
					case glfw::Key::vD: { x += 1.0f; break; };
				}
			}
			if(key_state == glfw::KeyState::release) {
				switch (key) {
					case glfw::Key::vW: { z -= 1.0f; break; };
					case glfw::Key::vA: { x += 1.0f; break; };
					case glfw::Key::vS: { z += 1.0f; break; };
					case glfw::Key::vD: { x -= 1.0f; break; };
					case glfw::Key::vEscape: { wnd.get().close(); break; }; // remove
				}
			}
		};
		window.set_key_callback(std::move(key_callback));

		auto update_position = [lastTime = std::chrono::steady_clock::now()](const std::pair<float, float>& xz) mutable -> std::array<float, 3> {
			auto currentTime = std::chrono::steady_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;

			auto&& [x, z] = xz;
			float dx = x;
			float dy = 0.0f;
			float dz = z;

			float length = std::sqrt(dx * dx + dy * dy + dz * dz);

			if (length > 0.0f) {
				dx /= length;
				dy /= length;
				dz /= length;
			}

			const float speed = 5.0f;
			float factor = speed * deltaTime;
			dx *= factor;
			dy *= factor;
			dz *= factor;

			return { dx, dy, dz };
		};

		auto update_mouse_data = [inital = m_pos, &m_pos]() mutable -> std::pair<float, float> {
			auto& [ix, iy] = inital;
			auto& [cx, cy] = m_pos;

			auto dx = cx - ix;
			auto dy = cy - iy;
			inital = m_pos;

			const float SENSITIVITY = 0.5f;  // deg for px

			auto rx = dx * SENSITIVITY;
			auto ry = dy * SENSITIVITY;

			return { rx, ry };
		};


		using update_f = std::function<void(const vk::raii::CommandBuffer&, const vk::raii::Framebuffer&)>;
		update_f update_commandbuffer = [&renderpass, &camera, &extent, &vkCube_shader, &update_mouse_data, &xz, &update_position, &gs, &sdsh, &skybox](
			const vk::raii::CommandBuffer& command_buffer,
			const vk::raii::Framebuffer& framebuffer
			) {
				camera.update_extent(extent);
				camera.update_angles_by_delta(update_mouse_data());
				auto pos = update_position(xz);
				camera.update_device_buffer(pos[0], pos[1], pos[2]);

				vk::Viewport viewport = {};
				viewport.minDepth = 0.0f;
				viewport.maxDepth = 1.0f;
				viewport.x = 0;
				viewport.y = 0;
				viewport.height = extent.height;
				viewport.width = extent.width;

				vk::Rect2D rect = {};
				rect.offset.x = 0;
				rect.offset.y = 0;
				rect.extent = extent;

				vk::CommandBufferBeginInfo cb_begin_info{};
				command_buffer.begin(cb_begin_info);

				std::array<vk::ClearValue, 2> clear_values{};
				clear_values[0] = vk::ClearColorValue{ 0.0f, 0.0f, 0.0f, 1.0f };
				clear_values[1] = vk::ClearDepthStencilValue{ 1.0f, 0 };
				vk::RenderPassBeginInfo rp_begin_info{ *renderpass, *framebuffer, {{0,0}, extent}, clear_values };
				command_buffer.beginRenderPass(rp_begin_info, vk::SubpassContents::eInline);

				command_buffer.setViewport(0, viewport);
				command_buffer.setScissor(0, rect);

				skybox.setup_command_buffers(command_buffer, camera.get_DescriptorSet());
				vkCube_shader.setup_command_buffers(command_buffer, camera.get_DescriptorSet());
				gs.setup_command_buffers(command_buffer, camera.get_DescriptorSet());
				
				command_buffer.endRenderPass();
				command_buffer.end();
			};

		auto update_swapchain = [&swapchain, &logical_device, &physical_device, &surface, &GaPq, &surface_format, &extent, &present_mode]() {
			auto newSwapchain = vk::supp::get_Swapchain(logical_device, physical_device, surface, GaPq, surface_format.format, extent, present_mode, std::move(swapchain));
			swapchain = std::move(newSwapchain);
			};

		vk::supp::Renderer renderer(logical_device, frames_in_flight, swapchain_ImageViews.size());
		auto render_frame = [&renderer, &logical_device, &swapchain, &graphics_queue, &present_queue, &command_buffers, &framebuffers, &update_commandbuffer]() -> bool {
			return renderer.render_frame(logical_device, swapchain, graphics_queue, present_queue, command_buffers, framebuffers, update_commandbuffer);
		};

		auto update_sync_primitives = [&logical_device, &renderer, &frames_in_flight, &swapchain_ImageViews]() {
			renderer.update_sync_primitives(logical_device, frames_in_flight, swapchain_ImageViews.size());
		};

		auto recreate_swapchain = [
			&update_swapchain,
			&update_swapchain_images,
			&update_image_views,
			&update_framebuffes,
			&update_sync_primitives
		]() {
			update_swapchain();
			update_swapchain_images();
			update_image_views();
			update_framebuffes();
			update_sync_primitives();
		};
		
		auto counter = [lastTime = std::chrono::steady_clock::now(), frameCount = 0u]() mutable {
			frameCount++;
			auto currentTime = std::chrono::steady_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();

			if (elapsed >= 1000) {
				int fps = frameCount * 1000 / elapsed;
				std::cout << "FPS: " << fps << std::endl;
				frameCount = 0;
				lastTime = currentTime;
			}
		};

		while (!called.load(std::memory_order_relaxed)) {
			auto res = render_frame();
			if (!res) {
				logical_device.waitIdle();
				update_extent();
				while (!extent.width || !extent.height) {
					update_extent();
				}
				recreate_swapchain();
			}
			counter();
		}
		logical_device.waitIdle();
		// surface destroyed
	}
	ready.store(true, std::memory_order_relaxed);
}
