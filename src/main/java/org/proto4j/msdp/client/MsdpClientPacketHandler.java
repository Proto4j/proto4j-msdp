package org.proto4j.msdp.client; //@date 26.09.2022

import org.proto4j.msdp.Packet;
import org.proto4j.xtral.annotation.Agent;
import org.proto4j.xtral.annotation.InboundHandler;
import org.proto4j.xtral.annotation.OutboundHandler;

import java.net.DatagramPacket;

@Agent
public class MsdpClientPacketHandler {

    @InboundHandler(addFirst = true)
    public byte[] onPacket(DatagramPacket packet) {
        return packet.getData();
    }

    @OutboundHandler(addLast = true)
    public byte[] onNextPacket(byte[] packet) {
        return Packet.getInstance().finishPacket(packet);
    }
}
