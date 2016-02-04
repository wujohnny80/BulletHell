//====================================================================================================
// Filename:	UIScore.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "UIScore.h"
#include "../Core/Application.h"
#include "../Core/Timer.h"

#include <sstream>
#include <string>

//====================================================================================================
// Class Definitions
//====================================================================================================

UIScore::UIScore()
	: mpText(nullptr)
	, mScore(0)
{
}

UIScore::~UIScore()
{
}

void UIScore::Initialize()
{
	mpText = new Text();
	mpText = AddComponent<Text>();

	mpText->Initialize("Transformers.ttf");
	mpText->SetCentered(false);

	SetText();

	// Set text properties
	mpText->SetColor(255, 255, 255, 255);
	mpText->SetSize(50);
	//mpText->Bold(true);
	
	layer = 3;
	transform->position = Vector2(20.0f, 10.0f);
}

void UIScore::Update()
{
	SetText();
	UpdateComponents();
}

void UIScore::HandleCollision(GameObject* other)
{
}

void UIScore::Deactivate()
{
}

void UIScore::SetText()
{
	// Set text string
	std::string finalStr = "Score: ";
	std::string intStr;
	std::stringstream out;
	out << mScore;
	intStr = out.str();
	finalStr += intStr;
	mpText->SetText(finalStr);
}