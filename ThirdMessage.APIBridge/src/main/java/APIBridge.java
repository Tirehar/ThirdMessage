import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.microsoft.signalr.HubConnection;
import com.microsoft.signalr.HubConnectionBuilder;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;
import models.ReceiveMessageModel;
import org.java_websocket.WebSocket;
import org.java_websocket.handshake.ClientHandshake;
import org.java_websocket.server.WebSocketServer;

import javax.net.ssl.*;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Executors;

public class APIBridge extends WebSocketServer {
    private final ClientManager clientManager = new ClientManager();
    private final SignalRClient signalRClient;

    public APIBridge(int port, String hubUrl) throws Exception {
        super(new InetSocketAddress(port));
        this.signalRClient = new SignalRClient(hubUrl, clientManager);
    }

    @Override
    public void onOpen(WebSocket webSocket, ClientHandshake clientHandshake) {
        String cookieHeader = clientHandshake.getFieldValue("Cookie");
        if (cookieHeader != null && !cookieHeader.isEmpty()) {
            Map<String, String> cookies = new HashMap<>();
            String[] pairs = cookieHeader.split(";");
            for (String pair : pairs) {
                String[] kv = pair.trim().split("=", 2);
                if (kv.length == 2) {
                    cookies.put(kv[0], kv[1]);
                }
            }
            String userId = cookies.get("uid");
            if (userId != null) {
                System.out.println("User " + userId + " connected.");
                clientManager.addClient(userId, webSocket);
            }
        }
        System.out.println("Client connected.");
    }

    @Override
    public void onClose(WebSocket webSocket, int code, String reason, boolean remote) {
        clientManager.removeClientBySocket(webSocket);
        System.out.println("Client disconnected.");
    }

    @Override
    public void onMessage(WebSocket webSocket, String messageJson) {
        System.out.println("Message: " + messageJson);
        signalRClient.sendMessage(messageJson);
    }

    @Override
    public void onError(WebSocket webSocket, Exception ex) {
        System.out.println("SignalR Bridge errored. " + (ex != null ? ex.getMessage() : ""));
    }

    @Override
    public void onStart() {
        System.out.println("SignalR Bridge started.");
    }
}
