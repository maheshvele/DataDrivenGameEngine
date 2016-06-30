#include "pch.h"
#include "AnimationManager.h"
#include "World.h"
#include "WorldState.h"
#include "EventPublisher.h"
#include <string>
#include <chrono>

using namespace std::chrono;
using namespace Library;

AnimationManager::AnimationManager(WorldState& state, World& nextWorld, sf::RenderWindow& window) :
mCurrentWorldState(&state), mNextWorld(&nextWorld), mWindow(&window), mCurrentFrame(0), mElapsedTime(0), mFrameDelay(400), mAtBeginning(true)
{
	Event<EventMessageAttributed>::Subscribe(this);
}

void AnimationManager::RenderScreen(Library::TetrominoRender& renderer, Library::GameTime& time)
{
	RenderFrame(renderer, time);
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::RenderFrame(Library::TetrominoRender& renderer, Library::GameTime& time)
{
	if (mAtBeginning)
	{
		mCurrentWorldState->GetGameTime().SetElapsedGameTime(0);
		mAtBeginning = false;
	}
	
	mElapsedTime += (float)time.ElapsedGameTime();

	std::cout << "ElapsedTime: " << mElapsedTime << std::endl;

	if (mElapsedTime >= mFrameDelay)
	{
		++mCurrentFrame;
		if (mCurrentFrame > 31)
		{
			mCurrentFrame = 0;
			mAtBeginning = true;
			mCurrentWorldState->SetWorld(mNextWorld);
		}
		mElapsedTime = 0;
		time.SetElapsedGameTime(0);
	}

	renderer.RenderFrame(*mWindow, mCurrentFrame, sf::Vector2f(0, 0), sf::Vector2f(4, 4));
}


void AnimationManager::Notify(Library::EventPublisher* publisher)
{
	if (mCurrentWorldState->GetWorld()->Name() == "IntroAnimation")
	{
		Event<EventMessageAttributed>* message = publisher->As<Event<EventMessageAttributed>>();
		if (message != nullptr)
		{
			if (message->Message().GetSubtype() == "KeyboardRelease")
			{
				std::string keyPressed = message->Message().Find("Key")->Get<std::string>();
				if (keyPressed.length() > 0)
				{
					if ((keyPressed == "Down"))
					{
						if (mHasScreenLoaded)
						{
							mCurrentFrame = 0;
							mAtBeginning = true;
							mCurrentWorldState->SetWorld(mNextWorld);
							mHasScreenLoaded = false;
						}
						else
						{
							mHasScreenLoaded = true;
						}
					}
				}
			}
		}
	}
}
