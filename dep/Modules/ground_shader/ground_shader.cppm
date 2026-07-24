module;

export module ground_shader;
import std;
import glm;
import vulkan;
import vulkan_helpers;
import shaders_compiler;

namespace {

#if 0
	struct GroundShader_s {
		public:
			glm::vec2 tileSize;
			float lineWidth;
			glm::vec3 color1;
			glm::vec3 color2;
			glm::vec3 lineColor;
	};
#endif

	constexpr std::string_view vert_src(
		R"(
			#version 460 core

			layout(set = 0, binding = 0) uniform X {
				mat4 view;
				mat4 projection;
				vec3 world_base_point;
			} camera;

			layout(location = 0) in vec3 inPosition;
			layout(location = 0) out vec3 position;
			layout(location = 1) out vec3 world_b_point;

			void main() {
				mat4 model = mat4(1.0);
				model[3].xyz = vec3(0.0, camera.world_base_point.y, 0.0);
				vec4 obj_pos = model * vec4(inPosition, 1.0);
				gl_Position = camera.projection * camera.view * obj_pos;
				position = obj_pos.xyz;
				world_b_point = camera.world_base_point;
			}
		)"
	);

	constexpr std::string_view frag_src(
		R"(
			#version 460 core

			layout(location = 0) in vec3 position;
			layout(location = 1) in vec3 world_base_point;
			layout(location = 0) out vec4 outColor;

			const float grid_step = 1.0;
			const float line_width = 0.01;
			const vec4 color = vec4(0.0, 0.0, 0.0, 1.0);
			const vec4 line_color = vec4(0.5, 0.07, 0.77, 0.66);

			void main() {
				vec3 rel = world_base_point - position;

				float dx = abs(mod(rel.x, grid_step) - grid_step * 0.5);
				float dy = abs(mod(rel.z, grid_step) - grid_step * 0.5);

				float half_width = line_width * 0.5;
				float dist_x = min(dx, grid_step - dx);
				float dist_y = min(dy, grid_step - dy);
				float dist = min(dist_x, dist_y);

				float ddx = dFdx(dist);
				float ddy = dFdy(dist);
				float w = length(vec2(ddx, ddy));

				float alpha = 1.0 - smoothstep(half_width - w, half_width + w, dist);
				vec4 final_color = mix(color, line_color, alpha);
				outColor = final_color;
			}
		)"
	);

#if 0
	template<unsigned N>
	constexpr auto get_floor() noexcept {
		constexpr unsigned vertsPerTile = 4;
		constexpr unsigned indicesPerTile = 6;
		constexpr unsigned totalTiles = N * N;
		constexpr unsigned totalVerts = totalTiles * vertsPerTile;
		constexpr unsigned totalIndices = totalTiles * indicesPerTile;

		std::array<float, totalVerts * 3> vertices{};
		std::array<unsigned, totalIndices> indices{};

		unsigned vertexOffset = 0;
		unsigned indexOffset = 0;

		for (unsigned j = 0; j < N; ++j) {
			for (unsigned i = 0; i < N; ++i) {
				float x0 = -static_cast<float>(N) + i * 2.0f;
				float x1 = x0 + 2.0f;
				float y0 = -static_cast<float>(N) + j * 2.0f;
				float y1 = y0 + 2.0f;

				vertices[vertexOffset * 3 + 0] = x0;
				// vertices[vertexOffset * 3 + 1] = y0;
				vertices[vertexOffset * 3 + 1] = 0.0f;
				// vertices[vertexOffset * 3 + 2] = 0.0f;
				vertices[vertexOffset * 3 + 2] = y0;

				vertices[(vertexOffset + 1) * 3 + 0] = x1;
				// vertices[(vertexOffset + 1) * 3 + 1] = y0;
				vertices[(vertexOffset + 1) * 3 + 1] = 0.0f;
				// vertices[(vertexOffset + 1) * 3 + 2] = 0.0f;
				vertices[(vertexOffset + 1) * 3 + 2] = y0;

				vertices[(vertexOffset + 2) * 3 + 0] = x1;
				// vertices[(vertexOffset + 2) * 3 + 1] = y1;
				vertices[(vertexOffset + 2) * 3 + 1] = 0.0f;
				//vertices[(vertexOffset + 2) * 3 + 2] = 0.0f;
				vertices[(vertexOffset + 2) * 3 + 2] = y1;

				vertices[(vertexOffset + 3) * 3 + 0] = x0;
				// vertices[(vertexOffset + 3) * 3 + 1] = y1;
				vertices[(vertexOffset + 3) * 3 + 1] = 0.0f;
				// vertices[(vertexOffset + 3) * 3 + 2] = 0.0f;
				vertices[(vertexOffset + 3) * 3 + 2] = y1;

				indices[indexOffset + 0] = vertexOffset + 0;
				indices[indexOffset + 1] = vertexOffset + 1;
				indices[indexOffset + 2] = vertexOffset + 2;
				indices[indexOffset + 3] = vertexOffset + 0;
				indices[indexOffset + 4] = vertexOffset + 2;
				indices[indexOffset + 5] = vertexOffset + 3;

				vertexOffset += 4;
				indexOffset += 6;
			}
		}

		return std::pair{ std::move(vertices), std::move(indices) };
	}

	const auto [floorVertices, floorIndices] = get_floor<100u>();
#endif	 

#if 1
	constexpr float distance = 500.0f;
	constexpr std::array<float, 12> floorVertices = {
		-distance, 0.0f, -distance,
		 distance, 0.0f, -distance,
		 distance, 0.0f,  distance,
		-distance, 0.0f,  distance
	};
#endif

#if 1
	constexpr std::array<unsigned short, 6> floorIndices = {
		0, 1, 2,
		0, 2, 3
	};
#endif

	vk::raii::PipelineLayout get_PipelineLayout_ground_shader(
		const vk::raii::Device& Device,
		const vk::raii::DescriptorSetLayout& camera_dcs_layout,
		const vk::raii::DescriptorSetLayout& samplers_dcs_layout
	) {
		vk::PipelineLayoutCreateFlagBits flags{};
		std::array<vk::DescriptorSetLayout, 2> dsl = { *camera_dcs_layout, *samplers_dcs_layout };
		vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo(flags, dsl, {}, nullptr);
		return vk::raii::PipelineLayout(Device, pipelineLayoutCreateInfo);;
	}

	vk::raii::PipelineCache get_PipelineCache_ground_shader(const vk::raii::Device& Device) {
		vk::PipelineCacheCreateInfo createInfo{};
		createInfo.flags;
		createInfo.initialDataSize;
		createInfo.pInitialData;
		createInfo.pNext;
		return vk::raii::PipelineCache(Device, createInfo);
	}

	vk::raii::Pipeline get_Pipeline_ground_shader(
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
		colorBlendAttachment.colorWriteMask =
			vk::ColorComponentFlagBits::eR
			| vk::ColorComponentFlagBits::eG
			| vk::ColorComponentFlagBits::eB
			| vk::ColorComponentFlagBits::eA;
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
		pipelineInfo.basePipelineHandle = nullptr;
		pipelineInfo.basePipelineIndex = -1;

		return vk::raii::Pipeline(Device, pipelineCache, pipelineInfo, nullptr);
	}

	std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> get_vertex_buffer(
		const vk::raii::Device& device,
		const vk::raii::PhysicalDevice& PhysicalDevice,
		const vk::raii::Queue& graphicsQueue,
		const vk::raii::CommandPool& commandPool
	) {
		auto vertices_size = vk::supp::vectorsizeof(floorVertices);

		vk::BufferCreateInfo bufferInfo{};
		bufferInfo.size = vertices_size;
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

		void* data = stagingMemory.mapMemory(0, vertices_size);
		char* ptr = static_cast<char*>(data);
		std::memcpy(ptr, floorVertices.data(), vertices_size);
		stagingMemory.unmapMemory();


		vk::BufferCreateInfo vertexInfo{};
		vertexInfo.size = vertices_size;
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
		copyRegion.size = vertices_size;
		cmdBuffer.copyBuffer(*stagingBuffer, *vertexBuffer, copyRegion);

		constexpr auto VK_QUEUE_FAMILY_IGNORED = std::numeric_limits<unsigned>::max();
		vk::BufferMemoryBarrier barrier{};
		barrier.buffer = *vertexBuffer;
		barrier.size = vertices_size;
		barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
		barrier.dstAccessMask = vk::AccessFlagBits::eVertexAttributeRead;
		barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

		cmdBuffer.pipelineBarrier(
			vk::PipelineStageFlagBits::eTransfer,
			vk::PipelineStageFlagBits::eVertexInput,
			vk::DependencyFlags(),
			nullptr,
			barrier,
			nullptr
		);

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
		auto total_size = vk::supp::vectorsizeof(floorIndices);

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
			auto ii = std::as_bytes(std::span{ floorIndices });
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

	auto frag_v = shaders_compiler::compile_shader(frag_src, shaders_compiler::shaderc_shader_kind::shaderc_glsl_fragment_shader);
	auto vert_v = shaders_compiler::compile_shader(vert_src, shaders_compiler::shaderc_shader_kind::shaderc_glsl_vertex_shader);

} // anon ns

export namespace ground_shader {
#if 1

	struct GroundShader {
		private:
			vk::raii::PipelineLayout pipeline_layout;
			vk::raii::Pipeline pipeline;
			std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> vertex_buffer_and_mem;
			std::pair<vk::raii::Buffer, vk::raii::DeviceMemory> indices_buffer_and_mem;

		public:
			GroundShader(
				const vk::raii::Device& logical_device,
				const vk::raii::DescriptorSetLayout& camera_dcs_layout,
				const vk::raii::DescriptorSetLayout& samplers_dcs_layout,
				const vk::raii::PhysicalDevice& physical_device,
				const vk::raii::RenderPass& renderpass,
				const vk::Extent2D& extent,
				const vk::raii::Queue& graphicsQueue,
				const vk::raii::CommandPool& commandPool
			)
				: pipeline_layout(get_PipelineLayout_ground_shader(logical_device, camera_dcs_layout, samplers_dcs_layout))
				, pipeline(
						get_Pipeline_ground_shader(
							logical_device,
							physical_device,
							renderpass,
							extent,
							vk::supp::installShader(logical_device, std::as_bytes(std::span<decltype(vert_v)::value_type>(vert_v.data(), vert_v.size()))),
							vk::supp::installShader(logical_device, std::as_bytes(std::span<decltype(frag_v)::value_type>(frag_v.data(), frag_v.size()))),
							pipeline_layout,
							get_PipelineCache_ground_shader(logical_device)
						)
					)
				, vertex_buffer_and_mem(get_vertex_buffer(logical_device, physical_device, graphicsQueue, commandPool))
				, indices_buffer_and_mem(get_index_buffer(logical_device, physical_device, graphicsQueue, commandPool))
			{}


		public:
			void setup_command_buffers(
				const vk::raii::CommandBuffer& commandBuffer,
				const vk::raii::DescriptorSet& desc_set_camera,
				const vk::raii::DescriptorSet& desc_set_samplers
			) {
				commandBuffer.bindVertexBuffers(0, { *vertex_buffer_and_mem.first }, { 0 });
				commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
				commandBuffer.bindIndexBuffer(*indices_buffer_and_mem.first, 0, vk::IndexType::eUint16);
				commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline_layout, 0, { desc_set_camera, desc_set_samplers }, {});
				commandBuffer.drawIndexed(floorIndices.size(), 1, 0, 0, 0);
			}
	};
#endif
} // ns ground_shader 

#if 0

/*
			layout(set = 1, binding = 0) uniform {
				mat4 model;
			} model;
*/

/*
			layout(set = 2, binding = 0) uniform {
					vec2 tileSize;
					float lineWidth;
					vec3 color1;
					vec3 color2;
					vec3 lineColor;
			} tileParams;
*/
#endif
