using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Threading.Tasks;
using ThirdMessage.ServierAPI.Database;
using ThirdMessage.ServierAPI.Database.Entitys;
using ThirdMessage.ServierAPI.Models.ReplyModels;

namespace ThirdMessage.ServierAPI.Controllers;

[ApiController]
[Route("api/[controller]/[action]")]
public class FriendController : ControllerBase
{
    private readonly ApplicationDbContext database;
    private readonly UserManager<UserEntity> userManager;
    public FriendController(ApplicationDbContext dbContext, UserManager<UserEntity> userManager)
    {
        this.userManager = userManager;
        this.database = dbContext;
    }
    [HttpGet]
    public async Task<ReplyModel<FriendReplyModel>> GetFriends(string uid)
    {
        Console.WriteLine($"GetFriends called with uid: {uid}");
        var user = await userManager.FindByIdAsync(uid);
        Console.WriteLine($"User found: {user != null}");
        if (user != null)
        {
            await database.Entry(user).Collection(u => u.Friends).LoadAsync();
            return new ReplyModel<FriendReplyModel>
            {
                Code = 0,
                Message = "Success",
                Model = new()
                {
                    Count = user.Friends.Count,
                    Friends = user.Friends
                }
            };
        }
        else
        {
            return new ReplyModel<FriendReplyModel>
            {
                Code = 1,
                Message = "User not found",
                Model = null
            };
        }
    }
}
