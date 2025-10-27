#pragma once
#include "../../header/UI/UIElements/Buttons/Button.h"
#include "../../header/Event/EventPollingManager.h"

using namespace UIElements;

namespace Gameplay
{
	class Cell
	{
	private:
		sf::Vector2i position;

		const int tile_size = 128;
		const int slice_count = 12;
		const std::string cell_texture_path = "assets/textures/cells.jpeg";

		Buttons::Button* cell_button;

		void Initialize(float width, float height, sf::Vector2i position);

	public:
		Cell(float width, float height, sf::Vector2i position);
		~Cell() = default;

		void Render(sf::RenderWindow& window);
	};
}