namespace ThirdMessage.ServierAPI.Models.ReplyModels;

public class MessageReplyModel
{
    public string FromUid { get; set; }
    public string ToUid { get; set; }
    public string Content { get; set; }
    public long Time { get; set; }
}
