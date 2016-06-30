#include "pch.h"
#include "LevelSelectorManager.h"
#include "World.h"
#include "WorldState.h"
#include "EventPublisher.h"
#include "TetrominoRender.h"

using namespace Library;

LevelSelectorManager::LevelSelectorManager(Library::WorldState& state, Library::World& nextWorld, sf::RenderWindow& window) :
mCurrentWorldState(&state), mNextWorld(&nextWorld), mWindow(&window)
{
	Event<EventMessageAttributed>::Subscribe(this);
}


LevelSelectorManager::~LevelSelectorManager()
{
}

void LevelSelectorManager::RenderScreen(TetrominoRender& renderer)
{
	renderer.RenderOnScreen(*mWindow, TetrominoRender::TextureType::BackgroundLevelSelector, sf::Vector2f(0, 0));
	for (std::uint32_t i = 0; i < 8; i++)
	{
		TetrominoRender::TextureType textureType = TetrominoRender::TextureType::BackgroundLevelSelector;
		textureType = (TetrominoRender::TextureType)((std::uint32_t)textureType + i + 1);
		renderer.RenderOnScreen(*mWindow, textureType, GetLevelPostion((i + 1),renderer), sf::Vector2f(mTextureScaleFactor, mTextureScaleFactor));
	}
	renderer.RenderOnScreen(*mWindow, TetrominoRender::TextureType::SelectedBackground, GetLevelPostion(mSelectedLevel, renderer), sf::Vector2f(mTextureScaleFactor, mTextureScaleFactor));
}

sf::Vector2f LevelSelectorManager::GetLevelPostion(std::uint32_t level, TetrominoRender& renderer)
{
	float xPosition = 26.f;
	float yPosition = 40.f;
	float yPositionMultiplier = (float)level;
	if (level<5)
	{
		
		yPosition *= (level);
		yPositionMultiplier -= 1.f;

	}
	else
	{
		xPosition = 812.f;
		yPosition *= (level - 4);
		yPositionMultiplier -= 5.f;
	}
	//yPosition *= mTextureScaleFactor;
	yPosition += (mTextureScaleFactor * renderer.GetSpriteDimensions(TetrominoRender::TextureType::Level1Background).y * yPositionMultiplier);
	return sf::Vector2f(xPosition, yPosition);
}


void LevelSelectorManager::Notify(Library::EventPublisher* publisher)
{
	if (mCurrentWorldState->GetWorld()->Name() == "LevelSelector")
	{
		Event<EventMessageAttributed>* message = publisher->As<Event<EventMessageAttributed>>();
		if (message != nullptr)
		{
			if (message->Message().GetSubtype() == "KeyboardRelease")
			{
				std::string keyPressed = message->Message().Find("Key")->Get<std::string>();
				if (keyPressed.length() > 0)
				{
					if ((keyPressed == "Up") || (keyPressed == "W"))
					{
						mSelectedLevel--;
						if (mSelectedLevel<1)
						{
							mSelectedLevel = 8;
						}
						Library::CreateAudioEvent("MenuMenuOptionChange", mCurrentWorldState->GetWorld());
					}
					else if ((keyPressed == "Down") || (keyPressed == "S"))
					{
						mSelectedLevel++;
						if (mSelectedLevel > 8)
						{
							mSelectedLevel = 1;
						}
						Library::CreateAudioEvent("MenuMenuOptionChange", mCurrentWorldState->GetWorld());
					}
					else if ((keyPressed == "A") || (keyPressed == "Left"))
					{
						if (mSelectedLevel>4)
						{
							mSelectedLevel -= 4;
						}
						Library::CreateAudioEvent("MenuMenuOptionChange", mCurrentWorldState->GetWorld());
					}
					else if ((keyPressed == "D") || (keyPressed == "Right"))
					{
						if (mSelectedLevel < 5)
						{
							mSelectedLevel += 4;
						}
						Library::CreateAudioEvent("MenuMenuOptionChange", mCurrentWorldState->GetWorld());
					}
					else if ((keyPressed == "Return") || (keyPressed == "Space"))
					{
						if (mHasEnteredScene)
						{
							auto& levelDatum = mNextWorld->Append("LevelSelected");
							levelDatum.SetType(Datum::INTEGER);
							levelDatum = (int)mSelectedLevel;
							mCurrentWorldState->SetWorld(mNextWorld);
							mNextWorld->SetActive(true);
							mHasEnteredScene = false;
							mSelectedLevel = 1;
							ActionPlayMusic::DestroyMusic();
							Library::CreateAudioEvent("OnStart", mNextWorld);
						}
						else
						{
							mHasEnteredScene = true;
						}
					}
				}
			}
		}
	}
}