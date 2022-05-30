#include "msg.h"

extern uint32_t IPC_Msg_Send(intptr_t data);

int MSG_ToSlave(MSG_TypeDef *msg)
{
    IPC_Msg_Send((intptr_t)msg);
}

int MSG_ToMaster(MSG_TypeDef *msg)
{
    IPC_Msg_Send((intptr_t)msg);
}
