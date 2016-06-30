#pragma once

#include <windows.h>
#include <exception>
#include "GameTime.h"
#include "SFML\System.hpp"

namespace Library
{
    class GameClock
    {
    public:
        GameClock();

        const LARGE_INTEGER& StartTime() const;
        const LARGE_INTEGER& CurrentTime() const;
        const LARGE_INTEGER& LastTime() const;

        void Reset();
        double GetFrequency() const;
        void GetTime(LARGE_INTEGER& time) const;
        void UpdateGameTime(GameTime& gameTime);

		/**
		*Wrapped to SFML get elapsed seconds (since last call)
		*
		*@return seconds as a float (1.0f == 1 second)
		*/
		float GetSFElapsedTime();

		/**
		*Resets the SFML clock (allows us to call GetSFElapsedTime again, starting at 0)
		*/
		void ResetSFClock();


    private:
        GameClock(const GameClock& rhs);
        GameClock& operator=(const GameClock& rhs);
        LARGE_INTEGER mStartTime;
        LARGE_INTEGER mCurrentTime;
        LARGE_INTEGER mLastTime;
        double mFrequency;
		sf::Time mSFTimer;
		sf::Clock mSFClock;
    };
}
