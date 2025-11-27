using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using System.Security.Claims;
using System.Threading.Tasks;
using ThirdMessage.ServierAPI.Database;
using ThirdMessage.ServierAPI.Database.Entitys;
using ThirdMessage.ServierAPI.Helper;
using ThirdMessage.ServierAPI.Models;
using ThirdMessage.ServierAPI.Models.ReplyModels;

namespace ThirdMessage.ServierAPI.Controllers;

[ApiController]
[Route("api/[controller]/[action]")]
public class MessageController : ControllerBase
{
    private readonly ApplicationDbContext database;
    private readonly UserManager<UserEntity> userManager;
    public MessageController(ApplicationDbContext dbContext, UserManager<UserEntity> userManager) 
    { 
        this.database = dbContext;
        this.userManager = userManager;
    }

    [HttpGet]

    public async Task<ReplyModel<MessageReplyModel[]>> GetMessage(string otheruid)
    {
        Console.WriteLine("获取与用户 " + otheruid + " 的消息记录");
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
                Console.WriteLine(messageEntities.Count);
                foreach (var message in messageEntities)
                {
                    messages.Add(new MessageReplyModel
                    {
                         Content = message.Content,
                         FromUid = message.FromUserId,
                         ToUid = message.ToUserId,
                         Time = TimeHelper.ToUnixSeconds(message.Timestamp)
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
