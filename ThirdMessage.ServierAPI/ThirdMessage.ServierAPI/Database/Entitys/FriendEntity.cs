namespace ThirdMessage.ServierAPI.Database.Entitys;

public class FriendEntity
{
    public int FriendId { get; set; }
    public string Uid { get; set; }
    public string UserName { get; set; }
    public ICollection<MessageEntity> Messages { get; set; }
}
