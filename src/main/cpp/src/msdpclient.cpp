#include "../include/msdpclient.hpp"

cmsdp::CMsdpClient::CMsdpClient(cmsdp::CMulticastChannel &&_Channel)
  : channel{_Channel} 
{
  this->state = 1;
}


int cmsdp::CMsdpClient::setup()
{
  if (this->state != 1) {
    return (int) msdp::error_t::ALREADY_INITIALIZED;
  }

#ifdef _WIN32
  DefWSAStartup()
#endif
  this->state = 2;
  return this->channel.joinGroup();
}

void cmsdp::CMsdpClient::start()
{
  if (interrupt) {
    return;
  }

  unsigned int counter = 0;
  do {
    msdp::packet::MSDPPacket next = this->receivePacket();
    if (next != nullptr) {
      for (size_t i = 0; i < this->handlerMap.size(); i++) {
        this->handlerMap.at(i)(this, next);
      }
    } else {
      counter++;
      continue;
    }

    if (counter > 0) {
      counter = 0;
    }
  } while (!this->interrupt && counter < 10);

}

int cmsdp::CMsdpClient::close()
{
  if (this->state != 2) {
    return (int) msdp::error_t::NOT_STARTED;
  }

  this->state = 3;
  this->interrupt = true;
  return msdp::error_t::SUCCESS;
}

void cmsdp::CMsdpClient::addHandler(cmsdp::MsdpHandler handler)
{
  if (handler != nullptr) {
    this->handlerMap.push_back(handler);
  }
}

