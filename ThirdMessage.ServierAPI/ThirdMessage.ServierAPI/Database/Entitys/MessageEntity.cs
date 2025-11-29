namespace ThirdMessage.ServierAPI.Database.Entitys;

public class MessageEntity
{
    public int Id { get; set; }
    public string FromUserId { get; set; } = null!;
    public string ToUserId { get; set; } = null!;
    public string Content { get; set; } = null!;
    public long Timestamp { get; set; }
}
