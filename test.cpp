#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>

// include headers for classes being tested
#include "basics.h"

using namespace std;


/*
	The outcome of each test case is described by this enum, which should make
	the result more obvious than if a boolean value was used in its place.
*/
enum TestResult { TR_PASS, TR_FAIL };

/*
	Helper macro to eliminate a lot of of code repetition. Macros aren't the best,
	but this is an easy way to get what we want.
*/

#define ASSERT_EQUALS(actual, expected)                                           \
    if (actual != expected) {                                                     \
        cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                \
             << "\tExpected '" << expected << "' but was '" << actual << "'" << endl; \
        return TR_FAIL;                                                           \
    }

#define ASSERT(condition)                                                         \
    if ((condition) == false) {                                                   \
        cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                \
             << "\tExpression '" << #condition << "' evaluated to false" << endl; \
        return TR_FAIL;                                                           \
    }

TestResult test_triple() {
	ASSERT_EQUALS(triple(1), 3);
	ASSERT_EQUALS(triple(5), 15);
	ASSERT_EQUALS(triple(0), 0);
	ASSERT_EQUALS(triple(33), 99);
	ASSERT_EQUALS(triple(-2), -6);
	ASSERT_EQUALS(triple(-123), -369);

    return TR_PASS;
}

TestResult test_absolute() {
    ASSERT_EQUALS(absolute(-3), 3);
    ASSERT_EQUALS(absolute(0), 0);
    ASSERT_EQUALS(absolute(-12), 12);
    ASSERT_EQUALS(absolute(3), 3);
    ASSERT_EQUALS(absolute(25), 25);
    ASSERT_EQUALS(absolute(-12.87), 12.87);
    ASSERT_EQUALS(absolute(3.0012), 3.0012);

    return TR_PASS;
}

TestResult test_min() {
    ASSERT_EQUALS(min(-3, 2), -3);
    ASSERT_EQUALS(min(0, 0), 0);
    ASSERT_EQUALS(min(0, 7), 0);
    ASSERT_EQUALS(min(5, 0), 0);
    ASSERT_EQUALS(min(29, 12), 12);
    ASSERT_EQUALS(min(-32, -87), -87);
    ASSERT_EQUALS(min(25, 92), 25);

    return TR_PASS;
}

TestResult test_max() {
    ASSERT_EQUALS(max(-3, 2), 2);
    ASSERT_EQUALS(max(0, 0), 0);
    ASSERT_EQUALS(max(0, 7), 7);
    ASSERT_EQUALS(max(5, 0), 5);
    ASSERT_EQUALS(max(29, 12), 29);
    ASSERT_EQUALS(max(-32, -87), -32);
    ASSERT_EQUALS(max(25, 92), 92);

    return TR_PASS;
}

TestResult test_round() {
    ASSERT_EQUALS(round(1.0), 1);
    ASSERT_EQUALS(round(5.1), 5);
    ASSERT_EQUALS(round(7.499), 7);
    ASSERT_EQUALS(round(2.51), 3);
    ASSERT_EQUALS(round(9.99), 10);
    ASSERT_EQUALS(round(-1.99), -2);
    ASSERT_EQUALS(round(-11.499), -11);

    return TR_PASS;
}


/*
This function collects up all the tests as a vector of function pointers. If you create your own
tests and want to be able to run them, make sure you add them to the `tests` vector here.
*/
vector<TestResult (*)()> generateTests() {
    vector<TestResult (*)()> tests;

    tests.push_back(&test_triple);
    tests.push_back(&test_absolute);
    tests.push_back(&test_min);
    tests.push_back(&test_max);
    tests.push_back(&test_round);

    return tests;
}

int main(int argc, char const* argv[]) {
    // If one or more test numbers are passed as command-line parameters, execute them
    vector<TestResult (*)()> tests_to_run = generateTests();
    unsigned int pass_count = 0;
    unsigned int fail_count = 0;
    unsigned int run_count = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            unsigned int test_num = atoi(argv[i]);
            if (test_num > tests_to_run.size()) {
                cout << "ERROR: unknown test case " << test_num << endl;
                continue;
            }
            // run the test
            ++run_count;
            TestResult result = tests_to_run[test_num]();
            if (result == TR_FAIL) {
                cout << "FAIL: Test " << test_num << " failed." << endl;
                ++fail_count;
            } else {
                cout << "PASS: Test " << test_num << " passed." << endl;
                ++pass_count;
            }
        }
    } else {
        // otherwise, run all tests
        // Make sure to update this section as you add more tests
        // Add the tests for the first task
        for (unsigned int t = 0; t < tests_to_run.size(); ++t) {
            ++run_count;
            TestResult result = tests_to_run[t]();
            if (result == TR_FAIL) {
                cout << "FAIL: Test " << t << " failed." << endl;
                ++fail_count;
            } else {
                cout << "PASS: Test " << t << " passed." << endl;
                ++pass_count;
            }
        }
    }
    cout << "\n-------------------------------------------------\n"
         << "Total Run: " << run_count << "\n"
         << "Total PASSED: " << pass_count << "\n"
         << "Total FAILED: " << fail_count << "\n"
         << "-------------------------------------------------\n" << endl;

    // Return 0 if everything was OK
    return 0;
}
