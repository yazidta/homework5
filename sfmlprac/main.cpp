#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class CustomSprite : public sf::Sprite
{
public:

    void setBounds(int left, int right, int top, int bottom)
    {
        bound_top = top;
        bound_bottom = bottom;
        bound_right = right;
        bound_left = left;
    }


    bool Collision_T(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds)
    {
        if ((guy_bounds.top+guy_bounds.height >= wall_bounds.top-3) && (guy_bounds.top < wall_bounds.top)
            && (guy_bounds.left+guy_bounds.width > wall_bounds.left+3) && (guy_bounds.left < wall_bounds.left+wall_bounds.width-3))
        {
            return 1;
        }
        else{return 0;}
    }
    bool Collision_B(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds)
    {
        if ((guy_bounds.top <= wall_bounds.top+ wall_bounds.height+3) && (guy_bounds.top + guy_bounds.height > wall_bounds.top + wall_bounds.height)
            && (guy_bounds.left+guy_bounds.width > wall_bounds.left+3) && (guy_bounds.left < wall_bounds.left+wall_bounds.width-3))
        {
            return 1;
        }
        else{return 0;}
    }
    bool Collision_L(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds)
    {
        if ((guy_bounds.left + guy_bounds.width >= wall_bounds.left-3) && (guy_bounds.left < wall_bounds.left)
            && (guy_bounds.top+guy_bounds.height > wall_bounds.top+3) && (guy_bounds.top < wall_bounds.top+wall_bounds.height-3))
        {
            return 1;
        }
        else{return 0;}
    }
    bool Collision_R(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds)
    {
        if ((guy_bounds.left <= wall_bounds.left+ wall_bounds.width+3) && (guy_bounds.left + guy_bounds.width > wall_bounds.left + wall_bounds.width)
            && (guy_bounds.top+guy_bounds.height > wall_bounds.top+3) && (guy_bounds.top < wall_bounds.top+wall_bounds.height-3))
        {
            return 1;
        }
        else{return 0;}
    }


    // add other collison checking sides here


    void moveInDirection(const sf::Time &elapsed, const std::vector<sf::Sprite> &obstacles, std::vector<sf::Sprite> &hearts)
    {
        float dt = elapsed.asSeconds();

        bool top=0, left=0, bottom=0, right=0;
        for(auto &obstacle : obstacles)
        {
            sf::FloatRect guy_bounds = getGlobalBounds();
            sf::FloatRect wall_bounds = obstacle.getGlobalBounds();
            if(Collision_T(wall_bounds, guy_bounds) == 1){top = 1;}
            if(Collision_L(wall_bounds, guy_bounds) == 1){left = 1;}
            if(Collision_B(wall_bounds, guy_bounds) == 1){bottom = 1;}
            if(Collision_R(wall_bounds, guy_bounds) == 1){right = 1;}
        }

        if(left || right || top || bottom)
        {
            hearts.pop_back();
            setPosition(1.0,1.0);
        }



        sf::FloatRect rectangle_bounds = getGlobalBounds();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rectangle_bounds.top > bound_top && bottom != true)
        {
            move(0,-1*m_speed_y*dt);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rectangle_bounds.top + rectangle_bounds.height < bound_bottom && top != true)
        {
            move(0, m_speed_y*dt);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && rectangle_bounds.left + rectangle_bounds.width < bound_right && left != true)
        {
            move(m_speed_x*dt, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rectangle_bounds.left > bound_left && right != true)
        {
            move(-1*m_speed_x*dt, 0);
        }


    }


private:
    int m_speed_x = 200;
    int m_speed_y = 200;
    int bound_top = 0;
    int bound_bottom = 0;
    int bound_left = 0;
    int bound_right = 0;
};

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::Clock clock;

    sf::Texture guy_tex;
    sf::Texture grass_tex;
    sf::Texture wall_tex;
    sf::Texture heart_tex;

    if(!grass_tex.loadFromFile("grass.png")) {std::cerr << "Could not load texture" << std::endl; return 0;}
    if(!guy_tex.loadFromFile("guy.png")) {std::cerr << "Could not load texture" << std::endl; return 0;}
    if(!wall_tex.loadFromFile("wall.png")) {std::cerr << "Could not load texture" << std::endl; return 0;}
    if(!heart_tex.loadFromFile("heart.png")) {std::cerr << "Could not load texture" << std::endl; return 0;}

    CustomSprite guy;
    guy.setPosition(1.0,1.0);
    guy.setTexture(guy_tex);

    sf::Sprite grass;
    grass_tex.setRepeated(true);
    grass.setTexture(grass_tex);
    grass.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));


    std::vector<sf::Sprite> walls;

    wall_tex.setRepeated(true);
    sf::Sprite wall;
    wall.setTexture(wall_tex);
    wall.setTextureRect(sf::IntRect(0, 0, 50, 250));
    wall.setPosition(25.0,100.0);

    sf::Sprite wall2;
    wall2.setTexture(wall_tex);
    wall2.setTextureRect(sf::IntRect(0, 0, 50, 300));
    wall2.setPosition(520.0,200.0);

    sf::Sprite wall3;
    wall3.setTexture(wall_tex);
    wall3.setTextureRect(sf::IntRect(0, 0, 150, 50));
    wall3.setPosition(250.0,75.0);

    sf::Sprite wall4;
    wall4.setTexture(wall_tex);
    wall4.setTextureRect(sf::IntRect(0, 0, 50, 350));
    wall4.setPosition(430.0,200.0);

    sf::Sprite wall5;
    wall5.setTexture(wall_tex);
    wall5.setTextureRect(sf::IntRect(0, 0, 200, 50));
    wall5.setPosition(650.0,400.0);

    walls.emplace_back(wall);
    walls.emplace_back(wall2);
    walls.emplace_back(wall3);
    walls.emplace_back(wall4);
    walls.emplace_back(wall5);


    std::vector<sf::Sprite> hearts;
    sf::Sprite heart1;
    heart1.setTexture(heart_tex);
    heart1.setScale(0.1,0.1);
    heart1.setPosition(750.0,0.0);

    sf::Sprite heart2;
    heart2.setTexture(heart_tex);
    heart2.setScale(0.1,0.1);
    heart2.setPosition(700.0,0.0);

    sf::Sprite heart3;
    heart3.setTexture(heart_tex);
    heart3.setScale(0.1,0.1);
    heart3.setPosition(650.0,0.0);



    hearts.emplace_back(heart1);
    hearts.emplace_back(heart2);
    hearts.emplace_back(heart3);

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        guy.setBounds(0, window.getSize().x, 0, window.getSize().y);
        guy.moveInDirection(elapsed, walls, hearts);

        if(hearts.size() == 0)
        {
            std::cerr << "Press Space to restart" << std::endl;
            window.clear(sf::Color::Black);
            window.draw(grass);
            window.draw(guy);

            for (auto &wall : walls)
                window.draw(wall);

            window.display();
            while(true)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    guy.setPosition(1.0,1.0);
                    hearts.emplace_back(heart1);
                    hearts.emplace_back(heart2);
                    hearts.emplace_back(heart3);

                    break;
                }

            }
        }

        window.clear(sf::Color::Black);
        window.draw(grass);
        window.draw(guy);

        for (auto &wall : walls){
            window.draw(wall);
        }

        for (auto &heart : hearts)
        {
            window.draw(heart);
        }

        window.display();
    }

    return 0;
}
