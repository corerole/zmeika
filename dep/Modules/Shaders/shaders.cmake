set(APP_SHADERS_DIR "${CMAKE_CURRENT_LIST_DIR}")

find_package(Vulkan REQUIRED COMPONENTS shaderc_combined)

target_sources(
	${PROJECT_NAME} PUBLIC
	FILE_SET CXX_MODULES 
	BASE_DIRS ${APP_SHADERS_DIR}
	FILES
		"${APP_SHADERS_DIR}/shaders_compiler.cppm"
		"${APP_SHADERS_DIR}/vk_shader_iface.cppm"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::shaderc_combined)