
//This is the definition for the class StringVar
//whose values are strings. An object is declared as follows.
//Note that you use (max_size), not [max_size]
//StringVar the_object(max_size);
//where max_size is the longest string length allowed.
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <iostream>
using namespace std;
class StringVar
{
public:
	
	StringVar(int size1);
	//Initializes the object so it can accept string values up to size
	//in length. Sets the value of the object equal to the empty string.

	StringVar();
	//Initializes the object so it can accept string values of length 100
	//or less. Sets the value of the object equal to the empty string.

	StringVar(const char a[]);
	//Precondition: The array a contains characters terminated with '\0'.
	//Initializes the object so its value is the string stored in a and
	//so that it can later be set to string values up to strlen(a) in length.

	StringVar(const StringVar& string_object);
	//Copy constructor.

	~StringVar();
	//Returns all the dynamic memory used by the object to the freestore.

	int length() const;
	//Returns the length of the current string value.

	void input_line(istream& ins);
	//Precondition: If ins is a file input stream, then ins has been
	//connected to a file.
	//Action: The next text in the input stream ins, up to '\n', is copied
	//to the calling object. If there is not sufficient room, then
	//only as much as will fit is copied.

	friend ostream& operator <<(ostream& outs, const StringVar& the_string);
	//Overloads the << operator so it can be used to output values
	//of type StringVar
	//Precondition: If outs is a file output stream, then outs
	//has already been connected to a file.

	// added function declarations
	StringVar copy_piece(const StringVar& str, const char* start, int num_chars);
	StringVar one_char(const StringVar& str, const char* start);
	StringVar set_char(const StringVar& str, const char* start, char new_char);

	bool operator==(const StringVar& other) const {
		return strcmp(value, other.value) == 0;
	}

	friend void conversation(int max_name_size);
	friend StringVar operator+(const StringVar& str1, const StringVar& str2);
	friend StringVar operator>>(istream& input, StringVar& str);

private:
	char* value; //pointer to dynamic array that holds the string value.
	size_t max_length; //declared max length of any string value.
};


void conversation(int max_name_size);
//Carries on a conversation with the user.

StringVar operator+(const StringVar& str, const StringVar& str2);

// Added Member Functions
StringVar StringVar::copy_piece(const StringVar& str, const char* start, int num_chars) {

	int chars = max(0, min(static_cast<int>(str.max_length) - static_cast<int>(start - str.value), num_chars));

	if (chars < num_chars) {
		return StringVar("Error: name too short to copy piece from");
	}

	else {
		StringVar result(chars);
		strncpy(result.value, start, chars);
		result.value[chars] = '\0';

		return result;
	}	
}

StringVar StringVar::one_char(const StringVar& str, const char* start)
{
	char singleChar[2] = { *start, '\0' };  // Create a null-terminated string with one character
	return StringVar(singleChar);
}

StringVar StringVar::set_char(const StringVar& str, const char* start, char new_char) {
	StringVar result(str);
	result.value[start - str.value] = new_char;
	
	return result;
}


// Main Function
int main()
{
	conversation(30);
	cout << "End of demonstration.\n";
	return 0;
}


//This is only a demonstration function:
void conversation(int max_name_size)
{
	//Values here determine where in the array to start the string, and how many characters from the start to read
	//Used in the copy_piece function, could change to be prompted for
	int starting_letter_index = 3;
	int characters_to_read = 4;

	StringVar your_name(max_name_size), our_name("Anita");
	cout << "What is your name?\n";
	your_name.input_line(cin);
	cout << "We are " << our_name << endl;
	cout << "We will meet again " << your_name << endl;
	// testing
	if (your_name.length() > 3) {
		StringVar piece = your_name.copy_piece(your_name, &your_name.value[starting_letter_index], characters_to_read);
		cout << "Copied piece: " << piece << endl;
	

	// testing one_char
	StringVar one_char = your_name.one_char(your_name, &your_name.value[starting_letter_index]);
	cout << "Character at Starting Index: " << one_char << endl << endl;

	// set_char
	cout << "What would you like to replace the starting index character with? (Only the first character entered will apply)" << endl;
	char new_char;
	cin >> new_char;

	StringVar set_char = your_name.set_char(your_name, &your_name.value[starting_letter_index], new_char);
	cout << "Character Replaced in Copy: " << set_char << endl;
	}
	else {
		cout << "Name too short to copy a piece, must be 4 letters minimum" << endl << endl;
		exit(1);
	}

	// Operator Test
	StringVar test_string(max_name_size);
	cout << "Now, Input a string to compare your original name string to" << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (your_name.length() > 3) {
		test_string.input_line(cin);
		if (strcmp(your_name.value, test_string.value) == 0) {
			cout << "\nYour Name is equal to the Inputted String" << endl;
		}
		else {
			cout << "\nThese two strings are not equal" << endl;
		}
	}
	else {
		cout << "\nName too short to copy a piece, muut be 4 letters minimum" << endl;
		exit(1);
	}
	
	StringVar concatted = your_name + test_string;
	cout << "\nYour name and compared string concatenated: " << concatted << endl;

	// Not Working Currently
	// revist
	// 	 
	StringVar first_word_test;
	cout << "\nNow write a sentence, the first word will be recorded." << endl;
	cin >> first_word_test;
	cout << "The first word from your sentence is " << first_word_test << endl;
}


StringVar operator+(const StringVar& str1, const StringVar& str2)
{
	int total_length = str1.length() + str2.length();
	StringVar result(total_length + 1);

	result.value = str1.value;
	strcat(result.value, str2.value);

	return result; // Return the result
}

StringVar operator>>(istream& input, StringVar& str)
{
	string first_word;
	input >> first_word;
	str = StringVar(first_word.c_str());
	return str;
}


//Given Member Functions
//Uses cstddef and cstdlib:
StringVar::StringVar(int size1)
{
	max_length = static_cast<size_t>(size1);
	value = new char[max_length + 1];//+1 is for '\0'.
	value[0] = '\0';
}

//Uses cstddef and cstdlib:
StringVar::StringVar()
{
	max_length = 100;
	value = new char[max_length + 1];//+1 is for '\0'.
	value[0] = '\0';
}

//Uses cstring, cstddef, and cstdlib:
StringVar::StringVar(const char a[])
{
	max_length = strlen(a);
	value = new char[max_length + 1];//+1 is for '\0'.
	strcpy(value, a);
}

//Uses cstring, cstddef, and cstdlib:
StringVar::StringVar(const StringVar& string_object)
{
	max_length = string_object.length();
	value = new char[max_length + 1];//+1 is for '\0'.
	strcpy(value, string_object.value);
}

StringVar::~StringVar()
{
	delete[] value;
}

//Uses cstring:
int StringVar::length() const
{
	return static_cast<int>(strlen(value));
}

//Uses iostream:
void StringVar::input_line(istream& ins)
{
	ins.getline(value, max_length + 1);
}

//Uses iostream:
ostream& operator <<(ostream& outs, const StringVar& the_string)
{
	outs << the_string.value;
	return outs;
}
