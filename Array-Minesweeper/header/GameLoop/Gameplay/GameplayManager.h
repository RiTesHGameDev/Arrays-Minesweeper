#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/Event/EventPollingManager.h"
#include "SFML/Graphics.hpp"

namespace Gameplay
{
	enum class GameResult
	{
		NONE,
		WON,
		LOST
	};
	class GameplayManager
	{
	private:
		const float background_aplha = 85.0f;

		sf::Texture background_texture;
		sf::Sprite background_sprite;
		std::string background_texture_path = "assets/textures/minesweeper_bg.png";
		Board* board;

		GameResult game_result;

		const float max_level_duration = 150.0f;
		const float game_over_time = 11.0f;
		float remaining_time;

		void Initialize();
		void Initialize_Variables();
		void Initialize_Background_Image();

		bool Has_Game_Ended();

		void Update_Remaining_Time();
		void Process_Time_Over();
		void Handle_Gameplay(Event::EventPollingManager& event_manager, sf::RenderWindow& window);

	public:
		GameplayManager();
		~GameplayManager();
		void Set_Game_Result(GameResult gameResult);
		void Render(sf::RenderWindow& window);
		void Update(Event::EventPollingManager& event_manager, const sf::RenderWindow& window);
	};
}