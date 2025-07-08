add_library(Core STATIC 
                "${CMAKE_SOURCE_DIR}/src/Core/Object/Object.cpp"
                )



target_include_directories(Core PRIVATE 
                                "${CMAKE_SOURCE_DIR}/includes/Core"
                                )  
