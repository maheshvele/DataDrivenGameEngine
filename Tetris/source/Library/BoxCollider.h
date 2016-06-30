#pragma once

namespace Library
{
	class BoxCollider
	{

	public:

		/**
		*Default constructor that initializes all data members 
		*/
		BoxCollider(float x, float y, float width, float height);

		/**
		*Default destructor
		*/
		~BoxCollider() = default;

		/**
		*Returns the X value associated with this box collider
		*
		*@return the X value associated with this box collider
		*/
		float GetX();

		/**
		*Returns the Y value associated with this box collider
		*
		*@return the Y value associated with this box collider
		*/
		float GetY();

		/**
		*Returns the Width value associated with this box collider
		*
		*@return the Width value associated with this box collider
		*/
		float GetWidth();

		/**
		*Returns the Height value associated with this box collider
		*
		*@return the Height value associated with this box collider
		*/
		float GetHeight();

		/**
		*Sets the x value associated with this box collider
		*
		*@param x = the x value to associated with this box collider
		*/
		void SetX(float x);

		/**
		*Sets the y value associated with this box collider
		*
		*@param y = the x value to associated with this box collider
		*/
		void SetY(float y);

		/**
		*Sets the width value associated with this box collider
		*
		*@param width = the width value to associated with this box collider
		*/
		void SetWidth(float width);

		/**
		*Sets the height value associated with this box collider
		*
		*@param height = the height value to associated with this box collider
		*/
		void SetHeight(float height);
		
		/**
		*Indicates if this box collider collided with the passed in collider on their left hand side
		*
		*@param other = the box we're checking our bounds against
		*@return true if we collider with the other box's left hand side, false otherwise
		*/
		bool WasCollisionLeft(BoxCollider& other);

		/**
		*Indicates if this box collider collided with the passed in collider on their right hand side
		*
		*@param other = the box we're checking our bounds against
		*@return true if we collided with the other box's right hand side, false otherwise
		*/
		bool WasCollisionRight(BoxCollider& other);

		/**
		*Indicates if this box collider collided with the passed in collider on their top side
		*
		*@param other = the box we're checking our bounds against
		*@return true if we collided with the other box's top side, false otherwise
		*/
		bool WasCollisionTop(BoxCollider& other);

		/**
		*Indicates if this box collider collided with the passed in collider on their bottom side
		*
		*@param other = the box we're checking our bounds against
		*@return true if we collided with the other box's bottom side, false otherwise
		*/
		bool WasCollisionBottom(BoxCollider& other);

		/**
		*Checks whether one box collider is colliding with another on any side
		*
		*@param a = the first box to check collisions with
		*@param b = the second box to check collisions with
		*@return true if there was a collision, false otherwise
		*/
		static bool CheckCollisions(BoxCollider& a, BoxCollider& b);

	private:
		float mX;
		float mY;
		float mWidth;
		float mHeight;

		float mOldX;
		float mOldY;
		float mOldWidth;
		float mOldHeight;
	};
}