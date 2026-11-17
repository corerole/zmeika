set(APP_SHADERS_DIR "${CMAKE_CURRENT_LIST_DIR}")

set(SPIRV_REFLECT_STATIC_LIB ON CACHE BOOL "Build SPIRV-Reflect static lib" FORCE)

target_sources(
	${PROJECT_NAME} PUBLIC
	FILE_SET CXX_MODULES 
	BASE_DIRS ${APP_SHADERS_DIR}
	FILES
		"${APP_SHADERS_DIR}/shaders_compiler.cppm"
		"${APP_SHADERS_DIR}/spv_reflect.cppm"
		"${APP_SHADERS_DIR}/vk_shader_iface.cppm"
)

include(FetchContent)
FetchContent_Declare(
    spirv_reflect
    GIT_REPOSITORY https://github.com/KhronosGroup/SPIRV-Reflect.git
    GIT_TAG        vulkan-sdk-1.4.350.0
)
FetchContent_MakeAvailable(spirv_reflect)
target_compile_definitions(${PROJECT_NAME} PUBLIC SPIRV_REFLECT_USE_SYSTEM_SPIRV_H)

target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::shaderc_combined spirv-reflect-static)