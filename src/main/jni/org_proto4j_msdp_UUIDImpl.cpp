/* DO NOT EDIT THIS FILE - it is machine generated */
#include "org_proto4j_msdp_UUID.h"
#include "../cpp/include/msdp.hpp"
/* Header for class org_proto4j_msdp_UUID */

/*
 * Class:     org_proto4j_msdp_UUID
 * Method:    newUUID
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_proto4j_msdp_UUID_newUUID
  (JNIEnv *env, jobject obj)
{
  msdp::uuid::msdpuuid muuid = msdp::uuid::NewUUID();
  jbyteArray array = env->NewByteArray(msdp::uuid::MSDP_UUID_LENGTH);
  env->SetByteArrayRegion(array, 0, msdp::uuid::MSDP_UUID_LENGTH, (const jbyte *)muuid);
  return array;
}

/*
 * Class:     org_proto4j_msdp_UUID
 * Method:    fillUUID
 * Signature: ([B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_proto4j_msdp_UUID_fillUUID___3B
  (JNIEnv *env, jobject obj, jbyteArray uuid)
{
  if (NULL == uuid) {
    return (jboolean) false;
  }

  jbyte *array = env->GetByteArrayElements(uuid, NULL);
  msdp::uuid::FillUUID((msdp::uuid::msdpuuid)array);
  env->SetByteArrayRegion(uuid, 0, msdp::uuid::MSDP_UUID_LENGTH, array);
  return (jboolean) true;
}

/*
 * Class:     org_proto4j_msdp_UUID
 * Method:    fillUUID
 * Signature: ([B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_proto4j_msdp_UUID_fillUUID___3B_3B
  (JNIEnv *env, jobject obj, jbyteArray uuid, jbyteArray filler)
{
    if (NULL == uuid || filler == NULL) {
    return (jboolean) false;
  }

  jbyte *array = env->GetByteArrayElements(uuid, NULL);
  jbyte *fill = env->GetByteArrayElements(filler, NULL);
  msdp::uuid::FillUUID((msdp::uuid::msdpuuid)array, (msdp::uint_8 *)fill);
  env->SetByteArrayRegion(uuid, 0, msdp::uuid::MSDP_UUID_LENGTH, array);
  return (jboolean) true;
}
