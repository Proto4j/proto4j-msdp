package org.proto4j.msdp;//@date 18.09.2022

import org.proto4j.msdp.client.MsdpClient;

public interface MsdpListener {

    public abstract void onPacketReceived(MsdpClient client, byte[] packet);
}
