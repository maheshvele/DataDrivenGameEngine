#pragma once
#include "EventSubscriber.h"

class Library::EventPublisher;
class Library::WorldState;
class Library::World;
class Library::TetrominoRender;
class LevelSelectorManager :
	public Library::EventSubscriber
{
public:
	LevelSelectorManager(Library::WorldState& state, Library::World& nextWorld, sf::RenderWindow& window);
	~LevelSelectorManager();

	void RenderScreen(Library::TetrominoRender& renderer);

	/**
	*Called when an event is fired, we verify its subtype and react to it.
	*
	*@param publisher = the event we're being notified
	*/
	void Notify(Library::EventPublisher* publisher) override;
private:
	sf::Vector2f GetLevelPostion(std::uint32_t level, Library::TetrominoRender& renderer);
	Library::WorldState* mCurrentWorldState;
	Library::World* mNextWorld;
	sf::RenderWindow* mWindow;
	std::uint32_t mSelectedLevel = 1;
	float mTextureScaleFactor = 0.18f;
	bool mHasEnteredScene = false;

};

