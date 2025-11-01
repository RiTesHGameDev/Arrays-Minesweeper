#include <iostream>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/GameLoop/Gameplay/Board.h"

namespace Gameplay
{
	Cell::Cell(float width, float height, sf::Vector2i position,Board* board)
	{
		Initialize(width, height, position,board);
	}
	void Cell::Initialize(float width, float height, sf::Vector2i position,Board* board)
	{
		this->position = position;
		this->board = board;

		sf::Vector2f cell_screen_position = Get_Cell_Screen_Position(width,height);

		cell_button = new Button(cell_texture_path, cell_screen_position, 
			width * slice_count, height);
		current_cell_state = CellState::HIDDEN;

		Register_Cell_Button_Call_Back();

	}
	void Cell::Register_Cell_Button_Call_Back()
	{
		//Call Cell's own call back logix
		cell_button->Register_Callback_Function([this](MouseButtonType button_type)
			{Cell_Button_Call_Back(button_type);});
	}
	void Cell::Cell_Button_Call_Back(MouseButtonType button_type)
	{
		board->On_Cell_Button_Clicked(Get_Cell_Position(), button_type);
	}
	sf::Vector2i Cell::Get_Cell_Position()
	{
		return position;
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
	CellType Cell::Get_Cell_Type()const
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
	void Cell::Update(Event::EventPollingManager& event_manager,const sf::RenderWindow& window)
	{
		if(cell_button)
		cell_button->Handle_Button_Interactions(event_manager, window);
	}
	bool Cell::Can_Open_Call()const
	{
		return current_cell_state == CellState::HIDDEN;
	}
	void Cell::Open()
	{
		Set_Cell_State(CellState::OPEN);
	}
	void Cell::Toggle_Flag()
	{
		if (current_cell_state == CellState::HIDDEN)
		{
			Set_Cell_State(CellState::FLAGGED);
		}
		else if (current_cell_state == CellState::FLAGGED)
		{
			Set_Cell_State(CellState::HIDDEN);
		}
	}
}