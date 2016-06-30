#include "pch.h"
#include "MainMenuManager.h"
#include "World.h"
#include "WorldState.h"
#include "EventPublisher.h"

using namespace Library;

MainMenuManager::MainMenuManager(WorldState& state, World& levelSelectorWorld, sf::RenderWindow& window) :
mCurrentWorldState(&state), mNextWorld(&levelSelectorWorld), mWindow(&window), mPlayButtonPosition(710, 550), mQuitButtonPosition(720, 600)
{
	Event<EventMessageAttributed>::Subscribe(this);
}

sf::Vector2f& MainMenuManager::GetPlayButtonPosition()
{
	return mPlayButtonPosition;
}
sf::Vector2f& MainMenuManager::GetQuitButtonPosition()
{
	return mQuitButtonPosition;
}

sf::Vector2f MainMenuManager::GetSelectedOptionArrowPosition()
{
	sf::Vector2f arrowPosition;

	arrowPosition = mSelectedOption == SelectedOption::Play ? GetPlayButtonPosition() : GetQuitButtonPosition();
	arrowPosition.x -= 40;
	arrowPosition.y += 15;

	return arrowPosition;
}

void MainMenuManager::Notify(Library::EventPublisher* publisher)
{
	if (!mHasBeenNotified)
	{
		if (mCurrentWorldState->GetWorld()->Name() == "MainMenu")
		{
			Event<EventMessageAttributed>* message = publisher->As<Event<EventMessageAttributed>>();
			if (message != nullptr)
			{
				if (message->Message().GetSubtype() == "Keyboard")
				{
					std::string keyPressed = message->Message().Find("Key")->Get<std::string>();
					if (keyPressed.length() > 0)
					{
						if ((keyPressed == "Up") || (keyPressed == "W"))
						{
							//mSelectedOption = mSelectedOption == SelectedOption::Quit ? SelectedOption::Play : SelectedOption::Play;

							if (mSelectedOption == SelectedOption::Quit)
							{
								mSelectedOption = SelectedOption::Play;

								Library::CreateAudioEvent("MenuMenuOptionChange", mCurrentWorldState->GetWorld());

								mHasBeenNotified = true;
							}
						}
						else if ((keyPressed == "Down") || (keyPressed == "S"))
						{
							if (mSelectedOption == SelectedOption::Play)
							{
								mSelectedOption = SelectedOption::Quit;
								Library::CreateAudioEvent("MenuMenuOptionChange", mCurrentWorldState->GetWorld());

								mHasBeenNotified = true;
							}
						}
						else if ((keyPressed == "Return") || (keyPressed == "Space"))
						{
							if (mSelectedOption == SelectedOption::Play)
							{
								mCurrentWorldState->SetWorld(mNextWorld);
							}
							else if (mSelectedOption == SelectedOption::Quit)
							{
								mWindow->close();
							}
							mHasBeenNotified = true;
						}
					}
				}
			}
		}
	}
}


MainMenuManager::SelectedOption MainMenuManager::GetSelectedOption()
{
	return mSelectedOption;
}

void MainMenuManager::ResetNotify()
{
	mHasBeenNotified = false;
}

MainMenuManager::~MainMenuManager()
{
	Event<EventMessageAttributed>::Unsubscribe(this);
}
