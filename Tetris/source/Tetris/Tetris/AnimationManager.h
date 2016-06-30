#pragma once
#include <chrono>
#include "EventSubscriber.h"

class Library::EventPublisher;
class Library::WorldState;
class Library::World;
class Library::TetrominoRender;
class AnimationManager : public Library::EventSubscriber
{
public:
	AnimationManager(Library::WorldState& state, Library::World& nextWorld, sf::RenderWindow& window);
	~AnimationManager();
	void RenderScreen(Library::TetrominoRender& renderer, Library::GameTime& time);

	void RenderFrame(Library::TetrominoRender& renderer, Library::GameTime& time);
	/**
	*Called when an event is fired, we verify its subtype and react to it.
	*
	*@param publisher = the event we're being notified
	*/
	void Notify(Library::EventPublisher* publisher) override;

	/**
	*Sets the current frame of the animation.
	*
	*@param frameNum = the number of the frame to play
	*/
	void SetCurrentFrame(int frameNum);

	/**
	*Gets the current frame index of the animation.
	*
	*@return int = the number of the current frame
	*/
	int GetCurrentFrame();

private:
	Library::WorldState* mCurrentWorldState;
	Library::World* mNextWorld;
	sf::RenderWindow* mWindow;
	bool mHasScreenLoaded = false;

	int mCurrentFrame;
	/*std::chrono::milliseconds mElapsedTime;
	std::chrono::milliseconds mTimeBetweenFrames;
	std::chrono::milliseconds mFrameDelay;*/

	float mElapsedTime;
	float mFrameDelay;

	bool mAtBeginning;
};