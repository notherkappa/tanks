//---------------------------------------------------------------------------


#pragma hdrstop

#include "logic.h"
bool valueInRange(int value, int min, int max)
{
        return (value >= min) && (value <= max);
}
TRect convertRect(TRect r, bool toRightBottomFmt)
{
        TRect res;
        res.left=r.left;
        res.top=r.top;
        if (toRightBottomFmt)
        {
                r.left = -r.left;
                r.top = -r.top;
        }
        res.right = r.right-r.left;
        res.bottom = r.bottom-r.top;
        return res;
}

bool rectCollision(TRect A, TRect B)
{
    bool xOverlap = valueInRange(A.left, B.left, B.left + B.right) ||
                    valueInRange(B.left, A.left, A.left + A.right);

    bool yOverlap = valueInRange(A.top, B.top, B.top + B.bottom) ||
                    valueInRange(B.top, A.top, A.top + A.bottom);

    return xOverlap && yOverlap;
}
//---------------------------------------------------------------------------
KeyUpdateProducer::KeyUpdateProducer()
{
}
KeyUpdateProducer::~KeyUpdateProducer()
{
        ;
}
void KeyUpdateProducer::addListener(KeyListener * l)
{
        listeners.push_back(l);
}
void KeyUpdateProducer::removeListener(KeyListener * l)
{
        listeners.remove(l);
}
void KeyUpdateProducer::clear()
{
        listeners.clear();
}
void KeyUpdateProducer::update()
{
        kbState newResult = kbState::get(KB_STATE_BOOLEAN_FORMAT);
        for (int i=0; i<256; i++)
        {
                if (newResult[i]!=prevResult[i])
                {
                        uint vk = ((newResult[i]==1) ? KEY_DOWN : KEY_UP)+ i;
                        for (std::list<KeyListener*>::iterator i = listeners.begin(); i!=listeners.end(); i++)
                                (*i)->keyUpdate(vk);
                }
        }
        prevResult = newResult;
}

kbState kbState::get(int format)
{
        kbState out;
        GetKeyboardState(out.state);
        if (format == KB_STATE_WINAPI_FORMAT);
        else if (format == KB_STATE_BOOLEAN_FORMAT)
        {
                for (int i=0; i<256; i++)
                        out.state[i] = (out.state[i]&128)?1:0;
                return out;
        }
        return out;
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
