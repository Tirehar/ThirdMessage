using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Security.Claims;
using ThirdMessage.ServierAPI.Database;
using ThirdMessage.ServierAPI.Database.Entitys;
using ThirdMessage.ServierAPI.Models;
using ThirdMessage.ServierAPI.Models.ReplyModels;

namespace ThirdMessage.ServierAPI.Controllers;

[ApiController]
[Route("api/[controller]/[action]")]
public class FriendController : ControllerBase
{
    private readonly ApplicationDbContext database;
    private readonly UserManager<UserEntity> userManager;
    private readonly ILogger<FriendController> logger;
    public FriendController(ApplicationDbContext dbContext, UserManager<UserEntity> userManager, ILogger<FriendController> logger)
    {
        this.userManager = userManager;
        this.database = dbContext;
        this.logger = logger;
    }

    [HttpGet]
    [Authorize]
    public async Task<ReplyModel<FriendReplyModel>> GetFriends()
    {
        logger.LogInformation("GetFriends called");
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

    [HttpGet]
    [Authorize]
    public async Task<ReplyModel<string[]>> SearchFriends(string keyword)
    {
        logger.LogInformation("SearchFriends called with keyword: {keyword}", keyword);
        var userId = User.FindFirst(ClaimTypes.NameIdentifier)?.Value ?? User.Identity?.Name;
        var user = await userManager.FindByIdAsync(userId);
        if(user != null)
        {
            await database.Entry(user).Collection(u => u.Friends).LoadAsync();
            var friendUids = user.Friends.Select(f => f.Uid).ToHashSet();
            var matches = await userManager.Users
                .Where(u => EF.Functions.Like(u.UserName, $"%{keyword}%"))
                .Where(u => u.Id != userId)
                .Where(u => !friendUids.Contains(u.Id))
                .Select(u => u.UserName!)
                .ToListAsync();
            if (matches != null && matches.Any())
            {
                return new ReplyModel<string[]>()
                {
                    Code = 0,
                    Message = "Success",
                    Model = matches.ToArray()
                };
            }
        }
        return new ReplyModel<string[]>()
        {
            Code = -1,
            Message = "No matches found",
            Model = Array.Empty<string>()
        };
    }

    [HttpPost]
    [Authorize]
    public async Task<ReplyModel<EmptyModel>> FriendRequest([FromQuery]string userName)
    {
        logger.LogInformation("FriendRequest called for userName: {userName}", userName);
        var userId = User.FindFirst(ClaimTypes.NameIdentifier)?.Value ?? User.Identity?.Name;
        var user = await userManager.FindByIdAsync(userId);
        var otherUser = await userManager.FindByNameAsync(userName);
        var otheruid = otherUser?.Id;
        if (user != null && otherUser != null)
        {
            if(userId != otheruid)
            {
                user.Friends.Add(new() { UserName = otherUser.UserName!, Uid = otheruid! });
                otherUser.Friends.Add(new() { UserName = user.UserName!, Uid = userId});
                await userManager.UpdateAsync(user);
                await userManager.UpdateAsync(otherUser);
                return new ReplyModel<EmptyModel>
                {
                    Code = 0,
                    Message = "Success"
                };
            }
            return new ReplyModel<EmptyModel>
            {
                Code = -2,
                Message = "Trying to send a request to yourself",
            };
        }
        return new ReplyModel<EmptyModel>
        {
            Code = -1,
            Message = "Not found user",
        };
    }
}
