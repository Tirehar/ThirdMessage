import org.java_websocket.WebSocket;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class ClientManager {
    private final Map<String, WebSocket> clients = new ConcurrentHashMap<>();

    public void addClient(String uid, WebSocket socket) {
        if (uid == null || socket == null) return;
        clients.put(uid, socket);
    }

    public void removeClientByUid(String uid) {
        if (uid == null) return;
        clients.remove(uid);
    }

    public void removeClientBySocket(WebSocket socket) {
        if (socket == null) return;
        clients.entrySet().removeIf(e -> e.getValue().equals(socket));
    }

    public WebSocket getClient(String uid) {
        if (uid == null) return null;
        return clients.get(uid);
    }
}
