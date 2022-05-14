#ifndef MS449_TESTING
#define MS449_TESTING

#include <iostream>
#include <string>
#include <vector>
#include <functional>

namespace testing {
	using namespace std;

	enum BoolResult {
		TRUE = 0,
		FALSE = 1,
	};

	class TestResult {
		public:
			//name of the test which the result came from
			string name;

			//if the test was passed
			bool passed;

			//constructor
			TestResult(string name, bool passed) {
				this->name = name;
				this->passed = passed;
			}
	};

	class UnitTest {
		private:
			//name of the unit testing session
			string name;

			//list of test results
			vector<TestResult> results;

		public:
			//constructor
			UnitTest(string name = "Unit Test") {
				this->name = name;
			}

			//logging function
			void LOG(string message, string testName = "") {
				cout << "[" << this->name << "]" << (testName.empty() ? "" : ("(" + testName + ")")) << ": " << message << endl;
			}

			//assert the value provided is true or false
			void ASSERT(string name, bool value, BoolResult result = TRUE) {
				switch (result) {
					case TRUE:
						results.push_back(TestResult(name, value == true));
						return;
					case FALSE:
						results.push_back(TestResult(name, value == false));
				}
			}

			//assert the value returned by the function provided is true or false
			void ASSERT(string name, function<bool()> func, BoolResult result = TRUE) {
				try {
					bool funcValue = func();

					switch (result) {
					case TRUE:
						results.push_back(TestResult(name, funcValue == true));
						return;
					case FALSE:
						results.push_back(TestResult(name, funcValue == false));
					}
				}
				catch (const std::exception& e) {
					this->LOG("Unhandled Exception: " + *e.what(), name);
					results.push_back(TestResult("[EXCEPTION]" + name, false));
				}
			}

			//check if the unit test has passed given the current results
			bool TEST_PASSED() {
				for (auto result : this->results) {
					if (!result.passed) return false;
				}

				return true;
			}

			//log UnitTest results
			void LOG_RESULTS() {
				cout << "+-" << string(this->name.length(), '-') << "---------+" << endl;
				cout << "| " << this->name						 << " Results |" << endl;
				cout << "+-" << string(this->name.length(), '-') << "---------+" << endl;
				cout << endl;
				
				for (int i = 0; i < this->results.size(); i++) {
					auto result = this->results[i];
					cout << "[#" << (i + 1) << ")[" << (result.passed ? "PASSED" : "FAILED") << "]: " << result.name << endl << endl;
				}

				//get number of tests
				int totalTests = this->results.size();
				int totalPassedTests = 0;

				for (auto result : this->results) {
					if (result.passed) totalPassedTests += 1;
				}

				cout << "|\\" << endl;
				cout << "|| <> RESULT <>" << endl;
				cout << "|| - " << (this->TEST_PASSED() ? "TEST PASSED" : "TEST FAILED") << endl;
				cout << "|| - " << totalPassedTests << "/" << totalTests << " Tests Passed" << endl;
				cout << "|/" << endl;
			}
	};
}

#endif