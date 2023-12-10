#if !defined(__MSDP_UUID_H__)
#define __MSDP_UUID_H__

#include <time.h>
#include <stdlib.h>

#include "msdptypes.hpp"
#include "msdperror.hpp"

namespace msdp
{
  
namespace uuid
{
  
int InitRandom();

msdpuuid NewUUID();
int FreeUUID(msdpuuid uuid); 
int FillUUID(msdpuuid uuid);
int FillUUID(msdpuuid uuid, uint_8 *values);

} // namespace uuid


} // namespace msdp


#endif // __MSDP_UUID_H__
