set(VK_CUBE_PWD "${CMAKE_CURRENT_LIST_DIR}")

target_sources(
	${PROJECT_NAME} PUBLIC
	FILE_SET CXX_MODULES 
	BASE_DIRS ${VK_CUBE_PWD}
	FILES
		"${VK_CUBE_PWD}/vkCube.cppm"
		"${VK_CUBE_PWD}/vkCube_shaders_data.cppm"
		"${VK_CUBE_PWD}/vkCube_shaders_sources.cppm"
		"${VK_CUBE_PWD}/vkCube_data.cppm"
)