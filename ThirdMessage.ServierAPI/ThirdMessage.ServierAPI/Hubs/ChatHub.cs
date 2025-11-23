using Microsoft.AspNetCore.SignalR;
using ThirdMessage.ServierAPI.Helper;
using ThirdMessage.ServierAPI.Models;

namespace ThirdMessage.ServierAPI.Hubs;

public class ChatHub : Hub
{
    public async Task SendMessage(string user, string message)
    {
        var response = new ReplyModel<EmptyModel> 
        { 
            Message = "正常响应",
            Code = 0,
            Model = new EmptyModel()
        };
        await Clients.All.SendAsync("ReceiveMessage", response);
    }
}
