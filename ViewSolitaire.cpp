// ViewSolitaire.cpp
// this is the view for solitaire game
#ifndef VIEW_CPP 
#define VIEW_CPP
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <utility>
//#include <Vector2.hpp>

#include <Card.hpp>
#include <Deck.hpp>
#include <ViewSolitaire.hpp>

View::View() {}
View::~View() {}

void View::initiateView(std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile1_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile2_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile3_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile4_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile5_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile6_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> mainPile7_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile1_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile2_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile3_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> foundationPile4_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> wastePile_,
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> movePile_, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile_, std::shared_ptr<Deck> deck_) {
    mainPile1 = mainPile1_;
    mainPile2 = mainPile2_;
    mainPile3 = mainPile3_;
    mainPile4 = mainPile4_;
    mainPile5 = mainPile5_;
    mainPile6 = mainPile6_;
    mainPile7 = mainPile7_;
    foundationPile1 = foundationPile1_;
    foundationPile2 = foundationPile2_;
    foundationPile3 = foundationPile3_;
    foundationPile4 = foundationPile4_;
    wastePile = wastePile_;
    movePile = movePile_;
    drawPile = drawPile_;
    deck = deck_;
    cardHeight = deck->getTopSprite()->getGlobalBounds().height;
    cardWidth = deck->getTopSprite()->getGlobalBounds().width;
    image.create(bounds_width, bounds_height, sf::Color::Black);
    texture.loadFromImage(image);
    sprite.setTexture(texture);

}
std::pair<std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int> View::getClick(sf::Vector2f mousePos) {
    // check if clicked on sprites
    if (!mainPile1->empty()) {
        for (int i = (int)mainPile1->size() - 1; i >= 0; i--) {
            if (mainPile1->at(i)->getPSprite()->getGlobalBounds().contains(mousePos)) {
                return std::make_pair(mainPile1, i);
            }
        }
    }
    if (!mainPile2->empty()) {
        for (int i = (int)mainPile2->size() - 1; i >= 0; i--) {
            if (mainPile2->at(i)->getPSprite()->getGlobalBounds().contains(mousePos)) {
                return std::make_pair(mainPile2, i);
            }
        }
    }
    if (!mainPile3->empty()) {
        for (int i = (int)mainPile3->size() - 1; i >= 0; i--) {
            if (mainPile3->at(i)->getPSprite()->getGlobalBounds().contains(mousePos)) {
                return std::make_pair(mainPile3, i);
            }
        }
    }
    if (!mainPile4->empty()) {
        for (int i = (int)mainPile4->size() - 1; i >= 0; i--) {
            if (mainPile4->at(i)->getPSprite()->getGlobalBounds().contains(mousePos)) {
                return std::make_pair(mainPile4, i);
            }
        }
    }
    if (!mainPile5->empty()) {
        for (int i = (int)mainPile5->size() - 1; i >= 0; i--) {
            if (mainPile5->at(i)->getPSprite()->getGlobalBounds().contains(mousePos)) {
                return std::make_pair(mainPile5, i);
            }
        }
    }
    if (!mainPile6->empty()) {
        for (int i = (int)mainPile6->size() - 1; i >= 0; i--) {
            if (mainPile6->at(i)->getPSprite()->getGlobalBounds().contains(mousePos)) {
                return std::make_pair(mainPile6, i);
            }
        }
    }
    if (!mainPile7->empty()) {
        for (int i = (int)mainPile7->size() - 1; i >= 0; i--) {
            if (mainPile7->at(i)->getPSprite()->getGlobalBounds().contains(mousePos)) {
                return std::make_pair(mainPile7, i);
            }
        }
    }
    if (!foundationPile1->empty()) {
        if (foundationPile1->back()->getPSprite()->getGlobalBounds().contains(mousePos)) {
            return std::make_pair(foundationPile1, (int)foundationPile1->size() - 1);
        }
    }
    if (!foundationPile2->empty()) {
        if (foundationPile2->back()->getPSprite()->getGlobalBounds().contains(mousePos)) {
            return std::make_pair(foundationPile2, (int)foundationPile2->size() - 1);
        }
    }
    if (!foundationPile3->empty()) {
        if (foundationPile3->back()->getPSprite()->getGlobalBounds().contains(mousePos)) {
            return std::make_pair(foundationPile3, (int)foundationPile3->size() - 1);
        }
    }
    if (!foundationPile4->empty()) {
        if (foundationPile4->back()->getPSprite()->getGlobalBounds().contains(mousePos)) {
            return std::make_pair(foundationPile4, (int)foundationPile4->size() - 1);
        }
    }
    if (!wastePile->empty()) {
        if (wastePile->back()->getPSprite()->getGlobalBounds().contains(mousePos)) {
            return std::make_pair(wastePile, (int)wastePile->size() - 1);
        }
    }
    if (!drawPile->empty()) {
        if (drawPile->back()->getPSprite()->getGlobalBounds().contains(mousePos)) {
            return std::make_pair(drawPile, (int)drawPile->size() - 1);
        }
    }

    // check if clicked in empty slots
    float x = mousePos.x;
    float y = mousePos.y;
    for (int i = 0; i < 7; i++) {
        if (x > startPointX + cardWidth * i + distBtwPiles * i && x < startPointX + cardWidth + cardWidth * i + 
        distBtwPiles * i && y > startPointY + cardHeight + distBtwPiles && y < startPointY + cardHeight + cardHeight
        + distBtwPiles) {
            return std::make_pair(getMainPile(i + 1), 0);
        }
    }
    for (int i = 0; i < 4; i++) {
        if (x > startPointX + cardWidth * 3 + cardWidth * i + distBtwPiles * 3 + distBtwPiles * i && x < startPointX
        + cardWidth * 4 + cardWidth * i + distBtwPiles * 3 + distBtwPiles * i && y > startPointY && y <
        startPointY + cardHeight) {
            return std::make_pair(getFoundationPile(i + 1), 0);
        }
    }

    if (x > startPointX - distBtwPiles / 2 && x < startPointX + cardWidth + distBtwPiles / 2 
    && y > startPointY - distBtwPiles / 2 && y < startPointY + cardHeight + distBtwPiles / 2) {
        return std::make_pair(getDrawPile(), 0);
    }

    return std::make_pair(nullptr, 0);
}

std::pair<std::shared_ptr<std::vector<std::shared_ptr<Card>>>, int> View::getRelease(sf::Vector2f mousePos) {
    float x = mousePos.x;
    float y = mousePos.y;
    for (int i = 0; i < 7; i++) {
        if (!getMainPile(i + 1)->empty()) {
            if (x > startPointX - distBtwPiles / 2 + cardWidth * i + distBtwPiles * i && x < startPointX + distBtwPiles / 2 
            + cardWidth + cardWidth * i + distBtwPiles * i && y > startPointY - distBtwPiles / 2 + cardHeight + distBtwPiles 
            && y < startPointY + distBtwPiles / 2 + getMainPile(i + 1)->size() * stackDistance
            + cardHeight + cardHeight + distBtwPiles) {
                return std::make_pair(getMainPile(i + 1), 0);
            }
        }
        else {
            if (x > startPointX - distBtwPiles / 2 + cardWidth * i + distBtwPiles * i && x < startPointX + distBtwPiles / 2 + cardWidth 
            + cardWidth * i + distBtwPiles * i && y > startPointY - distBtwPiles / 2 + cardHeight + distBtwPiles && 
            y < startPointY + distBtwPiles / 2 + cardHeight + cardHeight + distBtwPiles) {
                return std::make_pair(getMainPile(i + 1), 0);
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        if (x > startPointX - distBtwPiles / 2 + cardWidth * 3 + cardWidth * i + distBtwPiles * 3 + distBtwPiles * i 
        && x < startPointX + distBtwPiles / 2 + cardWidth * 4 + cardWidth * i + distBtwPiles * 3 + distBtwPiles * i 
        && y > startPointY - distBtwPiles / 2 && y < startPointY + distBtwPiles / 2 + cardHeight) {
            return std::make_pair(getFoundationPile(i + 1), 0);
        }
    }
    return std::make_pair(nullptr, 0);
}

void View::setPosition(int numWasteCards) {
    // set positions of all sprites (except movePile)
    if (!mainPile1->empty()) {
        for (long unsigned int i = 0; i < mainPile1->size(); i++) {
            mainPile1->at(i)->getPSprite()->setPosition(startPointX, startPointY + cardHeight + distBtwPiles 
            + stackDistance * i);
        }
    }
    if (!mainPile2->empty()) {
        for (long unsigned int i = 0; i < mainPile2->size(); i++) {
            mainPile2->at(i)->getPSprite()->setPosition(startPointX + cardWidth + distBtwPiles, startPointY 
            + cardHeight + distBtwPiles + stackDistance * i);
        }
    }
    if (!mainPile3->empty()) {
        for (long unsigned int i = 0; i < mainPile3->size(); i++) {
            mainPile3->at(i)->getPSprite()->setPosition(startPointX + cardWidth * 2 + distBtwPiles * 2, 
            startPointY + cardHeight + distBtwPiles + stackDistance * i);
        }
    }
    if (!mainPile4->empty()) {
        for (long unsigned int i = 0; i < mainPile4->size(); i++) {
            mainPile4->at(i)->getPSprite()->setPosition(startPointX + cardWidth * 3 + distBtwPiles * 3, 
            startPointY + cardHeight + distBtwPiles + stackDistance * i);
        }
    }
    if (!mainPile5->empty()) {
        for (long unsigned int i = 0; i < mainPile5->size(); i++) {
            mainPile5->at(i)->getPSprite()->setPosition(startPointX + cardWidth * 4 + distBtwPiles * 4, 
            startPointY + cardHeight + distBtwPiles + stackDistance * i);
        }
    }
    if (!mainPile6->empty()) {
        for (long unsigned int i = 0; i < mainPile6->size(); i++) {
            mainPile6->at(i)->getPSprite()->setPosition(startPointX + cardWidth * 5 + distBtwPiles * 5, 
            startPointY + cardHeight + distBtwPiles + stackDistance * i);
        }
    }
    if (!mainPile7->empty()) {
        for (long unsigned int i = 0; i < mainPile7->size(); i++) {
            mainPile7->at(i)->getPSprite()->setPosition(startPointX + cardWidth * 6 + distBtwPiles * 6, 
            startPointY + cardHeight + distBtwPiles + stackDistance * i);
        }
    }
    if (!foundationPile1->empty()) {
        
        foundationPile1->back()->getPSprite()->setPosition(startPointX + cardWidth * 3 + distBtwPiles * 3,
            startPointY);
        
    }
    if (!foundationPile2->empty()) {
        
        foundationPile2->back()->getPSprite()->setPosition(startPointX + cardWidth * 4 + distBtwPiles * 4,
            startPointY);
        
    }
    if (!foundationPile3->empty()) {
        
        foundationPile3->back()->getPSprite()->setPosition(startPointX + cardWidth * 5 + distBtwPiles * 5,
            startPointY);
        
    }
    if (!foundationPile4->empty()) {
        
        foundationPile4->back()->getPSprite()->setPosition(startPointX + cardWidth * 6 + distBtwPiles * 6,
            startPointY);
        
    }
    if (!wastePile->empty()) {
        int j = 0;
        for (int i = (int)wastePile->size() - numWasteCards; i < (int)wastePile->size(); i++) {
            wastePile->at(i)->getPSprite()->setPosition(startPointX + cardWidth + distBtwPiles + stackDistance * 
            j, startPointY);
            j++;
        }
        
    }
    if (!drawPile->empty()) {
        drawPile->back()->getPSprite()->setPosition(startPointX, startPointY);
    }
}
void View::draw(sf::RenderWindow* window, int numWasteCards) {
    // draw all sprites
    window->clear();
	// set all sprite positions
    setPosition(numWasteCards);

    if (!mainPile1->empty()) {
        for (long unsigned int i = 0; i < mainPile1->size(); i++) {
            window->draw(*(mainPile1->at(i)->getPSprite()));
        }
    }
    if (!mainPile2->empty()) {
        for (long unsigned int i = 0; i < mainPile2->size(); i++) {
            window->draw(*(mainPile2->at(i)->getPSprite()));
        }
    }
    if (!mainPile3->empty()) {
        for (long unsigned int i = 0; i < mainPile3->size(); i++) {
            window->draw(*(mainPile3->at(i)->getPSprite()));
        }
    }
    if (!mainPile4->empty()) {
        for (long unsigned int i = 0; i < mainPile4->size(); i++) {
            window->draw(*(mainPile4->at(i)->getPSprite()));
        }
    }
    if (!mainPile5->empty()) {
        for (long unsigned int i = 0; i < mainPile5->size(); i++) {
            window->draw(*(mainPile5->at(i)->getPSprite()));
        }
    }
    if (!mainPile6->empty()) {
        for (long unsigned int i = 0; i < mainPile6->size(); i++) {
            window->draw(*(mainPile6->at(i)->getPSprite()));
        }
    }
    if (!mainPile7->empty()) {
        for (long unsigned int i = 0; i < mainPile7->size(); i++) {
            window->draw(*(mainPile7->at(i)->getPSprite()));
        }
    }
    if (!foundationPile1->empty()) {
        window->draw(*(foundationPile1->back()->getPSprite()));
    }
    if (!foundationPile2->empty()) {
        window->draw(*(foundationPile2->back()->getPSprite()));
    }
    if (!foundationPile3->empty()) {
        window->draw(*(foundationPile3->back()->getPSprite()));
    }
    if (!foundationPile4->empty()) {
        window->draw(*(foundationPile4->back()->getPSprite()));
    }
    if (!wastePile->empty()) {
        for (int i = (int)wastePile->size() - numWasteCards; i < (int)wastePile->size(); i++) {
            window->draw(*(wastePile->at(i)->getPSprite()));
        }
    }
    if (!drawPile->empty()) {
        window->draw(*(drawPile->back()->getPSprite()));
    }
    if (!movePile->empty()) {
        for (int i = (int)movePile->size() - 1; i >= 0; i--) {
            window->draw(*(movePile->at(i)->getPSprite()));
        }
    }

    window->display();
}

void View::animateCard(sf::RenderWindow* window, std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile, int numWasteCards) {
    // animate card from move pile to target
    if (movePile->empty()) {
        return;
    }
    int num_frames = 50;
    sf::Vector2f beg_pos = movePile->back()->getPSprite()->getPosition();
    std::shared_ptr<sf::Sprite> card_sprite = movePile->back()->getPSprite();
    float x1 = beg_pos.x;
    float y1 = beg_pos.y;
    float x2 = startPointX;
    float y2 = startPointY;
    // get end position: x2, y2
    for (int i = 1; i < 5; i++) {
        if (to_pile == getFoundationPile(i)) {
            x2 = startPointX + cardWidth * 3 + cardWidth * (i - 1) + distBtwPiles * 3 + distBtwPiles * (i - 1);
            y2 = startPointY;
        }
    }
    float x_to_move = (x2 - x1) / num_frames;
    float y_to_move = (y2 - y1) / num_frames;
    // animate card
    for (int i = 0; i < num_frames; i++) {
        x1 += x_to_move;
        y1 += y_to_move;
        card_sprite->setPosition(x1, y1);
        draw(window, numWasteCards);
    }
}

// creates animation after a win
void View::animateWin(sf::RenderWindow* window) {
    srand((unsigned) time(0));
    Deck deck1 = Deck();
    Deck deck2 = Deck();
    Deck deck3 = Deck();
    Deck deck4 = Deck();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> card_vec = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    while (!deck1.isEmpty()) {
        deck1.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck2.isEmpty()) {
        deck2.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck3.isEmpty()) {
        deck3.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck4.isEmpty()) {
        deck4.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    // continue while loop till key is pressed or mouse clicked
    bool animation = true;
    while (animation) {
        sf::Event event;
        while (window->pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
				//window->close();
                animation = false;
                break;
			}
            else if (event.type == sf::Event::KeyReleased) {
                animation = false;
                break;
            }
        }
        if (animation == false) {
            break;
        }
        // code card burst here
        // create wrapper vec
        int numFrames = 2400;
        std::vector<AnimationWrapper> ani_vec;
        int i = 0;
        for (auto item : *card_vec) {
            AnimationWrapper wrapper = AnimationWrapper(item->getPSprite(), bounds_width / 2 - cardWidth / 2, 
                bounds_height / 2 - cardHeight / 2,
                (rand() % (bounds_width + 200)) - 100, (rand() % (bounds_height + 200)) - 100, numFrames);
            wrapper.setID(i);
            ani_vec.push_back(wrapper);
            i++;
        }
        // iterate through ani_vec, adding one each time
        for (int i = 0; i < (int)ani_vec.size() - 1; i++) {
            window->clear();
            for (int j = 0; j < i + 1; j++) {
                ani_vec.at(j).advance(i - ani_vec.at(j).getID());
                window->draw(*(ani_vec.at(j).getPSprite()));
            }
            window->display();
        }
        // keep animating more frames
        for (int i = (int)ani_vec.size(); i < (int)ani_vec.size() + 200; i++) {
            window->clear();
            for (int j = 0; j < (int)ani_vec.size(); j++) {
                ani_vec.at(j).advance(i - ani_vec.at(j).getID());
                window->draw(*(ani_vec.at(j).getPSprite()));
            }
            window->display();
        }
    }
}

void View::animateWin2(sf::RenderWindow* window) {
    srand((unsigned) time(0));
    Deck deck1 = Deck();
    Deck deck2 = Deck();
    Deck deck3 = Deck();
    Deck deck4 = Deck();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> card_vec = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    while (!deck1.isEmpty()) {
        deck1.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck2.isEmpty()) {
        deck2.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck3.isEmpty()) {
        deck3.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck4.isEmpty()) {
        deck4.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    // continue while loop till key is pressed or mouse clicked
    bool animation = true;
    while (animation) {
        sf::Event event;
        while (window->pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
				//window->close();
                animation = false;
                break;
			}
            else if (event.type == sf::Event::KeyReleased) {
                animation = false;
                break;
            }
        }
        if (animation == false) {
            break;
        }
        // code card burst here
        // create wrapper vec
        int numFrames = 2400;
        std::vector<AnimationWrapper> ani_vec;
        int i = 0;
        for (auto item : *card_vec) {
            AnimationWrapper wrapper = AnimationWrapper(item->getPSprite(), 
                (rand() % (bounds_width + 200)) - 100, 
                (rand() % (bounds_height + 200)) - 100,
                (rand() % (bounds_width + 200)) - 100, (rand() % (bounds_height + 200)) - 100, numFrames);
            wrapper.setID(i);
            ani_vec.push_back(wrapper);
            i++;
        }
        // iterate through ani_vec, adding one each time
        for (int i = 0; i < (int)ani_vec.size() - 1; i++) {
            window->clear();
            for (int j = 0; j < i + 1; j++) {
                ani_vec.at(j).advance(i - ani_vec.at(j).getID());
                window->draw(*(ani_vec.at(j).getPSprite()));
            }
            window->display();
        }
        // keep animating more frames
        for (int i = (int)ani_vec.size(); i < (int)ani_vec.size() + 200; i++) {
            window->clear();
            for (int j = 0; j < (int)ani_vec.size(); j++) {
                ani_vec.at(j).advance(i - ani_vec.at(j).getID());
                window->draw(*(ani_vec.at(j).getPSprite()));
            }
            window->display();
        }
    }
}

int View::getBoundsWidth() {
    return bounds_width;
}
int View::getBoundsHeight() {
    return bounds_height;
}
int View::getStackDistance() {
    return stackDistance;
}
std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getMainPile(int pile_num) {
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

std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getFoundationPile(int pile_num) {
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

std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getWastePile() {
    return wastePile;
}

std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getMovePile() {
    return movePile;
}

std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getDrawPile() {
    return drawPile;
}

std::shared_ptr<Deck> View::getDeck() {
    return deck;
}


#endif