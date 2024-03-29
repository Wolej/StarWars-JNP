//
// Created by Wojtek on 13/01/2019.
//

#ifndef UNTITLED_REBELFLEET_H
#define UNTITLED_REBELFLEET_H

#include "helper.h"
#include <cassert>
#include <memory>

class RebelStarship;
class RebelAttackingStarship;


class RebelStarship : public virtual SingleStarship{
    Speed speed;
public:
    RebelStarship(ShieldPoints shield, Speed nspeed) : SingleStarship(shield), speed(nspeed) {}

    Speed getSpeed() {
        return speed;
    };

    bool isRebel() { return true; }
};

class RebelAttackingStarship : public RebelStarship, public AttackingSingleStarship{
public:
    RebelAttackingStarship(ShieldPoints shield, Speed speed, AttackPower attack):    SingleStarship(shield), RebelStarship(shield, speed),
                                                                                    AttackingSingleStarship (shield, attack)
                                                                                     {}

    virtual void getAttacked(AttackingStarship &attacker) {
        AttackPower attacker_power = attacker.getAttackPower();
        attacker.takeDamage(this->getAttackPower());
        this->takeDamage(attacker_power);
    }
};



class XWing : public RebelAttackingStarship {
public:
    XWing(ShieldPoints shield, Speed speed, AttackPower attack) : SingleStarship(shield),
                                                                  RebelAttackingStarship(shield, speed, attack) {
        assert(speed.notGreater(2997960));
        assert(speed.notSmaller(299796));
    }
};

std::shared_ptr<RebelStarship>createXWing(int sh, int sp, int atp) {

    std::shared_ptr<RebelStarship> res;
    res = std::make_shared<XWing>(ShieldPoints(sh), Speed(sp), AttackPower(atp));
    return res;
}


class StarCruiser : public RebelAttackingStarship {
public:
    StarCruiser(ShieldPoints shield, Speed speed, AttackPower attack) : SingleStarship(shield),
                                                                        RebelAttackingStarship(shield, speed, attack) {
        assert(speed.notGreater(299795));
        assert(speed.notSmaller(99999));
    }
};

std::shared_ptr<RebelStarship> createStarCruiser(int sh, int sp, int atp) {

    std::shared_ptr<RebelStarship> res;
    res = std::make_shared<StarCruiser>(ShieldPoints(sh), Speed(sp), AttackPower(atp));
    return res;
}

class Explorer : public RebelStarship {
public:
    Explorer(ShieldPoints shield, Speed speed) : SingleStarship(shield),
                                                 RebelStarship(shield, speed) {
        assert(speed.notGreater(2997960));
        assert(speed.notSmaller(299796));
    }
};

std::shared_ptr<RebelStarship> createExplorer(int sh, int sp) {

    std::shared_ptr<RebelStarship> res;
    res = std::make_shared<Explorer>(ShieldPoints(sh), Speed(sp));
    return res;
}


#endif //UNTITLED_REBELFLEET_H
