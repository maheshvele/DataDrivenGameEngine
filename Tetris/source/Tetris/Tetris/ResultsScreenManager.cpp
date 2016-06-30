#include "pch.h"
#include "ResultsScreenManager.h"
#include "World.h"
#include "WorldState.h"
#include "EventPublisher.h"
#include <string>

using namespace Library;

ResultsScreenManager::ResultsScreenManager(WorldState& state, World& nextWorld, sf::RenderWindow& window):
mCurrentWorldState(&state), mNextWorld(&nextWorld), mWindow(&window)
{
	Event<EventMessageAttributed>::Subscribe(this);
}

void ResultsScreenManager::RenderScreen(Library::TetrominoRender& renderer)
{
	renderer.RenderOnScreen(*mWindow, TetrominoRender::TextureType::WinScreenBackground, sf::Vector2f(0, 50));
	World* currentWorld = mCurrentWorldState->GetWorld();
	int winner = (*currentWorld)["Winner"].Get<int>();

	//Paul won
	if (winner == 1)
	{
		renderer.RenderOnScreen(*mWindow, TetrominoRender::TextureType::Player1Win, sf::Vector2f(170,300),sf::Vector2f(3,3));
		renderer.RenderOnScreen(*mWindow, TetrominoRender::TextureType::Player2Lose, sf::Vector2f(650, 300), sf::Vector2f(3, 3));
	}//Tom won
	else
	{
		renderer.RenderOnScreen(*mWindow, TetrominoRender::TextureType::Player1Lose, sf::Vector2f(170, 300), sf::Vector2f(3, 3));
		renderer.RenderOnScreen(*mWindow, TetrominoRender::TextureType::Player2Win, sf::Vector2f(650, 300), sf::Vector2f(3, 3));
	}

	std::string message = "Player " + std::to_string(winner) + " wins!";
	renderer.RenderTextOnScreen(*mWindow, message.c_str(), sf::Vector2f(170, 200), 70, sf::Color::Red);
	renderer.RenderTextOnScreen(*mWindow, "Press Enter to return to main menu...", sf::Vector2f(200, 670), 20, sf::Color::White);
}

ResultsScreenManager::~ResultsScreenManager()
{
}

void ResultsScreenManager::Notify(Library::EventPublisher* publisher)
{
	if (mCurrentWorldState->GetWorld()->Name() == "ResultsScreen")
	{
		Event<EventMessageAttributed>* message = publisher->As<Event<EventMessageAttributed>>();
		if (message != nullptr)
		{
			if (message->Message().GetSubtype() == "KeyboardRelease")
			{
				std::string keyPressed = message->Message().Find("Key")->Get<std::string>();
				if (keyPressed.length() > 0)
				{
					if ((keyPressed == "Return") || (keyPressed == "Space"))
					{

						mCurrentWorldState->SetWorld(mNextWorld);
						World* currentWorld = mCurrentWorldState->GetWorld();
						(*currentWorld)["Winner"] = 0;
						mHasScreenLoaded = false;
						ActionPlayMusic::DestroyMusic();
						Library::CreateAudioEvent("OnStart", mNextWorld);

					}
				}
			}
		}
	}
}
