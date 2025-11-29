using System.Text.Json.Serialization;

namespace ThirdMessage.ServierAPI.Models;

public class MessageModel
{
    public string Uid { get; set; }

    public string ToUid { get; set; }

    public string Message { get; set; }

    public long Time{ get; set; }
}
