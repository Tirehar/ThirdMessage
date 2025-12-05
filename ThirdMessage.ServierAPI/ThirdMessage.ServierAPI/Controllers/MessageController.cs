using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using System.Security.Claims;
using ThirdMessage.ServierAPI.Database;
using ThirdMessage.ServierAPI.Database.Entitys;
using ThirdMessage.ServierAPI.Models.ReplyModels;

namespace ThirdMessage.ServierAPI.Controllers;

[ApiController]
[Route("api/[controller]/[action]")]
public class MessageController : ControllerBase
{
    private readonly ApplicationDbContext database;
    private readonly UserManager<UserEntity> userManager;
    private readonly ILogger<MessageController> logger;
    public MessageController(ApplicationDbContext dbContext, UserManager<UserEntity> userManager, ILogger<MessageController> logger) 
    { 
        this.database = dbContext;
        this.userManager = userManager;
        this.logger = logger;
    }

    [HttpGet]
    [Authorize]
    public async Task<ReplyModel<MessageReplyModel[]>> GetMessage(string otheruid)
    {
        logger.LogInformation("GetMessage called for uid: {otheruid}", otheruid);
        var userId = User.FindFirst(ClaimTypes.NameIdentifier)?.Value ?? User.Identity?.Name;
        var user = await userManager.FindByIdAsync(userId);
        if (user != null)
        {
            await database.Entry(user).Collection(u => u.Friends).LoadAsync();
            var firends = user.Friends;
            var firend = firends.FirstOrDefault(f => f.Uid == otheruid);
            if (firend != null)
            {
                await database.Entry(firend).Collection(u => u.Messages).LoadAsync();
                var messageEntities = firend.Messages;
                ICollection<MessageReplyModel> messages = [];
                foreach (var message in messageEntities)
                {
                    messages.Add(new MessageReplyModel
                    {
                         Content = message.Content,
                         FromUid = message.FromUserId,
                         ToUid = message.ToUserId,
                         Time = message.Timestamp
                    });
                }
                return new()
                {
                    Code = 0,
                    Message = "Messages retrieved successfully",
                    Model = messages.ToArray()
                };
            }
        }
        return new() 
        { 
            Code = -1,
            Message = "Failed to retrieve messages",
            Model = null
        };
    }
}
