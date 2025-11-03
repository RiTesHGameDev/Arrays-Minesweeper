#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/UI/UIElements/Buttons/Button.h"
#include "../../header/Event/EventPollingManager.h"


namespace Gameplay
{
	class GameplayManager;
}
namespace UI
{
	using namespace Gameplay;
	using namespace UIElements;
	using namespace Event;
	using namespace UIElements::Buttons;

	class GameplayUI
	{
	private:
		sf::Font bubbule_bobble_font;
		sf::Font ds_digib_font;

		sf::Text mine_text;
		sf::Text time_text;

		Buttons::Button* restart_button = nullptr;
		bool restart_button_clicked = false;

		const std::string restart_button_texture_path = "assets/textures/restart_button.png";
		const int font_size = 110;

		const float mine_text_top_offset = 65.0f;
		const float mine_text_left_offset = 660.0f;

		const float time_text_top_offset = 65.0f;
		const float time_text_left_offset = 1090.0f;

		const float restart_button_top_offset = 100.0f;
		const float restart_button_left_offset = 920.0f;

		const float button_width = 80.0f;
		const float button_height = 80.0f;
		const sf::Color text_color = sf::Color::Red;

		GameplayManager* gameplay_manager;

		void Initialize(GameplayManager* gameplay_manager);
		void Initialize_Texts();
		void Initialize_Button();
		void Load_Fonts();

		void Resigter_Button_Callback();
		void Restart_Button_Callback(MouseButtonType mouse_button_type);

	public:
		GameplayUI(GameplayManager* gameplay_manager);
		~GameplayUI() = default;

		void Update(int remaining_mines, int remaining_time,Event::EventPollingManager & event_manager,
			sf::RenderWindow& window);
		void Render(sf::RenderWindow& window);
	};
}