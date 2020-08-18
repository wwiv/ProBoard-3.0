#include "proboard.hpp"
#include <string.h>

void
TpMessage::remove()
{
 if(next || prev) delReply();

 if(!msgBase()->deleteMsg(*this)) LOG("Error deleting message");
}
