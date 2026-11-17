module;

#include <shaderc/shaderc.hpp>

export module shaders_compiler;
import std;

namespace {
  constexpr std::string_view CompilationResult_to_Name(shaderc_compilation_status rc) {
    switch(rc) {
			case shaderc_compilation_status_success : { return "shaderc_compilation_status_success"; }
			case shaderc_compilation_status_invalid_stage : { return "shaderc_compilation_status_invalid_stage"; }
			case shaderc_compilation_status_compilation_error : { return "shaderc_compilation_status_compilation_error"; }
			case shaderc_compilation_status_internal_error : { return "shaderc_compilation_status_internal_error"; }
			case shaderc_compilation_status_null_result_object  : { return "shaderc_compilation_status_null_result_object"; }
			case shaderc_compilation_status_invalid_assembly  : { return "shaderc_compilation_status_invalid_assembly"; }
			case shaderc_compilation_status_validation_error  : { return "shaderc_compilation_status_validation_error"; }
			case shaderc_compilation_status_transformation_error  : { return "shaderc_compilation_status_transformation_error"; }
			case shaderc_compilation_status_configuration_error  : { return "shaderc_compilation_status_configuration_error"; }	
			default : { return "FIX ME!"; }
    }
		return "FIX ME!";
  }
}

export namespace shaders_compiler {
  using shaderc_shader_kind = ::shaderc_shader_kind;
  /* TODO */
  std::vector<unsigned> compile_shader(std::string_view source, shaderc_shader_kind kind) {
    shaderc::SpvCompilationResult result;
    try {
      shaderc::Compiler compiler;
      shaderc::CompileOptions options;
      options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_4);
      options.SetTargetSpirv(shaderc_spirv_version_1_6);
      constexpr int ShaderVersion = 460;
      constexpr shaderc_profile profile = shaderc_profile_core;
      options.SetForcedVersionProfile(ShaderVersion, profile);

      result = compiler.CompileGlslToSpv(source.data(), source.size(), kind, "shader.glsl", options);
      if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
        throw std::runtime_error(std::string(CompilationResult_to_Name(result.GetCompilationStatus())));
      }
    } catch(const std::exception& E) {
      std::cout << "Shader Compilation Fail  |  " << E.what() << std::endl;
			std::terminate();
    } catch(...) {
      std::cout << "Shader Compilation Fail!" << std::endl;
	  	std::terminate();
    }
    return { result.cbegin(), result.cend() };
  }
}