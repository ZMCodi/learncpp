#include "Deck.h"

Deck::Deck() {
    std::size_t count{};
    for (auto suit : Card::allSuits)
        for (auto rank : Card::allRanks) {
            m_cards[count++] = Card{rank, suit};
        }

}

Card Deck::dealCard() {
    assert(m_idx < 52 && "Out of cards");
    return m_cards[m_idx++];
}

void Deck::shuffle() {
    std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
    m_idx = 0;
}
