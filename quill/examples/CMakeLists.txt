add_executable(example_backtrace example_backtrace.cpp)
target_link_libraries(example_backtrace quill)

add_executable(example_configure_backend example_configure_backend.cpp)
target_link_libraries(example_configure_backend quill)

add_executable(example_console_colours example_console_colours.cpp)
target_link_libraries(example_console_colours quill)

add_executable(example_console_colours_with_custom_formatter example_console_colours_with_custom_formatter.cpp)
target_link_libraries(example_console_colours_with_custom_formatter quill)

add_executable(example_custom_clock example_custom_clock.cpp)
target_link_libraries(example_custom_clock quill)

add_executable(example_custom_clock_advanced example_custom_clock_advanced.cpp)
target_link_libraries(example_custom_clock_advanced quill)

add_executable(example_custom_console_colours example_custom_console_colours.cpp)
target_link_libraries(example_custom_console_colours quill)

add_executable(example_trivial example_trivial.cpp)
target_link_libraries(example_trivial quill)

add_executable(example_logging_to_file example_logging_to_file.cpp)
target_link_libraries(example_logging_to_file quill)

add_executable(example_multiple_handlers example_multiple_handlers.cpp)
target_link_libraries(example_multiple_handlers quill)

add_executable(example_signal_handler example_signal_handler.cpp)
target_link_libraries(example_signal_handler quill)

add_executable(example_stdout_multiple_formatters example_stdout_multiple_formatters.cpp)
target_link_libraries(example_stdout_multiple_formatters quill)

add_executable(example_custom_formatter example_custom_formatter.cpp)
target_link_libraries(example_custom_formatter quill)

add_executable(example_custom_formatter_thread_name example_custom_formatter_thread_name.cpp)
target_link_libraries(example_custom_formatter_thread_name quill)

add_executable(example_custom_handler example_custom_handler.cpp)
target_link_libraries(example_custom_handler quill)

add_executable(example_daily_file_rotation example_daily_file_rotation.cpp)
target_link_libraries(example_daily_file_rotation quill)

add_executable(example_file_rotation example_file_rotation.cpp)
target_link_libraries(example_file_rotation quill)

add_executable(example_filters example_filters.cpp)
target_link_libraries(example_filters quill)

add_executable(example_handler_log_levels example_handler_log_levels.cpp)
target_link_libraries(example_handler_log_levels quill)

add_executable(example_json_structured_log example_json_structured_log.cpp)
target_link_libraries(example_json_structured_log quill)

add_executable(example_trivial_system_clock example_trivial_system_clock.cpp)
target_link_libraries(example_trivial_system_clock quill)

add_executable(example_user_defined_types example_user_defined_types.cpp)
target_link_libraries(example_user_defined_types quill)