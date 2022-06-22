//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : 3dColorBlue.fs
// Description : makes the object blue
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//
#version 460 core

out vec4 FinalColor;

//Output it as the color
void main()
{
	FinalColor = vec4(0.0f, 0.5f, 0.7f, 1.0f);
}