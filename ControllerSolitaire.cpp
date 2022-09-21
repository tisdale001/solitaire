// ControllerSolitaire.cpp
// this is the controller for solitaire game
#ifndef CONTROLLER_CPP 
#define CONTROLLER_CPP 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <vector>
#include <string>
//#include <Vector2.hpp>

#include <Card.hpp>
#include <Deck.hpp>
#include <ViewSolitaire.hpp>
#include <ModelSolitaire.hpp>
#include <ControllerSolitaire.hpp>

Controller::Controller() {}

Controller::~Controller() {}

void Controller::playGame() {
    view.initiateView(model.getMainPile(1), model.getMainPile(2), model.getMainPile(3),
    model.getMainPile(4), model.getMainPile(5), model.getMainPile(6), model.getMainPile(7),
    model.getFoundationPile(1), model.getFoundationPile(2), model.getFoundationPile(3),
    model.getFoundationPile(4), model.getWastePile(), model.getMovePile(), 
    model.getDrawPile(), model.getDeck());
    
    // setup random number
    srand((unsigned) time(0));

    // deal hand
    model.allDeckCardsToDrawPile();
    model.dealTableau();
    
    sf::RenderWindow window(sf::VideoMode(view.getBoundsWidth(), view.getBoundsHeight()), 
    "Solitaire", sf::Style::Close);

    while (window.isOpen()) {
		
		sf::Event event;

		while (window.pollEvent(event)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                    std::pair<std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int> click = view.getClick(mousePos);
                    if (click.first != nullptr) {
                        if (click.first == model.getDrawPile()) {
                            if (!model.getDrawPile()->empty()) {
                                if (threeCardVersion) {
                                    // deal 3 cards
                                    numWasteCards = model.deal3Cards(model.getWastePile());
                                }
                                else {
                                    // deal card
                                    model.dealCard(model.getWastePile());
                                }
                                if (automaticVersion) {
                                    view.draw(&window, numWasteCards);
                                    automaticUpdate(&window);
                                    if (checkWin()) {
                                        std::cout << "WINNER!\n";
                                        int num = rand() % 2;
                                        if (num == 0) {
                                            view.animateWin(&window);
                                        }
                                        else if (num == 1) {
                                            view.animateWin2(&window);
                                        }
                                    }
                                }
                            }
                            else {
                                // put cards back in drawPile
                                while (!model.getWastePile()->empty()) {
                                    model.getWastePile()->back()->setFaceUp(false);
                                    model.getDrawPile()->push_back(model.getWastePile()->back());
                                    model.getWastePile()->pop_back();
                                }
                            }
                        }
                        else if (!click.first->empty()) {
                            if (click.first == model.getWastePile()) {
                                // reduce the amount of waste cards to show in 3 card version
                                if (numWasteCards > 1 && threeCardVersion == true) {
                                    numWasteCards--;
                                }
                            }
                            if (click.first->at(click.second)->getFaceUp()) {
                                if (checkMove(click.first, click.second)) {
                                    model.cardsToMove(click.first, click.second);
                                   if (numWasteCards > 1 && threeCardVersion == true) {
                                    numWasteCards--;
                                } // set movePile positions?
                                    lastPile = click.first;
                                }
                            }
                        }
                    }
                }
            }
            if(event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    //std::cout << "Mouse button released\n";
                    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                    std::pair<std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int> click = view.getRelease(mousePos);
                    if (click.first != nullptr) {
                        if (checkDrop(click.first)) {
                            model.cardsFromMove(click.first);
                            if (!lastPile->empty()) {
                                model.revealCard(lastPile);
                            }
                            if (automaticVersion) {
                                view.draw(&window, numWasteCards);
                                automaticUpdate(&window);
                            }
                            if (checkWin()) {
                                std::cout << "WINNER!\n";
                                int num = rand() % 2;
                                if (num == 0) {
                                    view.animateWin(&window);
                                }
                                else if (num == 1) {
                                    view.animateWin2(&window);
                                }
                            }
                        }
                        else {
                            if (!model.getMovePile()->empty()) {
                                model.cardsFromMove(lastPile);
                                if (lastPile == model.getWastePile() && threeCardVersion == true) {
                                    numWasteCards++;
                                }
                            }
                            
                        }
                    }
                    else {
                        if (!model.getMovePile()->empty()) {
                            model.cardsFromMove(lastPile);
                            if (lastPile == model.getWastePile() && threeCardVersion == true) {
                                numWasteCards++;
                            }
                        }
                    }
                }
                once = 1;
            }
			
			if (event.type == sf::Event::Closed) {
				window.close();
                break;
				
			}
			
			if (event.type == sf::Event::KeyReleased) {
				
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
					break;
				}
                else if (event.key.code == sf::Keyboard::D) {
                    model.allCardsReturnToDeck();
                    model.shuffleCards();
                    model.allDeckCardsToDrawPile();
                    model.dealTableau();
                }
                else if (event.key.code == sf::Keyboard::V) {
                    if (threeCardVersion == true) {
                        threeCardVersion = false;
                        std::cout << "Toggle 3 card version: OFF\n";
                    }
                    else {
                        threeCardVersion = true;
                        std::cout << "Toggle 3 card version: ON\n";
                    }
                    numWasteCards = 1;
                }
                else if (event.key.code == sf::Keyboard::A) {
                    if (automaticVersion == true) {
                        automaticVersion = false;
                        std::cout << "Toggle automatic version: OFF\n";
                    }
                    else {
                        automaticVersion = true;
                        std::cout << "Toggle automatic version: ON\n";
                    }
                }
                else if (event.key.code == sf::Keyboard::M) {
                    int num = rand() % 2;
                    if (num == 0) {
                        view.animateWin(&window);
                    }
                    else if (num == 1) {
                        view.animateWin2(&window);
                    }
                }
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // drag move pile
            if (!model.getMovePile()->empty()) {
                sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                sf::Vector2f cardPos = model.getMovePile()->back()->getPSprite()->getPosition();
			    if(pressedLastFrame || (mousePos.x > xPos && mousePos.y > yPos
        	    && mousePos.x - view.getBoundsWidth() < xPos && mousePos.y - 
                view.getBoundsHeight() < yPos))
    		    {
        		    if(once)
        		    {
            		    xDiff = mousePos.x - cardPos.x;
            		    yDiff = mousePos.y - cardPos.y;
            	    	once = 0;
        		    }
        		    xPos = mousePos.x - xDiff;
        		    yPos = mousePos.y - yDiff;
				    for (int i = (int)model.getMovePile()->size() - 1; i >= 0; i--) {
					    model.getMovePile()->at(i)->getPSprite()->setPosition(xPos, yPos + 
                        view.getStackDistance() * (model.getMovePile()->size() - 1 - i));
				    }
    		    }
    		    pressedLastFrame = true;
		    }
		    
        }
        
        // draw all cards
        view.draw(&window, numWasteCards);
    }
    model.allCardsReturnToDeck();
    
}
bool Controller::checkMove(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile, int index) {
    if (index == (int)pile->size() - 1) {
        return true;
    }
    for (int i = index + 1; i < (int)pile->size(); i++) {
        if (i % 2 == index % 2) {
            // same color than at index
            if (pile->at(i)->getColor() != pile->at(index)->getColor()) {
                return false;
            }
            if (pile->at(i)->getValue() != pile->at(index)->getValue() + (index - i)) {
                return false;
            }
        }
        else {
            // different color than at index
            if (pile->at(i)->getColor() == pile->at(index)->getColor()) {
                return false;
            }
            if (pile->at(i)->getValue() != pile->at(index)->getValue() + (index - i)) {
                return false;
            }
        }
    }
    return true;
}
bool Controller::checkDrop(std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile) {
    if (model.getMovePile()->empty()) {
        return false;
    }
    if (to_pile == model.getFoundationPile(1) || to_pile == model.getFoundationPile(2) || to_pile == model.getFoundationPile(3)
    || to_pile == model.getFoundationPile(4)) {
        if (model.getMovePile()->size() != 1) {
            return false;
        }
        if (!to_pile->empty()) {
            if (model.getMovePile()->back()->getSuit() != to_pile->back()->getSuit()) {
                return false;
            }
            if (model.getMovePile()->back()->getValue() != to_pile->back()->getValue() + 1) {
                return false;
            }
        }
        else {
            // Foundation pile is empty
            if (model.getMovePile()->back()->getSymbol() != "A") {
                return false;
            }
        }
    }
    else if (to_pile == model.getWastePile() || to_pile == model.getDrawPile()) {
        return false;
    }
    else if (to_pile == nullptr) {
        return false;
    }
    else {
        // check main piles
        if (!to_pile->empty()) {
            if (model.getMovePile()->back()->getColor() == to_pile->back()->getColor()) {
                return false;
            }
            if (model.getMovePile()->back()->getValue() != to_pile->back()->getValue() - 1) {
                return false;
            }
        }
        else {
            // main pile is empty
            if (model.getMovePile()->back()->getSymbol() != "K") {
                return false;
            }
        }
    }
    return true;
}
bool Controller::checkWin() {
    if (model.getFoundationPile(1)->empty()) {
        return false;
    }
    if (model.getFoundationPile(2)->empty()) {
        return false;
    }
    if (model.getFoundationPile(3)->empty()) {
        return false;
    }
    if (model.getFoundationPile(4)->empty()) {
        return false;
    }
    if (model.getFoundationPile(1)->size() != 13) {
        return false;
    }
    if (model.getFoundationPile(2)->size() != 13) {
        return false;
    }
    if (model.getFoundationPile(3)->size() != 13) {
        return false;
    }
    if (model.getFoundationPile(4)->size() != 13) {
        return false;
    }
    return true;
}

void Controller::automaticUpdate(sf::RenderWindow* window) {
    // automatically moves cards into foundation piles
    int count = 1;
    while (count != 0) {
        count = 0;
        if (!model.getWastePile()->empty()) {
            // check if ace
            if (model.getWastePile()->back()->getSymbol() == "A") {
                model.cardsToMove(model.getWastePile(), (int)model.getWastePile()->size() - 1);
                for (int i = 1; i < 5; i++) {
                    if (model.getFoundationPile(i)->empty() && !model.getMovePile()->empty()) {
                        if (numWasteCards > 1 && threeCardVersion == true) {
                            numWasteCards--;
                        }
                        view.animateCard(window, model.getFoundationPile(i), numWasteCards);
                        model.cardsFromMove(model.getFoundationPile(i));
                        view.draw(window, numWasteCards);
                        count++;
                    }
                }
            }
            else {
                // not an ace
                for (int i = 1; i < 5; i++) {
                    if (!model.getFoundationPile(i)->empty() && !model.getWastePile()->empty()) {
                        if (model.getFoundationPile(i)->back()->getSuit() == model.getWastePile()->back()->getSuit() &&
                        model.getFoundationPile(i)->back()->getValue() + 1 == model.getWastePile()->back()->getValue()) {
                            model.cardsToMove(model.getWastePile(), (int)model.getWastePile()->size() - 1);
                            if (numWasteCards > 1 && threeCardVersion == true) {
                                numWasteCards--;
                            }
                            view.animateCard(window, model.getFoundationPile(i), numWasteCards);
                            model.cardsFromMove(model.getFoundationPile(i));
                            view.draw(window, numWasteCards);
                            count++;
                        }
                    }
                }
            }
        }
        // main piles
        for (int i = 1; i < 8; i++) {
            if (!model.getMainPile(i)->empty()) {
                // check if ace
                if (model.getMainPile(i)->back()->getSymbol() == "A") {
                    model.cardsToMove(model.getMainPile(i), (int)model.getMainPile(i)->size() - 1);
                    for (int j = 1; j < 5; j++) {
                        if (model.getFoundationPile(j)->empty() && !model.getMovePile()->empty()) {
                            view.animateCard(window, model.getFoundationPile(j), numWasteCards);
                            model.cardsFromMove(model.getFoundationPile(j));
                            model.revealCard(model.getMainPile(i));
                            view.draw(window, numWasteCards);
                            count++;
                        }
                    }
                }
                // not an ace
                else {
                    for (int j = 1; j < 5; j++) {
                        if (!model.getFoundationPile(j)->empty() && !model.getMainPile(i)->empty()) {
                            if (model.getFoundationPile(j)->back()->getSuit() == model.getMainPile(i)->back()->getSuit() &&
                            model.getFoundationPile(j)->back()->getValue() + 1 == model.getMainPile(i)->back()->getValue()) {
                                model.cardsToMove(model.getMainPile(i), (int)model.getMainPile(i)->size() - 1);
                                view.animateCard(window, model.getFoundationPile(j), numWasteCards);
                                model.cardsFromMove(model.getFoundationPile(j));
                                model.revealCard(model.getMainPile(i));
                                view.draw(window, numWasteCards);
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }
}


#endif