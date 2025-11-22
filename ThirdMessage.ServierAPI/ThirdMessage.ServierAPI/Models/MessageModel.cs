using System.Text.Json.Serialization;

namespace ThirdMessage.ServierAPI.Models;

public class MessageModel
{
    [JsonPropertyName("uid")]
    public int Uid { get; set; }

    [JsonPropertyName("message")]
    public string Message { get; set; }

    [JsonPropertyName("time")]
    public long Time{ get; set; }
}
