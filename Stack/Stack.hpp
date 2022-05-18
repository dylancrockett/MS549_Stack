#ifndef MS449_STACK
#define MS449_STACK

#include <iostream>
#include <string>

namespace stack {
	//generic stack exception
	class StackException : public std::exception {
		const char* what() const throw ()
		{
			return "A generic stack exception.";
		}
	};

	//thrown if the stack is empty and peak or pop is called
	class StackEmpty : public StackException {
		private:
			std::string message;

		public:
			StackEmpty(std::string message = "The stack is empty.") {
				this->message = message;
			}

			const char* what() const throw ()
			{
				return this->message.c_str();
			}
	};

	//thrown if the stack is full and push is called
	class StackFull : public StackException {
		const char* what() const throw ()
		{
			return "The Stack is currently full and can not accept another item.";
		}
	};

	template <typename T> class Stack {
		private:
			//the number of elements the stack can contain
			int size;

			//the index of the top element in the stack, is zero if the stack is empty
			int current = 0;

			// the container which contains the values of the stack, will be null if the stack is empty
			T* container = nullptr;

		public:
			Stack(int size = 10) {
				//initalize values
				this->size = size;
				this->current = 0;
				this->container = nullptr;
			}

			~Stack() {
				//delete the container if it exists (no mem leak)
				if (this->container != nullptr) delete this->container;
			}

			//push a value onto the stack
			void push(T item) throw() {
				//for the condition that the stack is full
				if (current + 1 >= this->size) {
					throw StackFull();
				}

				//for the condition that the stack is empty
				if (this->container == nullptr) {
					this->container = new T[size];
				}
				//if the stack is not empty increment the current index
				else {
					this->current += 1;
				}

				//add the item to the array
				this->container[current] = item;
			}

			//peak at the current top value in the stack
			T peak() throw() {
				//for the condition that the stack is empty
				if (this->container == nullptr) {
					throw StackEmpty("Can't call Peak on an empty stack.");
				}

				//return the value at the top of the stack
				return this->container[this->current];
			}

			//pop remove the value from the top of the stack and remove it from the stack
			T pop() throw() {
				//for the condition that the stack is empty
				if (this->container == nullptr) {
					throw StackEmpty("Can't call Pop on an empty stack.");
				}

				//store the current top value before removing it
				T item = this->container[this->current];

				//if there is only 1 item left in the stack
				if (this->current == 0) {
					//delete the container and set it to nullptr
					delete this->container;
					this->container = nullptr;

					//return the old top value
					return item;
				}

				//decrement the value of current to point to the new top value of the stack
				this->current -= 1;

				//return the old top value
				return item;
			}
	};
}

#endif // !
