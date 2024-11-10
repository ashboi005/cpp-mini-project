#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include "question.h"

using namespace std;

class GUI {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text questionText, timerText, inputPrompt, resultText;
    vector<sf::Text> optionTexts;
    sf::RectangleShape background;

public:
    GUI() : window(sf::VideoMode(1200, 800), "Exam System") {  // Increased window size
        if (!font.loadFromFile("arial.ttf")) {
            throw runtime_error("Failed to load font.");
        }

        // Set up background
        background.setSize(sf::Vector2f(1200, 800));
        background.setFillColor(sf::Color(30, 30, 60));  // Dark blue background

        // Initialize text objects
        questionText.setFont(font);
        questionText.setCharacterSize(36);  // Increased font size
        questionText.setFillColor(sf::Color::White);  // White text
        questionText.setPosition(50, 50);

        timerText.setFont(font);
        timerText.setCharacterSize(28);
        timerText.setFillColor(sf::Color(200, 100, 100));  // Red-ish color
        timerText.setPosition(1000, 20);

        inputPrompt.setFont(font);
        inputPrompt.setCharacterSize(28);
        inputPrompt.setFillColor(sf::Color::Yellow);
        inputPrompt.setPosition(50, 650);
        inputPrompt.setString("Enter your answer (a-d): ");

        for (int i = 0; i < 4; i++) {
            sf::Text option;
            option.setFont(font);
            option.setCharacterSize(28);
            option.setFillColor(sf::Color(180, 230, 180));  // Light green color
            option.setPosition(50, 150 + i * 50);
            optionTexts.push_back(option);
        }

        resultText.setFont(font);
        resultText.setCharacterSize(40);
        resultText.setFillColor(sf::Color::Cyan);  // Cyan result text
        resultText.setPosition(400, 350);
    }

    void updateTimer(int timeLeft) {
        stringstream ss;
        ss << "Time: " << timeLeft << "s";
        timerText.setString(ss.str());
    }

    void displayQuestion(const Question& question) {
        questionText.setString("Question: " + question.questionText);

        for (size_t i = 0; i < question.options.size(); ++i) {
            optionTexts[i].setString(static_cast<char>('a' + i) + string(". ") + question.options[i]);
        }
    }

    void draw() {
        window.clear();
        window.draw(background);  // Draw background
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
        resultText.setString("Your score: " + to_string(score) + " / " + to_string(maxScore));
        window.clear();
        window.draw(background);  // Draw background for result
        window.draw(resultText);
        window.display();
        sf::sleep(sf::seconds(5));  // Display result for 5 seconds
    }

    void handleWindowEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
};

int main() {
    GUI gui;
    vector<Question> questions = {
        {"What is 2 + 2?", {"1", "2", "3", "4"}, 3},
        {"What is the capital of France?", {"Berlin", "London", "Paris", "Rome"}, 2},
        {"Which is a programming language?", {"HTML", "CSS", "Java", "XML"}, 2},
        {"Which planet is closest to the Sun?", {"Earth", "Venus", "Mercury", "Mars"}, 2},
        {"Who wrote 'Romeo and Juliet'?", {"Shakespeare", "Hemingway", "Dickens", "Twain"}, 0},
        {"What is the boiling point of water?", {"90°C", "100°C", "120°C", "80°C"}, 1},
        {"Which is the largest ocean?", {"Atlantic", "Indian", "Pacific", "Arctic"}, 2},
        {"What is the square root of 64?", {"6", "8", "10", "7"}, 1},
        {"What is the chemical symbol for water?", {"HO", "O2", "H2O", "OH"}, 2},
        {"Who painted the Mona Lisa?", {"Van Gogh", "Da Vinci", "Picasso", "Rembrandt"}, 1},
        {"Which country has the largest population?", {"USA", "India", "China", "Russia"}, 2},
        {"What is the smallest prime number?", {"1", "2", "3", "5"}, 1},
        {"Which gas do plants absorb?", {"Oxygen", "Carbon Dioxide", "Nitrogen", "Hydrogen"}, 1},
        {"Who developed the theory of relativity?", {"Newton", "Einstein", "Tesla", "Curie"}, 1},
        {"What is the capital of Japan?", {"Seoul", "Beijing", "Tokyo", "Bangkok"}, 2},
        {"Which continent is known as the 'Dark Continent'?", {"Asia", "Africa", "Europe", "Australia"}, 1},
        {"Which planet is known as the Red Planet?", {"Venus", "Earth", "Mars", "Jupiter"}, 2},
        {"What is the national bird of the USA?", {"Eagle", "Peacock", "Swan", "Sparrow"}, 0},
        {"Which country invented pizza?", {"USA", "China", "Italy", "France"}, 2},
        {"Who discovered penicillin?", {"Darwin", "Fleming", "Pasteur", "Curie"}, 1},
        {"What is the capital of Australia?", {"Sydney", "Melbourne", "Canberra", "Brisbane"}, 2},
        {"Which planet has the most moons?", {"Earth", "Mars", "Saturn", "Jupiter"}, 3},
        {"What is the freezing point of water?", {"0°C", "32°F", "100°C", "Both A & B"}, 3},
        {"Who is known as the 'Father of Computers'?", {"Babbage", "Turing", "Jobs", "Gates"}, 0},
        {"What is the capital of Canada?", {"Toronto", "Vancouver", "Ottawa", "Montreal"}, 2},
        {"What is the main ingredient in guacamole?", {"Tomato", "Cucumber", "Avocado", "Pepper"}, 2},
        {"Which element has the atomic number 1?", {"Helium", "Hydrogen", "Oxygen", "Nitrogen"}, 1},
        {"Which is the longest river in the world?", {"Nile", "Amazon", "Yangtze", "Ganges"}, 1},
        {"Who wrote 'The Odyssey'?", {"Plato", "Homer", "Socrates", "Virgil"}, 1},
        {"What is the largest mammal?", {"Elephant", "Whale", "Shark", "Hippopotamus"}, 1}
    };


    questions = getShuffledQuestions(questions);
    vector<char> userAnswers;

    bool timeUp = false;
    int timeLeft = 3600;
    bool testComplete = false;

    // Timer thread
    thread timerThread([&]() {
        while (timeLeft > 0 && gui.isOpen() && !testComplete) {
            this_thread::sleep_for(chrono::seconds(1));
            timeLeft--;
            gui.updateTimer(timeLeft);
        }
        timeUp = true;
    });

    for (auto& question : questions) {
        if (timeUp || !gui.isOpen()) break;

        gui.displayQuestion(question);

        while (gui.isOpen()) {
            gui.handleWindowEvents();
            gui.draw();
            string answer = gui.getUserInput();
            if (!answer.empty()) {
                if (answer == "exit") break;
                userAnswers.push_back(answer[0]);
                break;
            }

            if (timeUp) break;
        }

        if (userAnswers.size() == questions.size()) {
            testComplete = true;
            break;
        }
    }

    timerThread.join();

    // Score calculation
    int score = 0;
    for (size_t i = 0; i < userAnswers.size(); ++i) {
        if ((userAnswers[i] - 'a') == questions[i].correctOptionIndex) {
            score += 4;
        } else {
            score -= 1;
        }
    }

    gui.displayResult(score, questions.size() * 4);

    return 0;
}
