#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

//some stuff to help later:
//paddle_1: Right paddle same for paddle_1_x and paddle_1_y
//text_1: Text displayed for the right paddle
//score_1: Score displayed for the right paddle

//paddle_2: Left paddle same for paddle_2_x and paddle_2_y
//text_2: Text displayed for the left right
//score_2: Score displayed for the left paddle

//text_3: game over screen when right paddle wins(if score_1 == 11)
//text_4: game over screen when left paddle wins(if score_2 == 11)

class Ball{
protected:
    float screen_width = 800;
    float screen_height = 600;

public:

    //attributes

    float ball_x; //ball is a square 20x20
    float ball_y;

    float speed_x;
    float speed_y;

    //method
    void restrictingBall(float screen_width, float screen_height, float & ball_x, float & ball_y, float & speed_x, float & speed_y, sf::RectangleShape ball){
        if (ball_y <= 0)
        {
            speed_y *= -1;
            ball_x += speed_x;
            ball_y += speed_y;
        }

        if (ball_y >= screen_height - 20)
        {
            speed_y *= -1;
            ball_x += speed_x;
            ball_y += speed_y;
        }

    }

};

class Collision: public Ball{
public:
    void collision(float paddle_1_y, sf::RectangleShape & paddle_1, sf::RectangleShape & ball){
        if (paddle_1.getGlobalBounds().intersects(ball.getGlobalBounds()))
        {

            if (ball_y + 10 > paddle_1_y + 50)
            {
                speed_x *= -1;
                speed_x -= 0.05;
                speed_y = 0.10;
                ball_x += speed_x;
                ball_y += speed_y;
            }

            if (ball_y + 10 < paddle_1_y + 50)
            {
                speed_x *= -1;
                speed_x -= 0.05;
                speed_y = -0.10;
                ball_x += speed_x;
                ball_y += speed_y;
            }

            if (ball_y + 10 == paddle_1_y + 50)
            {
                speed_x *= -1;
                speed_x -= 0.05;
                speed_y = 0;
                ball_x += speed_x;
                ball_y += speed_y;
            }
        }


}};

int main()
{

    float screen_width{800};
    float screen_height{600};

    Ball PongBall;

    Collision collision_paddle_1;

    PongBall.ball_x = screen_width / 2 - 10;
    PongBall.ball_y = screen_height / 2 - 10;

    PongBall.speed_x = 0.2;
    PongBall.speed_y = 0.2;

    float paddle_1_x{screen_width - 10};
    float paddle_1_y{screen_height / 2 - 50};

    float paddle_2_x{0};
    float paddle_2_y{screen_height / 2 - 50};


    std::string p1_dir{"STOP"};
    std::string p2_dir{"STOP"};


    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Ping Pong");

    int score_1{0};
    int score_2{0};

    sf::Font font;

    font.loadFromFile("28 Days Later.ttf");

    sf::Text text_1;

    text_1.setFont(font);
    text_1.setString(std::to_string(score_1));

    text_1.setCharacterSize(50);

    text_1.setFillColor(sf::Color::White);

    text_1.setPosition(screen_width - 50, 0);

    sf::Text text_2;

    text_2.setFont(font);
    text_2.setString(std::to_string(score_2));

    text_2.setCharacterSize(50);
    text_2.setFillColor(sf::Color::White);

    text_2.setPosition(50, 0);

    sf::Text text_3;

    text_3.setFont(font);
    text_3.setString("Game Over! Right Paddle Wins! ");

    text_3.setCharacterSize(50);
    text_3.setFillColor(sf::Color::White);

    text_3.setPosition(-10000, -10000);

    sf::Text text_4;

    text_4.setFont(font);
    text_4.setString("Game Over! Left Paddle Wins! ");

    text_4.setCharacterSize(50);
    text_4.setFillColor(sf::Color::White);

    text_4.setPosition(-10000, -10000);

    // Load sprites to display
    sf::RectangleShape ball(sf::Vector2<float>(20, 20));
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(sf::Vector2<float>(PongBall.ball_x, PongBall.ball_y));

    sf::RectangleShape paddle_1(sf::Vector2f(10, 100));
    paddle_1.setPosition(sf::Vector2<float>(paddle_1_x, paddle_1_y));

    paddle_1.setFillColor(sf::Color::Green);


    sf::RectangleShape paddle_2(sf::Vector2f(10, 100));
    paddle_2.setPosition(sf::Vector2<float>(paddle_2_x, paddle_2_y));

    paddle_2.setFillColor(sf::Color::Blue);

    //sf::Font myfont;
    //myfont.loadFromFile("space_invaders.ttf");
    ////sf::Text countdown;
    //countdown.setFont(myfont);

    // Start the game loop
    while (window.isOpen())
    {
        //events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    p1_dir = "UP";
                }

                if (event.key.code == sf::Keyboard::Down)
                {
                    p1_dir = "DOWN";
                }

                if (event.key.code == sf::Keyboard::W)
                {
                    p2_dir = "UP";
                }

                if (event.key.code == sf::Keyboard::S)
                {
                    p2_dir = "DOWN";
                }
            }

            if(event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    p1_dir = "STOP";
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    p1_dir = "STOP";
                }

                if (event.key.code == sf::Keyboard::W)
                {
                    p2_dir = "STOP";
                }

                if (event.key.code == sf::Keyboard::S)
                {
                    p2_dir = "STOP";
                }

            }
        }

        //logic

        if (p1_dir == "UP")
        {
            paddle_1_y -= 0.5;
            paddle_1.setPosition(sf::Vector2<float>(paddle_1_x, paddle_1_y));
            paddle_1.setFillColor(sf::Color::Green);
        }

        if (p1_dir == "DOWN")
        {
            paddle_1_y += 0.5;
            paddle_1.setPosition(sf::Vector2<float>(paddle_1_x, paddle_1_y));
            paddle_1.setFillColor(sf::Color::Green);
        }


        if (paddle_1_y >= screen_height - 100)
        {
            paddle_1_y = screen_height - 100;
            paddle_1_y += 0;
        }

        if (paddle_1_y <= 0)
        {
            paddle_1_y = 0;
            paddle_1_y -= paddle_1_y;
        }


        if (p1_dir == "STOP")
        {
            paddle_1_y = paddle_1_y;
            paddle_1.setPosition(sf::Vector2<float>(paddle_1_x, paddle_1_y));
            paddle_1.setFillColor(sf::Color::Green);
        }

        if (p2_dir == "UP")
        {
            paddle_2_y -= 0.5;
            paddle_2.setPosition(sf::Vector2<float>(paddle_2_x, paddle_2_y));
            paddle_2.setFillColor(sf::Color::Blue);
        }

        if (p2_dir == "DOWN")
        {
            paddle_2_y += 0.5;
            paddle_2.setPosition(sf::Vector2<float>(paddle_2_x, paddle_2_y));
            paddle_2.setFillColor(sf::Color::Blue);
        }

        if (paddle_2_y >= screen_height - 100)
        {
            paddle_2_y = screen_height - 100;
            paddle_2_y += 0;
        }

        if (paddle_2_y <= 0)
        {
            paddle_2_y = 0;
            paddle_2_y -= paddle_2_y;
        }


        if (p2_dir == "STOP")
        {
            paddle_2_y = paddle_2_y;
            paddle_2.setPosition(sf::Vector2<float>(paddle_2_x, paddle_2_y));
            paddle_2.setFillColor(sf::Color::Blue);
        }

        PongBall.ball_x += PongBall.speed_x;
        PongBall.ball_y += PongBall.speed_y;
        ball.setPosition(sf::Vector2<float>(PongBall.ball_x, PongBall.ball_y));

        PongBall.restrictingBall(screen_width, screen_height, PongBall.ball_x, PongBall.ball_y, PongBall.speed_x, PongBall.speed_y, ball);

        if (PongBall.ball_x >= screen_width - 20)
        {
            PongBall.ball_x = screen_width / 2 - 10;
            PongBall.ball_y = screen_height / 2 - 10;

            PongBall.speed_x = 0.2;
            PongBall.speed_y *= -1;

            PongBall.ball_x += PongBall.speed_x;
            PongBall.ball_y += PongBall.speed_y;

            score_2 += 1;
            text_2.setString(std::to_string(score_2));
        }

        if (PongBall.ball_x <= 0)
        {
            PongBall.ball_x = screen_width / 2 - 10;
            PongBall.ball_y = screen_height / 2 - 10;

            PongBall.speed_x = 0.2;
            PongBall.speed_y *= -1;

            PongBall.ball_x += PongBall.speed_x;
            PongBall.ball_y += PongBall.speed_y;

            score_1 += 1;
            text_1.setString(std::to_string(score_1));
        }

        if (paddle_1.getGlobalBounds().intersects(ball.getGlobalBounds()))
        {

            if (PongBall.ball_y + 10 > paddle_1_y + 50)
            {
                PongBall.speed_x *= -1;
                PongBall.speed_x -= 0.05;
                PongBall.speed_y = 0.10;
                PongBall.ball_x += PongBall.speed_x;
                PongBall.ball_y += PongBall.speed_y;
            }

            if (PongBall.ball_y + 10 < paddle_1_y + 50)
            {
                PongBall.speed_x *= -1;
                PongBall.speed_x -= 0.05;
                PongBall.speed_y = -0.10;
                PongBall.ball_x += PongBall.speed_x;
                PongBall.ball_y += PongBall.speed_y;
            }

            if (PongBall.ball_y + 10 == paddle_1_y + 50)
            {
                PongBall.speed_x *= -1;
                PongBall.speed_x -= 0.05;
                PongBall.speed_y = 0;
                PongBall.ball_x += PongBall.speed_x;
                PongBall.ball_y += PongBall.speed_y;
            }
        }

        collision_paddle_1.collision(paddle_1_y, paddle_1, ball);

        if (score_1 == std::max(0, 11))
        {
            paddle_1.setPosition(-10000, -10000);
            paddle_2.setPosition(-10000, -10000);
            ball.setPosition(-500, -500);

            PongBall.speed_x = 0;
            PongBall.speed_y = 0;

            text_3.setPosition(screen_width / 2 - 300, screen_height / 2);
        }

        if (score_2 == 11)
        {
            paddle_1.setPosition(-10000, -10000);
            paddle_2.setPosition(-10000, -10000);
            ball.setPosition(-500, -500);

            PongBall.speed_x = 0;
            PongBall.speed_y = 0;

            text_4.setPosition(screen_width / 2 - 300, screen_height / 2);
        }

        //display
        window.clear();
        window.draw(text_1);
        window.draw(text_2);
        window.draw(text_3);
        window.draw(text_4);
        window.draw(ball);
        window.draw(paddle_1);
        window.draw(paddle_2);
        window.display();
    }

    return EXIT_SUCCESS;
}
