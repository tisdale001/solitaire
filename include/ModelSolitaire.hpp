// ModelSolitaire.hpp
// This is the model for a solitaire game
#ifndef MODEL_HPP 
#define MODEL_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

#include <Deck.hpp>
#include <Card.hpp>

class Model {
    private:
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile1 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile2 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile3 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile4 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile5 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile6 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile7 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile1 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile2 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile3 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile4 = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> wastePile = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> movePile = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    std::shared_ptr<Deck> deck = std::make_shared<Deck>();

    public:
    Model();
    ~Model();
    void allDeckCardsToDrawPile();
    void allCardsReturnToDeck();
    void shuffleCards();
    void cardsToMove(std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int);
    void cardsFromMove(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    int dealCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    int deal3Cards(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    void dealTableau();
    void revealCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getMainPile(int);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getFoundationPile(int);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getWastePile();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getMovePile();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getDrawPile();
    std::shared_ptr<Deck> getDeck();

};

#endif