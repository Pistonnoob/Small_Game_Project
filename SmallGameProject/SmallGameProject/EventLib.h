#pragma once

namespace Events {
	enum ENTITY{
		CREATED,
		IDLE,
		MOVING,
		DEAD,
        Fire

	};
    enum BOSS {
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
}