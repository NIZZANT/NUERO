#include <core/abstract_channel.h>
#include <core/channel_factory.h>
#include <core/abstract_port.h>
#include <core/utils.h>
#include <channel/socket/socket_port.h>

using namespace message_infrastructure;

int main(int argc, char *argv[]) {
    ChannelFactory &channel_factory = GetChannelFactory();

    AbstractChannelPtr ch2 = channel_factory.GetTempChannel("./c2py");
    AbstractSendPortPtr sd = ch2->GetSendPort();
    sd->Start();

    AbstractChannelPtr ch = channel_factory.GetTempChannel("./py2c");
    AbstractRecvPortPtr rc = ch->GetRecvPort();

    // order matters
    rc->Start();

    for(uint _ = 0; _ < 10; ++_) {
        std::cout << "forwarding\n";
        MetaDataPtr recvd = rc->Recv();
        std::cout << "received from py, total size: " << recvd->total_size << "\n";
        sd->Send(recvd);
    }

    rc->Join();
    sd->Join();

    return 0;
}