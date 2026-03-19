get_filename_component(CHAPTER_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB SOURCES "*.cpp")
foreach(SOURCE ${SOURCES})
    get_filename_component(STEM ${SOURCE} NAME_WE)
    set(TARGET_NAME ${CHAPTER_DIR}_${STEM})
    add_executable(${TARGET_NAME} ${SOURCE})
    target_link_libraries(${TARGET_NAME} Threads::Threads)
    set_target_properties(${TARGET_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CHAPTER_DIR})

    # C++20 files
    if(SOURCE MATCHES "jthread")
        set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 20)
    endif()
endforeach()
