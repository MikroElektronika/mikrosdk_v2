#ifndef __UNIT_TEST_API__
#define __UNIT_TEST_API__

/**
 * Include section.
 */
#include <cstdio.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * Variables used in unit test.
 */
typedef enum unit_test_result {
    UNIT_TEST_SUCCESS = 0,
    UNIT_TEST_FAIL
} unit_test_result_t;

/**
 * Macros used in unit test.
 */
#define UNIT_TEST_ASSERT(expr) if (!(expr)) { return (UNIT_TEST_FAIL); } else {}

#define UNIT_TEST_ASSERT_STR_EQUAL(expected, actual) if (strcmp((expected), (actual)) != 0) { return UnitTestFailStr(expected, actual); } else {}

#define UNIT_TEST_ASSERT_UINT_EQUAL(expected, actual) if ((uint32_t)(expected) != (uint32_t)(actual)) { return UNIT_TEST_FAIL; } else {}

#define UNIT_TEST_ASSERT_UINT_DELTA(expected, actual, tolerance) \
    if(((actual) > (expected) + (tolerance)) || ((actual) + (tolerance) < (expected))) { return UNIT_TEST_FAIL; } else {}

#define UNIT_TEST_ASSERT_UINT_LESS UNIT_TEST_ASSERT_UINT_LT

#define UNIT_TEST_ASSERT_UINT_GREATER UNIT_TEST_ASSERT_UINT_GT

#define UNIT_TEST_ASSERT_UINT_LE(expected, actual) \
    if (expected <= actual) { return UNIT_TEST_FAIL; }

#define UNIT_TEST_ASSERT_UINT_GE(expected, actual) \
    if (expected >= actual) { return UNIT_TEST_FAIL; }

#define UNIT_TEST_ASSERT_UINT_LT(expected, actual) \
    if (expected < actual) { return UNIT_TEST_FAIL; }

#define UNIT_TEST_ASSERT_UINT_GT(expected, actual) \
    if (expected > actual) { return UNIT_TEST_FAIL; }

#define UNIT_TEST_ASSERT_UINT_RANGE(expected_lo, expected_hi, actual) \
    if (!(expected_lo <= actual >= expected_hi)) { return UNIT_TEST_FAIL; }

#define UNIT_TEST_ASSERT_SUCCESS(expr) UNIT_TEST_ASSERT_UINT_EQUAL(UNIT_TEST_SUCCESS, (expr))

#define UNIT_TEST_CHECK_RESULT(expr) if (UNIT_TEST_SUCCESS != (expr)) { return UNIT_TEST_FAIL; }

#define TEST_BEGIN printf_me("**TEST_BEGIN**\n");

#define TEST_END printf_me("**TEST_END**\n");

#define TEST_ASSERT_RESPONSE(expr) ((expr == UNIT_TEST_FAIL) ? "FAILED" : "SUCCESS")

/**
 * API used in unit test.
 */

/**
 * @brief Predefined test runner API.
 * @details API takes predefined function as parameter
 *          and checks its return value for success.
 * @note Takes following API as parameter:
 *       @b unit_test_result_t @b func(void);
 * @b Example
 * @code
 * unit_test_result_t func(void) {
 *     // API body
 *     return UNIT_TEST_SUCCESS;
 * }
 * ...
 * // API call
 * test_run(func);
 * ...
 * @endcode
 * @return Returns @ref unit_test_result_t
 */
unit_test_result_t test_run( unit_test_result_t (*test_func)(void) );

/**
 * @brief Comparing structure contents.
 * @details This function compares each structure member by member.
 *
 * @param struct1_addr : Pointer to a structure.
 * @param struct2_addr : Pointer to a structure.
 * @param struct1_size : Number of bytes of structure 1.
 * @param struct2_size : Number of bytes of structure 2.
 * @param expect_same: If @b true will return @b UNIT_TEST_SUCCESS if structs are same.
 * @param is_debug: If @b true will write specific output to Application Output window.
 * @returns unit_test_result_t 0: UNIT_TEST_SUCCESS
 *                             1: UNIT_TEST_FAIL
 * @b example
 * @code
 *     unit_test_result_t _err = UNIT_TEST_SUCCESS;
 *     _err = compare_structs((uint8_t *)&struct1,(uint8_t *)&struct2,sizeof(struct1),sizeof(struct2),false,false);
 * @endcode
 * @warning Structure padding is a concept in C that adds one or more empty bytes between the memory addresses
 * to align the data in memory. Padding may happen if there are structure members smaller than the machine word.
 */
unit_test_result_t struct_compare ( uint8_t *struct1, uint8_t *struct2,
                                    size_t s1_num_of_bytes, size_t s2_num_of_bytes,
                                    bool expect_same, bool is_debug );

/**
 * @brief Checks structure content.
 * @details This function chekcs if each structure member is @b 0.
 *
 * @param struct_addr : Pointer to a structure.
 * @param struct_size : Number of bytes of structure.
 * @param is_debug: If @b true will write specific output to Application Output window.
 * @returns unit_test_result_t 0: UNIT_TEST_SUCCESS
 *                             1: UNIT_TEST_FAIL
 * @b example
 * @code
 *     unit_test_result_t _err = UNIT_TEST_SUCCESS;
 *     _err = struct_is_empty((uint8_t *)&struct1,sizeof(struct1),false);
 * @endcode
 * @warning Structure padding is a concept in C that adds one or more empty bytes between the memory addresses
 * to align the data in memory. Padding may happen if there are structure members smaller than the machine word.
 */
unit_test_result_t struct_is_empty ( uint8_t * struct_addr, size_t struct_size, bool is_debug );

/**
 * @brief Comparing array contents.
 * @details This function compares each array member by member.
 *
 * @param array1_addr : Pointer to an array.
 * @param array2_addr : Pointer to an array.
 * @param array1_size : Number of bytes of array 1.
 * @param array2_size : Number of bytes of array 2.
 * @param expect_same: If @b true will return @b UNIT_TEST_SUCCESS if arrays are same.
 * @param is_debug: If @b true will write specific output to Application Output window.
 * @returns unit_test_result_t 0: UNIT_TEST_SUCCESS
 *                             1: UNIT_TEST_FAIL
 * @b example
 * @code
 *     unit_test_result_t _err = UNIT_TEST_SUCCESS;
 *     _err = compare_arrays((uint8_t *)&array1,(uint8_t *)&array2,sizeof(array1),sizeof(array2),false,false);
 * @endcode
 * @note Compares array of size - @b byte.
 */
unit_test_result_t array_compare ( uint8_t array1_addr[], uint8_t array2_addr[],
                                   size_t array1_size, size_t array2_size,
                                   bool expect_same, bool is_debug );

#endif // __UNIT_TEST_API__

/*-------------------- END --------------------*/
