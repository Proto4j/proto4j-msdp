#include "../include/msdpuuid.hpp"

using namespace msdp;

static volatile bool initialized = false;

int msdp::uuid::InitRandom()
{
  if (initialized) {
    return error_t::ALREADY_INITIALIZED;
  }

  srand(time(NULL));
  return error_t::SUCCESS;
}

msdp::uuid::msdpuuid msdp::uuid::NewUUID()
{
  return (uuid::msdpuuid) malloc(uuid::MSDP_UUID_LENGTH);
}

int msdp::uuid::FreeUUID(msdp::uuid::msdpuuid _Uuid)
{
  if (_Uuid == NULL) {
    return error_t::NULL_POINTER;
  }

  free((void *)_Uuid);
  return error_t::SUCCESS;
}

int msdp::uuid::FillUUID(msdp::uuid::msdpuuid _Uuid)
{
  if (_Uuid == NULL) {
    return error_t::NULL_POINTER;
  }

  for (size_t i = 0; i < uuid::MSDP_UUID_LENGTH; i++)
  {
    _Uuid[i] = ((rand() % (int)(((16) + 1) - (0))) + (0));
  }
  
  return error_t::SUCCESS;
}

int msdp::uuid::FillUUID(msdp::uuid::msdpuuid _Uuid, uint_8 *values)
{
  if (_Uuid == NULL || values == NULL) {
    return error_t::NULL_POINTER;
  }

  for (size_t i = 0; i < uuid::MSDP_UUID_LENGTH; i++)
  {
    _Uuid[i] = values[i];
  }

  return error_t::SUCCESS;
}
