// ControllerSolitaire.hpp
// this is header file for controller in solitaire game
#ifndef CONTROLLER_HPP 
#define CONTROLLER_HPP 

#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

#include <ViewSolitaire.hpp>
#include <ModelSolitaire.hpp>

class Controller {
    private:
    Model model = Model();
    View view = View();
    bool pressedLastFrame = true;
	int once = 1;
	int xPos = 0;
	int yPos = 0;
	int xDiff = 0;
	int yDiff = 0;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> lastPile = nullptr;
    bool threeCardVersion = false;
    int numWasteCards = 1;
    bool automaticVersion = true;

    public:
    Controller();
    ~Controller();
    void playGame();
    bool checkMove(std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int);
    bool checkDrop(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    bool checkWin();
    void automaticUpdate(sf::RenderWindow*);
};

#endif