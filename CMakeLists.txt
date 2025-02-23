cmake_minimum_required(VERSION 3.10)

project(MatchingEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(MatchingEngine/include)

add_executable(MatchingEngine
        MatchingEngine/src/Main.cpp
        MatchingEngine/src/Order.cpp
        MatchingEngine/src/Instrument.cpp
        MatchingEngine/src/OrderBook.cpp
        MatchingEngine/src/Utils.cpp
        MatchingEngine/src/InstrumentManager.cpp
        MatchingEngine/src/MatchingEngine.cpp
)