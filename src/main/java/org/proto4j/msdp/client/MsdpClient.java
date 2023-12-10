package org.proto4j.msdp.client; //@date 26.09.2022

import org.proto4j.msdp.MSDP;
import org.proto4j.msdp.MSDPException;
import org.proto4j.msdp.MsdpConnection;
import org.proto4j.msdp.MsdpListener;
import org.proto4j.xtral.XTralClient;
import org.proto4j.xtral.annotation.Agent;
import org.proto4j.xtral.annotation.AllowConfig;
import org.proto4j.xtral.annotation.Client;
import org.proto4j.xtral.config.XTralConfiguration;
import org.proto4j.xtral.config.XTralConfigurationFactory;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.List;
import java.util.Properties;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.ExecutorService;

@Agent
@AllowConfig
public class MsdpClient implements XTralConfigurationFactory<MsdpClient> {

    private final List<MsdpListener> listenerList =
            new CopyOnWriteArrayList<>();

    private MsdpConnection connection;

    @Client.Entry
    public void startClient(XTralClient client) throws Exception {
        connection = client.openConnection();
        Properties properties = client.getConfiguration().getProperties();
        ExecutorService service = client.getConfiguration().getExecutorService();

        connection.init(null);
        connection.doConnect((InetAddress) properties.get("msdp.address"), 3439);
        service.execute(this::listen);
    }

    private void listen() {
        while (!connection.isClosed()) {
            byte[] packet = (byte[]) connection.readObject();

            for (MsdpListener listener : listenerList) {
                listener.onPacketReceived(this, packet);
            }
        }
    }

    @Override
    public XTralConfiguration<MsdpClient> createConfiguration() {
        try {
            return MSDP.newConfiguration(this);
        } catch (UnknownHostException e) {
            throw new MSDPException(e);
        }
    }

    public void add(MsdpListener msdpListener) {
        listenerList.add(msdpListener);
    }

    public boolean remove(MsdpListener o) {
        return listenerList.remove(o);
    }
}
