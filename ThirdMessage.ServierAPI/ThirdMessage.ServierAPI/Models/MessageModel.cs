using System.Text.Json.Serialization;

namespace ThirdMessage.ServierAPI.Models;

public class MessageModel
{
    public int Uid { get; set; }

    public string Message { get; set; }

    public long Time{ get; set; }
}
