#ifndef MODIFIERS_H
#define MODIFIERS_H
namespace Modifiers
{
	//xNN stands for the amount of % the damage is increased
	enum WEAPON
	{
		PISTOL,
		SHOTGUN,
		UZI
	};

	int const static nrOfWeapons = 3;

	//not yet implemented
	enum POWERUPS
	{
		SPREAD_INCREASE,				//0
		PENETRATION						//1 if you know what I mean
	};

	int const static nrOfPowerUps = 2;
}
#endif