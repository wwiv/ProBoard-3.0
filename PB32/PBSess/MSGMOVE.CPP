#include "proboard.hpp"

#include <stdlib.h>

void
TpMessage::move()
{
    TpMsgArea ma;
    int areanum = 0;

    io << "\n\n";

    LineCounter(0);

    mSelectMessageArea(form("* -N -%d /L" , msgArea->areaNum));

    io << '\n' << S_SELECT_MSG_AREA_TO_MOVE_MESSAGE_TO;

    Input(areanum,5);

    if(areanum < 1) return;

    if(!ma.read(areanum))
      {
       io << "\n\n" << S_UNKNOWN_MESSAGE_AREA << "\n\n" << S_PRESS_ENTER_TO_CONTINUE;
       return;
      }

    io << "\n\n" << S_MOVING_MESSAGE;

    TpMessage msg(this,areanum);

    createMsgTextFile("MSGTMP",FALSE);

    remove();

    msg.add();

    io << "\n\n";
}
