#include "Button.hpp"
#include <iostream>
#include "../../Game.hpp"
#include "../../Camera/Camera.hpp"
#include "../../Physics/Vector2D.hpp"

Button::Button(Properties* prop): GameObject(prop)
{
//	std::cout << "Button init!\n";
}

void Button::State_Update()
{
    //If mouse event happened

	SDL_EventType eventtype = Input::Get_Instance()->Get_Event_Type();
	if( eventtype == SDL_MOUSEMOTION || eventtype == SDL_MOUSEBUTTONDOWN || eventtype == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x = Input::Get_Instance()->Get_Mouse_Position().X;
		int y = Input::Get_Instance()->Get_Mouse_Position().Y;
//		std::cout << x << " " << y << "\n";

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < gTransform->X )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > gTransform->X + gWidth )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < gTransform->Y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > gTransform->Y + gHeight )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			gButton_State = MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( eventtype )
			{
				case SDL_MOUSEMOTION:
				gButton_State = MOUSE_OVER;
				break;
			
				case SDL_MOUSEBUTTONDOWN:
				gButton_State = MOUSE_DOWN;
				break;
				
				case SDL_MOUSEBUTTONUP:
				gButton_State = MOUSE_UP;
				break;
			}
		}
	}
}

void Button::Draw()
{
	Vector2D Cam = Camera::Get_Instance()->Get_Position();
    TextureManager::Get_Instance()->DrawFrame(gTexture_ID, gTransform->X + (int)Cam.X, gTransform->Y + (int)Cam.Y, gWidth, gHeight, 1, gButton_State);
}