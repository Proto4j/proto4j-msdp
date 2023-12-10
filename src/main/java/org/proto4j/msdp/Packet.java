package org.proto4j.msdp; //@date 22.09.2022

public final class Packet {

    private static final Packet instance = new Packet();

    static {
        MSDP.ensureLibLoaded();
    }

    public static Packet getInstance() {
        return instance;
    }

    public native byte[] createPacket();

    public native boolean setPacketType(byte[] packet, int type);

    public native boolean setPacketUUID(byte[] packet, byte[] uuid);

    public native boolean setPayload(byte[] packet, byte[] payload);

    public native byte[] finishPacket(byte[] packet);

    public native byte getPacketType(byte[] packet);

    public native byte getPacketSystemID(byte[] packet);

    public native short getPacketVersion(byte[] packet);

    public native byte[] getPacketUUID(byte[] packet);

    public native short getPacketChecksum(byte[] packet);

    public native int getPacketDataLength(byte[] packet);

    public native byte[] getPacketPayload(byte[] packet);

}
