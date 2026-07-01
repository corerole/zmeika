module;

#include <shaderc/shaderc.hpp>

export module shaders_compiler;
import std;

export namespace shaders_compiler {
  using shaderc_shader_kind = ::shaderc_shader_kind;
  /* TODO */
  std::vector<unsigned> compile_shader(std::string_view source, shaderc_shader_kind kind) {
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;
    options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_3);
    //options.SetTargetSpirv(shaderc_spirv_version_1_6);

    auto result = compiler.CompileGlslToSpv(source.data(), source.size(), kind, "shader.glsl", options);
    if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
      throw;
    }

    return { result.cbegin(), result.cend() };
  }
}