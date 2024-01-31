#include "Core/Public/CData.h"

const CLinearColor CLinearColor::White(1.f,1.f,1.f);
const CLinearColor CLinearColor::Gray(0.5f,0.5f,0.5f);
const CLinearColor CLinearColor::Black(0,0,0);
const CLinearColor CLinearColor::Transparent(0,0,0,0);
const CLinearColor CLinearColor::Red(1.f,0,0);
const CLinearColor CLinearColor::Green(0,1.f,0);
const CLinearColor CLinearColor::Blue(0,0,1.f);
const CLinearColor CLinearColor::Yellow(1.f,1.f,0);

const CColor CColor::White(255,255,255);
const CColor CColor::Black(0,0,0);
const CColor CColor::Transparent(0, 0, 0, 0);
const CColor CColor::Red(255,0,0);
const CColor CColor::Green(0,255,0);
const CColor CColor::Blue(0,0,255);
const CColor CColor::Yellow(255,255,0);
const CColor CColor::Cyan(0,255,255);
const CColor CColor::Magenta(255,0,255);
const CColor CColor::Orange(243, 156, 18);
const CColor CColor::Purple(169, 7, 228);
const CColor CColor::Turquoise(26, 188, 156);
const CColor CColor::Silver(189, 195, 199);
const CColor CColor::Emerald(46, 204, 113);

CLinearColor::CLinearColor()
:	R(0.0f),
    G(0.0f),
    B(0.0f),
    A(1.0f)
{}

CLinearColor::CLinearColor(const float32& InR, const float32& InG, const float32& InB)
:   R(InR),
    G(InG),
    B(InB),
    A(1.0f)
{}

CLinearColor::CLinearColor(const float32& InR, const float32& InG, const float32& InB, const float32& InA)
:   R(InR),
    G(InG),
    B(InB),
    A(InA)
{}

CLinearColor::CLinearColor(const CColor& InColor)
:   R(static_cast<float>(InColor.R) / 255.0f),
    G(static_cast<float>(InColor.G) / 255.0f),
    B(static_cast<float>(InColor.B) / 255.0f),
    A(static_cast<float>(InColor.A) / 255.0f)
{}

CColor::CColor()
:	R(0),
    G(0),
    B(0),
    A(1)
{}

CColor::CColor(const int& InR, const int& InG, const int& InB)
:   R(InR),
    G(InG),
    B(InB),
    A(1)
{}

CColor::CColor(const int& InR, const int& InG, const int& InB, const int& InA)
:   R(InR),
    G(InG),
    B(InB),
    A(InA)
{}

CColor::CColor(const CLinearColor& InLinearColor)
:	R(static_cast<int>(InLinearColor.R * 255.0f)),
    G(static_cast<int>(InLinearColor.G * 255.0f)),
    B(static_cast<int>(InLinearColor.B * 255.0f)),
    A(static_cast<int>(InLinearColor.A * 255.0f))
{
}

glm::detail::float32 CLinearColor::GetChannel(CColorChannel Channel)
{
    return *( &R + Channel * sizeof(glm::detail::float32) );
}

int CColor::GetChannel(CColorChannel Channel)
{
    return *( &R + Channel );
}
