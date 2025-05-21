#pragma once
#include <string>
#include <string_view>

class Monster{
    public:
        enum Type{
            dragon,
            goblin,
            orc,
            ogre,
            skeleton,
            troll,
            vampire,
            zombie,
            maxMonsterTypes,
        };
    
    private:
        Type m_type{};
        std::string m_name{"???"};
        std::string m_roar{"???"};
        int m_hitpoints{};
    
        constexpr std::string getTypeString(Type t) const {
            switch(t) {
                case dragon: return "dragon";
                case goblin: return "goblin";
                case orc: return "orc";
                case ogre: return "ogre";
                case skeleton: return "skeleton";
                case troll: return "troll";
                case vampire: return "vampire";
                case zombie: return "zombie";
                default: return "???";
            }
        }
    
    public:
        Monster(Type type, std::string_view name, std::string_view roar, int hp)
            : m_type{type}
            , m_name{name}
            , m_roar{roar}
            , m_hitpoints{hp} {}
    
        void print() const;
    };
