if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_WIN32_KHR)
endif()
set(GLFW_DIR "${CMAKE_CURRENT_LIST_DIR}")
target_sources(
	${PROJECT_NAME} PUBLIC
	FILE_SET CXX_MODULES 
	BASE_DIRS ${GLFW_DIR}
	FILES
		"${GLFW_DIR}/glfw_win32_window.cppm"
		"${GLFW_DIR}/madmap.cppm"
		"${GLFW_DIR}/glfw.cppm"
		"${GLFW_DIR}/glfw_enums.cppm"
)