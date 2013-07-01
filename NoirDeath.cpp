#include <iostream>

#include <SFML/Graphics.hpp>

#define BLOCK_COLS 20
#define BLOCK_LINES 10
#define BLOCK_SIZE 40

int main() {

        sf::RenderWindow win(sf::VideoMode(BLOCK_COLS * BLOCK_SIZE, BLOCK_LINES * BLOCK_SIZE), "nanoLD - Fififox - Noir Death");

        win.Clear();
        win.Draw(sf::Text("\tNoir...\tDeath...\n\tDon't let the light take us!"));
        win.Display();
        sf::Sleep(3000);

        bool cells[BLOCK_COLS * BLOCK_LINES];

        for (unsigned line = 0; line < BLOCK_LINES; ++line)
                for (unsigned col = 0; col < BLOCK_COLS; ++col)
                        cells[line * BLOCK_COLS + col] = col < BLOCK_COLS / 2;

        unsigned remaining = BLOCK_COLS * BLOCK_LINES / 2;

        while (win.IsOpened() and remaining and remaining != BLOCK_COLS * BLOCK_LINES) {

                win.Display();

                sf::Event event;
                while (win.PollEvent(event)) {

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

                        if ((event.Type == sf::Event::KeyPressed and event.Key.Code == sf::Keyboard::Escape) or event.Type == sf::Event::Closed)
                                win.Close();
                        else if (event.Type == sf::Event::MouseButtonPressed) {

                                unsigned x = ( event.MouseButton.X * BLOCK_COLS ) / win.GetWidth();
                                unsigned y = ( event.MouseButton.Y * BLOCK_LINES) / win.GetHeight();

                                const bool old = cells[y * BLOCK_COLS + x];
                                remaining += old ? -1 : 1;
                                cells[y * BLOCK_COLS + x] = not old;

                        }

                }

                win.Clear();

                for (unsigned line = 0; line < BLOCK_LINES; ++line)
                        for (unsigned col = 0; col < BLOCK_COLS; ++col)
                                win.Draw(sf::Shape::Rectangle(sf::FloatRect(sf::Vector2f(col, line) * static_cast<float>(BLOCK_SIZE), sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)), (cells[line * BLOCK_COLS + col] ? sf::Color(255, 255, 255) : sf::Color(0, 0, 0))));

        }

        if (not win.IsOpened())
                return 0;

        win.Clear();

        if (not remaining)
                win.Draw(sf::Text("\tNoir... Death... Our Victory!"));
        else
                win.Draw(sf::Text("\tWhy?\tWhy did you abandon us?\tAAAaaarrrggghhh!!!"));

        win.Display();

        sf::Event event;
        while (true)
                if (win.PollEvent(event) and ((event.Type == sf::Event::KeyPressed and event.Key.Code == sf::Keyboard::Escape) or event.Type == sf::Event::Closed))
                        return 0;

}
