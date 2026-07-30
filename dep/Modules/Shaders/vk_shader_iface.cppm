module;

export module vk_shader_iface;
import std;
import vulkan;

export namespace vk_shader_iface {
	template<typename Shader> concept ShaderLike = requires(Shader shader,
		const vk::raii::Device& logical_device,
		const vk::raii::DescriptorSetLayout& camera_dcs_layout,
		const vk::raii::PhysicalDevice& physical_device,
		const vk::raii::RenderPass& renderpass,
		const vk::Extent2D& extent,
		const vk::raii::Queue& graphicsQueue,
		const vk::raii::CommandPool& commandPool,

		const vk::raii::CommandBuffer& cb,
		const vk::raii::DescriptorSet& camera_dsc_set
		
		)
	{
		{ Shader(logical_device, camera_dcs_layout, physical_device, renderpass, extent, graphicsQueue, commandPool) };
		{ shader.setup_command_buffers(cb, camera_dsc_set) } -> std::same_as<void>;
	};

}