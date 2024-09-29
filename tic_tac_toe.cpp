#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
char current_marker = 'X';
int current_player = 1;

void drawGrid(sf::RenderWindow& window) {
    // Vertical lines
    sf::RectangleShape line1(sf::Vector2f(10, 300));
    line1.setPosition(100, 0);
    line1.setFillColor(sf::Color::Black);

    sf::RectangleShape line2(sf::Vector2f(10, 300));
    line2.setPosition(200, 0);
    line2.setFillColor(sf::Color::Black);

    // Horizontal lines
    sf::RectangleShape line3(sf::Vector2f(300, 10));
    line3.setPosition(0, 100);
    line3.setFillColor(sf::Color::Black);

    sf::RectangleShape line4(sf::Vector2f(300, 10));
    line4.setPosition(0, 200);
    line4.setFillColor(sf::Color::Black);

    // Draw lines
    window.draw(line1);
    window.draw(line2);
    window.draw(line3);
    window.draw(line4);
}

void drawMarkers(sf::RenderWindow& window, sf::Font& font) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sf::Text marker;
            marker.setFont(font);
            marker.setString(string(1, board[i][j]));
            marker.setCharacterSize(60);
            marker.setFillColor(sf::Color::Black);
            marker.setPosition(j * 100 + 30, i * 100 + 10);
            window.draw(marker);
        }
    }
}

int getSlotFromClick(int x, int y) {
    int row = y / 100;
    int col = x / 100;
    return row * 3 + col + 1;
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = current_marker;
        return true;
    }
    return false;
}

void swapPlayerAndMarker() {
    if (current_marker == 'X') {
        current_marker = 'O';
        current_player = 2;
    } else {
        current_marker = 'X';
        current_player = 1;
    }
}

int checkWinner() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return current_player;
        }
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return current_player;
        }
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return current_player;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return current_player;
    }
    return 0;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 300), "Tic Tac Toe");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error loading font" << endl;
        return -1;
    }

    int winner = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int slot = getSlotFromClick(event.mouseButton.x, event.mouseButton.y);
                if (placeMarker(slot)) {
                    winner = checkWinner();
                    if (winner != 0) {
                        cout << "Player " << winner << " wins!" << endl;
                        window.close();
                    }
                    swapPlayerAndMarker();
                }
            }
        }

        window.clear(sf::Color::White);
        drawGrid(window);
        drawMarkers(window, font);
        window.display();
    }

    if (winner == 0) {
        cout << "It's a draw!" << endl;
    }

    return 0;
}