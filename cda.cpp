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
#include <math.h>

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
				std::string error = "Index " + std::to_string(index) + " is out of range\n";
				throw std::out_of_range(error);
			}
			else {
				return (this->head+index)%this->cap;
			}
		}

		/**
		 * Used for quick sort
		 * I didn't want to have to put parameters on my sorting function
		 */
		void quickRecursive(int min, int max) {
			int mid=partition(min,max);

			if (mid-1>min) quickRecursive(min,mid-1);
			if (mid+1<max) quickRecursive(mid+1,max);
		}

		/**
		 * Used by quick sort and quick select
		 * This function selects a pivot, puts every element bigger than it
		 * on the right side (larger index) and everything smaller than it on the
		 * left side (smaller index), and return's the pivot's updated position.
		 *
		 * @param min: the starting index of the portion of the array to be partitioned
		 * @param max: the ending index of the portion of the array to be partitioned
		 * @return: returns the pivot's updated position
		 */
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
		 * Merge sort
		 *
		 * @param min: starting point for the portion of the array being sorted
		 * @param max: ending point for the portion of the array being sorted
		 */
		void mergeSort(int min, int max) {
			if (min>=max) return;

			int mid = (max + min + 1)/2;
			mergeSort(min,mid-1);
			mergeSort(mid,max);
			//so now i've sorted the left and right halves, we zip them together

			zip(min,mid,max);
		}

		/**
		 * Used by mergeSort
		 * This function "zips" together two parts of an array assuming both
		 * sides were already sorted
		 *
		 * @param min: starting point for the portion of the array being zipped
		 * @param max: ending point for the portion of the array being zipped
		 * @param mid: the point where the two different arrays meet
		 */
		void zip(int min, int mid, int max) {
			T temp[max-min+1];
			int smin=min; //starting min

			int rmid=mid; //right mid
			int lmid=mid-1;//left mid
			int i=0;
			for (;min<=lmid && max>=rmid;i++) {
				if (this->list[relativeIndex(rmid)] < this->list[relativeIndex(min)]) {
					temp[i] = this->list[relativeIndex(rmid)];
					rmid++;
				}
				else {
					temp[i] = this->list[relativeIndex(min)];
					min++;
				}
			}

			for (;min<=lmid;i++, min++) temp[i] = this->list[relativeIndex(min)];
			for (;max>=rmid;i++, rmid++) temp[i] = this->list[relativeIndex(rmid)];

			for (int j=0;j<i;j++) {
				this->list[relativeIndex(j+smin)]=temp[j];
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

		T WCSelect(int k) {
			//I strongly disagree with this algorithm
		}

		/**
		 * This sort was simply written to verify partition functioned
		 * properly for quick select to work
		 */
		void quickSort() {
			int min=0;
			int max=size-1;
			quickRecursive(min,max);
		}

		/**
		 * Sorts it
		 */
		void stableSort() {
			mergeSort(0,size-1);
		}

		void radixSort(int bits) {
			int base=pow(2, bits);
			int comp=base-1;
			bool valid=1;
			//while something

			for (int i=0;valid;i++) {
				valid=countingSort(base,comp, i);
			}
		}

		bool countingSort(int base, int comp, int exp) {
			bool valid=0;
			int countArr[base];
			int indexArr[base];
			int shift=pow(base, exp);

			for (int i=0;i<base;i++) countArr[i]=0;

			for (int i=0;i<this->size;i++) {
				int k=(this->list[relativeIndex(i)]/shift)&comp;
				countArr[(this->list[relativeIndex(i)]/shift)&comp]++;
				if (valid || this->list[relativeIndex(i)]/shift != 0) valid=1;
			}

			indexArr[base-1]=this->size-countArr[base-1];
			for (int i=base-2;i>=0;i--) {
				indexArr[i]=indexArr[i+1]-countArr[i];
			}

			T sorted[this->cap];
			for (int i=0;i<size;i++) {
				sorted[indexArr[(this->list[relativeIndex(i)]/shift)&comp]]=this->list[relativeIndex(i)];
				indexArr[(this->list[relativeIndex(i)]/shift)&comp]++;//move ++ up
			}

			for (int i=0;i<this->size;i++) {
				this->list[relativeIndex(i)]=sorted[i];
			}
			/*
			delete [] this->list;
			this->list = sorted;
			this->head = 0;*/

			return valid;
		}

		int linearSearch(T value) {
			for (int i=0;i<this->size;i++) {
				if (value == this->list[relativeIndex(i)]) return i;
			}
			return -1;
		}

		int binarySearch(T value) {
			int min=0;
			int max=this->size-1;
			int mid=(max-min)/2;
			for (;value!=this->list[relativeIndex(mid)] && max > min;) {
				if (value < this->list[relativeIndex(mid)]) {
					max = mid-1;
					mid = (max+min)/2;
				}
				else {
					min = mid+1;
					mid = (max+min)/2;
				}
			}
			if (value == this->list[relativeIndex(mid)]) return mid;
			else return -1;
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
	int numElements=5;

	for (int i=0;i<numElements;i+=2) {
		list.addEnd(i);
		list.addFront(i+1);
	}

	list.printList();
	int dex = list.linearSearch(5);
	std::cout << list.linearSearch(5) << std::endl;
	std::cout << list[dex] << std::endl;

	list.stableSort();
	list.printList();
	int dex2 = list.binarySearch(3);
	std::cout << list.binarySearch(3) << std::endl;
	std::cout << list[dex2] << std::endl;

	/*
	for (int j=1;j<16;j++) {

		for (int k=10;k<1000000;k=k*10) {
			CDA<int> list2;

			for (int h=0;h<k;h+=2) {
				list2.addEnd(h);
				list2.addFront(h+1);
			}

			list.radixSort(j);

			for (int i=0;i<k;i++) {
				if (i!=list[i]) std::cout << "YOU SUCK" << std::endl;
			}
		}
	}
	*/

	return 0;
}
