#pragma once

namespace Modifiers
{
	//xNN stands for the amount of % the damage is increased
	enum WEAPON
	{
		DAMAGE_UPx10,				//0
		DAMAGE_UPx20,				//1
		DAMAGE_UPx30,				//2

		DAMAGE_DOWNx10,				//3
		DAMAGE_DOWNx20,				//4
		DAMAGE_DOWNx30,				//5

		SPEED_UPx10,				//6
		SPEED_UPx20,				//7
		SPEED_UPx30,				//8

		SPEED_DOWNx10,				//9
		SPEED_DOWNx20,				//10
		SPEED_DOWNx30,				//11
		
		ATTACK_SPEED_UPx10,			//12
		ATTACK_SPEED_UPx20,			//13
		ATTACK_SPEED_UPx30,			//14

		ATTACK_SPEED_DOWNx10,		//15
		ATTACK_SPEED_DOWNx20,		//16
		ATTACK_SPEED_DOWNx30		//17
	};

	//not yet implemented
	enum POWERUPS
	{
		SPREAD_INCREASE				//0
	};
}
