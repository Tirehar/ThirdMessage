import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;
import com.microsoft.signalr.HubConnection;
import com.microsoft.signalr.HubConnectionBuilder;
import models.ReceiveMessageModel;
import models.ReplyModel;
import org.java_websocket.WebSocket;
import utils.SSLUtils;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.SSLContext;
import javax.net.ssl.X509TrustManager;

public class SignalRClient {
    private final Gson gson = new GsonBuilder().create();
    private final HubConnection hubConnection;
    private final ClientManager clientManager;

    public SignalRClient(String hubUrl, ClientManager clientManager) throws Exception {
        this.clientManager = clientManager;

        SSLContext sslContext = SSLUtils.createTrustAllSslContext();
        X509TrustManager trustManager = SSLUtils.createTrustAllManager();
        HostnameVerifier hostnameVerifier = SSLUtils.trustAllHostnameVerifier();

        hubConnection = HubConnectionBuilder.create(hubUrl)
                .setHttpClientBuilderCallback(builder -> {
                    builder.sslSocketFactory(sslContext.getSocketFactory(), trustManager);
                    builder.hostnameVerifier(hostnameVerifier);
                })
                .build();

        hubConnection.on("ReceiveMessage", (response) -> {
            try {
                ReplyModel<ReceiveMessageModel> model = gson.fromJson(response, new TypeToken<ReplyModel<ReceiveMessageModel>>(){}.getType());
                if (model.getCode() == 0) {
                    var messageModel = model.getModel();
                    WebSocket sender = clientManager.getClient(messageModel.getFromUid());
                    WebSocket receiver = clientManager.getClient(messageModel.getToUid());
                    if (receiver != null) receiver.send(response);
                    if (sender != null) sender.send(response);
                }
            } catch (Exception ex) {
                System.err.println("Error handling ReceiveMessage: " + ex.getMessage());
            }
        }, String.class);

        start();
    }

    private void start() {
        try {
            System.out.println("Connecting to SignalR Hub...");
            hubConnection.start().blockingAwait();
            System.out.println("Connected to SignalR Hub.");
        } catch (Exception e) {
            System.err.println("Error connecting to SignalR Hub: " + e.getMessage());
        }
    }

    public void sendMessage(String messageJson) {
        if (hubConnection != null) {
            hubConnection.invoke("SendMessage", messageJson);
        }
    }

    public void stop() {
        if (hubConnection != null) {
            try {
                hubConnection.stop();
            } catch (Exception ignored) { }
        }
    }
}
