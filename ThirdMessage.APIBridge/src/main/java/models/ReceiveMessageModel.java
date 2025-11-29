package models;

import com.google.gson.annotations.SerializedName;

public class ReceiveMessageModel {
    @SerializedName("Content")
    private String content;
    @SerializedName("FromUid")
    private String fromUid;
    @SerializedName("ToUid")
    private String toUid;
    @SerializedName("Time")
    private int time;

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public String getFromUid() {
        return fromUid;
    }

    public void setFromUid(String fromUid) {
        this.fromUid = fromUid;
    }

    public String getToUid() {
        return toUid;
    }

    public void setToUid(String toUid) {
        this.toUid = toUid;
    }

    public int getTime() {
        return time;
    }

    public void setTime(int time) {
        this.time = time;
    }
}
