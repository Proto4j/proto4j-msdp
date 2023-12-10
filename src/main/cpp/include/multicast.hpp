#if !defined(__MULTICAST_H__)
#define __MULTICAST_H__

#if defined(_WIN32)

  #pragma comment(lib, "ws2_32.lib")

  #include <Winsock2.h> // before Windows.h, else Winsock 1 conflict
  #include <Ws2tcpip.h> // needed for ip_mreq definition for multicast
  #include <Windows.h>

#else

  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>

#endif // _WIN32

#if defined(_WIN32)

  #define DefWSAStartup(onError) \
    WSAData data; \
    if (WSAStartup(0x0101, &data)) { \
      onError \
      exit(0); \
    } \

  #define DefWSAClean \
    WSACleanup();

#else

#define DefWSAStartup
#define DefWSAClean

#endif // __MULTICAST_H__


namespace cmsdp
{

typedef struct sockaddr_in mc_sockaddr_in;
  
class CMulticastChannel {
  private:
    mc_sockaddr_in address;
    SOCKET socket;

  public:
    CMulticastChannel(mc_sockaddr_in address);
    ~CMulticastChannel();

    int joinGroup();
    int receive(char *buffer);
    int send(const char *buffer);
};

} // namespace cmsdp
#endif