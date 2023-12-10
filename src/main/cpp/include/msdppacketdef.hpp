#if !defined(__MSDP_PACKET_H_)
#define __MSDP_PACKET_H_

#include "msdptypes.hpp"
#include "msdperror.hpp"

namespace msdp {

namespace packet
{
  
  int GetType(const MSDPPacket pckt, uint_8 *type);
  int GetSystemId(const MSDPPacket pckt, uint_8 *id);
  int GetVersion(const MSDPPacket pckt, uint_16 *version);
  int GetUUID(const MSDPPacket pckt, msdp::uuid::msdpuuid uuid);
  int GetChecksum(const MSDPPacket pckt, uint_16 *checksum);
  int GetDataLength(const MSDPPacket pckt, uint_32 *length);
  int GetPayload(const MSDPPacket pckt, uint_8* payload);

  int SetType(MSDPPacket pckt, const uint_8 *type);
  int SetSystemId(MSDPPacket pckt, const uint_8 *id);
  int SetVersion(MSDPPacket pckt, const uint_16 *version);
  int SetUUID(MSDPPacket pckt, const msdp::uuid::msdpuuid uuid);
  int SetChecksum(MSDPPacket pckt, const uint_16 *checksum);
  int SetDataLength(MSDPPacket pckt, const uint_32 *length);
  int SetPayload(MSDPPacket pckt, const uint_8* payload, const uint_32 *length);

  bool ValidateChecksum(const MSDPPacket pckt, const uint_16 *checksum);
  int GenerateChecksum(const MSDPPacket pckt, uint_16 *checksum);

  MSDPPacket NewPacket(const uint_32 length);
  void FreePacket(MSDPPacket pckt);
} // namespace packet

}

#endif // __MSDP_PACKET_H_
