# Build python module.

find_package(Python REQUIRED COMPONENTS Interpreter Development)


set(SOURCES
        pyModule.cpp
        )

include_directories(${PROJECT_SOURCE_DIR}/Include)

# Create python module.
add_library(pyImageSequence SHARED ${SOURCES})



#target_link_libraries(pyImageSequence ImageSequence)
target_link_libraries(pyImageSequence
        PRIVATE
        ImageSequence
        )

set_target_properties(pyImageSequence PROPERTIES
        # Remove lib prefix. This is a unix thing.
        PREFIX ""
        )

if(WIN32)
    # Windows uses .pyd extension for python modules.
    set_target_properties(pyImageSequence PROPERTIES
            SUFFIX ".pyd"
            )
endif()

target_include_directories(pyImageSequence
        PRIVATE
        ${pybind11_INCLUDE_DIR}

        SYSTEM
        ${Python_INCLUDE_DIRS}
        )


if(WIN32)
    set(PYTHON_INSTALL_LIB_PATH "lib${LIB_SUFFIX}/site-packages")
else()
    set(PYTHON_INSTALL_LIB_PATH "lib${LIB_SUFFIX}/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages")
endif()

message(STATUS "Python install paths is: " ${PYTHON_INSTALL_LIB_PATH})
install(TARGETS pyImageSequence
        LIBRARY DESTINATION ${PYTHON_INSTALL_LIB_PATH}
        )
