package models;

import com.google.gson.annotations.SerializedName;

public class ReplyModel<T> {
    @SerializedName("Code")
    private int code;
    @SerializedName("Message")
    private String message;
    @SerializedName("Model")
    private T model;

    public int getCode() {
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public T getModel() {
        return model;
    }

    public void setModel(T model) {
        this.model = model;
    }
}
