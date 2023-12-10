#include "../include/multicast.hpp"

// CMulticastChannel
cmsdp::CMulticastChannel::CMulticastChannel(cmsdp::mc_sockaddr_in addr)
{
  this->address = addr;
}

cmsdp::CMulticastChannel::~CMulticastChannel() 
{
  closesocket(this->socket);
}

int cmsdp::CMulticastChannel::joinGroup()
{
  struct sockaddr_in bind_Address;

  bind_Address.sin_family = AF_INET;
  bind_Address.sin_addr.s_addr = htonl(INADDR_ANY);
  bind_Address.sin_port = this->address.sin_port;

  bind(this->socket, (struct sockaddr *)&bind_Address, sizeof(bind_Address));

  struct ip_mreq opt;
  opt.imr_multiaddr.s_addr = this->address.sin_addr.s_addr;
  opt.imr_interface.s_addr = htonl(INADDR_ANY);
  setsockopt(this->socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&opt, sizeof(opt));
}

int cmsdp::CMulticastChannel::receive(char *buffer)
{
  int count;
  socklen_t len;

  len = sizeof(this->address);
  count = recvfrom(this->socket, buffer, 1024, 0, (struct sockaddr *)&this->address, &len);
  if (count == SOCKET_ERROR) {
    return 0;
  }

  return count;
}

int cmsdp::CMulticastChannel::send(const char *buffer)
{
  int count;
  socklen_t len;

  len = sizeof(this->address);
  count = sendto(this->socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&this->address, len);
  if (count == EWOULDBLOCK) {
    return 0;
  }

  return count;
}