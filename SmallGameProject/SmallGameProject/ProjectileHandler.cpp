#include "ProjectileHandler.h"

ProjectileHandler::ProjectileHandler()
{
    this->m_ball = Model();
}
ProjectileHandler::~ProjectileHandler()
{

}
bool ProjectileHandler::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
    bool result = true;
    result = this->m_ball.Initialize(device, deviceContext, "sphere1");

    return result;
}
void ProjectileHandler::ShutDown()
{
    this->m_ball.Shutdown();
    this->clearProjectileVector(this->playerProjectiles);
    this->clearProjectileVector(this->enemyProjectiles);
    this->clearProjectileVector(this->bossProjectiles);

}
void ProjectileHandler::update()
{
    this->updateProjectileVector(this->playerProjectiles);
    this->updateProjectileVector(this->enemyProjectiles  );
    this->updateProjectileVector(this->bossProjectiles   );
}
void ProjectileHandler::render(GraphicHandler * gHandler, CameraHandler* camera)
{
    this->renderProjectileVector(gHandler, camera, this->playerProjectiles);
    this->renderProjectileVector(gHandler, camera, this->enemyProjectiles);
    this->renderProjectileVector(gHandler, camera, this->bossProjectiles);
}
void ProjectileHandler::onNotify(Entity* entity, Events::ENTITY evnt)
{

    switch (evnt)
    {
    case(Events::ENTITY::Fire) :
        RangedEnemy* ptr = nullptr;
        ptr = dynamic_cast<RangedEnemy*>(entity);
        if (ptr != nullptr)
        {
           XMFLOAT3 dir = ptr->getAimDir();
            XMFLOAT3 pos = ptr->getPosition();
            
            this->enemyProjectiles.push_back(new Projectile());
            this->enemyProjectiles.at(this->enemyProjectiles.size() - 1)->Initialize(&this->m_ball, nullptr, pos.x, pos.z, dir);
        }
        break;
    }
}

void ProjectileHandler::onNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets)
{


    std::vector<Projectile*>* vecPtr = nullptr;
    if (entity->getType() == Type::RANGED)
    {
        vecPtr = &this->bossProjectiles;
    }
    else if(entity->getType() == Type::PLAYER)
    {
        vecPtr = &this->playerProjectiles;
    }

    switch (evnt)
    {
    case(Events::UNIQUE_FIRE::ARCFIRE) :
        fireInArc(*vecPtr, entity->getPosition(), entity->getAimDir(), arc, nrOfBullets);
            break;
    }
}
void ProjectileHandler::fireInArc(std::vector<Projectile*> &projectiles, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float arc, int nrOfBullets)
{
    float x = dir.x;
    float y = dir.y;
    float z = dir.z;

    DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationY(-arc / 2);
    DirectX::XMVECTOR dirr = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);
    dirr = DirectX::XMVector3Transform(dirr, rotation);

    int nrOfProjectiles = nrOfBullets;
    rotation = DirectX::XMMatrixRotationY(arc / nrOfProjectiles);

    for (int i = 0; i <= nrOfProjectiles; i++)
    {
        x = DirectX::XMVectorGetX(dirr);
        y = DirectX::XMVectorGetY(dirr);
        z = DirectX::XMVectorGetZ(dirr);
        //Projectile* temp = new Projectile();
        //temp->Initialize(&this->m_ball, nullptr, pos.x, pos.z, dir);
        this->bossProjectiles.push_back(new Projectile());
        this->bossProjectiles.at(this->bossProjectiles.size() - 1)->Initialize(&this->m_ball, nullptr, pos.x, pos.z, DirectX::XMFLOAT3(x, y, z));
        dirr = DirectX::XMVector3Transform(dirr, rotation);
    }
}


void ProjectileHandler::renderProjectileVector(GraphicHandler * gHandler, CameraHandler* camera, std::vector<Projectile*>& projectiles)
{
    XMFLOAT3 pos;
    DirectX::XMMATRIX worldMatrix;
    for (int i = 0; i < projectiles.size(); i++)
    {
        pos = projectiles.at(i)->getPosition();
        worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
        projectiles.at(i)->getModel()->SetWorldMatrix(worldMatrix);

        gHandler->DeferredRender(projectiles.at(i)->getModel(), camera);
    }
}
void ProjectileHandler::updateProjectileVector(std::vector<Projectile*>& projectiles)
{
    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles.at(i)->update();
        DirectX::XMFLOAT3 pos = projectiles.at(i)->getPosition();
        if (pos.x < -100 || pos.x > 100 || pos.z < -100 || pos.z > 100)
        {
            Projectile* temp = projectiles.at(i);
            temp->Shutdown();
            delete temp;
            projectiles.erase(projectiles.begin() + i);
            i--;
        }
    }
}

void ProjectileHandler::clearProjectileVector(std::vector<Projectile*>& projectiles)
{
    for (int i = 0; i < projectiles.size(); i++)
    {
        Projectile* temp = projectiles.at(i);
        temp->Shutdown();
        delete temp;
    }
    projectiles.clear();
}
