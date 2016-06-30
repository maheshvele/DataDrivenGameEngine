#include "pch.h"
#include "GameClock.h"

namespace Library
{
    GameClock::GameClock()
		: mStartTime(), mCurrentTime(), mLastTime(), mFrequency(), mSFTimer(), mSFClock()
    {
        mFrequency = GetFrequency();
        Reset();	
    }

    const LARGE_INTEGER& GameClock::StartTime() const
    {
        return mStartTime;
    }

    const LARGE_INTEGER& GameClock::CurrentTime() const
    {
        return mCurrentTime;
    }

    const LARGE_INTEGER& GameClock::LastTime() const
    {
        return mLastTime;
    }

    void GameClock::Reset()
    {
        GetTime(mStartTime);
        mCurrentTime = mStartTime;
        mLastTime = mCurrentTime;
    }

    double GameClock::GetFrequency() const
    {
        LARGE_INTEGER frequency;

        if (QueryPerformanceFrequency(&frequency) == false)
        {
            throw std::exception("QueryPerformanceFrequency() failed.");
        }

        return (double)frequency.QuadPart;
    }
    void GameClock::GetTime(LARGE_INTEGER& time) const
    {
        QueryPerformanceCounter(&time);
    }

    void GameClock::UpdateGameTime(GameTime& gameTime)
    {
        GetTime(mCurrentTime);
        gameTime.SetTotalGameTime((mCurrentTime.QuadPart - mStartTime.QuadPart) / mFrequency);
        gameTime.SetElapsedGameTime((mCurrentTime.QuadPart - mLastTime.QuadPart) / mFrequency);

        mLastTime = mCurrentTime;
    }

	/**
	*Wrapped to SFML get elapsed seconds (since last call)
	*
	*@return seconds as a float (1.0f == 1 second)
	*/
	float GameClock::GetSFElapsedTime()
	{
		return mSFClock.getElapsedTime().asSeconds();
	}

	/**
	*Resets the SFML clock (allows us to call GetSFElapsedTime again, starting at 0)
	*/
	void GameClock::ResetSFClock()
	{
		mSFClock.restart();

	}
}