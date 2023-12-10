package org.proto4j.msdp; //@date 26.09.2022

import org.proto4j.xtral.multicast.DatagramSocketFactory;

import java.io.IOException;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.MulticastSocket;

public class MsdpDatagramFactory extends DatagramSocketFactory {

    @Override
    public DatagramSocket createSocket(InetAddress inetAddress, int i) throws IOException {
        return new MulticastSocket(new InetSocketAddress(inetAddress.getHostName(), i));
    }
}
