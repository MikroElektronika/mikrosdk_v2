Example is meant for testing if all modules build together.

This has been noticed on XC8 compilers for a specific case:

+ All modules have same function names (hal_ll_get_specifics)
+ When two or more modules are used, the compiler can not find appropriate reference to function

We shall run this test on all compilers just in case.

TODOs in code if new modules are added:

+ ./deploy/static_naming_convention_f/CMakeLists.txt
  + Call find_include_package(package_list module_list TODO_NEW_PACKAGE_NAME)
+ ./deploy/static_naming_convention_f/main.c
  + Ifdef new module header include and function call
