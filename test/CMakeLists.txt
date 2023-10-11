##########################################
# Rudimentary test executables.
##########################################

enable_testing()

#-------------------------
# UUIDRAND/UUIDSPACE
#-------------------------
add_executable(testUUID testUUID.c)
target_include_directories(testUUID PUBLIC ../include)
target_link_libraries(testUUID PRIVATE uuid)

add_test(uuid_test testUUID)
set_tests_properties(uuid_test PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")


#-------------------------
# FILEHASH
#-------------------------
add_executable(testHash testHash.c)
target_include_directories(testHash PUBLIC ../include)
target_link_libraries(testHash PRIVATE hashers)

add_test(hash_test testHash)
set_tests_properties(hash_test PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")


#-------------------------
# BLOWFISH
#-------------------------
add_executable(testBlowfish testBlowfish.c ../src/blowfish/blowfish.c)
target_include_directories(testBlowfish PUBLIC ../src/blowfish)
add_test(blowfish_test testBlowfish)
set_tests_properties(blowfish_test PROPERTIES PASS_REGULAR_EXPRESSION "SUCCESS")
