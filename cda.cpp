/**
 * Author: Asa Dillahunty
 * 
 * CS201 Programming Project
 * 
 * This program is written to implement
 * learned algorithms in CS201
 *
 * CDA stands for Circular Dynamic Array
 */
#include <iostream>

template <class T>
class CDA {
	private:
		int size;
		int cap;
		int head;
		T *list; 
		
		/*
		 * If I get rid of the need for the if statement
		 * I could save time
		 * 
		 * To do so just check when plausible for index to 
		 * be out of bounds
		 */
		int relativeIndex(int i) {
			
			if (i<0 || i>this->size-1) {
				throw;
			}
			else {
				return (this->head+i)%this->cap;
			}
		}

		void upsize() {
			
			int newCap = this->cap*2;			
			T *newList = new T[newCap];

			for (int i=0;i<size;i++) {
				newList[i] = this->list[this->relativeIndex(i)];
			}
			
			delete [] this->list;

			this->list=newList;
			this->cap=newCap;
			this->head=0;
		}

		void downsize() {
			if (size==0) return;
			
			int newCap = this->cap/2;
			T *newList = new T[newCap];

			for (int i=0;i<size;i++) {
				newList[i] = this->list[this->relativeIndex(i)];
			}

			delete [] this->list;

			this->list=newList;
			this->cap=newCap;
			this->head=0;
		}

		
	public:
		CDA() {
			this->size=0;
			this->cap=2;
			this->head=0;
			this->list=new T[cap];
		}

		CDA(int s) {
			this->size=0;
			this->cap=s;
			this->head=0;
			this->list=new T[cap];
		}

		~CDA() {
			delete [] this->list;
		}

		T& operator[](int i) {
			return this->list[this->relativeIndex(i)];
		}


		void addEnd(T data) {
			
			if (this->size==this->cap) {
				this->upsize();
				this->addEnd(data);
			}
			else {
				this->list[(this->head+this->size)%this->cap]=data;
				this->size++;
			}
		}

		void addFront(T data) {
			
			if (this->size==this->cap) {
				this->upsize();
				this->addFront(data);
			}
			else {
				this->head = (this->head+this->cap-1)%this->cap;
				this->list[this->head]=data;
				this->size++;
			}
		}

		/* Should I free the deleted Element??? */
		void delEnd() {
			
			T data = this->list[this->relativeIndex(this->size-1)];
			this->size--;
			
			if (((double) this->size)/((double) this->cap) <= .25) {
				this->downsize();
			}
		}

		void delFront() {

			T data = this->list[this->head];
			this->head=(this->head+1)%this->cap;
			this->size--;

			if (((double) this->size)/((double) this->cap) <= .25) {
				this->downsize();
			}
		}
		
		int length() {
			return this->size;
		}

		int capacity() {
			return this->cap;
		}

		void printList() {
			for (int i=0;i<size;i++) {
				std::cout << this->list[this->relativeIndex(i)] << std::endl;
			}
		}
};

int main(int argc, char const *argv[]) {
	std::cout << "Hello World!" << std::endl;
	
	CDA<std::string> list;
	
	list.addEnd("first");
	
	for (int i=0;i<1;i++) {
		std::cout << list[i] << std::endl;
	}

	list.addEnd("second");
	
	for (int i=0;i<2;i++) {
		std::cout << list[i] << std::endl;
	}
	
	list.addFront("third");

	for (int i=0;i<3;i++) {
		std::cout << list[i] << std::endl;
	}
	
	return 0;
}
