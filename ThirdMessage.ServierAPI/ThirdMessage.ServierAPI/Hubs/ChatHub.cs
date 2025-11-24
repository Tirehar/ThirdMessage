using Microsoft.AspNetCore.SignalR;
using ThirdMessage.ServierAPI.Helper;
using ThirdMessage.ServierAPI.Models;
using ThirdMessage.ServierAPI.Models.ReplyModels;

namespace ThirdMessage.ServierAPI.Hubs;

public class ChatHub : Hub
{
    public async Task SendMessage(string json)
    {
        var model = JsonHelper.ToModel<MessageModel>(json);
        Console.WriteLine("服务端收到消息" + model.Message);
        var response = new ReplyModel<EmptyModel> 
        { 
            Message = "正常响应",
            Code = 0,
            Model = new EmptyModel()
        };
        await Clients.All.SendAsync("ReceiveMessage", response);
    }
}
