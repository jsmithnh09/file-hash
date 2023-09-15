##########################################
# Rudimentary test executables.
##########################################

enable_testing()
add_executable(testUUID testUUID.c)
target_include_directories(testUUID PUBLIC ../include)
target_link_libraries(testUUID PRIVATE uuid)

add_test(uuid_test testUUID)
set_tests_properties(uuid_test PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")

add_executable(testHash testHash.c)
target_include_directories(testHash PUBLIC ../include)
target_link_libraries(testHash PRIVATE hashers)

add_test(hash_test testHash)
set_tests_properties(hash_test PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")