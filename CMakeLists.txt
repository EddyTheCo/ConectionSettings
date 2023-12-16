cmake_minimum_required(VERSION 3.24)

include(${CMAKE_CURRENT_BINARY_DIR}/local_conf.cmake OPTIONAL)
include(FetchContent)
FetchContent_Declare(
	ccommon
	GIT_REPOSITORY https://github.com/EddyTheCo/Common.git
        GIT_TAG v0.1.1
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
	qclient
	GIT_REPOSITORY https://github.com/EddyTheCo/Qclient-IOTA.git
        GIT_TAG develop
	FIND_PACKAGE_ARGS 0.2 CONFIG
	)
FetchContent_MakeAvailable(qclient)

FetchContent_Declare(
	qclientMQTT
	GIT_REPOSITORY https://github.com/EddyTheCo/QclientMqtt-IOTA.git
        GIT_TAG develop
	FIND_PACKAGE_ARGS 0.2 CONFIG
	)
FetchContent_MakeAvailable(qclientMQTT)

option(USE_QML "Create QML types and modules" ON)
if(USE_QML)
    FetchContent_Declare(
            EstervDesigns
            GIT_REPOSITORY https://github.com/EddyTheCo/MyDesigns.git
            GIT_TAG develop
            FIND_PACKAGE_ARGS 1.0 CONFIG
        )
    FetchContent_MakeAvailable(EstervDesigns)
    find_package(Qt6 COMPONENTS Core Gui Quick)
else()
    find_package(Qt6 COMPONENTS Core)
endif()

if (Qt6_FOUND)
	qt_standard_project_setup()
        add_library(nodeConnection src/nodeConnection.cpp include/nodeConnection.hpp)
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
                IMPORT_PATH ${CMAKE_BINARY_DIR} ${CMAKE_INSTALL_LIBDIR}
		)

        add_library(${PROJECT_NAME}::nodeConnectionplugin ALIAS nodeConnectionplugin)
        target_compile_definitions(nodeConnection PRIVATE WINDOWS_NCONN USE_QML)
        target_link_libraries(nodeConnection PUBLIC Qt6::Gui Qt6::Quick)
        target_link_libraries(nodeConnection PUBLIC EstervDesigns::SimpleStyle
            $<$<STREQUAL:$<TARGET_PROPERTY:EstervDesigns::SimpleStyle,TYPE>,STATIC_LIBRARY>:EstervDesigns::SimpleStyleplugin>
                )
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
        target_link_libraries(nodeConnection PUBLIC qclient qclientMQTT)

        target_include_directories(nodeConnection PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Esterv/${PROJECT_NAME}>")


        install(TARGETS nodeConnection
            EXPORT ${PROJECT_NAME}-config
                DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT nodeConnection
		)
	install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
                DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Esterv/${PROJECT_NAME}
                COMPONENT nodeConnection
		)

            install(EXPORT ${PROJECT_NAME}-config
                FILE ${PROJECT_NAME}-config.cmake
                DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Esterv
                NAMESPACE ${PROJECT_NAME}::
                COMPONENT ${PROJECT_NAME}
            )
            include(CMakePackageConfigHelpers)
            configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
                    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Esterv
                    )
            write_basic_package_version_file(
                    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
                    VERSION ${VERSION}
                    COMPATIBILITY SameMajorVersion
                    )
            install(FILES
                    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
                    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Esterv
                    )
            export(EXPORT ${PROJECT_NAME}-config
                    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
                    )

	if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
            add_subdirectory(examples)
		set(CPACK_PACKAGE_CONTACT "estervtech")
		include(CTest)
		set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-v${SEMVER}-${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_VERSION}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_CXX_COMPILER_ID}")
		if(USE_THREADS)
			set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-MThread")
		endif(USE_THREADS)
		include(CPack)
	endif()

endif(Qt6_FOUND)


if(BUILD_DOCS)
	get_target_property(build_docs cmake_build_docs SOURCES)
	include(${build_docs})
endif()

