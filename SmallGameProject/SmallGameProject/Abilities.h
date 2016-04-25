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
    virtual void activate(std::vector<Projectile*>& projectiles, Model* projectileModel, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float angle, int nrOfProjectiles);
    virtual void update(std::vector<Projectile*>& projectiles, Model* projectileModel);



};

class SplitFire : public Ability
{
private:
    int counter;
public:
    SplitFire();
    virtual~SplitFire();
    virtual void activate(std::vector<Projectile*>& projectiles, Model* projectileModel, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float angle, int nrOfProjectiles);
    virtual void update(std::vector<Projectile*>& projectiles, Model* projectileModel);

};

class ReverseFire : public Ability
{
private:
    int counter;
public:
    ReverseFire();
    virtual~ReverseFire();
    virtual void activate(std::vector<Projectile*>& projectiles, Model* projectileModel, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float angle, int nrOfProjectiles);
    virtual void update(std::vector<Projectile*>& projectiles, Model* projectileModel);

};

#endif
