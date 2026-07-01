module;

export module vulkan_helpers;
import std;
import vulkan;

namespace {
#if 0
	static vk::PresentModeKHR create_PresentModeKHR(const vk::raii::PhysicalDevice& PhysDevice, const vk::raii::SurfaceKHR& Surface) {
		std::vector<vk::PresentModeKHR> presentModes = PhysDevice.getSurfacePresentModesKHR(Surface);
		unsigned presentModeCount = (unsigned)presentModes.size();
		if (presentModeCount == 0) { throw std::runtime_error("No presentation modes supported"); }
		vk::PresentModeKHR presentMode = vk::PresentModeKHR::eFifo;
		if ((std::find(presentModes.begin(), presentModes.end(), (vk::PresentModeKHR::eFifo))) != presentModes.end()) {
			return presentMode;
		}
		return presentMode;
	}
#endif
}

namespace vk {
	export namespace supp {
		constexpr unsigned myVK_MAKE_VERSION(unsigned major, unsigned minor, unsigned patch) {
			return ((major << 22U) | (minor << 12U) | patch);
		}

		unsigned findMemoryType(
			unsigned typeFilter,
			vk::MemoryPropertyFlags properties,
			const vk::raii::PhysicalDevice& PhysDevice
		) {
			vk::PhysicalDeviceMemoryProperties memProperties = PhysDevice.getMemoryProperties();
			for (unsigned i = 0; i < memProperties.memoryTypeCount; ++i) {
				if ((typeFilter & (1 << i)) && ((memProperties.memoryTypes[i].propertyFlags & properties) == properties)) {
					return i;
				}
			}
			throw std::runtime_error("failed to find suitable memory type!");
		}


		vk::raii::ShaderModule installShader(
			const vk::raii::Device& device,
			std::span<const std::byte> ShaderCode
		) {
			vk::ShaderModuleCreateInfo createInfo{};
			createInfo.sType = vk::StructureType::eShaderModuleCreateInfo;
			createInfo.codeSize = ShaderCode.size();
			createInfo.pCode = reinterpret_cast<const unsigned*>(ShaderCode.data());
			return vk::raii::ShaderModule(device, createInfo);
		}


		std::pair<unsigned, unsigned> get_QueueFamilies(
			const vk::raii::PhysicalDevice& PhysicalDevice,
			const vk::raii::SurfaceKHR& Surface)
		{
			std::pair<unsigned, unsigned> GaP;
			std::vector<vk::QueueFamilyProperties> queueFamilies = PhysicalDevice.getQueueFamilyProperties();

			unsigned i = 0;
			std::vector<unsigned> GraphicQueueFamilyIndices;
			for (const auto& queueFamily : queueFamilies) {
				if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
					GaP.first = i;
					GraphicQueueFamilyIndices.push_back(i);
				}
				++i;
			}

			i = 0;
			std::vector<unsigned> PresentQueueFamilyIndices;
			for (const auto& queueFamily : queueFamilies) {
				if (PhysicalDevice.getSurfaceSupportKHR(i, Surface)) {
					GaP.second = i;
					PresentQueueFamilyIndices.push_back(i);
				}
				++i;
			}

	
			for (const auto& x : PresentQueueFamilyIndices) {
				auto find_same_ixd = [x](const auto& it) {
					if(x == it) { return true; }
					return false;
				};

				auto iter = std::find_if(
					GraphicQueueFamilyIndices.begin(),
					GraphicQueueFamilyIndices.end(),
					find_same_ixd
				);

				if(iter != GraphicQueueFamilyIndices.end()) {
					GaP.first = *iter;
					GaP.second = GaP.first;
					break;
				}
			}

			return GaP;
		}

		vk::raii::Device get_LogicalDevice(
			const vk::raii::PhysicalDevice& PhysicalDevice,
			const std::pair<unsigned, unsigned>& GaP)
		{
			std::set<unsigned> uniqueQueueFamilies = { GaP.first, GaP.second };
			std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;

			const std::vector<const char*> deviceExtensions = {
				// VK_KHR_SWAPCHAIN_EXTENSION_NAME
				"VK_KHR_swapchain"
				// VK_KHR_MAP_MEMORY_2_EXTENSION_NAME
			};

			float queuePriority = 1.0f;
			for (auto queueFamily : uniqueQueueFamilies) {
				vk::DeviceQueueCreateInfo queueCreateInfo{};
				queueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
				queueCreateInfo.flags = vk::DeviceQueueCreateFlags();
				queueCreateInfo.queueFamilyIndex = queueFamily;
				queueCreateInfo.queueCount = 1;
				queueCreateInfo.pQueuePriorities = &queuePriority;
				queueCreateInfos.push_back(queueCreateInfo);
			}

			// note: we are querying no device features
			vk::PhysicalDeviceFeatures deviceFeatures{};

			vk::DeviceCreateInfo createInfo{};
			createInfo.sType = vk::StructureType::eDeviceCreateInfo;
			createInfo.flags = vk::DeviceCreateFlags();
			createInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();
			createInfo.pQueueCreateInfos = queueCreateInfos.data();
			createInfo.pEnabledFeatures = &deviceFeatures;
			createInfo.enabledExtensionCount = (uint32_t)deviceExtensions.size();
			createInfo.ppEnabledExtensionNames = deviceExtensions.data();

			return vk::raii::Device(PhysicalDevice, createInfo);
		}

		vk::raii::CommandPool get_CommandPool(
			const vk::raii::Device& Device,
			const std::pair<unsigned, unsigned>& GaP
		) {
			vk::CommandPoolCreateInfo createInfo{};
			createInfo.sType = vk::StructureType::eCommandPoolCreateInfo;
			createInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
			createInfo.queueFamilyIndex = GaP.first;
			return vk::raii::CommandPool(Device, createInfo);
		}

		vk::SurfaceFormatKHR get_SurfaceFormatKHR(
			const vk::raii::PhysicalDevice& PhysDevice,
			const vk::raii::SurfaceKHR& Surface
		)	{
			vk::SurfaceFormatKHR SurfaceFormat;
			std::vector<vk::SurfaceFormatKHR> formats = PhysDevice.getSurfaceFormatsKHR(Surface);
			unsigned format_count = formats.size();

			SurfaceFormat = formats[0];
			auto lmbd = [](const auto& f) {
				bool fst = (f.format == vk::Format::eR8G8B8A8Srgb);// brga srgb
				bool snd = (f.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear);
				return (fst && snd);
			};
			auto res = std::find_if(formats.begin(), formats.end(), lmbd);

			if (res != formats.end()) {
				SurfaceFormat = *res;
			}

			return SurfaceFormat;
		}

		template <typename T> T myclamp(T x, T low, T hi) {
			if (x > hi) {
				return hi;
			} if (x < low) {
				return low;
			}
			return x;
		}

#if 0
		vk::Extent2D get_Extent2D(
			const vk::raii::PhysicalDevice& PhysDevice,
			const vk::raii::SurfaceKHR& Surface,
			const App_Window& Wnd
		) {
			vk::SurfaceCapabilitiesKHR capabilities = PhysDevice.getSurfaceCapabilitiesKHR(Surface);
			vk::Extent2D Extent;

			FramebufferSize fbs = Wnd.getFramebufferSize();
			unsigned width = fbs.getWidth();
			unsigned height = fbs.getHeight();

			Extent.width = myclamp(width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			Extent.height = myclamp(height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
			dbgs << "Extent: W = " << Extent.width << "; H = " << Extent.height << std::endl;

			return Extent;
		}
#endif
		vk::raii::SwapchainKHR get_Swapchain(
			const vk::raii::Device& Device,
			const vk::raii::PhysicalDevice& PhysDevice,
			const vk::raii::SurfaceKHR& Surface,
			const std::pair<unsigned, unsigned>& GaP,
			const vk::SurfaceFormatKHR& SurfaceFormat,
			const vk::Extent2D& Extent,
			std::optional<vk::raii::SwapchainKHR> oldSwapchain = std::nullopt
			)
		{
			unsigned GraphicsFamily = GaP.first;
			unsigned PresentFamily = GaP.second;

			unsigned queueFamilyIndices[] = { GraphicsFamily, PresentFamily };
			vk::SurfaceCapabilitiesKHR capabilities = PhysDevice.getSurfaceCapabilitiesKHR(Surface);
			vk::PresentModeKHR presentMode = vk::PresentModeKHR::eFifo; // create_PresentModeKHR(PhysDevice, Surface);

			unsigned ImageCount = capabilities.minImageCount;
			if (capabilities.maxImageCount > 0 && ImageCount > capabilities.maxImageCount) {
				ImageCount = capabilities.maxImageCount;
			}

			vk::SwapchainCreateInfoKHR createInfo{};
			createInfo.sType = vk::StructureType::eSwapchainCreateInfoKHR;
			createInfo.flags = vk::SwapchainCreateFlagsKHR();
			createInfo.surface = Surface;
			createInfo.minImageCount = ImageCount;
			createInfo.imageFormat = SurfaceFormat.format;
			createInfo.imageColorSpace = SurfaceFormat.colorSpace;
			createInfo.imageExtent = Extent;
			createInfo.imageArrayLayers = 1;
			createInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;

			if (GraphicsFamily != PresentFamily) {
				createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
				createInfo.queueFamilyIndexCount = 2;
				createInfo.pQueueFamilyIndices = queueFamilyIndices;
			} else {
				createInfo.imageSharingMode = vk::SharingMode::eExclusive;
			}

			createInfo.preTransform = capabilities.currentTransform;
			createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
			createInfo.presentMode = presentMode;
			createInfo.clipped = 1u;
			if (oldSwapchain.has_value()) {
				createInfo.oldSwapchain = oldSwapchain.value();
			}
			return vk::raii::SwapchainKHR(Device, createInfo);
		}

		vk::SampleCountFlagBits getMaxUsableSampleCount(const vk::raii::PhysicalDevice& physical_device) {
			vk::PhysicalDeviceProperties physicalDeviceProperties = physical_device.getProperties();
			vk::SampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts &
				physicalDeviceProperties.limits.framebufferDepthSampleCounts;

			if (counts & vk::SampleCountFlagBits::e64) { return vk::SampleCountFlagBits::e64; }
			if (counts & vk::SampleCountFlagBits::e32) { return vk::SampleCountFlagBits::e32; }
			if (counts & vk::SampleCountFlagBits::e16) { return vk::SampleCountFlagBits::e16; }
			if (counts & vk::SampleCountFlagBits::e8) { return vk::SampleCountFlagBits::e8; }
			if (counts & vk::SampleCountFlagBits::e4) { return vk::SampleCountFlagBits::e4; }
			if (counts & vk::SampleCountFlagBits::e2) { return vk::SampleCountFlagBits::e2; }
			return vk::SampleCountFlagBits::e1;
		}


		vk::raii::RenderPass get_RenderPass(
			const vk::raii::Device& Device,
			const vk::raii::PhysicalDevice& physical_device,
			const vk::Format& SwapchainImageFormat
		) {
			vk::AttachmentDescription colorAttachment{};
			// colorAttachment.sType = vk::StructureType::eAttachmentDescription2;
			colorAttachment.flags = vk::AttachmentDescriptionFlags();
			colorAttachment.format = SwapchainImageFormat;
			colorAttachment.samples = getMaxUsableSampleCount(physical_device);
			colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
			colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
			colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
			// colorAttachment.initialLayout = vk::ImageLayout::ePresentSrcKHR;
			// We want the image to be ready for presentation using the swap chain after rendering
			colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;
			colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
			colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;

			vk::AttachmentDescription depthAttachment{};
			depthAttachment.format = vk::Format::eD32Sfloat;
			depthAttachment.samples = getMaxUsableSampleCount(physical_device);
			depthAttachment.loadOp = vk::AttachmentLoadOp::eClear;
			depthAttachment.storeOp = vk::AttachmentStoreOp::eDontCare;
			depthAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
			depthAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
			depthAttachment.initialLayout = vk::ImageLayout::eUndefined;
			depthAttachment.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;
#if 1
			vk::AttachmentDescription resolveAttachment{};
			resolveAttachment.format = SwapchainImageFormat;
			resolveAttachment.samples = vk::SampleCountFlagBits::e1; // всегда 1
			resolveAttachment.loadOp = vk::AttachmentLoadOp::eDontCare;
			resolveAttachment.storeOp = vk::AttachmentStoreOp::eStore;
			resolveAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
			resolveAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
			resolveAttachment.initialLayout = vk::ImageLayout::eUndefined;
			resolveAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;

			vk::AttachmentReference resolveAttachmentRef{};
			resolveAttachmentRef.attachment = 2;
			resolveAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;
#endif

			vk::AttachmentReference colorAttachmentRef{};
			// colorAttachmentRef.aspectMask = vk::ImageAspectFlagBits::eNone;
			colorAttachmentRef.attachment = 0;
			colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

			vk::AttachmentReference depthAttachmentRef{};
			depthAttachmentRef.attachment = 1;
			depthAttachmentRef.layout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

			vk::SubpassDescription subpass{};
			//subpass.sType = vk::StructureType::eSubpassDescription2;
			subpass.flags = vk::SubpassDescriptionFlags();
			subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
			subpass.colorAttachmentCount = 1;
			subpass.pColorAttachments = &colorAttachmentRef;
			subpass.pDepthStencilAttachment = &depthAttachmentRef;
			subpass.pResolveAttachments = &resolveAttachmentRef;

			constexpr unsigned VK_SUBPASS_EXTERNAL = (~0U); // std::numeric_limits<unsigned>::max();

			vk::SubpassDependency dependency{};
			//dependency.sType = vk::StructureType::eSubpassDependency2;
			dependency.dependencyFlags = vk::DependencyFlags();
			dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
			dependency.dstSubpass = 0u;
			dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
			dependency.srcAccessMask = vk::AccessFlagBits::eNone;
			dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput | vk::PipelineStageFlagBits::eEarlyFragmentTests;
			dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eDepthStencilAttachmentWrite;

			vk::SubpassDependency presentDependency{};
			presentDependency.srcSubpass = 0;
			presentDependency.dstSubpass = VK_SUBPASS_EXTERNAL;
			presentDependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
			presentDependency.srcAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
			presentDependency.dstStageMask = vk::PipelineStageFlagBits::eBottomOfPipe;
			presentDependency.dstAccessMask = vk::AccessFlagBits::eMemoryRead;


			std::array<vk::AttachmentDescription, 3> attachments = { colorAttachment, depthAttachment, resolveAttachment };
			std::array<vk::SubpassDependency, 2> dependencies = { dependency, presentDependency };
			std::array<vk::SubpassDescription, 1> subpasses = { subpass };
#if 1
			vk::RenderPassCreateInfo createInfo{};
			// createInfo.sType = vk::StructureType::eRenderPassCreateInfo;
			createInfo.sType = vk::StructureType::eRenderPassCreateInfo;
			createInfo.flags = vk::RenderPassCreateFlags();
			createInfo.pNext = nullptr;
			createInfo.attachmentCount = attachments.size();
			createInfo.pAttachments = attachments.data();
			createInfo.subpassCount = subpasses.size();
			createInfo.pSubpasses = subpasses.data();
			createInfo.dependencyCount = dependencies.size();
			createInfo.pDependencies = dependencies.data();
			// createInfo.correlatedViewMaskCount = 0;
			// createInfo.pCorrelatedViewMasks = 0;
#else
			vk::AttachmentDescription colorAttachments[] = { colorAttachment };
			vk::SubpassDescription subpasses[] = { subpass };
			vk::SubpassDependency subpassesDependencies = { dependency };
			vk::RenderPassCreateInfo createInfo(
				vk::RenderPassCreateFlags(),
				colorAttachments,
				subpasses,
				subpassesDependencies
			);
#endif
			return vk::raii::RenderPass(Device, createInfo);
		}

		vk::raii::Buffer create_Buffer(
			const vk::raii::Device& Device,
			const vk::DeviceSize& bufferSize,
			const vk::BufferUsageFlags usage
		) {
			vk::BufferCreateInfo bufferInfo{};
			bufferInfo.sType = vk::StructureType::eBufferCreateInfo;
			bufferInfo.flags = vk::BufferCreateFlags();
			bufferInfo.size = bufferSize;
			bufferInfo.usage = usage;
			bufferInfo.sharingMode = vk::SharingMode::eExclusive;

			return vk::raii::Buffer(Device, bufferInfo);
		}

		vk::raii::DeviceMemory create_BufferMemory(
			const vk::raii::Device& Device,
			const vk::raii::PhysicalDevice& PhysDevice,
			vk::raii::Buffer&& Buffer,
			const vk::MemoryPropertyFlags properties
		) {
			vk::MemoryRequirements memRequirements = Buffer.getMemoryRequirements();

			vk::MemoryAllocateInfo allocInfo{};
			allocInfo.sType = vk::StructureType::eMemoryAllocateInfo;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties, PhysDevice);

			vk::raii::DeviceMemory bufferMemory = Device.allocateMemory(allocInfo);

			vk::BindBufferMemoryInfo bindBufferMemoryInfo{};
			bindBufferMemoryInfo.sType = vk::StructureType::eBindBufferMemoryInfo;
			bindBufferMemoryInfo.buffer = Buffer;
			bindBufferMemoryInfo.memory = bufferMemory;
			bindBufferMemoryInfo.memoryOffset = 0;

			Device.bindBufferMemory2(bindBufferMemoryInfo);
			return bufferMemory;
		}

		void set_ImageViews(
			const vk::raii::Device& Device,
			const vk::Format& SwapchainImageFormat,
			const std::vector<vk::Image>& SwapchainImages,
			std::vector<vk::raii::ImageView>& SwapchainImageViews
		) {
			SwapchainImageViews.clear();
			unsigned ImageCount = (unsigned)SwapchainImages.size();
			for (size_t i = 0; i < ImageCount; ++i) {
				vk::ImageViewCreateInfo createInfo(
					vk::ImageViewCreateFlags{},
					SwapchainImages[i],
					vk::ImageViewType::e2D,
					SwapchainImageFormat,
					{ // vk::ComponentMapping
						vk::ComponentSwizzle::eIdentity, // r
						vk::ComponentSwizzle::eIdentity, // g
						vk::ComponentSwizzle::eIdentity, // b
						vk::ComponentSwizzle::eIdentity  // a
					},
					{ // vk::ImageSubresourceRange
						vk::ImageAspectFlagBits::eColor, // aspectMask
						0, // baseMipLevel
						1, // levelCount
						0, // baseArrayLayer
						1  // layerCount
					},
					nullptr // pNext
				);
				SwapchainImageViews.emplace_back(Device, createInfo);
			}
		}

		void set_SwapchainFramebuffers(
			std::vector<vk::raii::Framebuffer>& SwapchainFramebuffers,
			const vk::raii::Device& Device,
			const vk::raii::RenderPass& RenderPass,
			const vk::Extent2D& SwapchainExtent,
			const std::vector<vk::raii::ImageView>& SwapchainImageViews,
			const vk::raii::ImageView& ColorImageViews,
			const vk::raii::ImageView& DepthImageView
		) {
			SwapchainFramebuffers.clear();
			unsigned nFrameBuffers = (unsigned)SwapchainImageViews.size();
			for (size_t i = 0; i < nFrameBuffers; i++) {
				vk::ImageView iv[] = { ColorImageViews, DepthImageView, SwapchainImageViews[i] };
				vk::FramebufferCreateFlags cf{ 0u };
				// vk::FramebufferCreateFlags cf = { vk::FramebufferCreateFlagBits::eImagelessKHR };
				vk::FramebufferCreateInfo framebufferInfo(
					cf, // create flags
					RenderPass, // RenderPass
					iv, // ImageView
					SwapchainExtent.width, // width
					SwapchainExtent.height, // height
					1 // n_layers
				);
				SwapchainFramebuffers.emplace_back(Device, framebufferInfo);
			}
		}
#if 0
		using command_buffer_update_f = std::function<void(const std::vector<vk::raii::CommandBuffer>&)>;
		using command_buffer_data = std::pair<unsigned, command_buffer_update_f>;

		void set_CommandBuffers(
			std::vector<vk::raii::CommandBuffer>& commandBuffers,
			const std::vector<vk::raii::Framebuffer>& framebuffers,
			const vk::raii::CommandPool& CommandPool,
			const vk::raii::Device& Device,
			const vk::raii::RenderPass& RenderPass,
			const vk::Viewport viewport,
			const std::vector<>
		) {
			commandBuffers.clear();
			unsigned NFrameBufs = (unsigned)framebuffers.size();

			vk::CommandBufferAllocateInfo allocInfo{};
			allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
			allocInfo.commandPool = CommandPool;
			allocInfo.level = vk::CommandBufferLevel::ePrimary;
			allocInfo.commandBufferCount = NFrameBufs;

			commandBuffers = Device.allocateCommandBuffers(allocInfo);

			for (auto&& x : ) {
				x.f(commandBuffers, framebuffers, RenderPass, viewport, x.data);
			}
		}
#endif
		struct Renderer {
			private:
				unsigned FramesInFlight;
				unsigned CurrentFrame = 0;
				std::vector<vk::raii::Fence> InFlightFences;
				std::vector<vk::raii::Fence> ImagesInFlight;
				std::vector<vk::raii::Semaphore> ImageAvailableSemaphores;
				std::vector<vk::raii::Semaphore> RenderFinishedSemaphores;

				static std::vector<vk::raii::Semaphore> get_Semaphores(const vk::raii::Device& device, unsigned n) {
					std::vector<vk::raii::Semaphore> semaphores;
					semaphores.reserve(n);
					vk::SemaphoreCreateInfo screateinfo = {};
					auto create_semaphore = [&device, &screateinfo]() { return vk::raii::Semaphore(device, screateinfo); };
					std::generate_n(std::back_inserter(semaphores), n, create_semaphore);
					return semaphores;
				}

				static std::vector<vk::raii::Fence> get_Fences(const vk::raii::Device& device, unsigned n) {
					std::vector<vk::raii::Fence> fences;
					fences.reserve(n);
					auto create_fence = [&device]() { return vk::raii::Fence(device, vk::FenceCreateInfo(vk::FenceCreateFlagBits::eSignaled)); };
					std::generate_n(std::back_inserter(fences), n, create_fence);
					return fences;
				}

			public:
				Renderer(const vk::raii::Device& device, unsigned fif, unsigned n_images)
					: FramesInFlight(fif)
					, InFlightFences(get_Fences(device, fif))
					, ImagesInFlight(get_Fences(device, n_images))
					, ImageAvailableSemaphores(get_Semaphores(device, n_images))
					, RenderFinishedSemaphores(get_Semaphores(device, n_images))
				{
				
				}

			public:
				bool render_frame(
					const vk::raii::Device& device,
					const vk::raii::SwapchainKHR& swapchain,
					const vk::raii::Queue& graphics_queue,
					const vk::raii::Queue& present_queue,
					const std::vector<vk::raii::CommandBuffer>& command_buffers,
					const std::vector<vk::raii::Framebuffer>& framebuffers,
					const std::function<void(const vk::raii::CommandBuffer&, const vk::raii::Framebuffer&)>& update_command_buffer
				) {
					constexpr unsigned timeout_U = std::numeric_limits<std::uint64_t>::max();
					std::ignore = device.waitForFences(*InFlightFences[CurrentFrame], 1u, timeout_U);

					vk::AcquireNextImageInfoKHR acquireInfo(
						swapchain,
						timeout_U,
						*ImageAvailableSemaphores[CurrentFrame],
						nullptr, 
						0x1, // dev_mask
						nullptr // pnext
					);

					vk::ResultValue<uint32_t> ret = device.acquireNextImage2KHR(acquireInfo);
					vk::Result result(ret.result);
					unsigned imageIndex = ret.value;

					if (result == vk::Result::eErrorOutOfDateKHR) {
						return false;
					}	else if ((result != vk::Result::eSuccess) && (result != vk::Result::eSuboptimalKHR)) {
						throw std::runtime_error("failed to acquire swap chain image!");
					}

					if (ImagesInFlight[imageIndex].getStatus() == vk::Result::eNotReady) {
						std::ignore = device.waitForFences(*ImagesInFlight[imageIndex], 1u, timeout_U);
					}

					command_buffers[CurrentFrame].reset(); //vk::CommandBufferResetFlagBits::eReleaseResources);
					update_command_buffer(command_buffers[CurrentFrame], framebuffers[CurrentFrame]);

					std::array<vk::PipelineStageFlags, 1> waitStages = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
					std::array<vk::Semaphore, 1> waitSemaphores = { *ImageAvailableSemaphores[CurrentFrame] };
					std::array<vk::Semaphore, 1> signalSemaphores = { *RenderFinishedSemaphores[CurrentFrame] };
					std::array<vk::CommandBuffer, 1> commandBuffers = { *command_buffers[CurrentFrame] };

					vk::SubmitInfo submitInfo(
						waitSemaphores,
						waitStages,
						commandBuffers,
						signalSemaphores
					);

					device.resetFences(*InFlightFences[CurrentFrame]);

					vk::SubmitInfo submits[] = { submitInfo };
					graphics_queue.submit(submits, InFlightFences[CurrentFrame]);

					std::array<vk::SwapchainKHR, 1> sa = { *swapchain };
					std::array<vk::Result, 1> result_present_info = { vk::Result::eSuccess };
					uint32_t image_indices[] = { imageIndex };
					vk::PresentInfoKHR presentInfo(
						signalSemaphores,
						sa,
						image_indices,
						result_present_info,
						nullptr
					);
					result = present_queue.presentKHR(presentInfo);

					if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR) {
						return false;
					}	else if (result != vk::Result::eSuccess) {
						throw std::runtime_error("failed to present swap chain image!");
					}

					CurrentFrame = (CurrentFrame + 1) % (FramesInFlight);
					return true;
				}
		};
	}
}