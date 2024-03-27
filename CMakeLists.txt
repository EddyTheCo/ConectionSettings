cmake_minimum_required(VERSION 3.24)

include(${CMAKE_CURRENT_BINARY_DIR}/local_conf.cmake OPTIONAL)
include(FetchContent)
FetchContent_Declare(
	ccommon
	GIT_REPOSITORY https://github.com/EddyTheCo/Common.git
	GIT_TAG use_IFW
	)
FetchContent_MakeAvailable(ccommon)
version_from_git(
	LOG       OFF
	TIMESTAMP "%Y%m%d%H%M%S"
	)
project(IotaNodeConn VERSION ${VERSION} DESCRIPTION "Methods to communicate with Iota nodes" LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(GNUInstallDirs)


FetchContent_Declare(
	IotaClient
	GIT_REPOSITORY https://github.com/EddyTheCo/Qclient-IOTA.git
	GIT_TAG use_IFW
	FIND_PACKAGE_ARGS 0.3 CONFIG
	)
FetchContent_MakeAvailable(IotaClient)

FetchContent_Declare(
	IotaMqttClient
	GIT_REPOSITORY https://github.com/EddyTheCo/QclientMqtt-IOTA.git
	GIT_TAG use_IFW
	FIND_PACKAGE_ARGS 0.3 CONFIG
	)
FetchContent_MakeAvailable(IotaMqttClient)

option(USE_QML "Create QML types and modules" ON)
if(USE_QML)
	find_package(Qt6 COMPONENTS Core Gui Quick)
else()
	find_package(Qt6 COMPONENTS Core)
endif()

if (Qt6_FOUND)
	qt_standard_project_setup()
	add_library(nodeConnection src/nodeConnection.cpp include/nodeConnection.hpp)
	set_target_properties(nodeConnection PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION_MAJOR})
	add_library(${PROJECT_NAME}::nodeConnection ALIAS nodeConnection)
	if(USE_QML)
		qt6_add_qml_module(nodeConnection
			URI   Esterv.Iota.NodeConnection
			VERSION 1.0
			QML_FILES
			"qml/NodeConnectionSettings.qml"
			OUTPUT_TARGETS out_targets_var
			RESOURCE_PREFIX
			"/esterVtech.com/imports"
			OUTPUT_DIRECTORY
			${CMAKE_BINARY_DIR}/Esterv/Iota/NodeConnection
			IMPORT_PATH ${CMAKE_BINARY_DIR} 
			)

		add_library(${PROJECT_NAME}::nodeConnectionplugin ALIAS nodeConnectionplugin)
		target_compile_definitions(nodeConnection PRIVATE USE_QML)
		target_link_libraries(nodeConnection PUBLIC Qt6::Gui Qt6::Quick)
		install(TARGETS ${out_targets_var}
			EXPORT ${PROJECT_NAME}-config
			DESTINATION ${CMAKE_INSTALL_LIBDIR}
			COMPONENT nodeConnection
			)
		install(DIRECTORY ${CMAKE_BINARY_DIR}/Esterv/Iota/NodeConnection/
			DESTINATION ${CMAKE_INSTALL_LIBDIR}/Esterv/Iota
			COMPONENT nodeConnection
			)
		install(TARGETS nodeConnectionplugin
			EXPORT ${PROJECT_NAME}-config
			DESTINATION ${CMAKE_INSTALL_LIBDIR}/Esterv/Iota/NodeConnection
			COMPONENT nodeConnection
			)

	endif(USE_QML)
	target_link_libraries(nodeConnection PUBLIC IotaMqttClient::qclientMQTT IotaClient::qclient )
	target_link_libraries(nodeConnection PUBLIC Qt6::Core)
	target_compile_definitions(nodeConnection PRIVATE WINDOWS_NCONN)
	target_include_directories(nodeConnection PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Esterv/>")


	install(TARGETS nodeConnection
		EXPORT ${PROJECT_NAME}-config
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		COMPONENT nodeConnection
		)
	install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Esterv
		COMPONENT ${PROJECT_NAME}
		)

	build_exports()
	if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
		add_subdirectory(examples)
		build_cpack()
	endif(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

endif(Qt6_FOUND)


if(BUILD_DOCS)
	build_docs()
endif()

