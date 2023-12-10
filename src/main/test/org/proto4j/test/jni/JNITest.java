package org.proto4j.test.jni; //@date 22.09.2022

import org.proto4j.msdp.MSDP;
import org.proto4j.msdp.client.MsdpClient;
import org.proto4j.xtral.XTralClient;

import java.util.Arrays;

public class JNITest {

    public static void main(String[] args) throws Exception {
        XTralClient  client = MSDP.getClient();

        MsdpClient msdpClient = (MsdpClient) client.getConfiguration().getReference();
        msdpClient.add((client1, packet) -> {

        });

        client.start();
    }
}
