# CMake generated Testfile for 
# Source directory: /Users/dmorton/projects/lithium
# Build directory: /Users/dmorton/projects/lithium/xcode
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(test "/Users/dmorton/projects/lithium/test/Debug/runUnitTests")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(test "/Users/dmorton/projects/lithium/test/Release/runUnitTests")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(test "/Users/dmorton/projects/lithium/test/MinSizeRel/runUnitTests")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(test "/Users/dmorton/projects/lithium/test/RelWithDebInfo/runUnitTests")
else()
  add_test(test NOT_AVAILABLE)
endif()
subdirs(lib/googletest)
