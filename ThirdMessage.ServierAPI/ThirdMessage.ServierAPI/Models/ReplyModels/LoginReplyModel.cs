using System.Text.Json.Serialization;

namespace ThirdMessage.ServierAPI.Models.ReplyModels;

public class LoginReplyModel
{
    public bool IsSuccess { get; set; }
    public string Uid { get; set; }
}
