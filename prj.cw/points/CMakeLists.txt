add_executable(prj.cw points.cpp)
target_include_directories(prj.cw PRIVATE ${GLFW3_INCLUDE_DIRS} ${IMGUI_INCLUDE_DIRS} ${STB_INCLUDE_DIRS})
target_link_libraries(prj.cw PRIVATE glfw imgui::imgui)