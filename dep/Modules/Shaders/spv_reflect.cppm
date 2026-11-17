module;

#ifndef __cplusplus
    #define __cplusplus
#endif

#ifndef SPIRV_REFLECT_DISABLE_CPP_BINDINGS
    #define SPIRV_REFLECT_DISABLE_CPP_BINDINGS
#endif

#include <spirv_reflect.h>

export module spv_reflect;
import vulkan;
import std;


std::string operator+(const char* a, std::string_view b) {
    return std::string(a) + std::string(b);
}

std::string operator+(const std::string& a, std::string_view b) {
    return a + std::string(b);
}

export namespace spv_reflect {
    using ::SpvReflectResult;
    constexpr std::string_view get_Result_name(SpvReflectResult res) noexcept {
        switch(res) {
            case SpvReflectResult::SPV_REFLECT_RESULT_SUCCESS : { return "SPV_REFLECT_RESULT_SUCCESS"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_NOT_READY : { return "SPV_REFLECT_RESULT_NOT_READY"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_PARSE_FAILED : { return "SPV_REFLECT_RESULT_ERROR_PARSE_FAILED"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_ALLOC_FAILED : { return "SPV_REFLECT_RESULT_ERROR_ALLOC_FAILED"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_RANGE_EXCEEDED : { return "SPV_REFLECT_RESULT_ERROR_RANGE_EXCEEDED"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_NULL_POINTER : { return "SPV_REFLECT_RESULT_ERROR_NULL_POINTER"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_INTERNAL_ERROR : { return "SPV_REFLECT_RESULT_ERROR_INTERNAL_ERROR"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_COUNT_MISMATCH : { return "SPV_REFLECT_RESULT_ERROR_COUNT_MISMATCH"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_ELEMENT_NOT_FOUND : { return "SPV_REFLECT_RESULT_ERROR_ELEMENT_NOT_FOUND"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_CODE_SIZE : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_CODE_SIZE"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_MAGIC_NUMBER : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_MAGIC_NUMBER"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_UNEXPECTED_EOF : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_UNEXPECTED_EOF"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_ID_REFERENCE : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_ID_REFERENCE"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_SET_NUMBER_OVERFLOW : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_SET_NUMBER_OVERFLOW"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_STORAGE_CLASS : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_STORAGE_CLASS"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_RECURSION : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_RECURSION"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_INSTRUCTION : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_INSTRUCTION"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_UNEXPECTED_BLOCK_DATA : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_UNEXPECTED_BLOCK_DATA"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_BLOCK_MEMBER_REFERENCE : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_BLOCK_MEMBER_REFERENCE"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_ENTRY_POINT : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_ENTRY_POINT"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_EXECUTION_MODE : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_INVALID_EXECUTION_MODE"; }
            case SpvReflectResult::SPV_REFLECT_RESULT_ERROR_SPIRV_MAX_RECURSIVE_EXCEEDED : { return "SPV_REFLECT_RESULT_ERROR_SPIRV_MAX_RECURSIVE_EXCEEDED"; }
        }
    }

    template<typename T> concept ArrayLike = requires (T a) {
        { a.data() } -> std::same_as<std::add_pointer_t<typename T::value_type>>;
        { a.size() } -> std::same_as<typename T::size_type>;
    };

    struct ShaderModule {
        using ShaderModuleCreateFlags = vk::Flags<SpvReflectModuleFlagBits>;

        private:
            SpvReflectShaderModule module;

        public:
            ShaderModule(const ArrayLike auto& shader_data, ShaderModuleCreateFlags flags = SpvReflectModuleFlagBits::SPV_REFLECT_MODULE_FLAG_NONE) { 
                using data_cont = std::remove_cvref_t<decltype(shader_data)>;
                auto p = static_cast<const void*>(shader_data.data());
                auto s = shader_data.size() * sizeof(typename data_cont::value_type);
                auto res = spvReflectCreateShaderModule2(ShaderModuleCreateFlags::MaskType(flags), s, p, &module);
                if(res != SpvReflectResult::SPV_REFLECT_RESULT_SUCCESS) {
                    throw std::runtime_error(std::string{} + "failed to load ShaderModule! | " + spv_reflect::get_Result_name(res) + "\n");
                }
            }

            ~ShaderModule() {
                spvReflectDestroyShaderModule(&module);
            }
        
        public:
            auto EnumerateDescriptorBindings() {
                std::uint32_t bindingCount = 0;
                auto res1 = spvReflectEnumerateDescriptorBindings(&module, &bindingCount, nullptr);
                if(res1 != SpvReflectResult::SPV_REFLECT_RESULT_SUCCESS) {
                    throw std::runtime_error(std::string{} + "error | " + spv_reflect::get_Result_name(res1) + "\n");
                }
                std::vector<SpvReflectDescriptorBinding*> bindings(bindingCount);
                auto res2 = spvReflectEnumerateDescriptorBindings(&module, &bindingCount, bindings.data());
                if(res2 != SpvReflectResult::SPV_REFLECT_RESULT_SUCCESS) {
                    throw std::runtime_error(std::string{} + "error | " + spv_reflect::get_Result_name(res2) + "\n");
                }
                return bindings;
            }

            std::string GetSource() {
                if(!module.source_file) { return {}; };
                return std::string(module.source_file);
            }
    };
}



