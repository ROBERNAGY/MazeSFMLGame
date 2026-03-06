#include "MenuController.h"

MenuController::MenuController() {
    
}

bool MenuController::WinWindow()
{
    sf::RenderWindow window(
        sf::VideoMode(600, 300),
        "You Win",
        sf::Style::Fullscreen | sf::Style::Titlebar
    );

    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        std::cout << "Could not load font!\n";
        return -1;
    }

    sf::Text winText;
    winText.setFont(font);
    winText.setString("YOU WIN");
    winText.setCharacterSize(128);
    winText.setFillColor(sf::Color::Yellow);

    sf::FloatRect bounds1 = winText.getLocalBounds();
    winText.setOrigin(bounds1.width / 2, bounds1.height / 2);
    winText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.5f);

    sf::Text winText2;
    winText2.setFont(font);
    winText2.setString("Press R to play again");
    winText2.setCharacterSize(40);
    winText2.setFillColor(sf::Color::Yellow);

    sf::FloatRect bounds2 = winText2.getLocalBounds();
    winText2.setOrigin(bounds2.width / 2, bounds2.height / 2);
    winText2.setPosition(window.getSize().x / 2.0f, window.getSize().y / 1.4f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
                window.close();
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::R)
            {
                window.close();
                return 1;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(winText);
        window.draw(winText2);
        window.display();
    }
    return 0;
}


bool MenuController::gameplayWindow()
{
    sf::RenderWindow window(sf::VideoMode(1975, 950), "Maze", sf::Style::Fullscreen);
    sf::View view = window.getDefaultView();
    view.zoom(0.4f);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("assets/Sound/SneakyAdventure.mp3"))
    {
        std::cout << "Error loading sound file!" << std::endl;
        std::cout << "error loading sound !!" << std::endl;
    }
    sf::Sound sound;
    sound.setVolume(10.0f);
    sound.setBuffer(buffer);
    sound.setLoop(true);
    sound.play();


    sf::Texture wallTexture;
    sf::Texture pathTexture;
    if (!wallTexture.loadFromFile("assets/wall.png") ||
        !pathTexture.loadFromFile("assets/path.png")) {
        std::cout << "error loading wall or path texture !!" << std::endl;
    }
    sf::Sprite wallSprite(wallTexture);
    sf::Sprite pathSprite(pathTexture);

    sf::Clock clock;
    float deltaTime = 0.0f;
    float lastFrameTime = 0.0f;

    Player player(sf::Vector2f(2 * 64.f / 2, 2 * 64.f / 2), 150.0f);

    int size = 31;
    int sizeTwo = 61;
    const int cellSize = 64;
    Maze maze(size, sizeTwo, cellSize);
    InputHandler input;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        sf::Vector2f oldPos = player.getPlayerPosition();

        deltaTime = clock.getElapsedTime().asSeconds() - lastFrameTime;
        lastFrameTime = clock.getElapsedTime().asSeconds();

        PlayerCommand command = input.getCommand();
        player.move(command, deltaTime);

        if (maze.checkCollided(player.getGlobalBound()))
        {
            player.setPlayerPosition(oldPos);
        }

        if (maze.isWin(player.getGlobalBound()))
        {
            sound.stop();
            window.close();
            return 1;
        }
        view.setCenter(player.getPlayerPosition());
        window.setView(view);
        window.clear(sf::Color::Black);
        maze.mazeDraw(window, wallSprite, pathSprite);
        maze.drawWinPosition(window);
        window.draw(player.CurrentAnimaton());
        window.display();
    }
    return 0;
}
