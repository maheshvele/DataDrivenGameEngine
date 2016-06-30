#include "pch.h"
#include "Factory.h"
#include "EventQueue.h"
#include "GameTime.h"
#include "InputManager.h"
#include "TetrominoRender.h"
#include "Board.h"
#include "Factory.h"
#include "XMLParseHelperTetris.h"
#include "XMLParseHelperExpression.h"
#include "XMLParseHelperUniverse.h"
#include "BlockEntity.h"
#include "MainMenuManager.h"
#include "SectorTetromino.h"
#include "TetrominoSpawner.h"
#include <crtdbg.h>
#include <chrono>
#include <thread>
#include <time.h>

//************************************FOR OUTPUTTING CONSOLE AS WELL
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
//#define CONSOLE_OUTPUT 1
//************************************FOR OUTPUTTING CONSOLE AS WELL

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
#include <string>
#include "LevelSelectorManager.h"
#include "ResultsScreenManager.h"
#include "AnimationManager.h"


LRESULT WINAPI WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

//using namespace Tetris;
using namespace Library;
using namespace std::chrono;

ConcreteFactory(Scope, BlockEntity);

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_crtBreakAlloc = 112;
#endif

#if defined(CONSOLE_OUTPUT)
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;
#endif

	//creates the window
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Tetris Battle Gaiden");
	TetrominoRender& renderer = *TetrominoRender::GetInstance();
	std::shared_ptr<BlockEntityFactory> blockfactory(new BlockEntityFactory());

	//main menu world
	World mainMenuWorld;
	EventQueue mainMenuEventQueue;
	mainMenuWorld.SetQueue(&mainMenuEventQueue);
	World animationWorld;
	EventQueue animationEventQueue;
	animationWorld.SetQueue(&animationEventQueue);
	World levelSelectorWorld;
	EventQueue levelSelectorEventQueue;

	World resultsScreenWorld;
	EventQueue resultsScreenEventQueue;
	resultsScreenWorld.SetQueue(&resultsScreenEventQueue);
	levelSelectorWorld.SetQueue(&levelSelectorEventQueue);
	resultsScreenWorld.SetName("ResultsScreen");
	
	//Input test
	World gameWorld;
	gameWorld.SetName("GameWorld");

	EventQueue q;
	WorldState state;

	SharedDataWorld sdw(&gameWorld);
	XmlParseMaster m(&sdw);
	XMLParseHelperUniverse p;
	XMLParseHelperTetris pht;
	XMLParseHelperTable pt;
	m.AddHelper(&p);
	m.AddHelper(&pht);
	m.AddHelper(&pt);

	m.ParseFromFile("Tetris.xml");

	GameTime time;
	gameWorld.SetQueue(&q);

	
	gameWorld.SetWorldState(state);
	mainMenuWorld.SetWorldState(state);
	animationWorld.SetWorldState(state);
	levelSelectorWorld.SetWorldState(state);
	
	state.SetWorld(&mainMenuWorld);
	
	mainMenuWorld.SetName("MainMenu");
	animationWorld.SetName("IntroAnimation");
	levelSelectorWorld.SetName("LevelSelector");
	MainMenuManager menuManager(state, animationWorld,window);
	AnimationManager animationManager(state, levelSelectorWorld, window);
	LevelSelectorManager levelManager(state, gameWorld, window);
	ResultsScreenManager resultsManager(state, mainMenuWorld, window);

	gameWorld.SetRenderWindow(window);
	mainMenuWorld.SetRenderWindow(window);

	EventMessageAttributed message;
	message.SetSubtype("lockPlayer1");

	EventMessageAttributed message2;
	message2.SetSubtype("lockPlayer2");

	Event<EventMessageAttributed> e(message);
	Event<EventMessageAttributed> e2(message2);


	e.Deliver();
	e2.Deliver();
	//ts->Notify(&e);

	auto& winnerDatum = gameWorld.Append("Winner");
	winnerDatum.SetType(Datum::INTEGER);
	winnerDatum = 0;

	auto& hideUIPlayer1 = gameWorld.Append("HideUIPlayer1");
	hideUIPlayer1.SetType(Datum::INTEGER);
	hideUIPlayer1 = 0;
	bool IsPlayer1HideUISelected = false;
	int Player1SelectedSprite = 0;
	int Player1UIHideSeconds = 0;
	seconds timeToHideUI(2);
	auto& hideUIPlayer2 = gameWorld.Append("HideUIPlayer2");
	hideUIPlayer2.SetType(Datum::INTEGER);
	hideUIPlayer2 = 0;
	bool IsPlayer2HideUISelected = false;
	int Player2SelectedSprite = 0;

	auto& resultsWinnerDatum = resultsScreenWorld.Append("Winner");
	resultsWinnerDatum.SetType(Datum::INTEGER);
	resultsWinnerDatum = 0;
	int Player2UIHideSeconds = 0;
	int HideUISeconds = 600;

	ActionPlayMusic::DestroyMusic();
	Library::CreateAudioEvent("OnStart", &mainMenuWorld);
	
	//run the program as long as the window is open
	while (window.isOpen())
	{
		milliseconds timeElapsedThisFrame = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		//check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			//close requested event: the window closes now
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//Clears the window of events that were drawn last frame.
		window.clear();

		//Updates the world that handles gameplay
		if (*(state.GetWorld()) == gameWorld)
		{
			auto texture = TetrominoRender::TextureType::Level1Background;
			Datum& selectedLevelDatum = gameWorld["LevelSelected"];
			int selectedLevel = selectedLevelDatum.Get<int>();
			texture = (TetrominoRender::TextureType)((int)texture+selectedLevel-1);

			renderer.RenderOnScreen(window, texture, sf::Vector2f(0, 0));
			renderer.RenderOnScreen(window, TetrominoRender::TextureType::BoardUI, sf::Vector2f(96, 32));
			renderer.RenderOnScreen(window, TetrominoRender::TextureType::BoardUI, sf::Vector2f(608, 32));
			renderer.RenderOnScreen(window, TetrominoRender::TextureType::NextThreeUI, sf::Vector2f(416, 32));

			time.SetTotalGameTime(time.TotalGameTime() + 1.0);
			gameWorld.Update(state);

			if (gameWorld["HideUIPlayer1"].Get<int>() != 0)
			{
				if (!IsPlayer1HideUISelected)
				{
					srand((unsigned int)std::time(NULL));
					Player1SelectedSprite = rand() % 4;
					Player1SelectedSprite += ((int)TetrominoRender::TextureType::HideUIPowerup1);
					IsPlayer1HideUISelected = true;

				}
				Player1UIHideSeconds++;

				if (Player1UIHideSeconds < HideUISeconds)
				{
					renderer.RenderOnScreen(window, (TetrominoRender::TextureType)Player1SelectedSprite, sf::Vector2f(96, 32), sf::Vector2f(1, 1), false, 1.f);
				}
			}

			if (gameWorld["HideUIPlayer2"].Get<int>() != 0)
			{
				if (!IsPlayer2HideUISelected)
				{
					srand((unsigned int)std::time(NULL));
					Player2SelectedSprite = rand() % 4;
					Player2SelectedSprite += ((int)TetrominoRender::TextureType::HideUIPowerup1);
					IsPlayer2HideUISelected = true;
				}
				Player2UIHideSeconds++;
				if (Player2UIHideSeconds < HideUISeconds)
				{
					renderer.RenderOnScreen(window, (TetrominoRender::TextureType)Player2SelectedSprite, sf::Vector2f(608, 32));
				}
			}

			if (gameWorld["Winner"].Get<int>() != 0)
			{
				gameWorld.SetActive(false);
				resultsScreenWorld["Winner"] = gameWorld["Winner"].Get<int>();
				state.SetWorld(&resultsScreenWorld);
				gameWorld["Winner"] = 0;
				gameWorld["HideUIPlayer1"] = 0;
				gameWorld["HideUIPlayer2"] = 0;
				Player1UIHideSeconds = 0;
				Player2UIHideSeconds = 0;
				IsPlayer1HideUISelected = false;
				IsPlayer2HideUISelected = false;
				//cleans up the board
				Board& board1 = *(gameWorld.Sectors()->Find("board1")->Get<Scope*>()->As<Board>());
				board1.InitBoard();
				Board& board2 = *(gameWorld.Sectors()->Find("board2")->Get<Scope*>()->As<Board>());
				board2.InitBoard();

				board1.ReinitializePowers();
				board2.ReinitializePowers();

				std::vector<SectorTetromino*> sectorsToDelete;
				//searches for any tetrominoes still left around in the world
				SectorTetromino* floatingTetromino;
				for (auto pair: (*gameWorld.Sectors()))
				{
					if (pair->second != nullptr)
					{
						Scope* scope = pair->second.Get<Scope*>();
						if (scope != nullptr)
						{
							floatingTetromino = scope->As<SectorTetromino>();
							if (floatingTetromino != nullptr)
							{
								sectorsToDelete.push_back(floatingTetromino);
							}
						}
					}
				}

				for (auto st : sectorsToDelete)
				{
					delete st;
				}
				
				//resets the spawner.
				Sector& spawnSector = *(gameWorld.Sectors()->Find("Backend")->Get<Scope*>()->As<Sector>());
				Entity& spawnContainer = *(spawnSector.Entities()->Find("SpawnContainer")->Get<Scope*>()->As<Entity>());
				TetrominoSpawner& spawner = *(spawnContainer.Actions()->Find("pool")->Get<Scope*>()->As<TetrominoSpawner>());

				spawner.GetQueue()->clear();
				spawner.Init();

				//Each requests a new block to handle.
				board1.RequestBlock();
				board2.RequestBlock();
			}

			//end the current frame
		}
		else if (*(state.GetWorld()) == mainMenuWorld)
		{
			//Renders the UI elements for the Main Menus
			renderer.RenderOnScreen(window, TetrominoRender::TextureType::BackgroundMainMenu, sf::Vector2f(0, 0));
			renderer.RenderTextOnScreen(window, "Play", menuManager.GetPlayButtonPosition(), 50, ((menuManager.GetSelectedOption() == MainMenuManager::SelectedOption::Play )? sf::Color::Red : sf::Color::White));
			renderer.RenderTextOnScreen(window, "Quit", menuManager.GetQuitButtonPosition(), 50, menuManager.GetSelectedOption() == MainMenuManager::SelectedOption::Quit ? sf::Color::Red : sf::Color::White);
			renderer.RenderOnScreen(window, TetrominoRender::TextureType::YellowArrow, menuManager.GetSelectedOptionArrowPosition());
			
			//Updates the main menu world
			time.SetTotalGameTime(time.TotalGameTime() + 1.0);
			mainMenuWorld.Update(state);
			menuManager.ResetNotify();
		}
		else if (*(state.GetWorld()) == animationWorld)
		{
			//Updates the main menu world
			time.SetElapsedGameTime(time.ElapsedGameTime() + 1.0);
			animationWorld.Update(state);
			animationManager.RenderScreen(renderer, time);
		}
		else if (*(state.GetWorld()) == levelSelectorWorld)
		{
			//Updates the level section World
			time.SetTotalGameTime(time.TotalGameTime() + 1.0);
			levelManager.RenderScreen(renderer);
			levelSelectorWorld.Update(state);
		}
		else if (*(state.GetWorld()) == resultsScreenWorld)
		{
			//Updates the result screens World
			time.SetTotalGameTime(time.TotalGameTime() + 1.0);
			resultsManager.RenderScreen(renderer);
			resultsScreenWorld.Update(state);
		}
		//end input test
		timeElapsedThisFrame = duration_cast<milliseconds>(system_clock::now().time_since_epoch()) - timeElapsedThisFrame;
		milliseconds timeToSleep(16);
		std::this_thread::sleep_for(timeToSleep-timeElapsedThisFrame);		
		window.display();
	}
	return 0;
}


LRESULT WINAPI WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(windowHandle, message, wParam, lParam);
}
