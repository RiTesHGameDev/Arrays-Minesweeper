#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/UI/UIElements/Buttons/Button.h"
#include "../../header/Event/EventPollingManager.h"

namespace UI
{
	using namespace UIElements;
	using namespace Buttons;

	class MainMenuManager
	{
	private:
		sf::RenderWindow* game_window;
		sf::Texture background_texture;
		sf::Sprite background_sprite;

		Button* play_button;
		Button* quit_button;

		const std::string bacground_texture_path = "assets/textures/minersweeper_bg.png";
		const std::string play_button_texture_path = "assets/textures/play_button.png";
		const std::string quit_button_texture_path = "assets/textures/quit_button.png";

		const float button_width = 300.0f;
		const float button_height = 100.0f;
		const float play_button_y_position = 600.0f;
		const float quit_button_y_position = 750.0f;
		const float background_aplha = 85.0f;

		void Initialize();
		void Initialize_Background();
		void Initialize_Buttons();

		void Play_Button_Callback(MouseButtonType mouse_button_type);
		void Quit_Button_Callback(MouseButtonType mouse_button_type);
		void Register_Button_Callbacks();

		sf::Vector2f Get_Button_Position(float offset_x, float offset_y);

	public:
		MainMenuManager(sf::RenderWindow* window);
		~MainMenuManager() = default;

		void Update(Event::EventPollingManager event_manager);
		void Render();
	};
}