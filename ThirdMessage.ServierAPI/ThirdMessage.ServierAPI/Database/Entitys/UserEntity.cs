using Microsoft.AspNetCore.Identity;

namespace ThirdMessage.ServierAPI.Database.Entitys;

public class UserEntity : IdentityUser
{
    public ICollection<FriendEntity> Friends { get; set; }
}
