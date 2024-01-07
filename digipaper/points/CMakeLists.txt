add_executable(digiPaper points.cpp)
target_include_directories(digiPaper PRIVATE ${GLFW3_INCLUDE_DIRS} ${IMGUI_INCLUDE_DIRS} ${STB_INCLUDE_DIRS})
target_link_libraries(digiPaper PRIVATE glfw imgui::imgui)