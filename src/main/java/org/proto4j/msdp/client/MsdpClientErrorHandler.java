package org.proto4j.msdp.client; //@date 26.09.2022

import org.proto4j.msdp.MsdpConnection;
import org.proto4j.xtral.annotation.Agent;
import org.proto4j.xtral.annotation.ExceptionHandler;

@Agent
public class MsdpClientErrorHandler {

    @ExceptionHandler
    public void nextError(Exception exception, MsdpConnection connection) {
        // handle
    }
}
