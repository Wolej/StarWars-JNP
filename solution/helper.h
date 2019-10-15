#ifndef UNTITLED_HELPER_H
#define UNTITLED_HELPER_H
class ShieldPoints;
class AttackPower;
class Speed;
class StarshipAbstract;
class SingleStarship;
class AttackingStarship;
class AttackingSingleStarship;

class AttackPower {
    int attackPower;
public:

    AttackPower(int attack) {
        attackPower = attack;
    }

    inline bool operator==(const AttackPower& other) {
      return attackPower == other.attackPower;
    }

    int getAttackPower() {
        return attackPower;
    };

    void add(AttackPower a) {
        attackPower += a.attackPower;
    }
};

class ShieldPoints {
    int shield;
public:
    ShieldPoints(int s) {
        shield = s;
    }

    inline bool operator==(const ShieldPoints& other) {
      return shield == other.shield;
    }


    void takeDamage(AttackPower damage) {
        int dam = damage.getAttackPower();
        if (dam > this->shield) this->shield = 0;
        else this->shield -= dam;
    }
    int getShield() {
        return shield;
    };

    void add(ShieldPoints s) {
        shield += s.shield;
    }
};


class Speed {
    int speed;
public:
    Speed(int s) {
        speed = s;
    }
    bool notGreater(int x) { return speed <= x; }
    bool notSmaller(int x) { return speed >= x; }
};

class StarshipAbstract {
public:
//    virtual void getAttacked(AttackingStarship &attacker) = 0;
    virtual ShieldPoints getShield() = 0;
    virtual void takeDamage(AttackPower damage) = 0;
    virtual int count() = 0;
    virtual bool isRebel() = 0;
};

class AttackingStarship : public virtual StarshipAbstract {
public:
    virtual AttackPower getAttackPower() = 0;
};

class SingleStarship : public virtual StarshipAbstract {
    ShieldPoints shield;
public:
    SingleStarship(ShieldPoints nshield): shield(nshield){}

    ShieldPoints getShield() override {
        return shield;
    }

    void takeDamage(AttackPower damage) override {
        shield.takeDamage(damage);
    }

    int count() override {
        if (shield.getShield() == 0)
            return 0;
        else
            return 1;
    }

    virtual void getAttacked(AttackingStarship &attacker) {
        this->takeDamage(attacker.getAttackPower());
    }
};

class AttackingSingleStarship : public virtual AttackingStarship, public virtual SingleStarship {
    AttackPower attackPower;
public:
    AttackingSingleStarship(ShieldPoints shield, AttackPower attack) : SingleStarship(shield), attackPower(attack){};

    AttackPower getAttackPower() {
        return attackPower;
    }
};
#endif //UNTITLED_HELPER_H
