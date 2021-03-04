#include "Character.hpp"
#include "RadScorpion.hpp"
#include "SuperMutant.hpp"
#include "Fish.hpp"
#include "Fox.hpp"
#include "PlasmaRifle.hpp"
#include "PowerFist.hpp"
#include "Grenade.hpp"
#include "FlameThrower.hpp"

int main()
{
    std::stringstream ss;
    Character* moi = new Character("moi");

    std::cout << *moi;

    Enemy* b = new RadScorpion();
    Enemy *c = new SuperMutant();
    Enemy *fish = new Fish();
    Enemy *fox = new Fox();

    AWeapon* pr = new PlasmaRifle();
    AWeapon* pf = new PowerFist();
    AWeapon* grenade = new Grenade();
    AWeapon* flameThrower = new FlameThrower();

    moi->attack(b);

    moi->equip(pf);
    moi->attack(b);

    std::cout << *moi;

    moi->equip(pr);
    std::cout << *moi;

    moi->attack(b);
    std::cout << *moi;
    ss << b->getHP();
    std::cout <<" il reste " + ss.str() + " hp a l'ennemie de type " + b->getType() << std::endl;
    ss.str("");

    moi->attack(c);
    std::cout << *moi;

    ss << c->getHP();
    std::cout <<" il reste " + ss.str() + " hp a l'ennemie de type " + c->getType() << std::endl;
    ss.str("");

    moi->attack(c);
    moi->attack(c);
    moi->attack(c);
    moi->attack(c);
    moi->attack(c);

    ss << c->getHP();
    std::cout <<" il reste " + ss.str() + " hp a l'ennemie de type " + c->getType() << std::endl;
    ss.str("");


    moi->equip(grenade);
    moi->recoverAP();
    std::cout << *moi;
    moi->attack(c);


    moi->equip(flameThrower);
    moi->recoverAP();
    std::cout << *moi;
    moi->attack(c);

    std::cout << *moi;
    moi->attack(fish);

    moi->recoverAP();
    std::cout << *moi;
    moi->attack(fox);

    delete b;
    delete c;
    delete fish;
    delete fox;
    delete pr;
    delete pf;
    delete grenade;
    delete flameThrower;

    return 0;
}
