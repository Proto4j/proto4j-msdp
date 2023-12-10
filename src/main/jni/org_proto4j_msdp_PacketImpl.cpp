#include "org_proto4j_msdp_Packet.h"
#include "../cpp/include/msdp.hpp"

/*
 * Class:     org_proto4j_msdp_Packet
 * Method:    createPacket
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_proto4j_msdp_Packet_createPacket
  (JNIEnv *env, jobject obj)
{
  msdp::uint_8 *values = msdp::packet::NewPacket(512);
  if (!values) {
    return NULL;
  }

  jbyteArray array = env->NewByteArray(512);
  env->SetByteArrayRegion(array, 0, 512, (const jbyte *) values);
  return array;
}

/*
 * Class:     org_proto4j_msdp_Packet
 * Method:    setPacketType
 * Signature: ([BI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_proto4j_msdp_Packet_setPacketType
  (JNIEnv *env, jobject obj, jbyteArray p, jint type)
{
  if (NULL == p) {
    return (jboolean)false;
  }
  
  if (type < 0) {
    return (jboolean)false;
  }

  jbyte *array = env->GetByteArrayElements(p, NULL);
  msdp::packet::SetType((msdp::packet::MSDPPacket)array, (const msdp::uint_8 *)&type);
  env->SetByteArrayRegion(p, 0, env->GetArrayLength(p), array);
  return (jboolean)true;
}

/*
 * Class:     org_proto4j_msdp_Packet
 * Method:    setPacketUUID
 * Signature: ([B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_proto4j_msdp_Packet_setPacketUUID
  (JNIEnv *env, jobject obj, jbyteArray p, jbyteArray uuid) 
{
   if (NULL == p) {
    return (jboolean)false;
  }

   if (NULL == uuid) {
    return (jboolean)false;
  }

  jbyte *array = env->GetByteArrayElements(p, NULL);
  jbyte *u = env->GetByteArrayElements(p, NULL);
  msdp::packet::SetUUID((msdp::packet::MSDPPacket) array, (const msdp::uuid::msdpuuid) u);
  env->SetByteArrayRegion(p, 0, env->GetArrayLength(p), array);
  return (jboolean)true;
}

/*
 * Class:     org_proto4j_msdp_Packet
 * Method:    setPayload
 * Signature: ([B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_proto4j_msdp_Packet_setPayload
  (JNIEnv *env, jobject obj, jbyteArray p, jbyteArray payload)
{

  if (NULL == p) {
    return (jboolean)false;
  }

   if (NULL == payload) {
    return (jboolean)false;
  }

  jbyte *array = env->GetByteArrayElements(p, NULL);
  jbyte *u = env->GetByteArrayElements(p, NULL);
  const msdp::uint_32 size = (msdp::uint_32) env->GetArrayLength(payload);

  msdp::packet::SetPayload(
    (msdp::packet::MSDPPacket) array,
    (msdp::uint_8 *)u,
    &size
  );
  env->SetByteArrayRegion(p, 0, env->GetArrayLength(p), array);
  return (jboolean)true;
}

/*
 * Class:     org_proto4j_msdp_Packet
 * Method:    finishPacket
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_proto4j_msdp_Packet_finishPacket
  (JNIEnv *env, jobject obj, jbyteArray p)
{
  if (NULL == p) {
    return NULL;
  }

  jbyte *array = env->GetByteArrayElements(p, NULL);
  int checksum;
  msdp::packet::GenerateChecksum(
    (msdp::packet::MSDPPacket)array, 
    (msdp::uint_16 *)&checksum
  );
  msdp::packet::SetChecksum(
    (msdp::packet::MSDPPacket)array, 
    (const msdp::uint_16 *)&checksum
  );
  env->SetByteArrayRegion(p, 0, env->GetArrayLength(p), array);
  return p;
}

#define GetProperty(env, p, type, retType, method) \
  if (NULL == p) { \
    return NULL; \
  } \
  jbyte *array = env->GetByteArrayElements(p, NULL); \
  msdp::type property; \
  msdp::packet::method((msdp::packet::MSDPPacket)array, &property); \
  return (retType)property; 

/*
 * Class:     org_proto4j_msdp_Packet
 * Method:    getPacketType
 * Signature: ([B)B
 */
JNIEXPORT jbyte JNICALL Java_org_proto4j_msdp_Packet_getPacketType
  (JNIEnv *env, jobject obj, jbyteArray p)
{
  GetProperty(env, p, uint_8, jbyte, GetType);
}

/*
 * Class:     org_proto4j_msdp_Packet
 * Method:    getPacketSystemID
 * Signature: ([B)B
 */
JNIEXPORT jbyte JNICALL Java_org_proto4j_msdp_Packet_getPacketSystemID
  (JNIEnv *env, jobject obj, jbyteArray p)
{
  GetProperty(env, p, uint_8, jbyte, GetSystemId);
}

/*
 * Class:     org_proto4j_msdp_Packet
 * Method:    getPacketVersion
 * Signature: ([B)S
 */
JNIEXPORT jshort JNICALL Java_org_proto4j_msdp_Packet_getPacketVersion
  (JNIEnv *env, jobject obj, jbyteArray p)
{
  GetProperty(env, p, uint_16, jshort, GetVersion);
}

/*
 * Class:     org_proto4j_msdp_Packet
 * Method:    getPacketUUID
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_proto4j_msdp_Packet_getPacketUUID
  (JNIEnv *env, jobject obj, jbyteArray p)
{
  if (NULL == p) { 
    return NULL; 
  } 

  jbyte *array = env->GetByteArrayElements(p, NULL); 

  msdp::uuid::msdpuuid property = msdp::uuid::NewUUID();
  msdp::packet::GetUUID((msdp::packet::MSDPPacket)array, property); 

  jbyteArray payload = env->NewByteArray(msdp::uuid::MSDP_UUID_LENGTH);
  env->SetByteArrayRegion(payload, 0, msdp::uuid::MSDP_UUID_LENGTH, (const jbyte *)property);
  return payload; 
}

/*
 * Class:     org_proto4j_msdp_Packet
 * Method:    getPacketChecksum
 * Signature: ([B)S
 */
JNIEXPORT jshort JNICALL Java_org_proto4j_msdp_Packet_getPacketChecksum
  (JNIEnv *env, jobject obj, jbyteArray p)
{
  GetProperty(env, p, uint_16, jshort, GetChecksum);
}

/*
 * Class:     org_proto4j_msdp_Packet
 * Method:    getPacketDataLength
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_org_proto4j_msdp_Packet_getPacketDataLength
  (JNIEnv *env, jobject obj, jbyteArray p)
{
  GetProperty(env, p, uint_32, jint, GetDataLength);
}

/*
 * Class:     org_proto4j_msdp_Packet
 * Method:    getPacketPayload
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_proto4j_msdp_Packet_getPacketPayload
  (JNIEnv *env, jobject obj, jbyteArray p)
{
  if (NULL == p) { 
    return NULL; 
  } 

  jbyte *array = env->GetByteArrayElements(p, NULL); 

  msdp::uint_32 size;
  msdp::packet::GetDataLength((const msdp::packet::MSDPPacket) array, &size);
  msdp::uint_8 *property = (msdp::uint_8 *)malloc(size); 
  msdp::packet::GetPayload((msdp::packet::MSDPPacket)array, property); 

  jbyteArray payload = env->NewByteArray(size);
  env->SetByteArrayRegion(payload, 0, size, (const jbyte *)property);
  return payload; 
}

