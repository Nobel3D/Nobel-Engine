#include "Color.h"

NE_NAMEUSING

Color::Color(float _R, float _G, float _B, float _A)
{
   if(_R <= 1.0f && _G <= 1.0f && _B <= 1.0f && _A <= 1.0f)
   {
   R = _R;
   G = _G;
   B = _B;
   A = _A;
   }
   else
   {
       NE_LOG("COLOR", "Illegal parameters on constructor")
       R = 0;
       G = 0;
       B = 0;
       A = 0;
   }
}


float Color::getRed() const { return R; }
float Color::getGreen() const { return G; }
float Color::getBlue() const { return B; }
float Color::getAlpha() const { return A; }

void Color::setRed(float _R) { if(_R <= 1.0f) R = _R; }
void Color::setGreen(float _G) { if(_G <= 1.0f) G = _G; }
void Color::setBlue(float _B) { if(_B <= 1.0f) B = _B; }
void Color::setAlpha(float _A) { if(_A <= 1.0f) A = _A; }
