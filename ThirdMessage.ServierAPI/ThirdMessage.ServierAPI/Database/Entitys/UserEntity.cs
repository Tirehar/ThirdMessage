using Microsoft.AspNetCore.Identity;

namespace ThirdMessage.ServierAPI.Database.Entitys;

public class UserEntity : IdentityUser
{
    public ICollection<FriendEntityl> Friends { get; set; }
}
