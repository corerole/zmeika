module;

export module vkCube;
import vulkan;
import vulkan_helpers;
import shaders_compiler;
import vkCube_shaders_sources;
import vkCube_shaders_data;
import vkCube_data;
import vk_shader_iface;


template<typename T> concept vector_like = std::true_type::value;
constexpr unsigned vectorsizeof(const vector_like auto& vec) noexcept {
	using value_type = std::remove_cvref_t<decltype(vec)>::value_type;
	return vec.size() * sizeof(value_type);
}

auto frag_v = shaders_compiler::compile_shader(vkCube::shaders_sources::frag, shaders_compiler::shaderc_shader_kind::shaderc_glsl_fragment_shader);
auto vert_v = shaders_compiler::compile_shader(vkCube::shaders_sources::vert, shaders_compiler::shaderc_shader_kind::shaderc_glsl_vertex_shader);

vk::raii::DescriptorSetLayout get_DescriptorSetLayout_vkCube(const vk::raii::Device& Device) {
	std::array<vk::DescriptorSetLayoutBinding, 1> layouts;
	layouts[0].binding = 0;
	layouts[0].descriptorCount = 1;
	layouts[0].descriptorType = vk::DescriptorType::eUniformBuffer;
	layouts[0].pImmutableSamplers = nullptr;
	layouts[0].stageFlags = vk::ShaderStageFlagBits::eVertex;

	vk::DescriptorSetLayoutCreateInfo descSetLayoutCreateInfo({}, layouts);

	return vk::raii::DescriptorSetLayout(Device, descSetLayoutCreateInfo);
}

vk::raii::DescriptorPool get_DescriptorPool(const vk::raii::Device& logical_device) {
	vk::DescriptorType dcst = vk::DescriptorType::eUniformBuffer;
	unsigned descriptors_count = 1;
	vk::DescriptorPoolSize dps(dcst, descriptors_count);
	vk::DescriptorPoolCreateFlags flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet; // { FREE_DESCRIPTOR_SET_BIT };
	unsigned MaxSets = 1;
	std::array<vk::DescriptorPoolSize, 1> poolSizes_ = { dps };
	vk::DescriptorPoolCreateInfo dci(flags, MaxSets,  poolSizes_);
	return vk::raii::DescriptorPool(logical_device, dci);
}

std::vector<vk::raii::DescriptorSet> get_DescriptorSets_vkCube(
	const vk::raii::Device& logical_device,
	const vk::raii::DescriptorPool& descPool,
	const vk::raii::DescriptorSetLayout& descSetLayout
) {
	std::array<vk::DescriptorSetLayout, 1> ls = { *descSetLayout };
	vk::DescriptorSetAllocateInfo dsai(descPool, ls);
	return logical_device.allocateDescriptorSets(dsai);
}

vk::raii::PipelineLayout get_PipelineLayout_vkCube(const vk::raii::Device& Device, const vk::raii::DescriptorSetLayout& descLayout) {
	vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
	pipelineLayoutCreateInfo.flags = {};
	pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
	pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;
	pipelineLayoutCreateInfo.setLayoutCount = 1;
	pipelineLayoutCreateInfo.pSetLayouts = &(*descLayout);

	return vk::raii::PipelineLayout(Device, pipelineLayoutCreateInfo);;
}

vk::raii::PipelineCache get_PipelineCache_vkCube(const vk::raii::Device& Device) {
	vk::PipelineCacheCreateInfo createInfo{};
	createInfo.flags;
	createInfo.initialDataSize;
	createInfo.pInitialData;
	createInfo.pNext;
	return vk::raii::PipelineCache(Device, createInfo);
}

export namespace vkCube {
	std::pair<vk::raii::Image, vk::raii::DeviceMemory> createDepthResources(
		const vk::raii::Device& device,
		const vk::raii::PhysicalDevice& physicalDevice,
		const vk::Extent2D& extent // ,
		// const vk::raii::CommandPool& commandPool,
		// const vk::raii::Queue& graphicsQueue
	) {
		vk::Format depthFormat = vk::Format::eD32Sfloat;

		vk::ImageCreateInfo imageInfo{};
		imageInfo.imageType = vk::ImageType::e2D;
		imageInfo.extent.width = extent.width;
		imageInfo.extent.height = extent.height;
		imageInfo.extent.depth = 1;
		imageInfo.mipLevels = 1;
		imageInfo.arrayLayers = 1;
		imageInfo.format = depthFormat;
		imageInfo.tiling = vk::ImageTiling::eOptimal;
		imageInfo.initialLayout = vk::ImageLayout::eUndefined;
		imageInfo.usage = vk::ImageUsageFlagBits::eDepthStencilAttachment;
		imageInfo.samples = vk::supp::getMaxUsableSampleCount(physicalDevice);
		imageInfo.sharingMode = vk::SharingMode::eExclusive;

		vk::raii::Image depthImage = device.createImage(imageInfo);

		vk::MemoryRequirements memRequirements = depthImage.getMemoryRequirements();

		vk::MemoryAllocateInfo allocInfo{};
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = vk::supp::findMemoryType(
			memRequirements.memoryTypeBits,
			vk::MemoryPropertyFlagBits::eDeviceLocal,
			physicalDevice
		);

		vk::raii::DeviceMemory depthImageMemory = device.allocateMemory(allocInfo);

		depthImage.bindMemory(*depthImageMemory, 0);

		return std::pair(std::move(depthImage), std::move(depthImageMemory));
	}

	vk::raii::ImageView createDepthImageView(
		const vk::raii::Device& device,
		const vk::raii::Image& depthImage
	) {
		vk::ImageViewCreateInfo viewInfo{};
		viewInfo.image = *depthImage;
		viewInfo.viewType = vk::ImageViewType::e2D;
		viewInfo.format = vk::Format::eD32Sfloat;
		viewInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;

		return vk::raii::ImageView(device, viewInfo);
	}

	std::pair<vk::raii::Image, vk::raii::DeviceMemory> createColorResources(
		const vk::raii::Device& device,
		const vk::raii::PhysicalDevice& physicalDevice,
		const vk::Extent2D& extent,
		const vk::Format& colorFormat
	) {
		vk::ImageCreateInfo imageInfo{};
		imageInfo.imageType = vk::ImageType::e2D;
		imageInfo.extent.width = extent.width;
		imageInfo.extent.height = extent.height;
		imageInfo.extent.depth = 1;
		imageInfo.mipLevels = 1;
		imageInfo.arrayLayers = 1;
		imageInfo.format = colorFormat;
		imageInfo.tiling = vk::ImageTiling::eOptimal;
		imageInfo.initialLayout = vk::ImageLayout::eUndefined;
		imageInfo.usage = vk::ImageUsageFlagBits::eColorAttachment;
		imageInfo.samples = vk::supp::getMaxUsableSampleCount(physicalDevice);
		imageInfo.sharingMode = vk::SharingMode::eExclusive;

		vk::raii::Image colorImage = device.createImage(imageInfo);

		vk::MemoryRequirements memRequirements = colorImage.getMemoryRequirements();

		vk::MemoryAllocateInfo allocInfo{};
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = vk::supp::findMemoryType(
			memRequirements.memoryTypeBits,
			vk::MemoryPropertyFlagBits::eDeviceLocal,
			physicalDevice
		);

		vk::raii::DeviceMemory colorImageMemory = device.allocateMemory(allocInfo);

		colorImage.bindMemory(*colorImageMemory, 0);

		return std::pair(std::move(colorImage), std::move(colorImageMemory));
	}

	vk::raii::ImageView createColorImageView(
		const vk::raii::Device& device,
		const vk::raii::Image& colorImage,
		const vk::Format& colorFormat
	) {
		vk::ImageViewCreateInfo viewInfo{};
		viewInfo.image = *colorImage;
		viewInfo.viewType = vk::ImageViewType::e2D;
		viewInfo.format = colorFormat;
		viewInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;

		return vk::raii::ImageView(device, viewInfo);
	}
}

vk::raii::Pipeline get_Pipeline_vkCube(
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

	std::array<vk::VertexInputBindingDescription, 3> bindingDescription;
	bindingDescription[0].binding = 0;
	bindingDescription[0].stride = 3 * sizeof(float);
	bindingDescription[0].inputRate = vk::VertexInputRate::eVertex;
	bindingDescription[1].binding = 1;
	bindingDescription[1].stride = 3 * sizeof(float);
	bindingDescription[1].inputRate = vk::VertexInputRate::eVertex;
	bindingDescription[2].binding = 2;
	bindingDescription[2].stride = 3 * sizeof(float);
	bindingDescription[2].inputRate = vk::VertexInputRate::eVertex;

	std::array<vk::VertexInputAttributeDescription, 3> attributeDescriptions;
	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = vk::Format::eR32G32B32Sfloat;
	attributeDescriptions[0].offset = 0;
	attributeDescriptions[1].binding = 1;
	attributeDescriptions[1].location = 1;
	attributeDescriptions[1].format = vk::Format::eR32G32B32Sfloat;
	attributeDescriptions[1].offset = 0;
	attributeDescriptions[2].binding = 2;
	attributeDescriptions[2].location = 2;
	attributeDescriptions[2].format = vk::Format::eR32G32B32Sfloat;
	attributeDescriptions[2].offset = 0;

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

	uint32_t x = 0;
	uint32_t y = 0;
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
	rasterizer.cullMode = vk::CullModeFlagBits::eBack; // vk::CullModeFlagBits::eNone
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
	depthStencilInfo.depthTestEnable = true;
	depthStencilInfo.depthWriteEnable = true; // bool
	depthStencilInfo.depthCompareOp = vk::CompareOp::eLess; // vk::CompareOp::eLessOrEqual;
	depthStencilInfo.depthBoundsTestEnable = false;
	depthStencilInfo.stencilTestEnable = false;
	depthStencilInfo.front = stencilOpState;
	depthStencilInfo.back = stencilOpState;
	depthStencilInfo.maxDepthBounds = 1.0f;
	depthStencilInfo.minDepthBounds = 0.0f;

	vk::PipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
	// vk::ColorComponentFlagBits::eA | vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB;
	colorBlendAttachment.blendEnable = 0;
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

std::array<std::size_t, 3> get_offsets_vkCube() {
	auto vVsize = vectorsizeof(vkCube::shaders_data::vVertices);
	auto vCsize = vectorsizeof(vkCube::shaders_data::vColors);
	auto vertex_offset = 0u;                      // вершины в начале
	auto colors_offset = vertex_offset + vVsize;
	auto normals_offset = colors_offset + vCsize;
	return std::array<std::size_t, 3>{vertex_offset, colors_offset, normals_offset};
}

vk::raii::Buffer get_UBO_Buffer(const vk::raii::Device& device) {
	vk::BufferCreateInfo uboInfo{};
	uboInfo.size = sizeof(vkCube::data::UBO);
	uboInfo.usage = vk::BufferUsageFlagBits::eUniformBuffer;
	uboInfo.sharingMode = vk::SharingMode::eExclusive;
	return vk::raii::Buffer(device, uboInfo);
}

std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> get_UBO_BufferAndDeviceMemory(
	const vk::raii::Device& device,
	const vk::raii::PhysicalDevice& physicalDevice,
	vk::raii::Buffer&& buffer)
{
	auto uboMemReqs = buffer.getMemoryRequirements();
	vk::MemoryAllocateInfo uboAlloc{};
	uboAlloc.allocationSize = uboMemReqs.size;
	uboAlloc.memoryTypeIndex = vk::supp::findMemoryType(
		uboMemReqs.memoryTypeBits,
		vk::MemoryPropertyFlagBits::eHostVisible |
		vk::MemoryPropertyFlagBits::eHostCoherent,
		physicalDevice
	);

	vk::raii::DeviceMemory uboBufferMemory(device, uboAlloc);
	buffer.bindMemory(uboBufferMemory, 0);
	return std::pair(std::forward<decltype(buffer)>(buffer), std::forward<decltype(std::move(uboBufferMemory))>(std::move(uboBufferMemory)));
}

#if 0
std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> get_Buffers_vkCube(vk::supp::BufferCreater& bc, std::array<size_t, 3>& offsets) {
	auto& vertex_offset = offsets[0];
	auto& colors_offset = offsets[1];
	auto& normals_offset = offsets[2];
	auto vNsize = vectorsizeof(vkcube::vNormals);
	size_t bufferSize = normals_offset + vNsize;
	auto bnm = bc.createEmptyBuffer(
		bufferSize,
		vk::BufferUsageFlagBits::eUniformBuffer | vk::BufferUsageFlagBits::eVertexBuffer,
		vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent
	);
	{
		auto mm = bc.get_MemoryMapper(bnm.second, bufferSize);
		void* mapped = mm.get_mapped();

		std::copy(vVertices.begin(), vVertices.end(), static_cast<decltype(vVertices)::value_type*>((void*)((char*)mapped + vertex_offset)));
		std::copy(vColors.begin(), vColors.end(), static_cast<decltype(vColors)::value_type*>((void*)((char*)mapped + colors_offset)));
		std::copy(vNormals.begin(), vNormals.end(), static_cast<decltype(vNormals)::value_type*>((void*)((char*)mapped + normals_offset)));
	}
	return bnm;
}
#endif
#if 0
vk::raii::DescriptorSet get_DescriptorSet_vkCube(
	vk::supp::DescritorPoolCreator& descPoolCreator,
	const vk::raii::DescriptorPool& descPool,
	const vk::raii::DescriptorSetLayout& descSetLayout
) {
	std::array<vk::DescriptorSetLayout, 1> ls = { *descSetLayout };

	auto descSets = descPoolCreator.allocate_DescriptorSets(descPool, ls);
	return std::move(descSets[0]);
}

void VkCube::update_DescriptorSet_vkCube(
	const vk::raii::Buffer& buffer,
	const vk::raii::DescriptorSet& descSet,
	vk::supp::DescritorPoolCreator& descPoolCreator
) {
	vk::DescriptorBufferInfo bufferInfo(buffer, 0, sizeof(vkcube::UBO));

	std::array<vk::WriteDescriptorSet, 1> wds;
	wds[0].dstSet = descSet;
	wds[0].dstBinding = 0;
	wds[0].dstArrayElement = 0;
	wds[0].descriptorCount = 1;
	wds[0].descriptorType = vk::DescriptorType::eUniformBuffer;
	wds[0].pBufferInfo = &bufferInfo;

	descPoolCreator.update_DescriptorSet(wds, {});
}

vk::supp::CommandBufferData get_CommandBufferData() {
	if (!is_inited) { throw std::runtime_error("can't be used without init"); }
	vk::supp::CommandBufferData cb_data;
	cb_data.data = &cbdata;
	cb_data.f = vkCube_set_CommandBuffer;
	return cb_data;
}
#endif
#if 0
void vkCube_set_CommandBuffer(
	std::span<vk::raii::CommandBuffer> commandBuffers,
	std::span<vk::raii::Framebuffer> framebuffers,
	const vk::raii::RenderPass& renderpass,
	const vk::Rect2D& scissor,
	const vk::Viewport& viewport
) {
	ubo_obj.update(scissor.extent);
	/* update buffer memory */
#if 0
	void* mapped = data.buffer.second.mapMemory(0, sizeof(vkcube::UBO));
	std::memcpy(mapped, &ubo, sizeof(vkcube::UBO));
	data.buffer.second.unmapMemory();
#endif
	auto v = std::views::zip(commandBuffers, framebuffers);
	for (auto& [commandBuffer, framebuffer] : v) {
		vk::CommandBufferBeginInfo cb_begin_info{};
		commandBuffer.begin(cb_begin_info);
		std::array<vk::ClearValue, 2> clearVal{};
		clearVal[0] = vk::ClearColorValue(0.0f, 0.0f, 0.0f, 1.0f);
		clearVal[1] = vk::ClearDepthStencilValue(1.0f, 0);
		vk::RenderPassBeginInfo rr_begin_info(*renderpass, *framebuffer, scissor, clearVal);
		commandBuffer.beginRenderPass(rr_begin_info, vk::SubpassContents::eInline);
		commandBuffer.bindVertexBuffers(0, { shaderBuffer.first, shaderBuffer.first, shaderBuffer.first }, data.offsets);
		commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, *data.pipeline);
		commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *data.pipelineLayout, 0, { *data.descriptorSet }, {});
		commandBuffer.setViewport(0, viewport);
		commandBuffer.setScissor(0, scissor);
		for (int j = 0; j < 6; ++j) {
			commandBuffer.draw(4, 1, j * 4, 0);
		}
		commandBuffer.endRenderPass();
		commandBuffer.end();
	}
}
#endif

std::array<std::size_t, 3> offsets = get_offsets_vkCube();

std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> get_vertex_buffer(
	const vk::raii::Device& device,
	const vk::raii::PhysicalDevice& PhysicalDevice,
	const vk::raii::Queue& graphicsQueue,
	const vk::raii::CommandPool& commandPool
) {
	std::size_t vertSize = vkCube::shaders_data::vVertices.size() * sizeof(float);
	std::size_t colorSize = vkCube::shaders_data::vColors.size() * sizeof(float);
	std::size_t normSize = vkCube::shaders_data::vNormals.size() * sizeof(float);
	auto total_size = offsets[2] + normSize;

	vk::BufferCreateInfo bufferInfo{};
	bufferInfo.size = total_size;
	bufferInfo.usage = vk::BufferUsageFlagBits::eTransferSrc; // VertexBuffer; // только вершинный
	bufferInfo.sharingMode = vk::SharingMode::eExclusive;

	auto stagingBuffer = vk::raii::Buffer(device, bufferInfo);

	// Запросить требования к памяти
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
	std::memcpy(ptr, vkCube::shaders_data::vVertices.data(), vertSize);
	std::memcpy(ptr + vertSize, vkCube::shaders_data::vColors.data(), colorSize);
	std::memcpy(ptr + vertSize + colorSize, vkCube::shaders_data::vNormals.data(), normSize);
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
	auto total_size = vectorsizeof(vkCube::shaders_data::vIndices);

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
			),
			total_size);
		// const auto& i = vkCube::shaders_data::vIndices;
		// using i_t = std::remove_cvref_t<decltype(i)>::value_type;
		// auto tmp = std::span<i_t>(i.data(), i.size());
		auto ii = std::as_bytes(std::span{vkCube::shaders_data::vIndices});
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

export namespace vkCube {
#if 1
	struct vkCubeT {
		private:
			vkCube::data::UBO_obj ubo_obj;
			vk::raii::DescriptorPool desc_pool;
			vk::raii::DescriptorSetLayout desc_layout;
			std::vector<vk::raii::DescriptorSet> desc_sets;
			vk::raii::PipelineLayout pipeline_layout;
			vk::raii::Pipeline pipeline;
			std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> ubo_buffer_and_mem;
			std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> vertex_buffer_and_mem;
			std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> indices_buffer_and_mem;

		private:
			vkCube::data::UBO update_ubo(const vk::Extent2D& extent) {
				return ubo_obj.update(extent);
			}

		public:
			vkCubeT(
				const vk::raii::Device& logical_device,
				const vk::raii::PhysicalDevice& physical_device,
				const vk::raii::RenderPass& renderpass,
				const vk::Extent2D& extent,
				const vk::raii::Queue& graphicsQueue,
				const vk::raii::CommandPool& commandPool
			)
				: ubo_obj({})
				, desc_pool(get_DescriptorPool(logical_device))
				, desc_layout(get_DescriptorSetLayout_vkCube(logical_device))
				, desc_sets(get_DescriptorSets_vkCube(logical_device, desc_pool, desc_layout))
				, pipeline_layout(get_PipelineLayout_vkCube(logical_device, desc_layout))
				, pipeline(
						get_Pipeline_vkCube(
							logical_device,
							physical_device,
							renderpass,
							extent,
							vk::supp::installShader(logical_device, std::as_bytes(std::span<decltype(vert_v)::value_type>(vert_v.data(), vert_v.size()))),
							vk::supp::installShader(logical_device, std::as_bytes(std::span<decltype(frag_v)::value_type>(frag_v.data(), frag_v.size()))),
							pipeline_layout,
							get_PipelineCache_vkCube(logical_device)
						)
					)
				, ubo_buffer_and_mem(get_UBO_BufferAndDeviceMemory(logical_device, physical_device, get_UBO_Buffer(logical_device)))
				, vertex_buffer_and_mem(get_vertex_buffer(logical_device, physical_device, graphicsQueue, commandPool))
				, indices_buffer_and_mem(get_index_buffer(logical_device, physical_device, graphicsQueue, commandPool))
			{
				constexpr unsigned ubo_size = sizeof(vkCube::data::UBO);
				
				vk::DescriptorBufferInfo bufferInfo{};
				bufferInfo.buffer = *ubo_buffer_and_mem.first;
				bufferInfo.offset = 0;
				bufferInfo.range = ubo_size;

				vk::WriteDescriptorSet writeSet{};
				writeSet.dstSet = *desc_sets[0];
				writeSet.dstBinding = 0;
				writeSet.dstArrayElement = 0;
				writeSet.descriptorCount = 1;
				writeSet.descriptorType = vk::DescriptorType::eUniformBuffer;
				writeSet.pBufferInfo = &bufferInfo;

				logical_device.updateDescriptorSets(writeSet, {});
			}
	
		public:
			void update(const vk::Extent2D& extent) {
				auto ubo = update_ubo(extent);

				void* uboPtr = ubo_buffer_and_mem.second.mapMemory(0, sizeof(decltype(ubo)));
				std::memcpy(uboPtr, &ubo, sizeof(ubo));
				ubo_buffer_and_mem.second.unmapMemory();
			}

			void setup_command_buffers(
				const vk::raii::CommandBuffer& commandBuffer,
				const vk::raii::Framebuffer& framebuffer,
				const vk::raii::RenderPass& renderpass,
				const vk::Extent2D& extent
			) {
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
				commandBuffer.begin(cb_begin_info);
				std::array<vk::ClearValue, 2> clearVal{};
				clearVal[0] = vk::ClearColorValue(0.0f, 0.0f, 0.0f, 1.0f);
				clearVal[1] = vk::ClearDepthStencilValue(1.0f, 0);
				vk::RenderPassBeginInfo rr_begin_info(*renderpass, *framebuffer, rect, clearVal);
				commandBuffer.beginRenderPass(rr_begin_info, vk::SubpassContents::eInline);
				commandBuffer.bindVertexBuffers(0, { *vertex_buffer_and_mem.first, *vertex_buffer_and_mem.first, *vertex_buffer_and_mem.first }, offsets);
				commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
				commandBuffer.bindIndexBuffer(*indices_buffer_and_mem.first, 0, vk::IndexType::eUint16);
				commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline_layout, 0, { desc_sets[0] }, {});
				commandBuffer.setViewport(0, viewport);
				commandBuffer.setScissor(0, rect);
				commandBuffer.drawIndexed(36, 1, 0, 0, 0);
				commandBuffer.endRenderPass();
				commandBuffer.end();
				
			}
	};
	
#endif
}