#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

// Method iterates file by char, looks for end-of-line characters, count them and returns its number.
int get_lines(std::ifstream &inputFile){
    if (inputFile.peek() == std::ifstream::traits_type::eof())
        return 0;
    else {
        int lines_number = std::count(std::istreambuf_iterator<char>(inputFile),
                                      std::istreambuf_iterator<char>(), '\n') + 1;
        return lines_number;
    }
}

// Method read file by char till end of its.
// In every loop program check if char is digit - if so, increments counter variable.
// After ending the loop method returns digits number.
int get_digits(std::ifstream &inputFile){
    int digits_number = 0;
    char ch;
    while (inputFile.get(ch)) {
        if (isdigit(ch))
            digits_number++;
    }
    return digits_number;
}

std::vector<int> get_numbers(std::ifstream &inputFile){

    // previous_char have to be ' ' in the case of a digit in the first place in the file
    char previous_char = ' ', current_char;
    std::string number; // stores legal characters - builds the number
    std::vector<int> numbers;

    // getting char till the end of the file
    while (inputFile >> std::noskipws >> current_char) {

        // char is a digit
        if (isdigit(current_char)) {
            if (isspace(previous_char)) number=current_char;
            else if (previous_char == '-' || isdigit(previous_char)) number+=current_char;
        }

        // char is a space -> checking if the previous char is a digit and the string number is not empty
        // (then we know if string stores number or there was some illegal character before
        //  - we don't want to add an empty string to vector)
        else if (isspace(current_char) && isdigit(previous_char) && !number.empty()) numbers.push_back(stoi(number));

        // we want only one minus char before number
        else if (current_char == '-') number='-';

        // if an illegal char \/ we don't care about the numbers followed by other sign than space.
        else number = "";

        previous_char = current_char;
    }
    //last char can be digit
    if (isdigit(current_char)) numbers.push_back(stoi(number));

    return numbers;
}

int get_chars(std::ifstream &inputFile){
    int counter=0;
    char ch=0;
    while (inputFile >> std::noskipws >> ch) counter++;
    return counter;
}

std::vector<std::string> get_words_from_file(std::ifstream &inputFile){
    std::vector<std::string> words;
    std::string word;
    while (inputFile >> word) words.push_back(word);
    return words;
}

std::vector<std::string> get_anagrams(std::vector<std::string> &parameters, std::ifstream &inputFile){

    std::vector<std::string> words_from_file = get_words_from_file(inputFile);
    std::vector<std::string> parameters_sorted = parameters; // maybe some smarter solution than copy here?
    for (std::string &s : words_from_file) sort(s.begin(), s.end()); // <- sort z std czy bez?
    for (std::string &s : parameters_sorted) sort(s.begin(), s.end());

    std::vector<std::string> result;

    for (int i=0; i<parameters.size(); i++) {
        for (std::string s : words_from_file){
            if (parameters_sorted.at(i) == s) {
                result.push_back(parameters.at(i));
                break;
            }
        }
    }

    return result;
}

std::vector<std::string> get_words_AtoZ(std::ifstream &inputFile){
    std::vector<std::string> words = get_words_from_file(inputFile);
    std::sort(words.begin(), words.end());
    return words;
}

std::vector<std::string> get_words_ZtoA(std::ifstream &inputFile){
    std::vector<std::string> words_ZtoA = get_words_from_file(inputFile);
    std::reverse(words_ZtoA.begin(),words_ZtoA.end());
    return words_ZtoA;
}

//int main(int argc, char** argv) {
int main(int argc, char** argv) {

//    std::string a = "-1";
//    std::cout << stoi(a);
    std::string program_description = "\nPJAText \n\n"
                                      "This program is used to work with files. Using flags You can get:\n"
                                      "- number of words, numbers, lines in file;\n"
                                      "- the most frequently appearing characters, words and numbers in the file;\n"
                                      "- anagrams and palindromes;\n"
                                      "- organize the contents of a file.\n";

    if (argc == 1){
        std::cout << program_description;
    } else {
        std::string inputs[argc-1];
        for (int i=0; i<argc-1; i++){
            inputs[i] = argv[i+1];
//            std::cout << inputs[i];
        }

        //if -f flag and file excepted
        if (inputs[0] == "-f"){
            //if file path specified
            if (argc < 3){
                std::cout << "File path excepted after -f flag.";
            } else {
                std::ifstream file(inputs[argc-2], std::fstream::in);
                std::vector<std::string> a ={"eli1n","76"};
                std::vector<std::string> anagrams = get_anagrams(a, file);
                for (std::string s : anagrams)
                    std::cout << s << "\n";
            }
        } else {
            std::cout << "Other";
        }
//        std::string file = argv[2];
//        std::cout << "Typed file: " << file;
    }



//    if (file.empty()){
//        std::cout << "No file typed. Program description: ...\n";
//        std::cout << program_description;
//    } else {
////        std::cout << file;
//    }

//    int retCode = system("prog.exe \"arg 1\" arg2 arg3");

//    std::cout << program_description;


//    std::cin >> file;
//    switch () {
//
//    }
}
