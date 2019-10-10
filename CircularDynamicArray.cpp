/**
 * @Author Asa Dillahunty
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
class CircularDynamicArray {
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
			int mid=partition(min,max,min);

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
		int partition(int min, int max, int pivotIndex) {
			T swap=this->list[relativeIndex(min)];
			this->list[relativeIndex(min)]=this->list[relativeIndex(pivotIndex)];
			this->list[relativeIndex(pivotIndex)]=swap;
			//swap pivot index and min
			T pivot = this->list[relativeIndex(min)];
			min++;
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

		/**
		 * Used by Radix sort
		 *
		 * Sorts data by the value of the bits and not by using
		 * the comparision operators
		 *
		 * Data may not be sorted the way you want it to be
		 *
		 * @param base: the base being compared
		 * @param comp: the number used to compare to get the bits
		 * @param exp: the number of bits/base already compared
		 */
		bool countingSort(int base, int comp, int exp) {
			bool valid=0;
			int countArr[base];
			int shift=pow(base, exp);

			for (int i=0;i<base;i++) countArr[i]=0;

			for (int i=0;i<this->size;i++) {
				countArr[(this->list[relativeIndex(i)]/shift)&comp]++;
				if (valid || this->list[relativeIndex(i)]/shift != 0) valid=1;
			}

			countArr[base-1]=this->size-countArr[base-1];
			for (int i=base-2;i>=0;i--) {
				countArr[i]=countArr[i+1]-countArr[i];
			}

			T* sorted = new T[this->cap];
			for (int i=0;i<size;i++) {
				sorted[countArr[(this->list[relativeIndex(i)]/shift)&comp]++]=this->list[relativeIndex(i)];
			}

			//Make sure everything is deleted?? Possible memory leak
			delete [] this->list;
			this->list = sorted;
			this->head = 0;

			return valid;
		}

		/**
		 * Used by Radix sort
		 *
		 * Sorts data by the value of the bits and not by using
		 * the comparision operators
		 *
		 * Data may not be sorted the way you want it to be
		 *
		 * @param base: the base being compared
		 * @param comp: the number used to compare to get the bits
		 * @param exp: the number of bits/base already compared
		 */
		bool countingSortCast(int base, int comp, int exp) {
			bool valid=0;
			int countArr[base];
			int shift=pow(base, exp);

			for (int i=0;i<base;i++) countArr[i]=0;

			for (int i=0;i<this->size;i++) {
				countArr[(((int) this->list[relativeIndex(i)])/shift)&comp]++;
				if (valid || ((int) this->list[relativeIndex(i)])/shift != 0) valid=1;
			}

			countArr[base-1]=this->size-countArr[base-1];
			for (int i=base-2;i>=0;i--) {
				countArr[i]=countArr[i+1]-countArr[i];
			}

			T* sorted = new T[this->cap];
			for (int i=0;i<size;i++) {
				sorted[countArr[(((int) this->list[relativeIndex(i)])/shift)&comp]++]=this->list[relativeIndex(i)];
			}

			//Make sure everything is deleted?? Possible memory leak
			delete [] this->list;
			this->list = sorted;
			this->head = 0;

			return valid;
		}

        /**
         * Used by Radix sort
         *
         * Sorts data by the value of the bits and not by using
         * the comparision operators
         *
         * Data may not be sorted the way you want it to be
         *
         * @param base: the base being compared
         * @param comp: the number used to compare to get the bits
         * @param exp: the number of bits/base already compared
         */
        bool countingSortCastPointer(int base, int comp, int exp) {
            bool valid=0;
            int countArr[base];
            int shift=pow(base, exp);

            for (int i=0;i<base;i++) countArr[i]=0;

            for (int i=0;i<this->size;i++) {
                countArr[(((int) &this->list[relativeIndex(i)])/shift)&comp]++;
                if (valid || ((int) &this->list[relativeIndex(i)])/shift != 0) valid=1;
            }

            countArr[base-1]=this->size-countArr[base-1];
            for (int i=base-2;i>=0;i--) {
                countArr[i]=countArr[i+1]-countArr[i];
            }

            T* sorted = new T[this->cap];
            for (int i=0;i<size;i++) {
                sorted[countArr[(((int) &this->list[relativeIndex(i)])/shift)&comp]++]=this->list[relativeIndex(i)];
            }

            //Make sure everything is deleted?? Possible memory leak
            delete [] this->list;
            this->list = sorted;
            this->head = 0;

            return valid;
        }

	public:
		/**
		 * This constructs the CDA with an initial capacity of 2
		 */
		CircularDynamicArray() {
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
		CircularDynamicArray(int s) {
			this->size=s;
			this->cap=s;
			this->head=0;
			this->list=new T[cap];
		}

		/**
		 * Deconstructs the CDA
		 */
		~CircularDynamicArray() {
			delete [] this->list;
		}

		/**
		 * Copy constructor
		 */
		CircularDynamicArray(CircularDynamicArray &original) {
			this->size = original->size;
			this->cap = original->cap;
			this->head = original->head;
			this->list = new T[this->cap];

			for (int i=0;i<cap;i++) {
				this->list[i] = original->list[i];
			}
		}

		/**
		 * Copy assignment operator
		 */
		CircularDynamicArray& operator=(CircularDynamicArray& original) {
			this->size = original.size;
			this->cap = original.cap;
			this->head = 0;
			this->list = new T[this->cap];

			for (int i=0;i<this->size;i++) {
				this->list[i] = original[i];
			}
			return *this;
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
		 */
		void clear() {
			delete [] this->list;
			this->size=0;
			this->cap=2;
			this->head=0;
			this->list=new T[cap];
		}

		/**
		 * Returns the kth smallest element, smallest element being 1
		 * and the largest being size
		 *
		 * @param k: the order of the element being searched for
		 * @return: returns the element being searched for
		 */
		T QuickSelect(int k) {
			k--;
			//select a pivot
			int pivotIndex=0;
			//partition
			int max=size-1;
			int min=0;

			pivotIndex = partition(min, max, pivotIndex);

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
				pivotIndex = partition(min, max, min);
			}
			//partition
			return this->list[relativeIndex(k)];
		}

		T WCSelect(int k) {
			k--;
			//select a pivot
			int pivotIndex=0;
			//partition
			int max=size-1;
			int min=0;

			pivotIndex = partition(min, max, pivotIndex);

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
				pivotIndex = partition(min, max, pivotIndex);
			}
			//partition
			return this->list[relativeIndex(pivotIndex)];

			//Divide into partitions of size K
			//Sort partitions
			for (int i=k;i<size-1;i+=k) {
				mergeSort(i-k,i);
			}
			//Find the median of those partitions
			//Go left or right
			//I strongly disagree with this algorithm
		}

        /**
         * Sorts the values in the range from a min index to a max index
         *
         * @param min: the min index (included in sorting)
         * @param max: the max index (included in sorting)
         */
		void selectionSort(int min, int max) {

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
		 * Sorts the array
		 */
		void stableSort() {
			mergeSort(0,size-1);
		}

		/**
		 * Sorts the data by the value of the bits and not by using
		 * the comparision operators on elements
		 *
		 * Data may not be sorted the way you want it to be
		 *
		 * @param bits: number of bits compared with each pass
		 */
		void radixSort(int bits) {
			int base=pow(2, bits);
			int comp=base-1;
			bool valid=1;
			//while something

			try {
				for (int i=0;valid;i++) {
					valid=countingSort(base,comp, i);
				}
			} catch (int e) {
                std::cout << "Maybe don't use radix sort for this type...\n";
                /*
                try {
                    for (int i=0;valid;i++) {
                        valid=countingSortCast(base,comp,i);
                    }
                } catch (int ex) {
                    for (int i=0;valid;i++) {
                        valid=countingSortCastPointer(base,comp,i);
                    }
                }
                */
			}
		}

		/**
		 * Performs a linear search for a data value and
		 * returns its index relative to the head
		 *
		 * @param value: the data value being searched for
		 * @returns: returns the index of the value.
		 */
		int linearSearch(T value) {
			for (int i=0;i<this->size;i++) {
				if (value == this->list[relativeIndex(i)]) return i;
			}
			return -1;
		}

		/**
		 * This search algorithm assumes the CDA is already
		 * sorted! Make sure to call a sort before using this
		 * search method, or use another search function.
		 *
		 * Performs a search for a specified value in the CDA
		 * and returns its relative index
		 *
		 * @param value: the data value being searched for
		 * @returns: returns the index of the value
		 */
		int binSearch(T value) {
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

/*
T findMedian(int arr[], int n) {

	int minInd = 0;

	for (int i = 0; i < n-1; i++) {
		minInd = i;

		for (int j = i+1; j < n; j++) {
			if (arr[realIndex(j)] < arr[realIndex(minInd)])
				minInd = j;
		}

		T temp = arr[realIndex(minInd)];
		arr[realIndex(minInd)] = arr[realIndex(i)];
		arr[realIndex(i)] = temp;
	}

	return arr[realIndex(n/2)];
}

T kthSmallestWC(int arr[], int l, int r, int k) {

	if (k > 0 && k <= r - l + 1) {
        int n = r-l+1;
        int i, median[(n+4)/5];

        for (i=0; i<n/5; i++) median[i] = findMedian(arr+l+i*5, 5);

        if (i*5 < n)
        {
            median[i] = findMedian(arr+l+i*5, n%5);
            i++;
        }

		int medOfMed = (i == 1)? median[i-1]:kthSmallest(median, 0, i-1, i/2);
		cout << "MedOfMed = " << medOfMed << endl;

		int pos = partitionWC(arr, l, r, medOfMed);
        if (pos-l == k-1)
            return arr[realIndex(pos)];

		if (pos-l > k-1)
            return kthSmallestWC(arr, l, pos-1, k);

		return kthSmallestWC(arr, pos+1, r, k-pos+l-1);
    }
	else {
		cout << "Invalid k-term for WCSelect";
	}
	return INT8_MAX;
}

int partitionWC(int arr[], int l, int r, T x) {
   int i;
   cout << "PARTITION CALLED" << endl;
   for (i=l; i<r; i++) {
		//cout << i << endl;
		//cout << arr[realIndex(i)] << endl;
       if (arr[realIndex(i)] == x)
          break;
	}
	swap(&arr[realIndex(i)], &arr[realIndex(r)]);
   i = l;
   for (int j = l; j <= r - 1; j++)
   {
       if (arr[realIndex(j)] <= x)
       {
           swap(&arr[realIndex(i)], &arr[realIndex(j)]);
           i++;
       }
   }
   swap(&arr[realIndex(i)], &arr[realIndex(r)]);
//for (int k = 0; k < size; k++) {
// cout << arr[realIndex(k)] << endl;
// }
   return i;
}

T WCSelect(int k) {
	cout << "WC SELECT CALLED" << endl;
	return kthSmallestWC(list, 0, size - 1, k);
}
*/