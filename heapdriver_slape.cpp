#include <iostream>
#include <cassert>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

void heapify(int * myArray, int size);
/*
	Applies percolateDown as needed to transform complete binary tree to a heap.
	Precondition: myArray[r] through myArray[size] stores a complete binary tree.
	Postcondition: The binary tree has been converted to a heap.  Since the array
	is dynamically allocated, no return type is needed.
*/

void percolateDown(int * semiHeap, int root, int size);
/*
	Precondition: semiHeap[r]-[size] stores a semiHeap and only semiHeap[r] fails
	heap order principle.
	Postcondition: semiHeap is converted into a heap.
*/

void displayArray(int* myArray, int size);
/* 
	Displays the contents of the array in a horizontal fashion.
	Precondition: None
	Postcondtion: the contents of the array are outputted to cout
*/

void displayTree(int * myTree, int size);
/*
	Precondition: myTree is initialized, complete, and size is greater than -1
	Postcondition: myTree is outputted to screen in an easy to read, tree format.
*/

void displayOneLevel(int * myTree, int numRows, int level, int beginIndex,
		                 int endIndex);
/*
  This function is only called instead of displayTree, and so displayTree is 
  successfully executed, then displayOneLevel will successfully execute.
	Precondition: displayTree() is executed properly.
	Postcondition: The specified line is printed from the tree.
*/

void heapsort(int* myHeap, int size);
/*
	Precondition:
	Postcondition: Ascending order as in textbook
*/

int main() {
	char ch;
	int size; //choice used to choose size of array as well as escape execution
	int * myHeap = NULL; //NULL for now
	srand(time(NULL) ); //seed srand
	while (size != -1) {
		cout << "Input the size of the array (-1 to quit): ";
		cin >> size;
		assert(size >= -1); //Assert that number of elements is greater than 1
		if (size > -1) { //Check for 0 values
			myHeap = new int[size+1]; //Allocate new array
			for(int i = 1; i < size+1; i++) {
				myHeap[i] = rand() % 1000;
			}
			displayTree(myHeap, size);
			displayArray(myHeap, size);
			cout << "Do you want to [h]eapify or heap[s]ort?\n";
			cin >> ch;
			if (ch == 'h'){
				cout << "Heapifying!\n";
			  heapify(myHeap, size);
			}
	    else if (ch == 's') {
	    	cout << "Sorting!\n";
        heapsort(myHeap, size);
			}
      displayTree(myHeap, size);
      displayArray(myHeap, size);
			cout << "Deleting the array\n";	
			delete [] myHeap;
		}
	}
	cout << "Goodbye!";
	return 0;
}

void percolateDown(int * semiHeap, int root, int size) {
	int child = 2 * root; //Left child
	int tempVal;
	while (child <= size) {
		if (child < size && semiHeap[child] < semiHeap[child+1])
		  child++;
    if (semiHeap[root] < semiHeap[child]) {
    	tempVal = semiHeap[root];
    	semiHeap[root] = semiHeap[child];
    	semiHeap[child] = tempVal;
    	root = child; //set root as child
    	child = 2 * child; //Set child as it's own left child
		}
		else {
			child = size+1; //exit loop
		}
	}
}

void heapify(int * myArray, int size) {
	for(int r = (size/2); r > 0; r--) {
		percolateDown(myArray, r, size);
	}
}

void heapsort(int* myHeap, int size) {
	const int ROOT = 1; //The root is stored at 1;
	int temp;
	heapify(myHeap, size); //convert binary tree to heap.
	for(int i = size; i >= 2; i--) {
		//root-leaf exchange follows
		temp = myHeap[1];
		myHeap[1] = myHeap[i];
		myHeap[i] = temp;
		//Prune leaf and percolate down
		percolateDown(myHeap, ROOT, i-1);
	}
}

void displayTree(int * myTree, int size) {
	int beginIndex = 1,
			endIndex = 1,
			rowLength,
			numLevels = int(ceil(log(double(size+1)) / log(2.0))); //# of levels
	for (int level = 0; level < numLevels; level++) {
		displayOneLevel(myTree, numLevels, level, beginIndex, endIndex);
		rowLength = endIndex - beginIndex + 1;
		beginIndex = endIndex + 1;
		endIndex = min(endIndex + 2*rowLength, size);
	}
}

void displayOneLevel(int * myTree, int numRows, int level, int beginIndex,
		                 int endIndex) {
  int skip = int(pow(2.0, numRows - level) - 1); //Space between items
  for(int i = beginIndex; i <= endIndex; i++) {
  	cout << setw(skip) << " "
  			 << setw(2) << myTree[i]
 		     << setw(skip) << " ";
	}
	cout << "\n\n";
}

void displayArray(int * myArray, int size) {
	for (int i = 1; i < size+1; i++) {
	  cout << myArray[i] << " ";
	}
	cout << endl;
}
