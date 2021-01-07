#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

// Method iterates file by char, looks for end-of-line characters, count them and returns its number.
int get_lines(std::string &path){
    std::ifstream inputFile(path, std::fstream::in);
    if (inputFile.peek() == std::ifstream::traits_type::eof()){
//        inputFile.close();
        return 0;
    } else {
        int lines_number = std::count(std::istreambuf_iterator<char>(inputFile),
                                      std::istreambuf_iterator<char>(), '\n') + 1;
//        inputFile.close();
        return lines_number;
    }
}

// Method read file by char till end of its.
// In every loop program check if char is digit - if so, increments counter variable.
// After ending the loop method returns digits number.
int get_digits(std::string &path){
    std::ifstream inputFile(path, std::fstream::in);
    int digits_number = 0;
    char ch;
    while (inputFile.get(ch)) {
        if (isdigit(ch))
            digits_number++;
    }
    return digits_number;
}

std::vector<int> get_numbers(std::string &path){

    std::ifstream inputFile(path, std::fstream::in);
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

int get_chars(std::string &path){
    std::ifstream inputFile(path, std::fstream::in);
    int counter=0;
    char ch=0;
    while (inputFile >> std::noskipws >> ch) counter++;
    return counter;
}

std::vector<std::string> get_words_from_file(std::string &path){
    std::ifstream inputFile(path, std::fstream::in);
    std::vector<std::string> words;
    std::string word;
    while (inputFile >> word) words.push_back(word);
    return words;
}

std::vector<std::string> get_anagrams(std::vector<std::string> &parameters, std::string &path){

    std::vector<std::string> words_from_file = get_words_from_file(path);
//    std::vector<std::string> parameters_sorted = parameters; // maybe some smarter solution than copy here?
//    for (std::string &s : words_from_file) sort(s.begin(), s.end());
    for (std::string &s : parameters) sort(s.begin(), s.end());

    std::vector<std::string> result;

    for (std::string s1 : words_from_file) {
        for (std::string s2 : parameters){
            std::string tmp = s1;
            sort(tmp.begin(), tmp.end());
            if (s2 == tmp) {
                result.push_back(s1);
                break;
            }
        }
    }

    return result;
}

// Method gets typed words and selected file and return vector of palindromes from file.
std::vector<std::string> get_palindromes(std::vector<std::string> &parameters, std::string &path){

    std::vector<std::string> result;
    std::vector<std::string> words_from_file = get_words_from_file(path);
    for (std::string &s : parameters) reverse(s.begin(), s.end());

    for (auto i = words_from_file.begin(); i != words_from_file.end(); ++i) // iterates through "file"
        if (std::find(parameters.begin(), parameters.end(), *i) != parameters.end()) result.push_back(*i); // looks for same words

    return result;
}

std::vector<std::string> get_words_AtoZ(std::string &path){
    std::vector<std::string> words_AtoZ = get_words_from_file(path);
    std::sort(words_AtoZ.begin(), words_AtoZ.end());
    return words_AtoZ;
}

std::vector<std::string> get_words_ZtoA(std::string &path){
    std::vector<std::string> words = get_words_AtoZ(path);
    std::reverse(words.begin(), words.end());
    return words;
}

void resolve(int &argc, std::string inputs[]) {


    std::string program_description = "\nPJAText \n\n"
                                      "This program is used to work with files. Using flags You can get:\n"
                                      "- number of words, numbers, lines in file;\n"
                                      "- the most frequently appearing characters, words and numbers in the file;\n"
                                      "- anagrams and palindromes;\n"
                                      "- organize the contents of a file.\n";

    if (argc < 2){
        std::cout << program_description;
    }
    if (argc == 2) {
        std::cout << "\nProgram excepts parameters like:\n"
                     "a) -f path_to_file *flags\n"
                     "b) -i file_with_flags\n";
    }
    else if (argc > 2) {
        std::ifstream file(inputs[1], std::fstream::in);
        if (file.good()) {
            if (inputs[0] == "-f") {
                file.close();
                std::ofstream output_file;

                std::vector<std::string> result;
                std::vector<std::string> words_parameters;
                bool to_output = false;

                for (int i = 2; i < argc - 1; ++i) {
                    if ((inputs[i] == "-n") || (inputs[i] == "--newlines"))
                        result.push_back("Number of lines: " + std::to_string(get_lines(inputs[1])) + "\n");

                    else if ((inputs[i] == "-d") || (inputs[i] == "--digits"))
                        result.push_back("Number of digits: " + std::to_string(get_digits(inputs[1])) + "\n");

                    else if ((inputs[i] == "-dd") || (inputs[i] == "--numbers")) {
                        result.push_back("Numbers: ");
                        std::vector<int> numbers = get_numbers(inputs[1]);
                        for (int i : numbers) result.push_back(std::to_string(i) + " ");
                        result.push_back("\n");

                    } else if ((inputs[i] == "-c") || (inputs[i] == "--chars"))
                        result.push_back("Number of characters: " + std::to_string(get_chars(inputs[1])) + "\n");

                    else if ((inputs[i] == "-a") || (inputs[i] == "--anagrams")) {
                        for (int j = i + 1; j < argc - 1; ++j) {
                            words_parameters.push_back(inputs[j]);
                        }
                        std::vector<std::string> anagrams = get_anagrams(words_parameters, inputs[1]);
                        result.push_back("Anagrams: ");
                        for (std::string s : anagrams) result.push_back(s + " ");
                        break;

                    } else if ((inputs[i] == "-p") || (inputs[i] == "--palindromes")) {
                        for (int j = i + 1; j < argc - 1; ++j)
                            words_parameters.push_back(inputs[j]);

                        std::vector<std::string> anagrams = get_palindromes(words_parameters, inputs[1]);
                        result.push_back("Palindromes: ");
                        for (std::string s : anagrams) result.push_back(s + " ");
                        break;

                    } else if ((inputs[i] == "-s") || (inputs[i] == "--sorted")) {
                        result.push_back("Words in A-Z order: ");
                        std::vector<std::string> words = get_words_AtoZ(inputs[1]);
                        for (std::string s : words) result.push_back(s + " ");
                        result.push_back("\n");

                    } else if ((inputs[i] == "-rs") || (inputs[i] == "--reverse-sorted")) {
                        result.push_back("Words in Z-A order: ");
                        std::vector<std::string> words = get_words_ZtoA(inputs[1]);
                        for (std::string s : words) result.push_back(s + " ");
                        result.push_back("\n");

                    } else if ((inputs[i] == "-o") || (inputs[i] == "--output")) {
                        output_file.open(inputs[i + 1]);
                        to_output = true;
                        i++;

                    } else result.push_back("Illegal flag: " + inputs[i] + "\n");
                }

                if (to_output) {
                    for (std::string s : result) output_file << s;
                    output_file.close();
                    std::cout << "Result saved to file.\n";
                } else for (std::string s : result) std::cout << s;

            } else if ((inputs[0] == "-i")  || (inputs[0] == "--input")) {
                std::ifstream external_file(inputs[1], std::fstream::in);
                std::vector<std::string> v = get_words_from_file(inputs[1]);
                int size = v.size() + 2;
                std::string external[size];
                int i = 0;
                for (std::string s : v) {
                    external[i] = s;
                    i++;
                }
                external_file.close();
                resolve(size, external);
            }  else {
                std::cout << "Illegal first flag.\n";
            }
        } else {
            std::cout << "Wrong path to file: " << inputs[1] << "\n";
        }
    }
}

int main(int argc, char** argv) {

    std::string inputs[argc-1];
    for (int i=0; i<argc-1; i++) {
        inputs[i] = argv[i + 1];
    }

    resolve(argc, inputs);
}


