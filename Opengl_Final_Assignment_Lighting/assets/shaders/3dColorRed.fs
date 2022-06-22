//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : 3dColorRed.fs
// Description : Makes the object red
//
// Author : James Koster-Smtih
// Mail : james.kostersmith@mediadesignschool.com
//
#version 460 core

out vec4 FinalColor;

//output at the color, doesn't need to take anything in'
void main()
{
	FinalColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}