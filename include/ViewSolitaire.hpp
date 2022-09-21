// ViewSolitaire.hpp
// this is header file for View for Solitaire game
#ifndef VIEW_HPP 
#define VIEW_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <utility>
#include <memory>
#include <cstdlib>
#include <ctime>

#include <Card.hpp>
#include <Deck.hpp>
#include <AnimationWrapper.hpp>

class View {
    private:
    int bounds_width = 1100;
	int bounds_height = 1000;
	bool pressedLastFrame = false;
	int once = 0;
	int xPos = 0;
	int yPos = 0;
	int xDiff = 0;
	int yDiff = 0;
	int stackDistance = 30;
    int distBtwPiles = 50;
    int cardHeight = 0; // set cardHeight with sprite.getSize()
    int cardWidth = 0; // set cardWidth with sprite.getSize()
    int startPointX = 100;
    int startPointY = 100;
    //sf::RenderWindow window;
    sf::Image image; // initiate
    sf::Texture texture; // initiate
    sf::Sprite sprite; // initiate
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile1; // initiate all below
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile2;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile3;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile4;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile5;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile6;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile7;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile1;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile2;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile3;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile4;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> wastePile;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> movePile;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile;
    std::shared_ptr<Deck> deck;

    public:
    View();
    ~View();
    void initiateView(std::shared_ptr<std::vector<std::shared_ptr<Card>>>, std::shared_ptr<std::vector<std::shared_ptr<Card>>>, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>>, std::shared_ptr<std::vector<std::shared_ptr<Card>>>, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>>,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>>, std::shared_ptr<std::vector<std::shared_ptr<Card>>>, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>>, std::shared_ptr<std::vector<std::shared_ptr<Card>>>, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>>,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>>, std::shared_ptr<std::vector<std::shared_ptr<Card>>>, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>>, std::shared_ptr<std::vector<std::shared_ptr<Card>>>, 
    std::shared_ptr<Deck>);

    std::pair<std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int> getClick(sf::Vector2f);
    std::pair<std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int> getRelease(sf::Vector2f);
    void setPosition(int);
    void draw(sf::RenderWindow*, int);
    void animateCard(sf::RenderWindow*, std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int);
    void animateWin(sf::RenderWindow* window);
    void animateWin2(sf::RenderWindow* window);


    int getBoundsWidth();
    int getBoundsHeight();
    int getStackDistance();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getMainPile(int);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getFoundationPile(int);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getWastePile();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getMovePile();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getDrawPile();
    std::shared_ptr<Deck> getDeck();


};

#endif