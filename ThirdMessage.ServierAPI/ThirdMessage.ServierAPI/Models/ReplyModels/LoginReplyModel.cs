using System.Text.Json.Serialization;

namespace ThirdMessage.ServierAPI.Models.ReplyModels;

public class LoginReplyModel
{
    public bool IsSuccess { get; set; }
    public int Uid { get; set; }
}
