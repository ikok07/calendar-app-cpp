cmake_minimum_required(VERSION 3.28)
project(calendar_app_cpp)

set(CMAKE_CXX_STANDARD 23)

add_executable(calendar_app_cpp main.cpp
        models/option_list/OptionList.cpp
        models/option_list/OptionList.h
        models/option_handler/OptionHandler.cpp
        models/option_handler/OptionHandler.h
        models/utils/Utils.cpp
        models/utils/Utils.h
        models/note/Note.cpp
        models/note/Note.h)
