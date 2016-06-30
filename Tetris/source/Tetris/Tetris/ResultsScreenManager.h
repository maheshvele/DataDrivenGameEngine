#pragma once
#include "EventSubscriber.h"

class Library::EventPublisher;
class Library::WorldState;
class Library::World;
class Library::TetrominoRender;
class ResultsScreenManager : public Library::EventSubscriber
{
public:
	ResultsScreenManager(Library::WorldState& state, Library::World& nextWorld, sf::RenderWindow& window);
	~ResultsScreenManager();
	void RenderScreen(Library::TetrominoRender& renderer);
	/**
	*Called when an event is fired, we verify its subtype and react to it.
	*
	*@param publisher = the event we're being notified
	*/
	void Notify(Library::EventPublisher* publisher) override;

private:
	Library::WorldState* mCurrentWorldState;
	Library::World* mNextWorld;
	sf::RenderWindow* mWindow;
	bool mHasScreenLoaded = false;
};

