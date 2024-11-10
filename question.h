#ifndef QUESTION_H
#define QUESTION_H

#include <vector>
#include <string>

struct Question {
    std::string questionText;
    std::vector<std::string> options;
    int correctOptionIndex;
};

std::vector<Question> getShuffledQuestions(std::vector<Question> questions);
std::vector<std::string> shuffleOptions(std::vector<std::string> options, int& correctOptionIndex);

#endif
