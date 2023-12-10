#if !defined(__MSDP_CLIENT_H__)
#define __MSDP_CLIENT_H__

#include "msdp.hpp"
#include "multicast.hpp"
#include <vector>

namespace cmsdp {

class CMsdpClient {
  private:
    CMulticastChannel channel;
    std::vector<MsdpHandler> handlerMap;

    volatile int state{0};
    volatile bool interrupt;

  public:
    CMsdpClient(CMulticastChannel &&_Channel);
    CMsdpClient(CMulticastChannel &_Channel);
    CMsdpClient(CMulticastChannel *_Channel);
    ~CMsdpClient();

    int setup();
    int close();
    void start();

    int sendPacket(const msdp::packet::MSDPPacket pkt, const size_t length);
    msdp::packet::MSDPPacket receivePacket();

    void addHandler(MsdpHandler handler);
  private:
    void handleINIPacket(msdp::packet::MSDPPacket pkt);
    void handleLVEPacket(msdp::packet::MSDPPacket pkt);
    void handleQRYPacket(msdp::packet::MSDPPacket pkt);
    void handleUndefinedPacket(msdp::packet::MSDPPacket pkt);

};

typedef void (*MsdpHandler)(CMsdpClient *, msdp::packet::MSDPPacket);

}

#endif // __MSDP_CLIENT_H__
