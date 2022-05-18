#ifndef MS449_STACK_TESTING
#define MS449_STACK_TESTING

#include <iostream>
#include <string>
#include <vector>
#include "Stack.hpp"
#include "Testing.hpp"

namespace stack_test {
	using namespace stack;
	using namespace testing;

	//test the Stack class to ensure it functions as expected
	inline void test() {
		//create a new unit test
		UnitTest test = UnitTest("Stack Datastructure Test");

		//set a size for the stack & create it
		int stackSize = 5;
		Stack<int> stack = Stack<int>(stackSize);

		test.assert<bool>("A StackEmpty exception is raised when calling Pop on an empty stack.", [&stack]() {
			try {
				stack.pop();
			}
			catch (StackEmpty& e) {
				return true;
			}

			return false;
		}, true);

		test.assert<bool>("A StackEmpty exception is raised when calling Peak on an empty stack.", [&stack]() {
			try {
				stack.peak();
			}
			catch (StackEmpty& e) {
				return true;
			}

			return false;
		}, true);

		//check that the stack can be filled with n items
		test.assert<bool>(("The stack set to a size " + std::to_string(stackSize) + " of can be filled with " + std::to_string(stackSize) + " items."), [&stack, &stackSize]() {
			for (int i = 0; i < stackSize; i++) {
				stack.push(i + 1);
			}

			return true;
		}, true);

		test.assert<bool>(("A StackFull exception is raised when calling Push on a full stack."), [&stack, &stackSize]() {
			try {
				stack.push(42);
			}
			catch (StackFull& e) {
				return true;
			}

			return false;
		}, true);

		test.assert<bool>(("A StackEmpty exception will be raised after all items have been removed from the list."), [&stack, &stackSize]() {
			try {
				for (int i = 0; i < 1000000000; i++) {
					stack.pop();
				}
			}
			catch (StackEmpty& e) {
				return true;
			}

			return false;
		}, true);

		test.assert<bool>(("An item can be added to an emptied stack."), [&stack, &stackSize]() {
			stack.push(42);
			return true;
		}, true);

		//log the results of the UnitTest
		test.log_results();
	}
}

#endif // !
