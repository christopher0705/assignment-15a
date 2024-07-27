#include <iostream>
#include <stdexcept>

// Custom exception classes
class invalidCharacterException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid character input.";
    }
};

class invalidRangeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Resulting character out of range.";
    }
};

// Function prototype
char character(char start, int offset);

// Main function for testing
int main() {
    // Sample test cases
    char testCases[][2] = {
        {'a', 1},
        {'a', -1},
        {'Z', -1},
        {'?', 5},
        {'A', 32}
    };

    for (auto& test : testCases) {
        try {
            char result = character(test[0], test[1]);
            std::cout << "character('" << test[0] << "', " << test[1] << ") returned '" << result << "'.\n";
        }
        catch (const std::exception& e) {
            std::cout << "character('" << test[0] << "', " << test[1] << ") threw an exception: " << e.what() << "\n";
        }
    }

    return 0;
}

// Function definition
char character(char start, int offset) {
    // Check if start is a valid letter
    if (!isalpha(start)) {
        throw invalidCharacterException();
    }

    char result = start + offset;

    // Check for valid range without case transition
    if (isupper(start)) {
        if (result < 'A' || result > 'Z') {
            throw invalidRangeException();
        }
    }
    else if (islower(start)) {
        if (result < 'a' || result > 'z') {
            throw invalidRangeException();
        }
    }
    else {
        throw invalidRangeException();
    }

    return result;
}
