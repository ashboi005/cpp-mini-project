#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <sstream>
#include "question.h"

using namespace std;

class GUI {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text questionText, timerText, inputPrompt, resultText;
    vector<sf::Text> optionTexts;
    string userInput;

public:
    GUI() : window(sf::VideoMode(800, 600), "Exam System") {
        if (!font.loadFromFile("arial.ttf")) {
            throw runtime_error("Failed to load font.");
        }

        // Initialize text objects
        questionText.setFont(font);
        questionText.setCharacterSize(24);
        questionText.setPosition(50, 50);

        timerText.setFont(font);
        timerText.setCharacterSize(20);
        timerText.setPosition(650, 10);

        inputPrompt.setFont(font);
        inputPrompt.setCharacterSize(20);
        inputPrompt.setPosition(50, 400);
        inputPrompt.setString("Enter your answer (a-d): ");

        for (int i = 0; i < 4; i++) {
            sf::Text option;
            option.setFont(font);
            option.setCharacterSize(20);
            option.setPosition(50, 150 + i * 30);
            optionTexts.push_back(option);
        }
    }

    void updateTimer(int timeLeft) {
        stringstream ss;
        ss << "Time: " << timeLeft << "s";
        timerText.setString(ss.str());
    }

    void displayQuestion(const Question& question) {
        window.clear();
        questionText.setString("Question: " + question.questionText);

        for (size_t i = 0; i < question.options.size(); ++i) {
            optionTexts[i].setString(static_cast<char>('a' + i) + string(". ") + question.options[i]);
        }

        window.draw(questionText);
        for (auto& option : optionTexts) {
            window.draw(option);
        }
        window.draw(timerText);
        window.draw(inputPrompt);
        window.display();
    }

    string getUserInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return "exit";
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= 'a' && event.text.unicode <= 'd') {
                    return string(1, static_cast<char>(event.text.unicode));
                }
            }
        }
        return "";
    }

    bool isOpen() {
        return window.isOpen();
    }

    void displayResult(int score, int maxScore) {
        resultText.setFont(font);
        resultText.setCharacterSize(30);
        resultText.setString("Your score: " + to_string(score) + " / " + to_string(maxScore));
        resultText.setPosition(200, 300);

        window.clear();
        window.draw(resultText);
        window.display();
        sf::sleep(sf::seconds(5));  // Display result for 5 seconds
    }
};
