cmake_minimum_required(VERSION 2.8)

# Set project
project(ModConfig_Test C CXX)

# Set file list
file(GLOB PROJECT_SRCS 
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	)

file(GLOB TEST_TXT
	${CMAKE_CURRENT_SOURCE_DIR}/*.txt
	)
list(REMOVE_ITEM TEST_TXT ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt)

# Set dependences
set(PROJECT_DEPS modcfg)

install(FILES ${TEST_TXT}
	DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
	)

# Build test
foreach(TEST_FILE_PATH ${PROJECT_SRCS})
	# Get each file name
	get_filename_component(TEST_FILE_NAME ${TEST_FILE_PATH} NAME_WE)
	
	# Build executable
	add_executable(${TEST_FILE_NAME} ${TEST_FILE_PATH})
	set_target_properties(${TEST_FILE_NAME}
		PROPERTIES OUTPUT_NAME ${TEST_FILE_NAME}
		)
	target_link_libraries(${TEST_FILE_NAME} ${PROJECT_DEPS})

	# Install
	install(TARGETS ${TEST_FILE_NAME}
		RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
		)
endforeach()

