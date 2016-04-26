#pragma once

namespace Events {
	enum ENTITY{
		CREATED,
		IDLE,
		MOVING,
		DEAD

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
