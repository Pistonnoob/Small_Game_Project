#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Observer.h"
#include "Projectile.h"
#include "GameState.h"
#include "RangedEnemy.h"
#include "MeleeEnemy.h"
#include "BomberEnemy.h"

class ProjectileHandler : public Observer {

private:
    std::vector<Projectile*> playerProjectiles;
    std::vector<Projectile*> enemyProjectiles;
    std::vector<Projectile*> bossProjectiles;
    Model m_ball;

    void renderProjectileVector(GraphicHandler * gHandler, CameraHandler* camera, std::vector<Projectile*>& projectiles);
    void updateProjectileVector(std::vector<Projectile*>& projectiles);
    void clearProjectileVector(std::vector<Projectile*>& projectiles);
public:
    ProjectileHandler();
    ~ProjectileHandler();
    bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
    void ShutDown();
    void update();
    void render(GraphicHandler * gHandler, CameraHandler* camera);
    virtual void onNotify(Entity* entity, Events::ENTITY evnt);
    virtual void onNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets);

    void fireInArc(std::vector<Projectile*> &projectiles, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float arc, int nrOfBullets);

};

#endif