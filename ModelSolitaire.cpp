// ModelSolitaire.cpp
// This is model for solitaire game
#ifndef MODEL_CPP 
#define MODEL_CPP
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

#include <Deck.hpp>
#include <Card.hpp>
#include <ModelSolitaire.hpp>

Model::Model() {}
Model::~Model() {}

void Model::allDeckCardsToDrawPile() {
    if (!deck->isEmpty()) {
        while (!deck->isEmpty()) {
            deck->dealCard(drawPile);
        }
    }
}

void Model::allCardsReturnToDeck() {
    // use deck->returnCards(pile)
    for (int i = 1; i < 8; i++) {
        deck->returnCards(getMainPile(i));
    }
    for (int i = 1; i < 5; i++) {
        deck->returnCards(getFoundationPile(i));
    }
    deck->returnCards(wastePile);
    deck->returnCards(movePile);
    deck->returnCards(drawPile);
}

void Model::shuffleCards() {
    deck->shuffleDeck();
}

void Model::cardsToMove(std::shared_ptr<std::vector<std::shared_ptr<Card>>> from_pile, int index) {
    long unsigned int num = from_pile->size() - index;
    for (long unsigned int i = num; i > 0; i--) {
        movePile->push_back(from_pile->back());
        from_pile->pop_back();
    }
    
}

void Model::cardsFromMove(std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile) {
    while (!movePile->empty()) {
        to_pile->push_back(movePile->back());
        movePile->pop_back();
    }
    
}

int Model::dealCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile) {
    if (!drawPile->empty()) {
        to_pile->push_back(drawPile->back());
        to_pile->back()->setFaceUp(true);
        drawPile->pop_back();
        return 1;
    }
    return -1;
}

int Model::deal3Cards(std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile) {
    if (!drawPile->empty()) {
        if (drawPile->size() >= 3) {
            dealCard(to_pile);
            dealCard(to_pile);
            dealCard(to_pile);
            return 3;
        }
        else if (drawPile->size() == 2) {
            dealCard(to_pile);
            dealCard(to_pile);
            return 2;
        }
        else if (drawPile->size() == 1) {
            dealCard(to_pile);
            return 1;
        }
    }
    return -1;

}

void Model::dealTableau() {
    int num = 1;
    for (int i = 1; i < 8; i++) {
        for (int j = num; j < 8; j++) {
            dealCard(getMainPile(j));
            //turn face down
            getMainPile(j)->back()->setFaceUp(false);
        }
        num++;
    }

    // reveal bottom card
    for (int i = 1; i < 8; i++) {
        revealCard(getMainPile(i));
    }
}

void Model::revealCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    if (!pile->empty()) {
        pile->back()->setFaceUp(true);
    }
}

std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getMainPile(int pile_num) {
    switch(pile_num) {
        case 1 :
            return mainPile1;
        case 2 :
            return mainPile2;
        case 3 :
            return mainPile3;
        case 4 :
            return mainPile4;
        case 5 :
            return mainPile5;
        case 6 :
            return mainPile6;
        case 7 :
            return mainPile7;
        default :
            return nullptr;
    }
}

std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getFoundationPile(int pile_num) {
    switch(pile_num) {
        case 1 :
            return foundationPile1;
        case 2 :
            return foundationPile2;
        case 3 :
            return foundationPile3;
        case 4 :
            return foundationPile4;
        default :
            return nullptr;
    }
}

std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getWastePile() {
    return wastePile;
}

std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getMovePile() {
    return movePile;
}

std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getDrawPile() {
    return drawPile;
}

std::shared_ptr<Deck> Model::getDeck() {
    return deck;
}

#endif