//---------------------------------------------------------------------------

#ifndef logicH
#define logicH
#include <vcl.h>
#include <list>


#define PBMP Graphics::TBitmap *
#define BMP  Graphics::TBitmap

#define KEY_UP          0x0100
#define KEY_DOWN        0x0200

#define KB_STATE_WINAPI_FORMAT          0
#define KB_STATE_BOOLEAN_FORMAT         1

typedef unsigned int uint;
typedef unsigned char byte;
template <class T> const T& min ( const T& a, const T& b ) {
  return (a>b)?b:a;
}
template <class T> const T& max ( const T& a, const T& b ) {
  return (a>b)?a:b;
}

struct TDoubleRect
{
        double left, top, right, bottom;
        double Width(){return right-left;}
        double Height(){return bottom-top;}
};
struct kbState
{
        kbState(){memset(state,0,256);}
        static kbState get(int format);
        byte state[256];
        byte operator[](int index) {return state[index];}
};
bool valueInRange(int value, int min, int max);
TRect convertRect(TRect r, bool toRightBottomFmt=false);
bool rectCollision(TRect A, TRect B);


class KeyListener
{
public:
        KeyListener(){;}
        ~KeyListener(){;}
        virtual void keyUpdate(uint spKey)=0;
};

class KeyUpdateProducer
{
public:
        KeyUpdateProducer();
        ~KeyUpdateProducer();
        void update();
        void addListener(KeyListener * l);
        void removeListener(KeyListener * l);
        void clear();
private:
        std::list<KeyListener*> listeners;
        kbState prevResult;

};



//---------------------------------------------------------------------------
#endif
