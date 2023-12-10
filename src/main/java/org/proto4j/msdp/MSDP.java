package org.proto4j.msdp; //@date 26.09.2022

import org.proto4j.msdp.client.MsdpClient;
import org.proto4j.xtral.XTral;
import org.proto4j.xtral.XTralClient;
import org.proto4j.xtral.config.AbstractXTralConfiguration;
import org.proto4j.xtral.config.XTralConfiguration;
import org.proto4j.xtral.io.ConnectionFactory;
import org.proto4j.xtral.io.channel.ChannelFactory;
import org.proto4j.xtral.multicast.DatagramSocketFactory;
import org.proto4j.xtral.multicast.XTralMulticastConfiguration;

import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.UnknownHostException;
import java.util.Properties;
import java.util.concurrent.ForkJoinPool;

public final class MSDP extends AbstractXTralConfiguration<MsdpClient>
        implements XTralMulticastConfiguration<MsdpClient> {

    public static final     String  UDP_BROADCAST = "224.0.0.200";
    private static volatile boolean loaded        = false;
    private final Properties properties = new Properties();

    public MSDP(MsdpClient instance) throws UnknownHostException {
        super(MsdpClient.class, instance);
        setChannelFactory((ChannelFactory<MulticastSocket>) MsdpChannel::new);
        setConnectionFactory((ConnectionFactory<MulticastSocket>) MsdpConnection::new);
        setService(new ForkJoinPool(5));

        properties.putIfAbsent("msdp.address", InetAddress.getByName(UDP_BROADCAST));
    }

    public static XTralClient getClient() {
        return XTral.client(MsdpClient.class);
    }

    public static void ensureLibLoaded() {
        if (!loaded) {
            System.loadLibrary("msdplib");
        }
    }

    public static XTralConfiguration<MsdpClient> newConfiguration(MsdpClient client) throws UnknownHostException {
        return new MSDP(client);
    }

    @Override
    public Properties getProperties() {
        return properties;
    }

    @Override
    public DatagramSocketFactory getDatagramFactory() {
        return new MsdpDatagramFactory();
    }


}
