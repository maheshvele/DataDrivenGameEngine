#pragma once
#include "EventSubscriber.h"

class Library::EventPublisher;
class Library::WorldState;
class Library::World;
class MainMenuManager :	public Library::EventSubscriber
{
public:
	enum class SelectedOption
	{
		Invalid = -1,
		Play,
		Quit,
		Max
	};
	MainMenuManager(Library::WorldState& state, Library::World& levelSelectorWorld, sf::RenderWindow& window);
	~MainMenuManager();
	void ResetNotify();
	SelectedOption GetSelectedOption();
	sf::Vector2f& GetPlayButtonPosition();
	sf::Vector2f& GetQuitButtonPosition();
	sf::Vector2f GetSelectedOptionArrowPosition();

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
	SelectedOption mSelectedOption = SelectedOption::Play;
	bool mHasBeenNotified = false;
	sf::Vector2f mPlayButtonPosition;
	sf::Vector2f mQuitButtonPosition;
};
