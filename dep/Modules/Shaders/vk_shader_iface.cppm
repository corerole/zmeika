module;

export module vk_shader_iface;
import std;
import vulkan;

export namespace vk_shader_iface {
	template<typename Shader> concept ShaderLike = requires(Shader shader) {
		{ Shader() };
	};

}