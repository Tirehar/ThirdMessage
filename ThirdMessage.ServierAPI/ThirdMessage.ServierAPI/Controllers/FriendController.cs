using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Security.Claims;
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
    [Authorize]
    public async Task<ReplyModel<FriendReplyModel>> GetFriends()
    {
        var userId = User.FindFirst(ClaimTypes.NameIdentifier)?.Value ?? User.Identity?.Name;
        var user = await userManager.FindByIdAsync(userId);
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
