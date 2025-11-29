public class Main {
    public static void main(String[] args) throws Exception {
        APIBridge bridge = new APIBridge(8080, "https://localhost:7034/chatHub");
        bridge.start();
    }
}
