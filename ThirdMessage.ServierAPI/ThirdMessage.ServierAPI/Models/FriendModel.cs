namespace ThirdMessage.ServierAPI.Models;

public class FriendModel
{
    public int Uid { get; set; }
    public string UserName { get; set; }
    public MessageModel[] Messages { get; set; }
}
