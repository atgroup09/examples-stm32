/* @page scale.c
 *       Scaling values
 *       2020, atgroup09@gmail.com
 */

#include "scale.h"


inline float ScaleA(float In, float KaIn, float KbIn)
{
    return ((In*KaIn)+KbIn);
}


float ScaleA_Ka(float Y1In, float Y2In, float In1, float In2)
{
    float In = (In2 - In1);
    return ((In > 0.0) ? ((Y2In - Y1In)/In) : (float)0.0);
}


float ScaleA_Kb(float Y1In, float Y2In, float In1, float In2)
{
    float In = (In2 - In1);
    return ((In > 0.0) ? (((Y1In*In2) - (Y2In*In1))/In) : (float)0.0);
}
