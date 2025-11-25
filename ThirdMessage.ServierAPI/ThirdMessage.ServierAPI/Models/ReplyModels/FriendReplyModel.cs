namespace ThirdMessage.ServierAPI.Models.ReplyModels;

public class FriendReplyModel
{
    public int Count { get; set; }
    public ICollection<FriendModel> Friends { get; set; }
}
