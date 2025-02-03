/* @page type.c
 *       Structured and union types
 *       2020, atgroup09@gmail.com
 */

#include "type.h"


// SIZE =========================================================================

uint8_t Type_GetSz(const uint8_t TyIn)
{
    switch(TyIn)
    {
        case TYPE_BYTE:
            return (TYPE_BYTE_SZ);
        case TYPE_SINT:
            return (TYPE_SINT_SZ);
        case TYPE_WORD:
            return (TYPE_WORD_SZ);
        case TYPE_INT:
            return (TYPE_INT_SZ);
        case TYPE_DWORD:
            return (TYPE_DWORD_SZ);
        case TYPE_DINT:
            return (TYPE_DINT_SZ);
        case TYPE_FLOAT:
            return (TYPE_FLOAT_SZ);
        case TYPE_LWORD:
            return (TYPE_LWORD_SZ);
        case TYPE_LINT:
            return (TYPE_LINT_SZ);
        case TYPE_DOUBLE:
            return (TYPE_DOUBLE_SZ);
    }
    return ((uint8_t)0);
}


uint8_t Type_GetWSz(const uint8_t TyIn)
{
    switch(TyIn)
    {
        case TYPE_BYTE:
            return (TYPE_BYTE_WSZ);
        case TYPE_SINT:
            return (TYPE_SINT_WSZ);
        case TYPE_WORD:
            return (TYPE_WORD_WSZ);
        case TYPE_INT:
            return (TYPE_INT_WSZ);
        case TYPE_DWORD:
            return (TYPE_DWORD_WSZ);
        case TYPE_DINT:
            return (TYPE_DINT_WSZ);
        case TYPE_FLOAT:
            return (TYPE_FLOAT_WSZ);
        case TYPE_LWORD:
            return (TYPE_LWORD_WSZ);
        case TYPE_LINT:
            return (TYPE_LINT_WSZ);
        case TYPE_DOUBLE:
            return (TYPE_DOUBLE_WSZ);
    }
    return ((uint8_t)0);
}


// BYTE =========================================================================

uint8_t Type_InitBytes(uint8_t *BuffIn, const uint16_t BuffSzIn, const uint8_t InitValIn)
{
    uint16_t i=0;

    if(BuffIn)
    {
        for(i=0; i<BuffSzIn; i++)
        {
            *(BuffIn+i) = InitValIn;
        }
    }
    return (i);
}

uint8_t Type_CopyBytesExt(const uint8_t *FromIn, const uint8_t FromSzIn, uint8_t *ToIn, const uint8_t ToSzIn, const uint8_t ZeroedIn)
{
    uint8_t i=0;

    if(ToIn && ToSzIn)
    {
        for(i=0; i<ToSzIn; i++)
        {
            if(FromIn && i<FromSzIn)
            {
                *(ToIn+i) = *(FromIn+i);
            }
            else if(ZeroedIn)
            {
                *(ToIn+i) = 0;
            }
        }
    }
    return (i);
}


inline uint8_t Type_CopyBytes(const uint8_t *FromIn, const uint8_t FromSzIn, uint8_t *ToIn)
{
    return (Type_CopyBytesExt(FromIn, FromSzIn, ToIn, FromSzIn, 0));
}


uint8_t Type_CopyBytesRevExt(const uint8_t *FromIn, const uint8_t FromSzIn, uint8_t *ToIn, const uint8_t ToSzIn, const uint8_t ZeroedIn)
{
    uint8_t i=0;
    uint8_t idx;

    if(ToIn && ToSzIn)
    {
        for(i=0; i<ToSzIn; i++)
        {
        	idx = (FromSzIn-i-1);
            if(FromIn && i<FromSzIn)
            {
                *(ToIn+i) = *(FromIn+idx);
            }
            else if(ZeroedIn)
            {
                *(ToIn+i) = 0;
            }
        }
    }
    return (i);
}


inline uint8_t Type_CopyBytesRev(const uint8_t *FromIn, const uint8_t FromSzIn, uint8_t *ToIn)
{
	return (Type_CopyBytesRevExt(FromIn, FromSzIn, ToIn, FromSzIn, 0));
}


// WORD =========================================================================

uint16_t Type_InitWords(uint16_t *BuffIn, const uint16_t BuffSzIn, const uint16_t InitValIn)
{
    uint16_t i=0;

    if(BuffIn)
    {
        for(i=0; i<BuffSzIn; i++)
        {
            *(BuffIn+i) = InitValIn;
        }
    }
    return (i);
}


uint16_t Type_ReplaceWordBytes(const uint16_t WoIn)
{
    WORD_ubt Res;
    Res.bytes[0] = BYTE1(WoIn);
    Res.bytes[1] = BYTE0(WoIn);
    return (Res.data);
}


uint16_t Type_OrderWordBytes(const uint16_t WoIn, const uint8_t FromOrdIn, const uint8_t ToOrdIn)
{
    switch(FromOrdIn)
    {
        case TYPE_BYTE_ORDER_3210:
        case TYPE_BYTE_ORDER_1032:
            if(ToOrdIn == TYPE_BYTE_ORDER_0123 || ToOrdIn == TYPE_BYTE_ORDER_2301) return Type_ReplaceWordBytes(WoIn);
            break;
        case TYPE_BYTE_ORDER_0123:
        case TYPE_BYTE_ORDER_2301:
            if(ToOrdIn == TYPE_BYTE_ORDER_3210 || ToOrdIn == TYPE_BYTE_ORDER_1032) return Type_ReplaceWordBytes(WoIn);
            break;
    }
    return (WoIn);
}


void Type_ReplaceWords(uint16_t *Wo1In, uint16_t *Wo2In)
{
    if(Wo1In && Wo2In)
    {
        uint16_t Buff = *Wo1In;
        *Wo1In = *Wo2In;
        *Wo2In = Buff;
    }
}


uint8_t Type_CopyWordsExt(const uint16_t *FromIn, const uint16_t FromSzIn, const uint8_t FromOrdIn, uint16_t *ToIn, const uint16_t ToSzIn, const uint8_t ToOrdIn, const uint8_t ZeroedIn, uint8_t *ChangeMonIn)
{
    uint16_t i=0;
    uint8_t  c=0, fChange = 0;

    if(ToIn && ToSzIn)
    {
        for(i=0; i<ToSzIn; i++)
        {
            if(FromIn && i<FromSzIn)
            {
                if(!fChange)
                {
                    if(*(ToIn+i) != *(FromIn+i)) fChange++;
                }

                if(!c)
                {
                    *(ToIn+i) = Type_OrderWordBytes(*(FromIn+i), FromOrdIn, ToOrdIn);

                    switch(FromOrdIn)
                    {
                        case TYPE_BYTE_ORDER_3210:
                        case TYPE_BYTE_ORDER_2301:
                            if(ToOrdIn == TYPE_BYTE_ORDER_0123 || ToOrdIn == TYPE_BYTE_ORDER_1032) c++;
                            break;
                        case TYPE_BYTE_ORDER_0123:
                        case TYPE_BYTE_ORDER_1032:
                            if(ToOrdIn == TYPE_BYTE_ORDER_3210 || ToOrdIn == TYPE_BYTE_ORDER_2301) c++;
                            break;
                    }
                }
                else
                {
                    //replace pair words
                    *(ToIn+i)   = *(ToIn+i-1);
                    *(ToIn+i-1) = Type_OrderWordBytes(*(FromIn+i), FromOrdIn, ToOrdIn);
                    c=0;
                }
            }
            else if(ZeroedIn)
            {
                *(ToIn+i) = 0;
            }
            else
            {
                break;
            }
        }
    }

    if(ChangeMonIn) *ChangeMonIn = fChange;

    return (i);
}


inline uint8_t Type_CopyWords(const uint16_t *FromIn, const uint16_t FromSzIn, uint16_t *ToIn)
{
    return (Type_CopyWordsExt(FromIn, FromSzIn, TYPE_BYTE_ORDER_NONE, ToIn, FromSzIn, TYPE_BYTE_ORDER_NONE, 0, 0));
}
