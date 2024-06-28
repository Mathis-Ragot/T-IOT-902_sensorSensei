#include "unity.h"
#include "optional.hpp"

void test_optional_basic() {
    tl::optional<int> opt;
    TEST_ASSERT_EQUAL(opt.has_value(), false);
    opt = 42;
    TEST_ASSERT_EQUAL(opt.has_value(), true);
    TEST_ASSERT_EQUAL(*opt, 42);
    opt.reset();
    TEST_ASSERT_EQUAL(opt.has_value(), false);
    TEST_ASSERT_EQUAL(opt.value_or(42), 42);
    TEST_ASSERT_EQUAL(opt.operator*(), 42);
    opt = 42;
    TEST_ASSERT_EQUAL(opt.value_or(0), 42);
    TEST_ASSERT_NOT_EMPTY(&opt.value());
    try {
        tl::optional<int> opt2;
        opt2.value();
    } catch (tl::bad_optional_access& e) {
        TEST_ASSERT_EQUAL_STRING(e.what(), "Optional has no value");
    }

    tl::detail::optional_storage_base<int> storage;
    TEST_ASSERT_EQUAL(storage.m_has_value, false);

}