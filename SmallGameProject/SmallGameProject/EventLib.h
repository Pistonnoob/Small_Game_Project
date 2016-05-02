#pragma once

namespace Events {
	enum ENTITY{
		CREATED,
		IDLE,
		MOVING,
		DEAD,
        Fire
	};
    enum UNIQUE_FIRE {
        ARCFIRE,
        SPLITFIREONBULLETS,
        REVERSERBULLETS,
    };
	enum STAGE {
		STAGECOMPLETED,
		STAGESTART,
		STAGEEND
	};

	enum WAVE {
		WAVECOMPLETED,
		WAVESTART,
		WAVEEND
	};

	enum ACHIEVEMENT
	{
		WEAPON_UNLOCK,
		POWERUP_UNLUCK,
	};

	enum PICKUP
	{
		WEAPON_PICKUP,
		POWERUP_PICKUP
	};
}
