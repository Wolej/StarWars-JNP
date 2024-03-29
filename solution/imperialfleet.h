//
// Created by Wojtek on 13/01/2019.
//

#ifndef UNTITLED_IMPERIALFLEET_H
#define UNTITLED_IMPERIALFLEET_H

#include <vector>
#include <memory>
#include "helper.h"


class ImperialStarship;
class ImperialSingleStarship;
class Squadron;


class ImperialStarship : public virtual AttackingStarship {
public:
    bool virtual isRebel() override{ return false; }
};

class ImperialSingleStarship : public virtual AttackingSingleStarship, public ImperialStarship {
public:
    ImperialSingleStarship(ShieldPoints shield, AttackPower attack) : SingleStarship(shield), AttackingSingleStarship(shield, attack){}
};

class Squadron : public ImperialStarship {
    std::vector<std::shared_ptr<ImperialStarship>> ships;
public:

    Squadron(std::vector<std::shared_ptr<ImperialStarship>> ships_v) {
        ships = ships_v;
    }

    Squadron (std::initializer_list<std::shared_ptr<ImperialStarship>> ships_l) : ships(ships_l) {};

    int count() {
        int res = 0;
        for (auto ship : ships) {
            res += ship->count();
        }
        return res;
    }

    ShieldPoints getShield() override {
        ShieldPoints res = ShieldPoints(0);
        for (auto ptr : ships) {
            if (ptr->count() > 0) {
                res.add(ptr->getShield());
            }
        }
        return res;
    };

    AttackPower getAttackPower() override {
        AttackPower res = AttackPower(0);
        for (auto ptr : ships) {
            if (ptr->count() > 0) {
                res.add(ptr->getAttackPower());
            }
        }
        return res;
    };

    void takeDamage(AttackPower damage) override {
        for (auto ptr : ships) {
            ptr->takeDamage(damage);
        }
    };
};

std::shared_ptr<ImperialStarship> createSquadron (std::vector<std::shared_ptr<ImperialStarship>> ships_v) {
    std::shared_ptr<ImperialStarship> res;
    res = std::make_shared<Squadron>(ships_v);
    return res;
}



class DeathStar : public ImperialSingleStarship {
public:
    DeathStar(ShieldPoints shield, AttackPower attack) : SingleStarship(shield), 
                                                         AttackingSingleStarship(shield, attack), ImperialSingleStarship(shield, attack){}
};

std::shared_ptr<ImperialStarship> createDeathStar(int sh, int atp) {

    std::shared_ptr<ImperialStarship> res;
    res = std::make_shared<DeathStar>(ShieldPoints(sh), AttackPower(atp));
    return res;
}

class ImperialDestroyer : public ImperialSingleStarship {
public:
    ImperialDestroyer(ShieldPoints shield, AttackPower attack) : SingleStarship(shield), AttackingSingleStarship(shield, attack), ImperialSingleStarship(shield, attack)
    {}
};

std::shared_ptr<ImperialStarship> createImperialDestroyer(int sh, int atp) {

    std::shared_ptr<ImperialStarship> res;
    res = std::make_shared<ImperialDestroyer>(ShieldPoints(sh), AttackPower(atp));
    return res;
}
class TIEFighter : public ImperialSingleStarship {
public:
    TIEFighter(ShieldPoints shield, AttackPower attack) : SingleStarship(shield), AttackingSingleStarship(shield, attack), ImperialSingleStarship(shield, attack)
    {}
};

std::shared_ptr<ImperialStarship> createTIEFighter(int sh, int atp) {

    std::shared_ptr<ImperialStarship> res;
    res = std::make_shared<TIEFighter>(ShieldPoints(sh), AttackPower(atp));
    return res;
}
#endif //UNTITLED_IMPERIALFLEET_H
