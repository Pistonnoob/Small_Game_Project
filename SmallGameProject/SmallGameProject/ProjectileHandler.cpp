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
	for (int i = 0; i < this->projectiles.size(); i++)
	{
		Projectile* temp = this->projectiles.at(i);
        if (temp != nullptr)
        {
            temp->Shutdown();
            delete temp;
        }

	}
	this->projectiles.clear();

}
void ProjectileHandler::Update(float deltaTime)
{
	for (int i = 0; i < this->projectiles.size(); i++)
	{
        if (this->projectiles.at(i) != nullptr)
        {
            this->projectiles.at(i)->update(deltaTime);
            DirectX::XMFLOAT3 pos = this->projectiles.at(i)->GetPosition();
            if (pos.x < -100 || pos.x > 100 || pos.z < -100 || pos.z > 100)
            {
                Projectile* temp = this->projectiles.at(i);
                temp->Shutdown();
                delete temp;
                this->projectiles.at(i) = nullptr;
                //this->projectiles.erase(projectiles.begin() + i);
                //i--;
            }
        }

	}
}
void ProjectileHandler::Render(GraphicHandler * gHandler, CameraHandler* camera)
{
	XMFLOAT3 pos;
	DirectX::XMMATRIX worldMatrix;
	for (int i = 0; i < this->projectiles.size(); i++)
	{
        if (this->projectiles.at(i) != nullptr)
        {
            pos = this->projectiles.at(i)->GetPosition();
            worldMatrix = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
            this->projectiles.at(i)->GetModel()->SetWorldMatrix(worldMatrix);

            gHandler->DeferredRender(this->projectiles.at(i)->GetModel(), camera);
        }
	}
}
bool ProjectileHandler::IntersectionTest(Entity * entity)
{
	bool result = false;

	//do intersection test shit

	return result;
}
void ProjectileHandler::OnNotify(Entity* entity, Events::ENTITY evnt)
{

	switch (evnt)
	{
	case(Events::ENTITY::Fire) :

		XMFLOAT3 dir = entity->GetAimDir();
		XMFLOAT3 pos = entity->GetPosition();

		this->projectiles.push_back(new Projectile());
		this->projectiles.at(this->projectiles.size() - 1)->Initialize(&this->m_ball, nullptr, pos.x, pos.z, dir);
		break;
	}
}

void ProjectileHandler::OnNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets)
{

	trigger_event event;
	switch (evnt)
	{
	case(Events::UNIQUE_FIRE::ARCFIRE) :
		FireInArc(entity->GetPosition(), entity->GetAimDir(), arc, nrOfBullets);

		break;
	case(Events::UNIQUE_FIRE::SPLITFIRE) :

		event.start = this->projectiles.size();
		event.type = Events::ABILITY_TRIGGER::SPLITFIRE_ON_PROJECTILES;

		FireInArc(entity->GetPosition(), entity->GetAimDir(), arc, nrOfBullets);

		event.end = this->projectiles.size();

		this->eventsToTrack.push_back(event);

		break;
	case(Events::UNIQUE_FIRE::REVERSERBULLETS) :

		event.start = this->projectiles.size();
		event.type = Events::ABILITY_TRIGGER::REVERSER_PROJECTILES;

		FireInArc(entity->GetPosition(), entity->GetAimDir(), arc, nrOfBullets);

		event.end = this->projectiles.size();
		this->eventsToTrack.push_back(event);

		break;
	}
}
void ProjectileHandler::OnNotify(Entity * entity, Events::ABILITY_TRIGGER evnt, float arc, int nrOfBullets)
{
	for (int i = 0; i < this->eventsToTrack.size(); i++)
	{
		if (this->eventsToTrack.at(i).type == evnt)
		{
			this->triggerEvent(this->eventsToTrack.at(i), arc, nrOfBullets);
			this->eventsToTrack.erase(this->eventsToTrack.begin() + i);
			break;
		}
	}
}
void ProjectileHandler::OnNotify(Entity * entity, Events::PICKUP evnt)
{
}
void ProjectileHandler::FireInArc(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float arc, int nrOfBullets)
{
	float x = dir.x;
	float y = dir.y;
	float z = dir.z;
	float fireArc = arc;

	if (nrOfBullets == 1)
	{
		fireArc = 0;
	}

	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationY(-fireArc / 2);
	DirectX::XMVECTOR dirr = DirectX::XMVectorSet(dir.x, dir.y, dir.z, 0.0f);

	dirr = DirectX::XMVector3Transform(dirr, rotation);
	dirr = DirectX::XMVector3Normalize(dirr);

	int nrOfProjectiles = nrOfBullets;

	rotation = DirectX::XMMatrixRotationY(fireArc / (nrOfProjectiles - 1));

	for (int i = 0; i < nrOfProjectiles; i++)
	{
		x = DirectX::XMVectorGetX(dirr);
		y = DirectX::XMVectorGetY(dirr);
		z = DirectX::XMVectorGetZ(dirr);

		this->projectiles.push_back(new Projectile());
		this->projectiles.at(this->projectiles.size() - 1)->Initialize(&this->m_ball, nullptr, pos.x, pos.z, DirectX::XMFLOAT3(x, y, z));

		dirr = DirectX::XMVector3Transform(dirr, rotation);
	}
}
void ProjectileHandler::triggerEvent(trigger_event &evnt, float arc, int nrOfBullets)
{
    int projectilesErased = 0;
	DirectX::XMFLOAT3 dir;
	DirectX::XMFLOAT3 pos;
	for (int i = evnt.start; i < evnt.end; i++)
	{
        if (i >= this->projectiles.size())
        {
            break;
        }
        if (this->projectiles.at(i) == nullptr)
        {
            this->projectiles.erase(projectiles.begin() + i);
            i--;
            evnt.end--;
            projectilesErased++;
        }
        else
        {
            switch (evnt.type)
            {
            case(Events::ABILITY_TRIGGER::SPLITFIRE_ON_PROJECTILES) :

                dir = this->projectiles.at(i)->getMoveDir();
                pos = this->projectiles.at(i)->getPos();
                this->FireInArc(pos, dir, arc, nrOfBullets);

                break;
            case(Events::ABILITY_TRIGGER::REVERSER_PROJECTILES) :

                dir = this->projectiles.at(i)->getMoveDir();

                dir.x *= -1;
                dir.y *= -1;
                dir.z *= -1;

                this->projectiles.at(i)->setMoveDir(dir);

                break;
            }
        }

	}
    for (int i = 0; i < this->eventsToTrack.size(); i++)
    {
        this->eventsToTrack.at(i).start -= projectilesErased;
        this->eventsToTrack.at(i).end -= projectilesErased;
    }
}

