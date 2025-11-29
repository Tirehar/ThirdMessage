package utils;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.SSLContext;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;
import java.security.SecureRandom;
import java.security.cert.X509Certificate;

public class SSLUtils {
    public static X509TrustManager createTrustAllManager() {
        return new X509TrustManager() {
            @Override
            public void checkClientTrusted(X509Certificate[] chain, String authType) { }

            @Override
            public void checkServerTrusted(X509Certificate[] chain, String authType) { }

            @Override
            public X509Certificate[] getAcceptedIssuers() {
                return new X509Certificate[0];
            }
        };
    }

    public static SSLContext createTrustAllSslContext() throws Exception {
        X509TrustManager trustAll = createTrustAllManager();
        SSLContext sslContext = SSLContext.getInstance("TLS");
        sslContext.init(null, new TrustManager[]{trustAll}, new SecureRandom());
        return sslContext;
    }

    public static HostnameVerifier trustAllHostnameVerifier() {
        return (hostname, session) -> true;
    }
}
