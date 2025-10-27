#include <iostream>
#include "../../header/GameLoop/Gameplay/Cell.h"

namespace Gameplay
{
	Cell::Cell(float width, float height, sf::Vector2i position)
	{
		Initialize(width, height, position);
	}
	void Cell::Initialize(float width, float height, sf::Vector2i position)
	{
		this->position = position;
		sf::Vector2f float_position(static_cast<float>(position.x),
			static_cast<float>(position.y)); //converted into float
		cell_button = new Buttons::Button(cell_texture_path, float_position, width * slice_count, height);
	}
	void Cell::Render(sf::RenderWindow& window)
	{
		if (cell_button) 
			cell_button->Render(window);
	}
}