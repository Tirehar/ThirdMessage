using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using ThirdMessage.ServierAPI.Database;
using ThirdMessage.ServierAPI.Models.ReplyModels;

namespace ThirdMessage.ServierAPI.Controllers;

[ApiController]
[Route("api/[controller]/[action]")]
public class FriendController : ControllerBase
{
    private readonly ApplicationDbContext database;
    public FriendController(ApplicationDbContext dbContext)
    {
        this.database = dbContext;
    }
    [HttpGet]
    public ReplyModel<FriendReplyModel> GetFriends(int uid)
    {
        var user = database.Users.Include(u => u.Friends).FirstOrDefault(u => u.Uid == uid);
        if (user != null)
        {
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
