module;

export module skybox_shader;
import vulkan;
import vulkan_helpers;
import shaders_compiler;
import vk_shader_iface;
import stb_image;
import CubeMapData;
import glm;

namespace {
	constexpr std::string_view vert(
		R"(
			#version 450 core

			layout(set = 0, binding = 0) uniform Matrices {
				mat4 view;
				mat4 proj;
				vec3 world_position;
			} CameraUBO;

			layout(location = 0) in vec3 in_position;
			layout(location = 0) out vec3 outUVW;

			void main() {
				mat4 viewNoTranslation = mat4(mat3(CameraUBO.view));
				vec4 pos = CameraUBO.proj * viewNoTranslation * vec4(in_position, 1.0);
				gl_Position = pos.xyww;
				outUVW = in_position;
			}
		)"
	);

	constexpr std::string_view frag(
		R"(
			#version 450 core

			layout(location = 0) out vec4 f_color;
			layout(set = 1, binding = 0) uniform samplerCube skyboxSampler;
			layout(location = 0) in vec3 outUVW;

			void main() {
				vec3 outUVW_my = vec3(outUVW.x, -outUVW.y, outUVW.z);
				f_color = texture(skyboxSampler, outUVW_my);
			}
		)"
	);

	constexpr std::array<glm::vec3, 8> vertices = {
		 glm::vec3{ -1.0f, -1.0f, -1.0f }, glm::vec3{ 1.0f, -1.0f, -1.0f }, glm::vec3{ 1.0f, 1.0f, -1.0f }, glm::vec3{ -1.0f, 1.0f, -1.0f },
		 glm::vec3{ -1.0f, -1.0f,  1.0f }, glm::vec3{ 1.0f, -1.0f,  1.0f }, glm::vec3{ 1.0f, 1.0f,  1.0f }, glm::vec3{ -1.0f, 1.0f,  1.0f }
	};

	constexpr std::array<unsigned short, 36> indices = {
			0,1,2, 2,3,0,
			1,5,6, 6,2,1,
			5,4,7, 7,6,5,
			4,0,3, 3,7,4,
			3,2,6, 6,7,3,
			4,5,1, 1,0,4
	};

	vk::raii::DescriptorSetLayout get_Sampler_DescriptorSetLayout(const vk::raii::Device& device) {
		vk::DescriptorSetLayoutBinding skyboxBinding{};
		skyboxBinding.binding = 0;
		skyboxBinding.descriptorType = vk::DescriptorType::eCombinedImageSampler;
		skyboxBinding.descriptorCount = 1;
		skyboxBinding.stageFlags = vk::ShaderStageFlagBits::eFragment;

		vk::DescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.bindingCount = 1;
		layoutInfo.pBindings = &skyboxBinding;

		return vk::raii::DescriptorSetLayout(device, layoutInfo);
	}

	vk::raii::DescriptorPool get_Sampler_DescriptorPool(const vk::raii::Device& device) {

		vk::DescriptorPoolSize poolSize{};
		poolSize.type = vk::DescriptorType::eCombinedImageSampler;
		poolSize.descriptorCount = 1;

		vk::DescriptorPoolCreateInfo poolInfo{};
		poolInfo.poolSizeCount = 1;
		poolInfo.pPoolSizes = &poolSize;
		poolInfo.maxSets = 1;
		poolInfo.flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet;

		return vk::raii::DescriptorPool(device, poolInfo);
	}

	vk::raii::DescriptorSet get_Sampler_DescriptorSet(
		const vk::raii::Device& device,
		const vk::raii::DescriptorPool& descriptorPool,
		const vk::raii::DescriptorSetLayout& skyboxDescriptorSetLayout
	) {
		vk::DescriptorSetAllocateInfo allocInfo{};
		allocInfo.descriptorPool = *descriptorPool;
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &*skyboxDescriptorSetLayout;

		return std::move(device.allocateDescriptorSets(allocInfo)[0]);
	}

	vk::raii::Sampler get_Sampler(const vk::raii::Device& device) {
		vk::SamplerCreateInfo samplerInfo{};
		samplerInfo.magFilter = vk::Filter::eLinear;
		samplerInfo.minFilter = vk::Filter::eLinear;
		samplerInfo.addressModeU = vk::SamplerAddressMode::eClampToEdge;
		samplerInfo.addressModeV = vk::SamplerAddressMode::eClampToEdge;
		samplerInfo.addressModeW = vk::SamplerAddressMode::eClampToEdge;
		samplerInfo.anisotropyEnable = false;
		samplerInfo.compareEnable = false;
		samplerInfo.mipmapMode = vk::SamplerMipmapMode::eLinear;
		samplerInfo.mipLodBias = 0.0f;
		samplerInfo.minLod = 0.0f;
		constexpr float VK_LOD_CLAMP_NONE = 1000.0F;
		samplerInfo.maxLod = VK_LOD_CLAMP_NONE;

		return vk::raii::Sampler(device, samplerInfo);
	}

	vk::raii::Image get_Sampler_Image(
		unsigned height, unsigned width,
		const vk::raii::Device& device
	) {
		vk::ImageCreateInfo imageInfo{};
		imageInfo.flags = vk::ImageCreateFlagBits::eCubeCompatible;
		imageInfo.imageType = vk::ImageType::e2D;
		imageInfo.extent.width = 1024;
		imageInfo.extent.height = 1024;
		imageInfo.extent.depth = 1;
		imageInfo.mipLevels = 1;
		imageInfo.arrayLayers = 6;
		imageInfo.format = vk::Format::eR8G8B8A8Srgb;
		imageInfo.tiling = vk::ImageTiling::eOptimal;
		imageInfo.initialLayout = vk::ImageLayout::eUndefined;
		imageInfo.usage = vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled;
		imageInfo.samples = vk::SampleCountFlagBits::e1;
		imageInfo.sharingMode = vk::SharingMode::eExclusive;

		return vk::raii::Image(device, imageInfo);
	}

	vk::raii::DeviceMemory get_Sampler_Image_DeviceMemory(
		const vk::raii::Device& device,
		const vk::raii::PhysicalDevice& physicalDevice,
		const vk::raii::Image& image
	) {
		auto memReqs = image.getMemoryRequirements();
		vk::MemoryAllocateInfo allocInfo{};
		allocInfo.allocationSize = memReqs.size;
		allocInfo.memoryTypeIndex = vk::supp::findMemoryType(
			memReqs.memoryTypeBits,
			vk::MemoryPropertyFlagBits::eDeviceLocal,
			physicalDevice
		);
		auto mem = vk::raii::DeviceMemory(device, allocInfo);
		image.bindMemory(*mem, 0);
		return mem;
	}

	void CopyToImg(
		const vk::raii::Device& device,
		const vk::raii::PhysicalDevice& physicalDevice,
		const vk::raii::CommandPool& commandPool,
		const vk::raii::Image& image,
		const vk::raii::Queue& graphicsQueue
	) {
		auto img_fix = [](stb_image::RawPic& r) {
			if (r.channels == 3) {
				auto n_c = r.width * r.height;
				decltype(r.data) new_data(n_c * 4);
				for (int i = 0; i < n_c; ++i) {
					new_data[i * 4 + 0] = r.data[i * 3 + 0];
					new_data[i * 4 + 1] = r.data[i * 3 + 1];
					new_data[i * 4 + 2] = r.data[i * 3 + 2];
					new_data[i * 4 + 3] = 255;
				}
				r.channels = 4;
				r.data = new_data;
			}
		};

		auto eimg = stb_image::load_image_from_memory(CubeMapData::Epng);
		if (eimg.height != eimg.width) { throw; }
		img_fix(eimg);
		auto wimg = stb_image::load_image_from_memory(CubeMapData::Wpng);
		if (wimg.height != wimg.width) { throw; }
		img_fix(wimg);
		auto timg = stb_image::load_image_from_memory(CubeMapData::Tpng);
		if (timg.height != timg.width) { throw; }
		img_fix(timg);
		auto bimg = stb_image::load_image_from_memory(CubeMapData::Bpng);
		if (bimg.height != bimg.width) { throw; }
		img_fix(bimg);
		auto simg = stb_image::load_image_from_memory(CubeMapData::Spng);
		if (simg.height != simg.width) { throw; }
		img_fix(simg);
		auto nimg = stb_image::load_image_from_memory(CubeMapData::Npng);
		if (nimg.height != nimg.width) { throw; }
		img_fix(nimg);

		auto total_size
			= eimg.data.size()
			+ wimg.data.size()
			+ timg.data.size()
			+ bimg.data.size()
			+ simg.data.size()
			+ nimg.data.size();

		auto test = total_size / 6;
		if (
				 test != eimg.data.size()
			|| test != wimg.data.size()
			|| test != timg.data.size()
			|| test != bimg.data.size()
			|| test != nimg.data.size()
			|| test != simg.data.size()
			) {
			throw std::runtime_error("All faces must have the same dimensions");
		}

		vk::BufferCreateInfo stagingInfo{};
		stagingInfo.size = total_size;
		stagingInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
		stagingInfo.sharingMode = vk::SharingMode::eExclusive;

		auto stagingBuffer = vk::raii::Buffer(device, stagingInfo);
		auto memReqs = stagingBuffer.getMemoryRequirements();
		vk::MemoryAllocateInfo allocInfo{};
		allocInfo.allocationSize = memReqs.size;
		allocInfo.memoryTypeIndex = vk::supp::findMemoryType(
			memReqs.memoryTypeBits,
			vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
			physicalDevice
		);
		auto stagingMemory = vk::raii::DeviceMemory(device, allocInfo);
		stagingBuffer.bindMemory(*stagingMemory, 0);

		auto data = std::span<unsigned char>(reinterpret_cast<unsigned char *>(stagingMemory.mapMemory(0, total_size)), total_size);
		auto data_iter = data.begin();
		data_iter = std::copy(eimg.data.begin(), eimg.data.end(), data_iter);
		data_iter = std::copy(wimg.data.begin(), wimg.data.end(), data_iter);
		data_iter = std::copy(timg.data.begin(), timg.data.end(), data_iter);
		data_iter = std::copy(bimg.data.begin(), bimg.data.end(), data_iter);
		data_iter = std::copy(simg.data.begin(), simg.data.end(), data_iter);
		data_iter = std::copy(nimg.data.begin(), nimg.data.end(), data_iter);
		stagingMemory.unmapMemory();

		vk::CommandBufferAllocateInfo cmdAlloc(*commandPool, vk::CommandBufferLevel::ePrimary, 1);
		auto cmdBuf = std::move(device.allocateCommandBuffers(cmdAlloc)[0]);
		cmdBuf.begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit));

		vk::ImageMemoryBarrier barrier{};
		barrier.image = *image;
		barrier.oldLayout = vk::ImageLayout::eUndefined;
		barrier.newLayout = vk::ImageLayout::eTransferDstOptimal;
		barrier.srcAccessMask = vk::AccessFlagBits::eNone;
		barrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;
		barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
		barrier.subresourceRange.baseMipLevel = 0;
		barrier.subresourceRange.levelCount = 1;
		barrier.subresourceRange.baseArrayLayer = 0;
		barrier.subresourceRange.layerCount = 6;
		cmdBuf.pipelineBarrier(
			vk::PipelineStageFlagBits::eTopOfPipe,
			vk::PipelineStageFlagBits::eTransfer,
			vk::DependencyFlags(),
			nullptr, nullptr, barrier
		);

		vk::BufferImageCopy regionE{};
		regionE.bufferOffset = 0;
		regionE.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
		regionE.imageSubresource.mipLevel = 0;
		regionE.imageSubresource.baseArrayLayer = 0;
		regionE.imageSubresource.layerCount = 1;
		regionE.imageExtent.width = eimg.width;
		regionE.imageExtent.height = eimg.height;
		regionE.imageExtent.depth = 1;
		cmdBuf.copyBufferToImage(*stagingBuffer, *image, vk::ImageLayout::eTransferDstOptimal, regionE);

		vk::BufferImageCopy regionW{};
		regionW.bufferOffset = eimg.data.size();
		regionW.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
		regionW.imageSubresource.mipLevel = 0;
		regionW.imageSubresource.baseArrayLayer = 1;
		regionW.imageSubresource.layerCount = 1;
		regionW.imageExtent.width = wimg.width;
		regionW.imageExtent.height = wimg.height;
		regionW.imageExtent.depth = 1;
		cmdBuf.copyBufferToImage(*stagingBuffer, *image, vk::ImageLayout::eTransferDstOptimal, regionW);

		vk::BufferImageCopy regionT{};
		regionT.bufferOffset = eimg.data.size() + wimg.data.size();
		regionT.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
		regionT.imageSubresource.mipLevel = 0;
		regionT.imageSubresource.baseArrayLayer = 2;
		regionT.imageSubresource.layerCount = 1;
		regionT.imageExtent.width = timg.width;
		regionT.imageExtent.height = timg.height;
		regionT.imageExtent.depth = 1;
		cmdBuf.copyBufferToImage(*stagingBuffer, *image, vk::ImageLayout::eTransferDstOptimal, regionT);

		vk::BufferImageCopy regionB{};
		regionB.bufferOffset = eimg.data.size() + wimg.data.size() + timg.data.size();
		regionB.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
		regionB.imageSubresource.mipLevel = 0;
		regionB.imageSubresource.baseArrayLayer = 3;
		regionB.imageSubresource.layerCount = 1;
		regionB.imageExtent.width = bimg.width;
		regionB.imageExtent.height = bimg.height;
		regionB.imageExtent.depth = 1;
		cmdBuf.copyBufferToImage(*stagingBuffer, *image, vk::ImageLayout::eTransferDstOptimal, regionB);

		vk::BufferImageCopy regionS{};
		regionS.bufferOffset = eimg.data.size() + wimg.data.size() + timg.data.size() + bimg.data.size();
		regionS.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
		regionS.imageSubresource.mipLevel = 0;
		regionS.imageSubresource.baseArrayLayer = 4;
		regionS.imageSubresource.layerCount = 1;
		regionS.imageExtent.width = simg.width;
		regionS.imageExtent.height = simg.height;
		regionS.imageExtent.depth = 1;
		cmdBuf.copyBufferToImage(*stagingBuffer, *image, vk::ImageLayout::eTransferDstOptimal, regionS);

		vk::BufferImageCopy regionN{};
		regionN.bufferOffset = eimg.data.size() + wimg.data.size() + timg.data.size() + bimg.data.size() + simg.data.size();
		regionN.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
		regionN.imageSubresource.mipLevel = 0;
		regionN.imageSubresource.baseArrayLayer = 5;
		regionN.imageSubresource.layerCount = 1;
		regionN.imageExtent.width = nimg.width;
		regionN.imageExtent.height = nimg.height;
		regionN.imageExtent.depth = 1;
		cmdBuf.copyBufferToImage(*stagingBuffer, *image, vk::ImageLayout::eTransferDstOptimal, regionN);

		barrier.oldLayout = vk::ImageLayout::eTransferDstOptimal;
		barrier.newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
		barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;
		cmdBuf.pipelineBarrier(
			vk::PipelineStageFlagBits::eTransfer,
			vk::PipelineStageFlagBits::eFragmentShader,
			vk::DependencyFlags(),
			nullptr, nullptr, barrier
		);

		cmdBuf.end();
		vk::SubmitInfo submit{};
		submit.commandBufferCount = 1;
		submit.pCommandBuffers = &*cmdBuf;
		graphicsQueue.submit(submit, nullptr);
		graphicsQueue.waitIdle();
	}

	vk::raii::ImageView get_Sampler_ImageView(
		const vk::raii::Device& device,
		const vk::raii::Image& skyboxImage
	) {
		vk::ImageViewCreateInfo viewInfo{};
		viewInfo.image = *skyboxImage;
		viewInfo.viewType = vk::ImageViewType::eCube;
		viewInfo.format = vk::Format::eR8G8B8A8Srgb; // ваш формат
		viewInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 6; // все 6 граней

		return vk::raii::ImageView(device, viewInfo);
	}

	struct SkyboxSampler {
		private:
			vk::raii::Sampler sampler;
			vk::raii::Image image;
			vk::raii::DeviceMemory image_memory;
			vk::raii::ImageView image_view;
			vk::raii::DescriptorSetLayout desc_set_layout;
			vk::raii::DescriptorPool desc_pool;
			vk::raii::DescriptorSet desc_set;

		public:
			SkyboxSampler(
				const vk::raii::Device& device,
				const vk::raii::PhysicalDevice& physicalDevice,
				const vk::raii::CommandPool& commandPool,
				const vk::raii::Queue& graphicsQueue
			)
				: sampler(get_Sampler(device))
				, image(get_Sampler_Image(1024, 1024, device))
				, image_memory(get_Sampler_Image_DeviceMemory(device, physicalDevice, image))
				, image_view(get_Sampler_ImageView(device, image))
				, desc_set_layout(get_Sampler_DescriptorSetLayout(device))
				, desc_pool(get_Sampler_DescriptorPool(device))
				, desc_set(get_Sampler_DescriptorSet(device, desc_pool, desc_set_layout))
			{
			
				CopyToImg(device, physicalDevice, commandPool, image, graphicsQueue);

				vk::DescriptorImageInfo imageInfo{};
				imageInfo.sampler = *sampler;
				imageInfo.imageView = *image_view;
				imageInfo.imageLayout = vk::ImageLayout::eShaderReadOnlyOptimal;

				vk::WriteDescriptorSet write{};
				write.dstSet = *desc_set;
				write.dstBinding = 0;
				write.dstArrayElement = 0;
				write.descriptorType = vk::DescriptorType::eCombinedImageSampler;
				write.descriptorCount = 1;
				write.pImageInfo = &imageInfo;

				device.updateDescriptorSets(write, nullptr);
			}

		public:
			const vk::raii::DescriptorSetLayout& get_DescriptorSetLayout() const { return desc_set_layout; }
			const vk::raii::DescriptorSet& get_DescriptorSet() const { return desc_set; }
	
	};

	auto frag_v = shaders_compiler::compile_shader(frag, shaders_compiler::shaderc_shader_kind::shaderc_glsl_fragment_shader);
	auto vert_v = shaders_compiler::compile_shader(vert, shaders_compiler::shaderc_shader_kind::shaderc_glsl_vertex_shader);

	vk::raii::PipelineLayout get_PipelineLayout(
		const vk::raii::Device& Device,
		const vk::raii::DescriptorSetLayout& camera_descLayout,
		const vk::raii::DescriptorSetLayout& sampler_descLayout
	) {
		vk::PipelineLayoutCreateFlagBits flags{};
		std::array<vk::DescriptorSetLayout, 2> desc_lay = { camera_descLayout, sampler_descLayout };
		vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo(flags, desc_lay, {}, nullptr);
		return vk::raii::PipelineLayout(Device, pipelineLayoutCreateInfo);
	}

	vk::raii::PipelineCache get_PipelineCache(const vk::raii::Device& Device) {
		vk::PipelineCacheCreateInfo createInfo{};
		createInfo.flags;
		createInfo.initialDataSize;
		createInfo.pInitialData;
		createInfo.pNext;
		return vk::raii::PipelineCache(Device, createInfo);
	}

	vk::raii::Pipeline get_Pipeline(
		const vk::raii::Device& Device,
		const vk::raii::PhysicalDevice& physical_device,
		const vk::raii::RenderPass& RenderPass,
		const vk::Extent2D& Extent,
		const vk::raii::ShaderModule& VertexShaderModule,
		const vk::raii::ShaderModule& FragmentShaderModule,
		const vk::raii::PipelineLayout& pipelineLayout,
		const vk::raii::PipelineCache& pipelineCache
	) {
		vk::PipelineShaderStageCreateInfo vertShaderStageInfo(
			vk::PipelineShaderStageCreateFlags(),
			vk::ShaderStageFlagBits::eVertex,
			VertexShaderModule,
			"main",
			nullptr,
			nullptr
		);

		vk::PipelineShaderStageCreateInfo fragShaderStageInfo(
			vk::PipelineShaderStageCreateFlags(),
			vk::ShaderStageFlagBits::eFragment,
			FragmentShaderModule,
			"main",
			nullptr,
			nullptr
		);

		std::array<vk::PipelineShaderStageCreateInfo, 2> shaderStages = { vertShaderStageInfo, fragShaderStageInfo };

		std::array<vk::VertexInputBindingDescription, 1> bindingDescription;
		bindingDescription[0].binding = 0;
		bindingDescription[0].stride = 3 * sizeof(float);
		bindingDescription[0].inputRate = vk::VertexInputRate::eVertex;

		std::array<vk::VertexInputAttributeDescription, 1> attributeDescriptions;
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = vk::Format::eR32G32B32Sfloat;
		attributeDescriptions[0].offset = 0;

		vk::PipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = vk::StructureType::ePipelineVertexInputStateCreateInfo;
		vertexInputInfo.flags = vk::PipelineVertexInputStateCreateFlags();
		vertexInputInfo.vertexBindingDescriptionCount = (unsigned)bindingDescription.size();
		vertexInputInfo.vertexAttributeDescriptionCount = (unsigned)attributeDescriptions.size();
		vertexInputInfo.pVertexBindingDescriptions = bindingDescription.data();
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

		vk::PipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = vk::StructureType::ePipelineInputAssemblyStateCreateInfo;
		inputAssembly.flags = vk::PipelineInputAssemblyStateCreateFlags();
		inputAssembly.topology = vk::PrimitiveTopology::eTriangleList;
		inputAssembly.primitiveRestartEnable = 0;

		vk::Viewport viewport{};
		viewport.x = 0.0f; // 
		viewport.y = 0.0f; // left botom corner in px(float)
		viewport.width = Extent.width; // 
		viewport.height = Extent.height; // resolution 
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		unsigned x = 0;
		unsigned y = 0;
		vk::Offset2D offset(x, y);

		vk::Rect2D scissor{};
		scissor.offset = offset;
		scissor.extent = Extent;

		vk::PipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = vk::StructureType::ePipelineViewportStateCreateInfo;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		vk::PipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = vk::StructureType::ePipelineRasterizationStateCreateInfo;
		rasterizer.depthClampEnable = 0;
		rasterizer.rasterizerDiscardEnable = 0;
		rasterizer.polygonMode = vk::PolygonMode::eFill; // vk::PolygonMode::eLine;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = vk::CullModeFlagBits::eBack; // vk::CullModeFlagBits::eNone;
		rasterizer.frontFace = vk::FrontFace::eClockwise; // vk::FrontFace::eCounterClockwise;
		rasterizer.depthBiasEnable = 0;
		rasterizer.depthBiasConstantFactor = 0.0f;
		rasterizer.depthBiasClamp = 0.0f;
		rasterizer.depthBiasSlopeFactor = 0.0f;

		vk::SampleMask sampleMask = std::numeric_limits<unsigned>::max(); // uint32_t

		vk::PipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = vk::StructureType::ePipelineMultisampleStateCreateInfo;
		multisampling.flags = vk::PipelineMultisampleStateCreateFlags();
		multisampling.rasterizationSamples = vk::supp::getMaxUsableSampleCount(physical_device);
		multisampling.sampleShadingEnable = 0u; // def. false
		multisampling.minSampleShading = 1.0f;
		multisampling.pSampleMask = &sampleMask;
		multisampling.alphaToCoverageEnable = 0;
		multisampling.alphaToOneEnable = 0;

		vk::StencilOpState stencilOpState{};
		stencilOpState.failOp = vk::StencilOp::eKeep;
		stencilOpState.passOp = vk::StencilOp::eKeep;
		stencilOpState.depthFailOp = vk::StencilOp::eKeep;
		stencilOpState.compareOp = vk::CompareOp::eAlways;
		stencilOpState.compareMask = 0;
		stencilOpState.writeMask = 0;
		stencilOpState.reference = 0;

		vk::PipelineDepthStencilStateCreateInfo depthStencilInfo{};
		depthStencilInfo.sType = vk::StructureType::ePipelineDepthStencilStateCreateInfo;
		depthStencilInfo.flags = vk::PipelineDepthStencilStateCreateFlags();
		depthStencilInfo.depthTestEnable = false;
		depthStencilInfo.depthWriteEnable = false;
		depthStencilInfo.depthCompareOp = vk::CompareOp::eLessOrEqual;
		depthStencilInfo.depthBoundsTestEnable = false;
		depthStencilInfo.stencilTestEnable = false;
		depthStencilInfo.front = stencilOpState;
		depthStencilInfo.back = stencilOpState;
		depthStencilInfo.maxDepthBounds = 1.0f;
		depthStencilInfo.minDepthBounds = 0.0f;

		vk::PipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask =
			vk::ColorComponentFlagBits::eR
			| vk::ColorComponentFlagBits::eG
			| vk::ColorComponentFlagBits::eB
			| vk::ColorComponentFlagBits::eA;
		// vk::ColorComponentFlagBits::eA | vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB;
		colorBlendAttachment.blendEnable = false;
		colorBlendAttachment.srcColorBlendFactor = vk::BlendFactor::eZero;
		colorBlendAttachment.dstColorBlendFactor = vk::BlendFactor::eZero;
		colorBlendAttachment.colorBlendOp = vk::BlendOp::eAdd;
		colorBlendAttachment.srcAlphaBlendFactor = vk::BlendFactor::eZero;
		colorBlendAttachment.dstAlphaBlendFactor = vk::BlendFactor::eZero;
		colorBlendAttachment.alphaBlendOp = vk::BlendOp::eAdd;

		std::array<vk::PipelineColorBlendAttachmentState, 1> colorBlendAttachments = { colorBlendAttachment };

		vk::PipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = vk::StructureType::ePipelineColorBlendStateCreateInfo;
		colorBlending.flags = vk::PipelineColorBlendStateCreateFlags();
		colorBlending.logicOpEnable = 0;
		colorBlending.logicOp = vk::LogicOp::eCopy;
		colorBlending.attachmentCount = (unsigned)colorBlendAttachments.size();
		colorBlending.pAttachments = colorBlendAttachments.data();
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		std::array<vk::DynamicState, 2> dynamicStates = { vk::DynamicState::eViewport, vk::DynamicState::eScissor };

		vk::PipelineDynamicStateCreateInfo pipelineDynamicState{};
		pipelineDynamicState.sType = vk::StructureType::ePipelineDynamicStateCreateInfo;
		pipelineDynamicState.flags = vk::PipelineDynamicStateCreateFlags();
		pipelineDynamicState.dynamicStateCount = (unsigned)dynamicStates.size();
		pipelineDynamicState.pDynamicStates = dynamicStates.data();

		vk::GraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = vk::StructureType::eGraphicsPipelineCreateInfo;
		pipelineInfo.flags = vk::PipelineCreateFlags();
		pipelineInfo.stageCount = (unsigned)shaderStages.size();
		pipelineInfo.pStages = shaderStages.data();
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pTessellationState = nullptr;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = &depthStencilInfo;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = &pipelineDynamicState;
		pipelineInfo.layout = pipelineLayout;
		pipelineInfo.renderPass = RenderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = nullptr; // VK_NULL_HANDLE;
		pipelineInfo.basePipelineIndex = -1;

		return vk::raii::Pipeline(Device, pipelineCache, pipelineInfo, nullptr);
	}

	std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> get_vertex_buffer(
		const vk::raii::Device& device,
		const vk::raii::PhysicalDevice& PhysicalDevice,
		const vk::raii::Queue& graphicsQueue,
		const vk::raii::CommandPool& commandPool
	) {

		auto total_size = vk::supp::vectorsizeof(vertices);

		vk::BufferCreateInfo bufferInfo{};
		bufferInfo.size = total_size;
		bufferInfo.usage = vk::BufferUsageFlagBits::eTransferSrc; // VertexBuffer; 
		bufferInfo.sharingMode = vk::SharingMode::eExclusive;

		auto stagingBuffer = vk::raii::Buffer(device, bufferInfo);

		auto memReqs = stagingBuffer.getMemoryRequirements();
		vk::MemoryAllocateInfo allocInfo{};
		allocInfo.allocationSize = memReqs.size;
		allocInfo.memoryTypeIndex = vk::supp::findMemoryType(memReqs.memoryTypeBits,
			vk::MemoryPropertyFlagBits::eHostVisible |
			vk::MemoryPropertyFlagBits::eHostCoherent,
			PhysicalDevice
		);

		auto stagingMemory = vk::raii::DeviceMemory(device, allocInfo);
		stagingBuffer.bindMemory(stagingMemory, 0);

		void* data = stagingMemory.mapMemory(0, total_size);
		char* ptr = static_cast<char*>(data);
		std::memcpy(ptr, vertices.data(), total_size);
		stagingMemory.unmapMemory();

		vk::BufferCreateInfo vertexInfo{};
		vertexInfo.size = total_size;
		vertexInfo.usage =
			vk::BufferUsageFlagBits::eVertexBuffer
			| vk::BufferUsageFlagBits::eTransferDst;
		vertexInfo.sharingMode = vk::SharingMode::eExclusive;

		auto vertexBuffer = vk::raii::Buffer(device, vertexInfo);
		auto vertexReqs = vertexBuffer.getMemoryRequirements();
		vk::MemoryAllocateInfo vertexAlloc{};
		vertexAlloc.allocationSize = vertexReqs.size;
		vertexAlloc.memoryTypeIndex = vk::supp::findMemoryType(
			vertexReqs.memoryTypeBits,
			vk::MemoryPropertyFlagBits::eDeviceLocal,
			PhysicalDevice
		);

		auto vertexMemory = vk::raii::DeviceMemory(device, vertexAlloc);
		vertexBuffer.bindMemory(vertexMemory, 0);

		vk::CommandBufferAllocateInfo cmdAllocInfo(*commandPool, vk::CommandBufferLevel::ePrimary, 1);
		auto cmd_buffs = device.allocateCommandBuffers(cmdAllocInfo);
		auto cmdBuffer = std::move(cmd_buffs[0]);

		cmdBuffer.begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit));

		vk::BufferCopy copyRegion{};
		copyRegion.srcOffset = 0;
		copyRegion.dstOffset = 0;
		copyRegion.size = total_size;
		cmdBuffer.copyBuffer(*stagingBuffer, *vertexBuffer, copyRegion);

		constexpr auto VK_QUEUE_FAMILY_IGNORED = std::numeric_limits<unsigned>::max();
		vk::BufferMemoryBarrier barrier{};
		barrier.buffer = *vertexBuffer;
		barrier.size = total_size;
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
		barrier.dstAccessMask = vk::AccessFlagBits::eVertexAttributeRead;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

		cmdBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer,
			vk::PipelineStageFlagBits::eVertexInput,
			vk::DependencyFlags(),
			nullptr, barrier, nullptr);

		cmdBuffer.end();

		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*cmdBuffer;
		graphicsQueue.submit(submitInfo, nullptr);
		graphicsQueue.waitIdle();

		return std::pair(std::move(vertexBuffer), std::move(vertexMemory));
	}

	std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> get_index_buffer(
		const vk::raii::Device& device,
		const vk::raii::PhysicalDevice& PhysicalDevice,
		const vk::raii::Queue& graphicsQueue,
		const vk::raii::CommandPool& commandPool
	) {
		auto total_size = vk::supp::vectorsizeof(indices);

		vk::BufferCreateInfo stagingBufferInfo{};
		stagingBufferInfo.size = total_size;
		stagingBufferInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
		stagingBufferInfo.sharingMode = vk::SharingMode::eExclusive;

		auto stagingBuffer = vk::raii::Buffer(device, stagingBufferInfo);

		auto memReqs = stagingBuffer.getMemoryRequirements();
		vk::MemoryAllocateInfo allocInfo{};
		allocInfo.allocationSize = memReqs.size;
		allocInfo.memoryTypeIndex = vk::supp::findMemoryType(memReqs.memoryTypeBits,
			vk::MemoryPropertyFlagBits::eHostVisible |
			vk::MemoryPropertyFlagBits::eHostCoherent,
			PhysicalDevice
		);

		auto stagingMemory = vk::raii::DeviceMemory(device, allocInfo);
		stagingBuffer.bindMemory(stagingMemory, 0);

		// void* data = stagingMemory.mapMemory(0, total_size);
		// char* ptr = static_cast<char*>(data);
		// TODO
		// stagingMemory.unmapMemory();
		{
			auto data = std::span<std::byte>(
				reinterpret_cast<std::byte*>(
					stagingMemory.mapMemory(0, total_size)
					)
				, total_size
			);
			// const auto& i = vkCube::shaders_data::vIndices;
			// using i_t = std::remove_cvref_t<decltype(i)>::value_type;
			// auto tmp = std::span<i_t>(i.data(), i.size());
			auto ii = std::as_bytes(std::span{ indices });
			std::copy(ii.begin(), ii.end(), data.begin());
			stagingMemory.unmapMemory();
		}

		vk::BufferCreateInfo indicesInfo{};
		indicesInfo.size = total_size;
		indicesInfo.usage =
			vk::BufferUsageFlagBits::eIndexBuffer
			| vk::BufferUsageFlagBits::eTransferDst;
		indicesInfo.sharingMode = vk::SharingMode::eExclusive;

		auto indicesBuffer = vk::raii::Buffer(device, indicesInfo);
		auto indicesReqs = indicesBuffer.getMemoryRequirements();
		vk::MemoryAllocateInfo indicesAlloc{};
		indicesAlloc.allocationSize = indicesReqs.size;
		indicesAlloc.memoryTypeIndex = vk::supp::findMemoryType(
			indicesReqs.memoryTypeBits,
			vk::MemoryPropertyFlagBits::eDeviceLocal,
			PhysicalDevice
		);

		auto indicesMemory = vk::raii::DeviceMemory(device, indicesAlloc);
		indicesBuffer.bindMemory(indicesMemory, 0);

		vk::CommandBufferAllocateInfo cmdAllocInfo(*commandPool, vk::CommandBufferLevel::ePrimary, 1);
		auto cmd_buffs = device.allocateCommandBuffers(cmdAllocInfo);
		auto cmdBuffer = std::move(cmd_buffs[0]);

		cmdBuffer.begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit));

		vk::BufferCopy copyRegion{};
		copyRegion.srcOffset = 0;
		copyRegion.dstOffset = 0;
		copyRegion.size = total_size;
		cmdBuffer.copyBuffer(*stagingBuffer, *indicesBuffer, copyRegion);

		constexpr auto VK_QUEUE_FAMILY_IGNORED = std::numeric_limits<unsigned>::max();
		vk::BufferMemoryBarrier barrier{};
		barrier.buffer = *indicesBuffer;
		barrier.size = total_size;
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
		barrier.dstAccessMask = vk::AccessFlagBits::eIndexRead;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

		cmdBuffer.pipelineBarrier(
			vk::PipelineStageFlagBits::eTransfer,
			vk::PipelineStageFlagBits::eVertexInput,
			vk::DependencyFlags(),
			nullptr, barrier, nullptr
		);

		cmdBuffer.end();

		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &*cmdBuffer;
		graphicsQueue.submit(submitInfo, nullptr);
		graphicsQueue.waitIdle();

		return std::pair(std::move(indicesBuffer), std::move(indicesMemory));
	}
} // anon ns

export namespace skybox_shader {
#if 1
	struct SkyBox {
		private:
			SkyboxSampler sampler;
			vk::raii::PipelineLayout pipeline_layout;
			vk::raii::Pipeline pipeline;
			std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> vertex_buffer_and_mem;
			std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> indices_buffer_and_mem;

		public:
			SkyBox(
				const vk::raii::Device& logical_device,
				const vk::raii::DescriptorSetLayout& camera_desc_layout,
				const vk::raii::PhysicalDevice& physical_device,
				const vk::raii::RenderPass& renderpass,
				const vk::Extent2D& extent,
				const vk::raii::Queue& graphicsQueue,
				const vk::raii::CommandPool& commandPool
			)
				: sampler(logical_device, physical_device, commandPool, graphicsQueue)
				, pipeline_layout(get_PipelineLayout(logical_device, camera_desc_layout, sampler.get_DescriptorSetLayout()))
				, pipeline(
					get_Pipeline(
						logical_device,
						physical_device,
						renderpass,
						extent,
						vk::supp::installShader(logical_device, std::as_bytes(std::span<decltype(vert_v)::value_type>(vert_v.data(), vert_v.size()))),
						vk::supp::installShader(logical_device, std::as_bytes(std::span<decltype(frag_v)::value_type>(frag_v.data(), frag_v.size()))),
						pipeline_layout,
						get_PipelineCache(logical_device)
					)
				)
				, vertex_buffer_and_mem(get_vertex_buffer(logical_device, physical_device, graphicsQueue, commandPool))
				, indices_buffer_and_mem(get_index_buffer(logical_device, physical_device, graphicsQueue, commandPool))
			{
			}

		public:
			void setup_command_buffers(
				const vk::raii::CommandBuffer& commandBuffer,
				const vk::raii::DescriptorSet& desc_set_camera
			) {
				commandBuffer.bindVertexBuffers(0, { vertex_buffer_and_mem.first }, { 0 });
				commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
				commandBuffer.bindIndexBuffer(*indices_buffer_and_mem.first, 0, vk::IndexType::eUint16);
				commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline_layout, 0, { desc_set_camera, sampler.get_DescriptorSet() }, {});
				commandBuffer.drawIndexed(indices.size(), 1, 0, 0, 0);
			}
	};

#endif
}