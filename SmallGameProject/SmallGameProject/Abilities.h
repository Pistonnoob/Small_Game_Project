#ifndef ABILITIES
#define ABILITIES
#include "Ability.h"


class ArcFire : public Ability
{
private:

protected:
    bool isActivated;


public:
    ArcFire();
    virtual~ArcFire();
    virtual void activate(Enemy* enemy, EntitySubject* entitySubject, DirectX::XMFLOAT3 playerPos, float arc, int nrOfProjectiles);
    virtual void update(Enemy* enemy, EntitySubject* entitySubject);



};

class SplitFire : public Ability
{
private:
    int counter;
public:
    SplitFire();
    virtual~SplitFire();
    virtual void activate(Enemy* enemy, EntitySubject* entitySubject, DirectX::XMFLOAT3 playerPos, float arc, int nrOfProjectiles);
    virtual void update(Enemy* enemy, EntitySubject* entitySubject);

};

class ReverseFire : public Ability
{
private:
    int counter;
public:
    ReverseFire();
    virtual~ReverseFire();
    virtual void activate(Enemy* enemy, EntitySubject* entitySubject, DirectX::XMFLOAT3 playerPos, float arc, int nrOfProjectiles);
    virtual void update(Enemy* enemy, EntitySubject* entitySubject);

};

#endif
