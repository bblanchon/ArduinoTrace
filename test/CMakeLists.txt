add_executable(ArduinoTraceTest
	test.cpp
)

target_compile_features(ArduinoTraceTest
	PRIVATE
		cxx_std_11
)

include_directories(.)

add_test(ArduinoTraceTest ArduinoTraceTest)