file(GLOB HEADERS "include/mos/history_plugin/*.hpp")
add_library( history_plugin
             history_plugin.cpp
             ${HEADERS} )

target_link_libraries( history_plugin chain_plugin mos_chain appbase )
target_include_directories( history_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
