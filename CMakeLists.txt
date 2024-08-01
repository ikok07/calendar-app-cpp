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
        models/note/Note.h
        models/coordinates/Coordinates.cpp
        models/coordinates/Coordinates.h
        models/request/Request.cpp
        models/request/Request.h
        models/request/BasicResponse.cpp
        models/request/BasicResponse.h
        models/responses/fetch_time/FetchTimeResponse.cpp
        models/responses/fetch_time/FetchTimeResponse.h
        models/bodies/FriendlyDateBody.h
        models/responses/friendly_date/FriendlyDateResponse.cpp
        models/responses/friendly_date/FriendlyDateResponse.h
)

find_package(unofficial-curlpp CONFIG REQUIRED)
target_link_libraries(calendar_app_cpp PRIVATE unofficial::curlpp::curlpp)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(calendar_app_cpp PRIVATE nlohmann_json::nlohmann_json)
