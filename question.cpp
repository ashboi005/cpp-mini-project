#include "question.h"
#include <algorithm>
#include <random>
#include <ctime>

std::vector<Question> getShuffledQuestions(std::vector<Question> questions) {
    std::srand(std::time(0));
    std::random_shuffle(questions.begin(), questions.end());
    return questions;
}

std::vector<std::string> shuffleOptions(std::vector<std::string> options, int& correctOptionIndex) {
    std::string correctOption = options[correctOptionIndex];
    std::srand(std::time(0));
    std::random_shuffle(options.begin(), options.end());

    for (size_t i = 0; i < options.size(); ++i) {
        if (options[i] == correctOption) {
            correctOptionIndex = i;
            break;
        }
    }
    return options;
}
