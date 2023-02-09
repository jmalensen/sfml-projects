#pragma once

struct ParamsMovement
{
	int topSpriteMoveRight;
	int topSpriteMoveLeft;
	int topSpriteMoveUp;
	int topSpriteMoveDown;
	ParamsMovement() : topSpriteMoveRight(0),
										 topSpriteMoveLeft(0),
										 topSpriteMoveUp(0),
										 topSpriteMoveDown(0) {}

	ParamsMovement(int topMoveRight, int topMoveLeft, int topMoveUp, int topMoveDown) : topSpriteMoveRight(topMoveRight),
																																											topSpriteMoveLeft(topMoveLeft),
																																											topSpriteMoveUp(topMoveUp),
																																											topSpriteMoveDown(topMoveDown) {}
};