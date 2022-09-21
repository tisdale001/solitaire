// test program for solitaire
//g++ -std=c++17 Card.cpp Deck.cpp test_solitaire.cpp -I./include/ -o test -lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Card.hpp>
#include <Deck.hpp>

#include <iostream>
#include <vector>

int main() {
	Deck deck;
	int bounds_width = 1300;
	int bounds_height = 1000;
	bool pressedLastFrame = false;
	int once = 0;
	int xPos = 0;
	int yPos = 0;
	int xDiff = 0;
	int yDiff = 0;
	int stack_distance = 30;
	//sf::Vector2f& mousePos;
	//sf::Vector2f& acePos;
    sf::RenderWindow window(sf::VideoMode(bounds_width, bounds_height), "Solitaire", sf::Style::Close);
	
	//window.setVerticalSyncEnabled(true);

	sf::Image image;
	image.create(bounds_width, bounds_height, sf::Color::White);

	sf::Texture texture;
	texture.loadFromImage(image);

	sf::Sprite sprite;
	sprite.setTexture(texture);

    /* sf::Image image2;
    image2.loadFromFile("../aceOfClubs.png");

    sf::Texture texture2;
    texture2.loadFromImage(image2);

    sf::Sprite aceOfClubs;
    aceOfClubs.setTexture(texture2); */

	
	std::vector<Card*> pile;
	std::vector<Card*>* p_pile = &pile;
	for (int i = 0; i < 19; i++) {
		deck.dealCard(p_pile);
	}
	
	std::vector<sf::Sprite*> pointers_vec;
	for (int i = 0; i < pile.size(); i++) {
		sf::Sprite* p_sprite = pile[i]->getPSprite();
		pointers_vec.push_back(p_sprite);
	}

	/* sf::Sprite* s_pointer = &aceOfClubs;
	pointers_vec.push_back(s_pointer); */

	//std::cout << pointers_vec[0] << std::endl;
	//pointers_vec[0]->setPosition(200, 200);
	//for (int i = 1; i < 5; i++) {
	//	sf::Sprite card_sprite;
	//	card_sprite.setTexture(texture2);
	//	sf::Sprite* s_pointer = &card_sprite;
	//	pointers_vec.push_back(s_pointer);
	//}

	/* sf::Sprite sprite3;
	sprite3.setTexture(texture2);
	sf::Sprite* s_pointer2 = &sprite3;
	pointers_vec.push_back(s_pointer2); */

	for (int i = 0; i < pointers_vec.size(); i++) {
		pointers_vec[i]->setPosition(200, 200 + stack_distance * i);
	}
	/* for (int i = 0; i < pointers_vec.size(); i++) {
		std::cout << pointers_vec[i] << std::endl;
	} */



    while (window.isOpen()) {
			
		sf::Event event;

		
		while (window.pollEvent(event)) {
			
			if (event.type == sf::Event::Closed) {
				window.close();
				exit(EXIT_SUCCESS);
			}

			
			if (event.type == sf::Event::KeyReleased) {
				// std::cout << "Key Pressed" << std::endl;
				
				if (event.key.code == sf::Keyboard::Escape) {
					//std::cout << "escape Pressed" << std::endl;
					window.close();
					exit(EXIT_SUCCESS);
				}
            }
        }
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f acePos = pointers_vec[0]->getPosition();
			if(pressedLastFrame ||
        	(mousePos.x > xPos && mousePos.y > yPos
        	&& mousePos.x - bounds_width < xPos && mousePos.y - bounds_height < yPos))
    		{
        		if(once)
        		{
            		xDiff = mousePos.x - acePos.x;
            		yDiff = mousePos.y - acePos.y;
            		once = 0;
        		}
        		xPos = mousePos.x - xDiff;
        		yPos = mousePos.y - yDiff;
        		//aceOfClubs.setPosition(xPos, yPos);
				for (int i = 0; i < pointers_vec.size(); i++) {
					pointers_vec[i]->setPosition(xPos, yPos + stack_distance * i);
				}
    		}
    		pressedLastFrame = true;
		}
		else
		{
    		once = 1;
    		//aceOfClubs.setPosition(xPos, yPos);
    		pressedLastFrame = false;
		}
		

        window.clear();
			 
		window.draw(sprite);
		//std::cout << "Position 1\n";
        //window.draw(aceOfClubs);
		for (int i = 0; i < pointers_vec.size(); i++) {
			window.draw(*pointers_vec[i]);
		}
		//std::cout << "Position 2\n";
		window.display();
    }   

	deck.destroy(); 

    
}