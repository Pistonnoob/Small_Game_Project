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
    for (int i = 0; i < this->projectiles.size(); i++)
    {
        Projectile* temp = this->projectiles.at(i);
        temp->Shutdown();
        delete temp;
    }
    this->projectiles.clear();
    this->m_ball.Shutdown();
}
void ProjectileHandler::update()
{
    for (int i = 0; i < this->projectiles.size(); i++)
    {
        this->projectiles.at(i)->update();
        DirectX::XMFLOAT3 pos = this->projectiles.at(i)->getPosition();
        if (pos.x < -100 || pos.x > 100 || pos.z < -100 || pos.z > 100)
        {
            Projectile* temp = this->projectiles.at(i);
            temp->Shutdown();
            delete temp;
            this->projectiles.erase(projectiles.begin() + i);
            i--;
        }
    }
}
void ProjectileHandler::render(GraphicHandler * gHandler, CameraHandler* camera)
{
    XMFLOAT3 pos;
    DirectX::XMMATRIX worldMatrix;
    for (int i = 0; i < this->projectiles.size(); i++)
    {
        pos = this->projectiles.at(i)->getPosition();
        worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
        this->projectiles.at(i)->getModel()->SetWorldMatrix(worldMatrix);

        gHandler->DeferredRender(this->projectiles.at(i)->getModel(), camera);
    }
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
            
            this->projectiles.push_back(new Projectile());
            this->projectiles.at(this->projectiles.size() - 1)->Initialize(&this->m_ball, nullptr, pos.x, pos.z, dir);
        }
        break;
    }
}

void ProjectileHandler::onNotify(Entity* entity, Events::BOSS evnt, float arc, int nrOfBullets)
{
    Enemy* ptr = nullptr;
    ptr = dynamic_cast<Enemy*>(entity);
    switch (evnt)
    {
    case(Events::BOSS::ARCFIRE) :
        fireInArc(ptr->getPosition(), ptr->getAimDir(), arc, nrOfBullets);
            break;
    }
}
void ProjectileHandler::fireInArc(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float arc, int nrOfBullets)
{
    DirectX::XMMATRIX rotation;
    int nrOfProjectiles = nrOfBullets;
    rotation = DirectX::XMMatrixRotationY(arc / nrOfProjectiles);
    DirectX::XMVECTOR dirr = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);
    float x;
    float y;
    float z;
    for (int i = 0; i <= nrOfProjectiles; i++)
    {
        x = DirectX::XMVectorGetX(dirr);
        y = DirectX::XMVectorGetY(dirr);
        z = DirectX::XMVectorGetZ(dirr);
        Projectile* temp = new Projectile();
        temp->Initialize(&this->m_ball, nullptr, pos.x, pos.z, dir);
        projectiles.push_back(temp);
        dirr = DirectX::XMVector3Transform(dirr, rotation);
    }
}
