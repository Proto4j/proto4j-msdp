#include "../include/msdppacketdef.hpp"
#include <string>

using namespace msdp;
using namespace msdp::packet;

#define CheckLen(buffer, len) \
  if ((sizeof(buffer) / sizeof(uint_8)) < len) { \
    return error_t::BUFFER_TOO_SMALL; \
  }

#define RequireNonNull(o0, o1) \
  if (NULL == o0 || NULL == o1) { \
    return error_t::NULL_POINTER; \
  }

#define RequireNonNullElement(o0) \
  if (NULL == o0) { \
    return error_t::NULL_POINTER; \
  }

int msdp::packet::GetType(const MSDPPacket pckt, uint_8 *type)
{
  RequireNonNull(pckt, type)
  CheckLen(pckt, 1)

  *type = (uint_8)*pckt;
  return error_t::SUCCESS;
}

int msdp::packet::GetSystemId(const MSDPPacket pckt, uint_8 *id)
{
  RequireNonNull(pckt, id)
  CheckLen(pckt, 2)

  *id = (uint_8)pckt[1];
  return error_t::SUCCESS;
}

int msdp::packet::GetVersion(const MSDPPacket pckt, uint_16 *version)
{
  RequireNonNull(pckt, version)
  CheckLen(pckt, 4)
  
  *version = *(const uint_16 *)(pckt + 2);
  return error_t::SUCCESS;
}

int msdp::packet::GetUUID(const MSDPPacket pckt, msdp::uuid::msdpuuid uuid)
{
  RequireNonNull(pckt, uuid)
  CheckLen(pckt, 16)

  memcpy((void *)uuid, (const void *)(pckt+4), msdp::uuid::MSDP_UUID_LENGTH);
  return error_t::SUCCESS;
}

int msdp::packet::GetChecksum(const MSDPPacket pckt, uint_16 *checksum)
{
  RequireNonNull(pckt, checksum)
  CheckLen(pckt, 18)

  *checksum = *(const uint_16 *)(pckt + 16);
  return error_t::SUCCESS;
}

int msdp::packet::GetDataLength(const MSDPPacket pckt, uint_32 *length) 
{
  RequireNonNull(pckt, length)
  CheckLen(pckt, 22)

  *length = *(const uint_32 *)(pckt + 18);
  return error_t::SUCCESS;
}

int msdp::packet::GetPayload(const MSDPPacket pckt, uint_8* payload)
{
  RequireNonNull(pckt, payload)

  size_t size = sizeof(payload) / sizeof(uint_8);
  CheckLen(pckt, 22 + size)

  memcpy((void *)payload, (const void *)(pckt + 22), size);
  return error_t::SUCCESS;
}

int msdp::packet::SetType(MSDPPacket pckt, const uint_8 *type)
{
  RequireNonNull(pckt, type)
  CheckLen(pckt, 1)

  *pckt = *type;
  return error_t::SUCCESS;
}

int msdp::packet::SetSystemId(MSDPPacket pckt, const uint_8 *id)
{
  RequireNonNull(pckt, id)
  CheckLen(pckt, 2)

  *(pckt + 1) = *id;
  return error_t::SUCCESS;
}

int msdp::packet::SetVersion(MSDPPacket pckt, const uint_16 *version)
{
  RequireNonNull(pckt, version)
  CheckLen(pckt, 4)

  *(uint_16 *)(pckt+2) = *version;
  return error_t::SUCCESS;
}

int msdp::packet::SetUUID(MSDPPacket pckt, const msdp::uuid::msdpuuid uuido)
{
  RequireNonNull(pckt, uuido)
  CheckLen(pckt, 16)
  CheckLen(uuido, uuid::MSDP_UUID_LENGTH)

  memcpy((void *)(pckt + 4), (const void *)uuido, uuid::MSDP_UUID_LENGTH);
  return error_t::SUCCESS;
}

int msdp::packet::SetChecksum(MSDPPacket pckt, const uint_16 *checksum)
{
  RequireNonNull(pckt, checksum)
  CheckLen(pckt, 18)

  *(uint_16 *)(pckt+16) = *checksum;
  return error_t::SUCCESS;
}

int msdp::packet::SetDataLength(MSDPPacket pckt, const uint_32 *length)
{
  RequireNonNull(pckt, length)
  CheckLen(pckt, 22)

  *(uint_32 *)(pckt+18) = *length;
  return error_t::SUCCESS;
}

int msdp::packet::SetPayload(MSDPPacket pckt, const uint_8* payload, const uint_32 *length)
{
  RequireNonNull(pckt, payload)
  RequireNonNullElement(length)
  
  CheckLen(pckt, 22+(*length))
  memcpy((void *)pckt, (const void *)payload, *length);
  return error_t::SUCCESS;
}

int msdp::packet::GenerateChecksum(const MSDPPacket pckt, uint_16 *checksum)
{
  uint_16 sum = 0;
  uint_8 counter = 0;

  RequireNonNull(pckt, checksum)
  CheckLen(pckt, 16)

  do {
    sum += pckt[counter] + pckt[counter + 1];
    counter += 2;
  } while (counter < 16);

  sum = (sum >> 8) + (sum & 0xFF); 
  *checksum = ~((sum >> 8) + sum);
  return error_t::SUCCESS;
}

bool msdp::packet::ValidateChecksum(const MSDPPacket pckt, const uint_16 *checksum)
{
  uint_16 sum;

  RequireNonNull(pckt, checksum)
  CheckLen(pckt, 16)

  if (GenerateChecksum(pckt, &sum) != error_t::SUCCESS) {
    return false;
  }

  return sum == *(checksum);
}

MSDPPacket msdp::packet::NewPacket(const uint_32 length)
{
  if (length < 22) {
    return (MSDPPacket)NULL;
  }

  return (MSDPPacket) malloc(length);
}

void msdp::packet::FreePacket(MSDPPacket pckt)
{
  free(pckt);
}