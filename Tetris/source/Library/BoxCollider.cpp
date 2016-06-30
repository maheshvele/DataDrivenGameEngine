#include "pch.h"

namespace Library
{
	/**
	*Default constructor that initializes all data members
	*/
	BoxCollider::BoxCollider(float x, float y, float width, float height) :mX(x), mY(y), mWidth(width), mHeight(height), mOldX(mX), mOldY(mY), mOldWidth(mWidth), mOldHeight(mHeight)
	{
	}

	/**
	*Returns the X value associated with this box collider
	*
	*@return the X value associated with this box collider
	*/
	float BoxCollider::GetX()
	{
		return mX;
	}

	/**
	*Returns the Y value associated with this box collider
	*
	*@return the Y value associated with this box collider
	*/
	float BoxCollider::GetY()
	{
		return mY;
	}

	/**
	*Returns the Width value associated with this box collider
	*
	*@return the Width value associated with this box collider
	*/
	float BoxCollider::GetWidth()
	{
		return mWidth;
	}

	/**
	*Returns the Height value associated with this box collider
	*
	*@return the Height value associated with this box collider
	*/
	float BoxCollider::GetHeight()
	{
		return mHeight;
	}

	/**
	*Sets the x value associated with this box collider
	*
	*@param x = the x value to associated with this box collider
	*/
	void BoxCollider::SetX(float x)
	{
		mOldX = mX;
		mX = x;
	}

	/**
	*Sets the y value associated with this box collider
	*
	*@param y = the x value to associated with this box collider
	*/
	void BoxCollider::SetY(float y)
	{
		mOldY = mY;
		mY = y;
	}

	/**
	*Sets the width value associated with this box collider
	*
	*@param width = the width value to associated with this box collider
	*/
	void BoxCollider::SetWidth(float width)
	{
		mOldWidth = mWidth;
		mWidth = width;
	}

	/**
	*Sets the height value associated with this box collider
	*
	*@param height = the height value to associated with this box collider
	*/
	void BoxCollider::SetHeight(float height)
	{
		mOldHeight = mHeight;
		mHeight = height;
	}

	/**
	*Indicates if this box collider collided with the passed in collider on their left hand side
	*
	*@param other = the box we're checking our bounds against
	*@return true if we collider with the other box's left hand side, false otherwise
	*/
	bool BoxCollider::WasCollisionLeft(BoxCollider& other)
	{
		float otherLeft = other.GetX();
		float myOldRight = mOldX + mWidth;
		float myRight = mX + mWidth;
		return ((myOldRight <= otherLeft) && //was not colliding before
			(myRight > otherLeft)); //is collider now
	}

	/**
	*Indicates if this box collider collided with the passed in collider on their right hand side
	*
	*@param other = the box we're checking our bounds against
	*@return true if we collided with the other box's right hand side, false otherwise
	*/
	bool BoxCollider::WasCollisionRight(BoxCollider& other)
	{
		float otherRight = other.GetX() + other.GetWidth();
		return ((mOldX >= otherRight) && //was not colliding before
			(mX < otherRight)); //is collider now
	}

	/**
	*Indicates if this box collider collided with the passed in collider on their top side
	*
	*@param other = the box we're checking our bounds against
	*@return true if we collided with the other box's top side, false otherwise
	*/
	bool BoxCollider::WasCollisionTop(BoxCollider& other)
	{
		float otherTop = other.GetY();
		float myOldBottom = mOldY + mHeight;
		float myBottom = mY + mHeight;
		return ((myOldBottom <= otherTop) && //was not colliding before
			(myBottom > otherTop)); //is collider now
	}

	/**
	*Indicates if this box collider collided with the passed in collider on their bottom side
	*
	*@param other = the box we're checking our bounds against
	*@return true if we collided with the other box's bottom side, false otherwise
	*/
	bool BoxCollider::WasCollisionBottom(BoxCollider& other)
	{
		float otherBottom = other.GetY() + other.GetHeight();
		return ((mOldY >= otherBottom) && //was not colliding before
			(mY < otherBottom)); //is collider now
	}

	/**
	*Checks whether one box collider is colliding with another on any side
	*
	*@param a = the first box to check collisions with
	*@param b = the second box to check collisions with
	*@return true if there was a collision, false otherwise
	*/
	bool BoxCollider::CheckCollisions(BoxCollider& a, BoxCollider& b)
	{
		float aLeft = a.GetX();
		float aRight = a.GetX() + a.GetWidth();
		float aTop = a.GetY();
		float aBottom = a.GetY() + a.GetHeight();

		float bLeft = b.GetX();
		float bRight = b.GetX() + b.GetWidth();
		float bTop = b.GetY();
		float bBottom = b.GetY() + b.GetHeight();

		return ((aLeft< bRight) && (aRight > bLeft) && (aTop < bBottom) && (aBottom > bTop));
	}
}