cmake_minimum_required(VERSION 3.10)

project(MatchingEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(matching_engine/include)

add_executable(MatchingEngine
        matching_engine/src/main.cpp
        matching_engine/src/Order.cpp
        matching_engine/src/OrderBook.cpp
        matching_engine/src/Instrument.cpp
        matching_engine/src/MatchingEngine.cpp
)
