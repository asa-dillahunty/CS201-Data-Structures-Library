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
#include <string>

template <class T>
class CDA {
	private:
		int size;
		int cap;
		int head;
		T *list; 
	
		/**
		 * Increases the size of the internal array
		 * and copies all values over.
		 */
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

		/**
		 * Decreases the size of the internal array
		 * and copies all values over.
		 */
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

		/**
		 * Returns the real index when given the index relative to the head
		 * (Starting with the head of the array as index zero
		 *  and iterating from there)
		 *
		 *  @param index: the index relative to the head of the array
		 *  @return: returns the actual index for the internal array
		 */
		/*
		 * If I get rid of the need for the if statement
		 * I could save time
		 * 
		 * To do so just check when plausible for index to 
		 * be out of bounds, this should just be when the
		 * operator calls it
		 */
		int relativeIndex(int index) {
			if (index<0 || index>this->size-1) {
				std::cout << "\n\nCustom Error\n"; 
				std::string error = "Index " + std::to_string(index) + " is out of range\n";
				throw std::out_of_range(error);
			}
			else {
				return (this->head+index)%this->cap;
			}
		}
		
	public:
		/**
		 * This constructs the CDA with an initial capacity of 2
		 */
		CDA() {
			this->size=0;
			this->cap=2;
			this->head=0;
			this->list=new T[cap];
		}

		/**
		 * this constructs the CDA with an initial capacity of s
		 *
		 * @param s: the given initial capacity
		 */
		CDA(int s) {
			this->size=0;
			this->cap=s;
			this->head=0;
			this->list=new T[cap];
		}

		/**
		 * Deconstructs the CDA
		 */
		~CDA() {
			delete [] this->list;
		}

		/**
		 * Defines the bracket operator so it can be used on the CDA class
		 *
		 * @param index: the index relative to the head of the array
		 * @return: returns the data stored at the index
		 */
		T& operator[](int index) {
			return this->list[this->relativeIndex(index)];
		}

		/**
		 * Adds data at the end of the circular array, relative to the head
		 *
		 * @param data: the data to be added to the end of the array
		 */
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

		/**
		 * Adds data at the front of the circular array, relative to the head
		 *
		 * @param data: the data to be added to the front of the array
		 */
		void addFront(T data) {
			
			if (this->size==this->cap) {
				this->upsize();
				this->addFront(data);
			}
			else {
				this->head = (this->head+this->cap-1)%this->cap; //capacity is added here to avoid the mod of negative numbers when head = 0
				this->list[this->head]=data;
				this->size++;
			}
		}

		/**
		 * Removes the last element in the CDA relative to the head
		 */
		/* Should I free the deleted Element??? */
		void delEnd() {
			
			T data = this->list[this->relativeIndex(this->size-1)];
			this->size--;
			
			if (((double) this->size)/((double) this->cap) <= .25) {
				this->downsize();
			}
		}

		/**
		 * Removes the first element in the CDA relative to the head
		 */
		void delFront() {

			T data = this->list[this->head];
			this->head=(this->head+1)%this->cap;
			this->size--;

			if (((double) this->size)/((double) this->cap) <= .25) {
				this->downsize();
			}
		}
		
		/**
		 * Returns the number of elements in the CDA
		 *
		 * @return: returns the size of the CDA
		 */
		int length() {
			return this->size;
		}

		/**
		 * Returns the capacity of the CDA
		 *
		 * @return: returns the capacity of the CDA
		 */
		int capacity() {
			return this->cap;
		}

		/**
		 * Clears the CDA and starts over from a new CDA
		 *
		 */
		void clear() {
			delete [] this->list;
			this->size=0;
			this->cap=2;
			this->head=0;
			this->list=new T[cap];
		}

		/**
		 * Returns the kth smallest element
		 *
		 * @param k: the order of the element being searched for
		 * @return: returns the element being searched for
		 */
		T QuickSelect(int k) {
			//select a pivot
			int pivotIndex=0;
			//partition
			int max=size-1;
			int min=0;
			
			pivotIndex = partition(min, max);
			//count while loop

			while (pivotIndex!=k) {
				if (pivotIndex<k) {
					//go right
					min = pivotIndex+1;
				}
				else {
					//go left
					max = pivotIndex-1;
				}
				pivotIndex = partition(min, max);
			}
			//partition
			return this->list[relativeIndex(pivotIndex)];
		}
		
		void quickSort() {
			int min=0;
			int max=size-1;
			quickRecursive(min,max);
		}

		void quickRecursive(int min, int max) {
			int mid=partition(min,max);
			
			if (mid-1>min) quickRecursive(min,mid-1);
			if (mid+1<max) quickRecursive(mid+1,max);
		}

		int partition(int min, int max) {
			T pivot = this->list[relativeIndex(min)];
			min++;
			T swap;
			int i=min;
			
			for (;;) {
				if (this->list[relativeIndex(i)] <= pivot) {
					this->list[relativeIndex(i-1)]=this->list[relativeIndex(i)];
					i++;

					if (i>max) {
						this->list[relativeIndex(i-1)]=pivot;
						return i-1;
					}
				}
				else if (this->list[relativeIndex(i)] > pivot) {
					swap = this->list[relativeIndex(max)];
					this->list[relativeIndex(max)] = this->list[relativeIndex(i)];
					this->list[relativeIndex(i)] = swap;
					max--;

					if (i>max) {
						list[relativeIndex(i-1)]=pivot;
						return i-1;
					}
				}
			}
		}

		/**
		 * Prints the CDA starting from the head
		 */
		void printList() {
			for (int i=0;i<size;i++) {
				std::cout << this->list[this->relativeIndex(i)] << ",";
			}
			std::cout << std::endl;
		}
};

int main(int argc, char const *argv[]) {
	std::cout << "Hello World!\n" << std::endl;
	
	CDA<int> list;
	
	for (int i=0;i<100;i+=2) {
		list.addEnd(i);
		list.addFront(i+1);
	}
	
	list.printList();
	std::cout << list.QuickSelect(1) << std::endl;
	std::cout << list.QuickSelect(99) << std::endl;
	std::cout << list.QuickSelect(8) << std::endl;
	list.printList();
	return 0;
}
