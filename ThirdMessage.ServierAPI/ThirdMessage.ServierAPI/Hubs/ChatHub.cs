using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.SignalR;
using ThirdMessage.ServierAPI.Database;
using ThirdMessage.ServierAPI.Database.Entitys;
using ThirdMessage.ServierAPI.Helper;
using ThirdMessage.ServierAPI.Models;
using ThirdMessage.ServierAPI.Models.ReplyModels;

namespace ThirdMessage.ServierAPI.Hubs;

public class ChatHub : Hub
{
    private readonly ApplicationDbContext database;
    private readonly UserManager<UserEntity> userManager;
    private readonly ILogger<ChatHub> logger;
    public ChatHub(ApplicationDbContext dbContext, UserManager<UserEntity> userManager, ILogger<ChatHub> logger)
    {
        this.database = dbContext;
        this.userManager = userManager;
        this.logger = logger;
    }
    //[Authorize]
    public async Task SendMessage(string json)
    {
        var model = JsonHelper.ToModel<MessageModel>(json);
        var user = await userManager.FindByIdAsync(model.Uid);
        var firendUser = await userManager.FindByIdAsync(model.ToUid);
        if (user != null && firendUser != null) 
        {
            //加载发送者好友列表
            await database.Entry(user).Collection(u => u.Friends).LoadAsync();
            var firend = user.Friends.FirstOrDefault(f => f.Uid == model.ToUid)!;

            //加载接收者好友列表
            await database.Entry(firendUser).Collection(u => u.Friends).LoadAsync();
            var firendOfFirend = firendUser.Friends.FirstOrDefault(f => f.Uid == model.Uid)!;

            //加载消息列表
            await database.Entry(firend).Collection(u => u.Messages).LoadAsync();
            await database.Entry(firendOfFirend).Collection(u => u.Messages).LoadAsync();

            var entityForSender = new MessageEntity
            {
                FromUserId = model.Uid,
                ToUserId = model.ToUid,
                Content = model.Message,
                Timestamp = model.Time
            };
            var entityForReceiver = new MessageEntity
            {
                FromUserId = model.Uid,
                ToUserId = model.ToUid,
                Content = model.Message,
                Timestamp = model.Time
            };

            firend.Messages.Add(entityForSender);
            firendOfFirend.Messages.Add(entityForReceiver);
            await database.SaveChangesAsync();
            var response = new ReplyModel<MessageReplyModel>
            {
                Message = "Send Success",
                Code = 0,
                Model = new()
                {
                    FromUid = model.Uid,
                    ToUid = model.ToUid,
                    Content = model.Message,
                    Time = model.Time
                }
            };
            logger.LogInformation("User {Uid} sent message to {ToUid}: {Message}", model.Uid, model.ToUid, model.Message);
            await Clients.All.SendAsync("ReceiveMessage", JsonHelper.ToJson(response));
        }
    }
}
