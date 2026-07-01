include(FetchContent)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	master
)
FetchContent_MakeAvailable(glm)

message("${glm_SOURCE_DIR}")
target_sources(
	${PROJECT_NAME} PUBLIC
	FILE_SET CXX_MODULES 
	BASE_DIRS ${glm_SOURCE_DIR}
	FILES
		"${glm_SOURCE_DIR}/glm/glm.cppm"
)