#include "Blackjack.h"

bool playersTurn(Deck& deck, Player& player) {
    std::cout << "\n(h) to hit, or (s) to stand: ";
    char choice{};
    std::cin >> choice;

    if (choice == 's') {return false;}

    Card card{deck.dealCard()};

    std::cout << "You were dealt " << card;
    player.score += card.value();
    std::cout << ". You now have: " << player.score;

    if (player.score >= Settings::bust) {return false;}

    return true;
}

bool dealersTurn(Deck& deck, Dealer& dealer) {
    Card card{deck.dealCard()};

    std::cout << "\nThe dealer flips a " << card;
    dealer.score += card.value();
    std::cout << ". They now have: " << dealer.score;

    if (dealer.score >= Settings::dealerMax) {return false;}
    if (dealer.score >= Settings::bust) {return false;}

    return true;
}

// returns true if dealer wins, false if player wins
bool blackjack() {

    Deck deck{};
    deck.shuffle();

    // draw one card for the dealer
    Dealer dealer{deck.dealCard().value()};
    std::cout << "\nThe dealer is showing: " << dealer.score;

    // draw two for the player
    Player player{deck.dealCard().value() + deck.dealCard().value()};
    std::cout << "\nYou have score: " << player.score;
    if (player.score == Settings::bust) {
        std::cout << "\nBazinga! You got blackjack!!";
        return false;
    }

    // player's turn
    while (playersTurn(deck, player));
    if (player.score > Settings::bust) {return true;}
    if (player.score == Settings::bust) {return false;}

    // dealer's turn
    while (dealersTurn(deck, dealer));
    if (dealer.score > Settings::bust) {return false;}
    if (dealer.score == Settings::bust) {return true;}

    return dealer.score >= player.score;
}
