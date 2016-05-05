#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Observer.h"
#include "Projectile.h"
#include "GameState.h"
#include "RangedEnemy.h"
#include "MeleeEnemy.h"
#include "BomberEnemy.h"

struct trigger_event
{
	float timer;
	int start;
	int end;
	Events::UNIQUE_FIRE type;
	float arc;
	int nrOfProjectiles;
};

class ProjectileHandler : public Observer {

private:
	std::vector<Projectile*> projectiles;
	std::vector<Projectile*> unique_Projectiles;
	std::vector<trigger_event> eventsToTrack;
	Model m_ball;

	void triggerEvent(trigger_event &evnt, float arc, int nrOfBullets);
public:
	ProjectileHandler();
	~ProjectileHandler();
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void ShutDown();
	void update(float deltaTime);
	void render(GraphicHandler * gHandler, CameraHandler* camera);
	bool intersectionTest(Entity* entity);
	virtual void onNotify(Entity* entity, Events::ENTITY evnt);
	virtual void onNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets);
	virtual void onNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, float triggerDelay);
	virtual void onNotify(Entity* entity, Events::UNIQUE_FIRE evnt, float arc, int nrOfBullets, float triggerDelay, float arcOnSplit, int projectilesOnSplit);
	virtual void onNotify(Entity* entity, Events::ABILITY_TRIGGER evnt, float arc, int nrOfBullets);

	void fireInArc(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 dir, float arc, int nrOfBullets);

};

#endif