module;

export module vulkan_helpers;
import std;
import vulkan;

namespace vk {
	export namespace supp {
		constexpr unsigned myVK_MAKE_VERSION(unsigned major, unsigned minor, unsigned patch) {
			return ((major << 22U) | (minor << 12U) | patch);
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
			createInfo.flags = vk::CommandPoolCreateFlags();
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
		vk::raii::RenderPass get_RenderPass(
			const vk::raii::Device& Device,
			const vk::Format& SwapchainImageFormat
		) {
			vk::AttachmentDescription colorAttachment{};
			// colorAttachment.sType = vk::StructureType::eAttachmentDescription2;
			colorAttachment.flags = vk::AttachmentDescriptionFlags();
			colorAttachment.format = SwapchainImageFormat;
			colorAttachment.samples = vk::SampleCountFlagBits::e1;
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
			depthAttachment.samples = vk::SampleCountFlagBits::e1;
			depthAttachment.loadOp = vk::AttachmentLoadOp::eClear;
			depthAttachment.storeOp = vk::AttachmentStoreOp::eDontCare;
			depthAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
			depthAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
			depthAttachment.initialLayout = vk::ImageLayout::eUndefined;
			depthAttachment.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

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

			std::array<vk::AttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };
#if 1
			vk::RenderPassCreateInfo createInfo{};
			// createInfo.sType = vk::StructureType::eRenderPassCreateInfo;
			createInfo.sType = vk::StructureType::eRenderPassCreateInfo;
			createInfo.flags = vk::RenderPassCreateFlags();
			createInfo.pNext = nullptr;
			createInfo.attachmentCount = static_cast<unsigned>(attachments.size());
			createInfo.pAttachments = attachments.data();
			createInfo.subpassCount = 1;
			createInfo.pSubpasses = &subpass;
			createInfo.dependencyCount = 1;
			createInfo.pDependencies = &dependency;
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

	}
}