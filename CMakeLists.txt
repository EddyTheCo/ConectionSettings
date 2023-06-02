cmake_minimum_required(VERSION 3.16)
project(IOTA VERSION 0.1 LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick)


qt6_add_qml_module(nodeConection
	URI  nodeConection
	VERSION 1.0
	SOURCES
	src/nodeConnection.cpp include/nodeConnection.hpp
	QML_FILES
	qml/Node_Connections.qml
	OUTPUT_TARGETS out_targets_var
	RESOURCE_PREFIX
	"/esterVtech.com/imports"
	NO_IMPORT_SCAN
	IMPORTS MyDesigns
	IMPORT_PATH
	${CMAKE_BINARY_DIR}/_deps/mydesigns-build
	OUTPUT_DIRECTORY
	${CMAKE_CURRENT_BINARY_DIR}/nodeConection
	)

target_link_libraries(nodeConection PUBLIC Qt6::Gui Qt6::Quick)

target_include_directories(nodeConection PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	"$<INSTALL_INTERFACE:include>")


include(FetchContent)

FetchContent_Declare(
	qclient
	GIT_REPOSITORY git@github.com:EddyTheCo/Qclient-IOTA.git
	GIT_TAG v0.0.1
	FIND_PACKAGE_ARGS 0 CONFIG
	)
FetchContent_MakeAvailable(qclient)

FetchContent_Declare(
	qclientMQTT
	GIT_REPOSITORY git@github.com:EddyTheCo/QclientMqtt-IOTA.git
	GIT_TAG v0.0.1
	FIND_PACKAGE_ARGS 0 CONFIG
	)
FetchContent_MakeAvailable(qclientMQTT)

FetchContent_Declare(
	Designs
	GIT_REPOSITORY https://github.com/EddyTheCo/MyDesigns.git
	GIT_TAG v0.0.1
	FIND_PACKAGE_ARGS 0 CONFIG
	)
FetchContent_MakeAvailable(Designs)

target_link_libraries(nodeConection PUBLIC MyDesigns qclient qclientMQTT)

target_compile_definitions(nodeConection
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

install(TARGETS nodeConection ${out_targets_var} EXPORT nodeConectionTargets DESTINATION bin )
install(DIRECTORY include/ DESTINATION include/)

install(EXPORT nodeConectionTargets
	FILE nodeConectionTargets.cmake
	DESTINATION lib/cmake/nodeConection
	)
include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/nodeConectionConfig.cmake"
	INSTALL_DESTINATION "lib/cmake/nodeConection"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
	)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/nodeConectionConfigVersion.cmake"
	VERSION "0.1.1.0"
	COMPATIBILITY AnyNewerVersion
	)
install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/nodeConectionConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/nodeConectionConfigVersion.cmake
	DESTINATION lib/cmake/nodeConection
	)
export(EXPORT nodeConectionTargets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/nodeConectionTargets.cmake"
	)
list(APPEND QML_IMPORT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/qml ${CMAKE_CURRENT_BINARY_DIR}/)
set(QML_IMPORT_PATH ${QML_IMPORT_PATH} CACHE STRING "" FORCE)

