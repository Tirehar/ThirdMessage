using System.Text.Json.Serialization;

namespace ThirdMessage.ServierAPI.Models;

public class ReplyModel<T> where T : class
{
    [JsonPropertyName("model")]
    public T Model{ get; set; }

    [JsonPropertyName("message")]
    public string Message { get; set; }

    [JsonPropertyName("code")]
    public int Code { get; set;}
}
