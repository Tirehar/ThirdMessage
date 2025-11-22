import com.microsoft.signalr.HubConnection;
import com.microsoft.signalr.HubConnectionBuilder;
import org.java_websocket.WebSocket;
import org.java_websocket.handshake.ClientHandshake;
import org.java_websocket.server.WebSocketServer;

import javax.net.ssl.*;
import java.net.InetSocketAddress;

public class APIBridge extends WebSocketServer {

    private HubConnection hubConnection;

    public APIBridge(int port) {
        super(new InetSocketAddress(port));
        setupSignalRConnection();
    }

    private void setupSignalRConnection() {
        String hubUrl = "https://localhost:7034/chatHub";

        TrustManager[] trustAllCerts = new TrustManager[]{
                new X509TrustManager() {
                    @Override
                    public void checkClientTrusted(java.security.cert.X509Certificate[] chain, String authType) {
                    }

                    @Override
                    public void checkServerTrusted(java.security.cert.X509Certificate[] chain, String authType) {
                    }

                    @Override
                    public java.security.cert.X509Certificate[] getAcceptedIssuers() {
                        return new java.security.cert.X509Certificate[0];
                    }
                }
        };
        try{
            SSLContext sslContext = SSLContext.getInstance("TLS");
            sslContext.init(null, trustAllCerts, new java.security.SecureRandom());
            HostnameVerifier hostnameVerifier = (hostname, session) -> true;
            hubConnection = HubConnectionBuilder.create(hubUrl).setHttpClientBuilderCallback(builder -> {
                builder.sslSocketFactory(sslContext.getSocketFactory(), (X509TrustManager) trustAllCerts[0]);
                builder.hostnameVerifier(hostnameVerifier);
            }).build();
        }catch (Exception e) {
            System.err.println("Error creating SSLContext: " + e.getMessage());
        }

        // 1. 从 SignalR Hub 接收消息，并将其转发到 C++ 客户端
        hubConnection.on("ReceiveMessage", (response) -> {
            System.out.println("Received from SignalR Hub: " + response);
            // 广播给所有连接的 WebSocket 客户端 (例如 C++)
            broadcast(response);
        }, String.class);

        // 启动 SignalR 连接
        try {
            System.out.println("Connecting to SignalR Hub...");
            hubConnection.start().blockingAwait();
            System.out.println("Connected to SignalR Hub.");
        } catch (Exception e) {
            System.err.println("Error connecting to SignalR Hub: " + e.getMessage());
        }
    }

    @Override
    public void onOpen(WebSocket webSocket, ClientHandshake clientHandshake) {
        System.out.println("Client connected.");
    }

    @Override
    public void onClose(WebSocket webSocket, int i, String s, boolean b) {
        System.out.println("Client disconnected.");
    }

    @Override
    public void onMessage(WebSocket webSocket, String message) {
        System.out.println("Message: " + message);
        // 假设消息格式为 "user:message"
        String[] parts = message.split(":", 2);
        String user = parts.length > 1 ? parts[0] : "JavaBridgeClient";
        String msg = parts.length > 1 ? parts[1] : message;

        // 调用 Hub 的 SendMessage 方法
        hubConnection.invoke("SendMessage", user.trim(), msg.trim());
    }

    @Override
    public void onError(WebSocket webSocket, Exception e) {
        System.out.println("SignalR Bridge errored." + e.getMessage());
    }

    @Override
    public void onStart() {
        System.out.println("SignalR Bridge started.");
    }
}
