#include <iostream>
#include"../../header/GameLoop/Gameplay/GameplayManager.h"
#include"../../header/Time/TimeManager.h"

namespace Gameplay
{
	GameplayManager::GameplayManager()
	{
		Initialize();
	}
	GameplayManager::~GameplayManager()
	{

	}
	void GameplayManager::Initialize()
	{
		Initialize_Variables();
		Initialize_Background_Image();
	}
	void GameplayManager::Initialize_Variables()
	{
		board = new Board(this);
		remaining_time = max_level_duration;
	}
	void GameplayManager::Initialize_Background_Image()
	{
		if (!background_texture.loadFromFile(background_texture_path))
		{
			std::cerr << "Failed to load background texture!" << std::endl;
		}
		background_sprite.setTexture(background_texture);
		background_sprite.setColor(sf::Color(255, 255, 255, background_aplha));
	}
	void GameplayManager::Render(sf::RenderWindow& window)
	{
		window.draw(background_sprite);
		board->Render(window);
	}
	void GameplayManager::Update(Event::EventPollingManager& event_manager,
		 sf::RenderWindow& window)
	{
		if (!Has_Game_Ended())
		{
			Handle_Gameplay(event_manager,window);
		}
		else if (board->Get_Board_State() != BoardState::COMPLETED)
		{
			Process_Game_Result();
		}
	}
	void GameplayManager::Handle_Gameplay(Event::EventPollingManager& event_manager, sf::RenderWindow& window)
	{
		Update_Remaining_Time();
		board->Update(event_manager, window);
		Check_Game_Win();
	}
	void GameplayManager::Update_Remaining_Time()
	{
		remaining_time -= Time::TimeManager::getDeltaTime();
		Process_Time_Over();
	}
	void GameplayManager::Process_Time_Over()
	{
		if (remaining_time <= 0)
		{
			remaining_time = 0;
			game_result = GameResult::LOST;
		}
	}
	void GameplayManager::Check_Game_Win()
	{
		if (board->Are_All_Cells_Open())
		{
			game_result = GameResult::WON;
		}
	}
	void GameplayManager::Process_Game_Result()
	{
		switch (game_result)
		{
		case GameResult::WON:
			Game_Won();
			break;
		case GameResult::LOST:
			Game_Lost();
			break;
		default:
			break;
		}
	}
	void GameplayManager::Game_Won()
	{
		Sound::SoundManager::PlaySound(Sound::SoundType::GAME_WON);
		board->Flag_All_Mines();
		board->Set_Board_State(BoardState::COMPLETED);
	}
	void GameplayManager::Game_Lost()
	{
		Sound::SoundManager::PlaySound(Sound::SoundType::EXPLOSION);
		board->Set_Board_State(BoardState::COMPLETED);
		board->Reveal_All_Mines();
	}
	void GameplayManager::Set_Game_Result(GameResult gameResult)
	{
		this->game_result = gameResult;
	}
	bool GameplayManager::Has_Game_Ended()
	{
		return game_result != GameResult::NONE;
	}
}