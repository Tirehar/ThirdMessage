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
    public ChatHub(ApplicationDbContext dbContext, UserManager<UserEntity> userManager)
    {
        this.database = dbContext;
        this.userManager = userManager;
    }
    //[Authorize]
    public async Task SendMessage(string json)
    {
        var model = JsonHelper.ToModel<MessageModel>(json);
        //将消息存储到数据库
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
        await Clients.All.SendAsync("ReceiveMessage", JsonHelper.ToJson(response));
    }
}
