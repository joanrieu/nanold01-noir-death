#include <iostream>

#include <SFML/Graphics.hpp>

#define BLOCK_COLS 20
#define BLOCK_LINES 10
#define BLOCK_SIZE 40

int main() {

        sf::RenderWindow win(sf::VideoMode(BLOCK_COLS * BLOCK_SIZE, BLOCK_LINES * BLOCK_SIZE), "nanoLD - Fififox - Noir Death");
        win.setMouseCursorVisible(true);
        sf::Font font;
        font.loadFromFile("Tuffy.ttf");

        win.clear();
        win.draw(sf::Text("\tNoir...\tDeath...\n\tDon't let the light take us!", font));
        win.display();
        sf::sleep(sf::milliseconds(3000));

        bool cells[BLOCK_COLS * BLOCK_LINES];

        for (unsigned line = 0; line < BLOCK_LINES; ++line)
                for (unsigned col = 0; col < BLOCK_COLS; ++col)
                        cells[line * BLOCK_COLS + col] = col < BLOCK_COLS / 2;

        unsigned remaining = BLOCK_COLS * BLOCK_LINES / 2;

        while (win.isOpen() and remaining and remaining != BLOCK_COLS * BLOCK_LINES) {

                win.display();

                sf::Event event;
                while (win.pollEvent(event)) {

                        {

                                unsigned pos1 = (rand() % BLOCK_LINES) * BLOCK_COLS + (rand() % BLOCK_COLS);
                                unsigned pos2 = (rand() % BLOCK_LINES) * BLOCK_COLS + (rand() % BLOCK_COLS);

                                const bool cheat = not (rand() % 4);
                                const bool old = cells[pos1];
                                cells[pos1] = cells[pos2];
                                cells[pos2] = cheat ? true : old;

                                if (cheat and not old)
                                        ++remaining;

                        }

                        if ((event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape) or event.type == sf::Event::Closed)
                                win.close();
                        else if (event.type == sf::Event::MouseButtonPressed) {

                                unsigned x = ( event.mouseButton.x * BLOCK_COLS ) / win.getSize().x;
                                unsigned y = ( event.mouseButton.y * BLOCK_LINES) / win.getSize().y;

                                const bool old = cells[y * BLOCK_COLS + x];
                                remaining += old ? -1 : 1;
                                cells[y * BLOCK_COLS + x] = not old;

                        }

                }

                win.clear();

                for (unsigned line = 0; line < BLOCK_LINES; ++line) {
                        for (unsigned col = 0; col < BLOCK_COLS; ++col) {
                                sf::RectangleShape rect(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                                rect.setPosition(sf::Vector2f(col, line) * static_cast<float>(BLOCK_SIZE));
                                rect.setFillColor(cells[line * BLOCK_COLS + col] ? sf::Color(255, 255, 255) : sf::Color(0, 0, 0));
                                win.draw(rect);
                        }
                }

        }

        if (not win.isOpen())
                return 0;

        win.clear();

        if (not remaining)
                win.draw(sf::Text("\tNoir... Death... Our Victory!", font));
        else
                win.draw(sf::Text("\tWhy?\tWhy did you abandon us?\tAAAaaarrrggghhh!!!", font));

        win.display();

        sf::Event event;
        while (win.waitEvent(event))
                if ((event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape) or event.type == sf::Event::Closed)
                        return 0;

}
