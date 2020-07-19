// text2number: converts numbers (written in words) in a string into their numerical value

#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

// Translator class
class Translator {
	private:
		map<string,int> dictionary;
		map<string,int>::iterator it;
		vector<string> tokens;

	public:
		Translator()
		{
			// construct dictionary
			dictionary["zero"]=0;
			dictionary["one"]=1;
			dictionary["two"]=2;
			dictionary["three"]=3;
			dictionary["four"]=4;
			dictionary["five"]=5;
			dictionary["six"]=6;
			dictionary["seven"]=7;    
			dictionary["eight"]=8;
			dictionary["nine"]=9;
			dictionary["ten"]=10; 
			dictionary["eleven"]=11;
			dictionary["twelve"]=12;
			dictionary["thirteen"]=13;
			dictionary["fourteen"]=14;
			dictionary["fifteen"]=15;
			dictionary["sixteen"]=16;
			dictionary["seventeen"]=17;
			dictionary["eighteen"]=18;
			dictionary["nineteen"]=19;
			dictionary["twenty"]=20;
			dictionary["thirty"]=30;
			dictionary["fourty"]=40;
			dictionary["fifty"]=50;
			dictionary["sixty"]=60;
			dictionary["seventy"]=70;
			dictionary["eighty"]=80;
			dictionary["ninety"]=90;
			dictionary["hundred"]=100;
			dictionary["thousand"]=1000;
			dictionary["million"]=1000000;
			dictionary["and"]=0;
		}

		// translate method
		string translate(vector<string> tokens)
		{
			string output_str = "";
			int current = 0;
			int result = 0;
			int scale = 0;
			int increment = 0;
			bool match = false;
	
			// check if vector is empty	
			if (tokens.empty())
				return "";
	
			// iterate tokens vector to check matching elements
			for (vector<string>::iterator it_match = tokens.begin() ; it_match != tokens.end(); ++it_match)
			{
				// find match
				it = dictionary.find(*it_match);
				if (it != dictionary.end()){
					// it is a match
					match = true;
					// assign scale (powers of ten) and increment values (sum elements)
					if (it->second == 100) {
						scale = 100;
						increment = 0;
					}else if (it->second == 1000){
						scale = 1000;
						increment = 0;
					}else if (it->second == 1000000){ 
						scale = 1000000;
						increment = 0;
					}else{ 
						// any other element including 'and'
						scale = 1;
						increment = it->second;
					}

					// obtain current working value
					current = current * scale + increment;

					// if a 10^3 or 10^6 has been applied, reset current working value 
					// (limit is 10^9: numbers greater than a thousand million - a billion- are not valid ) 
					if (scale > 100){
						result = result + current;
						current = 0;
					}
					
					// apply some logic for 'and' element or continue if there are more elements of a number
					if (*it_match=="and"){
						// 'and' is not part of a number in the first or last position
						// 'and' followed by an element not in the dictionary is not a part of a number
						if(it_match == tokens.begin() || next(it_match) == tokens.end()){
							if (current > 0)
								output_str = output_str + " " + to_string(result+current) ;
							match = false;
						}else if(next(it_match) != tokens.end() && dictionary.find(*(next(it_match))) == dictionary.end()){
							match = false;
						}else{
							continue;
						}
					}else if (next(it_match) != tokens.end() && dictionary.find(*(next(it_match))) != dictionary.end()){ 
						continue;
					}

				}else{
					// not a match
					result = 0;
					current = 0;
					match = false;
				}

				// add words or translated numbers
				if (match)
					output_str = output_str + to_string(result + current) + " ";
				else
					output_str = output_str + *it_match + " ";	
	
			} 
 	
			// remove end space 
			output_str.erase(output_str.end() - 1);
			// return result
			return output_str;
		}

		// test method
		void test1()
		{
			string test_string = "two";
			string expected_result = "2";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 1]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test2()
		{
			string test_string = "eleven";
			string expected_result = "11";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 2]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test3()
		{
			string test_string = "one hundred and one";
			string expected_result = "101";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 3]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test4()
		{
			string test_string = "seven hundred fifty six";
			string expected_result = "756";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 4]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test5()
		{
			string test_string = "five thousand seven hundred and three";
			string expected_result = "5703";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 5]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test6()
		{
			string test_string = "eighty thousand nine hundred sixty four";
			string expected_result = "80964";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 6]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test7()
		{
			string test_string = "nine hundred thousand fifty three";
			string expected_result = "900053";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 7]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test8()
		{
			string test_string = "seven million seven hundred";
			string expected_result = "7000700";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 8]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test9()
		{
			string test_string = "nine hundred ninety nine million nine hundred ninety nine thousand nine hundred ninety nine";
			string expected_result = "999999999";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 9]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test10()
		{
			string test_string = "this is a test with one number: five thousand seven hundred and three ... is it ok?";
			string expected_result = "this is a test with 1 number: 5703 ... is it ok?";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 10]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test11()
		{
			string test_string = "this is a test with two numbers: first number is five thousand seven hundred and three second number is one million seven hundred sixty two ... is it ok?";
			string expected_result = "this is a test with 2 numbers: first number is 5703 second number is 1000762 ... is it ok?";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 11]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test12()
		{
			string test_string = "this is just a text test";
			string expected_result = "this is just a text test";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 12]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test13()
		{
			string test_string = "and (at the start) and (in the middle) & (at the end) and";
			string expected_result = "and (at the start) and (in the middle) & (at the end) and";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 13]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test14()
		{
			string test_string = "+-#%&/";
			string expected_result = "+-#%&/";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 14]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}

		// test method
		void test15()
		{
			string test_string = "";
			string expected_result = "";
			string translated_result = translate(string2vector(test_string));
			string result = "";
						
			cout << "[Test 15]: " << compare(expected_result,translated_result) << " -> " << expected_result << " vs " << translated_result << "\n";	
		}


		// test method
		void test()
		{
			cout << "------- text2number Test -------\n";
			test1();
			test2();
			test3();
			test4();
			test5();
			test6();
			test7();
			test8();
			test9();
			test10();
			test11();
			test12();
			test13();
			test14();
			test15();
			cout << "--------------------------------\n";
		}

		// string2vector method
		vector<string> string2vector(string s)
		{
			istringstream iss(s);
			vector<string> v{istream_iterator<string>{iss},istream_iterator<string>{}};
	
			return v;
		}

		// compare method
		string compare(string expected_result, string translated_result)
		{
			string result = "";

			if (expected_result == translated_result) 
				result = "OK";
			else
				result = "WRONG";

			return result;
		}



};

int main (int argc, char *argv[]){

	vector<string> tokens;
	bool test = false;

	// check if input args are correct
	if (argc > 1){
		if (std::string(argv[1]) == "--test"){
			// test mode
			test = true;
		}else if (std::string(argv[1]) == "--info"){
			// print information	
			cout << "text2number information: \n text2number converts numbers (written in words) in a string into their numerical value. \n Valid number range: from 0 to 999999999 \n\n" ;
			cout << "text2number usage: \n 'text2number text_to_convert' \n 'text2number --test' for testing purposes \n 'text2number --info' for extra information" << "\n";
			return 0;
		}else{
			// prepare tokens vector
			for(int i=1; i<argc; i++)
				tokens.push_back(argv[i]);
		}
  	}else{
		// print usage
		cout << "text2number usage: \n 'text2number text_to_convert' \n 'text2number --test' for testing purposes \n 'text2number --info' for extra information" << "\n";
		return 0;
  	}
  
	Translator translator;

	if (test)
		translator.test();
	else
		cout << translator.translate(tokens) << "\n";

  	return 0;
}
