#pragma once
#include <array>
#include <string_view>

struct Card {

    enum Rank {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,
        max_ranks,
    };

    enum Suit {
        suit_club,
        suit_diamond,
        suit_heart,
        suit_spade,
        max_suits,
    };

    Rank rank{};
    Suit suit{};

    static constexpr std::array<Rank, max_ranks> allRanks{
        rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king
    };
    static constexpr std::array<Suit, max_suits> allSuits{
        suit_club, suit_diamond, suit_heart, suit_spade
    };
    static constexpr std::array<std::string_view, max_ranks> ranks{
        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
    };
    static constexpr std::array<std::string_view, max_suits> suits{"C", "D", "H", "S"};

    int value();
    friend std::ostream& operator<<(std::ostream& out, const Card &card);
};
