#if !defined(__MSDP_ERROR_H__)
#define __MSDP_ERROR_H__

namespace msdp
{
  
  typedef enum _msdp_error : int {

    BUFFER_TOO_SMALL = -2,
    NULL_POINTER = -1,
    
    SUCCESS,
    ALREADY_INITIALIZED,
    NOT_STARTED

  } error_t;

} // namespace msdp


#endif // __MSDP_ERROR_H__
