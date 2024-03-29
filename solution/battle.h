//
// Created by Wojtek on 13/01/2019.
//

#ifndef UNTITLED_BATTLE_H
#define UNTITLED_BATTLE_H

#include <memory>
#include <vector>
#include <iostream>
#include "helper.h"
#include "rebelfleet.h"
#include "imperialfleet.h"

typedef std::size_t Time;

class Builder;
class StrategyAbstract {
public:
    virtual bool isTimeOfAttack(Time t) = 0;
};

class Strategy : StrategyAbstract {
public:
    bool isTimeOfAttack(Time t) override{
        return (t%5 and (!(t%2) or !(t%3)));
    }
};

class ClockAbstract {
public:
    virtual Time getCurrTime() = 0;
    virtual void advance(Time t) = 0;
};

class Clock : public ClockAbstract {
    Time maxTime;
    Time currTime;
public:
    Clock(Time maxT, Time currT) {
        maxTime = maxT + 1;
        currTime = currT;
    }

    void advance(Time t) override{
        currTime += t;
        currTime = currTime%maxTime;
    }

    Time getCurrTime() {
        return  currTime;
    }
};


class SpaceBattleAbstract {
public:
    virtual size_t countImperialFleet() = 0;
    virtual size_t countRebelFleet() = 0;
    virtual void tick(Time Timestep) = 0;
};

class SpaceBattle : public  SpaceBattleAbstract {
    std::vector<std::shared_ptr<ImperialStarship>> imperials;
    std::vector<std::shared_ptr<RebelStarship>> rebels;
    Clock clock;
    Strategy strategy;

    void battle() {
        for (auto imperial : imperials) {
            for (auto rebel : rebels) {
                if (imperial->count() > 0 and rebel->count() > 0) {
                    rebel->getAttacked(*imperial);
                }
            }
        }
    }
public:
    class Builder;

    SpaceBattle(Clock c, Strategy s, std::vector<std::shared_ptr<ImperialStarship>> imperialFleet,
    std::vector<std::shared_ptr<RebelStarship>> rebelFleet) : imperials(imperialFleet), rebels(rebelFleet),
                                                              clock(c), strategy(s)
                                    {};

    size_t countImperialFleet() {
        size_t res = 0;
        for (auto ptr : imperials) {
            res += ptr->count();
        }
        return res;
    }

    size_t countRebelFleet() {
        size_t res = 0;
        for (auto ptr : rebels) {
            res += ptr->count();
        }
        return res;
    }

    void tick(Time timeStep) {

        if (countRebelFleet() == 0) {
            if (countImperialFleet() == 0) {
                std::cout << "DRAW\n";
            } else {
                std::cout << "IMPERIUM WON\n";
            }
            return;
        } else {
            if (countImperialFleet() == 0) {
                std::cout << "REBEL WON\n";
                return;
            }
        }


        if (strategy.isTimeOfAttack(clock.getCurrTime())) {
            battle();
        }

        clock.advance(timeStep);
    }
};

class SpaceBattle::Builder {
    std::vector<std::shared_ptr<ImperialStarship>> imperials;
    std::vector<std::shared_ptr<RebelStarship>> rebels;
    Time start;
    Time maxT;

public:
    Builder& ship(std::shared_ptr<StarshipAbstract> s) {
        if (s->isRebel()) {
            std::shared_ptr<RebelStarship> reb = std::dynamic_pointer_cast<RebelStarship>(s);
            rebels.push_back(reb);
        } else {
            std::shared_ptr<ImperialStarship> imp = std::dynamic_pointer_cast<ImperialStarship>(s);
            imperials.push_back(imp);
        }
        return *this;
    }

    Builder& startTime(Time t) { start = t; return *this; };

    Builder& maxTime(Time t) { maxT = t; return *this; }

    SpaceBattle build() const {
        return SpaceBattle(Clock(maxT, start), Strategy(), imperials, rebels);
    }

};

#endif //UNTITLED_BATTLE_H
