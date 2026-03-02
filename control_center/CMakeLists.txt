cmake_minimum_required(VERSION 3.5)
project(control_center LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
  control_center.cpp
  websocket_client.cpp
  ipc_udp.cpp
  http.cpp
  uuid.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Find and link Boost (system), OpenSSL, CURL and Threads
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
find_package(Threads REQUIRED)

if(TARGET Boost::system)
  set(BOOST_LIBS Boost::system)
else()
  set(BOOST_LIBS ${Boost_LIBRARIES})
endif()

if(TARGET OpenSSL::SSL)
  set(OPENSSL_LIBS OpenSSL::SSL OpenSSL::Crypto)
else()
  set(OPENSSL_LIBS ${OPENSSL_LIBRARIES})
endif()

if(TARGET CURL::libcurl)
  set(CURL_LIBS CURL::libcurl)
else()
  set(CURL_LIBS ${CURL_LIBRARIES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${BOOST_LIBS} ${OPENSSL_LIBS} ${CURL_LIBS} Threads::Threads)

# Optional small test program (matches Makefile's "opus_test")
option(BUILD_OPUS_TEST "Build opus_test utility" OFF)
if(BUILD_OPUS_TEST AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/opus.cpp")
  add_executable(opus_test opus.cpp)
  target_include_directories(opus_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(opus_test PRIVATE opus speexdsp)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)