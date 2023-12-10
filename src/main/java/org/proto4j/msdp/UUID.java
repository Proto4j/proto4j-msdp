package org.proto4j.msdp; //@date 22.09.2022

public final class UUID {

    static {
        MSDP.ensureLibLoaded();
    }

    public static UUID getInstance() {
        return new UUID();
    }

    public native byte[] newUUID();

    public native boolean fillUUID(byte[] uuid);

    public native boolean fillUUID(byte[] uuid, byte[] values);
}
