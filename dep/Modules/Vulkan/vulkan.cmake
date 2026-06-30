set(VULKAN_DIR "${CMAKE_CURRENT_LIST_DIR}")

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

target_sources(
	${PROJECT_NAME} PUBLIC
	FILE_SET CXX_MODULES 
	BASE_DIRS ${VULKAN_DIR}
	FILES
		"${VULKAN_DIR}/vulkan.cppm"
		"${VULKAN_DIR}/vulkan_video.cppm"
		"${VULKAN_DIR}/vulkan_helpers.cppm"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Vulkan::Vulkan
)