using ThirdMessage.ServierAPI.Database.Entitys;

namespace ThirdMessage.ServierAPI.Models.ReplyModels;

public class FriendReplyModel
{
    public int Count { get; set; }
    public ICollection<FriendEntity> Friends { get; set; }
}
