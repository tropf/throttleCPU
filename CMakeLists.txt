cmake_minimum_required(VERSION 3.0)

project(throttleCPU)

add_executable(throttleCPU
    throttleCPU.cpp
)

install(TARGETS throttleCPU DESTINATION /usr/bin/)
install(FILES throttleCPU.service DESTINATION /etc/systemd/system/)
install(FILES throttleCPU.conf DESTINATION /etc/)
