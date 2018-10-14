#include <iostream>
#include <cmath>
#include <string>

#ifdef _WIN32
#include "getopt.h"
#else
#include <unistd.h>
#endif

using namespace std;

struct WordInfo { // Struct deffinition that contains a string with an associated int.
	int count;    
	string text;
};

template <class T>
class Vector { // Vector Class.

public:

	typedef T* iterator;
	Vector() {    // Default Constructor.
		volume = 0; // Initilise 'volume' variable to 0. 'volume' is used to keep track of the size of the vector. 
		capacity = 20; // Initilise 'capacity' to 20. This is the default vector size when first declared. 
		items = new T[capacity]; // Declares items as a vector of size 20.
	}

	iterator begin() { return &items[0]; } // Returns memory location of the beginning of the vector.

	iterator end() { return &items[volume]; } // Returns the memory location of the end of the vector.

	int size() { return (volume); } // Returns the size of the vector.

	iterator insert(iterator position, const T& item) { // Inserts an item at a particular position within the vector.
		if (volume >= capacity) { // If the volume of the vector = max capacity...
			int posIndex = position - items; // Get the index at which the postition pointer is at.
			double_capacity(); // Call function to double the capacity.
			position = items + posIndex; // Set position = to the original index it was at in the original vector.
		}
		for (iterator i = end(); i > position; i--) { // For loop shuffles everything along the vector to make room for the item to be inserted.
			*i = *(i - 1);
		}
		*position = item; // Inserts item in the required position here.
		volume++; // Increments 'volume' whenever an item is inserted to keep track of the size of the vector.

		return(position); // Returns the memory location of position.
	}

	void double_capacity() { // Double capacity function.
		capacity *= 2;       // Double the capacity variable.
		T* NewItems = new T[capacity]; // Declare a new vector called 'NewItems' and set it with the increased capacity.
		for (int i = 0; i < volume; i++) { // The for loop is used to copy everything from the old vector to the new vector.
			NewItems[i] = items[i];
		}
		delete[] items; // Deletes the contents of the old vector.
		items = NewItems; // Sets the pointer that pointed to the start of the original vector to point to the start of the new vector.
	}

private:
	int capacity;  // Declares an int variable to store the capacity value of the vector.
	T* items; // Declares a storage container of type 'T', defined by the decleration of the variable within main.
	int volume;      // Declares an int to keep track of vector size.
};

int main(int argc, char** argv) {

	string word;
	Vector<WordInfo> main_vector; // Declaration of a vector of 'WordInfo's', eg a vector of strings with an int associated with each string.
	int count = 0; // Sets the variable responsible for keeping track of the 'total' size of the vector to 0.

	enum { total, unique, alphabetical } mode = total; 

	for (int c; (c = getopt(argc, argv, "tui")) != -1;) { // Reads the command line argument to determine which mode to use.
		switch (c) {
		case 't': mode = total; break;
		case 'u': mode = unique; break;
		case 'i': mode = alphabetical; break;
		}
	}

	argc -= optind;
	argv += optind;

	while (cin >> word) { // While there are words in the input stream.
		count += 1; // Increment count.
		bool found = false; // Initilise the 'found' variable.

		Vector<WordInfo>::iterator i = main_vector.begin(); // Iterator decleration is outside of the for loop because it needs to remain at its last location in order to correctly insert words in alphabetical order.
		for (/* Iterator defined above */; i < main_vector.end(); i++) {
			if (word == i->text) { found = true; } // If the word == the text string at location i, set the found flag to true.
			if (word <= i->text) { break; }        // If the word is <= the text string at location i indicating that it is at the correct spot to be inserted, break from the loop.
		}
		if (found == false) { // If the found flag was not set, it is therefore a new word.
			WordInfo info;    // WordInfo variable decleration.
			info.text = word; // Sets the text variable of WordInfo = word.
			info.count = 1;   // Sets the count variable of WordInfo = 1.
			main_vector.insert(i, info); // Then inserts the WordInfo variable at position i, the correct alphabetical position.
		}
		else { i->count++; } // Else it is a repeat word so increment the count variable within info.
	}

	switch (mode) { // Determines which output to produce based on the mode selected by the command line arguments.
	case total: { cout << "Total: " << count << endl; break; } // Outputs the total number of words read in.
	case unique: { cout << "Unique: " << main_vector.size() << endl; break; } // Outputs the total number of unique words stored in the vector.
	case alphabetical: { // Outputs the contents of the vector, in alphabetical order, and also the number of times each word was read in.
		for (Vector<WordInfo>::iterator i = main_vector.begin(); i < main_vector.end(); i++) {
			cout << i->text << ": " << i->count << endl;
		}
		break;
	}				
   }
	
//	system("Pause");
	return(0); 
}