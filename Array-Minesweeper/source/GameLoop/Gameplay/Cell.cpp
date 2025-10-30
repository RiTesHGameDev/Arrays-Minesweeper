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
		/*sf::Vector2f float_position(static_cast<float>(position.x),
			static_cast<float>(position.y));*/ //converted into float

		sf::Vector2f cell_screen_position = Get_Cell_Screen_Position(width,height);

		cell_button = new Buttons::Button(cell_texture_path, cell_screen_position, 
			width * slice_count, height);

	}
	void Cell::Render(sf::RenderWindow& window)
	{
		Set_Cell_Texture();
		if (cell_button) 
			cell_button->Render(window);
	}
	CellState Cell::Get_Cell_State()const
	{
		return current_cell_state;
	}
	CellType Cell::Get_Cell_Tyoe()const
	{
		return cell_type;
	}
	void Cell::Set_Cell_State(CellState state)
	{
		current_cell_state = state;
	}
	void Cell::Set_Cell_Type(CellType type)
	{
		cell_type = type;
	}
	sf::Vector2f Cell::Get_Cell_Screen_Position(float width,float height)const
	{
		float x_screen_position = cell_left_offset + position.x * width;
		float y_screen_position = cell_top_offset + position.y * height;

		return sf::Vector2f(x_screen_position, y_screen_position);
	}
	void Cell::Set_Cell_Texture()
	{
		int index = static_cast<int>(cell_type);

		switch (current_cell_state)
		{
		case CellState::OPEN:
			cell_button->Set_Texture_Rect(sf::IntRect(index * tile_size, 0, tile_size, tile_size));
			break;

		case CellState::HIDDEN:
			cell_button->Set_Texture_Rect(sf::IntRect(10 * tile_size, 0, tile_size, tile_size));
			break;

		case CellState::FLAGGED:
			cell_button->Set_Texture_Rect(sf::IntRect(11 * tile_size, 0, tile_size, tile_size));
			break;
		}
	}
}